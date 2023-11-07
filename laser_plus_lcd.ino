#include "rgb_lcd.h"

uint8_t laserPin = 3;
uint8_t buttonPin = 5;
uint8_t buttonState = LOW;
uint8_t oldButtonState = LOW;
double calibrationFactor = 0.01551;
bool unitState = true;
rgb_lcd lcd;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(buttonPin,INPUT);
}

double calibrate()
{
  double total = 0;
  for(i = 0; i < 100; i++)
  {
    total += 
      /* Looks like you are planning on taking an average here. So you want to make a new measurement for 
      each cycle of this loop (the "pulseIn"  needs to be in here) You'll then add each of those measurements to your total.
      This would be easier if you put the whole of the measurement process inside a separate function. */
  }
  uint64_t a = pulseIn(laserPin,HIGH);
}

void loop() {
  lcd.clear();
  // Put all this in a function, from HERE ...
  pinMode(laserPin,OUTPUT);
  digitalWrite(laserPin,HIGH);
  delayMicroseconds(2);
  digitalWrite(laserPin,LOW);
  pinMode(laserPin,INPUT);
  uint64_t time = pulseIn(laserPin,HIGH);
  // ... to here - you would then return the "time" variable
  // BTW - don't call it "time" - this name is used in some libraries
      Serial.println(time);
  double distance = time*calibrationFactor;
  buttonState = digitalRead(buttonPin);
  if(oldButtonState == LOW && buttonState == HIGH)
  {
    unitState = !unitState;
  }
  oldButtonState = buttonState;
  if(distance >= 2 && distance <=200)
  {
    if(unitState == true)
    {
      lcd.print(distance);
      lcd.print(" cm");
    }
    else
    {
      distance = distance/2.54;
      lcd.print(distance);
      lcd.print(" in");
    }
  }
  if(distance < 2)
  {
    lcd.print("GET OUT OF MY FACE");
  }
  if(distance > 200)
  {
    lcd.print("GET OVER HERE");
  }
  
  delay(250);
}
