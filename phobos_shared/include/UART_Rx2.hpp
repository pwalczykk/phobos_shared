#ifndef UART_Rx_HPP_
#define UART_Rx_HPP_

#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include <stdlib.h>
#include <string>
#include <sstream>

#include "UART_Shared.hpp"
#include "Sys64Coder.hpp"

#define UART_RX_BUFF_SIZE 32

class UART_Rx{
private:
    int rx_length;
    int uart0_filestream;
    struct termios options;
public:
    char* CBUFFOR;


public:

    UART_Rx(const char* device_addres){
        // Open UART device
        rx_length = 0;
        uart0_filestream = -1;
        uart0_filestream = open(device_addres, O_RDWR | O_NOCTTY | O_NDELAY);
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

        CBUFFOR = (char*)malloc(UART_RX_BUFF_SIZE);
    }

    ~UART_Rx(){
        close(uart0_filestream);
    }

    bool ReadBuffor(){
        rx_length = read(uart0_filestream, (void*)CBUFFOR, UART_RX_BUFF_SIZE);

        if(rx_length == 0){
            return false;
        }
        else if(rx_length > 0){
            return true;
        }
        else{
            printf("UART RX ERROR!\n");
            return false;
        }
    }

    char DecodeMessageType(){
        if(*(CBUFFOR+0) != FRAME_BEGIN_CHAR) return 0;      // "<" - begin transmission
        return *(CBUFFOR+1);
    }

};

template <typename FrameType>
class UART_Rx_Decoder{
private:
    UART_Rx* RX;
    int data_num, data_size, buff_size;

public:
    FrameType FRAME;

public:
    UART_Rx_Decoder(UART_Rx* RX, int data_num, int data_size, int buff_size){
        this->RX = RX;
        this->data_num = data_num;
        this->data_size = data_size;
        this->buff_size = buff_size;
    }

    int DecodeFromBuffor(int begin, int length){
        return Sys64_Char2Int((RX->CBUFFOR + begin), length);
    }

    bool DecodeBuffor(){
        FRAME.header.type = DecodeFromBuffor(FRAME_TYPE_BEGIN, TYPE_LEN);
        FRAME.header.ctrl = DecodeFromBuffor(FRAME_CTRL_BEGIN, CTRL_LEN);
        // FRAME.header.csum = DecodeFromBuffor(FRAME_CSUM_BEGIN, CSUM_LEN); // Moved to CheckControlSum()

        for(int i = 0; i < this->data_num; i++){
            FRAME.data[i] = DecodeFromBuffor(FRAME_DATA_BEGIN + i*this->data_size, this->data_size);
        }
    }


    bool CheckControlSum(){
        FRAME.header.csum = DecodeFromBuffor(FRAME_CSUM_BEGIN, CSUM_LEN);
        uint32_t control_sum = 0;

        for(int i = FRAME_TYPE_BEGIN; i < FRAME_CSUM_BEGIN; i++){
            control_sum += *(RX->CBUFFOR + i);
        }

        for(int i = FRAME_DATA_BEGIN; i < this->buff_size; i++){
            control_sum += *(RX->CBUFFOR + i);
        }

        if(control_sum == FRAME.header.csum){
            return true;
        }else{
            printf("WRONG CONTROL SUM!!!\n");
            printf("Calculated: %d    Recived: %d\n", control_sum, FRAME.header.csum);
            return false;
        }
    }
};

#endif
