# Distance Detector - IoT Project

![IoT Project Preview](https://github.com/dndyprd/distance-detector/blob/main/iot.jpeg)

## 📖 Deskripsi Project

Distance Detector adalah project IoT yang menggunakan sensor ultrasonik untuk mendeteksi jarak objek dan memberikan visual feedback melalui traffic light serta audio alert melalui buzzer. Project ini cocok untuk aplikasi parkir kendaraan, sistem peringatan objek, atau sebagai alat bantu navigasi.

## 🚀 Fitur

- **📏 Deteksi Jarak Real-time** - Menggunakan sensor HC-SR04
- **🚦 Traffic Light System** - LED merah, kuning, hijau berdasarkan jarak
- **🔊 Audio Alert** - Buzzer aktif saat jarak terlalu dekat
- **📺 LCD Display** - Menampilkan informasi jarak secara visual
- **📊 Serial Monitoring** - Data real-time melalui Serial Monitor

## 🛠️ Komponen yang Digunakan

| Komponen | Jumlah | Keterangan |
|----------|---------|------------|
| Arduino Uno | 1 | Main controller |
| HC-SR04 Ultrasonic Sensor | 1 | Sensor jarak |
| LCD I2C 16x2 | 1 | Display informasi |
| Traffic Light Module | 1 | LED merah, kuning, hijau |
| Buzzer KY-006 | 1 | Audio alert |
| Breadboard | 1 | Tempat penyolderan |
| Resistor 220Ω | 3 | Untuk LED traffic light |
| Kabel Jumper | - | Koneksi antar komponen |

## 🔌 Wiring Diagram

```
ARDUINO UNO CONNECTIONS:

SENSOR ULTRASONIC:
- VCC  → 5V
- TRIG → Pin 3
- ECHO → Pin 2
- GND  → GND

LCD I2C:
- VCC → 5V
- GND → GND
- SDA → A4
- SCL → A5

TRAFFIC LIGHT:
- RED    → Pin 4 (+ resistor 220Ω)
- YELLOW → Pin 5 (+ resistor 220Ω)
- GREEN  → Pin 6 (+ resistor 220Ω)
- GND    → GND

BUZZER KY-006:
- S (Signal) → Pin 7
- - (Ground) → GND
- Pin tengah  → Tidak terhubung
```

## 💻 Program Logic

### Threshold Jarak:
- **🟢 HIJAU** (GO): > 25 cm
- **🟡 KUNING** (CAUTION): 10 - 25 cm  
- **🔴 MERAH** (STOP): < 10 cm + Buzzer aktif

### Fungsi Buzzer:
- Bunyi "beep-beep" ketika status MERAH
- Menggunakan frekuensi tinggi untuk suara yang nyaring
- Dapat dikustomisasi dengan berbagai efek suara

## 📋 Instalasi dan Penggunaan

1. **Clone Repository**
   ```bash
   git clone https://github.com/dndyprd/distance-detector.git
   cd distance-detector
   ```

2. **Buka di Arduino IDE**
   - Buka file `distance_detector.ino`
   - Install library yang diperlukan:
     - `LiquidCrystal_I2C` by Frank de Brabander
     - `Wire` (built-in Arduino library)

3. **Upload ke Arduino**
   - Sambungkan Arduino Uno via USB
   - Pilih board dan port yang sesuai
   - Upload program

4. **Testing**
   - Buka Serial Monitor (9600 baud)
   - Lihat output di LCD dan traffic light
   - Test dengan objek pada berbagai jarak

## 🎛️ Konfigurasi

### Mengubah Threshold Jarak:
```cpp
#define CLOSE_DISTANCE 10    // Ubah nilai untuk merah
#define FAR_DISTANCE 25      // Ubah nilai untuk hijau
```

### Mengubah Efek Suara Buzzer:
Ganti pemanggilan fungsi di bagian `// LOGIC TRAFFIC LIGHT`:
```cpp
// Pilih salah satu:
beepBuzzer();        // Beep-beep standard
// alertBuzzer();     // Alarm alternating
// policeSiren();     // Efek sirine
```

## 🔧 Troubleshooting

1. **LCD Tidak Menyala**
   - Cek alamat I2C (0x27 atau 0x3F)
   - Pastikan koneksi SDA dan SCL benar

2. **Buzzer Tidak Bunyi**
   - Pastikan pin S terhubung ke pin digital
   - Coba ganti ke pin PWM (3, 5, 6, 9, 10, 11)

3. **Sensor Tidak Akurat**
   - Pastikan objek tidak menyerap suara
   - Beri delay yang cukup antara pembacaan

---
