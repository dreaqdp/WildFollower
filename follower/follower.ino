#include<Servo.h>
#include <Wire.h>
#include <Adafruit_AMG88xx.h>

// servos 
Servo servoy;
Servo servox;

int valx = 0;
int valy = 0;

// Thermal camara
Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
float max_value;
int x, y; 

void setup() {
  servoy.attach(22);
  servox.attach(24);
  servox.write(90);
  servoy.write(90);
  Serial.begin(9600);
  Serial.println(F("AMG88xx pixels"));
  bool status;
    
  // default settings
  status = amg.begin();
  if (!status) {
      Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
      while (1);
  }
  delay(100); // let sensor boot up
}

void loop() {
  /*for (int i = 0; i <= 180; i +=5) {
    servox.write(i);
    //servox.write(i);
    delay(150);
  }

  for (int j = 180; j >= 0; j -= 5) {
    servox.write(j);
    //servox.write(i);
    delay(150);
  }*/
  //read all the pixels
  amg.readPixels(pixels);
  max_value = pixels[0];
  x = y = 0;
  Serial.println("--------");
  for(int i=1; i<AMG88xx_PIXEL_ARRAY_SIZE; i++){
    if (max_value < pixels[i] and pixels[i] > 30.00) {
      max_value = pixels[i];
      x = i/8;
      y = i%8;
    }
  }
  Serial.println("x = ");
  Serial.println(x);
  Serial.println("y =");
  Serial.println(y);
  Serial.println("max = ");
  Serial.println(max_value);
  // re map the current range to the one servo uses [0, 180]
  x = map(x, 0, 7, 0, 180);
  servox.write(x);
  y = map(y, 0, 7, 0, 180);
  servoy.write(y);
  
  delay(500);
   
}
