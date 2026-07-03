# KaravanOS - Akıllı Karavan Kontrol Sistemi 🚐💻

KaravanOS, ESP32 mikrodenetleyicisi tabanlı, karavanınızın temel yaşamsal verilerini (sıcaklık, nem, gaz, eğim) izlemenizi ve karavanınızdaki cihazları (inverter, su pompası vb.) yönetmenizi sağlayan gelişmiş bir Akıllı Karavan Kontrol sistemidir. Sistem, sensör verilerini gerçek zamanlı işleyerek hem güvenlik alarmları üretir hem de yerleşik web arayüzü sayesinde tüm kontrolü akıllı telefonunuza veya tabletinize taşır.

## 🌟 Temel Özellikler

* **Gerçek Zamanlı İzleme:** BME280 ile sıcaklık, nem ve basınç takibi.
* **Akıllı Dengeleme (Eğim Ölçer):** ADXL345 ivmeölçer ile karavanın X ve Y eksenlerindeki eğimini görerek kolay park ve dengeleme imkanı.
* **Gaz ve Yangın Güvenliği:** MQ-2 gaz sensörü ile LPG, duman veya karbonmonoksit kaçağı algılama ve sesli uyarı (Buzzer alarmı).
* **Cihaz Kontrolü:** Röleler üzerinden İnverter ve Su Pompası kontrolü. İnverter için zamanlayıcı (Timer) özelliği.
* **SD Kart Veri Kaydı (Datalogging):** Tüm sensör verilerini `log.csv` formatında SD karta kaydeder, geçmişe dönük sıcaklık trendlerini tutar.
* **Dosya Yöneticisi:** Web arayüzü üzerinden SD karttaki dosyaları listeleme, indirme, yükleme ve silme özellikleri.
* **Gün Sonu Raporları:** DS3231 RTC modülü entegrasyonu ile gün sonu kamp raporları (en yüksek/en düşük sıcaklık) oluşturma.
* **Kalibrasyon Yeteneği:** Sensör eğim (tilt), sıcaklık ofseti ve gaz eşik değerlerini web arayüzünden ayarlama.
* **Kablosuz Ağ ve mDNS (Local Host):** Dahili Access Point (Hotspot) olarak çalışabilir veya mevcut bir Wi-Fi ağına bağlanabilir. `karavan.local` adresi ile IP bilmeden cihaza erişim.
* **OTA Güncelleme:** Kabloya ihtiyaç duymadan Wi-Fi üzerinden yazılım güncelleyebilme.
* **Dinamik Web Arayüzü:** WebSocket, TailwindCSS ve Chart.js destekli hızlı, modern ve tepkisel web arayüzü.

---

## 🛠 Kullanılan Donanımlar (Bileşenler)

* **Mikrodenetleyici:** ESP32 (30-Pin versiyonu önerilir)
* **Hava Durumu Sensörü:** BME280 (I2C)
* **Eğim / İvme Sensörü:** ADXL345 (I2C) / GY-291
* **Gerçek Zamanlı Saat:** DS3231 RTC Modülü (I2C)
* **Hava Kalite / Gaz Sensörü:** MQ-2 Gaz Sensörü (Analog)
* **Hafıza:** MicroSD Kart Modülü (SPI)
* **Kontrol:** 2 Kanal 5V Röle Modülü (Active-LOW)
* **Sesli Uyarı:** Aktif veya Pasif Buzzer
* **Güç Kaynağı:** 5V Stabil Güç Kaynağı / DC-DC Çevirici (ESP32 ve röleleri beslemek için)

---

## 🔌 Pin Bağlantıları

ESP32 ile bileşenler arasındaki bağlantı şeması aşağıdaki gibidir:

| Bileşen / Sensör | ESP32 Pin | Bağlantı Türü | Açıklama |
| :--- | :--- | :--- | :--- |
| **BME280 / ADXL345 / RTC** | `GPIO 21` (SDA) | I2C | Tüm I2C cihazları paralel bağlanır. |
| **BME280 / ADXL345 / RTC** | `GPIO 22` (SCL) | I2C | Tüm I2C cihazları paralel bağlanır. |
| **SD Kart Modülü** | `GPIO 5` (CS) | SPI | Chip Select |
| **SD Kart Modülü** | `GPIO 23` (MOSI) | SPI | Standart SPI MOSI pini |
| **SD Kart Modülü** | `GPIO 19` (MISO) | SPI | Standart SPI MISO pini |
| **SD Kart Modülü** | `GPIO 18` (SCK) | SPI | Standart SPI SCK pini |
| **MQ-2 Gaz Sensörü** | `GPIO 34` | Analog Giriş | Sensörün A0 pinine bağlanır. |
| **İnverter Rölesi** | `GPIO 25` | Dijital Çıkış | Röle IN1 (Active-LOW) |
| **Pompa Rölesi** | `GPIO 26` | Dijital Çıkış | Röle IN2 (Active-LOW) |
| **Buzzer** | `GPIO 27` | PWM/Dijital | Sesli Uyarı Çıkışı |

