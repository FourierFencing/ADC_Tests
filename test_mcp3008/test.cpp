#include <wiringPi.h>
#include <mcp3004.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
 
#define	TRUE	            (1==1)
#define	FALSE	            (!TRUE)
#define CHAN_CONFIG_SINGLE  8
#define CHAN_CONFIG_DIFF    0
 
static int myFd ;
 
//char *usage = "Usage: mcp3008 all|analogChannel[1-8] [-l] [-ce1] [-d]";
// -l   = load SPI driver,  default: do not load
// -ce1  = spi analogChannel 1, default:  0
// -d   = differential analogChannel input, default: single ended
 
void loadSpiDriver()
{
    if (system("gpio load spi") == -1)
    {
        fprintf (stderr, "Can't load the SPI driver: %s\n", strerror (errno)) ;
        exit (EXIT_FAILURE) ;
    }
}
 
void spiSetup (int spiChannel)
{
    if ((myFd = wiringPiSPISetup (spiChannel, 1000000)) < 0)
    {
        fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
        exit (EXIT_FAILURE) ;
    }
}
 
int myAnalogRead(int spiChannel,int channelConfig,int analogChannel)
{
    if(analogChannel<0 || analogChannel>7)
        return -1;
    unsigned char buffer[3] = {1}; // start bit
    buffer[1] = (channelConfig+analogChannel) << 4;
    wiringPiSPIDataRW(spiChannel, buffer, 3);
    return ( (buffer[1] & 3 ) << 8 ) + buffer[2]; // get last 10 bits
}

int main() {
	//loadSpiDriver();
	wiringPiSetup();
	spiSetup(0);
	//mcp3004Setup (BASE, SPI_CHAN);
	int i = 10;
	int chan;
	int x;
while(1){
	//chan = 1;
	//for(chan = 0; chan < 8; ++chan){
	x = myAnalogRead (0, 8, 1-1);
	printf("%d \n", x);
	//fflush(stdout);
	sleep(1);
	//i--;
	}
	return 0;
}
