#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64);

#define TRIG 5
#define ECHO 16

void setup() {
  pinMode(TRIG, OUTPUT); 
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);   
  display.display();
}

// read distance sensor, return centimeters
float readDistance() {
  digitalWrite(TRIG, LOW); delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  unsigned long timeout=micros()+26233L;
  while((digitalRead(ECHO)==LOW)&&(micros()<timeout));
  unsigned long start_time = micros();
  timeout=start_time+26233L;
  while((digitalRead(ECHO)==HIGH)&&(micros()<timeout));
  unsigned long lapse = micros() - start_time;
  return lapse*0.01716f;
}


void loop() {
  float dist = readDistance();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Dist:");
  display.println(dist);
  display.display();
}
