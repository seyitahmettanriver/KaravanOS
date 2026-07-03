/*
 * KARAVAN OS - Akıllı Karavan Kontrol Sistemi
 * Yazar: Antigravity
 * 
 * GEREKLİ KÜTÜPHANELER:
 * 1. WiFiManager by tzapu
 * 2. ESPAsyncWebServer by me-no-dev
 * 3. AsyncTCP by me-no-dev
 * 4. ArduinoJson by Benoit Blanchon
 * 5. Adafruit BME280 Library
 * 6. Adafruit ADXL345 (ADXL345 uyumlu)
 * 7. Adafruit Unified Sensor
 */

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Preferences.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_ADXL345_U.h>
#include <RTClib.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <Preferences.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_ADXL345_U.h>
#include <RTClib.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <ESPmDNS.h>
#include <Update.h>

// PIN TANIMLAMALARI (ESP32 30-Pin)
#define PIN_MQ2         34
#define PIN_BUZZER      27
#define PIN_SDA         21
#define PIN_SCL         22
#define PIN_RELAY_INV   25
#define PIN_RELAY_PUMP  26
#define PIN_SD_CS       5



#define BUZZ_FREQ_DEFAULT 1000  // başlangıç frekansı (Hz)
#define USE_ACTIVE_BUZZER false // Aktif (kendinden bipleyen) buzzer kullanıyorsanız true yapın.

bool is_buzzer_on = false;

// Ton çal yardımcı fonksiyonları (ESP32 Core 3.0.0+ Uyumlu)
void buzzTone(uint32_t freq) {
    if(freq == 0) {
        if (!is_buzzer_on) return; // Zaten kapalıysa işlem yapma (tık sesini önler)
        if (USE_ACTIVE_BUZZER) {
            digitalWrite(PIN_BUZZER, LOW);
        } else {
            ledcDetach(PIN_BUZZER); pinMode(PIN_BUZZER, OUTPUT); digitalWrite(PIN_BUZZER, LOW);
        }
        is_buzzer_on = false;
    } else {
        if (is_buzzer_on) return; // Zaten çalıyorsa işlem yapma
        if (USE_ACTIVE_BUZZER) {
            digitalWrite(PIN_BUZZER, HIGH);
        } else {
            // İstenen frekansta (örn: 2800 Hz) %50 duty cycle ile ton üretmek için tekrar bağla
            ledcAttach(PIN_BUZZER, freq, 8); ledcWriteTone(PIN_BUZZER, freq);
        }
        is_buzzer_on = true;
    }
}

void buzzOff() { 
    buzzTone(0); 
}

// Nesneler
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
Preferences preferences;
String last_scan_json = "";
bool shouldRebootSystem = false;
Adafruit_BME280 bme;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
RTC_DS3231 rtc;

// Gün Sonu Raporu Takip Değişkenleri
float daily_min_temp = 100.0;
float daily_max_temp = -100.0;
int last_day = -1;
String last_report_msg = "";

// Kalibrasyon ve Durum Değişkenleri
float x_offset = 0.0;
float y_offset = 0.0;
float t_offset = 0.0;
float h_offset = 0.0;
int mq2_thresh = 2000;
bool mq2_en = true;
bool inv_state = false;
unsigned long inv_timer_end_ms = 0;
bool pump_state = false;

String ap_ssid = "Hotomobil Ronin XL";
String ap_pass = "12345678";
String mdns_name = "karavan";

// Anlık Veriler
float current_voltage = 0.0;
float current_pressure = 1013.0;
float current_temp = 0.0;
float current_hum = 0.0;
float current_x = 0.0;
float current_y = 0.0;
int current_gas = 0;
bool alarm_active = false;

// Donanım Durumları
bool status_bme = false;
bool status_adxl = false;
bool status_sd = false;
bool status_rtc = false;

// Hava Durumu / Geçmiş Veriler
int weather_forecast = 2; // Başlangıçta 2 (Stabil/Durgun) kabul et
float last_pressure_read = 0.0;
#define HISTORY_SIZE 72
float temp_history[HISTORY_SIZE];
int history_idx = 0;
int history_count = 0;

// Zamanlayıcılar
unsigned long last_ws_update = 0;
unsigned long last_bme_update = 0;
unsigned long last_sd_update = 0;
unsigned long mute_until = 0;
unsigned long chime_override_until = 0;

// WEB ARAYÜZÜ (HTML/CSS/JS) - Moved to WebPage.h
#include "WebPage.h"


