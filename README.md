# SmartLock-ESP32

[TR] ESP32 ve MFRC522 RFID modülü kullanılarak geliştirilmiş, buzzer ve LED bildirimli akıllı kilit / erişim kontrol sistemi. Proje, hem ana kilit sistemini hem de kart UID numaralarını tespit etmek için kullanılan test kodunu içerir.

[EN] A smart lock / access control system developed using ESP32 and MFRC522 RFID module with buzzer and LED notifications. The project includes both the main lock system and a test script used to detect card UID numbers.

---

## 🚀 Proje Özellikleri / Features

### [TR] Türkçe
* **Erişim Kontrolü:** Tanımlı UID'ye sahip kartlar için erişim izni (Yeşil LED + Kısa Bip).
* **Güvenlik Logları:** Seri monitör üzerinden anlık durum takibi (Başarılı/Başarısız geçişler).
* **Kolay Kart Tanımlama:** Kartların UID numaralarını öğrenmek için özel test kodu.
* **Hata Bildirimi:** Yetkisiz kartlarda görsel ve sesli uyarı (Kırmızı LED + Uzun Bip).

### [EN] English
* **Access Control:** Access granted for predefined UID cards (Green LED + Short Beep).
* **Security Logs:** Real-time status tracking via serial monitor (Success/Fail transitions).
* **Easy Card Identification:** Dedicated test code to easily find card UID numbers.
* **Error Notification:** Visual and audible warning for unauthorized cards (Red LED + Long Beep).

---

## 🛠️ Donanım Bileşenleri / Hardware Components

* ESP32 Development Board
* MFRC522 RFID RC522 Module
* 1x Green LED (Yeşil LED)
* 1x Red LED (Kırmızı LED)
* 1x Buzzer
* 2x 220Ω Resistors (Direnç)
* Jumper Wires & Breadboard

---

## 📂 Dosya Yapısı / Repository Structure

* 📄 `rfid_system.ino` -> [TR] Ana erişim kontrol kodu. / [EN] Main access control code.
* 📄 `kart_id.ino` -> [TR] Kart ID'lerini okumak için test kodu. / [EN] Test code to scan card UIDs.

---

## 🛠️ Kurulum ve Kullanım / Installation & Usage

### 1️⃣ Kart UID Numaranızı Öğrenin / Find Your Card UID
1. `kart_id.ino` kodunu ESP32'nize yükleyin.
2. Arduino IDE Seri Monitörünü açın ve hızı **115200 Baud** olarak ayarlayın.
3. Kartınızı okutun ve ekranda görünen `HEX` kodlarını (örn: `57 97 D1 06`) not edin.

> 💡 *[TR] Seri monitörde 2 saniyede bir nokta (`.`) görüyorsanız ESP32 çalışıyor ancak kartı henüz okumamış demektir.*
> 💡 *[EN] If you see a dot (`.`) every 2 seconds on the serial monitor, it means ESP32 is running but hasn't read a card yet.*

### 2️⃣ Ana Kodu Yükleyin / Upload Main Code
1. `rfid_system.ino` kodunu açın.
2. Aşağıdaki satırı kendi kartınızın UID numaralarıyla güncelleyin:
   ```cpp
   byte dogruKartUID[] = {0x57, 0x97, 0xD1, 0x06}; // Kendi ID'nizi yazın / Enter your ID
