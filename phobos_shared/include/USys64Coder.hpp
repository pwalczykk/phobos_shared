#ifndef MY_SYS64_HPP_
#define MY_SYS64_HPP_

#include <stdio.h>

char Encode64(int value){
    if(37 < value && value < 64){
        return (char)value + 27;
    }
    else if(11 < value && value < 38){
        return (char)value + 85;
    }
    else if(-1 < value && value < 12){
        return (char)value + 48;
    }else{
        printf("WRONG INT TO CONVERT: %i\n", (int)value);
    }
}

int Decode64(char value){
    if(64 < value && value < 91){ // A(38) - Z(63)
        return (int)value - 27;
    }
    else if(96 < value && value < 123){  // a(12) - z(37)
        return (int)value - 85;
    }
    else if(47 < value && value < 60){  // 0(0) - ;(11) (0123456789:;)
        return (int)value - 48;
    }else{
        printf("WRONG CHAR TO CONVERT: %i\n", (int)value);
    }
}


class USys64Coder2{
public:
    int decimal;
    char sys64[2];
public:
    USys64Coder2(int decimal){
        this->decimal = decimal;

        this->sys64[0] = Encode64(decimal / 64);
        this->sys64[1] = Encode64(decimal % 64);
    }

    USys64Coder2(char* sys64){
        this->sys64[0] = *(sys64+0);
        this->sys64[1] = *(sys64+1);

        this->decimal = 64*Decode64(sys64[0]) + Decode64(sys64[1]);
    }
};

class USys64Coder3{
public:
    int decimal;
    char sys64[3];
public:
    USys64Coder3(int decimal){
        this->decimal = decimal;

        this->sys64[0] = Encode64(decimal / 4096);
        this->sys64[1] = Encode64((decimal % 4096)/64);
        this->sys64[2] = Encode64(decimal % 64);
    }

    USys64Coder3(char* sys64){
        this->sys64[0] = *(sys64+0);
        this->sys64[1] = *(sys64+1);
        this->sys64[2] = *(sys64+2);

        this->decimal = 4096*Decode64(sys64[0]) + 64*Decode64(sys64[1]) + Decode64(sys64[2]);
    }
};

class USys64Coder4{
public:
    int decimal;
    char sys64[4];
public:
    USys64Coder4(int decimal){
        this->decimal = decimal;

        this->sys64[0] = Encode64(decimal / 262144);
        this->sys64[1] = Encode64((decimal % 262144)/4096);
        this->sys64[2] = Encode64((decimal % 4096)/64);
        this->sys64[3] = Encode64((decimal % 64)/1);
    }

    USys64Coder4(char* sys64){
        this->sys64[0] = *(sys64+0);
        this->sys64[1] = *(sys64+1);
        this->sys64[2] = *(sys64+2);
        this->sys64[3] = *(sys64+3);

        this->decimal = 262144*Decode64(sys64[0]) + 4096*Decode64(sys64[1]) + 64*Decode64(sys64[2]) + Decode64(sys64[3]);
    }
};

#endif