// Web Socket Gelen Mesaj İşleyici
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        if (last_report_msg != "") {
            StaticJsonDocument<256> rdoc;
            rdoc["syslog"] = true;
            rdoc["msg"] = last_report_msg;
            rdoc["type"] = "report";
            String msg;
            serializeJson(rdoc, msg);
            client->text(msg);
        }
    } else if (type == WS_EVT_DATA) {
        AwsFrameInfo *info = (AwsFrameInfo*)arg;
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
            data[len] = 0;
            StaticJsonDocument<256> doc;
            DeserializationError err = deserializeJson(doc, (char*)data);
            if (!err) {
                const char* cmd = doc["cmd"];
                if (strcmp(cmd, "inv") == 0) {
                    inv_state = doc["val"];
                    digitalWrite(PIN_RELAY_INV, inv_state ? LOW : HIGH); // Active-LOW
                    inv_timer_end_ms = 0; // Always clear timer when manual inv command received
                } else if (strcmp(cmd, "inv_timer") == 0) {
                    int minutes = doc["val"];
                    if (minutes > 0) {
                        inv_state = true;
                        digitalWrite(PIN_RELAY_INV, LOW); // Active-LOW
                        inv_timer_end_ms = millis() + (minutes * 60000UL);
                    } else {
                        inv_timer_end_ms = 0;
                        inv_state = false;
                        digitalWrite(PIN_RELAY_INV, HIGH); // Active-LOW
                    }
                } else if (strcmp(cmd, "pump") == 0) {
                    pump_state = doc["val"];
                    digitalWrite(PIN_RELAY_PUMP, pump_state ? LOW : HIGH); // Active-LOW
                } else if (strcmp(cmd, "reboot") == 0) {
                    shouldRebootSystem = true;
                } else if (strcmp(cmd, "sync_time") == 0) {
                    uint32_t epoch = doc["val"];
                    if (status_rtc) {
                        rtc.adjust(DateTime(epoch));
                        Serial.println("RTC saati telefon ile senkronize edildi!");
                    }
                } else if (strcmp(cmd, "cal") == 0) {
                    const char* cal_type = doc["type"];
                    if (strcmp(cal_type, "tilt") == 0) {
                        x_offset = current_x + x_offset; // Ham okuma
                        y_offset = current_y + y_offset;
                        preferences.putFloat("x_offset", x_offset);
                        preferences.putFloat("y_offset", y_offset);
                        
                        // Relaxing success chime
                        chime_override_until = millis() + 250;
                        buzzTone(1500); delay(80);
                        buzzTone(2000); delay(120);
                        buzzOff();
                    } else if (strcmp(cal_type, "t") == 0) {
                        t_offset = doc["val"];
                        preferences.putFloat("t_offset", t_offset);
                    } else if (strcmp(cal_type, "g") == 0) {
                        mq2_thresh = doc["val"];
                        preferences.putInt("mq2_thresh", mq2_thresh);
                    } else if (strcmp(cal_type, "gen") == 0) {
                        mq2_en = (doc["val"] == 1);
                        preferences.putBool("mq2_en", mq2_en);
                        if(!mq2_en) {
                            alarm_active = false;
                            buzzOff();
                        }
                    }
                } else if (strcmp(cmd, "mute") == 0) {
                    mute_until = millis() + (5 * 60 * 1000); // 5 dakika sustur
                    buzzOff();
                } else if (strcmp(cmd, "set_wifi") == 0) {
                    const char* n_ssid = doc["ssid"];
                    const char* n_pass = doc["pass"];
                    const char* n_mdns = doc["mdns"];
                    
                    if (n_ssid) preferences.putString("ap_ssid", String(n_ssid));
                    if (n_pass) preferences.putString("ap_pass", String(n_pass));
                    if (n_mdns) preferences.putString("mdns_name", String(n_mdns));
                    
                    doc.clear();
                    doc["status"] = "restarting";
                    String resp; serializeJson(doc, resp);
                    client->text(resp);
                    
                    delay(500);
                    ESP.restart();
                } else if (strcmp(cmd, "scan_wifi") == 0) {
                    last_scan_json = "";
                    
                    // ESP32 Bug Fix: Eğer STA bağlı değilse ve bağlanmaya çalışıyorsa tarama 0 dönebilir.
                    // Taramanın sağlıklı çalışması için geçici disconnect atıyoruz (şifreyi silmez).
                    if (WiFi.status() != WL_CONNECTED) {
                        WiFi.disconnect(false);
                        delay(50);
                    }
                    
                    WiFi.scanNetworks(true); // Asenkron tarama baslat
                    doc.clear();
                    doc["status"] = "scanning";
                    String resp; serializeJson(doc, resp);
                    client->text(resp);
                } else if (strcmp(cmd, "get_scan") == 0) {
                    if (last_scan_json.length() > 0) {
                        client->text(last_scan_json);
                    }
                } else if (strcmp(cmd, "connect_ext") == 0) {
                    const char* e_ssid = doc["ssid"];
                    const char* e_pass = doc["pass"];
                    if(e_ssid) preferences.putString("ext_ssid", String(e_ssid));
                    if(e_pass) preferences.putString("ext_pass", String(e_pass));
                    
                    WiFi.disconnect();
                    delay(100);
                    WiFi.begin(e_ssid, e_pass);
                    
                    doc.clear();
                    doc["status"] = "connecting";
                    String resp; serializeJson(doc, resp);
                    client->text(resp);
                } else if (strcmp(cmd, "disconnect_ext") == 0) {
                    preferences.remove("ext_ssid");
                    preferences.remove("ext_pass");
                    WiFi.disconnect();
                    delay(100);
                } else if (strcmp(cmd, "clear_log") == 0) {
                    if(SD.exists("/log.csv")) {
                        SD.remove("/log.csv");
                    }
                    File file = SD.open("/log.csv", FILE_WRITE);
                    if(file) {
                        file.println("Tarih-Saat,Sicaklik(C),Nem(%),Basinc(hPa),Gaz(ppm),Egim-X,Egim-Y,Inverter,Pompa,Alarm");
                        file.close();
                    }
                }
            }
        }
    }
}

