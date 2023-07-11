/**
 * Controle de acesso RFID. 
 */

// RFID
#include <MFRC522.h>
#include <SPI.h>

//   WiFi Libs 
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include "arduino_secrets.h"
#include "thingProperties.h"

//-------------------------------
//       Variaveis globais
//-------------------------------

// Criar instancia da MRFC522
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Cria instância de um cliente HTTP
WiFiClientSecure client;            


//-------------------------------
//       Rotinas 
//-------------------------------

void setup() {

  #ifdef DEBUG
    Serial.begin(115200); 
    delay(100); 
    Serial.setDebugOutput(true);
    DBG(); // Imprime linha em branco após gibberish

    configTime(1 * 3600, 1 * 3600, "pool.ntp.org", "time.nist.gov"); 
    delay(5000); 

    SPI.begin();   // inicializa bus SPI 
    delay(100); 

    mfrc522.PCD_Init(); // inicializa leitora rfid 
    delay(1000); 

    DBG("Realiza auto teste");
    DBG(String(mfrc522.PCD_PerformSelfTest())); 
    delay(100); 

    DBG("Recupera gain da antena"); 
    DBG(String(mfrc522.PCD_GetAntennaGain()));
    delay(100); 

    DBG("Seta gain maximo da antena"); 
    DBG(String(mfrc522.RxGain_max));
    delay(100); 

    DBG("Recupera gain da antena"); 
    DBG(String(mfrc522.PCD_GetAntennaGain()));
    delay(100); 

  #endif

  pinMode(BUILTIN_LED, OUTPUT);         // Initialize the BUILTIN_LED pin as an output
  digitalWrite(BUILTIN_LED, HIGH);      // Turn the LED off by making the voltage HIGH
  delay(10);
  

  setupWiFi();
    
}


void setupWiFi(){
  int WiFiCounter = 0; 
  DBG("Conectando a "); 
  DBG(ssid); 
  WiFi.disconnect(); 
  WiFi.mode(WIFI_STA);   // Desabilita o modo AP 
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED && WiFiCounter < 30) {  // espera ate um maximo de 30 seg. 
      delay(1000); 
      WiFiCounter++; 
      #ifdef DEBUG
        Serial.print("."); 
      #endif
  }
  DBG();
  DBG("WiFi conectada");
  DBG("Endereco IP: ");
  DBG(WiFi.localIP());

  // Si vous n'avez pas besoin de checker le fingerprint
  client.setInsecure();

  // Si vous voulez checker le fingerprint
  // client.setFingerprint(HOST_FINGERPRINT);
  // client = server.available();
}

  
void loop() {

  // look for new cards 
  if(!mfrc522.PICC_IsNewCardPresent()){
    delay(50);
    return;  
  }

  // Select one of the cards 
  if(!mfrc522.PICC_ReadCardSerial()){
    DBG("Selecao falhou");
    delay(50); 
    return;  
  }

  // Imprime detalhes 
  DBG(); 
  DBG("Card UID: ");
  #ifdef DEBUG
    dump_byte_array_hex(mfrc522.uid.uidByte, mfrc522.uid.size); 
    delay(10); 
  #endif 

  DBG(); 

  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  bool isValido = validaAcesso(content.substring(1)); 
  Serial.println(isValido);

}


bool validaAcesso(String pass){
  // Abre a conexao com o servidor (utilisar a porta 80)
  if(!client.connect(HOST_ADDRESS, HTTPS_PORT)){
      Serial.println(F("Conexao sem sucesso"));
      return false;
  }  

  DBG(pass);

  // Deixa um pouco de tempo para o ESP 
  yield(); 
  
}




//------------------------------------
//        Rotinas utilitarias 
//------------------------------------
/**
 * Estas sao rotinas que tem origem nos sketchs de exemplo da biblioteca
 * RFID de Miguel Balboa (https://github.com/miguelbalboa/rfid). As rotinas
 * estão disponiveis em open-source
 */

 //// Helper routine to dump a byte array as hex values to Serial
void dump_byte_array_hex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; ++i) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}


// Helper routine to dump a byte array to Serial
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; ++i) {
    Serial.print(buffer[i] < 100 ? buffer[i] < 10 ? " 00" : " 0" : " ");
    Serial.print(buffer[i]);
  }
}


// Helper routine to dump a byte array as hex values to String
String byte_array_hex_string(byte *buffer, byte bufferSize) {
  String hex = "";
  for (byte i = 0; i < bufferSize; ++i) {
    hex += String(buffer[i], HEX);
  }
  return hex;
}


//Helper routine to dump a byte array as a String
String byte_array_string(byte *buffer, byte bufferSize) {
  String str = "";
  for (byte i = 0; i < bufferSize; ++i) {
    str += char(buffer[i]);
  }
  return str;
}


//Helper routine to convert C string to String
String cstring_string(const byte *buffer) {
  String str = "";
  byte i = 0;
  while(buffer[i] != '\0') {
    str += char(buffer[i]);
    ++i;
  }
  return str;
}
