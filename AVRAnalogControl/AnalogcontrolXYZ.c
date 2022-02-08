/*code has been modified from http://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-adc?page=all*/
#include <avr/io.h> 
#include <avr/interrupt.h> 				      /*Header file for the interrupt mode*/ 
#include <util/delay.h>						/*Header file for the delay*/
#include <stdio.h>
void Setup();							// Setup function prototype

int main (void)
{


	Setup();

	for(;;)  // Loop Forever
	{
		ADCSRA |= _BV(ADSC);  // Start A2D Conversions

	}
}

ISR(ADC_vect)	/*ADC_vect is the ADC interrupt vector for when running in 
		interrupt mode*/
{


	switch ADMUX
	{
		case 0x60:			/*this switch value corresponds to MUX0 being zero i.e. Read from Analog pin 0*/

			{

		                DDRB |= 0b00000101;


				if (ADCH < 50)			/*Condition for the analog moved in the negative direction*/
				{

					PORTB |= _BV(PIN0);	/*Turning on PIN0*/
					_delay_ms(10);
					PORTB &= ~_BV(PIN2);	/*Turning off the other pins*/
					PORTB &= ~_BV(PIN1);
					PORTB &= ~_BV(PIN3);
					PORTB &= ~_BV(PIN4);
					PORTB &= ~_BV(PIN5);

					while ((ADMUX == 0x60) & (ADCH < 50))
					{
						_delay_ms(20);		/*Delay Loop to Pulse Pin0 for the driver input*/
						PORTB &= ~_BV(PIN0);
						_delay_ms(20);
						PORTB |= _BV(PIN0);
					}

				}

				else if (ADCH > 128)		/*Condition for the analog moved in the positive direction*/
				{

					PORTB |= _BV(PIN2);	/*Turning on two pins for the driver to operate the motor in reverse direction*/
					_delay_ms(10);
					PORTB |= _BV(PIN0);
					PORTB &= ~_BV(PIN1);
					PORTB &= ~_BV(PIN3);
					PORTB &= ~_BV(PIN4);
					PORTB &= ~_BV(PIN5);

					while ((ADMUX == 0x60) & (ADCH > 128))
					{
						_delay_ms(20);		/*Delay Loop for the Pin0. Only this pin needs to pulse for the reverse direction*/
						PORTB &= ~_BV(PIN0);
						_delay_ms(20);
						PORTB |= _BV(PIN0);
					}
				}

				else				/*This is to turn off all pins if the Analog stick isn't moved*/
				{

					PORTB &= ~_BV(PIN0);
					PORTB &= ~_BV(PIN1);
					PORTB &= ~_BV(PIN2);
					PORTB &= ~_BV(PIN3);
					PORTB &= ~_BV(PIN4);
					PORTB &= ~_BV(PIN5);


			                ADCSRA &= ~_BV(ADSC); // Stop A2D Conversions to use the  other pin


					ADMUX |= _BV(MUX0);	/*Changes ADMUX to on so that the program will read from Analog PIN1*/
								/*switch statement is used to isolate the pins from being read from almost simultaneously*/
				}				/*This prevents multiple unwanted pins from going high at the same time e.g PIN1 and PIN0*/
				break;
			}

		case 0x61:					/*Condition to read from Analog PIN1*/

			{

		                DDRB |= 0b00001010;
				ADCSRA |= _BV(ADSC);  // Start A2D Conversions


				if (ADCH < 50)			/*This case follows the same principle as the one that came before it*/
				{				/*In this case the PINs are different. PIN1 is used as pulse, PIN3 is used for negative direction*/

					PORTB |= _BV(PIN1);
					_delay_ms(10);
					PORTB &= ~_BV(PIN0);
					PORTB &= ~_BV(PIN2);
					PORTB &= ~_BV(PIN3);
					PORTB &= ~_BV(PIN4);
					PORTB &= ~_BV(PIN5);

					while ((ADMUX == 0x61) & (ADCH < 50))
					{
						_delay_ms(20);
						PORTB &= ~_BV(PIN1);
						_delay_ms(20);
						PORTB |= _BV(PIN1);
					}
				}

				else if (ADCH > 128)
				{

                        		PORTB |= _BV(PIN3);
					_delay_ms(10);
                        		PORTB |= _BV(PIN1);
                        		PORTB &= ~_BV(PIN0);
                        		PORTB &= ~_BV(PIN2);
					PORTB &= ~_BV(PIN4);
					PORTB &= ~_BV(PIN5);

                                        while ((ADMUX == 0x61) & (ADCH > 128))
					{
						_delay_ms(20);
						PORTB &= ~_BV(PIN1);
						_delay_ms(20);
						PORTB |= _BV(PIN1);
					}

				}

                        	else
                    		{

                        		PORTB &= ~_BV(PIN0);
                        		PORTB &= ~_BV(PIN1);
                        		PORTB &= ~_BV(PIN2);
                        		PORTB &= ~_BV(PIN3);
					PORTB &= ~_BV(PIN4);
					PORTB &= ~_BV(PIN5);

                                        ADCSRA &= ~_BV(ADSC); // Stop A2D Conversions to use the  other pin


					ADMUX &= ~_BV(MUX0);

					ADMUX |= _BV(MUX1);

                        	}
				break;

		case 0x62:					/*Condition to read from Analog PIN1*/

			{

		                DDRB |= 0b00110000;
				ADCSRA |= _BV(ADSC);  // Start A2D Conversions


				if (ADCH < 50)			/*This case follows the same principle as the one that came before it*/
				{				/*In this case the PINs are different. PIN1 is used as pulse, PIN3 is used for negative direction*/

					PORTB |= _BV(PIN4);
					_delay_ms(10);
					PORTB &= ~_BV(PIN0);
					PORTB &= ~_BV(PIN2);
					PORTB &= ~_BV(PIN3);
					PORTB &= ~_BV(PIN1);
					PORTB &= ~_BV(PIN5);

					while ((ADMUX == 0x62) & (ADCH < 50))
					{
						_delay_ms(20);
						PORTB &= ~_BV(PIN4);
						_delay_ms(20);
						PORTB |= _BV(PIN4);
					}
				}

				else if (ADCH > 128)
				{

                        		PORTB |= _BV(PIN5);
					_delay_ms(10);
                        		PORTB |= _BV(PIN4);
                        		PORTB &= ~_BV(PIN0);
                        		PORTB &= ~_BV(PIN2);
					PORTB &= ~_BV(PIN3);
					PORTB &= ~_BV(PIN1);

                                        while ((ADMUX == 0x62) & (ADCH > 128))
					{
						_delay_ms(20);
						PORTB &= ~_BV(PIN4);
						_delay_ms(20);
						PORTB |= _BV(PIN4);
					}

				}

                        	else
                    		{

                        		PORTB &= ~_BV(PIN0);
                        		PORTB &= ~_BV(PIN1);
                        		PORTB &= ~_BV(PIN2);
                        		PORTB &= ~_BV(PIN3);
					PORTB &= ~_BV(PIN4);
					PORTB &= ~_BV(PIN5);

                                        ADCSRA &= ~_BV(ADSC); // Stop A2D Conversions to use the  other pin


					ADMUX &= ~_BV(MUX1);

					ADMUX &= ~_BV(MUX0);

                        	}
				break;
			}

			}

		default :
			ADMUX &= ~_BV(MUX0);
			ADMUX &= ~_BV(MUX1);

                        PORTB &= ~_BV(PIN0);
                        PORTB &= ~_BV(PIN1);
                        PORTB &= ~_BV(PIN2);
                        PORTB &= ~_BV(PIN3);
                        PORTB &= ~_BV(PIN4);
                        PORTB &= ~_BV(PIN5);




	}

}

void Setup() //sets up the ADC
{

	 ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC 
                                                              //prescaler to 128 - 125KHz sample rate @ 16MHz

        ADMUX |= (1 << REFS0); // Set ADC reference to AVCC
        ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 
                                //bit reading

        // No MUX values needed to be changed to use ADC0

        ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
        ADCSRA |= (1 << ADEN);  // Enable ADC

        ADCSRA |= (1 << ADIE);  // Enable ADC Interrupt

	sei();			//Enable Global interrupts



}

