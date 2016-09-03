#ifndef UART_CONFIG_HPP_
#define UART_CONFIG_HPP_

#include <termios.h>
#define SHARED_C_CC_VMIN 1
#define SHARED_C_CFLAG B115200 | CS8 | CLOCAL | CREAD
#define SHARED_C_IFLAG IGNPAR
#define SHARED_C_OFLAG 0
#define SHARED_C_LFLAG 0

#endif