// Tüm istemcilere güncel veriyi gönder
void notifyClients() {
    StaticJsonDocument<2048> doc;
    doc["v"] = current_voltage;
    doc["p"] = current_pressure;
    doc["t"] = current_temp;
    doc["h"] = current_hum;
    doc["x"] = current_x;
    doc["y"] = current_y;
    doc["g"] = current_gas;
    doc["al"] = alarm_active;
    doc["inv"] = inv_state;
    
    long inv_timer = 0;
    if (inv_timer_end_ms > 0) {
        inv_timer = (inv_timer_end_ms - millis()) / 1000;
        if (inv_timer < 0) inv_timer = 0;
    }
    doc["inv_timer"] = inv_timer;
    doc["p"] = current_pressure;
    doc["wf"] = weather_forecast;
    
    // Donanım Durumları
    doc["st_b"] = status_bme;
    doc["st_a"] = status_adxl;
    doc["st_s"] = status_sd;
    doc["st_r"] = status_rtc;
    doc["st_v"] = false;
    doc["st_g"] = (current_gas > 0);
    if (status_sd) {
        doc["sd_t"] = SD.totalBytes() / (1024.0 * 1024.0);
        doc["sd_u"] = SD.usedBytes() / (1024.0 * 1024.0);
    }
    if (status_rtc) {
        doc["epoch"] = rtc.now().unixtime();
    }
    
    // UI Ayarları Senkronizasyonu
    doc["pm"] = pump_state;
    doc["t_off"] = t_offset;
    doc["g_thr"] = mq2_thresh;
    doc["g_en"] = mq2_en;
    doc["ap_s"] = ap_ssid;
    doc["ap_p"] = ap_pass;
    doc["mdns"] = mdns_name;
    doc["ext_ip"] = WiFi.status() == WL_CONNECTED ? WiFi.localIP().toString() : "";
    doc["ext_ssid"] = WiFi.status() == WL_CONNECTED ? WiFi.SSID() : "";
    
    JsonArray t_arr = doc.createNestedArray("t_hist");
    for(int i=0; i<history_count; i++) {
        int idx = (history_idx - history_count + i + HISTORY_SIZE) % HISTORY_SIZE;
        t_arr.add(temp_history[idx]);
    }
    
    char buffer[1024];
    size_t len = serializeJson(doc, buffer);
    ws.textAll(buffer, len);
}
File uploadFile;

