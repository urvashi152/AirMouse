#include <Wire.h>
#include <MPU6050.h>
#include <Mouse.h>

#define LEFT_SWITCH_PIN 2
#define RIGHT_SWITCH_PIN 3
#define SCROLL_UP_PIN 5
#define SCROLL_DOWN_PIN 4
#define POTENTIOMETER_PIN A3

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;

void setup() {
  Serial.begin(9600);
  Mouse.begin();

  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1); // Stop if the sensor isn't connected
  }

  pinMode(LEFT_SWITCH_PIN, INPUT_PULLUP);
  pinMode(RIGHT_SWITCH_PIN, INPUT_PULLUP);
  pinMode(SCROLL_UP_PIN, INPUT_PULLUP);
  pinMode(SCROLL_DOWN_PIN, INPUT_PULLUP);

  Serial.println("Setup complete, MPU6050 connected!");
}

int angleToMove(int angle) {
  if (angle < -80) return -40;
  else if (angle < -60) return -20;
  else if (angle < -30) return -10;
  else if (angle < -10) return -5;
  else if (angle > 80) return 40;
  else if (angle > 60) return 20;
  else if (angle > 30) return 10;
  else if (angle > 10) return 5;
  else return 0;
}

void loop() {
  // Read motion data
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert accelerometer readings into angles
  int vx = map(ax, -16000, 16000, 90, -90);
  int vy = map(ay, -16000, 16000, 90, -90);

  // Move mouse cursor
  Mouse.move(angleToMove(vx), angleToMove(vy), 0);

  // Handle left click
  if (digitalRead(LEFT_SWITCH_PIN) == LOW) {
    if (!Mouse.isPressed(MOUSE_LEFT)) Mouse.press(MOUSE_LEFT);
  } else {
    if (Mouse.isPressed(MOUSE_LEFT)) Mouse.release(MOUSE_LEFT);
  }

  // Handle right click
  if (digitalRead(RIGHT_SWITCH_PIN) == LOW) {
    if (!Mouse.isPressed(MOUSE_RIGHT)) Mouse.press(MOUSE_RIGHT);
  } else {
    if (Mouse.isPressed(MOUSE_RIGHT)) Mouse.release(MOUSE_RIGHT);
  }

  // Scroll up
  if (digitalRead(SCROLL_UP_PIN) == LOW) {
    Mouse.move(0, 0, 1); // Scroll up
    delay(50);
  }

  // Scroll down
  if (digitalRead(SCROLL_DOWN_PIN) == LOW) {
    Mouse.move(0, 0, -1); // Scroll down
    delay(50);
  }

  // Optional: Adjust scroll speed with potentiometer
  int scrollSpeed = analogRead(POTENTIOMETER_PIN) / 128; // 0–7
  delay(10 + scrollSpeed * 2); // adjustable speed
}
