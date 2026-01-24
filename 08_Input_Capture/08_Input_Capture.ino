//For circuit diagram and output : 08_Timer_Input.png and 08
unsigned int capture = 0;

void setup() {
  // ENABLE THE GLOBAL INTERRUPT ENABLE BIT 

  sei();

  // ENABLE THE REQUIRED TIMER INTERRUPT 
    // TIMSK 1 REGISTER HAS ICIE1 BIT AS INPUT CAPTURE ENABLE : 15.11.8 

    TIMSK1 |=(1<<ICIE1);
  
  // SET MODE OF THE TIMER 
    // NOORMAL MODE 0000 
     // SAME AS PREVIOUS 

     TCCR1A &= (~(1<<WGM10)) & (~(1<<WGM11));
     TCCR1A &= (~(1<<WGM12)) & (~(1<<WGM13));

  // SET THE PRESCALAR FOR THE TIMER 
        // CONFIGUIRING TO 1024 

      TCCR1B |= (1<<CS12) | (1<<CS10);
      TCCR1B &= (~(1<<CS11)); // PRE = 1024 FROM DATA SHEET, 15.6 

  // START THE TIMER WITH INITIAL VALUE 

    TCNT1 = 0; 

  // SELECT THE EDGE FOR CAPTURING
    // For ref: 15.11.2
    
    TCCR1B |= (1<<ICES1);

  // programming logic
     // collect the timer value when the input button is pressed
      Serial.begin(9600); 
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

 // IMPLEMENT THE ISR FUNCTION 
  ISR(TIMER1_CAPT_vect)
  {
    // capturing the value of capture register ie., ICR1
    capture = ICR1; 
    Serial.println(capture);
  }
