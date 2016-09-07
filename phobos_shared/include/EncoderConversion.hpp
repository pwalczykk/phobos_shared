#ifndef JOINTCONFIG_HPP_
#define JOINTCONFIG_HPP_

namespace enc_conv{
    class EncoderConversion{
        double max_pose;
        double min_pose;
        double imp_per_rad;

    public:
        EncoderConversion(double min_pose, double max_pose, int imp_per_rot){
            this->max_pose = max_pose;
            this->min_pose = min_pose;
            this->imp_per_rad = imp_per_rot / 3.1415;

        }

        float Imp2Rad(int impulses){
            return impulses / imp_per_rad + min_pose;
        }

        int Rad2Imp(double radians){
            return (radians - min_pose) * imp_per_rad;
        }

    };

    EncoderConversion link0(-3.00, 3.00, 10000);
    EncoderConversion link1(-1.25, 1.60, 10000);
    EncoderConversion link2( 0.00, 3.65, 10000);
    EncoderConversion link3(-2.30, 1.10, 10000);
    EncoderConversion link4(-3.14, 3.14, 10000);
    EncoderConversion grip(0.00, 0.09, 10000);

    EncoderConversion wheel( -3.14, 3.14, 10000);

    EncoderConversion rocker(-0.50, 0.50, 10000);
    EncoderConversion bogie( -0.50, 0.50, 10000);
}

#endif