> **Not:** Röle modülünüz `Active-LOW` (Düşük sinyalde tetiklenen) değilse, koddaki röle tetikleme mantığını tersine çevirmeniz gerekebilir.

---

## 📚 Gerekli Kütüphaneler

Projeyi derlemeden önce Arduino IDE'ye (veya PlatformIO) aşağıdaki kütüphaneleri yüklediğinizden emin olun:

1. `WiFiManager` (tzapu)
2. `ESPAsyncWebServer` (me-no-dev)
3. `AsyncTCP` (me-no-dev)
4. `ArduinoJson` (Benoit Blanchon)
5. `Adafruit BME280 Library` (Adafruit)
6. `Adafruit ADXL345` (Adafruit)
7. `Adafruit Unified Sensor` (Adafruit)
8. `RTClib` (Adafruit)

---

## 💾 SD Kart Hazırlığı (ÖNEMLİ)

Projenin web arayüzünün (Tailwind CSS) düzgün çalışabilmesi için gerekli stil dosyalarının SD kartta bulunması gerekmektedir.
1. Proje dizininde yer alan `tailwindcss.js` dosyasını bilgisayarınız üzerinden SD kartın **ana dizinine (root)** kopyalayın.
2. Hazırladığınız SD kartı ESP32 üzerindeki MicroSD modülüne takın.

---

## 🚀 Kurulum ve Yükleme (Arduino IDE)

1. Projeyi bilgisayarınıza indirin veya `git clone` ile çekin.
2. `KaravanOS.ino` dosyasını Arduino IDE ile açın.
3. Kütüphane yöneticisinden gerekli kütüphaneleri kurun.
4. Geliştirme kartı olarak **"ESP32 Dev Module"** seçin.
5. Partition Scheme ayarını (Araçlar -> Partition Scheme) **"Huge APP (3MB No OTA/1MB SPIFFS)"** veya web sunucu dosyaları büyük olduğu için yeterli alan sağlayan bir şemaya ayarlayın (OTA kullanacaksanız **"Default 4MB with spiffs"** seçebilirsiniz).
6. Derleyin ve ESP32'ye yükleyin (Upload).
7. Yükleme tamamlandıktan sonra Serial Monitörü açarak sistemin hazır olup olmadığını kontrol edin (Baud Rate: `115200`).

---

## 📱 Kullanım Kılavuzu

1. **Bağlantı Kurma:** ESP32 ilk açıldığında `Hotomobil Ronin XL` adında bir Wi-Fi ağı yayacaktır.
2. **Wi-Fi Şifresi:** Varsayılan Wi-Fi şifresi `12345678`'dir.
3. **Web Arayüzüne Erişim:** Ağa bağlandıktan sonra tarayıcınızdan `http://192.168.4.1` veya mDNS adresi olan `http://karavan.local` adresine giderek kontrol paneline ulaşabilirsiniz.
4. **Harici Ağa Bağlanma (İsteğe Bağlı):** Arayüzdeki Wi-Fi ayarları kısmından karavanınızın veya telefonunuzun internetine (Hotspot) ESP32'yi bağlayabilirsiniz.
5. **Eğim Kalibrasyonu:** Karavanı terazideyken (düz zeminde) web arayüzündeki kalibrasyon ayarlarına girip eğim sensörünü sıfırlayabilirsiniz.
6. **Gaz Eşik Ayarı:** MQ-2 sensörünün yanlış alarm vermemesi için gaz eşik (threshold) değerini web arayüzünden karavanın ortamına göre kalibre edebilirsiniz.

## 🤝 Katkıda Bulunma

Bu proje açık kaynak kodludur. Hata bildirimleri (Issues) ve geliştirme talepleri (Pull Requests) her zaman kabul edilir! Geliştirmeler için bir dal (branch) oluşturun ve pull request gönderin.

## 📝 Lisans

Bu proje MIT Lisansı altında lisanslanmıştır. Dilediğiniz gibi kullanabilir ve geliştirebilirsiniz.
