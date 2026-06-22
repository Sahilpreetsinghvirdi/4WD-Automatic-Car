// C++ code
//
#include <Adafruit_LiquidCrystal.h>

#include "Adafruit_LEDBackpack.h"

#include <Servo.h>

int light = 0;

int slideswitch = 0;

int udsd = 0;

int udsf = 0;

int udsl = 0;

int udsr = 0;

int udsbl = 0;

int udsbr = 0;

int udsb = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Adafruit_LiquidCrystal lcd_1(0);

Adafruit_7segment led_display1 = Adafruit_7segment();

Servo servo_13;

void setup()
{
  pinMode(A3, INPUT);
  pinMode(0, INPUT);
  lcd_1.begin(16, 2);
  led_display1.begin(112);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  servo_13.attach(13, 500, 2500);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  lcd_1.display();
  lcd_1.setBacklight(1);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Hello sir/mam");
  lcd_1.setCursor(0, 1);
  lcd_1.print("This is Jarvis");
  delay(1000); // Wait for 1000 millisecond(s)
  lcd_1.setCursor(0, 0);
  lcd_1.clear();
  lcd_1.print("This is a 4WD ");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Smart car");
  delay(1000); // Wait for 1000 millisecond(s)
  if (analogRead(A3) == 0) {
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
  } else {
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
  }
  if (slideswitch == 0) {
    lcd_1.setCursor(0, 0);
    lcd_1.clear();
    lcd_1.print("Please turn ONN the ");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Car Engine.");
  } else {
    lcd_1.setCursor(0, 0);
    lcd_1.clear();
    lcd_1.print("Car is ready");
    lcd_1.setCursor(0, 1);
    lcd_1.print("to go in......");
    led_display1.println("0005");
    led_display1.writeDisplay();
    delay(1000); // Wait for 1000 millisecond(s)
    led_display1.println("0004");
    led_display1.writeDisplay();
    delay(1000); // Wait for 1000 millisecond(s)
    led_display1.println("0003");
    led_display1.writeDisplay();
    delay(1000); // Wait for 1000 millisecond(s)
    led_display1.println("0002");
    led_display1.writeDisplay();
    delay(1000); // Wait for 1000 millisecond(s)
    led_display1.println("0001");
    led_display1.writeDisplay();
    delay(1000); // Wait for 1000 millisecond(s)
    led_display1.println("0000");
    led_display1.writeDisplay();
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    led_display1.clear();
    led_display1.writeDisplay();
    servo_13.write(90);
  }
}

