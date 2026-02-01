// Miguel Monteiro-Thibault
// MIAE 215 Project

// The goal of this project is to make a servo motor replicate the motion of a tachometer in a car. A potentiometer will be used like a throttle,
// and a passive buzzer will be used to make sounds to sound like an engine.
const int PIN_BUZZ = 11;
const int PIN_SERVO = 7;
const int PIN_LED = 3;

const float k_factor= 0.25; //will be explained later

float rpm = 0;

const float MAX_RPM = 7500; // redline at 7000, limiter at 7500, just for fun.
const float IDLE_RPM = 850; 
#include <Servo.h> //necessary library file

Servo servo1; //declaring servo object

void setup()
{
  // set up the pin modes to the desired ones
  pinMode (PIN_BUZZ,OUTPUT);
  pinMode (PIN_LED, OUTPUT);

  servo1.attach(PIN_SERVO); //set up the servo object

  Serial.begin (115200);

  servo1.write (0); //start the servo motor at the 0 position

  delay (500); // give the servo time to get to the 0 position 
}

float CheckThrottle();
void writeServo(float rpm);
void modifyRPM(float &rpm,float throttle,float t1,float &t2);
void makeSound(float rpm);
void flashLED();
void printVal(float rpm, float t);


void loop() 
{
float t1,t2; //store time in order to use later.

  t1=millis();


  float throttle= CheckThrottle(); // Check the throttle input (potentiometer input).

  modifyRPM(rpm,throttle,t1,t2); // Change the RPM value according to the potentiometer input. Also calculates t2.
  
  writeServo(rpm);  // Instructs the servo to move to the position required to represent the RPM.

  makeSound(rpm); // Plays a sound through the passive buzzer related to the RPM of the system.

  //printVal(rpm, t2); // Prints values of the system to serial for optimization/debugging. Will be commented out (when not debugging) 
                     // to improve program performance but still included in the submitted file.
}


float CheckThrottle()
{
  float val, ans;
    val= analogRead(A0); //read potentiometer input 

  ans=(val-400); // In real cars, once the throttle goes under a certain threshold, RPMs begin to decrease. In this case,
                 // if the read analog input for the potentiometer is lower than 300 (out of approximately 1000 due to the design of the circuit and the resistance of the capacitor)
                 // RPMs begin to decrease. 

  return ans;
  

}

void writeServo(float rpm)
{
  // want that 180 = 7500. Therefore :

  float theta_d = (rpm*(180.f/7500.f));
  servo1.write(180-theta_d); // this should make the movement of the tachometer clockwise, as is the case in most cars. If not made negative, the tachometer would be 
                             // counter-clockwise.

}

void modifyRPM(float &rpm,float throttle,float t1,float &t2)
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                  Calculating the change in RPM for each loop iteration                       //
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // If the potentiometer is meant to represent the engine throttle, then the engine RPM should represent the   //
  // integral of the engine throttle with respect to time. Therefore, dRPM = throttle*t.                       //
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////


  t2= millis();
  float dt=0;
  dt=t2-t1;

  rpm=rpm+(throttle*k_factor*dt); // k_factor is an arbitrarily-defined value that modifies the slope of the rpm function in order to 
                                // make it seem more realisic. The value was found through plug-and-play repetition.

  if(rpm>7000.f) //redline zone
  {
  flashLED(); // make the red LED flash when the redline is reached. 
    if(rpm>MAX_RPM) rpm=rpm-1000; // differentiate between being in the redline area (when repairs might be needed) to rev limiting threshold (when the car will not go further)

    return;
  }
  else if(rpm<IDLE_RPM)
  {rpm=IDLE_RPM; delay(2); return;} //the reason both these cases delay by 2 ms is because the flash LED function needs to delay in order to let the LED shine.
                                      //Regardless, the void loop function would need to be delayed 2 ms anyway, because it gives stability to the program (letting it iterate constantly causes irregularities)

  else delay(2);
                      
}

void makeSound(float rpm)
{
  tone(PIN_BUZZ,rpm/20);  //speaker produces a tone of frequency rpm/20 in order to (somewhat) represent a real car sound. In practice, it succeeds in
                           // sounding like a car in a 1980s videogame.
}

void flashLED()
{
digitalWrite(PIN_LED, HIGH);  //turn on the LED
delay (2); // let the LED shine for a bit
digitalWrite(PIN_LED, LOW);   //then turn it off
}

void printVal(float rpm, float t)   // this function prints to any connected computer in such a way that the outputs can be graphed in the arduino IDE. 
{
  Serial.print("\n");
  Serial.print(rpm);
  Serial.print(",");
  Serial.print(t);
}


