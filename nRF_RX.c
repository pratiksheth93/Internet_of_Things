#include "mbed.h"
#include "nRF24L01P.h"

Serial pc(USBTX, USBRX); // tx, rx

nRF24L01P my_nrf24l01p(PTD6, PTE3, PTE2, PTB8, PTB9, PTD0);    // mosi, miso, sck, csn, ce, irq
DigitalOut GreenLED(LED2);


int main() {
    
    char count[2];
    char RxDataCnt;
    char temp;

    my_nrf24l01p.powerUp();
    my_nrf24l01p.setRfFrequency(2450);

    // Display the (default) setup of the nRF24L01+ chip
    pc.printf( "nRF24L01+ Frequency    : %d MHz\r\n",  my_nrf24l01p.getRfFrequency() );
    pc.printf( "nRF24L01+ Output power : %d dBm\r\n",  my_nrf24l01p.getRfOutputPower() );
    pc.printf( "nRF24L01+ Data Rate    : %d kbps\r\n", my_nrf24l01p.getAirDataRate() );
    pc.printf( "nRF24L01+ TX Address   : 0x%010llX\r\n", my_nrf24l01p.getTxAddress() );
    pc.printf( "nRF24L01+ RX Address   : 0x%010llX\r\n", my_nrf24l01p.getRxAddress() );

    pc.printf( "Simple 2 Byte Receiver\r\n" );
    
    RxDataCnt = 2;
    my_nrf24l01p.setTransferSize( RxDataCnt );
    
    my_nrf24l01p.setReceiveMode(); //setting receive mode
    my_nrf24l01p.enable(); // enables reception

    while (1) {

        // If we've received anything in the nRF24L01+...
        if ( my_nrf24l01p.readable() ) { //count of data is given so that hw much data is stored in he buffer

            // ...read the data into the receive buffer
            temp = my_nrf24l01p.read( NRF24L01P_PIPE_P0, count, RxDataCnt ); //copy 2 bytes frm receive buffer on count


            pc.printf( "Cnt %d = %d %d\r\n",temp,count[0],count[1]);


            // Toggle LED2 (to help debug nRF24L01+ -> Host communication)
            GreenLED = !GreenLED;
            wait_ms(10);
        }
    }
}
