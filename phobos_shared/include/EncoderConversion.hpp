#ifndef JOINTCONFIG_HPP_
#define JOINTCONFIG_HPP_

class JointConfig{
    double max_pose;
    double min_pose;
    double imp_per_rad;

public:
    JointConfig(double min_pose, double max_pose, int imp_per_rot){
        this->max_pose = max_pose;
        this->min_pose = min_pose;
        this->imp_per_rad = imp_per_rot / 3.1415;

    }

    double IMP2RAD(int impulses){
        return impulses / imp_per_rad + min_pose;
    }

    int RAD2IMP(double radians){
        return (radians - min_pose) * imp_per_rad;
    }

};

JointConfig LINK_0(-3.00, 3.00, 10000);
JointConfig LINK_1(-1.25, 1.60, 10000);
JointConfig LINK_2( 0.00, 3.65, 10000);
JointConfig LINK_3(-2.30, 1.10, 10000);
JointConfig LINK_4(-3.14, 3.14, 10000);
JointConfig GRIPPER(0.00, 0.09, 10000);
JointConfig WHEEL( -3.14, 3.14, 10000);
JointConfig ROCKER(-0.50, 0.50, 10000);
JointConfig BOGIE( -0.50, 0.50, 10000);

#endif
