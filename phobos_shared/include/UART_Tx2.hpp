#ifndef UART_TX_HPP_
#define UART_TX_HPP_

#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include <stdlib.h>
#include <string>
#include <cstring>

#include "UART_Shared.hpp"
#include "Sys64Coder.hpp"

#define UART_TX_BUFF_SIZE 32

class UART_Tx{
private:
    int uart0_filestream;
    struct termios options;

public:
    char* CBUFFOR;

public:
    UART_Tx(const char* device_addres){
        // Open UART device
        uart0_filestream = -1;
        uart0_filestream = open(device_addres, O_RDWR | O_NOCTTY);
        if(uart0_filestream == -1){
            printf("ERROR - Unable to acces UART\n");
        }

        // UART device settings
        tcgetattr(uart0_filestream, &options);
        options.c_cc[VMIN] = SHARED_C_CC_VMIN;
        options.c_cflag = SHARED_C_CFLAG;
        options.c_iflag = SHARED_C_IFLAG;
        options.c_oflag = SHARED_C_OFLAG;
        options.c_lflag = SHARED_C_LFLAG;
        tcflush(uart0_filestream, TCIFLUSH);
        tcsetattr(uart0_filestream, TCSANOW, &options);

        CBUFFOR = (char*)malloc(UART_TX_BUFF_SIZE);

    }

    ~UART_Tx(){
        close(uart0_filestream);
    }

    void Transmit(int buff_size){
        // Transmiting bytes
        if (uart0_filestream != -1){
            int count = write(uart0_filestream, (const void*)CBUFFOR, buff_size);
            if(count < 0){
                printf("'UART TX error code: %d'\n", count);
            }
        }

        printf("*** TX:%s\n", this->CBUFFOR);
    }
};


template <typename FrameType>
class UART_Tx_Encoder{
private:
    UART_Tx* TX;
    int data_num, data_size, buff_size;
public:
    FrameType FRAME;

public:
    UART_Tx_Encoder(UART_Tx* TX, int data_num, int data_size, int buff_size){
        this->TX = TX;
        this->data_num = data_num;
        this->data_size = data_size;
        this->buff_size = buff_size;

        this->FRAME.header.type='X';
        this->FRAME.header.ctrl=0;
        this->FRAME.header.csum=0;

        for(int i = 0; i < data_num; i++){
            this->FRAME.data[i] = 0;
        }

    }

    void CopyToBuffor(const char* data, int begin, int length){
        memcpy((void*)(TX->CBUFFOR + begin), (const void*)data, length);
    }

    void CopyToBuffor(int data, int begin){
        *(TX->CBUFFOR + begin) = (char)data;
        // memcpy((void*)(TX->CBUFFOR + begin), (const void*)data, length);
    }

    void EncodeToBuffor(int data, int begin, int length){
        Sys64_Int2Char(data, (TX->CBUFFOR + begin), length);
    }

    void EncodeBuffor(){
        CopyToBuffor(&FRAME_BEGIN_CHAR, 0, BEGIN_LEN);
        CopyToBuffor(FRAME.header.type, FRAME_TYPE_BEGIN);
        EncodeToBuffor(FRAME.header.ctrl, FRAME_CTRL_BEGIN, CTRL_LEN);

        for(int i = 0; i < this->data_num; i++){
            EncodeToBuffor(FRAME.data[i], FRAME_DATA_BEGIN + i*this->data_size, this->data_size);
        }
        CopyToBuffor(&FRAME_END_CHAR, FRAME_DATA_BEGIN + this->data_size * this->data_size, END_LEN);

        EncodeToBuffor(this->ControlSum(), FRAME_CSUM_BEGIN, CSUM_LEN);

        printf("//TX// type: %c  data_num: %d  data_size: %d, buff_size: %d", FRAME.header.type, data_num, data_size, buff_size);

    }

    int32_t ControlSum(){
        uint32_t control_sum = 0;

        for(int i = FRAME_TYPE_BEGIN; i < FRAME_CSUM_BEGIN; i++){
            control_sum += *(TX->CBUFFOR + i);
        }

        for(int i = FRAME_DATA_BEGIN; i < this->buff_size - END_LEN; i++){
            control_sum += *(TX->CBUFFOR + i);
        }

        printf("ControlSum: %d\n", control_sum);

        return control_sum;
    }
};

#endif
