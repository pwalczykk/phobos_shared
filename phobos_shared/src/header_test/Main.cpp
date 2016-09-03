#include "../../include/UART_Shared.hpp"

int main(int argc, char** argv){

    UART_Rx RX("/dev/ttyACM0");
    UART_Rx_Decoder <FrameTeleoperationCtrl> rx_decoder(&RX, 10, 1,20);

    RX.ReadBuffor();
    char aqq = RX.DecodeMessageType();

    rx_decoder.DecodeBuffor();
    rx_decoder.CheckControlSum();

    UART_Tx TX("/dev/ttyACM0");
    UART_Tx_Encoder <FrameTeleoperationCtrl> tx_encoder(&TX, 10, 1,20);

    tx_encoder.EncodeBuffor();
    TX.Transmit(10);


    return 0;
}