void listSDRecursiveStream(File dir, AsyncResponseStream *response, bool &first, String currentPath = "") {
    File file = dir.openNextFile();
    while(file) {
        String fname = file.name();
        
        String fullPath = fname;
        if(!fullPath.startsWith("/")) fullPath = "/" + fullPath;
        if(currentPath.length() > 0 && !fullPath.startsWith(currentPath)) {
            fullPath = currentPath + "/" + fname;
            fullPath.replace("//", "/");
        }
        
        // İşletim sistemi kalıntılarını ve gizli sistem dosyalarını yoksay (Windows/Mac)
        if(fullPath.indexOf("System Volume Information") >= 0 || 
           fullPath.indexOf("WPSettings.dat") >= 0 || 
           fullPath.indexOf("IndexerVolumeGuid") >= 0 || 
           fullPath.indexOf(".DS_Store") >= 0 || 
           fullPath.indexOf("__MACOSX") >= 0) {
            file.close();
            file = dir.openNextFile();
            continue;
        }
        
        if(!first) response->print(",");
        response->print("{\"name\":\"");
        response->print(fullPath);
        response->print("\",\"size\":");
        response->print(file.isDirectory() ? 0 : file.size());
        response->print(",\"isDir\":");
        response->print(file.isDirectory() ? "true" : "false");
        response->print("}");
        first = false;
        
        if (file.isDirectory()) {
            listSDRecursiveStream(file, response, first, fullPath);
        }
        file.close();
        file = dir.openNextFile();
    }
}

