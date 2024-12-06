#include <Servo.h>  // For controlling the servo motor

// Pin definitions
const int proximitySensorPin = D8; // Proximity sensor connected to GPIO5
const int servoPin = D2;           // Servo motor signal pin connected to GPIO4
const int dirPin = D6;              // Stepper motor DIR pin
const int stepPin = D7;             // Stepper motor STEP pin
const int stepsPerRevolution = 200; // Number of steps per revolution for the stepper motor

// Servo setup
Servo myServo;

void setup()
{
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize proximity sensor
  pinMode(proximitySensorPin, INPUT);

  // Initialize servo motor
  myServo.attach(servoPin);
  myServo.write(90); // Neutral position

  // Initialize stepper motor pins
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  Serial.println("System initialized");
}

void loop()
{
  // Check if the proximity sensor detects an object
  if (digitalRead(proximitySensorPin) == HIGH)
  {
    Serial.println("Object detected!");

    // Mock classification of object
    bool isMetallic = classifyObject();

    if (isMetallic)
    {
      Serial.println("Metallic object detected. Moving to Bin 1...");
      moveServoToBin(45); // Bin 1 (left)
    }
    else
    {
      Serial.println("Non-metallic object detected. Moving to Bin 2...");
      moveServoToBin(135); // Bin 2 (right)
    }

    delay(2000); // Pause for action to complete

    // Reset servo position
    moveServoToBin(90); // Neutral position

    // Use stepper motor to reset or assist
    resetStepper();
  }
}

// Function to classify the object (mock logic, replace with real sensor)
bool classifyObject()
{
  // Mock classification: Assume input from Serial Monitor
  Serial.println("Enter classification (1 for metallic, 0 for non-metallic):");
  while (!Serial.available()); // Wait for user input
  char input = Serial.read();
  return (input == '1');
}

// Function to move the servo to a specific angle
void moveServoToBin(int angle)
{
  myServo.write(angle);
  delay(500); // Allow servo to reach position
}

// Function to reset or assist using the stepper motor
void resetStepper()
{
  Serial.println("Resetting stepper motor...");

  // Stepper motor moves forward
  digitalWrite(dirPin, HIGH); // Clockwise direction
  for (int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000); // Adjust speed
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

  delay(1000); // Wait a second

  // Stepper motor moves backward
  digitalWrite(dirPin, LOW); // Counterclockwise direction
  for (int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000); // Adjust speed
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

  delay(1000); // Wait a second
}
