#include <Siv3D.hpp> // OpenSiv3D v0.6.6
#include "dynamixel_sdk.h"
#include "ControlTable.hpp"

#include "Main.hpp"

#define PORT_NAME "/dev/ttyUSB0"
#define PROTOCOL 2.0
#define BAUDRATE 1000000
#define ID2 6

#define TORQUE_ENABLE 1
#define TORQUE_DISABLE 0

#define OPERATING_MODE_TORQUE 0
#define OPERATING_MODE_VELOCITY 1
#define OPERATING_MODE_POSITION 3

#define DISABLE_MODE 0
#define IN_RANGE 1
#define POSITION_MODE 2
#define VELOCITY_MODE 3
#define TORQUE_MODE 4

void Main()
{
    String title = U"Bootleg Wizard";

    double position = 0;
    double velocity = 0;
    double torque = 0;

    size_t index = DISABLE_MODE;
    size_t latest_index = DISABLE_MODE;

    dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(PORT_NAME);
    dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL);

    portHandler->setBaudRate(BAUDRATE);

    uint8_t dxl_error = 0;

    packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);

    uint32_t min_position = 0;
    packetHandler->read4ByteTxRx(portHandler, ID2, ADDR_MIN_POSITION_LIMIT, (uint32_t *)&min_position, &dxl_error);
    Print << U"Min: " << min_position;

    uint32_t max_position = 0;
    packetHandler->read4ByteTxRx(portHandler, ID2, ADDR_MAX_POSITION_LIMIT, (uint32_t *)&max_position, &dxl_error);
    Print << U"Max: " << max_position;

    uint32_t target_position = (max_position - min_position) / 2.0 + min_position;
    Print << U"Tgt: " << target_position;

    uint32_t present_position = 0;
    packetHandler->read4ByteTxRx(portHandler, ID2, ADDR_PRESENT_POSITION, (uint32_t *)&present_position, &dxl_error);
    Print << U"Pst: " << present_position;

    PIDController pid_controller = PIDController(0.2, 0.0, 0.0);

    while (System::Update())
    {
        Window::SetTitle(title);

        // Control Dynamixel motor

        SimpleGUI::RadioButtons(index, {U"Disable", U"In range", U"Position", U"Velocity", U"Torque"}, Vec2(100, 40));

        if (index == DISABLE_MODE)
        {
            Scene::SetBackground(ColorF{0.8, 0.2, 0.2});
            latest_index = DISABLE_MODE;
        }
        else
        {
            Scene::SetBackground(ColorF{0.1});
        }

        if (index == POSITION_MODE)
        {
            if (index != latest_index)
            {
                packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
                packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_OPERATING_MODE, OPERATING_MODE_POSITION, &dxl_error);
                packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
            }

            SimpleGUI::Slider(U"Position {:.0f}"_fmt(position), position, 1536, 2388, Vec2{100, 300}, 150.0, 300.0);

            if (SimpleGUI::Button(U"Rotation", Vec2{300, 40}))
            {
                uint8_t mode_position = 120;
                packetHandler->read4ByteTxRx(portHandler, ID2, ADDR_PRESENT_POSITION, (uint32_t *)&present_position, &dxl_error);
                Print << U"Pst: " << present_position;
                Print << U"Tgt: " << (int32_t)position;

                packetHandler->read1ByteTxRx(portHandler, ID2, ADDR_OPERATING_MODE, (uint8_t *)&mode_position, &dxl_error);

                packetHandler->write4ByteTxRx(portHandler, ID2, ADDR_GOAL_POSITION, (int32_t)position, &dxl_error);
            }
            latest_index = POSITION_MODE;
        }

        if (index == IN_RANGE)
        {
            if (SimpleGUI::Button(U"In Range", Vec2{300, 40}))
            {
                if (index != latest_index)
                {
                    packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
                    packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_OPERATING_MODE, OPERATING_MODE_VELOCITY, &dxl_error);
                    packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
                }

                while (present_position >= max_position || present_position <= min_position)
                {
                    packetHandler->read4ByteTxRx(portHandler, ID2, ADDR_PRESENT_POSITION, (uint32_t *)&present_position, &dxl_error);

                    velocity = (int32_t)pid_controller.calculate((double)target_position, (double)present_position);
                    if (velocity > 200)
                        velocity = 200;
                    if (velocity < -200)
                        velocity = -200;

                    packetHandler->write4ByteTxRx(portHandler, ID2, ADDR_GOAL_VELOCITY, (int32_t)velocity, &dxl_error);
                }
                packetHandler->write4ByteTxRx(portHandler, ID2, ADDR_GOAL_VELOCITY, 0, &dxl_error);
            }
            latest_index = IN_RANGE;
        }

        if (index == VELOCITY_MODE)
        {
            if (index != latest_index)
            {
                packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
                packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_OPERATING_MODE, OPERATING_MODE_VELOCITY, &dxl_error);
                packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
            }

            SimpleGUI::Slider(U"Velocity {:.0f}"_fmt(velocity), velocity, -200.0, 200.0, Vec2{100, 300}, 150.0, 300.0);

            if (SimpleGUI::Button(U"Stop", Vec2(600, 300)))
            {
                velocity = 0;
            }

            packetHandler->write4ByteTxRx(portHandler, ID2, ADDR_GOAL_VELOCITY, (int32_t)velocity, &dxl_error);
            latest_index = VELOCITY_MODE;
        }

        if (index == TORQUE_MODE)
        {
            if (index != latest_index)
            {
                packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
                packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_OPERATING_MODE, OPERATING_MODE_TORQUE, &dxl_error);
                packetHandler->write1ByteTxRx(portHandler, ID2, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
            }
            SimpleGUI::Slider(U"Torque {:.0f}"_fmt(torque), torque, -1000.0, 1000.0, Vec2{100, 300}, 150.0, 300.0);

            if (SimpleGUI::Button(U"Stop", Vec2(600, 300)))
            {
                torque = 0;
            }

            packetHandler->write4ByteTxRx(portHandler, ID2, ADDR_GOAL_VELOCITY, (int32_t)torque, &dxl_error);
            latest_index = TORQUE_MODE;
        }
    }
}
