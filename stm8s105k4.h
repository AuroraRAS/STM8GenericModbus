#ifndef _STM8S105K4_H
#define _STM8S105K4_H

#include <stdint.h>
#include <asm/stm8/features.h>

#define PD_ODR      (*(volatile uint8_t *)0x500F)	//Port D data output latch register
#define PD_DDR      (*(volatile uint8_t *)0x5011)	//Port D data direction register
#define PD_CR1      (*(volatile uint8_t *)0x5012)	//Port D control register 1
#define PD_CR2      (*(volatile uint8_t *)0x5013)	//Port D control register 2

#define PE_ODR      (*(volatile uint8_t *)0x5014)	//Port E data output latch register
#define PE_DDR      (*(volatile uint8_t *)0x5016)	//Port E data direction register
#define PE_CR1      (*(volatile uint8_t *)0x5017)	//Port E control register 1
#define PE_CR2      (*(volatile uint8_t *)0x5018)	//Port E control register 2

#define UART2_SR    (*(volatile uint8_t *)0x5240) 	//UART2 status register 0xC0
#define UART2_DR    (*(volatile uint8_t *)0x5241) 	//UART2 data register 0xXX
#define UART2_BRR1  (*(volatile uint8_t *)0x5242) 	//UART2 baud rate register 1 0x00
#define UART2_BRR2  (*(volatile uint8_t *)0x5243) 	//UART2 baud rate register 2 0x00
#define UART2_CR1   (*(volatile uint8_t *)0x5244) 	//UART2 control register 1 0x00
#define UART2_CR2   (*(volatile uint8_t *)0x5245) 	//UART2 control register 2 0x00
#define UART2_CR3   (*(volatile uint8_t *)0x5246) 	//UART2 control register 3 0x00
#define UART2_CR4   (*(volatile uint8_t *)0x5247) 	//UART2 control register 4 0x00
#define UART2_CR5   (*(volatile uint8_t *)0x5248) 	//UART2 control register 5 0x00
#define UART2_CR6   (*(volatile uint8_t *)0x5249) 	//UART2 control register 6 0x00
#define UART2_GTR   (*(volatile uint8_t *)0x524A) 	//UART2 guard time register 0x00
#define UART2_PSCR  (*(volatile uint8_t *)0x524B) 	//UART2 prescaler register 0x00

#define TIM2_CR1    (*(volatile uint8_t *)0x5300)	//TIM2 control register 1
#define TIM2_IER    (*(volatile uint8_t *)0x5301)	//TIM2 Interrupt enable register 0x00
#define TIM2_SR1    (*(volatile uint8_t *)0x5302)	//TIM2 status register 1
#define TIM2_SR2    (*(volatile uint8_t *)0x5303)	//TIM2 status register 2
#define TIM2_EGR    (*(volatile uint8_t *)0x5304)	//TIM2 event generation register
#define TIM2_CCMR1  (*(volatile uint8_t *)0x5305)	//TIM2 capture/compare mode register 1
#define TIM2_CCMR2  (*(volatile uint8_t *)0x5306)	//TIM2 capture/compare mode register 2
#define TIM2_CCMR3  (*(volatile uint8_t *)0x5307)	//TIM2 capture/compare mode register 3
#define TIM2_CCER1  (*(volatile uint8_t *)0x5308)	//TIM2 capture/compare enable register 1
#define TIM2_CCER2  (*(volatile uint8_t *)0x5309)	//TIM2 capture/compare enable register 2
#define TIM2_CNTRH  (*(volatile uint8_t *)0x530A)	//TIM2 counter high
#define TIM2_CNTRL  (*(volatile uint8_t *)0x530B)	//TIM2 counter low
#define TIM2_PSCR   (*(volatile uint8_t *)0x530C)	//TIM2 prescaler register
#define TIM2_ARRH   (*(volatile uint8_t *)0x530D)	//TIM2 auto-reload register high 0xFF
#define TIM2_ARRL   (*(volatile uint8_t *)0x530E)	//TIM2 auto-reload register low
#define TIM2_CCR1H  (*(volatile uint8_t *)0x530F)	//TIM2 capture/compare register 1 high
#define TIM2_CCR1L  (*(volatile uint8_t *)0x5310)	//TIM2 capture/compare register 1 low
#define TIM2_CCR2H  (*(volatile uint8_t *)0x5311)	//TIM2 capture/compare register 2 high
#define TIM2_CCR2L  (*(volatile uint8_t *)0x5312)	//TIM2 capture/compare register 2 low
#define TIM2_CCR3H  (*(volatile uint8_t *)0x5313)	//TIM2 capture/compare register 3 high
#define TIM2_CCR3L  (*(volatile uint8_t *)0x5314)	//TIM2 capture/compare register 3 low

#define TIM4_CR1    (*(volatile uint8_t *)0x5340)	// control register 1 0x00
#define TIM4_IER    (*(volatile uint8_t *)0x5341)	// interrupt enable register 0x00
#define TIM4_SR     (*(volatile uint8_t *)0x5342)	// status register 0x00
#define TIM4_EGR    (*(volatile uint8_t *)0x5343)	// event generation register 0x00
#define TIM4_CNTR   (*(volatile uint8_t *)0x5344)	// counter 0x00
#define TIM4_PSCR   (*(volatile uint8_t *)0x5345)	// prescaler register 0x00
#define TIM4_ARR    (*(volatile uint8_t *)0x5346)	// auto-reload register 0xFF

#define CLK_ICKR    (*(volatile uint8_t *)0x50C0)	//Internal clock control register
#define CLK_CKDIVR  (*(volatile uint8_t *)0x50C6)	//Clock divider register
#define CCR         (*(volatile uint8_t *)0x7F0A)	//Condition code register

#define FLASH_IAPSR (*(volatile uint8_t *)0x505F)	//Flash in-application programming status register
#define FLASH_DUKR  (*(volatile uint8_t *)0x5064)	//Data EEPROM unprotection register

#endif
