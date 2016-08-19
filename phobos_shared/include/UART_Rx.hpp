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

template <typename FrameType>
class UART_Rx{
private:
    int uart0_filestream;
    struct termios options;
protected:
    int rx_length;
    int data_num;
    int buff_size;
public:
    FrameType WORD;
    std::string BUFFOR;
    char* CBUFFOR;

public:
    UART_Rx(const char* device_addres, const int data_num, const int buff_size){
        this->data_num = data_num;
        this->buff_size = buff_size;
        // Open UART device
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

        CBUFFOR = (char*)malloc(buff_size);
    }

    ~UART_Rx(){
        close(uart0_filestream);
    }

    bool ReadBuffer(){
        rx_length = read(uart0_filestream, (void*)WORD.buffor, sizeof(WORD));

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

    bool ReadBufferAsString(){
        BUFFOR.clear();
        rx_length = read(uart0_filestream, (void*)BUFFOR.data(), data_num * 5 + 16);

        printf("Rx BUFFOR: %s \n", BUFFOR.c_str());

        if(rx_length == 0){
            return false;
        }
        else if(rx_length > 0){
            // std::string temp_buff;
            std::stringstream stream(BUFFOR);
            int temp_buff;
            for(int i = 0; i < data_num; i++){
                stream >> temp_buff;
                *(WORD.begin + i) = temp_buff;
            //     *(WORD.begin + i) = std::stoi(temp_buff);
                // stream >> *(WORD.begin + i);
            }
            stream >> temp_buff;
            WORD.control_sum = temp_buff;
            // WORD.control_sum = std::stoi(temp_buff);
            // stream >> WORD.control_sum;

            return true;
        }
        else{
            printf("UART RX ERROR!\n");
            return false;
        }
    }

    bool ReadBufferAsChar(){
        rx_length = read(uart0_filestream, (void*)CBUFFOR, buff_size);

        printf("Rx BUFFOR: %s \n", CBUFFOR);

        if(rx_length == 0){
            return false;
        }
        else if(rx_length > 0){
            for(int i = 0; i < data_num; i++){
                char temp_buff[4];
                memcpy(temp_buff,(CBUFFOR + 4*i), 4);
                *(WORD.begin + i) = std::atoi(temp_buff);
            }
            char temp_buff[6];
            memcpy(temp_buff, CBUFFOR + 4*data_num, 6);
            WORD.control_sum = std::atoi(temp_buff);

            return true;
        }
        else{
            printf("UART RX ERROR!\n");
            return false;
        }
    }


    bool ReadBufferAsChar64(){
        rx_length = read(uart0_filestream, (void*)CBUFFOR, buff_size);


        if(rx_length == 0){
            return false;
        }
        else if(rx_length > 0){
            printf("Rx BUFFOR: %s \n", CBUFFOR);

            for(int i = 0; i < data_num; i++){
                Sys64Coder3 coder(CBUFFOR + 3*i);
                *(WORD.begin + i) = coder.decimal;
            }
            Sys64Coder4 coder(CBUFFOR + 3*data_num);
            WORD.control_sum = coder.decimal;

            return true;
        }
        else{
            printf("UART RX ERROR!\n");
            return false;
        }
    }


    bool CheckControlSum(){
        int32_t control_sum = 0;

        // Control sum calculated as sum of all WORD's data elements
        for(int i = 0; i < data_num; i++){
            control_sum += *(WORD.begin + i);
        }

        if(control_sum == WORD.control_sum){
            return true;
        }else{
            printf("WRONG CONTROL SUM!!!\n");
            printf("Calculated: %d    Recived: %d\n", control_sum, WORD.control_sum);
            return false;
        }
    }
};

#endif
