#include <Servo.h>
const float thruster_config[6][8] = {
  /*
   *      1  2  3  4  5  6  7  8
   * x
   * y
   * z
   * roll
   * pitch
   * yaw
   * 
   */
  {  1.0,  1.0, -1.0, -1.0,  0.0,  0.0,  0.0,  0.0  },
  {  1.0, -1.0,  1.0, -1.0,  0.0,  0.0,  0.0,  0.0  },
  {  0.0,  0.0,  0.0,  0.0,  1.0,  1.0,  1.0,  1.0  },
  {  0.0,  0.0,  0.0,  0.0, -1.0,  1.0, -1.0,  1.0  },
  {  0.0,  0.0,  0.0,  0.0,  1.0,  1.0, -1.0, -1.0  },
  { -1.0,  1.0,  1.0, -1.0,  0.0,  0.0,  0.0,  0.0  }
};

byte led = 0;
byte t1_pin = 1;
byte l_pin = 2;
Servo thruster1;
Servo thruster2;
Servo thruster3;
Servo thruster4;
Servo thruster5;
Servo thruster6;
Servo thruster7;
Servo thruster8;
Servo lights;

void setup() {
  while (!Serial && millis() < 15000) {
    // wait up to 15 seconds for Arduino Serial Monitor
  }
  //pinMode(led, OUTPUT);
  //lights.attach(l_pin);
  thruster1.attach(t1_pin);
  thruster1.writeMicroseconds(1500); // send "stop" signal to ESC.
  delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  // put your main code here, to run repeatedly:

  /* ** read serial messages from jetson
   *    should we handle configuration of thruster power
   *    on jetson or on teensy? probably teensy
   *      message format:
   *          [enum::control_type, value]
   *      or 
   *          binary value
   *          (types) byte, short (16 bits), 
   * ** multiply power value for each value needed in config matrix
   * ** ensure scaling is correct
   * ** send to thruster using servo lib
   * ** ack to serial?
   */

  // example from https://bluerobotics.com/learn/controlling-basic-esc-with-the-arduino-serial-monitor/
  Serial.println("Enter PWM signal value 1100 to 1900, 1500 to stop");
  while (Serial.available() == 0);
  int val = Serial.parseInt(); 
  if(val < 1100 || val > 1900) {
    Serial.println("not valid");
  }
  else {
    thruster1.writeMicroseconds(val); // Send signal to ESC.
  }
  //lights.writeMicroseconds(1700);
  //analogWrite(led, 500);
  delay(1000);
  thruster1.writeMicroseconds(1500);
  //lights.writeMicroseconds(0);
  //analogWrite(led, 0);
}
