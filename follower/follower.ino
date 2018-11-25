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
int x, y, oldx, oldy; 

void setup() {
  servoy.attach(22);
  servox.attach(24);
  oldx = oldy = 90;
  servox.write(oldx);
  servoy.write(oldy);

  Serial.begin(9600);
  //Serial1.begin(9600);
  //Serial.println(F("AMG88xx pixels"));
  bool status;
    
  // default settings
  status = amg.begin();
  if (!status) {
      //Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
      while (1);
  }
  //Serial.println("last part setup");
  delay(100); // let sensor boot up
}

void loop() {
  //read all the pixels
  amg.readPixels(pixels);
  max_value = pixels[0];
  x = y = 0;

  for(int i=1; i<AMG88xx_PIXEL_ARRAY_SIZE; i++){
    if (max_value < pixels[i] and pixels[i] > 30.00) {
      max_value = pixels[i];
      x = i/8;
      y = i%8;
    }
  }

  if (max_value > 29) {
    if (y < 3 && oldx < 180) {
      oldx -= 5;
    }
    else if (y > 4 && oldx > 0) {
      oldx +=5;
    }
    servox.write(oldx);
    
    if (x < 3 && oldy < 180) {
      oldy -= 5;
    }
    else if (x > 4 && oldy > 0) {
      oldy += 5;
    }
    servoy.write(oldy);
    
    if ((x >= 2 && x <= 4) && (y >= 2 && y <= 4)) {

      Serial.write(1);
    }
  }  
  delay(500);
}
