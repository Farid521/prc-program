#include <L298N.h>

// Definisi Pin berdasarkan wiring diagram
const int ENA = 14; 
const int IN1 = 27; 
const int IN2 = 26; 
const int IN3 = 25; 
const int IN4 = 33; 
const int ENB = 32; 

// Inisialisasi instance motor (Pin Enable, Pin IN_A, Pin IN_B)
L298N motorA(ENA, IN1, IN2);
L298N motorB(ENB, IN3, IN4);

void setup() {
  Serial.begin(115200);
  
  // Mengatur kecepatan maksimal (0 - 255)
  motorA.setSpeed(255);
  motorB.setSpeed(255);
  
  // Seed untuk generator angka acak
  randomSeed(analogRead(0));
  
  Serial.println("Memulai Testing Motor Driver dengan Library L298N...");
}

void loop() {
  // Menghasilkan nilai acak: 0 (Berhenti), 1 (Maju), 2 (Mundur)
  int stateMotorA = random(0, 3);
  int stateMotorB = random(0, 3);

  Serial.println("--- Perintah Baru ---");
  
  // Logika kontrol Motor A (Kiri)
  if (stateMotorA == 0) {
    motorA.stop();
    Serial.println("Motor A : BERHENTI");
  } else if (stateMotorA == 1) {
    motorA.forward();
    Serial.println("Motor A : MAJU");
  } else {
    motorA.backward();
    Serial.println("Motor A : MUNDUR");
  }

  // Logika kontrol Motor B (Kanan)
  if (stateMotorB == 0) {
    motorB.stop();
    Serial.println("Motor B : BERHENTI");
  } else if (stateMotorB == 1) {
    motorB.forward();
    Serial.println("Motor B : MAJU");
  } else {
    motorB.backward();
    Serial.println("Motor B : MUNDUR");
  }

  Serial.println("---------------------\n");
  
  // Tahan pergerakan selama 2 detik sebelum mengacak perintah lagi
  delay(2000); 
}