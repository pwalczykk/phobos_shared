#ifndef JOINTPARAMS_HPP_
#define JOINTPARAMS_HPP_

#include <vector.h>
#include <string.h>

class JointParams{
    double max_pose;
    double min_pose;
    int imp_per_rot;

    double alfa;
    double beta;

public:
    JointParams(double max_pose, double min_pose, int imp_per_rot){
        this->max_pose = max_pose;
        this->min_pose = min_pose;
        this->imp_per_rot = imp_per_rot;

        this->alfa = (max_pose - min_pose) / 4096;
        this->beta = min_pose;
    }

    double Imp2Rad(int impulses){
        return alfa * impulses + beta;
    }

    int Rad2Imp(double radians){
        return (radians - beta) / alfa;
    }


};

#endif
