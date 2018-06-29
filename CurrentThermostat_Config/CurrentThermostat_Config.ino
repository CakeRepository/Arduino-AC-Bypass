// include LCD library Needed for display
#include <LiquidCrystal.h>
// select the pins used on the LCD panel needed for display
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons Probably not needed
int lcd_key     = 0;
int adc_key_in  = 0;
int loopTotal = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//setup serial communication
  pinMode(36, OUTPUT);// setup relay 2
  digitalWrite(36, HIGH);//set Relay 2 to Off
}
void loop() {
  int cool = 0;// sets cool needed to No

  for(int i = 0; i < 30; i++)//loops to test connection over 10 second period
  {
  int sensorValue = analogRead(A8);//gets data from pin 8 which is AC detection
  double voltage = map(sensorValue, 0, 1023,0,2500);//Converts to 24V from 5V 1000 vs 25000
  Serial.println(voltage); //write volatge to serial
  if(voltage > 2000.00)//checks if voltage is above 20V
  {
  cool++;//adds to Cool Detection needed
  }
  loopTotal++;//adds 1 to loopTotal
  delay(1000);
  }
  lcd.clear();
  if(cool >= 1){
    lcd.print("CS: Cooling");
    digitalWrite(36, LOW);//set Relay 2 to Off
  }
  else{
    lcd.print("CS: Not Cooling");
    digitalWrite(36, HIGH);//set Relay 2 to Off
  }
  if(loopTotal = 18){
    loopTotal = 0; //sets loop total back to 0
    for(int i = 600; i > 0; i--){
    lcd.print("CS: Defosting ");
    lcd.print(i);
    }
    lcd.print("CS: Defosting");
    delay(600000); //Delay for 10 minutes to cool off ac unit
  }
}
