#include "mbed.h"
#include "nRF24L01P.h"

Serial pc(USBTX, USBRX); // tx, rx

nRF24L01P my_nrf24l01p(PTD6, PTE3, PTE2, PTB8, PTB9, PTD0);    // mosi, miso, sck, csn, ce, irq
DigitalOut RedLED(LED1);

int main()
{
    char count[2]; // array of 2 elements
    char TxDataCnt;
    char temp;


    my_nrf24l01p.powerUp(); //power up devices
    my_nrf24l01p.setRfFrequency(2450); // set frequency

    // Display the (default) setup of the nRF24L01+ chip
    pc.printf( "nRF24L01+ Frequency    : %d MHz\r\n",  my_nrf24l01p.getRfFrequency() );
    pc.printf( "nRF24L01+ Output power : %d dBm\r\n",  my_nrf24l01p.getRfOutputPower() );
    pc.printf( "nRF24L01+ Data Rate    : %d kbps\r\n", my_nrf24l01p.getAirDataRate() );
    pc.printf( "nRF24L01+ TX Address   : 0x%010llX\r\n", my_nrf24l01p.getTxAddress() );
    pc.printf( "nRF24L01+ RX Address   : 0x%010llX\r\n", my_nrf24l01p.getRxAddress() );

    pc.printf( "Simple Transmitter (0 - 9 Counter) \r\n");

    TxDataCnt = 2; //transmits packets when we have 2 bytes
    my_nrf24l01p.setTransferSize(TxDataCnt); // transmitter buffer there is a utility to check the value

    my_nrf24l01p.enable(); //enables transmission mode

    count[0] = 0x01;
    count[1] = 0x01;

    while (1) {

        // Send the Transmit buffer via the nRF24L01+
        temp = my_nrf24l01p.write( NRF24L01P_PIPE_P0,count, TxDataCnt );//write something on transmission buffer count=array we copy only 2 bytes

        pc.printf( "Sending %d - %d %d\r\n",temp,count[0],count[1]); //count0 n count 1 are printed on my terminal

        // Toggle LED1 (to help debug Host -> nRF24L01+ communication)
        RedLED = !RedLED;
            
        count[1]++;
        
        wait(1);
    }
}
