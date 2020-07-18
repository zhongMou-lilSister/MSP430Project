#include <msp430.h>
#include <stdint.h>


/*
 * Key.h
 *
 *  Created on: Jul 18, 2020
 *      Author: Dell
 */

#ifndef KEY_H_
#define KEY_H_

//typedef struct{
//    const volatile uint8_t *PxIN;
//    volatile uint8_t *PxOUT;
//    volatile uint8_t *PxDIR;
//    volatile uint8_t *PxREN;
//    volatile uint8_t *PxSEL;
//} GPIO_TypeDef;
//const GPIO_TypeDef GPIO3 = {&P3IN, &P3OUT, &P3DIR, &P3REN, &P3SEL};
//const GPIO_TypeDef GPIO6 = {&P6IN, &P6OUT, &P6DIR, &P6REN, &P6SEL};
//const GPIO_TypeDef GPIO8 = {&P8IN, &P8OUT, &P8DIR, &P8REN, &P8SEL};
//
//const GPIO_TypeDef * LED_GPIO[4] = {&GPIO8, &GPIO3, &GPIO6, &GPIO3};
//const uint8_t LED_PORT[4] = {BIT1, BIT7, BIT4, BIT5};

void InitKey();
void UpdateKey();

#endif /* KEY_H_ */
