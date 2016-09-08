#ifndef CONVERSION_HPP_
#define CONVERSION_HPP_

namespace conv{

    int Power(int input, int power){
        float output = 1;
        for(int i = 0; i < power; i++){
            output *= input;
        }
        return output;
    };

    template <typename InType, typename OutType>
    class SignalConversion{
        float input_min;
        float input_max;

        float output_min;
        float output_max;

        float trans_min;
        float trans_max;

        int sys64_order;


    public:
        SignalConversion(InType input_min, InType input_max, OutType output_min, OutType output_max, int sys64_order){
            this->input_min = (float)input_min;
            this->input_max = (float)input_max;

            this->output_min = (float)output_min;
            this->output_max = (float)output_max;

            this->sys64_order = sys64_order;

            this->trans_min = -Power(64, sys64_order)/2;
            this->trans_max = Power(64, sys64_order)/2 -1;

        }

        SignalConversion(InType input_min, InType input_max, OutType output_min, OutType output_max, int trans_min, int trans_max){
            this->input_min = input_min;
            this->input_max = input_max;

            this->output_min = output_min;
            this->output_max = output_max;

            this->sys64_order = sys64_order;

            this->trans_min = trans_min;
            this->trans_max = trans_max;

        }

        int ToTx(InType input){
            return (int)((input - input_min)/(input_max - input_min)*(trans_max - trans_min) + trans_min);
        }

        OutType FromRx(int input){
            return (OutType)(((float)input - trans_min)/(trans_max - trans_min)*(output_max - output_min) + output_min);
        }
    };

    float link0_gearbox = 10; float link0_motor = 91.66; float link0_encoder = 36;  float link0_ratio = link0_gearbox * link0_motor * link0_encoder;
    float link1_gearbox = 50; float link1_motor = 91.66; float link1_encoder = 36;  float link1_ratio = link1_gearbox * link1_motor * link1_encoder;
    float link2_gearbox = 38; float link2_motor = 67.22; float link2_encoder = 36;  float link2_ratio = link2_gearbox * link2_motor * link2_encoder;
    float link3_gearbox = 38; float link3_motor = 67.22; float link3_encoder = 36;  float link3_ratio = link3_gearbox * link3_motor * link3_encoder;
    float link4_gearbox = 6;  float link4_motor = 94.37; float link4_encoder = 36;  float link4_ratio = link4_gearbox * link4_motor * link4_encoder;
    float grip_gearbox  = 40; float grip_motor  = 19.00; float grip_encoder  = 36;  float grip_ratio = grip_gearbox * grip_motor * grip_encoder;

    float wheel_gearbox = 1;  float wheel_motor = 46.70; float wheel_encoder = 18;  float wheel_ratio = wheel_gearbox * wheel_motor * wheel_encoder;



    // TODO : Uwzględnić kąty manipulatora!
    //
    // JointConfig LINK_0(-3.00, 3.00, 10000);
    // JointConfig LINK_1(-1.25, 1.60, 10000);
    // JointConfig LINK_2( 0.00, 3.65, 10000);
    // JointConfig LINK_3(-2.30, 1.10, 10000);
    // JointConfig LINK_4(-3.14, 3.14, 10000);
    // JointConfig GRIPPER(0.00, 0.09, 10000);
    // JointConfig WHEEL( -3.14, 3.14, 10000);
    // JointConfig ROCKER(-0.50, 0.50, 10000);
    // JointConfig BOGIE( -0.50, 0.50, 10000);

    SignalConversion <float, int> link0_sig(-3.14, 3.14, -314, 314,2);
    SignalConversion <float, int> link1_sig(-1.25, 1.60, -125, 160,2);
    SignalConversion <float, int> link2_sig( 0.00, 3.65, 0, 365,2);
    SignalConversion <float, int> link3_sig(-2.30, 1.10, 230, 110,2);
    SignalConversion <float, int> link4_sig(-3.14, 3,14, -314, 314,2);
    SignalConversion <float, int>  grip_sig(-0.00, 1.00, 0, 100,2);

    SignalConversion <float, int> wheel_sig(-1.00, 1.00, -256, 256,2);

    SignalConversion <float, int> rocker_sig(0,1,1,1,2);
    SignalConversion <float, int> bogie_sig(0,1,1,1,2);


    SignalConversion <int, float> link0_enc(0,1000,0,1,2);
    SignalConversion <int, float> link1_enc(0,1000,0,1,2);
    SignalConversion <int, float> link2_enc(0,1000,0,1,2);
    SignalConversion <int, float> link3_enc(0,1000,0,1,2);
    SignalConversion <int, float> link4_enc(0,1000,0,1,2);
    SignalConversion <int, float> grip_enc(0,1000,0,1,2);

    SignalConversion <int, float> wheel_enc(0,1000,0,1,2);

    SignalConversion <int, float> rocker_enc(0,1000,0,1,2);
    SignalConversion <int, float> bogie_enc(0,1000,0,1,2);

};

#endif