void loop()
{
  light = analogRead(A3);
  udsf = 0.01723 * readUltrasonicDistance(7, 7);
  udsl = 0.01723 * readUltrasonicDistance(8, 8);
  udsr = 0.01723 * readUltrasonicDistance(9, 9);
  udsbl = 0.01723 * readUltrasonicDistance(10, 10);
  udsbr = 0.01723 * readUltrasonicDistance(11, 11);
  udsd = 0.01723 * readUltrasonicDistance(12, 12);
  udsb = 0.01723 * readUltrasonicDistance(A0, A0);
  slideswitch = digitalRead(0);
  if (light == 0) {
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
  } else {
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
  }
  if (slideswitch == 0) {
    if (light == 0) {
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
    } else {
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
    }
    lcd_1.setCursor(0, 0);
    lcd_1.clear();
    lcd_1.print("Car Engiine is OFF");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Please turn it ONN");
    analogWrite(5, 0);
    analogWrite(3, 0);
  }
  if (slideswitch == 1) {
    if (udsd < 100) {
      if (light == 0) {
        digitalWrite(A1, HIGH);
        digitalWrite(A2, HIGH);
      } else {
        digitalWrite(A1, LOW);
        digitalWrite(A2, LOW);
      }
      lcd_1.clear();
      lcd_1.setCursor(0, 0);
      lcd_1.print("Engine = ONN");
      lcd_1.setCursor(0, 1);
      lcd_1.print("Speed = 150");
      digitalWrite(1, HIGH);
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      analogWrite(5, 150);
      analogWrite(6, 150);
      if (udsf < 200) {
        lcd_1.setCursor(0, 0);
        lcd_1.clear();
        lcd_1.print("Obstacle detected");
        if (udsl > 200 && udsr > 200) {
          lcd_1.clear();
          lcd_1.print("Both side clear");
          lcd_1.setCursor(0, 1);
          lcd_1.print("Turning slight right.");
          analogWrite(5, 190);
          analogWrite(6, 150);
          delay(1000); // Wait for 1000 millisecond(s)
          lcd_1.setCursor(0, 0);
          lcd_1.clear();
          lcd_1.print("Going angle straight");
          analogWrite(5, 150);
          analogWrite(6, 150);
          while (!(udsl < 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          while (!(udsl > 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print("Becoming straight");
          analogWrite(5, 150);
          analogWrite(6, 190);
          delay(1000); // Wait for 1000 millisecond(s)
          lcd_1.clear();
          lcd_1.print("Going straight");
          analogWrite(5, 150);
          analogWrite(6, 150);
          while (!(udsbl < 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          while (!(udsbl > 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          lcd_1.clear();
          lcd_1.print("Turning slight left.");
          analogWrite(5, 150);
          analogWrite(6, 190);
          delay(1000); // Wait for 1000 millisecond(s)
          lcd_1.clear();
          lcd_1.print("Going angled straight.");
          analogWrite(5, 150);
          analogWrite(6, 150);
          while (!(udsbl < 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          while (!(udsbl > 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          lcd_1.clear();
          lcd_1.print("Becoming straight.");
          analogWrite(5, 190);
          analogWrite(6, 150);
          delay(1000); // Wait for 1000 millisecond(s)
          lcd_1.clear();
          lcd_1.print("Going straight.");
          analogWrite(5, 150);
          analogWrite(6, 150);
          lcd_1.clear();
          lcd_1.print("Engine = ONN");
          lcd_1.setCursor(0, 1);
          lcd_1.print("Speed = 150");
          lcd_1.setCursor(0, 0);
        }
        if (udsl > 200 && udsr < 200) {
          lcd_1.clear();
          lcd_1.print("Left clear , right blocked.");
          lcd_1.setCursor(0, 1);
          lcd_1.print("Turning slight left.");
          analogWrite(5, 150);
          analogWrite(6, 190);
          delay(1000); // Wait for 1000 millisecond(s)
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print("Going angle straight");
          analogWrite(5, 150);
          analogWrite(6, 150);
          while (!(udsr < 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          while (!(udsr > 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          lcd_1.clear();
          lcd_1.print("Becoming straight");
          analogWrite(5, 190);
          analogWrite(6, 150);
          delay(1000); // Wait for 1000 millisecond(s)
          lcd_1.clear();
          lcd_1.print("Going straight");
          analogWrite(5, 150);
          analogWrite(6, 150);
          while (!(udsbr < 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          while (!(udsbr > 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          lcd_1.clear();
          lcd_1.print("Turning slight right");
          analogWrite(5, 190);
          analogWrite(6, 150);
          delay(1000); // Wait for 1000 millisecond(s)
          lcd_1.clear();
          lcd_1.print("Going angle straight");
          analogWrite(5, 150);
          analogWrite(6, 150);
          while (!(udsbr < 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          while (!(udsbr > 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          lcd_1.clear();
          lcd_1.print("Becoming straight");
          analogWrite(5, 150);
          analogWrite(6, 190);
          delay(1000); // Wait for 1000 millisecond(s)
          lcd_1.clear();
          lcd_1.print("Going straight");
          analogWrite(5, 150);
          analogWrite(6, 150);
          lcd_1.clear();
          lcd_1.print("Engine = ONN");
          lcd_1.setCursor(0, 1);
          lcd_1.print("Speed = 150");
          lcd_1.setCursor(0, 0);
        }
        if (udsl < 200 && udsr > 200) {
          lcd_1.clear();
          lcd_1.print("Left blocked, right clear.");
          lcd_1.setCursor(0, 1);
          lcd_1.print("Turning slight right.");
          analogWrite(5, 190);
          analogWrite(6, 150);
          delay(1000); // Wait for 1000 millisecond(s)
          lcd_1.setCursor(0, 0);
          lcd_1.clear();
          lcd_1.print("Going angle straight");
          analogWrite(5, 150);
          analogWrite(6, 150);
          while (!(udsl < 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          while (!(udsl > 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          lcd_1.clear();
          lcd_1.setCursor(0, 0);
          lcd_1.print("Becoming straight");
          analogWrite(5, 150);
          analogWrite(6, 190);
          delay(1000); // Wait for 1000 millisecond(s)
          lcd_1.clear();
          lcd_1.print("Going straight");
          analogWrite(5, 150);
          analogWrite(6, 150);
          while (!(udsbl < 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          while (!(udsbl > 200)) {
            delay(500); // Wait for 500000 millisecond(s)
          }
          lcd_1.clear();
          lcd_1.print("Turning slight left.");
          analogWrite(5, 150);
          analogWrite(6, 190);
          delay(1000); // Wait for 1000 millisecond(s)
          lcd_1.clear();
          lcd_1.print("Going angled straight.");
          analogWrite(5, 150);
          analogWrite(6, 150);
          while (!(udsbl < 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          while (!(udsbl > 200)) {
            delay(500); // Wait for 500 millisecond(s)
          }
          lcd_1.clear();
          lcd_1.print("Becoming straight.");
          analogWrite(5, 190);
          analogWrite(6, 150);
          delay(1000); // Wait for 1000 millisecond(s)
          lcd_1.clear();
          lcd_1.print("Going straight.");
          analogWrite(5, 150);
          analogWrite(6, 150);
          lcd_1.clear();
          lcd_1.print("Engine = ONN");
          lcd_1.setCursor(0, 1);
          lcd_1.print("Speed = 150");
          lcd_1.setCursor(0, 0);
        }
        if (udsl < 200 && udsr < 200) {
          lcd_1.setCursor(0, 0);
          lcd_1.clear();
          lcd_1.print("Both blocked");
          analogWrite(5, 0);
          analogWrite(6, 0);
          lcd_1.clear();
          lcd_1.print("Car stopped");
          lcd_1.clear();
          lcd_1.print("Checking right");
          servo_13.write(0);
          delay(1000); // Wait for 1000 millisecond(s)
          // seeing right clear
          if (udsf > 200) {
            lcd_1.clear();
            lcd_1.print("Right is cleared");
            lcd_1.clear();
            lcd_1.print("Checking left");
            servo_13.write(180);
            delay(1000); // Wait for 1000 millisecond(s)
            // seeing left clear
            if (udsf > 200) {
              lcd_1.clear();
              lcd_1.print("Left also clear");
              lcd_1.clear();
              lcd_1.print("Car rotating right.");
              // rotating right
              servo_13.write(90);
              digitalWrite(A1, HIGH);
              digitalWrite(A2, LOW);
              digitalWrite(1, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, LOW);
              digitalWrite(4, HIGH);
              analogWrite(5, 150);
              analogWrite(6, 150);
              delay(2000); // Wait for 2000 millisecond(s)
              digitalWrite(1, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, HIGH);
              digitalWrite(4, LOW);
              digitalWrite(A1, LOW);
              digitalWrite(A2, LOW);
              lcd_1.clear();
              lcd_1.print("Engine = ONN");
              lcd_1.setCursor(0, 1);
              lcd_1.print("Speed = 150");
            }
            // seeing left unclear
            if (udsf < 200) {
              lcd_1.clear();
              lcd_1.setCursor(0, 0);
              lcd_1.print("Left unclear.");
              lcd_1.clear();
              lcd_1.print("Car rotating right.");
              servo_13.write(90);
              digitalWrite(A1, HIGH);
              digitalWrite(A2, LOW);
              digitalWrite(1, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, LOW);
              digitalWrite(4, HIGH);
              analogWrite(5, 150);
              analogWrite(6, 150);
              delay(2000); // Wait for 2000 millisecond(s)
              digitalWrite(1, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, HIGH);
              digitalWrite(4, LOW);
              digitalWrite(A1, LOW);
              digitalWrite(A2, LOW);
              lcd_1.clear();
              lcd_1.print("Engine = ONN");
              lcd_1.setCursor(0, 1);
              lcd_1.print("Speed = 150");
            }
          }
          // seeing right unclear
          if (udsf < 200) {
            lcd_1.setCursor(0, 0);
            lcd_1.clear();
            lcd_1.print("Right unlear.");
            lcd_1.clear();
            lcd_1.print("Checking left");
            servo_13.write(180);
            delay(1000); // Wait for 1000 millisecond(s)
            // seeing left clear.
            if (udsf > 200) {
              lcd_1.clear();
              lcd_1.print("Left clear");
              lcd_1.clear();
              lcd_1.print("Car rotating left");
              servo_13.write(90);
              digitalWrite(A1, LOW);
              digitalWrite(A2, HIGH);
              digitalWrite(1, LOW);
              digitalWrite(2, HIGH);
              digitalWrite(3, HIGH);
              digitalWrite(4, LOW);
              analogWrite(5, 150);
              analogWrite(6, 150);
              delay(2000); // Wait for 2000 millisecond(s)
              digitalWrite(1, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, HIGH);
              digitalWrite(4, LOW);
              digitalWrite(A1, LOW);
              digitalWrite(A2, LOW);
              lcd_1.clear();
              lcd_1.print("Engine = ONN");
              lcd_1.setCursor(0, 1);
              lcd_1.print("Speed = 150");
            }
            // if left unclear
            if (udsf < 200) {
              lcd_1.setCursor(0, 0);
              lcd_1.clear();
              lcd_1.print("all side blocked");
              servo_13.write(90);
              // reverse
              lcd_1.clear();
              lcd_1.print("Car reversing");
              digitalWrite(A1, HIGH);
              digitalWrite(A2, HIGH);
              digitalWrite(1, LOW);
              digitalWrite(2, HIGH);
              digitalWrite(3, LOW);
              digitalWrite(4, HIGH);
              analogWrite(5, 150);
              analogWrite(6, 150);
              while (!(udsbl > 200 || (udsbr > 200 || udsb < 200))) {
                delay(500); // Wait for 500 millisecond(s)
              }
              analogWrite(5, 0);
              analogWrite(6, 0);
              if (udsbl > 200) {
                lcd_1.clear();
                lcd_1.print("Left clear");
                lcd_1.clear();
                lcd_1.print("Rotating left");
                digitalWrite(1, LOW);
                digitalWrite(2, HIGH);
                digitalWrite(3, HIGH);
                digitalWrite(4, LOW);
                analogWrite(5, 150);
                analogWrite(6, 150);
                delay(2000); // Wait for 2000 millisecond(s)
                digitalWrite(1, HIGH);
                digitalWrite(2, LOW);
                digitalWrite(3, HIGH);
                digitalWrite(4, LOW);
              }
              if (udsbr > 200) {
                lcd_1.clear();
                lcd_1.print("Right clear");
                lcd_1.clear();
                lcd_1.print("Rotating right");
                digitalWrite(1, HIGH);
                digitalWrite(2, LOW);
                digitalWrite(3, LOW);
                digitalWrite(4, HIGH);
                analogWrite(5, 150);
                analogWrite(6, 150);
                delay(2000); // Wait for 2000 millisecond(s)
                digitalWrite(1, HIGH);
                digitalWrite(2, LOW);
                digitalWrite(3, HIGH);
                digitalWrite(4, LOW);
              }
              if (udsbl > 200 && udsbr > 200) {
                lcd_1.clear();
                lcd_1.print("Both side clear");
                lcd_1.clear();
                lcd_1.print("Rotating right");
                digitalWrite(1, HIGH);
                digitalWrite(2, LOW);
                digitalWrite(3, LOW);
                digitalWrite(4, HIGH);
                analogWrite(5, 150);
                analogWrite(6, 150);
                delay(2000); // Wait for 2000 millisecond(s)
                digitalWrite(1, HIGH);
                digitalWrite(2, LOW);
                digitalWrite(3, HIGH);
                digitalWrite(4, LOW);
              }
              if (udsb < 200) {
                lcd_1.clear();
                lcd_1.print("Car stoped");
                digitalWrite(1, HIGH);
                digitalWrite(2, LOW);
                digitalWrite(3, HIGH);
                digitalWrite(4, LOW);
                analogWrite(5, 0);
                analogWrite(6, 0);
              }
              digitalWrite(A1, LOW);
              digitalWrite(A2, LOW);
            }
          }
        }
      }
      if (udsbl < 200 || udsbr < 200) {
        if (udsbl < 200) {
          analogWrite(5, 190);
          analogWrite(6, 150);
          delay(1000); // Wait for 1000 millisecond(s)
          analogWrite(5, 150);
          analogWrite(6, 150);
          while (!(udsbl > 200 || (udsbr < 200 || udsf < 200))) {
            delay(500); // Wait for 500 millisecond(s)
          }
          if (udsbl > 200 || udsbr < 200) {
            analogWrite(5, 150);
            analogWrite(6, 190);
            delay(1000); // Wait for 1000 millisecond(s)
            analogWrite(5, 150);
            analogWrite(6, 150);
          }
        }
        if (udsbr < 200) {
          analogWrite(5, 150);
          analogWrite(6, 190);
          delay(1000); // Wait for 1000 millisecond(s)
          analogWrite(5, 150);
          analogWrite(6, 150);
          delay(1000); // Wait for 1000 millisecond(s)
          while (!(udsbr > 200 && (udsbl < 200 && udsf < 200))) {
            delay(500); // Wait for 500 millisecond(s)
          }
          if (udsbr > 200 || udsbl < 200) {
            analogWrite(5, 190);
            analogWrite(6, 150);
            delay(1000); // Wait for 1000 millisecond(s)
            analogWrite(5, 150);
            analogWrite(6, 150);
          }
        }
        if (udsbl < 200 && udsbr < 200) {
          if (udsbl < udsbr) {
            analogWrite(5, 190);
            analogWrite(6, 150);
            delay(1000); // Wait for 1000 millisecond(s)
            analogWrite(5, 150);
            analogWrite(6, 150);
            while (!(udsbl == udsbr && udsf < 200)) {
              delay(500); // Wait for 500 millisecond(s)
            }
            if (udsbl == udsbr) {
              analogWrite(5, 190);
              analogWrite(6, 150);
              delay(1000); // Wait for 1000 millisecond(s)
              analogWrite(5, 150);
              analogWrite(6, 150);
            }
          }
          if (udsbl > udsbr) {
            analogWrite(5, 150);
            analogWrite(6, 190);
            delay(1000); // Wait for 1000 millisecond(s)
            analogWrite(5, 150);
            analogWrite(6, 190);
            while (!(udsbl == udsbr && udsf < 200)) {
              delay(500); // Wait for 500 millisecond(s)
            }
            if (udsbl == udsbr) {
              analogWrite(5, 150);
              analogWrite(6, 190);
              delay(1000); // Wait for 1000 millisecond(s)
              analogWrite(5, 150);
              analogWrite(6, 150);
            }
          }
        }
      }
    } else {
      analogWrite(5, 200);
      analogWrite(6, 200);
      digitalWrite(1, LOW);
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      while (!(udsd < 100 || udsb < 200)) {
        delay(500); // Wait for 500 millisecond(s)
      }
      analogWrite(5, 0);
      analogWrite(6, 0);
      digitalWrite(1, HIGH);
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      if (udsb < 200) {
        analogWrite(5, 0);
        analogWrite(6, 0);
      }
      if (udsd < 100) {
        analogWrite(5, 0);
        analogWrite(6, 0);
        lcd_1.clear();
        lcd_1.print("Car stopped");
        lcd_1.clear();
        lcd_1.print("Checking right");
        servo_13.write(0);
        delay(1000); // Wait for 1000 millisecond(s)
        // seeing right clear
        if (udsf > 200) {
          lcd_1.clear();
          lcd_1.print("Right is cleared");
          lcd_1.clear();
          lcd_1.print("Checking left");
          servo_13.write(180);
          delay(1000); // Wait for 1000 millisecond(s)
          // seeing left clear
          if (udsf > 200) {
            lcd_1.clear();
            lcd_1.print("Left also clear");
            lcd_1.clear();
            lcd_1.print("Car rotating right.");
            // rotating right
            servo_13.write(90);
            digitalWrite(A1, HIGH);
            digitalWrite(A2, LOW);
            digitalWrite(1, HIGH);
            digitalWrite(2, LOW);
            digitalWrite(3, LOW);
            digitalWrite(4, HIGH);
            analogWrite(5, 150);
            analogWrite(6, 150);
            delay(2000); // Wait for 2000 millisecond(s)
            digitalWrite(1, HIGH);
            digitalWrite(2, LOW);
            digitalWrite(3, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(A1, LOW);
            digitalWrite(A2, LOW);
            lcd_1.clear();
            lcd_1.print("Engine = ONN");
            lcd_1.setCursor(0, 1);
            lcd_1.print("Speed = 150");
          }
          // seeing left unclear
          if (udsf < 200) {
            lcd_1.clear();
            lcd_1.setCursor(0, 0);
            lcd_1.print("Left unclear.");
            lcd_1.clear();
            lcd_1.print("Car rotating right.");
            servo_13.write(90);
            digitalWrite(A1, HIGH);
            digitalWrite(A2, LOW);
            digitalWrite(1, HIGH);
            digitalWrite(2, LOW);
            digitalWrite(3, LOW);
            digitalWrite(4, HIGH);
            analogWrite(5, 150);
            analogWrite(6, 150);
            delay(2000); // Wait for 2000 millisecond(s)
            digitalWrite(1, HIGH);
            digitalWrite(2, LOW);
            digitalWrite(3, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(A1, LOW);
            digitalWrite(A2, LOW);
            lcd_1.clear();
            lcd_1.print("Engine = ONN");
            lcd_1.setCursor(0, 1);
            lcd_1.print("Speed = 150");
          }
        }
        // seeing right unclear
        if (udsf < 200) {
          lcd_1.setCursor(0, 0);
          lcd_1.clear();
          lcd_1.print("Right unlear.");
          lcd_1.clear();
          lcd_1.print("Checking left");
          servo_13.write(180);
          delay(1000); // Wait for 1000 millisecond(s)
          // seeing left clear.
          if (udsf > 200) {
            lcd_1.clear();
            lcd_1.print("Left clear");
            lcd_1.clear();
            lcd_1.print("Car rotating left");
            servo_13.write(90);
            digitalWrite(A1, LOW);
            digitalWrite(A2, HIGH);
            digitalWrite(1, LOW);
            digitalWrite(2, HIGH);
            digitalWrite(3, HIGH);
            digitalWrite(4, LOW);
            analogWrite(5, 150);
            analogWrite(6, 150);
            delay(2000); // Wait for 2000 millisecond(s)
            digitalWrite(1, HIGH);
            digitalWrite(2, LOW);
            digitalWrite(3, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(A1, LOW);
            digitalWrite(A2, LOW);
            lcd_1.clear();
            lcd_1.print("Engine = ONN");
            lcd_1.setCursor(0, 1);
            lcd_1.print("Speed = 150");
          }
          // if left unclear
          if (udsf < 200) {
            lcd_1.setCursor(0, 0);
            lcd_1.clear();
            lcd_1.print("all side blocked");
            servo_13.write(90);
            // reverse
            lcd_1.clear();
            lcd_1.print("Car reversing");
            digitalWrite(A1, HIGH);
            digitalWrite(A2, HIGH);
            digitalWrite(1, LOW);
            digitalWrite(2, HIGH);
            digitalWrite(3, LOW);
            digitalWrite(4, HIGH);
            analogWrite(5, 150);
            analogWrite(6, 150);
            while (!(udsbl > 200 || (udsbr > 200 || udsb < 200))) {
              delay(500); // Wait for 500 millisecond(s)
            }
            analogWrite(5, 0);
            analogWrite(6, 0);
            if (udsbl > 200) {
              lcd_1.clear();
              lcd_1.print("Left clear");
              lcd_1.clear();
              lcd_1.print("Rotating left");
              digitalWrite(1, LOW);
              digitalWrite(2, HIGH);
              digitalWrite(3, HIGH);
              digitalWrite(4, LOW);
              analogWrite(5, 150);
              analogWrite(6, 150);
              delay(2000); // Wait for 2000 millisecond(s)
              digitalWrite(1, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, HIGH);
              digitalWrite(4, LOW);
            }
            if (udsbr > 200) {
              lcd_1.clear();
              lcd_1.print("Right clear");
              lcd_1.clear();
              lcd_1.print("Rotating right");
              digitalWrite(1, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, LOW);
              digitalWrite(4, HIGH);
              analogWrite(5, 150);
              analogWrite(6, 150);
              delay(2000); // Wait for 2000 millisecond(s)
              digitalWrite(1, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, HIGH);
              digitalWrite(4, LOW);
            }
            if (udsbl > 200 && udsbr > 200) {
              lcd_1.clear();
              lcd_1.print("Both side clear");
              lcd_1.clear();
              lcd_1.print("Rotating right");
              digitalWrite(1, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, LOW);
              digitalWrite(4, HIGH);
              analogWrite(5, 150);
              analogWrite(6, 150);
              delay(2000); // Wait for 2000 millisecond(s)
              digitalWrite(1, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, HIGH);
              digitalWrite(4, LOW);
            }
            if (udsb < 200) {
              lcd_1.clear();
              lcd_1.print("Car stoped");
              digitalWrite(1, HIGH);
              digitalWrite(2, LOW);
              digitalWrite(3, HIGH);
              digitalWrite(4, LOW);
              analogWrite(5, 0);
              analogWrite(6, 0);
            }
            digitalWrite(A1, LOW);
            digitalWrite(A2, LOW);
          }
        }
      }
    }
  }
}