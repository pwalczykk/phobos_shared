#ifndef SHARED_UART_433_HPP_
#define SHARED_UART_433_HPP_

#include <stdint.h>

//////////////////////////////////////////////////////////////
//////////////////////// SHARED //////////////////////////////
//////////////////////////////////////////////////////////////


// Transmission limiting chars
const char FRAME_BEGIN_CHAR = '<';
const char FRAME_END_CHAR = '>';

// Frame types available:
const char FRAME_TO_CTRL =      'C';
const char FRAME_TO_WHEELS =    'W';
const char FRAME_TO_ARM =       'A';

const char FRAME_TM_POSE =      'p';
const char FRAME_TM_ORIENT =    'o';
const char FRAME_TM_WHEELS =    'w';
const char FRAME_TM_ARM =       'a';
const char FRAME_TM_SUSP =      's';

// Const length frame elementsw:
#define BEGIN_LEN 1
#define END_LEN 1
#define TYPE_LEN 1
#define CTRL_LEN 1
#define CSUM_LEN 2

// Frame header - type, control commans and control sum
#define HEADER_LEN (TYPE_LEN + CTRL_LEN + CSUM_LEN)
struct FrameHeader{
    int32_t type;
    int32_t ctrl;
    int32_t csum;
};

// Positions of fields in transmission buffor
#define FRAME_TYPE_BEGIN (BEGIN_LEN)
#define FRAME_CTRL_BEGIN (BEGIN_LEN + TYPE_LEN)
#define FRAME_CSUM_BEGIN (BEGIN_LEN + TYPE_LEN + CSUM_LEN)
#define FRAME_DATA_BEGIN (BEGIN_LEN + HEADER_LEN)
#define EMPTY_FRAME_LEN (BEGIN_LEN + HEADER_LEN + END_LEN)

//////////////////////////////////////////////////////////////
//////////////////////// TELEOPERATION (TO) //////////////////
//////////////////////////////////////////////////////////////

#define TO_CTRL_DATA_NUM 0
#define TO_CTRL_DATA_SIZE 0
#define TO_CTRL_BUFFOR_SIZE (TO_CTRL_DATA_NUM * TO_CTRL_DATA_SIZE + EMPTY_FRAME_LEN)
union FrameTeleoperationCtrl{
    struct{
        FrameHeader header;

    };
    struct {
        int32_t head[HEADER_LEN];
        int32_t data[TO_CTRL_DATA_NUM];
    };
};

#define TO_WHEELS_DATA_NUM 2
#define TO_WHEELS_DATA_SIZE 2
#define TO_WHEELS_BUFFOR_SIZE (TO_WHEELS_DATA_NUM * TO_WHEELS_DATA_SIZE + EMPTY_FRAME_LEN)
union FrameTeleoperationWheels{
    struct{
        FrameHeader header;

        int32_t wheels_left;
        int32_t wheels_right;

    };
    struct {
        int32_t head[HEADER_LEN];
        int32_t data[TO_WHEELS_DATA_NUM];
    };
};


#define TO_ARM_DATA_NUM 6
#define TO_ARM_DATA_SIZE 2
#define TO_ARM_BUFFOR_SIZE (TO_ARM_DATA_NUM * TO_ARM_DATA_SIZE + EMPTY_FRAME_LEN)
union FrameTeleoperationArm{
    struct{
        FrameHeader header;

        int32_t link_0;
        int32_t link_1;
        int32_t link_2;
        int32_t link_3;
        int32_t link_4;
        int32_t grip;

    };
    struct {
        int32_t head[HEADER_LEN];
        int32_t data[TO_ARM_DATA_NUM];
    };
};
//////////////////////////////////////////////////////////////
//////////////////////// TELEMETRY (TM) //////////////////////
//////////////////////////////////////////////////////////////


#define TM_POSE_DATA_NUM 3
#define TM_POSE_DATA_SIZE 3
#define TM_POSE_BUFFOR_SIZE (TM_POSE_DATA_NUM * TM_POSE_DATA_SIZE + EMPTY_FRAME_LEN)
union FrameTelemetryPose{
    struct{
        FrameHeader header;

        int32_t position_x;
        int32_t position_y;
        int32_t position_z;

    };
    struct {
        int32_t head[HEADER_LEN];
        int32_t data[TM_POSE_DATA_NUM];
    };
};

#define TM_ORIENT_DATA_NUM 4
#define TM_ORIENT_DATA_SIZE 2
#define TM_ORIENT_BUFFOR_SIZE (TM_ORIENT_DATA_NUM * TM_ORIENT_DATA_SIZE + EMPTY_FRAME_LEN)
union FrameTelemetryOrient{
    struct{
        FrameHeader header;

        int32_t orientation_x;
        int32_t orientation_y;
        int32_t orientation_z;
        int32_t orientation_w;

    };
    struct {
        int32_t head[HEADER_LEN];
        int32_t data[TM_ORIENT_DATA_NUM];
    };
};

#define TM_WHEELS_DATA_NUM 6
#define TM_WHEELS_DATA_SIZE 2
#define TM_WHEELS_BUFFOR_SIZE (TM_WHEELS_DATA_NUM * TM_WHEELS_DATA_SIZE + EMPTY_FRAME_LEN)
union FrameTelemetryWheels{
    struct{
        FrameHeader header;

        int32_t wheel_vel_fl;
        int32_t wheel_vel_fr;
        int32_t wheel_vel_ml;
        int32_t wheel_vel_mr;
        int32_t wheel_vel_bl;
        int32_t wheel_vel_br;

    };
    struct {
        int32_t head[HEADER_LEN];
        int32_t data[TM_WHEELS_DATA_NUM];
    };
};

#define TM_ARM_DATA_NUM 6
#define TM_ARM_DATA_SIZE 2
#define TM_ARM_BUFFOR_SIZE (TM_ARM_DATA_NUM * TM_ARM_DATA_SIZE + EMPTY_FRAME_LEN)
union FrameTelemetryArm{
    struct{
        FrameHeader header;

        int32_t link_pose_0;
        int32_t link_pose_1;
        int32_t link_pose_2;
        int32_t link_pose_3;
        int32_t link_pose_4;
        int32_t grip_pose;

    };
    struct {
        int32_t head[HEADER_LEN];
        int32_t data[TM_ARM_DATA_NUM];
    };
};

#define TM_SUSP_DATA_NUM 4
#define TM_SUSP_DATA_SIZE 2
#define TM_SUSP_BUFFOR_SIZE (TM_SUSP_DATA_NUM * TM_SUSP_DATA_SIZE + EMPTY_FRAME_LEN)
union FrameTelemetrySusp{
    struct{
        FrameHeader header;

        int32_t rocker_pose_l;
        int32_t rocker_pose_r;
        int32_t bogie_pose_l;
        int32_t bogie_pose_r;

    };
    struct {
        int32_t head[HEADER_LEN];
        int32_t data[TM_SUSP_DATA_NUM];
    };
};

#endif
