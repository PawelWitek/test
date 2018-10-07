/*
 * 18b20.c
 *
 *  Created on: 15-01-2014
 *      Author: Administrator
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "18b20.h"


//char buf[8];
//void select_pin (unsigned char p){
//	WE = p;
//}

//unsigned char read_pin(void){
//	return WE;
//}


unsigned char RESET_PULSE(void) {
	unsigned char PRESENCE;
	DDRC|=(1<<WE);//CLEAR_1Wire;
	_delay_us(500);
	DDRC&=~(1<<WE);//SET_1Wire;
	_delay_us(66);
	if (!(PORT_1Wire & (1<<WE))) {PRESENCE=1;} else {PRESENCE=0; return 0;}
	_delay_us(470);
	if ((PORT_1Wire & (1<<WE))) {PRESENCE=1;} else {PRESENCE=0; return 0;}
	return PRESENCE;
}

void send(char bit) {
	DDRC|=(1<<WE);//CLEAR_1Wire;
	_delay_us(10);
		if (bit==1) DDRC&=~(1<<WE);//SET_1Wire;
	_delay_us(100);
	DDRC&=~(1<<WE);//SET_1Wire;
}

unsigned char read(void) {
	unsigned char PRESENCE=0;

	DDRC|=(1<<WE);//CLEAR_1Wire;
	_delay_us(2);
	DDRC&=~(1<<WE);//SET_1Wire;
	_delay_us(15);
	if ((PORT_1Wire & (1<<WE))) PRESENCE=1;
		else PRESENCE=0;

	return(PRESENCE);
}

void send_byte(char wartosc) {
	unsigned char i;
	unsigned char pom;

	for (i=0; i<8; i++) {
		pom = wartosc >> i;
		pom &= 0x01;
		send(pom);
	}

	_delay_us(100);
}

unsigned char read_byte(void) {
	unsigned char i;
	unsigned char wartosc = 0;

	for (i=0;i<8;i++) {
		if(read()) wartosc |=0x01<<i;
		_delay_us(50);
	}

	return(wartosc);
}

////////////////////////////////////////////////////////////////////////////////////////

unsigned char RESET_PULSE1(void) {
	unsigned char PRESENCE;
	DDRC|=(1<<WE1);//CLEAR_1Wire;
	_delay_us(500);
	DDRC&=~(1<<WE1);//SET_1Wire;
	_delay_us(30);
	if (!(PORT_1Wire & (1<<WE1))) {PRESENCE=1;} else {PRESENCE=0;}
	_delay_us(470);
	if ((PORT_1Wire & (1<<WE1))) {PRESENCE=1;} else {PRESENCE=0;}
	return PRESENCE;
}

void send1(char bit) {
	DDRD|=(1<<WE1);//CLEAR_1Wire;
	_delay_us(10);
		if (bit==1) DDRD&=~(1<<WE1);//SET_1Wire;
	_delay_us(100);
	DDRD&=~(1<<WE1);//SET_1Wire;
}

unsigned char read1(void) {
	unsigned char PRESENCE=0;

	DDRD|=(1<<WE1);//CLEAR_1Wire;
	_delay_us(2);
	DDRD&=~(1<<WE1);//SET_1Wire;
	_delay_us(15);
	if ((PORT_1Wire & (1<<WE1))) PRESENCE=1;
		else PRESENCE=0;

	return(PRESENCE);
}

void send_byte1(char wartosc) {
	unsigned char i;
	unsigned char pom;

	for (i=0; i<8; i++) {
		pom = wartosc >> i;
		pom &= 0x01;
		send1(pom);
	}

	_delay_us(100);
}

unsigned char read_byte1(void) {
	unsigned char i;
	unsigned char wartosc = 0;

	for (i=0;i<8;i++) {
		if(read1()) wartosc |=0x01<<i;
		_delay_us(50);
	}

	return(wartosc);
}
