#include "Key.h"

volatile unsigned char LiquidDrop_Quantity = 0 ;
volatile unsigned char Start_Stop = 0 ;
volatile unsigned char Setting_Flag = 0;
volatile unsigned char Reg_Hour = 0;
volatile unsigned char Reg_Minute = 0;
volatile unsigned char updateFlag = 0;
uint8_t last1 = 0xFF, last2 = 0xFF;
uint8_t cur1, temp, cur2;

void InitKey(){
    P1REN |= 0xFF;
    P1OUT |= 0xFF;
    P2REN |= 0xFF;
    P2OUT |= 0xFF;

}
void UpdateKey(){
    static unsigned char Key_Counter;

    cur1 = P1IN & 0xFF;
    temp = (cur1 ^ last1) & last1;
    last1 = cur1;
    if (temp & (1 << 2)){   // S1
        Setting_Flag += 1;
        if(Setting_Flag == 4) Setting_Flag = 0;
        updateFlag = 1;
        return;
    }
    if (temp & (1 << 3)){   // S2
        Key_Counter += 1;
        if(Key_Counter == 1)
        {
            Start_Stop = 1;                         // Start
        }
        if(Key_Counter == 2)                        // Stop
        {
            Key_Counter = 0;
            Start_Stop = 0;
            Setting_Flag = 0;                       // Forbid Setting function
        }
        updateFlag = 1;
        return;
    }
    cur2 = P2IN & 0xFF;
    temp = (cur2 ^ last2) & last2;
    last2 = cur2;
    if (temp & (1 << 3)){   // S3
        if(Setting_Flag == 1)
        {
            if(Reg_Hour >= 24) Reg_Hour = 24;
            else Reg_Hour += 1;          // every time increase 1 hour
        }
        if(Setting_Flag == 2)
        {
            if(Reg_Minute >= 59) Reg_Minute = 59;
            else Reg_Minute += 1;          // every time increase 1 minute
        }
        if(Setting_Flag == 3)
        {
            if(LiquidDrop_Quantity >= 100) LiquidDrop_Quantity = 100;
            else LiquidDrop_Quantity += 5;          // every time increase 5 drops
        }
        updateFlag = 1;
        return;
    }
    if (temp & (1 << 6)){   // S4
        if(Setting_Flag == 1)
        {
            if(Reg_Hour <= 0) Reg_Hour = 0;
            else Reg_Hour -= 1;          // every time decrease 1 hour
        }
        if(Setting_Flag == 2)
        {
            if(Reg_Minute <= 0) Reg_Minute = 0;
            else Reg_Minute -= 1;          // every time decrease 1 minute
        }
        if(Setting_Flag == 3)
        {
            if(LiquidDrop_Quantity <= 0) LiquidDrop_Quantity = 0;
            else LiquidDrop_Quantity -= 5;          // every time Decrease 5 drops
        }
        updateFlag = 1;
        return;
    }
    updateFlag = 0;
}
