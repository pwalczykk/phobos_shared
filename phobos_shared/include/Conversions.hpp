#ifndef MY_CONVERSIONS_HPP_
#define MY_CONVERSIONS_HPP_


///////////////////////////////// POSITION

#define POSE_MAX 1000
#define POSE_MIN -1000

#define POSE_RESOLUTION 0.01
#define POSE_INTMAX (POSE_MAX / POSE_RESOLUTION)
#define POSE_INTMIN (POSE_MIN / POSE_RESOLUTION)

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

#define ORIENT_MAX 1
#define ORIENT_MIN -1

#define ORIENT_RESOLUTION 0.001
#define ORIENT_INTMAX (ORIENT_MAX / ORIENT_RESOLUTION)
#define ORIENT_INTMIN (ORIENT_MIN / ORIENT_RESOLUTION)

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

#endif
