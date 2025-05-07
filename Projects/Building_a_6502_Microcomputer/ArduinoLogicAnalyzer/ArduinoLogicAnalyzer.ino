const char ADDR[] = {52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22};  // Set digital pins to read address lines
const char DATA[] = {53, 51, 49, 47, 45, 43, 41, 39};                                  // Set digital pins to read data lines
#define CLOCK 2                                                                        // Set clock pin
#define READ_WRITE 3                                                                   // Set read/write pin

void setup() 
{
  // Set address pins to INPUT
  for (int n = 0; n < 16; n += 1)
  {
    pinMode(ADDR[n], INPUT);                                                            
  }
  // Set data pins to INPUT
  for (int n = 0; n < 8; n += 1)
  {
    pinMode(DATA[n], INPUT);
  }
  // Set clock and r/w pins to input
  pinMode(CLOCK, INPUT);
  pinMode(READ_WRITE, INPUT);

  //Attach interrupt to the clock pin
  attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);

  Serial.begin(57600);
}

void onClock()
{
  // Initialize output array, address and data variable
  char output[15];
  unsigned int address = 0;
  unsigned int data = 0;

  // Print bit values of each address line
  for (int n = 0; n < 16; n += 1)
  {
    int bit = digitalRead(ADDR[n]) ? 1 : 0;
    Serial.print(bit);
    address = (address << 1) + bit; 
  }
  Serial.print("  ");

  // Print bit values of each data line
  for (int n = 0; n < 8; n += 1)
  {
    int bit = digitalRead(DATA[n]) ? 1 : 0;
    Serial.print(bit);
    data = (data << 1) + bit;
  }

  // Format bit values to hex and show if CPU is reading or writing
  sprintf(output, "  %04x %c %02x", address, digitalRead(READ_WRITE) ? 'r' : 'W', data);

  Serial.println(output);
}

void loop() 
{
//  for (int n = 0; n < 16; n += 1)
//  {
//    int bit = digitalRead(ADDR[n]) ? 1 : 0;
//    Serial.print(bit);  
//  }
//  Serial.println();

}
