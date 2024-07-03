#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "defines.h"


// Peripheral Method
// U_LCR defines
#define WORD_LEN_8 3 // Binart 11 for 8 bit length
#define DLAB_BIT 7

// U_LSR Defines
#define DR_BIT 0
#define THRE_BIT 5
#define TEMT_BIT 6

#define FOSC 12000000 // 12MHz in Hz
#define CCLK 5*FOSC
#define PCLK CCLK/4

#define TX 0
#define RX 1

u32 BAUD, DIV;
extern u8 mode, inp, flag;


void UART0_isr(void) __irq{
	u8 ch='\0';
	if(U0IIR & 0x04){
		ch=U0RBR;
		if(mode=='0'){
			if(ch=='!') mode='1';
		}
		else{
			inp=ch;
			flag=1;
		}
	}
	VICVectAddr = 0; // dummy write
}


void initUART(u32 rate){
	BAUD = rate;
	DIV = PCLK/(16*BAUD);

	CFGPIN(PINSEL0, TX, FUN2); // cfg tx pin as fun2
	CFGPIN(PINSEL0, RX, FUN2); // cfg rx pin as fun2
	
	U0LCR = (1<<DLAB_BIT)|WORD_LEN_8;
	U0DLL = DIV;
	U0DLM = DIV>>8;
	CLRBIT(U0LCR, DLAB_BIT);
	
	// Enable UART Interrupt
	VICIntSelect = 0; // IRQ // Selaecting another interrupt source
  VICVectAddr0 = (unsigned)UART0_isr;
  VICVectCntl0 = 0x20 | 6; // UART0 Interrupt
  VICIntEnable = 1 << 6;   // Enable UART0 Interrupt
 
  U0IER = 0x01;       // Enable UART0 RBR Interrupts   
}


u8 rxUART(void){
	while(READBIT(U0LSR, DR_BIT) == 0);
	return U0RBR;
}


void txUART(u8 data){
	// while(READBIT(U0LSR, THRE_BIT) == 0); // Wait for previous data sending
	U0THR = data;
	while(READBIT(U0LSR, TEMT_BIT) == 0);
}


void strUART(u8 *ptr){
	while(*ptr)
	txUART(*ptr++);
}

