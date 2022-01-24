#ifndef _STM8S003_H
#define _STM8S003_H

#include <stdint.h>
#include <asm/stm8/features.h>

#define UART1_SR    (*(volatile uint8_t *)0x5230) 	//UART1 status register 0xC0
#define UART1_DR    (*(volatile uint8_t *)0x5231) 	//UART1 data register 0xXX
#define UART1_BRR1  (*(volatile uint8_t *)0x5232) 	//UART1 baud rate register 1 0x00
#define UART1_BRR2  (*(volatile uint8_t *)0x5233) 	//UART1 baud rate register 2 0x00
#define UART1_CR1   (*(volatile uint8_t *)0x5234) 	//UART1 control register 1 0x00
#define UART1_CR2   (*(volatile uint8_t *)0x5235) 	//UART1 control register 2 0x00
#define UART1_CR3   (*(volatile uint8_t *)0x5236) 	//UART1 control register 3 0x00
#define UART1_CR4   (*(volatile uint8_t *)0x5237) 	//UART1 control register 4 0x00
#define UART1_CR5   (*(volatile uint8_t *)0x5238) 	//UART1 control register 5 0x00
#define UART1_GTR   (*(volatile uint8_t *)0x5239) 	//UART1 guard time register 0x00
#define UART1_PSCR  (*(volatile uint8_t *)0x523A) 	//UART1 prescaler register 0x00

#define TIM4_CR1    (*(volatile uint8_t *)0x5340)	// control register 1 0x00
#define TIM4_IER    (*(volatile uint8_t *)0x5343)	// interrupt enable register 0x00
#define TIM4_SR     (*(volatile uint8_t *)0x5344)	// status register 0x00
#define TIM4_EGR    (*(volatile uint8_t *)0x5345)	// event generation register 0x00
#define TIM4_CNTR   (*(volatile uint8_t *)0x5346)	// counter 0x00
#define TIM4_PSCR   (*(volatile uint8_t *)0x5347)	// prescaler register 0x00
#define TIM4_ARR    (*(volatile uint8_t *)0x5348)	// auto-reload register 0xFF

/* ADC */
#define ADC_DBxR    (*(volatile uint8_t *)0x53E0)	// ADC data buffer registers 0x00
#define ADC_CSR     (*(volatile uint8_t *)0x5400)	// ADC control/status register 0x00
#define ADC_CR1     (*(volatile uint8_t *)0x5401)	// ADC configuration register 1 0x00
#define ADC_CR2     (*(volatile uint8_t *)0x5402)	// ADC configuration register 2 0x00
#define ADC_CR3     (*(volatile uint8_t *)0x5403)	// ADC configuration register 3 0x00
#define ADC_DRH     (*(volatile uint8_t *)0x5404)	// ADC data register high 0xXX
#define ADC_DRL     (*(volatile uint8_t *)0x5405)	// ADC data register low 0xXX
#define ADC_TDRH    (*(volatile uint8_t *)0x5406)	// ADC Schmitt trigger disable register high 0x00
#define ADC_TDRL    (*(volatile uint8_t *)0x5407)	// ADC Schmitt trigger disable register low 0x00
#define ADC_HTRH    (*(volatile uint8_t *)0x5408)	//
#define ADC_HTRL    (*(volatile uint8_t *)0x5409)	//
#define ADC_LTRH    (*(volatile uint8_t *)0x540A)	//
#define ADC_LTRL    (*(volatile uint8_t *)0x540B)	//
#define ADC_AWSRH   (*(volatile uint8_t *)0x540C)	//
#define ADC_AWSRL   (*(volatile uint8_t *)0x540D)	//
#define ADC_AWCRH   (*(volatile uint8_t *)0x540E)	//
#define ADC_AWCRL   (*(volatile uint8_t *)0x540F)	//

#endif /* STM8S003_H_ */
