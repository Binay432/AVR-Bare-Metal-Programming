// For circuit diagram connect the interrupt led in previous circuit diagram to PB1/OC1A , remaining is same

void setup() {
  // ENABLE THE GLOBAL TIMERRUPT ENABLE BIT 

    sei();

  // ENABLE THE REQUIRED TIMER INTERRUPT 
      // For A type, enable OCIE1A OF TIMSK1 AND OCIE1B FOR B TYPE
      
    TIMSK1 |= (1<<OCIE1A); // FROM DATA SHEET 15.11.8,

  // SET MODE OF THE TIMER 
     //Normal Mode 0000
     // SAME AS PREVIOUS 

     TCCR1A &= (~(1<<WGM10)) & (~(1<<WGM11));
     TCCR1A &= (~(1<<WGM12)) & (~(1<<WGM13));
   
  // SET THE COMPARE OUTPUT MODE 
    // FOR CHANNEL A CONFIGURE COM1A1 AND COM1A0 OF TCCR1A 
    // REF : 15.11.1

    TCCR1A |= (1<<COM1A0);
    TCCR1A &= (~(1<<COM1A1)); // TOGGLE
    
  // SET THE PRESCALER FOR THE TIMER 
      // CONFIGUIRING TO 1024 

      TCCR1B |= (1<<CS12) | (1<<CS10);
      TCCR1B &= (~(1<<CS11)); // PRE = 1024 FROM DATA SHEET, 15.6 
      
  // START THE TIMER WITH INITIAL VALUE 
    
    TCNT1 = 0; // TIMER/COUNTER 1 FROM 15.11.4
    
  // LOAD THE PERIOD FOR THE TIMER 
     // Using timer calculation for 1 second for 16MHz = 15625 

     OCR1A = 15625; // Output compare register 1 A is OCR1A : 15.11.5
     
  // CONFIGURE THE OUTPUT COMPARE PIN AS O/P
      
      DDRC |= (1<<PC1); //PC0 AS INTERRUPT AND PC1 AS REGULAR
      
      DDRB |= (1<<PB1); // THIS IS THE OC1A, SETTING IT AS OUTPUT
}

void loop() {
  PORTC ^= (1<<PC1);
  delay(100);

}

// IMPLIMENT THE ISR FUCNTION
ISR(TIMER1_COMPA_vect)
{
  TCNT1 = 0;  // INITALIZING THE INITAL TIMER 
      // NO NEED TO ISR PROGRAM AS IT GENRATE A WAVE FORM, AND IS TOGGLE EVERY TIMER PERIOD FROM 0 TO 15625
  OCR1A = 15625; // RESETTIGN THE PERIOD 
}
