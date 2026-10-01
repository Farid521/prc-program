const int JOY1_Y = 35;
const int JOY2_X = 34;

const int DEADZONE = 300;
const int CENTER = 2048;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(JOY1_Y, INPUT);
  pinMode(JOY2_X, INPUT);

  Serial.println();
  Serial.println("=================================");
  Serial.println("       JOYSTICK TEST ESP32");
  Serial.println("=================================");
  Serial.println("GPIO 35 = Y Joystick 1");
  Serial.println("GPIO 34 = X Joystick 2");
  Serial.println("Arah sudah dibalik");
  Serial.println();
}

void loop() {
  int y1 = analogRead(JOY1_Y);
  int x2 = analogRead(JOY2_X);

  // =========================
  // JOYSTICK 1 - Y
  // =========================
  Serial.print("JOY1 Y: ");
  Serial.print(y1);
  Serial.print(" -> ");

  // Dibalik: nilai tinggi = BAWAH
  //          nilai rendah = ATAS
  if (y1 > CENTER + DEADZONE) {
    Serial.print("BAWAH");
  }
  else if (y1 < CENTER - DEADZONE) {
    Serial.print("ATAS");
  }
  else {
    Serial.print("TENGAH");
  }

  // =========================
  // JOYSTICK 2 - X
  // =========================
  Serial.print("    |    JOY2 X: ");
  Serial.print(x2);
  Serial.print(" -> ");

  // Dibalik: nilai tinggi = KIRI
  //          nilai rendah = KANAN
  if (x2 > CENTER + DEADZONE) {
    Serial.println("KIRI");
  }
  else if (x2 < CENTER - DEADZONE) {
    Serial.println("KANAN");
  }
  else {
    Serial.println("TENGAH");
  }

  delay(100);
}
