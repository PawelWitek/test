/*
 * main.c
 *
 *  Created on: 15-01-2014
 *      Author: Administrator
 */
//zmiana main tylko main
//zmiana pliku main
// zmiana  2222222222222222222222222
// dodane jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
//#include <tAvrLib/hd44780.h>
//#include <avr/iom8.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "18b20.h"

#define RS485_SEND (PORTD |= (1<<2))
#define RS485_REC (PORTD &= ~(1<<2))

#define LED_OFF (PORTD |= (1<<3))
#define LED_ON (PORTD &= ~(1<<3))

static unsigned char sprawdz;
static signed int temp1=0, temp2=0, temp3 = 0, temp_pp = 0, sign = 0,  temp=0, cor;

unsigned char dig[18]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x58,0x5E,0x79,0x71,0x40,0x00};
volatile static uint8_t BUFOR[10], L_BUF, dip_switch, address, sign_cor, send_temp_flag;

void USART0_Init()
{
	#define BAUDRATE 9600
	#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)

	UBRRH = (BAUD_PRESCALE >> 8);
	UBRRL = BAUD_PRESCALE;

	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	UCSRB = (1<<TXEN)|(1<<RXEN)|(1<<RXCIE);
}

void send_usart(unsigned char buf)
/* send buffer <buf> to uart */
{

        UDR = buf;
while ( !( UCSRA & (1<<UDRE)) );
}



//$GPRMC,064951.000,A,2307.1256,N,12016.4438,E,0.03,165.48,260406, 3.05,W,A*55 

ISR(USART_RXC_vect){
	BUFOR[L_BUF]=UDR;
	L_BUF++;
	
if(BUFOR[0] != 'T') L_BUF = 0;
if(L_BUF >= 3){
	if(BUFOR[2] == '?'){
		//LED_OFF;
		if((BUFOR[1]-0x30) == address)
			send_temp_flag=1;
			
	}
	L_BUF = 0;
} 



}


int main()
{
	/* inicjacja wy wietlacza */
//	hd44780_init();
	/* powi zanie wy wietlacza ze standardowym wyj ciem */
//	HD44780_BIND_STREAM(stdout);


//printf("   1-wire");
_delay_ms(200);

int licznik = 0;


//FILE std = FDEV_SETUP_STREAM(rs_put0,rs_get0, _FDEV_SETUP_RW);


//unsigned char a = 0;
unsigned char display[2];
	USART0_Init(47);


//}

		//DDRC = 0x7f; // port wyswietlacza
		DDRD = 0x3e; // sterowanie anod , wyjscie transmisji , enable transcivera

DDRB = 0x00;
LED_ON;
RS485_REC;
sei();
for(;;){
	
		PORTB=0xff;
		PORTD|=0xc0;
		
		dip_switch=~(((PINB & 0x3f) << 2) | ((PIND & 0xC0)>>6));
		
		address = dip_switch & 0x07;
		if(dip_switch & 0x08)sign_cor = '-';
		else sign_cor = ' ';
		cor = ((dip_switch & 0xf0) >> 4 ) * 5;
	
	
	_delay_ms(2);
	licznik++;
	if(licznik == 100){
		licznik = 0;
		//for(numer = 5; numer < 8; numer++){
			//select_pin(numer);
			_delay_ms(500);
if(send_temp_flag){
	send_temp_flag = 0;			
		sprawdz=RESET_PULSE();

				if (sprawdz==1) {
					
					send_byte(0xCC);
					send_byte(0x44);
					_delay_ms(1000);

					sprawdz=RESET_PULSE();
					send_byte(0xCC);
					send_byte(0xBE);

					temp1=read_byte();
					temp2=read_byte();

					sprawdz=RESET_PULSE();

					if((temp2&0xf0)==0xf0)sign=1; else sign=0;
					temp3=(temp1&0x0f);
					temp1=(temp1&0xf0)>>4;
					temp2=(temp2&0x0f)<<4;

					temp=(temp1+temp2)*10;

					temp_pp=(temp3*62);
					if((temp_pp%100)>5) temp_pp=(temp_pp+5)/100;
					else temp_pp=temp_pp/100;
				   temp=temp+temp_pp;
				   if (sign==1){ temp=(2560-temp);}
					   
					   	if(sign_cor=='-')temp=temp-cor;
					   	else temp=temp+cor;

					_delay_ms(200);
					display[0] = ~dig[temp%100/10];
					display[1] = ~dig[temp%10];
RS485_SEND;
LED_OFF;
_delay_ms(2);
					send_usart('T');
					send_usart(address + 0x30);
					send_usart('=');
					if(sign)
						send_usart('-');
					else
						send_usart(' ');
					//if(temp>=1000)
					//	send_usart(((temp%10000)/1000) + 0x30);
					//else
					//	send_usart(' ');
					if(temp>=100)
					send_usart(((temp%1000)/100) + 0x30);
					else
						send_usart(' ');
						
					send_usart(((temp%100)/10) + 0x30);
					send_usart('.');
					send_usart((temp%10) + 0x30);
					
					send_usart(0x0d);



					//sprintf("temperatura: %d\n", temp);
				}
				else{
RS485_SEND;
LED_OFF;
_delay_ms(2);
					send_usart('T');
										send_usart(address + 0x30);
										send_usart('E');
										send_usart('R');
										send_usart('R');
										
										send_usart('_');
										send_usart('_');
										send_usart('_');
										send_usart(0x0a);
				}
				_delay_ms(5);
LED_ON;
RS485_REC;



					
						
						
			/*	send_usart('P');
				send_usart(':');
				send_usart(dip_switch/100+0X30);
				send_usart(dip_switch%100/10+0X30);
				send_usart(dip_switch%10+0X30);
				send_usart(0x0a);
				*/

	}
}
	//DDRC = 0x7f; // port wyswietlacza
	//DDRD = 0x36; // sterowanie anod , wyjscie transmisji , enable transcivera



}
	return 0;
}
