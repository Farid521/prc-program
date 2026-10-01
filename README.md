# PRC - Test Joystick & Motor ESP32

Dua program test untuk robot berbasis ESP32:

1. **Test Joystick** - membaca gerakan stik joystick
2. **Test Motor** - menggerakkan 2 motor DC lewat driver L298N

Kedua program dijalankan terpisah lewat Arduino IDE.

---

## File

| File | Fungsi |
|------|--------|
| `test_joystick_esp32_v1.ino` | Membaca arah joystick (atas/bawah/kiri/kanan) |
| `test_motor_L298N_random.ino` | Menggerakkan motor secara acak (maju/mundur/berhenti) |

---

## 1. Test Joystick

### Koneksi

```
Joystick 1 (sumbu Y)  ->  GPIO 35
Joystick 2 (sumbu X)  ->  GPIO 34
```

### Cara kerja

- Nilai ADC ESP32: 0 - 4095, posisi tengah = 2048
- Ada **deadzone** 300, jadi nilai 1748 - 2348 dianggap **TENGAH** (tidak bergerak)
- Arah sengaja dibalik:
  - Joystick 1: nilai > 2348 = **BAWAH**, nilai < 1748 = **ATAS**
  - Joystick 2: nilai > 2348 = **KIRI**, nilai < 1748 = **KANAN**
- Hasil dicetak ke Serial Monitor setiap 0,1 detik

### Contoh output

```
JOY1 Y: 1890 -> TENGAH    |    JOY2 X: 4095 -> KIRI
JOY1 Y: 500  -> ATAS      |    JOY2 X: 1900 -> TENGAH
```

### Batasan

- Baru baca 2 arah saja (Y dan X), belum lengkap
- Nilai tengah 2048 masih perkiraan, tiap joystick bisa beda
- Belum ada filter, kadang angkanya lompat-lompat

---

## 2. Test Motor L298N

### Koneksi

```
L298N Pin    ->    ESP32 Pin
--------------------------------
ENA          ->    GPIO 14
IN1          ->    GPIO 27
IN2          ->    GPIO 26
IN3          ->    GPIO 25
IN4          ->    GPIO 33
ENB          ->    GPIO 32
```

- **Motor A** (kiri): pakai ENA, IN1, IN2
- **Motor B** (kanan): pakai ENB, IN3, IN4
- Kecepatan: 255 (maksimal)

### Perlu install library dulu

Program ini butuh library **L298N**. Cara install di Arduino IDE:

```
Sketch -> Include Library -> Manage Libraries
-> cari "L298N" -> Install
```

Kalau belum diinstall, program tidak akan bisa di-compile.

### Cara kerja

- Setiap **2 detik**, program memilih acak untuk tiap motor:
  - `0` = BERHENTI
  - `1` = MAJU
  - `2` = MUNDUR
- Status tiap motor dicetak ke Serial Monitor

### Contoh output

```
--- Perintah Baru ---
Motor A : BERHENTI
Motor B : MAJU
---------------------
```

### PERHATIAN

- Gerakan motor **acak dan tidak terduga**
- Uji dengan roda menggantung atau sasis diganjal, **jangan di lantai**

---

## Cara Pakai

1. Buka file `.ino` di Arduino IDE
2. Pilih board **ESP32** dan port COM
3. Kalau test motor: install library `L298N` dulu (lihat di atas)
4. Klik Upload
5. Buka Serial Monitor, set **baud rate 115200**
6. Test joystick dulu sampai arahnya benar, baru test motor

---

## Rencana Lanjut

Gabungkan kedua program jadi satu:

- Joystick Y -> maju / mundur
- Joystick X -> belok kiri / kanan
- Nilai joystick diubah jadi kecepatan motor (0-255)
