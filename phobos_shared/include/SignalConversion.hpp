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
        InType input_min;
        InType input_max;

        OutType output_min;
        OutType output_max;

        float trans_min;
        float trans_max;

        int sys64_order;


    public:
        SignalConversion(InType input_min, InType input_max, OutType output_min, OutType output_max, int sys64_order){
            this->input_min = input_min;
            this->input_max = input_max;

            this->output_min = output_min;
            this->output_max = output_max;

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

        int ToTransmissionSystem(InType input){
            return (int)((input - input_min)/(input_max - input_min)*(trans_max - trans_min) + trans_min);
        }

        OutType FromTransmissionSystem(int input){
            return (OutType)((input - trans_min)/(trans_max - trans_min)*(output_max - output_min) + output_min);
        }
    };

};

#endif
