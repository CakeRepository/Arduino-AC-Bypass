// include LCD library
#include <LiquidCrystal.h>
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
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
  
  int cool = 0;
  for(int i = 0; i < 10; i++){
  int sensorValue = analogRead(A8);
  double voltage = map(sensorValue, 0, 1023,0,2500);
  Serial.println(voltage);
  if(voltage > 2000.00){
  cool++;
  }
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
}
