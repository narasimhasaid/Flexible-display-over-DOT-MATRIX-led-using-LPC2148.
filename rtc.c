#include <LPC21xx.h>
#include "types.h"

#define FOSC 12000000
#define CCLK 5*FOSC
#define PCLK CCLK/4
#define PREINT_VAL ((PCLK/32768)-1)
#define PREFRAC_VAL (PCLK - ((PREINT_VAL + 1) * 32768))


void initRTC(void){
	PREINT=PREINT_VAL;
  PREFRAC=PREFRAC_VAL;
	CCR=0x01; //timer started
}


void setTime(u32 sec, u32 min, u32 hr, u32 dom, u32 month, u32 year, u32 dow){
	CCR=0x02;
	
	SEC=sec;
	MIN=min;
	HOUR=hr;
	DOM=dom;
	DOW=dow;
	MONTH=month;
	YEAR=year;
	
	CCR=0x01;
}
