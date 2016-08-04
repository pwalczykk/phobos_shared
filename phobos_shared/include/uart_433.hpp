#ifndef SHARED_UART_433_HPP_
#define SHARED_UART_433_HPP_

#define TELEOPERATION_DATA_NUM 9
union FrameTeleoperation{
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
union FrameTelemetry{
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
