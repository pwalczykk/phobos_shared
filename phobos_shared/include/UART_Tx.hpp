#ifndef UART_TX_HPP_
#define UART_TX_HPP_

#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include <stdlib.h>
#include <string.h>

#include "UART_Shared.hpp"

template <typename FrameType>
class UART_Tx{
private:
    int uart0_filestream;
    struct termios options;
protected:
    int data_num;
public:
    FrameType WORD;
    std::string BUFFOR;

public:
    UART_Tx(const char* device_addres, const int data_num){
        this->data_num = data_num;
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

        const char* end_char = "\n";
        WORD.buffor[sizeof(WORD)-2] = end_char[0];
        WORD.buffor[sizeof(WORD)-1] = end_char[1];

    }

    ~UART_Tx(){
        close(uart0_filestream);
    }

    void Transmit(){
        // Transmiting bytes
        if (uart0_filestream != -1){
            int count = write(uart0_filestream, (const void*)WORD.buffor, sizeof(WORD));
            if(count < 0){
                printf("'UART TX error code: %d'\n", count);
            }
        }
    }

    void TransmitAsString(){
        if (uart0_filestream != -1){

            BUFFOR.clear();
            for(int i = 0; i < data_num; i++){
                BUFFOR += std::to_string(*(WORD.begin + i));
                BUFFOR += " ";
            }
            BUFFOR += WORD.control_sum;
            BUFFOR += "\n";

            printf("Tx BUFFOR: %s \n", BUFFOR.c_str());

            int count = write(uart0_filestream, (const void*)BUFFOR.data(), (int)BUFFOR.size());
            if(count < 0){
                printf("'UART TX error code: %d'\n", count);
            }
        }
    }

    int32_t ControlSum(){
        int32_t control_sum = 0;

        // Control sum calculated as sum of all WORD elements
        for(int i = 0; i < data_num; i++){
            control_sum += *(WORD.begin + i);
        }
        return control_sum;
    }

    void Close(){
        close(uart0_filestream);
        printf("'Closing uart'");
    }

};

#endif
