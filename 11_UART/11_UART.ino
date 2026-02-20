//Circuit diagram is in the ss 
void GPIO_setup(){
  DDRC |= (1<<DDC1); //pc1 as output
  DDRB |= (1<<DDB1);
}

void blinkSignal(){
  PORTB |= (1<<PB1); 
  delay(100); 
  PORTB &= (~(1<<PB1));
  delay(100);
}

// Function responsible for a character transfer
// UDRE0 register of UCSR0A is responsible to indicate if the data register is empty or full 
void UART_TxChar(char ch){
  while(!(UCSR0A & (1<<UDRE0))); // Wait for empty transmit buffer
  UDR0 = ch;        // load the new character to the data register of UART communication 
}


// Function responsible for a character receive
unsigned char USART_Receive(){
    blinkSignal();
    while(!(UCSR0A & (1<<RXC0))); // RXC0 is to indicate if the recieved buffer 
    return UDR0;
}

void UART_setup() {
    // Enable the transmission and reception in USART b
    UCSR0B |= (1<<RXEN0) | (1<<TXEN0);

   // Set data size for communication in  c 
      // Set the mode of asynchrounus communication (USCRnC) 
          UCSR0C &= (~(1<<UMSEL00)) & (~(1<<UMSEL01));
        
      // Setting the parity mode (0 0 --> No parity))
          UCSR0C &= (~(1<<UPM00)) & (~(1<<UPM01));
    
        // Set the stop bit ( 0 for 1 stop bit , 1 for 2 stop bit)
          UCSR0C &=(~(1<<USBS0)); 
    
  // set the data length to be 8 bits (UCSZn)(011 for 8 bits)
      UCSR0B &= (~(1<<UCSZ02)); 
      UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01); 
      
  // set the speed of the transmission (U2Xn in USART A) 
      UCSR0A |= (1<<U2X0); // HIGH SPEED MODE
      
  // set the baud rate (FROM TABLE 19.9 BEYOND FOR MORE BAUD RATE SAMPLING) 
    // FORM THE BAUD RATE REGISTER (19.10.5)

     UBRR0 = 207; // FROM TABLE FOR 16MHz, FOR 9600 BAUD RATE FOR U2X0 = 1 i.e High speed mod
}

void setup() {
  UART_setup(); 
  GPIO_setup();
//  pinMode(9, OUTPUT);
}

unsigned char data = 'n';

void loop() {
  // put your main code here, to run repeatedly:
    data = USART_Receive(); 
    UART_TxChar(data);
    if (data == 'a'){
      PORTC |= (1<<PC1);
    }
    if (data == 'b'){
      PORTC &= (~(1<<PC1));
    }

}
