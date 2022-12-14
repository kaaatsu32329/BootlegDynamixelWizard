#ifndef DYNAMIXEL_MANAGER_HPP
#define DYNAMIXEL_MANAGER_HPP

#include <vector>

#include "dynamixel_sdk.h"
#include "DynamixelMotor.hpp"

class DynamixelManager
{
    dynamixel::PortHandler *m_portHandler;
    dynamixel::PacketHandler *m_packetHandler;

    std::vector<std::pair<int, DynamixelMotor>> m_motors;

public:
    DynamixelManager();
    ~DynamixelManager();

    void setupTask();

    void send();

    void set_value();

    void updatePositionControl(uint32_t motor1_target, uint32_t motor2_target);

    void updateVelocityControl(int32_t motor1_target, int32_t motor2_target);
    void updateTorqueControl(int32_t motor1_target, int32_t motor2_target);
};

#endif /* DYNAMIXEL_MANAGER_HPP */