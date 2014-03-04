// include the servo library
#include <Servo.h>

Servo myServo;  // create a servo object 

int angle = 0; 
const int msgBufferLen = 80;
char msg[msgBufferLen];
char msgSeparator = '\n';
String message;

const String msgRotate = "angle";
/* Send message like: "angle 20" (value between 0 and 180) */

void setup() {
  myServo.attach(9); // attaches the servo on pin 9 to the servo object 
  Serial.begin(115200); // open a serial connection to your computer
}

void loop() {

  //Serial.print("angle: ");
  //Serial.println(angle); 

  // set the servo position  
  myServo.write(angle);

  // wait for the servo to get there 
  delay(15);
}

void serialEvent(){
  Serial.readBytesUntil(msgSeparator, msg, msgBufferLen);
  message = String(msg);
  Serial.println(message);  
  //trim newline character from message
  message = message.substring(0, message.length()-1);
  if (message.startsWith(msgRotate)) {
    Serial.print("Rotate message received, angle = ");
    int ix = message.lastIndexOf(msgRotate) + msgRotate.length();
    angle = message.substring(ix).toInt();
  }
  else {
    Serial.println("No valid message");
  }  
  //reset the char array
  memset(msg, 0, sizeof msg);  
}
