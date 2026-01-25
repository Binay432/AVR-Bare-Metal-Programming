//OUTPIT COMPARE CHANNEL IS USED TO GENERATE THE PWM 
// CIRCUIT DIAGRAM SAME AS ABOVE
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

}

void loop() {

  // min to maximum 
  for (i = 0; i<1024; i++)
  {
     // SET THE DUTY CYCLE
       // FOR THE NON INVERTING MODE, DUTY CYCLE IS VALUE GIVEN TO THE OUTPUT COMPARE OF THE TIMER REGISTER
       // VALUE RANGES FROM [0 -1023]
      OCR1A = i; 
      delay(2);
  }
  delay(2000);
  // max to min
    for (i = 1023; i>0; i--)
  {
      OCR1A = i; 
      delay(2);
  }
 delay(2000);

}
