// Reference: https://emanual.robotis.com/docs/en/dxl/x/xm430-w350/

#define ADDR_MODEL_NUMBER 0           // size 2
#define ADDR_MODEL_INFORMATION 2      // size 4
#define ADDR_FIRMWARE_VERSION 6       // size 1
#define ADDR_ID 7                     // size 1
#define ADDR_BAUD_RATE 8              // size 1
#define ADDR_DRIVE_MODE 10            // size 2
#define ADDR_OPERATING_MODE 11        // size 1
#define ADDR_SECONDARY_ID 12          // size 1
#define ADDR_PROTOCOL_TYPE 13         // size 1
#define ADDR_HOMING_OFFSET 20         // size 4
#define ADDR_MOVING_THRESHOLD 24      // size 4
#define ADDR_TEMPERATURE_LIMIT 31     // size 1
#define ADDR_MAX_VOLTAGE_LIMIT 32     // size 2
#define ADDR_MIN_VOLTAGE_LIMIT 34     // size 2
#define ADDR_PWM_LIMIT 36             // size 2
#define ADDR_CURRENT_LIMIT 38         // size 2
#define ADDR_VELOCITY_LIMIT 44        // size 4
#define ADDR_MAX_POSITION_LIMIT 48    // size 4
#define ADDR_MIN_POSITION_LIMIT 52    // size 4
#define ADDR_STARTUP_CONFIGURATION 60 // size 1
#define ADDR_SHUTDOWN 63              // size 1

#define ADDR_TORQUE_ENABLE 64          // size 1
#define ADDR_LED 65                    // size 1
#define ADDR_STATUS_RETURN_LEVEL 68    // size 1
#define ADDR_REGISTERED_INSTRUCTION 69 // size 1
#define ADDR_HARDWARE_ERROR_STATUS 70  // size 1
#define ADDR_VELOCITY_I_GAIN 76        // size 2
#define ADDR_VELOCITY_P_GAIN 78        // size 2
#define ADDR_POSITION_D_GAIN 80        // size 2
#define ADDR_POSITION_I_GAIN 82        // size 2
#define ADDR_POSITION_P_GAIN 84        // size 2
#define ADDR_FEEDFORWARD_2ND_GAIN 88   // size 2
#define ADDR_FEEDFORWARD_1ST_GAIN 90   // size 2
#define ADDR_BUS_WATCHING 98           // size 1
#define ADDR_GOAL_PWM 100              // size 2
#define ADDR_GOAL_CURRENT 102          // size 2
#define ADDR_GOAL_VELOCITY 104         // size 4
#define ADDR_PROFILE_ACCELERATION 108  // size 4
#define ADDR_PROFILE_VELOCITY 112      // size 4
#define ADDR_GOAL_POSITION 116         // size 4
#define ADDR_REALTIME_TICK 120         // size 2
#define ADDR_MOVING 122                // size 1
#define ADDR_MOVING_STATUS 123         // size 1
#define ADDR_PRESENT_PWM 124           // size 2
#define ADDR_PRESENT_CURRENT 126       // size 2
#define ADDR_PRESENT_VELOCITY 128      // size 4
#define ADDR_PRESENT_POSITION 132      // size 4
#define ADDR_VELOCITY_TRAJECTORY 136   // size 4
#define ADDR_POSITION_TRAJECTORY 140   // size 4
#define ADDR_PRESENT_INPUT_VOLTAGE 144 // size 2
#define ADDR_PRESENT_TEMPERATURE 146   // size 1
#define ADDR_BACKUP_READY 147          // size 1

#define ADDR_INDIRECT_ADDRESS(index) index > 28 ? (166 + 2 * index) : (576 + 2 * index) // size 2, index 1~28
#define ADDR_INDIRECT_DATA(index) index > 28 ? (223 + index) : (633 + index)            // size 1, index 1~56
