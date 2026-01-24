void togle_led()
{
  PORTC ^= (1<<PC1);
}
void setup() {
  // INTERRUPT STEPS:
    DDRC |= (1<<PC0) | (1<<PC1); // Build out put
    // Enable the GIE (GLOBAL INTERRUPT ENABLE BIT)
    
    SREG |= (1<<7); //SREG is  AVR status register 
    
    //ENABLE THE REQUIRED EXTERNAL INTERRUPTS FROM THE CORRESPONDING REGISTERS
     
     EIMSK |= (1<<INT0) | (1<<INT1);
    
    // SET THE EDGE SELECT FOR EXTERNAL ITERRUPTS 
      // We want to recognize the interrupt on risin edge
      // ISC10 = 1 AND ISC11 = 1 FOR INT1 
      // ISC00 = 1 AND ISC01 = 1 FOR INT0
      
     EICRA |= (1<<ISC10) | (1<<ISC11) | (1<<ISC00) | (1<<ISC01);
     
    
}

void loop() {
  // put your main code here, to run repeatedly:
  togle_led(); //uninterrupted task
  delay(500);
}

// IMPLEMENT THE INTERPT HANDLER
ISR(INT0_vect)
{
  PORTC |= (1<<PC0);  // WHEN BUTTON IS PRESSED AT INT0 , BULB GLOWS
}

ISR(INT1_vect)
{
  PORTC &= (~(1<<PC0));
}
