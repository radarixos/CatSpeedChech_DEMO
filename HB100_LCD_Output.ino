// signal input pin#8 - on UNO
// 

#include <FreqMeasure.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(57600);
  lcd.begin();
  lcd.print("Cat");
  lcd.setCursor(4,0);
  lcd.print("Speed check:");
  FreqMeasure.begin();
}

double sum=0;
int count=0;

void loop() {
  if (FreqMeasure.available()) {
    // average 5 readings together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 5) {
      float frequency = FreqMeasure.countToFrequency(sum / count);
      float spd = frequency / 19.49; //conversion from frequency to kilometers per hour (sorry, imperial guys :)
      //to improve speed, we update only the bottom row of the LCD
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.setCursor(8,1);
      lcd.print(spd);
      lcd.print("km/h");
      sum = 0;
      count = 0;
    }
  }
}
