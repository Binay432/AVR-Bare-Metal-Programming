void setup() {
  // Seven Segment Display 
  // Using Common Cathode 7 Segment Display 
  // Hex Code for 1 to 9 = 0x3F, 0x06, 0x5B, 0x4F, Ox66, 0x6E, 0x7C, 0x07, 0x7F, Ox6F
  // Port used = Port D 
  // Tested on Proteus 
      // For Schematics : See 02_Seven_Segmeent_Schematics.jpg under Circuit Diagram Folder.

  DDRD = 0xFF; // Setting all pin of port D to output i.e, 0b1111 1111
}

unsigned char Seven_Segment[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
int i = 0;

void loop() {
  for (i = 0 ; i<=9; i++){
    PORTD = Seven_Segment[i];
    delay(1000);
  }

}
