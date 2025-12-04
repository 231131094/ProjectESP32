#include <WiFi.h>
#include <firebase_ESP_Client.h>

//Wifi Credentials
const char* ssid = "vivo V40 Lite 5G"
const char* password = "medan098"

//firebase Credential 
#define API_KEY "AIzaSyBQoKDjQUrJnQGwAYIR5XsatJ3C9zpVhsQ"
#define db_URL "https://rest-api-arduino-default-rtdb.asia-southeast1.firebasedatabase.app"
#define user_mail "marvin@gmail.com"
#define user_pass "marvin123"

void setup() {
  connectWiFi();
  config.api_key = API_KEY;
  config.database_url = db_URL;
  auth.user.email = user_mail;
  auth.user.password = user_pass;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  unsigned long fbStart = millis();
  while (!firebse.ready() - fbStart <10000){
    Serial.print("-");
    delay(500);
  }
  if(firebase.ready()){
    Serial.print("Firebase Terhubung..");
    Serial.print("Siap Monitoring");
  }else{
    Serial.print("Firebase Gagal Terhubung");
  }

}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    Serial.print(Wifi Terputus coba Reconnect);
    connectWiFi();
  }
  unsigned long now = millis();
  if (now - lastSensorUpdate > sensorInterval){
    lastSensorUpdate = now;
  }
}

void connectWiFi(){
  WiFi.begin(ssid,password);
  unsigned long start= millis();
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
    if(millis()- start > 20000){
      Serial.print("Gagal Terhubung");
      ESP.restart();
    }
  }
  Serial.print("IP Address :");
  Serial.print(WiFi.localIP());
}

void bacaDanKirimData(){
  int rawLdr = analogRead(LDR_PIN);
  //mapping : LDr semkain gelap = nilai ADC semakin tinggi
  //invert untuk mendapat persentase cahaya (0% gelap, 100% terang)
  lightLevel = map(rawLdr, 4095,0,0,100);
  lightLevel = contrain(lightLevel,0,0,100) 
  Serial.print("Cahaya : %d %% (ADC=%D)\n", lightLevel, rawLdr);
  int rawSoil = analogRead(SOIL_PIN);
  //mapping: Sensor Kering = nilai Tinggi, basah = nilai rendah
  //invert untuk mendapat persentase kelembaban(0% kering 100% basah)
  int soilPercent= map(rawSoil, 4095,0,0,100);
  int soilPercent= constrain(soilPercent, 4095,0,0,100);
}
