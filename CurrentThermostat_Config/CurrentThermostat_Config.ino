//Sample using LiquidCrystal library
#include <LiquidCrystal.h>;

int loopTotal;

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

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;
 if (adc_key_in < 250)  return btnUP;
 if (adc_key_in < 450)  return btnDOWN;
 if (adc_key_in < 650)  return btnLEFT;
 if (adc_key_in < 850)  return btnSELECT;

 // For V1.0 comment the other threshold and use the one below:
/*
 if (adc_key_in < 50)   return btnRIGHT;
 if (adc_key_in < 195)  return btnUP;
 if (adc_key_in < 380)  return btnDOWN;
 if (adc_key_in < 555)  return btnLEFT;
 if (adc_key_in < 790)  return btnSELECT;
*/


 return btnNONE;  // when all others fail, return this...
}
void setup() {
  lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);

  loopTotal = 0;
  Serial.begin(9600);//setup serial communication
  pinMode(36, OUTPUT);// setup relay 2
  digitalWrite(36, LOW);//set Relay 2 to Off
  lcd.print("Detecting System");
}
void loop() {
  int cool = 0;// sets cool needed to No


  for(int i = 0; i < 30; i++)//loops to test connection over 30 second period
  {
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);

    int sensorValue = analogRead(A9);//gets data from pin 8 which is AC detection
    double voltage = map(sensorValue, 0, 1023,0,2500);//Converts to 24V from 5V 1000 vs 25000

    loopTotal++;//adds 1 to loopTotal

    lcd.print(sensorValue);//Debug info
    if(sensorValue > 1000)//checks if voltage is above 20V
    {
      cool++;//adds to Cool Detection needed
    }
    delay(1000);//Delay for one Second
  }
Serial.println("end check loop");
  if(cool >= 1){
     lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Cooling");
    digitalWrite(36, HIGH);//set Relay 2 to Off
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Not Cooling");
    digitalWrite(36, LOW);//set Relay 2 to Off
  }

  if(loopTotal > 2700)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Defrosting");
    digitalWrite(36, LOW);//set Relay 2 to Off
    loopTotal = 0;//sets default value of Loop again
    for(int i = 600; 600 >= 0; i--)
    {
        delay(1000);
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print(i);
        lcd.print(" Remaining");
    }

  }
}
