# PRC - Test Joystick & Motor ESP32

Kumpulan sketch pengujian awal untuk robot: sisi **input** (joystick) dan sisi **output** (driver motor L298N). Kedua sketch berdiri sendiri dan dijalankan bergantian via Arduino IDE.

## File

| File | Fungsi |
|------|--------|
| `test_joystick_esp32_v1.ino` | Baca 2 sumbu joystick via ADC ESP32, tampilkan arah di Serial Monitor |
| `test_motor_L298N_random.ino` | Test driver L298N + 2 motor DC dengan perintah acak Maju/Mundur/Berhenti |

## 1. Test Joystick (`test_joystick_esp32_v1.ino`)

### Hardware
- Board: ESP32
- Joystick 1 sumbu Y -> GPIO 35
- Joystick 2 sumbu X -> GPIO 34
- Baud: 115200

### Logika
- ADC 12-bit (0-4095), `CENTER = 2048`, `DEADZONE = 300`
- Rentang `TENGAH`: 1748-2348
- Arah dibalik:
  - `JOY1_Y > 2348` = BAWAH, `< 1748` = ATAS
  - `JOY2_X > 2348` = KIRI, `< 1748` = KANAN
- Print tiap 100 ms

### Contoh output
```
JOY1 Y: 1890 -> TENGAH    |    JOY2 X: 4095 -> KIRI
JOY1 Y: 500 -> ATAS    |    JOY2 X: 1900 -> TENGAH
```

### Keterbatasan
- Hanya 2 dari 4 sumbu dibaca
- `CENTER` masih asumsi 2048, perlu kalibrasi per joystick
- Tanpa filter (ADC ESP32 noisy)
- `pinMode(..., INPUT)` tidak wajib untuk `analogRead()`

## 2. Test Motor L298N (`test_motor_L298N_random.ino`)

### Hardware
| L298N | ESP32 |
|-------|-------|
| ENA | GPIO 14 |
| IN1 | GPIO 27 |
| IN2 | GPIO 26 |
| IN3 | GPIO 25 |
| IN4 | GPIO 33 |
| ENB | GPIO 32 |

- Motor A (kiri): ENA + IN1 + IN2
- Motor B (kanan): ENB + IN3 + IN4
- Kecepatan: `setSpeed(255)` (maksimal)

### Dependensi
- Library Arduino: `L298N` (install via Library Manager sebelum compile)

### Logika
- Tiap 2 detik random per motor: `0 = BERHENTI, 1 = MAJU, 2 = MUNDUR`
- Status dicetak ke Serial Monitor (115200)

### Perhatian
- Gerakan acak, tidak terduga. Uji dengan roda menggantung / sasis diganjal.
- `randomSeed(analogRead(0))` sebaiknya diganti pin ADC nganggur (mis. 36/39) untuk seed lebih baik.
- Belum ada kontrol kecepatan variabel / belok.

## Cara pakai

1. Buka salah satu `.ino` di Arduino IDE, pilih board ESP32 + port COM.
2. Untuk motor: install library `L298N` dulu (Sketch > Include Library > Manage Libraries).
3. Upload, buka Serial Monitor 115200.
4. Uji joystick dulu sampai arah benar, baru uji motor.

## Rencana lanjut
- Gabungkan: `JOY1_Y` untuk maju/mundur + `JOY2_X` untuk belok, `map()` ke PWM 0-255 untuk `motorA`/`motorB` (differential drive).
