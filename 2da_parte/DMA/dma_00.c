#include "lpc17xx_dac.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpdma.h"

#define DMA_SIZE 60
#define NUM_SINE_SAMPLE 60
#define SINE_FREQ_IN_HZ 50
#define PCLK_DAC_IN_MHZ 23 //cclk/4

void configPin();
void configDAC();
void configDMA();

GPDMA_Channel_CFG_Type GPDMACfg;

uint32_t dac_sine_lut[NUM_SINE_SAMPLE]; //lo que va a transferir el DMA al DAC

int main(){
    uint32_t i;
   	uint32_t sin_0_to_90_16_samples[16] = {0, 1045, 2079, 3090, 4067, 5000, 5877, 6691, 7431, 8090, 8660, 9135, 9510, 9781, 9945, 10000};

    configPin();
    configDAC();

    for (i = 0; i < NUM_SINE_SAMPLE; i++)
    {
  		if(i <= 15){
			dac_sine_lut[i] = 512 + 512*sin_0_to_90_16_samples[i]/10000;
			if(i == 15) dac_sine_lut[i] = 1023;
		}
		else if(i <= 30){
			dac_sine_lut[i] = 512 + 512*sin_0_to_90_16_samples[30-i]/10000;
		}
		else if(i<=45){
			dac_sine_lut[i] = 512 - 512*sin_0_to_90_16_samples[i-30]/10000;
		}
		else{
			dac_sine_lut[i] = 512 - 512*sin_0_to_90_16_samples[60-i]/10000;
		}
		dac_sine_lut[i] = (dac_sine_lut[i]<<6);
	}
    configDMA();
    while(1);
    return 0;
}

void confPin(){
	PINSEL_CFG_Type PinCfg;
	/*
	*	Init DAC pin connect
	*	AOUT on P0.26
	*/
	PinCfg.Funcnum = 2;
	PinCfg.Pinnum = 26;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.OpenDrain = 0;
	PINSEL_ConfigPin(&PinCfg);
}

void configDAC(){
    uint32 tmp;
    DAC_CONVERTER_CFG_Type cfg;
    cfg.CNT_ENA = SET; //Habilito el tiemr del dac
    cfg.DMA_ENA = SET; //Habilito el acceso por dma
    DAC_Init(LPC_DAC); //Por defecto
    tmp = (PCLK_DAC_IN_MHZ*1000000)/(SINE_FREQ_IN_HZ*NUM_SINE_SAMPLE);
    DAC_SetDmaTimerOut(LPC_DAC, tmp); //Set dma timer
    DAC_ConfigDAConverterControl(LPC_DAC, &cfg); //habilita la operacion del dma y el dma timer
}

void configDMA(){
    GPDMA_LLI_Type dma;
    dma.SrcAddr = (uint32_t) dac_sine_lut;
    dma.DstAddr = (uint32_t) & (LPC_DAC->DACR);
    dma.NextLLI = (uint32_t)&dma; //Se enlaza a si misma.
    dma.Control = DMA_SIZE | (2<<18) | (); //Ver
    GPDMA_Init();

    GPDMAcfg.ChannelNum = 0; //canal 0
    GPDMAcfg.SrcMemAddr = (uint32_t)dac_sine_lut; //source memory
    GPDMAcfg.DstMemAddr = 0; //indico que termino
    GPDMAcfg.TransferSize = DMA_SIZE;
    GPDMAcfg.TransferWidht = 0; //no se usa
    GPDMAcfg.TransferType = GPDMA_TRANSFERTYPE_M2P;
    GPDMAcfg.SrcConn = 0; //no se usa pq va a un periferico
    GPDMAcfg.DstConn = GPDMA_CONN_DAC;
    GPDMAcfg.DMALLI = (uint32_t) &dma;

    GPDMA_SetUp(&GPDMACfg);
    GPDMA_ChannerlCmd(0, ENABLE);
}