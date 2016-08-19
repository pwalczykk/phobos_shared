#ifndef MY_CONVERSIONS_HPP_
#define MY_CONVERSIONS_HPP_

#define ODOM_MAX 1000
#define ODOM_MIN -1000

#define ODOM_RESOLUTION 0.01
#define ODOM_INTMAX (ODOM_MAX / ODOM_RESOLUTION)
#define ODOM_INTMIN (ODOM_MIN / ODOM_RESOLUTION)


int32_t Odom_Float2Int(float input){
    if(input > ODOM_MAX) input = ODOM_MAX;
    if(input < ODOM_MIN) input = ODOM_MIN;

    return (int32_t) input * ODOM_RESOLUTION;
};

float Odom_Int2Float(int input){
    if(input > ODOM_INTMAX) input = ODOM_INTMAX;
    if(input < ODOM_INTMIN) input = ODOM_INTMIN;

    return (float) input / ODOM_RESOLUTION;
};

#endif