void setup() {
   
    Serial.begin(115200);

    analogReadResolution(12);          // ESP32 için 0-4095
    analogSetAttenuation(ADC_11db);    // 0-3.3V ölçüm aralığı
    
    // Pin Modları
    pinMode(PIN_MQ2, INPUT);
    pinMode(PIN_RELAY_INV, OUTPUT);
    pinMode(PIN_RELAY_PUMP, OUTPUT);
    
    // Röleleri güç geldiğinde daima KAPALI başlat (Active-LOW için HIGH)
    digitalWrite(PIN_RELAY_INV, HIGH);
    digitalWrite(PIN_RELAY_PUMP, HIGH);
    inv_state = false;
    pump_state = false;
    
    // BUZZER KURULUMU
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);
    
    if (!USE_ACTIVE_BUZZER) {
      ledcAttach(PIN_BUZZER, 2000, 8);
    }
    is_buzzer_on = true; // İlk kapatmayı zorlamak için
    buzzOff(); // Başlangıçta sessiz olduğundan emin ol
    
    digitalWrite(PIN_RELAY_PUMP, HIGH);
    
    // NVS'den Kayıtlı Ayarları Yükle
    preferences.begin("karavan", false);
    x_offset = preferences.getFloat("x_offset", 0.0);
    y_offset = preferences.getFloat("y_offset", 0.0);
    t_offset = preferences.getFloat("t_offset", 0.0);
    h_offset = preferences.getFloat("h_offset", 0.0);
    mq2_thresh = preferences.getInt("mq2_thresh", 2000);
    mq2_en = preferences.getBool("mq2_en", true);
    
    daily_min_temp = preferences.getFloat("d_min", 100.0);
    daily_max_temp = preferences.getFloat("d_max", -100.0);
    last_day = preferences.getInt("l_day", -1);
    last_report_msg = preferences.getString("l_rep", "");
    
    ap_ssid = preferences.getString("ap_ssid", "Hotomobil Ronin XL");
    ap_pass = preferences.getString("ap_pass", "12345678");
    mdns_name = preferences.getString("mdns_name", "karavan");
    
    // I2C ve Sensörler
    Wire.begin();
    status_bme = bme.begin(0x76);
    if(!status_bme) {
        Serial.println("BME280 bulunamadi!");
    } else {
        // EN DOĞRU HAVA İZLEME (WEATHER STATION) AYARLARI
        bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                        Adafruit_BME280::SAMPLING_X16,  // Sıcaklık için maksimum hassasiyet
                        Adafruit_BME280::SAMPLING_X16,  // Basınç için maksimum hassasiyet
                        Adafruit_BME280::SAMPLING_X16,  // Nem için maksimum hassasiyet
                        Adafruit_BME280::FILTER_X16,    // Rüzgar/Hava akımı gürültüsünü engelle
                        Adafruit_BME280::STANDBY_MS_1000); // Sensörü yormamak için 1 sn bekleme
    }
    
    status_adxl = accel.begin();
    if(!status_adxl) {
        Serial.println("ADXL345 (GY-291) bulunamadi!");
    }
    
    // RTC Başlatma
    status_rtc = rtc.begin();
    if(!status_rtc) {
        Serial.println("DS3231 RTC modulu bulunamadi!");
    } else {
        Serial.println("DS3231 RTC hazir.");
        if (rtc.lostPower()) {
            rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
            Serial.println("RTC saati derleme zamanine ayarlandi.");
        }
    }
    
    // SD Kart
    status_sd = SD.begin(PIN_SD_CS);
    if(!status_sd) {
        Serial.println("SD Kart baslatilamadi!");
    } else {
        Serial.println("SD Kart hazir.");
        
        // Geçmiş sıcaklık trendini SD karttan yükle (NVS ömrünü korumak için)
        if (SD.exists("/trend.bin")) {
            File f = SD.open("/trend.bin", FILE_READ);
            if (f && f.size() == (sizeof(temp_history) + sizeof(int)*2)) {
                f.read((uint8_t*)temp_history, sizeof(temp_history));
                f.read((uint8_t*)&history_idx, sizeof(history_idx));
                f.read((uint8_t*)&history_count, sizeof(history_count));
            }
            if (f) f.close();
        }

        // Başlık yazdırılmamışsa yaz (Basınç sütunu eklendi)
        if(!SD.exists("/log.csv")) {
            File file = SD.open("/log.csv", FILE_WRITE);
            if(file) {
                file.println("Tarih-Saat,Sicaklik(C),Nem(%),Basinc(hPa),Gaz(ppm),Egim-X,Egim-Y,Inverter,Pompa,Alarm");
                file.close();
            }
        }
    }
    // Cihazın modeme/routera bağlanırken kendini "ESP32-..." yerine özel ismiyle tanıtmasını sağlar.
    // Bu sayede etrafta veya ağda fazladan "ESP32" cihazları görmezsiniz.
    WiFi.setHostname(mdns_name.c_str());

    // Her durumda Karavan Ağı'nı (İç Ağ) ayakta tut! (Kullanıcı arayüze her an girebilsin)
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(ap_ssid.c_str(), ap_pass.c_str());
    Serial.print("Karavan AP (Dahili) Baslatildi. IP: ");
    Serial.println(WiFi.softAPIP());

    // Dahili Dış Ağ (İstasyon) Bağlantısı (Arka planda denenir)
    String ext_ssid = preferences.getString("ext_ssid", "");
    String ext_pass = preferences.getString("ext_pass", "");
    if (ext_ssid != "") {
        Serial.println("Kaydedilmis dis ag bulundu, arka planda baglaniliyor: " + ext_ssid);
        WiFi.begin(ext_ssid.c_str(), ext_pass.c_str());
    } else {
        Serial.println("Kaydedilmis dis ag yok, yalnizca AP modunda calisiyor.");
    }
    
    // mDNS (Alan Adı) Başlatma
    if (MDNS.begin(mdns_name.c_str())) {
        Serial.println("mDNS Baslatildi! Baglanti adresi: http://" + mdns_name + ".local");
    }
    
    // Wi-Fi ve BLE Çakışmasını (Anten Tıkanmasını) Önlemek İçin
    // Web Sunucu Yönlendirmeleri
    server.on("/", AsyncWebRequestMethod::HTTP_GET, [](AsyncWebServerRequest *request){
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", (const uint8_t*)index_html, sizeof(index_html) - 1);
        response->addHeader("Cache-Control", "no-store, no-cache, must-revalidate");
        response->addHeader("Pragma", "no-cache");
        request->send(response);
    });
    
    server.on("/indir", AsyncWebRequestMethod::HTTP_GET, [](AsyncWebServerRequest *request){
        if(SD.exists("/log.csv")) {
            AsyncWebServerResponse *response = request->beginResponse(SD, "/log.csv", "text/csv");
            response->addHeader("Cache-Control", "no-store, no-cache, must-revalidate");
            response->addHeader("Pragma", "no-cache");
            request->send(response);
        } else {
            request->send(404, "text/plain", "Log dosyasi bulunamadi.");
        }
    });

    server.on("/api/sd/list", AsyncWebRequestMethod::HTTP_GET, [](AsyncWebServerRequest *request){
        if (!status_sd) {
            request->send(500, "application/json", "{\"error\":\"SD Kart Bulunamadi\"}");
            return;
        }
        File root = SD.open("/");
        AsyncResponseStream *response = request->beginResponseStream("application/json");
        response->print("{");
        response->print("\"totalMB\":"); response->print((uint32_t)(SD.totalBytes() / (1024 * 1024))); response->print(",");
        response->print("\"usedMB\":"); response->print((uint32_t)(SD.usedBytes() / (1024 * 1024))); response->print(",");
        response->print("\"files\":[");
        bool first = true;
        listSDRecursiveStream(root, response, first);
        response->print("]}");
        request->send(response);
    });

    server.on("/api/sd/upload", AsyncWebRequestMethod::HTTP_POST, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Yüklendi");
    }, [](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final){
        if(!index){
            String path = filename;
            if(!path.startsWith("/")) path = "/" + path;
            uploadFile = SD.open(path, FILE_WRITE);
        }
        if(uploadFile){
            uploadFile.write(data, len);
            if(final){
                uploadFile.close();
            }
        }
    });

    server.on("/api/sd/delete", AsyncWebRequestMethod::HTTP_POST, [](AsyncWebServerRequest *request){
        if(request->hasParam("f", true)){
            String filename = request->getParam("f", true)->value();
            if(!filename.startsWith("/")) filename = "/" + filename;
            if(SD.exists(filename)){
                File f = SD.open(filename);
                bool isDir = f && f.isDirectory();
                if(f) f.close();
                
                if(isDir) SD.rmdir(filename);
                else SD.remove(filename);
                
                request->send(200, "text/plain", "OK");
            } else {
                request->send(404, "text/plain", "Bulunamadi");
            }
        } else {
            request->send(400, "text/plain", "Parametre Eksik");
        }
    });

    server.on("/api/sd/download", AsyncWebRequestMethod::HTTP_GET, [](AsyncWebServerRequest *request){
        if(request->hasParam("f")){
            String filename = request->getParam("f")->value();
            if(!filename.startsWith("/")) filename = "/" + filename;
            if(SD.exists(filename)){
                request->send(SD, filename, "application/octet-stream", true);
            } else {
                request->send(404, "text/plain", "Dosya bulunamadi.");
            }
        } else {
            request->send(400, "text/plain", "Parametre eksik.");
        }
    });
    
    // SD karttan tailwindcss.js dosyasını önbellekli sun (Eski yol uyumluluğu için)
    server.serveStatic("/tailwindcss.js", SD, "/tailwindcss.js").setCacheControl("max-age=31536000");
    
    // JS kütüphanelerini klasörden sun (Chart.js, PapaParse, Tailwind)
    server.serveStatic("/js", SD, "/js").setCacheControl("max-age=31536000");
    
    server.on("/manifest.json", AsyncWebRequestMethod::HTTP_GET, [](AsyncWebServerRequest *request){
        const char* manifest = "{"
        "\"name\":\"KaravanOS\","
        "\"short_name\":\"Karavan\","
        "\"start_url\":\"/\","
        "\"display\":\"standalone\","
        "\"background_color\":\"#0f172a\","
        "\"theme_color\":\"#0f172a\","
        "\"icons\":[{"
          "\"src\":\"data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='%230ea5e9' stroke-width='2' stroke-linecap='round' stroke-linejoin='round'%3E%3Cpath d='M19 17h2c.6 0 1-.4 1-1v-3c0-.9-.7-1.7-1.5-1.9C18.7 10.6 16 10 16 10s-1.3-1.4-2.2-2.3c-.5-.4-1.1-.7-1.8-.7H5c-.6 0-1.1.4-1.4.9l-1.4 2.9A3.7 3.7 0 0 0 2 12v4c0 .6.4 1 1 1h2'%3E%3C/path%3E%3Ccircle cx='7' cy='17' r='2'%3E%3C/circle%3E%3Cpath d='M9 17h6'%3E%3C/path%3E%3Ccircle cx='17' cy='17' r='2'%3E%3C/circle%3E%3C/svg%3E\","
          "\"sizes\":\"192x192\","
          "\"type\":\"image/svg+xml\""
        "}]"
        "}";
        request->send(200, "application/json", manifest);
    });

    server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request){
        bool shouldReboot = !Update.hasError();
        String respText = "OK";
        if(!shouldReboot){
            respText = String(Update.errorString());
        }
        AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", respText);
        response->addHeader("Connection", "close");
        request->send(response);
        if(shouldReboot){
            shouldRebootSystem = true;
        }
    }, [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
        if(!index){
            Serial.printf("Update Start: %s\n", filename.c_str());
            Update.clearError();
            if(!Update.begin(UPDATE_SIZE_UNKNOWN)){
                Update.printError(Serial);
            }
        }
        if(!Update.hasError()){
            if(Update.write(data, len) != len){
                Update.printError(Serial);
            }
        }
        if(final){
            if(Update.end(true)){
                Serial.printf("Update Success: %uB\n", index+len);
            } else {
                Update.printError(Serial);
            }
        }
    });
    
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    server.begin();
    Serial.println("Sistem Hazir ve Sunucu Baslatildi.");
}

