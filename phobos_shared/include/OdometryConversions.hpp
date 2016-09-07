#ifndef MY_ODOMETRY_CONVERSIONS_HPP_
#define MY_ODOMETRY_CONVERSIONS_HPP_
//
namespace conv{

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
};

#endif
