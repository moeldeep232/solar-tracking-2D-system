/*
 * Author : MohamedEldeep
 */ 


#include "PORT_Core.h"
#include "LCD_Core.h"
#include "ADC_Core.h"
#include "MicroStep_Driver.h"


extern uint32 ADC_Vin_Value_mv;


int main(void)
{
	PORT_Init();
	LCD_Init();
	ADC_Init();
uint32 sensorValue0 = 0;
uint32 sensorValue7 = 0;
      while(1)
      {
	
		                    ADC_Read(7);                                     // Get the first sensor value from pin7
		                    sensorValue7 = ((ADC_Vin_Value_mv * 1000) / 1024);
		    	            LCD_GoTo(1, 7);
		                    LCD_WiteInteger(sensorValue7);       
		                    ADC_Read(6);                                      // Get the second sensor value from pin6 
		      		        sensorValue0 = ((ADC_Vin_Value_mv * 1000) / 1024);
						    LCD_GoTo(0, 7);
							LCD_WiteInteger(sensorValue0);
							_delay_ms(1000);
							 LCD_Clear();
		                     _delay_ms(100);
							 
		             Enable_TB6600();                             //Enable Motor Driver
					 
		        if(sensorValue0 >= sensorValue7 +50)
		        {
			        SetDirection_TB600(CLOCKWISE);
			        for (int i = 0; i < 10; i++)                  // Adjust the number of steps as needed
			        {
				        Pul_TB6600();                             //move the stepper motor
			        }
			       
		        }
		        else if(sensorValue7 >= sensorValue0 +50)
				{
                    SetDirection_TB600(CLOCKWISE);
		       for (int i = 0; i < 10; i++)                        // Adjust the number of steps as needed
                    {
				        Pul_TB6600();                              //move the stepper motor
			        }
			     
		        }
				else
				{
					    Disable_TB6600();                         //disable the stepper motor
				}
				
	        }
       }