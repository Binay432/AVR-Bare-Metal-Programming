// For circuit diagram . refer the previous tutorial circuit

void setup() {
  // ENABKE THE GLOBAL INTERRUPT ENABLE BIT 
  
    sei(); 
   
  // ENABLE THE REQUIRED TIMER INTERRUPT

    TIMSK1 |= (1<<TOIE1); 
    
  // SET MODE OF THE TIMER 
    // FOR NORMAL MODE = 0000
    // WGM 11 and WGM 10 Is in TCCR1A 
    // Rest WGM 12 AND WGM 13 IS IN TCCR1B

    TCCR1A &= (~(1<<WGM10)) & (~(1<<WGM11));
    TCCR1B &= (~(1<<WGM12)) & (~(1<<WGM13));
    
  // SET THE PRESCALER FOR THE TIMER 
      // PRESSCALAR IS TO REDUCE THE FREQUENCY OF THE TIMER , INCREASING OF TIME PERIOD 
      // CAN BE DONE BY CONFIGURING  TCCR1B REGISTER, FROM CS10 TO CS12
      // We are using 1024 , that is 101 

      TCCR1B |= (1<<CS12) | (1<<CS10);
      TCCR1B &= (~(1<<CS11));     // PRESCALAR = 1024
      
  // SET THE PERIOD FOR THE TIMER 
    // The system clk is 16 MHZ 
    // The clock frequency becomes 16000000 /1024 = 15625 Hz 
    // Time for each Tick is 1/15625 = 0.00064 sec = 64 usec
    // For 1000 msec(1s) to elaspse the count is 1000ms/64us = 15625 
    // Max time (Period Value) = 65535 - 15625 = 49910 

    //Register to load the timer period value is TCNT1

    TCNT1 = 49910; // startng


    // lED CONNECTION
    DDRC |= (1<<PC0) | (1<<PC1);  // PC1 LED A REGULAR FUNCTION, WHILE PC0 IS TIMER INTERRUPT FUNCTION
    
}

void loop() {
  PORTC ^= (1<<PC1); // A regular function
  delay(300);
}

// IMPLEMENT THE INTERRUPT HANDLER FUNCTION

ISR(TIMER1_OVF_vect) {
  //USSER CODE 
  PORTC ^= (1<<PC0); // TOGGLING THE STATE OF PIN i.e., LED FUNCTION TO INDICATE THE TIMER INTERRUPT 
  TCNT1 = 49910;  // After user code reset the timer period value 
  
}
