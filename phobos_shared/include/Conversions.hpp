#ifndef MY_CONVERSIONS_HPP_
#define MY_CONVERSIONS_HPP_
//
// namespace conv{

    ///////////////////////////////// POSITION

    float POSE_MAX = 1000;
    float POSE_MIN = -1000;

    float POSE_RESOLUTION = 0.01;
    float POSE_INTMAX = (POSE_MAX / POSE_RESOLUTION);
    float POSE_INTMIN = (POSE_MIN / POSE_RESOLUTION);

    int Pose_Float2Int(float input){
        if(input > POSE_MAX) input = POSE_MAX;
        if(input < POSE_MIN) input = POSE_MIN;

        return (int) (input / POSE_RESOLUTION);
    };

    float Pose_Int2Float(int input){
        if(input > POSE_INTMAX) input = POSE_INTMAX;
        if(input < POSE_INTMIN) input = POSE_INTMIN;

        return (float) (input * POSE_RESOLUTION);
    };


    ///////////////////////////////// ORIENTATION

    float ORIENT_MAX = 1;
    float ORIENT_MIN = -1;

    float ORIENT_RESOLUTION = 0.001;
    float ORIENT_INTMAX = (ORIENT_MAX / ORIENT_RESOLUTION);
    float ORIENT_INTMIN = (ORIENT_MIN / ORIENT_RESOLUTION);

    int Orient_Float2Int(float input){
        if(input > ORIENT_MAX) input = ORIENT_MAX;
        if(input < ORIENT_MIN) input = ORIENT_MIN;

        return (int) (input / ORIENT_RESOLUTION);
    };

    float Orient_Int2Float(int input){
        if(input > ORIENT_INTMAX) input = ORIENT_INTMAX;
        if(input < ORIENT_INTMIN) input = ORIENT_INTMIN;

        return (float) (input * ORIENT_RESOLUTION);
    };

    ////////////////////////////////// WHEELS_VEL

    // float WHEELS_VEL_FLOAT_MAX = 1;
    // float WHEELS_VEL_INT_MAX = 256;
    //
    // int WheelsVel_Float2Int(float input){
    //     if(input > WHEELS_VEL_FLOAT_MAX) input = WHEELS_VEL_FLOAT_MAX;
    //     if(input < -WHEELS_VEL_FLOAT_MAX) input = -WHEELS_VEL_FLOAT_MAX;
    //
    //     return (int) (input * WHEELS_VEL_INT_MAX / WHEELS_VEL_FLOAT_MAX);
    // }
    //
    // float WHEELS_IMPS_PER_ROT = 1000;
    //
    // float WheelsVel_Imps2Rots(int impulses){
    //     return ((float) impulses) / WHEELS_IMPS_PER_ROT;
    // }
    //
    // float WheelsVel_Imps2Rads(int impulses){
    //     return ((float) impulses) / WHEELS_IMPS_PER_ROT * 2 * 3.1416;
    // }
    //
    // ////////////////////////////////// ARM_VEL
    //
    // float LINK_VEL_FLOAT_MAX[6];
    // float LINK_VEL_INT_MAX[6];
    //
    // LINK_VEL_FLOAT_MAX[0] = 1;
    // LINK_VEL_FLOAT_MAX[1] = 1;
    // LINK_VEL_FLOAT_MAX[2] = 1;
    // LINK_VEL_FLOAT_MAX[3] = 1;
    // LINK_VEL_FLOAT_MAX[4] = 1;
    // LINK_VEL_FLOAT_MAX[5] = 1;
    //
    // LINK_VEL_INT_MAX[0] = 256;
    // LINK_VEL_INT_MAX[1] = 256;
    // LINK_VEL_INT_MAX[2] = 256;
    // LINK_VEL_INT_MAX[3] = 256;
    // LINK_VEL_INT_MAX[4] = 256;
    // LINK_VEL_INT_MAX[5] = 256;
    //
    // float ArmVel_

// }

#endif
