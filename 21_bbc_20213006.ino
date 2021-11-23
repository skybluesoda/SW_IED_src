
#include <Servo.h>

#define PIN_IR A0
#define PIN_LED 9
#define PIN_SERVO 10

int angle = 90;
int a, b; // unit: mm
Servo myservo;

void setup() {
  myservo.attach(PIN_SERVO);
  // myservo.write(90);
  myservo.writeMicroseconds(1500);
  //myservo.writeMicroseconds(1000); 
  //myservo.writeMicroseconds(2000);
// initialize GPIO pins
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED, 1);
  
// initialize serial port
  Serial.begin(57600);

  a = 98; //70;
  b = 390; //300;
}

float ir_distance(void){ // return value unit: mm
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  return val;
}

void loop() {
  float raw_dist = ir_distance();
  if (raw_dist > b && raw_dist < a){
    raw_dist = ir_distance();
  }
  float dist_cali = 100 + 300.0 / (b - a) * (raw_dist - a);
  Serial.print("min:0,max:500,dist:");
  Serial.print(raw_dist);
  Serial.print(",dist_cali:");
  Serial.println(dist_cali);
  if(dist_cali > 255){
    for (angle = 0; angle < 80; angle++){
      myservo.write(angle);
      delay(30);
    }
  }
  if(dist_cali < 255){
    for (angle = 90; angle < 110; angle++){
      myservo.write(angle);
      delay(30);
    }
  }
  if(raw_dist > 156 && raw_dist <224) digitalWrite(PIN_LED, 0);
  else digitalWrite(PIN_LED, 255);
  delay(300);
}
