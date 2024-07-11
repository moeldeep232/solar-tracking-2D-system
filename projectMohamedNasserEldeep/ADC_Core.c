/*
 *  Author: MohamedEldeep
 */ 
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ADC_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
float64  ADC_Vin_Value_mv ;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void ADC_Init(void)
{

  #if (ADC_VOLTAGE_REFRENCE == ADC_VREF_VCC)
  SET_BIT(ADMUX,6);
  CLR_BIT(ADMUX,7);  
  #elif (ADC_VOLTAGE_REFRENCE == ADC_VREF_AREF)
  CLR_BIT(ADMUX,6);
  CLR_BIT(ADMUX,7);
  #elif (ADC_VOLTAGE_REFRENCE == ADC_VREF_INTERNAL)
  SET_BIT(ADMUX,6);
  SET_BIT(ADMUX,7);
  #endif /*if (ADC_VOLTAGE_REFRENCE == ADC_VREF_VCC)*/
  #if (ADC_CONVERSION_TRIGGER  == ADC_CONVERSION_SINGLE_CONVERSION)
  CLR_BIT(ADCSRA , 5);
  #elif (ADC_CONVERSION_TRIGGER  == ADC_CONVERSION_FREE_RUNNING)
  SET_BIT(ADCSRA , 5);
  SFIOR  |= (0X00 << 5);
  #elif (ADC_CONVERSION_TRIGGER  == ADC_CONVERSION_Analog_Comparator)
  SET_BIT(ADCSRA , 5);
  SFIOR  |= (0X01 << 5); 
  #elif (ADC_CONVERSION_TRIGGER  == ADC_CONVERSION_External_Interrupt_Request_0)
  SET_BIT(ADCSRA , 5);
  SFIOR  |= (0X02 << 5);  
  #elif (ADC_CONVERSION_TRIGGER  == ADC_CONVERSION_Timer_Counter0_Compare_Match)
  SET_BIT(ADCSRA , 5);
  SFIOR  |= (0X03 << 5);  
  #elif (ADC_CONVERSION_TRIGGER  == ADC_CONVERSION_Timer_Counter0_Overflow)
  SET_BIT(ADCSRA , 5);
  SFIOR  |= (0X04 << 5);  
  #elif (ADC_CONVERSION_TRIGGER  == ADC_CONVERSION_Timer_Counter_Compare_Match_B)
  SET_BIT(ADCSRA , 5);
  SFIOR  |= (0X05 << 5);  
  #elif (ADC_CONVERSION_TRIGGER  == ADC_CONVERSION_Timer_Counter1_Overflow)
  SET_BIT(ADCSRA , 5);
  SFIOR  |= (0X06 << 5);  
  #elif (ADC_CONVERSION_TRIGGER  == ADC_CONVERSION_Timer_Counter1_Capture_Event)
  SET_BIT(ADCSRA , 5);
  SFIOR  |= (0X07 << 5);  
  #endif /*if (ADC_CONVERSION_TRIGGER  == ADC_CONVERSION_FREE_RUNNING)*/

  #if (ADC_PRESCALE == ADC_PRESCALER_2)
  ADCSRA |= 0X01;
  #elif (ADC_PRESCALE == ADC_PRESCALER_4)
  ADCSRA |= 0X02;
  #elif (ADC_PRESCALE == ADC_PRESCALER_8)
  ADCSRA |= 0X03;
  #elif (ADC_PRESCALE == ADC_PRESCALER_16)
  ADCSRA |= 0X04; 
  #elif (ADC_PRESCALE == ADC_PRESCALER_32)
  ADCSRA |= 0X05;
  #elif (ADC_PRESCALE == ADC_PRESCALER_64)
  ADCSRA |= 0X06; 
  #elif (ADC_PRESCALE == ADC_PRESCALER_128)
  ADCSRA |= 0X07;	
  #endif /*if (ADC_PRESCALE == ADC_PRESCALER_128)*/
	

  #if (ADC_INTERRUPT_STATUS == ADC_INTERRUPT_ENABLED)
  SET_BIT(ADCSRA , 3);
  #elif (ADC_INTERRUPT_STATUS == ADC_INTERRUPT_DISABLED)
  CLR_BIT(ADCSRA , 3);
  #endif /*if (ADC_INTERRUPT_STATUS == ADC_INTERRUPT_ENABLED)*/

  #if (ADC_REG_ADJUST == ADC_RIGHT_ADJUCT)
  CLR_BIT(ADMUX , 5);
  #elif (ADC_REG_ADJUST == ADC_LEFT_ADJUCT)
  SET_BIT(ADMUX , 5);
  #endif /*if (ADC_REG_ADJUST == ADC_RIGHT_ADJUCT)*/
  
  /*Enable ADC*/
  SET_BIT(ADCSRA , 7);
}


void ADC_Read(uint8 PIN_NUMBER)
{
	uint32 ADC_Digital_Value = 0;
	// Select ADC channel
	ADMUX = (ADMUX & 0xF8) | (PIN_NUMBER & 0x07);
	/* Start ADC Conversion */
	SET_BIT (ADCSRA , 6);
	
	#if (ADC_INTERRUPT_STATUS == ADC_INTERRUPT_DISABLED)
	while (GET_BIT(ADCSRA , 4) == 0);
	
	#if (ADC_REG_ADJUST    ==   ADC_RIGHT_ADJUCT)
	ADC_Digital_Value = ADC_INPUT_16BIT_ACCESS;
	#elif (ADC_REG_ADJUST    ==   ADC_LEFT_ADJUCT)
	ADC_Digital_Value = (ADCH << 2) | (ADCL >> 6);
	#endif //#if (ADC_REG_ADJUST    ==   ADC_RIGHT_ADJUCT)
	
	ADC_Vin_Value_mv = ADC_Digital_Value ;
	#endif //#if (ADC_INTERRUPT_STATUS == ADC_INTERRUPT_DISABLED)
}


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void ADC_CLEAR(void)
{
	ADMUX=0x00;
	
	  CLR_BIT(ADCSRA , 7);


ADC_INPUT_16BIT_ACCESS=0;


	
	 #if (ADC_VOLTAGE_REFRENCE == ADC_VREF_VCC)
	 SET_BIT(ADMUX,6);
	 CLR_BIT(ADMUX,7);
	 #elif (ADC_VOLTAGE_REFRENCE == ADC_VREF_AREF)
	 CLR_BIT(ADMUX,6);
	 CLR_BIT(ADMUX,7);
	 #elif (ADC_VOLTAGE_REFRENCE == ADC_VREF_INTERNAL)
	 SET_BIT(ADMUX,6);
	 SET_BIT(ADMUX,7);
	 #endif /*if (ADC_VOLTAGE_REFRENCE == ADC_VREF_VCC)*/
	 
	 #if (ADC_REG_ADJUST == ADC_RIGHT_ADJUCT)
	 CLR_BIT(ADMUX , 5);
	 #elif (ADC_REG_ADJUST == ADC_LEFT_ADJUCT)
	 SET_BIT(ADMUX , 5);
	 #endif /*if (ADC_REG_ADJUST == ADC_RIGHT_ADJUCT)*/
	 
	   SET_BIT(ADCSRA , 7);

}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
