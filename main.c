#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint16_t adcDt1Data;
double adcDt1Distance;

GPIO_InitTypeDef Pot;
ADC_InitTypeDef ADCStructure;
ADC_CommonInitTypeDef ADCCommonStructure;

uint16_t Read_ADC(void)
{
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles); //A0
	 ADC_SoftwareStartConv(ADC1);

	 while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
		 ;

	 return ADC_GetConversionValue(ADC1);
}

void config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	//POT Configs
	Pot.GPIO_Mode = GPIO_Mode_AN;
	Pot.GPIO_OType = GPIO_OType_PP;
	Pot.GPIO_Pin = GPIO_Pin_0;
	Pot.GPIO_PuPd = GPIO_PuPd_NOPULL;
	Pot.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &Pot);

	ADCCommonStructure.ADC_Mode = ADC_Mode_Independent;
	ADCCommonStructure.ADC_Prescaler = ADC_Prescaler_Div4;
	//diger 2 structure default olarak býraktýk
	ADC_CommonInit(&ADCCommonStructure);

	ADCStructure.ADC_Resolution=ADC_Resolution_12b;  //0-4096
	//ADCStructure.ADC_ContinuousConvMode = ENABLE;
	//diger ayarlar default olarak kalýyor
	ADC_Init(ADC1, &ADCStructure);

	ADC_Cmd(ADC1,ENABLE);

}

int main(void)
{
  config();

  while (1)
  {
	  adcDt1Data = Read_ADC();
	  adcDt1Distance = (((double)adcDt1Data * 0.04638671) + 10.0); //0.04638671 = 190/4096
  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}


uint16_t EVAL_AUDIO_GetSampleCallBack(void){

  return -1;
}
