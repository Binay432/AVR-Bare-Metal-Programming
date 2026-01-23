void lcd_data(unsigned char data){
  PORTD = data; 
  PORTB |= (1<<PB0); // RS = 1 for Data register 
  PORTB &= (~(1<<PB1)); // RW = 0 for Write Data 
  PORTB |= (1<<PB2); // EN = 1 // Trigger the transfer of data
  delay(10);
  PORTB &= (~(1<<PB2)); // EN = 1 // Resetting the data transfer mode 
}

void lcd_cmd(unsigned char command){
  PORTD = command; 
  PORTB &= (~(1<<PB0)); // RS = 0 for Instructor register 
  PORTB &= (~(1<<PB1)); // RW = 0 for Write Data 
  PORTB |= (1<<PB2); // EN = 1 // Trigger the transfer of data
  delay(10);
  PORTB &= (~(1<<PB2)); // EN = 1 // Resetting the data transfer mode 
}

void lcd_string(const unsigned char *str, unsigned char length){
  int i = 0; 
  for (i=0; i<length; i++){
    lcd_data(str[i]);
  }
}

void lcd_initialize(){
  lcd_cmd(0x38); // set the dimension of the lcd
  lcd_cmd(0x06); // increment of the cursor after printing 
  lcd_cmd(0x0c); // Display on, cursor off 
  lcd_cmd(0x01); // Clear the display 
}

void setup() {
  // 16*2 LCD is use 
  // For Circuit Diagram : See the 03_LCD_Config.png

  DDRD = 0xFF; // All the pis of pord D to o/p
  DDRB |= (1<<PB0) | (1<<PB1) | (1<<PB2); // Pin 0 to 2 of port B as o/p , RS = 0, RW = 1 , E = 2
  lcd_initialize();
}

void loop() {
  lcd_cmd(0x80); //Command code to set the cursor at first row
  lcd_string("Embedded",8); 
  lcd_cmd(0xC0); //Set the cursor to second line
  lcd_string("Systems",7);
}
