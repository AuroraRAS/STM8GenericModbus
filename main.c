#include "stm8s003.h"

#include <stdbool.h>
#include <string.h>
#include <modbus.h>

static const struct ENV
{
	uint8_t MODBUS_ADDR;
	uint8_t UART_BRR1;
	uint8_t UART_BRR2;
	uint8_t TIM_PSCR;
	uint8_t TIM_ARR;
} *env = (struct ENV*) (volatile uint8_t*) 0x4000;

static bool frame_timeout;

static uint8_t uart_rx_head;
static uint8_t uart_rx_size;
static uint8_t uart_rx_buffer[UINT8_MAX + 1];

void frame_timer(void) __interrupt 23
{
	frame_timeout = true;
	TIM4_SR &= 0b11111110;
}

//void uart_rx(void) __interrupt 21
void uart_rx(void) __interrupt 18
{
	// frame timeout set to false
	frame_timeout = false;

	uart_rx_buffer[uart_rx_size++] = UART1_DR;

	// frame timer set to 0
	TIM4_CNTR = 0;
	// enable frame timer
	TIM4_CR1 |= 0b00000001;
}

void uart_send(uint8_t *data, uint8_t size)
{
	for(uint8_t i=0; i<size; i++)
	{
		UART1_DR = data[i];
		// waiting here, if TXE not set
		while(!(UART1_SR&0b10000000));
	}
	// waiting here, if TC not set
	while(!(UART1_SR&0b01000000));
}

void main(void)
{
	frame_timeout = false;
	uart_rx_head = 0;
	uart_rx_size = 0;

	/*
	 The format for each byte ( 11 bits ) in RTU mode is :
	 Coding System: 8–bit binary
	 Bits per Byte: 1 start bit
	 8 data bits, least significant bit sent first
	 1 bit for parity completion
	 1 stop bit
	 */
	// UART init
	// Set even parity
	UART1_CR1 &= 0b11111101;
	// Parity control enabled, 1 Start bit, 8 Data bits + 1 parity bit, 1 Stop bit
	UART1_CR1 |= 0b00010100;
	// RI,TX,RX enable
	UART1_CR2 |= 0b00101100;
	// 1 Stop bit
//	UART1_CR3 &= 0b11001111;

	UART1_BRR1 = env->UART_BRR1;
	UART1_BRR2 = env->UART_BRR2;
	//*/

	// Timer init
	TIM4_PSCR = env->TIM_PSCR;
	TIM4_ARR = env->TIM_ARR;
	// enable TIM4 Update Interrupt
	TIM4_IER |= 0b00000001;
	// enable One-pulse mode
	TIM4_CR1 |= 0b00001000;
	// enable frame timer
	TIM4_CR1 |= 0b00000001;

        // global interrupt enable
	__asm__("rim");

//	uart_send("6", 2);
//	uart_send(test, sizeof(test));
//	uart_send((volatile uint8_t*) 0x48cd, 12);
//	uart_send((volatile uint8_t*) 0x4865, 12);
//	uart_send((uint8_t*)env, sizeof(struct ENV));

	uint8_t request_buffer[UINT8_MAX + 1];
	uint8_t response_buffer[UINT8_MAX + 1];

	while (true)
	{
		if (uart_rx_size == uart_rx_head)
			continue;
		if (frame_timeout == false)
			continue;

		uint8_t str_size;
		for (str_size = 0; uart_rx_size != uart_rx_head; str_size++)
		{
			request_buffer[str_size] = uart_rx_buffer[uart_rx_head++];
		}


		if (modbus((struct modbus_response*) response_buffer, (struct modbus_request*) request_buffer, env->MODBUS_ADDR))
		{
			if (((struct modbus_request*) request_buffer)->func == READ_HOLDING_REGISTERS)
				uart_send(response_buffer, ((struct modbus_response*) response_buffer)->data_len + 5);
			else if (((struct modbus_request*) request_buffer)->func == WRITE_SINGLE_REGISTER && ((struct modbus_request*) request_buffer)->dev_addr != 0)
				uart_send(request_buffer, sizeof(struct modbus_request));
		}
//		else
//			uart_send("error", 6);
	}
}
