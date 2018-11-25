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
  //Serial.println("asdf");
  //read all the pixels
  amg.readPixels(pixels);
  max_value = pixels[0];
  x = y = 0;
  //Serial.println("--------");
  for(int i=1; i<AMG88xx_PIXEL_ARRAY_SIZE; i++){
    if (max_value < pixels[i] and pixels[i] > 30.00) {
      max_value = pixels[i];
      x = i/8;
      y = i%8;
    }
  }

 // print_matrix(x, y);
/*
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (i == x && j == y) {
        Serial.print("#");
      } else {
        Serial.print("·");
      }
    }
    Serial.println();
  }
  Serial.print("x = ");
  Serial.println(x);
  Serial.print("y =");
  Serial.println(y);
  Serial.print("max = ");
  Serial.println(max_value);*/
  if (max_value > 29) {
    
    // re map the current range to the one servo uses [0, 180]
    if (x < 3 && oldx < 180) {
      oldx += 5;
    }
    else if (x > 4 && oldx > 0) {
      oldx -=5;
    }
    //Serial.println(oldx);
    servox.write(oldx);
    if (y < 3 && oldy < 180) {
      oldy += 5;
    }
    else if (y > 4 && oldy > 0) {
      oldy -= 5;
    }
    //Serial.println(oldy);
    servoy.write(oldy);
    if ((x >= 2 && x <= 4) && (y >= 2 && y <= 4)) {
      //Serial.println("1-------------1");
      Serial.write(1);
    }
  }  
  delay(500);
   
}
