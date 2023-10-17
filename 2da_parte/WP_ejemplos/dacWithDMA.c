#include "LPC17xx.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpdma.h"


#define DMA_SIZE 60
#define NUM_SINE_SAMPLE 60
#define SINE_FREQ_IN_HZ 100
#define PCLK_DAC_IN_MHZ 25

void configPin();
void configDAC();
void configDMA();



uint32_t sinSamples[NUM_SINE_SAMPLE] = {511, 564, 617, 669, 719, 767, 812, 853, 891, 925, 954, 978, 997, 1011, 1020, 1023,
							   1020, 1011, 997, 978, 954, 925, 891, 853, 812, 767, 719, 669, 617, 564, 511, 458,
							   405, 353, 303, 255, 210, 169, 131, 97, 68, 44, 25, 11, 2, 0, 2, 11, 25, 44, 68,
							   97, 131, 169, 210, 255, 303, 353, 405, 458};

int main()
{

	configPin();
	configDAC();
	for(uint8_t index = 0; index<NUM_SINE_SAMPLE; index++)
		sinSamples[index] = sinSamples[index]<<6;
	configDMA();

	GPDMA_ChannelCmd(0, ENABLE);

	while(1);
}

void configPin()
{
	PINSEL_CFG_Type pinCfg;
	pinCfg.Funcnum = 2;
	pinCfg.OpenDrain = 0;
	pinCfg.Pinmode = 0;
	pinCfg.Portnum = 0;
	pinCfg.Pinnum = 26;
	PINSEL_ConfigPin(&pinCfg);
}

void configDAC()
{
	DAC_CONVERTER_CFG_Type dacCfg;
	dacCfg.CNT_ENA = SET;
	dacCfg.DMA_ENA = SET;
	DAC_Init(LPC_DAC);
	/*Set timeout*/
	uint32_t tmp;
	tmp = (PCLK_DAC_IN_MHZ * 1000000)/(SINE_FREQ_IN_HZ * NUM_SINE_SAMPLE);
	DAC_SetDMATimeOut(LPC_DAC, tmp);
	DAC_ConfigDAConverterControl(LPC_DAC, &dacCfg);

}

void configDMA()
{
	GPDMA_LLI_Type LLI1;
	LLI1.SrcAddr = (uint32_t) sinSamples;
	LLI1.DstAddr = (uint32_t) &LPC_DAC->DACR;
	LLI1.NextLLI = (uint32_t) &LLI1;
	LLI1.Control = DMA_SIZE
				   | (2<<18) //source width 32 bits
				   | (2<<21) //dest width 32 bits
				   | (1<<26); //source increment

	GPDMA_Init();

	GPDMA_Channel_CFG_Type GPDMACfg;
	GPDMACfg.ChannelNum = 0;
	GPDMACfg.SrcMemAddr = (uint32_t)sinSamples;
	GPDMACfg.DstMemAddr = 0;
	GPDMACfg.TransferSize = DMA_SIZE;
	GPDMACfg.TransferWidth = 0;
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P;
	GPDMACfg.SrcConn = 0;
	GPDMACfg.DstConn = GPDMA_CONN_DAC;
	GPDMACfg.DMALLI = (uint32_t)&LLI1;
	GPDMA_Setup(&GPDMACfg);

}

