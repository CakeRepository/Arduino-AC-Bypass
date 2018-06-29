int loopTotal;

void setup() {
  loopTotal = 0;
  Serial.begin(9600);//setup serial communication
  pinMode(36, OUTPUT);// setup relay 2
  digitalWrite(36, HIGH);//set Relay 2 to Off
  Serial.print("Detecting System");
}
void loop() {
  int cool = 0;// sets cool needed to No


  for(int i = 0; i < 30; i++)//loops to test connection over 10 second period
  {
  int sensorValue = analogRead(A8);//gets data from pin 8 which is AC detection
  double voltage = map(sensorValue, 0, 1023,0,2500);//Converts to 24V from 5V 1000 vs 25000
   loopTotal++;//adds 1 to loopTotal
  Serial.println(loopTotal);
  if(voltage > 2000.00)//checks if voltage is above 20V
  {
  cool++;//adds to Cool Detection needed
  }

  delay(1000);//Delay for one Second
  }

  if(cool >= 1){
    digitalWrite(36, LOW);//set Relay 2 to Off
  }
  else
  {
    digitalWrite(36, HIGH);//set Relay 2 to Off
  }

  if(loopTotal > 60){
    loopTotal = 0;
  Serial.println("delay");
  delay(600000);
  Serial.println("Awake");
  }

}
