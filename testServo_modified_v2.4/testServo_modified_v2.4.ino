#include <Wire.h> //Library which allows I2C communication.
#include <Adafruit_PWMServoDriver.h> //This library must be downloaded to run the code.
 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();//Instantiating objects with the Adafruit_PWMServoDriver class.
 
#define MIN_PULSE_WIDTH 500   //These are the minimum and maximum wavelength values which serve MG 995.
#define MAX_PULSE_WIDTH 2500
#define DEFAULT_PULSE_WIDTH 1500
#define FREQUENCY 50
 
int pulseWidth(int angle){ //This function calculates servo's motion angle.
int pulse_wide, analog_value;
pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH); //This function get angle from 0 to 180 degrees and map from length minimum value to maximum. 
analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
Serial.println(analog_value);
return analog_value; //The value this function returns.
}
  
void setup(){
Serial.begin(9600);
//Serial.println("16 channel Servo test!");
pwm.begin();  //Initialize the library and send PWM signals.
pwm.setPWMFreq(FREQUENCY); //Servo's update frequency at 60 Hertz.
// pwm.setPWM(1,0,pulseWidth(120)); //HIP_SERVO 1,
pwm.setPWM(2,0,pulseWidth(126)); //WAAAIST_SERVO
pwm.setPWM(3,0,pulseWidth(85)); //SHOULDER_SERVO
pwm.setPWM(4,0,pulseWidth(90)); //ELBOW_SERVO 
pwm.setPWM(5,0,pulseWidth(0)); //WRIST_SERVO
pwm.setPWM(6,0,pulseWidth(67)); //CRAW_SERVO
}
 

void loop() {
  if (Serial.available()) { // Check if data is available on the serial port
    String command = Serial.readStringUntil('\n'); // Read the command
    executeCommand(command);
  }


}

void executeCommand(String command) {
  if (command.startsWith("HIP ")) {
    int angle = command.substring(4).toInt();
    pwm.setPWM(1, 0, pulseWidth(angle));
    Serial.println("HIP moved to " + String(angle) + " degrees");
  } else if (command.startsWith("WAAAIST ")) {
    int angle = command.substring(8).toInt();
    pwm.setPWM(2, 0, pulseWidth(angle));
    Serial.println("WAAAIST moved to " + String(angle) + " degrees");
  } else if (command.startsWith("SHOULDER ")) {
    int angle = command.substring(9).toInt();
    pwm.setPWM(3, 0, pulseWidth(angle));
    Serial.println("SHOULDER moved to " + String(angle) + " degrees");
  } else if (command.startsWith("ELBOW ")) {
    int angle = command.substring(6).toInt();
    pwm.setPWM(4, 0, pulseWidth(angle));
    Serial.println("ELBOW moved to " + String(angle) + " degrees");
  } else if (command.startsWith("WRIST ")) {
    int angle = command.substring(6).toInt();
    pwm.setPWM(5, 0, pulseWidth(angle));
    Serial.println("WRIST moved to " + String(angle) + " degrees");
  } else if (command.startsWith("CRAW ")) {
    int angle = command.substring(5).toInt();
    pwm.setPWM(6, 0, pulseWidth(angle));
    Serial.println("CRAW moved to " + String(angle) + " degrees");
  } else {
    Serial.println("Unknown command: " + command);
  }
}
