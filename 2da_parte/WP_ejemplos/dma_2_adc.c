/*
===============================================================================
 Name        : EjeDMA2_ADC.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "lpc17xx_gpdma.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"

#define MaxData 64

void confPin();
void confDMA();
void confADC();
uint32_t tabla1[MaxData];
uint32_t tabla2[MaxData];
uint32_t tabla3[MaxData];
uint32_t tabla4[MaxData];
uint32_t tabla5[MaxData];
GPDMA_Channel_CFG_Type DMACFG;

volatile uint32_t Channel0_TC;
volatile uint32_t Channel0_Err;
#include <cr_section_macros.h>

int main(void) {
	SystemInit();
	confPin();
	confADC();
	Channel0_TC = 0;
	Channel0_Err = 0;
    while(1) {
    	if (ADCR>VREF){
    		TIM_ResetCounte(LPC_TIM0);
    		TIM_Cmd(LPC_TIM0,Enable);
    		While(((ADDR>>4)&0xFFF)>VREF){

    		}
    		alcanzo = 0;
    	}else;
    NVIC_EnableIRQ(DMA_IRQn);
    // Disable GPDMA channel 0
    GPDMA_ChannelCmd(0, DISABLE);
   //monitor = 0xFFF&(adc_value>>4);
    // Wait for a while
    for(int tmp = 0; tmp < 1000000; tmp++);
    /* GPDMA Re-setup */
    GPDMA_Setup(&DMACFG);
    /* Reset terminal counter */
    Channel0_TC = 0;
    /* Reset Error counter */
    Channel0_Err = 0;

    ADC_DeInit(LPC_ADC);
    }
    return 0 ;
}

void confPin(){
	PINSEL_CFG_Type Pines;			//configuramos el p0.23 como ADC0
	Pines.Funcnum=1;
	Pines.OpenDrain=0;
	Pines.Pinmode=PINSEL_PINMODE_TRISTATE;
	Pines.Pinnum=23;
	Pines.Portnum=0;
	PINSEL_ConfigPin(&Pines);
	}

void confADC(){
	int rate = 200000;
	ADC_Init(LPC_ADC,rate);
	//ADC_BurstCmd (LPC_ADC, 0);
	ADC_ChannelCmd (LPC_ADC, 0, SET);
	//ADC_IntConfig(LPC_ADC, ADC_ADINTEN0,SET);
	//ADC_StartCmd (LPC_ADC, ADC_START_CONTINUOUS);
	//ADC_EdgeStartConfig (LPC_ADC, ADC_START_ON_RISING);
	//NVIC_EnableIRQ(ADC_IRQn);
}




void TIMER0_IRQHandler(void) {
	TIM_ClearIntPending();
}

void confDMA(){
	NVIC_DisableIRQ(DMA_IRQn);
	GPDMA_LLI_Type Lista1,Lista2,Lista3,Lista4,Lista5;
	Lista1.SrcAddr=LPC_ADC->ADDR0;
	Lista1.DstAddr=(uint32_t) &tabla1;
	Lista1.Control=MaxData |(1<<17)|(1<<19)|(1<<22)| (1<<27) ;
	Lista1.Control &= ~(1<<26);
	Lista1.NextLLI=(uint32_t) &Lista2;

	Lista2.SrcAddr=LPC_ADC->ADDR0;
	Lista2.DstAddr=(uint32_t) &tabla2;
	Lista2.Control=MaxData |(1<<17)|(1<<19)|(1<<22)| (1<<27) ;
	Lista2.Control &= ~(1<<26);
	Lista2.NextLLI=(uint32_t) &Lista3;

	Lista3.SrcAddr=LPC_ADC->ADDR0;
	Lista3.DstAddr=(uint32_t) &tabla3;
	Lista3.Control=MaxData |(1<<17)|(1<<19)|(1<<22)| (1<<27) ;
	Lista3.Control &= ~(1<<26);
	Lista3.NextLLI=(uint32_t) &Lista4;

	Lista4.SrcAddr=LPC_ADC->ADDR0;
	Lista4.DstAddr=(uint32_t) &tabla4;
	Lista4.Control=MaxData |(1<<17)|(1<<19)|(1<<22)| (1<<27);
	Lista4.Control &= ~(1<<26);
	Lista4.NextLLI=(uint32_t) &Lista5;

	Lista5.SrcAddr=LPC_ADC->ADDR0;
	Lista5.DstAddr=(uint32_t) &tabla5;
	Lista5.Control=MaxData |(1<<17)|(1<<19)|(1<<22)| (1<<27) ;
	Lista5.Control &= ~(1<<26);
	Lista5.NextLLI=0;


	DMACFG.ChannelNum=0;
	DMACFG.SrcMemAddr=0;
	DMACFG.DstMemAddr=(uint32_t) tabla1;
	DMACFG.TransferSize=MaxData;
	DMACFG.TransferType=GPDMA_TRANSFERTYPE_P2M;
	DMACFG.TransferWidth=0;
	DMACFG.SrcConn=GPDMA_CONN_ADC;
	DMACFG.DstConn=0;
	DMACFG.DMALLI=(uint32_t) &Lista1;
	GPDMA_Init();
	GPDMA_Setup(&DMACFG);
}

void DMA_IRQHandler (void)
{
	if (GPDMA_IntGetStatus(GPDMA_STAT_INT, 0)){
	// Check counter terminal status
	if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, 0)){
	// Clear terminate counter Interrupt pending
	GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, 0);
	Channel0_TC++;
	}
	// Check error terminal status
	if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, 0)){
	// Clear error counter Interrupt pending
	GPDMA_ClearIntPending (GPDMA_STATCLR_INTERR, 0);
	Channel0_Err++;
	}
	}
}
