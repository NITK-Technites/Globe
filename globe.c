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
//24X48 globe array
unsigned long int disp_arr[N_channel]={
		0xFFFFFF,
		0xFFFFDF,
		0xFFFF8F,
		0xFFFF8F,
		0xFFFFCF,
		0xFFFF8F,
		0xFFF80F,
		0xFFF00F,
		0xFFE007,
		0xFFE807,
		0xFFD807,
		0xFE3867,
		0xFC1C31,
		0x803E05,
		0xE03F2D,
		0xF07FF9,
		0xF87FC1,
		0xFEFFE1,
		0xFFFFF0,
		0xFFFFF1,
		0xFFEFFD,
		0xFF87FF,
		0xFF803F,
		0xFF827F,
		0xFC020D,
		0xF0060D,
		0xF0000F,
		0xF8000F,
		0xFF000F,
		0xF9800F,
		0xFFE00F,
		0xFFF007,
		0xFFF007,
		0xFFC007,
		0xFFE003,
		0xFFF003,
		0xFFE007,
		0xFFC007,
		0xFF7007,
		0xF37007,
		0xF1FE07,
		0xF1FF47,
		0xE17FCF,
		0xF3FF8F,
		0xFFFFCF,
		0xFFFFEF,
		0xFFFFFF,
		0xFFFFFF
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
        _delay_cycles(390);

    }

}


void SendData(void)
{
	unsigned long int temp,check=0x800000;
	int m;
    P1OUT &= ~(SIN5916 + SCLK5916);
   P2OUT &=~(LTCH5916);


		temp=~disp_arr[i];

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




