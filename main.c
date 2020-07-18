#include <msp430.h>
#include "Key.h"
#include <stdint.h>
#include "Paper_Display.h"
#include <stdio.h>
#include <string.h>

#define TimesNewRoman 0
#define Arial 1
#define ArialBlack 2
#define size8 0
#define size16 1
volatile unsigned char DisBuffer[250*16];

extern volatile unsigned char updateFlag;
extern volatile unsigned char LiquidDrop_Quantity  ;
extern volatile unsigned char Start_Stop   ;
extern volatile unsigned char Reg_Hour ;
extern volatile unsigned char Reg_Minute ;
extern volatile unsigned char Setting_Flag;

void initClock()
{
     UCSCTL6 &= ~XT1OFF; //启动XT1
     P5SEL |= BIT2 + BIT3; //XT2引脚功能选择
     UCSCTL6 &= ~XT2OFF;          //打开XT2
     __bis_SR_register(SCG0);
     UCSCTL0 = DCO0+DCO1+DCO2+DCO3+DCO4;
     UCSCTL1 = DCORSEL_4;       //DCO频率范围在28.2MHZ以下
     UCSCTL2 = FLLD_5 + 1;       //D=16，N=1
     UCSCTL3 = SELREF_5 + FLLREFDIV_3;    //n=8,FLLREFCLK时钟源为XT2CLK；DCOCLK=D*(N+1)*(FLLREFCLK/n);DCOCLKDIV=(N+1)*(FLLREFCLK/n);
     UCSCTL4 = SELA_4 + SELS_3 +SELM_3;    //ACLK的时钟源为DCOCLKDIV,MCLK\SMCLK的时钟源为DCOCLK
     UCSCTL5 = DIVA_5 +DIVS_1;      //ACLK由DCOCLKDIV的32分频得到，SMCLK由DCOCLK的2分频得到
                 //最终MCLK:16MHZ,SMCLK:8MHZ,ACLK:32KHZ

//   __bic_SR_register(SCG0);                   //Enable the FLL control loop

}


void main(void){
    char option[40];
    char status[40];
    char rate[40];
    WDTCTL = WDTPW+WDTHOLD;
    P8DIR |= BIT1;
    P8OUT &=~ BIT1;
    initClock();
    PaperIO_Int();
    INIT_SSD1673();
    Init_buff();
    InitKey();
    DIS_IMG(1);
    while(1){
        if (updateFlag){
            sprintf(option,"option: %d", Setting_Flag);
            display((unsigned char *)option,0,18,0,0,0,0);
            if (Start_Stop == 1) strcpy(status, "on ");
            else strcpy(status, "off");
            display((unsigned char *)status,0,0,0,0,0,0);
            sprintf(rate,"rate: %d", LiquidDrop_Quantity);
            display((unsigned char *)rate,0,36,0,0,0,0);
            DIS_IMG(1);
        }
        UpdateKey();

    }
}
