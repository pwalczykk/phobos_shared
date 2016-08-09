#ifndef SHARED_UART_433_HPP_
#define SHARED_UART_433_HPP_

#include <termios.h>
#define SHARED_C_CC_VMIN 1
#define SHARED_C_CFLAG B19200 | CS8 | CLOCAL | CREAD
#define SHARED_C_IFLAG IGNPAR
#define SHARED_C_OFLAG 0
#define SHARED_C_LFLAG 0


#define TELEOPERATION_DATA_NUM 9
#define TELEOPERATION_DATA_LENGTH 2         // Length in chars number, eg. length of 9999 is 4
#define TELEOPERATION_CTRL_SUM_LENGTH 3
#define TELEOPERATION_BUFFOR_SIZE (TELEOPERATION_DATA_NUM*TELEOPERATION_DATA_LENGTH + TELEOPERATION_CTRL_SUM_LENGTH + 2)
union FrameTeleoperation{
    // struct {
    //     char buffor[TELEOPERATION_BUFFOR_SIZE];
    // };
    struct{
        int16_t wheels_left;
        int16_t wheels_right;

        int16_t link_0;
        int16_t link_1;
        int16_t link_2;
        int16_t link_3;
        int16_t link_4;
        int16_t grip_force;

        int16_t control_mode;
        int32_t control_sum;
    };

    struct{
        int16_t begin[TELEOPERATION_DATA_NUM];
        // int32_t control_sum;
    };
};


#define TELEMETRY_DATA_NUM 24
#define TELEMETRY_DATA_LENGTH 2
#define TELEMETRY_CTRL_SUM_LENGTH 3
#define TELEMETRY_BUFFOR_SIZE (TELEMETRY_DATA_NUM*TELEMETRY_DATA_LENGTH + TELEMETRY_CTRL_SUM_LENGTH + 2)
union FrameTelemetry{
    // struct{
    //     char buffor[TELEMETRY_BUFFOR_SIZE];
    // };
    struct{
        int16_t position_x;
        int16_t position_y;
        int16_t position_z;
        int16_t orientation_x;
        int16_t orientation_y;
        int16_t orientation_z;
        int16_t orientation_w;

        int16_t wheel_vel_fl;
        int16_t wheel_vel_fr;
        int16_t wheel_vel_ml;
        int16_t wheel_vel_mr;
        int16_t wheel_vel_bl;
        int16_t wheel_vel_br;

        int16_t link_pose_0;
        int16_t link_pose_1;
        int16_t link_pose_2;
        int16_t link_pose_3;
        int16_t link_pose_4;
        int16_t grip_pose;

        int16_t rocker_pose_l;
        int16_t rocker_pose_r;
        int16_t bogie_pose_l;
        int16_t bogie_pose_r;

        int16_t error_code;
        int32_t control_sum;
    };

    struct{
        int16_t begin[TELEMETRY_DATA_NUM];
        // int32_t control_sum;
    };
};

#endif
