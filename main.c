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
     UCSCTL6 &= ~XT1OFF; //����XT1
     P5SEL |= BIT2 + BIT3; //XT2���Ź���ѡ��
     UCSCTL6 &= ~XT2OFF;          //��XT2
     __bis_SR_register(SCG0);
     UCSCTL0 = DCO0+DCO1+DCO2+DCO3+DCO4;
     UCSCTL1 = DCORSEL_4;       //DCOƵ�ʷ�Χ��28.2MHZ����
     UCSCTL2 = FLLD_5 + 1;       //D=16��N=1
     UCSCTL3 = SELREF_5 + FLLREFDIV_3;    //n=8,FLLREFCLKʱ��ԴΪXT2CLK��DCOCLK=D*(N+1)*(FLLREFCLK/n);DCOCLKDIV=(N+1)*(FLLREFCLK/n);
     UCSCTL4 = SELA_4 + SELS_3 +SELM_3;    //ACLK��ʱ��ԴΪDCOCLKDIV,MCLK\SMCLK��ʱ��ԴΪDCOCLK
     UCSCTL5 = DIVA_5 +DIVS_1;      //ACLK��DCOCLKDIV��32��Ƶ�õ���SMCLK��DCOCLK��2��Ƶ�õ�
                 //����MCLK:16MHZ,SMCLK:8MHZ,ACLK:32KHZ

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
