#ifndef SHARED_UART_433_HPP_
#define SHARED_UART_433_HPP_

#include <termios.h>
#define SHARED_C_CC_VMIN 1
#define SHARED_C_CFLAG B115200 | CS8 | CLOCAL | CREAD
#define SHARED_C_IFLAG IGNPAR
#define SHARED_C_OFLAG 0
#define SHARED_C_LFLAG 0


#define TELEOPERATION_DATA_NUM 9
#define TELEOPERATION_DATA_LENGTH 3         // Length in chars number, eg. length of 9999 is 4
#define TELEOPERATION_CTRL_SUM_LENGTH 4
#define TELEOPERATION_BUFFOR_SIZE (TELEOPERATION_DATA_NUM*TELEOPERATION_DATA_LENGTH + TELEOPERATION_CTRL_SUM_LENGTH + 2)
union FrameTeleoperation{
    // struct {
    //     char buffor[TELEOPERATION_BUFFOR_SIZE];
    // };
    struct{
        int32_t wheels_left;
        int32_t wheels_right;

        int32_t link_0;
        int32_t link_1;
        int32_t link_2;
        int32_t link_3;
        int32_t link_4;
        int32_t grip_force;

        int32_t control_mode;
        int32_t control_sum;
    };

    struct{
        int32_t begin[TELEOPERATION_DATA_NUM];
        // int32_t control_sum;
    };
};


// #define TELEMETRY_DATA_NUM 9  - WORKING 433
#define TELEMETRY_DATA_NUM 24
#define TELEMETRY_DATA_LENGTH 3
#define TELEMETRY_CTRL_SUM_LENGTH 4
#define TELEMETRY_BUFFOR_SIZE (TELEMETRY_DATA_NUM*TELEMETRY_DATA_LENGTH + TELEMETRY_CTRL_SUM_LENGTH + 2)
union FrameTelemetry{
    // struct{
    //     char buffor[TELEMETRY_BUFFOR_SIZE];
    // };
    struct{
        int32_t position_x;
        int32_t position_y;
        int32_t position_z;
        int32_t orientation_x;
        int32_t orientation_y;
        int32_t orientation_z;
        int32_t orientation_w;

        int32_t wheel_vel_fl;
        int32_t wheel_vel_fr;
        int32_t wheel_vel_ml;
        int32_t wheel_vel_mr;
        int32_t wheel_vel_bl;
        int32_t wheel_vel_br;

        int32_t link_pose_0;
        int32_t link_pose_1;
        int32_t link_pose_2;
        int32_t link_pose_3;
        int32_t link_pose_4;
        int32_t grip_pose;

        int32_t rocker_pose_l;
        int32_t rocker_pose_r;
        int32_t bogie_pose_l;
        int32_t bogie_pose_r;

        int32_t error_code;
        int32_t control_sum;
    };

    struct{
        int32_t begin[TELEMETRY_DATA_NUM];
        // int32_t control_sum;
    };
};

#endif
