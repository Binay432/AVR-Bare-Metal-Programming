// Potentiometer is connected at pc0 
// led at pb1 

int i;
void setup() {
  
  // SET MODE OF THE TIMER 
    // FROM DATASHEET, SETTING FAST pwm , 10 BIT 
    
     TCCR1A |= (1<<WGM10) | (1<<WGM11);
     TCCR1B |= (1<<WGM12);
     TCCR1B &= (~(1<<WGM13));

    
  // SET PWM MODE 
    // TWO MODES OF PWM 
        // 1.  INVERTING MODE : COM1A1/COM1B1 = 1 AND COM1A0/COM1B0 = 1
        // 2. NON INVERTING MODE = 1, 0 

        TCCR1A |= (1<<COM1A1);
        TCCR1A &= ~(1<<COM1A0);
        

  // SET THE PRESCALER FOR THE TIMER FOR SETTING PWM FREQUENCY 
    // CLOCK is  16 MHz
    // FOR 250 KHz , PRE SCALAR IS SET T0 64 SO THAT 16 MHz /64 = 250KHz
    // FROM TABLE 48 , TO SET THE PRE SCALAR OF 64 

    TCCR1B |= (1<<CS10) | (1<<CS11);
    TCCR1B &= (~(1<<CS12));   // PRE SCALAR  = 64

  // CONFIGURE THE OUTPUT COMPARE PIN AS O/P 
    // SELECTING OC1A/PB1 as output 

    DDRB |= (1<<PB1);


  // Analog to Digital Converter

   // ENABLE THE GLOBAL INTERRUPT BIT 

      sei();

  // Set the reference to NO AVCC and input to ADC0

    ADMUX &= (~(1<<REFS0)) & (~(1<<REFS1)) ;  // From ADMUX register !, no internal reference voltage

  // Set data alignement in data register
      // Resolution is 10 bit but the microcontroller is 8 bit 
      // So two 8 bit register is used and we need to aligned the data for it

      // ADCH and ADCL - The ADC data register 
      // ADLAR = 0 : Right justification 

    ADMUX &= (~(1<<ADLAR));
      
  // Enable ADC, set prescalar
    //ADCSRA REGISTER IS USED

    ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADATE) | (1<<ADPS2); // Enable the ADC , Enable the ADC Interrupt, Enable the ADPS2 bit to set the prescalar at 16Mh, as 100, where 1 is ADPS2

    ADCSRA &= (~(1<<ADPS0)) & (~(1<<ADPS1)); // Clock of ADC = 16Mhz /16  = 1MHz 

  // start the conversion 

    ADCSRA |= (1<<ADSC);

  // Selecting the channel for the ADC , that is ADCO (PC0) to ADC7 (PC)

    ADMUX &= (~(1<< MUX0)) & (~(1<< MUX1)) & (~(1<< MUX2)) & (~(1<< MUX3)); // ADC0 = PC0 

}

void loop() {


}

// implement ISR Interrupt handler 
  ISR(ADC_vect)
  {
        OCR1A = ADC; // DUTYCYCLE = 0 TO 1023 , // ADC register value is giving here that is ADCL and ADCH 
  }


  // Program Flow:
    // Setup all register 
    // Whenever the change is happen in the ADC register 
    // It will give the change value to OCR1A that is PB1 register by halting the main loop and giving executing ISR function 
    
