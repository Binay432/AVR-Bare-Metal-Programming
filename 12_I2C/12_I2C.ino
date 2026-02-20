unsigned char data ;
void hex_to_ascii(unsigned char value)
{
    unsigned char bcd;
    bcd= value;              // E,g : 82
    bcd= bcd & 0xf0;        // All the lsb bits to 0 i.e., 1000 0010 & 1111 0000 = 1000 0000 = 80 
    bcd= bcd >> 4;          // 1000 000 >> 4 = 0000 1000 = 08
    bcd= bcd | 0x30;        //  OR_ing with 0x30 for hexadecimal i.e., 08 | 30 = 0x38 
    // lcd_data(bcd);          //  sending ascii code to lcd that is 8 
    Serial.print(bcd);
      
    bcd= value;              // for LSB 
    bcd= bcd & 0x0f;
    bcd= bcd | 0x30;
//    lcd_data(bcd);
    Serial.println(bcd);
}

char decimal_to_bcd(unsigned char value)
{
    unsigned char msb, lsb,hex; // value =  82 
    msb= value/10;          // msb = 8 
    lsb= value%10;          // lsb = 2 
    hex = ((msb << 4)+lsb);  // 80 + 2 = 82
    return hex;
}


/* 12C initialize function */
void I2C_Init(){
  TWSR = 0; 
  TWBR = ((F_CPU/100000)-16)/(2*pow(4,(TWSR&((1 << TWPS0)|(1 << TWPS1))))); /* Get bit rate register value by formula */
}

/* 12C start function */
/* Used to sed the address bit and data bit */

uint8_t I2C_Start(char write_address){

  TWCR =(1 << TWSTA)|(1 << TWEN)|(1 << TWINT);  /* Enable TWI, generate start condition and clear interrupt flag | TWCR = Two Wire Control Register */
  while (!(TWCR & (1 << TWINT)));               /* Wait until TWI finish its current job (start condition) -> INTERUPT FLAG*/ 
  
  TWDR = write_address;                         /* If yes then write SLA+W in TWI data register */
  TWCR=(1 << TWEN)|(1 << TWINT);                /* Enable TWI and clear interrupt flag */
  while (!(TWCR & (1 << TWINT)));               /* Wait until TWI finish its current job (Write operation) */
}


/* 12C repeated start function */

uint8_t I2C_Repeated_Start(char read_address){
  
  TWCR =(1 << TWSTA)|(1 << TWEN)|(1 << TWINT);   /* Enable TWI, generate start condition and clear interrupt flag */
  while (!(TWCR & (1 << TWINT)));                /* Wait until TWI finish its current job (start condition) */
  
  TWDR = read_address;                          /* If yes then write SLA+R in TWI data register */
  TWCR = (1 << TWEN)|(1 << TWINT);              /* Enable TWI and clear interrupt flag */
  while (!(TWCR & (1 << TWINT)));               /* Wait until TWI finish its current job (Write operation) */
}


/* 12C stop function */
void I2C_Stop(){
  
  TWCR =(1 << TWSTO)|(1 << TWINT)|(1 << TWEN);   /* Enable TWI, generate stop condition and clear interrupt flag */

  while(TWCR & (1 << TWSTO));                   /* Wait until stop condition execution */
}

/* I2C write (1 byte of data) function */
uint8_t I2C_Write(char data){
  
  TWDR = decimal_to_bcd(data);                   /* Copy data in TWI data register */
  TWCR= (1 << TWEN)|(1 << TWINT);               /* Enable TWI and clear interrupt flag */
  while (!(TWCR & (1 << TWINT)));               /* Wait until TWI finish its current job (Write operation) */
}


/* 12C read ack function */
char I2C_Read_Ack(){
  
   TWCR=(1 << TWEN)|(1 << TWINT)|(1 << TWEA);   /* Enable TWI, generation of ack and clear interrupt flag */

   while (!(TWCR & (1 << TWINT)));              /* Wait until TWI finish its current job (read operation) */
   return TWDR;                                 /* Return received data */

}

/* I2C read nack(not acknowledge) function */
char I2C_Read_Nack(){
  
  TWCR=(1 << TWEN)|(1 << TWINT);              /* Enable TWI and clear interrupt flag */
  while (!(TWCR & (1 << TWINT)));             /* Wait until TWI finish its current job (read operation) */
  return TWDR;                                /* Return received data */
}



// Communication WITH EEPROM 24C04A

void setup() {
  // enable the global interrupt 
    sei(); 

  // Serial begin 
    Serial.begin(9600); 

  // Initializing the I2C 
     I2C_Init();

  
  /* Start I2C communication with RTC : Write Sequence: See doc for more*/ 
  /*
     * Slave Address from doc : Considering A0 A1 A2 to be gnd and remaing as 1010
     * So address = 1010000
     * for read/write  =1/0 
     * for writting address = 10100000 = 0xA0 
     * for reading address = 10100001 = 0xA1 
     * 
     * 
     * Writing the address to eeprom at 0x22 to be as 0x99 
   */
      I2C_Start(0xA0);
      I2C_Write(22);
      I2C_Write(99);
      I2C_Stop ();        /* Stop I2C communication */
      
      delay(500);

      /* Start 12C communication with RTC */
      /* Read Sequence */
      
      I2C_Start(0xA0);
      I2C_Write(22);         /* Write on 0 location for second value */
      I2C_Repeated_Start(0xA1);  /* 0xA1 as read */
      data = I2C_Read_Nack();
      I2C_Stop ();            /* Stop I2C communication */
      
      delay(500);
      
      hex_to_ascii(data); // print the data to serial monitor
  
}


void loop() {
  // put your main code here, to run repeatedly:

}
