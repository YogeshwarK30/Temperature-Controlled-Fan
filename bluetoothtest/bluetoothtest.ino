#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
#include <SoftwareSerial.h>
SoftwareSerial Blue(0, 1);
int tempPin = A0; // the output pin of LM35
int fan = 9 ; // the pin where fan is connected
int temp;
int analogvalue;
int tempMin = 35; // the temperature to start the fan 0%
int tempMax = 60; // the temperature when fan is at 100%
int fanSpeed;
int fanLCD;
long int value;
long int value1;

void setup() {
pinMode(tempPin, INPUT);
pinMode(fan, OUTPUT);
lcd.begin(16,2);
Serial.begin(9600);
Blue.begin(9600);
}

void loop()
{

while(Blue.available()==0) ;
if(Blue.available()>0)
{
  value=Blue.parseInt();
}
delay(200);
  Serial.println(value);
  
  if(value==1001)//manual control
  {
    while(1)
    {
    Serial.println(value);
    
    //digitalWrite(fan,HIGH);
    
  while(Blue.available()==0) ;
  if(Blue.available()>0)
  {
  value1=Blue.parseInt();
  
  } 
  delay(200); 
  Serial.println(value1);
 
  if(value1>=30 && value1<=130)
    {
      
     fanSpeed= map(value1, 30, 130, 40, 255); 
     Serial.print("fanSpeed");
     analogWrite(fan, fanSpeed); 
    }
  lcd.print("FAN IS UNDER ");
  lcd.setCursor(0,1);
  lcd.print("MANUAL CONTROL ");
  delay(500);
  lcd.clear();
  }
  }
  if(value==1000)
  {while(1)
   {
  analogvalue = analogRead(tempPin);
  temp= analogvalue * 0.48828125;
  Serial.println(temp);
 
  if(temp < tempMin)
  {
  fanSpeed = 0; // fan is not spinning
  analogWrite(fan, fanSpeed);
  fanLCD=0;
  digitalWrite(fan, LOW);
  }
 if(temp>tempMax)
 {
  fanSpeed=255; // fan is maximum speed
  analogWrite(fan, fanSpeed);
  fanLCD= 100;
 }

 if((temp >= tempMin) && (temp <= tempMax)) 
 {
 fanSpeed = temp;
 fanSpeed= map(temp, 35, 60, 40, 255); // the actual speed of fan
 fanLCD = map(temp, tempMin, tempMax, 0, 100);// speed of fan to display on LCD100
 analogWrite(fan, fanSpeed); 
 }

 lcd.print("TEMP: ");
 lcd.print(temp); // display the temperature
 lcd.print("C ");
 lcd.setCursor(0,1); // move cursor to next line
 lcd.print("FANSPEED: ");
 lcd.print(fanLCD); // display the fan speed
 lcd.print("%");
 delay(500);
 lcd.clear();
 
 }
}
}
