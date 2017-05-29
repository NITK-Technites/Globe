
#include <msp430G2553.h>
/*------]]]]-------------------------------------------
TECHNITES 2016
UNIVERSAL 5916 ARRAY_SHIFTER

                        MSP430G2553
                      -----------------
            3.3 V -->|Vcc          Gnd |<-- Ground
                     |                 |
          Unused  -->|P1.0         P2.7|--> unused
                     |                 |
               Rx -->|P1.1         P2.6|--> unused
                     |                 |
               Tx <--|P1.2         TST |--> Open
                     |                 |
                  <--|P1.3         RST |<-- Pulled high
                     |                 |
               <--|P1.4         P1.7|--> SIN_5916
                     |                 |
               <--|P1.5         P1.6|--> SCLK5916
                     |                 |
          SIN_595 <--|P2.0         P2.5|<--LTCH5916
                     |                 |
         SCLK_595 <--|P2.1         P2.4|<--
                     |                 |
         LTCH_595 <--|P2.2         P2.3|<--
                      -----------------
  -------------------------------------------------*/

//PIN 5916 PORT1
#define SIN5916 	 BIT7
#define SCLK5916     BIT6
#define LTCH5916 	 BIT5
#define N_channel	 48
int i=0;
//technites array
unsigned long int disp_arr[N_channel]={
		0X000200,
		0X000200,
		0X003E00,
		0X000200,
		0X000200,
		0X000000,
		0X003E00,
		0X002A00,
		0X002A00,
		0X000000,
		0X000000,
		0X003E00,
		0X002200,
		0X002200,
		0X000000,
		0X000000,
		0X003E00,
		0X000800,
		0X000800,
		0X003E00,
		0X000000,
		0X000000,
		0X003E00,
		0X000600,
		0X001800,
		0X003000,
		0X003E00,
		0X000000,
		0X000000,
		0X003E00,
		0X000000,
		0X000200,
		0X000200,
		0X003E00,
		0X000200,
		0X000200,
		0X000000,
		0X003E00,
		0X002A00,
		0X002A00,
		0X000000,
		0X000000,
		0X002E00,
		0X002A00,
		0X003A00,
		0X000000,
		0X000000,
		0X000000
};
void InitializeClocks(void);
void SendData(void);

void main(void)
{
	//int i;
	//unsigned long int temp_disp;
    WDTCTL = WDTPW + WDTHOLD;
	//TLC initialization
	P1DIR = 0;
    P1DIR |= (SIN5916 + SCLK5916 );
    P2DIR|=LTCH5916;
    P1OUT=0;
    P2OUT=0;
	InitializeClocks();						  // Setup clock
    _bis_SR_register(GIE);

	while (1)

 {
		SendData();
		P2OUT|=LTCH5916;
        P2OUT&=~(LTCH5916);
        _delay_cycles(360);

    }

}


void SendData(void)
{
	unsigned long int temp,check=0x800000;
	int m;
    P1OUT &= ~(SIN5916 + SCLK5916);
   P2OUT &=~(LTCH5916);


		temp=disp_arr[i];

		for(m=0;m<=23;m++)
		{
		if(temp&check)
			P1OUT|=SIN5916;
		else
			P1OUT&=~SIN5916;
		P1OUT|=SCLK5916;
		P1OUT&=~SCLK5916;
		temp=temp<<1;
		}

     i++;
     if(i==48)
    	i=0;

}

void InitializeClocks(void)
{
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
}



