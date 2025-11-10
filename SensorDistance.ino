#include <Wire.h>
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define echoPin 2
#define trigPin 3

// Pin untuk traffic light
#define redPin 4
#define yellowPin 5
#define greenPin 6

// Pin untuk buzzer
#define buzzerPin 7

// Threshold jarak
#define CLOSE_DISTANCE 8
#define FAR_DISTANCE 25  

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Set pin traffic light sebagai OUTPUT
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  // Set pin buzzer sebagai OUTPUT
  pinMode(buzzerPin, OUTPUT);
  
  // Matikan semua LED awal
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  noTone(buzzerPin);  // Matikan buzzer
  
  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  
  Serial.begin(9600);
  Serial.println("Ultrasonic Sensor + Traffic Light + Buzzer");
  delay(2000);
}

void beepBuzzer() {
  // Fungsi untuk bunyi beep-beep dengan tone (lebih nyaring)
  tone(buzzerPin, 2000, 300);  // Frekuensi 2000Hz, durasi 300ms
  delay(400);  // Total delay termasuk bunyi
  tone(buzzerPin, 2500, 200);  // Frekuensi 2500Hz, durasi 200ms
  delay(300);
}

void alertBuzzer() {
  // Alternatif: bunyi alarm seperti sirine
  for (int i = 0; i < 2; i++) {
    tone(buzzerPin, 1500, 150);
    delay(200);
    tone(buzzerPin, 2000, 150);
    delay(200);
  }
}

void policeSiren() {
  // Efek sirine polisi
  for (int i = 0; i < 3; i++) {
    for (int freq = 1000; freq <= 2000; freq += 50) {
      tone(buzzerPin, freq, 10);
      delay(5);
    }
    delay(100);
    for (int freq = 2000; freq >= 1000; freq -= 50) {
      tone(buzzerPin, freq, 10);
      delay(5);
    }
    delay(100);
  }
}

void loop() {
  // Baca jarak dari ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  // Tampilkan di Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Tampilkan di LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");
  
  // LOGIC TRAFFIC LIGHT berdasarkan jarak
  if (distance < CLOSE_DISTANCE) {
    // JARAK DEKAT (< 10 cm) = MERAH + BUZZER
    digitalWrite(redPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
    Serial.println("Status: STOP (Red) - BUZZER ON");
    
    // Pilih salah satu efek suara:
    beepBuzzer();        // Beep-beep tinggi
    // alertBuzzer();     // Alternatif: alarm pendek
    // policeSiren();     // Alternatif: sirine polisi
    
  } else if (distance > FAR_DISTANCE) {
    // JARAK JAUH (> 25 cm) = HIJAU
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, HIGH);
    noTone(buzzerPin);  // Pastikan buzzer mati
    Serial.println("Status: GO (Green)");
    delay(500);
    
  } else {
    // JARAK MENENGAH (10-25 cm) = KUNING
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(greenPin, LOW);
    noTone(buzzerPin);  // Pastikan buzzer mati
    Serial.println("Status: CAUTION (Yellow)");
    delay(500);
  }
}