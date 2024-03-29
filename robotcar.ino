#include <Servo.h>
#include <SoftwareSerial.h>

#include <Ultrasonic.h>

#define mA1 8  //LEFT BOTTOM MOTOR
#define mA2 9
#define mB1 10  //RIGHT BOTTOM MOTOR
#define mB2 11   
#define mAT1 2  //LEFT TOP MOTOR
#define mAT2 3
#define mBT1 4    //Right top motor
#define mBT2 5


int leftLook;
int rightLook;
int distance;
String voice;


SoftwareSerial BT(0, 1); //TX and RX respectively
Servo myservo; //create a servo object
Ultrasonic ultrasonic(6, 7); //Trigger and Echo respectively
void servofunction();
void forward();
void backward();
void left();
void right();
void stop();
void obstacleavoidance();
void comparison();
void distances();




void setup()
{

  pinMode(mA1, OUTPUT);//Set the motor pins as output
  pinMode(mA2, OUTPUT);
  pinMode(mB1, OUTPUT);
  pinMode(mB2, OUTPUT);
   pinMode(mAT1, OUTPUT);//Set the motor pins as output
  pinMode(mAT2, OUTPUT);
  pinMode(mBT1, OUTPUT);
  pinMode(mBT2, OUTPUT);

  myservo.attach(12);//Attaches the servo on pin 12
  BT.begin(9600);
  Serial.begin(9600);//Start a serial communication


  servofunction();
  delay(500);//delay added to make things prominent
 
}

void loop()
{

  while (BT.available()) 
  {// Check for incoming Serial Data over Bluetooth
    delay(10);//Delay added to make things stable
    char c = BT.read();//Conduct a Serial Bluetooth read
    voice += c;//Build the Strings
  }
  if (voice.length() > 0) 
  {//If any Serial data is available
    Serial.println(voice);//Print the data on the serial monitor
  
      //                       Physical Activities

       if (voice == "*look left#")
       {
        myservo.write(180);
      }
      else if (voice == "*look right#") 
      {
        myservo.write(0);
      }
      else if (voice == "*look ahead#")
      {
        myservo.write(90);
      }
      else if (voice == "*turn front#")
      {
        myservo.write(90);
      }

      else if (voice == "*go forward#") 
      {
        forward();
        delay(700);
        stop();
      }
      else if (voice == "A") 
      {
        forward();
      }
      else if (voice == "*go back#") 
      {
        backward();
        delay(700);
        stop();
      }
      else if (voice == "B") 
      {
        backward();
      }
      else if (voice == "*turn left#")
      {
        myservo.write(180);
        delay(500);
        myservo.write(90);
        delay(400);
        left();
        delay(750);
        stop();
      }
      else if (voice == "C") 
      {
        left();
      }
      else if (voice == "G")
      {//look left
        myservo.write(180);
      }
      else if (voice == "*turn right#")
      {
        myservo.write(0);
        delay(500);
        myservo.write(90);
        delay(400);
        right();
        delay(750);
        stop();
      }
      else if (voice == "D") 
      {
        right();
      }
      else if (voice == "F")
      {//look right
        myservo.write(0);
      }
      else if (voice == "*stop#") 
      {
        stop();
       // wtv020sd16p.reset();
        myservo.write(90);
      }
      else if (voice == "E") 
      {
        stop();
        myservo.write(90);
      }

      //                              Performing Activities
      while (voice ==  "*avoid the obstacles#")
      {        // Obstacle avoidance mode
        obstacleavoidance();
      }
    }
    voice = "";//Reset the variable
  }

//                                 Functions

void servofunction() {
  myservo.write(180);
  delay(500);
  myservo.write(90);
  delay(500);
  myservo.write(0);
  delay(500);
  myservo.write(90);
}

void forward() {
  digitalWrite(mA1, HIGH);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
  digitalWrite(mAT1, HIGH);
  digitalWrite(mAT2, LOW);
  digitalWrite(mBT1, HIGH);
  digitalWrite(mBT2, LOW);
}
void backward() {
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
    digitalWrite(mAT1, LOW);
  digitalWrite(mAT2, HIGH);
  digitalWrite(mBT1, LOW);
  digitalWrite(mBT2, HIGH);
}
void right() {
  digitalWrite(mA1, HIGH); 
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, HIGH);
   digitalWrite(mAT1, HIGH); 
  digitalWrite(mAT2, LOW);
  digitalWrite(mBT1, LOW);
  digitalWrite(mBT2, HIGH);
}
void left() {
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, HIGH);
  digitalWrite(mB1, HIGH);
  digitalWrite(mB2, LOW);
  digitalWrite(mAT1, LOW);
  digitalWrite(mAT2, HIGH);
  digitalWrite(mBT1, HIGH);
  digitalWrite(mBT2, LOW);
}
void stop() {
  digitalWrite(mA1, LOW);
  digitalWrite(mA2, LOW);
  digitalWrite(mB1, LOW);
  digitalWrite(mB2, LOW);
   digitalWrite(mAT1, LOW);
  digitalWrite(mAT2, LOW);
  digitalWrite(mBT1, LOW);
  digitalWrite(mBT2, LOW);
}

void obstacleavoidance()
{
  distance = ultrasonic.Ranging(CM); // (Use CM for centimeter and INC for inches)
  delay (50);// check for objects
  
  if (distance > 30) 
  {
    forward();
  }

  else if (distance <= 30) 
  {
    backward();// Act as a brake
    stop(); //Object detected 
    delay(500);
    distances(); // Proceed to the next function

  }
}
void distances()
{

  myservo.write(180);//take distances from the left side
  delay(350);
  leftLook = ultrasonic.Ranging(CM);

  myservo.write(90);
  delay(500);
  myservo.write(0);//take distances from the right side
  delay(350);
  rightLook = ultrasonic.Ranging(CM);
  myservo.write(90);
  delay(40);
  comparison();
}
void comparison() 
{
  if (leftLook > rightLook)
  {
    left();
    delay(750);
    obstacleavoidance();
  }
  else if (leftLook < rightLook)
  {
    right();
    delay(750);
    obstacleavoidance();
  }
  else if (leftLook < 15 && rightLook < 15) 
  {
    backward();
    delay(350);
    stop();
    distances();
  }
}