void setup() {
  DDRB |= 1<<DDB5;
}

void loop() {
//  PORTB |= (1<<PB5) ; //PB5 = HIGH
//  delay(1000);
//  PORTB &= ~(1<<PB5) ; // PB5 = Low 
//  delay(1000);

toggle_led();
}

void toggle_led(){
  PORTB ^= (1<<PB5); // Toggle Logic: x ^= (1 << n)
  delay(1000);
} 
