// Define motor pins
const int motorA1 = 5; // IN1
const int motorA2 = 6; // IN2
const int motorB1 = 10; // IN3
const int motorB2 = 11; // IN4
const int enableA = 9; // ENA
const int enableB = 8; // ENB

// Define ultrasonic sensor pins
const int trigPin = 7;
const int echoPin = 8;

// Define variables for distance measurement
long duration;
int distance;

void setup() {
  // Initialize motor pins as outputs
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  
  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Set initial motor speed
  analogWrite(enableA, 255);
  analogWrite(enableB, 255);
  
  // Begin serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Measure distance using ultrasonic sensor
  distance = measureDistance();
  
  // Debugging output
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // Decision making based on distance
  if (distance < 20) {
    // If too close to the wall, turn right
    turnRight();
  } else {
    // If at a safe distance, move forward
    moveForward();
  }
  
  delay(100); // Small delay for stability
}

int measureDistance() {
  // Send a 10us pulse to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in cm
  distance = duration * 0.034 / 2;
  
  return distance;
}

void moveForward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void turnRight() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void stopMotors() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
