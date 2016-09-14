/*
 * Byggern.h
 *
 * Created: 31.08.2016 15:28:40
 *  Author: audunel
 */ 

#ifndef UART_H_
#define UART_H_

int UART_init(unsigned int ubrr);
int UART_transmit(char data, FILE* f);
unsigned char UART_receive(void);
#endif /* BYGGERN_H_ */
