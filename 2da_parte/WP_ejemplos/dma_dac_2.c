/*
===============================================================================
 Name        : EjercicioDMA1_Segura_Atencio.c
 Author      :
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "lpc17xx_gpdma.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_dac.h"

#include <cr_section_macros.h>
void confPin();
void confDMA();
void confDAC();
uint32_t *variable0= 0x2007c000;
uint32_t *variable1= 0x2007D000;
uint32_t *variable2= 0x2007E000;

int main(void) {

	uint32_t *prt1=(uint32_t *) 0x2007C000;
		uint32_t *prt2=(uint32_t *) 0x2007D000;
		uint32_t *prt3=(uint32_t *) 0x2007E000;
		for (int i=0; i<767;i++){
			*(prt1+i)=(333<<6); //1.073V
			*(prt2+i)=(512<<6); //1.93V
			*(prt3+i)=(1023<<6) ;//3.3 V/
		}

	SystemInit();
	confPin();
	confDAC();
	confDMA();
	GPDMA_ChannelCmd(0, ENABLE);
	while(1){

	}
    return 0 ;
}

void confPin(){
	PINSEL_CFG_Type PinCFG;		//configuramos el p0.26 para que sea AOUT salida del DAC
	PinCFG.Funcnum=2;
	PinCFG.OpenDrain =0;
	PinCFG.Pinmode =PINSEL_PINMODE_PULLUP;
	PinCFG.Pinnum=26;
	PinCFG.Portnum=0;
	PINSEL_ConfigPin(&PinCFG);
}
void confDAC(){
	DAC_CONVERTER_CFG_Type DACCFG;
	DACCFG.CNT_ENA =SET;

	DACCFG.DMA_ENA=SET;

	DAC_Init(LPC_DAC);
	DAC_SetDMATimeOut(LPC_DAC,6250);
	DAC_ConfigDAConverterControl(LPC_DAC,&DACCFG);
}
void confDMA(){
	GPDMA_Channel_CFG_Type ChnCFG;
	GPDMA_LLI_Type LLI0;
	GPDMA_LLI_Type LLI1;
	GPDMA_LLI_Type LLI2;
	GPDMA_Init();
	LLI0.SrcAddr= (uint32_t) variable0;
	LLI0.DstAddr= (uint32_t)&(LPC_DAC->DACR);
	LLI0.NextLLI= (uint32_t) &LLI1;
	LLI0.Control=768| (2<<18) | (2<<21) | (1<<26) ;

	LLI1.SrcAddr= (uint32_t) variable1;
	LLI1.DstAddr= (uint32_t) &LPC_DAC->DACR;
	LLI1.NextLLI= (uint32_t) &LLI2;
	LLI1.Control=768
		| (2<<18) //source width 32 bit
		| (2<<21) //dest. width 32 bit
		| (1<<26) //source increment
		;
	LLI2.SrcAddr= (uint32_t) variable2;
	LLI2.DstAddr= (uint32_t) &LPC_DAC->DACR;
	LLI2.NextLLI= (uint32_t) &LLI0;
	LLI2.Control=768
		| (2<<18) //source width 32 bit
		| (2<<21) //dest. width 32 bit
		| (1<<26) //source increment
		;

	ChnCFG.ChannelNum=0;
	ChnCFG.SrcMemAddr= (uint32_t) variable0;
	ChnCFG.DstMemAddr=0;
	ChnCFG.TransferSize=767;
	ChnCFG.TransferType=GPDMA_TRANSFERTYPE_M2P;
	ChnCFG.TransferWidth=0;
	ChnCFG.DMALLI=(uint32_t) &LLI1;
	ChnCFG.SrcConn=0;
	ChnCFG.DstConn=GPDMA_CONN_DAC;

	GPDMA_Setup(&ChnCFG);

}