void loop() {
    if(shouldRebootSystem) {
        delay(1000);
        ESP.restart();
    }
    
    ws.cleanupClients();
    
    int16_t scan_n = WiFi.scanComplete();
    if(scan_n >= 0) {
        DynamicJsonDocument d(4096);
        d["type"] = "scan_res";
        JsonArray arr = d.createNestedArray("nets");
        for(int i=0; i<scan_n && i<15; ++i) { // Maksimum 15 ağ göster
            JsonObject net = arr.createNestedObject();
            net["s"] = WiFi.SSID(i);
            net["q"] = WiFi.RSSI(i);
        }
        serializeJson(d, last_scan_json);
        ws.textAll(last_scan_json);
        WiFi.scanDelete();
    }

    // Check Inverter Timer
    if (inv_timer_end_ms > 0 && millis() > inv_timer_end_ms) {
        inv_timer_end_ms = 0;
        inv_state = false;
        digitalWrite(PIN_RELAY_INV, HIGH);
        // Force broadcast update
        last_ws_update = 0;
    }
    unsigned long now = millis();
    
    // Web Arayüzünün çökmemsi/donmaması için ESP32'nin işlemcisine saniyenin yüzde biri kadar nefes aldırıyoruz.
    // Bu kod arka plandaki WiFi ve HTTP isteklerinin işlenmesini sağlar!
    delay(10); 
    
    // --- YENİ EKLENEN: Her 5 Saniyede BME280 Okuma (Isınmayı Önler) ---
    // --- YENİ EKLENEN: Her 5 Saniyede Donanım/I2C/SD Durum Kontrolü ve BME Okuma ---
    if(now - last_bme_update > 5000) {
        last_bme_update = now;
        
        // I2C Donanım Ping Testleri (Bağlantı durumunu anlık takip etmek için)
        Wire.beginTransmission(0x76);
        status_bme = (Wire.endTransmission() == 0);
        
        Wire.beginTransmission(0x53);
        status_adxl = (Wire.endTransmission() == 0);

        Wire.beginTransmission(0x68);
        status_rtc = (Wire.endTransmission() == 0);
        
        // SD Kart Fiziksel Durum Kontrolü (Hot-Plug Desteği)
        if (status_sd) {
            File root = SD.open("/");
            if (!root) {
                status_sd = false;
                SD.end(); // SPI bus serbest bırak
            } else {
                root.close();
            }
        } else {
            // SD Kart kopmuşsa yeniden başlatmayı dene
            status_sd = SD.begin(PIN_SD_CS);
        }
        
        if (status_bme) {
            current_temp = bme.readTemperature() + t_offset;
            current_hum = bme.readHumidity() + h_offset;
            current_pressure = bme.readPressure() / 100.0F; // hPa
            
            if (status_rtc) {
                DateTime n = rtc.now();
                if (current_temp < daily_min_temp) { daily_min_temp = current_temp; preferences.putFloat("d_min", daily_min_temp); }
                if (current_temp > daily_max_temp) { daily_max_temp = current_temp; preferences.putFloat("d_max", daily_max_temp); }
                
                if (last_day != -1 && last_day != n.day()) {
                    char dateStr[16];
                    snprintf(dateStr, sizeof(dateStr), "%02d/%02d", last_day, n.month());
                    last_report_msg = String("Gün Sonu Kamp Raporu (") + String(dateStr) + "): En Düşük " + String(daily_min_temp, 1) + "°C, En Yüksek " + String(daily_max_temp, 1) + "°C";
                    preferences.putString("l_rep", last_report_msg);
                    
                    if (status_sd) {
                        File f = SD.open("/kamp_raporu.txt", FILE_APPEND);
                        if (f) {
                            f.printf("\r\n--- Gun Sonu Kamp Raporu ---\r\n");
                            f.printf("Tarih: %02d/%02d/%04d\r\n", last_day, n.month(), n.year());
                            f.printf("En Dusuk Sicaklik: %.1f C\r\n", daily_min_temp);
                            f.printf("En Yuksek Sicaklik: %.1f C\r\n", daily_max_temp);
                            f.printf("----------------------------\r\n");
                            f.close();
                        }
                    }
                    daily_min_temp = current_temp;
                    daily_max_temp = current_temp;
                    preferences.putFloat("d_min", daily_min_temp);
                    preferences.putFloat("d_max", daily_max_temp);
                    
                    StaticJsonDocument<256> rdoc;
                    rdoc["syslog"] = true;
                    rdoc["msg"] = last_report_msg;
                    rdoc["type"] = "report";
                    String msg;
                    serializeJson(rdoc, msg);
                    ws.textAll(msg);
                }
                if (last_day != n.day()) {
                    last_day = n.day();
                    preferences.putInt("l_day", last_day);
                }
            }
        } else {
            current_temp = 0.0;
            current_hum = 0.0;
        }
    }

    // 2. Her 200 Milisaniyede (5 FPS) Sensörleri Oku ve Web'e Gönder (Yeniden Hızlandırıldı)
    // BLE kaldırıldığı için Wi-Fi anteni tamamen boşa çıktı, eski süper hızlı haline geri döndürüldü.
    if(now - last_ws_update > 200) {
        last_ws_update = now;
        

        float raw_x = 0.0;
        float raw_y = 0.0;
        
        // ADXL345 bağlı ise oku, kopuk ise okumayı atla (kilitlenmeyi önler)
        if (status_adxl) {
            sensors_event_t event; 
            accel.getEvent(&event);
            raw_x = event.acceleration.x - x_offset;
            raw_y = event.acceleration.y - y_offset;
        }
        
        // %20 yeni değer, %80 eski değer ile çok yumuşak ve kararlı veri akışı
        current_x = (current_x * 0.8) + (raw_x * 0.2);
        current_y = (current_y * 0.8) + (raw_y * 0.2);
        
        static float filtered_gas = 0;
        if (mq2_en) {
            int raw_gas = analogRead(PIN_MQ2);
            if (filtered_gas == 0) filtered_gas = raw_gas; // İlk okumada eşitle
            filtered_gas = (filtered_gas * 0.9) + (raw_gas * 0.1); // Yumuşatma (Low-Pass Filter)
            current_gas = (int)filtered_gas;
            
            // Alarm Mantığı
            if(current_gas > mq2_thresh) {
                alarm_active = true;
                if(now > mute_until) {
                    buzzTone(2000);
                }
            } else {
                alarm_active = false;
                if (millis() > chime_override_until) buzzOff();
                mute_until = 0;
            }
        } else {
            // Sensör kapalıysa sistemi yormamak için analog okuma ve matematik yapma
            current_gas = 0;
            filtered_gas = 0;
            alarm_active = false;
            if (millis() > chime_override_until) buzzOff();
            mute_until = 0;
        }
        
        notifyClients();
    }
    
    // 3. Her 5 Dakikada Bir (300.000 ms) Veri Kaydı ve Trend Güncellemesi
    static bool first_log = true;
    if(first_log || now - last_sd_update > 300000) {
        first_log = false;
        last_sd_update = now;
        
        // Hava Tahmini (Barometrik Basınç Değişimi - Delta hPa / 10 dk)
        if (last_pressure_read > 500) { // İlk okumada saçmalamaması için kontrol
            float p_delta = current_pressure - last_pressure_read;
            if (p_delta <= -0.5) weather_forecast = 0;      // Hızlı Düşüş -> Fırtına Bekleniyor
            else if (p_delta < -0.15) weather_forecast = 1; // Düşüş -> Hava Bozacak
            else if (p_delta > 0.25) weather_forecast = 3;  // Yükseliş -> Hava Açacak
            else weather_forecast = 2;                      // Sabit -> Hava Durgun
        }
        last_pressure_read = current_pressure;
        
        // 12 Saatlik Trend İçin RAM Buffer'a Ekle
        temp_history[history_idx] = current_temp;
        history_idx = (history_idx + 1) % HISTORY_SIZE;
        if(history_count < HISTORY_SIZE) history_count++;

        // Yeniden başlatmalara karşı SD karta (trend.bin) kaydet (NVS ömrünü korumak için)
        if (status_sd) {
            SD.remove("/trend.bin");
            File f = SD.open("/trend.bin", FILE_WRITE);
            if (f) {
                f.write((uint8_t*)temp_history, sizeof(temp_history));
                f.write((uint8_t*)&history_idx, sizeof(history_idx));
                f.write((uint8_t*)&history_count, sizeof(history_count));
                f.close();
            }
        }

        // Zaman damgası belirle (RTC aktifse unix epoch, değilse uptime saniye)
        char timeStr[24];
        if (status_rtc) {
            DateTime n = rtc.now();
            snprintf(timeStr, sizeof(timeStr), "%04d-%02d-%02d %02d:%02d:%02d", n.year(), n.month(), n.day(), n.hour(), n.minute(), n.second());
        } else {
            snprintf(timeStr, sizeof(timeStr), "%lu_sn", now / 1000);
        }

        // SD Karta Kaydet
        File file = SD.open("/log.csv", FILE_APPEND);
        if(file) {
            file.printf("%s,%.1f,%.1f,%.1f,%d,%.1f,%.1f,%d,%d,%d\n", 
                timeStr, current_temp, current_hum, current_pressure, current_gas, current_x, current_y, inv_state ? 1 : 0, pump_state ? 1 : 0, alarm_active ? 1 : 0);
            file.close();
        }
    }
}
