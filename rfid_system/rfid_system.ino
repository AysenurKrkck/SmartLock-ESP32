#include <SPI.h>       // SPI iletişimi kütüphanesi / SPI communication library
#include <MFRC522.h>   // MFRC522 RFID modülü kütüphanesi / MFRC522 RFID module library

// Pin Tanımlamaları / Pin Definitions
#define SS_PIN     5
#define RST_PIN    22
#define YESIL_LED  12
#define KIRMIZI_LED 14
#define BUZZER     27

// RFID nesnesi oluşturuluyor / Creating RFID instance
MFRC522 rfid(SS_PIN, RST_PIN);

// ⚠️ BURAYI KENDİ KARTININ UID NUMARALARIYLA DEĞİŞTİR! 
// ⚠️ REPLACE THIS WITH YOUR OWN CARD'S UID NUMBERS!
byte dogruKartUID[] = {0x57, 0x97, 0xD1, 0x06}; 

void setup() {
  // Seri haberleşme başlatılıyor / Initializing serial communication
  Serial.begin(115200);
  
  // SPI ve RFID başlatılıyor / Initializing SPI and RFID
  SPI.begin();
  rfid.PCD_Init();

  // Pin modları çıkış olarak ayarlanıyor / Setting pin modes as OUTPUT
  pinMode(YESIL_LED, OUTPUT);
  pinMode(KIRMIZI_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Başlangıçta tüm bileşenleri kapat / Turn off all components at startup
  digitalWrite(YESIL_LED, LOW);
  digitalWrite(KIRMIZI_LED, LOW);
  digitalWrite(BUZZER, LOW);
  
  Serial.println("Sistem Hazir. Kart Bekleniyor... / System Ready. Waiting for card...");
}

void loop() {
  // Yeni bir kart okutulmadıysa veya okunamadıysa döngüden çık
  // If a new card is not present or cannot be read, exit the loop
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  bool kartDogruMu = true;

  // Okunan kart ile doğru kartı karşılaştır 
  // Compare the scanned card UID with the correct card UID
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] != dogruKartUID[i]) {
      kartDogruMu = false; // Kart eşleşmedi / Card mismatch
      break;
    }
  }

  // Erişim Kontrolü / Access Control
  if (kartDogruMu) {
    // Erişim Onaylandı Durumu / Access Granted Status
    Serial.println("Erisim Onaylandi! Hos geldiniz. / Access Granted! Welcome.");
    digitalWrite(YESIL_LED, HIGH);
    
    // Buzzer kısa bip sesi / Short buzzer beep
    digitalWrite(BUZZER, HIGH); 
    delay(150); 
    digitalWrite(BUZZER, LOW);
    
    delay(2000); // 2 saniye boyunca yeşil ışık yansın / Keep green LED on for 2 seconds
    digitalWrite(YESIL_LED, LOW);
  } 
  else {
    // Erişim Reddedildi Durumu / Access Denied Status
    Serial.println("Erisim Reddedildi! Hatali Kart. / Access Denied! Invalid Card.");
    digitalWrite(KIRMIZI_LED, HIGH);
    
    // Buzzer hata sesi (Uzun) / Long buzzer beep for error
    digitalWrite(BUZZER, HIGH); 
    delay(500); 
    digitalWrite(BUZZER, LOW);
    
    delay(1500); // 1.5 saniye kırmızı ışık yansın / Keep red LED on for 1.5 seconds
    digitalWrite(KIRMIZI_LED, LOW);
  }

  // Kart okumayı sonlandır (Aynı kartın üst üste okunmasını engeller)
  // Halt PICC (Prevents continuous reading of the same card)
  rfid.PICC_HaltA();
}
