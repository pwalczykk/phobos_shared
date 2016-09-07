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
        printf("WRONG CHAR TO CONVERT: %c\n", value);
    }
}

class Sys64Coder1{
public:
    int decimal;
    char sys64[1];
public:
    Sys64Coder1(int decimal){
        this->decimal = decimal;

        int unsigned_decimal = decimal + 32;
        this->sys64[0] = Encode64(unsigned_decimal);
    }

    Sys64Coder1(char* sys64){
        this->sys64[0] = *(sys64+0);

        this->decimal = Decode64(sys64[0]) - 32;
    }
};

class Sys64Coder2{
public:
    int decimal;
    char sys64[2];
public:
    Sys64Coder2(int decimal){
        this->decimal = decimal;

        int unsigned_decimal = decimal + 2048;
        this->sys64[0] = Encode64(unsigned_decimal / 64);
        this->sys64[1] = Encode64(unsigned_decimal % 64);
    }

    Sys64Coder2(char* sys64){
        this->sys64[0] = *(sys64+0);
        this->sys64[1] = *(sys64+1);

        this->decimal = 64*Decode64(sys64[0]) + Decode64(sys64[1]) - 2048;
    }
};

class Sys64Coder3{
public:
    int decimal;
    char sys64[3];
public:
    Sys64Coder3(int decimal){
        this->decimal = decimal;

        int unsigned_decimal = decimal + 131072;
        this->sys64[0] = Encode64(unsigned_decimal / 4096);
        this->sys64[1] = Encode64((unsigned_decimal % 4096)/64);
        this->sys64[2] = Encode64(unsigned_decimal % 64);
    }

    Sys64Coder3(char* sys64){
        this->sys64[0] = *(sys64+0);
        this->sys64[1] = *(sys64+1);
        this->sys64[2] = *(sys64+2);

        this->decimal = 4096*Decode64(sys64[0]) + 64*Decode64(sys64[1]) + Decode64(sys64[2]) - 131072;
    }
};

class Sys64Coder4{
public:
    int decimal;
    char sys64[4];
public:
    Sys64Coder4(int decimal){
        this->decimal = decimal;

        int unsigned_decimal = decimal + 8388608;
        this->sys64[0] = Encode64(unsigned_decimal / 262144);
        this->sys64[1] = Encode64((unsigned_decimal % 262144)/4096);
        this->sys64[2] = Encode64((unsigned_decimal % 4096)/64);
        this->sys64[3] = Encode64((unsigned_decimal % 64)/1);
    }

    Sys64Coder4(char* sys64){
        this->sys64[0] = *(sys64+0);
        this->sys64[1] = *(sys64+1);
        this->sys64[2] = *(sys64+2);
        this->sys64[3] = *(sys64+3);

        this->decimal = 262144*Decode64(sys64[0]) + 4096*Decode64(sys64[1]) + 64*Decode64(sys64[2]) + Decode64(sys64[3]) - 8388608;
    }
};

int Sys64_Char2Int(char* input, int length){
    switch(length){
        case 1:{
            Sys64Coder1 coder(input);
            return coder.decimal;
        }
        case 2:{
            Sys64Coder2 coder(input);
            return coder.decimal;
        }
        case 3:{
            Sys64Coder3 coder(input);
            return coder.decimal;
        }
        case 4:{
            Sys64Coder4 coder(input);
            return coder.decimal;
        }
        default:
            return 0;
    }
}

void Sys64_Char2Int(char* input, int* output, int length){
    switch(length){
        case 1:{
            Sys64Coder1 coder(input);
            *output = coder.decimal;
            break;
        }
        case 2:{
            Sys64Coder2 coder(input);
            *output = coder.decimal;
            break;
        }
        case 3:{
            Sys64Coder3 coder(input);
            *output = coder.decimal;
            break;
        }
        case 4:{
            Sys64Coder4 coder(input);
            *output = coder.decimal;
            break;
        }

        return;
    }
};

void Sys64_Int2Char(int input, char* output, int length){
    switch(length){
        case 1:{
            Sys64Coder1 coder(input);
            *(output+0) = coder.sys64[0];
            break;
        }
        case 2:{
            Sys64Coder2 coder(input);
            *(output+0) = coder.sys64[0];
            *(output+1) = coder.sys64[1];
            break;
        }
        case 3:{
            Sys64Coder3 coder(input);
            *(output+0) = coder.sys64[0];
            *(output+1) = coder.sys64[1];
            *(output+2) = coder.sys64[2];
            break;
        }
        case 4:{
            Sys64Coder4 coder(input);
            *(output+0) = coder.sys64[0];
            *(output+1) = coder.sys64[1];
            *(output+2) = coder.sys64[2];
            *(output+3) = coder.sys64[3];
            break;
        }

        return;
    }
};

#endif
