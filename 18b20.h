/*
 * 18b20.h
 *
 *  Created on: 15-01-2014
 *      Author: Administrator
 */
//#include <avr/io.h>
//#include <util/delay.h>
//#include <stdlib.h>

#ifndef _18B20_H_
#define _18B20_H_




#define WE 1
#define WE1 0
#define PORT_1Wire PINC
#define SET_1Wire DDRC&=~(1<<WE)
#define CLEAR_1Wire DDRC|=(1<<WE)




unsigned char RESET_PULSE(void);
void send(char bit);
unsigned char read(void) ;
void send_byte(char wartosc);
unsigned char read_byte(void);

//
unsigned char RESET_PULSE1(void);
void send1(char bit);
unsigned char read1(void) ;
void send_byte1(char wartosc);
unsigned char read_byte1(void);



#endif /* 18B20_H_ */
