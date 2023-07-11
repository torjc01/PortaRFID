/*
 * Firmware controle de acessos RFID.
 * 
 * Copyright (c)2023 Julio Cesar Torres dos Santos <torjc01>
 * License-Filename: /LICENSE
 * 
 */

// --------------------------------------------
//   Standard Library
// --------------------------------------------
#include "ACS-RFID.h"
#include <SPI.h>

//   WiFi Libs 
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//   RFID Libs 
#include <MFRC522.h>

// --------------------------------------------
//   Arquivos header personalizados
// --------------------------------------------
#include "arduino_secrets.h"
#include "thingProperties.h"

// --------------------------------------------
//   Variáveis globais
// --------------------------------------------
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Cria instância MFRC522.
WiFiClientSecure client;            // Cria instância de um cliente HTTP

void setup()
{
  Serial.begin(115200); 
  Serial.println("[ACS-RFID] Inicializando a comunicacao SPI");
  SPI.begin();      // Initiate  SPI bus
  Serial.println("[ACS-RFID] Inicializando MRC522");
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("[ACS-RFID] Leitora inicializada.");

  setupWiFi(); 

}

/**
 * Rotina de conxão à rede WiFi. 
 */
void setupWiFi(){
  Serial.println("[WIFI] Setup do WiFI");

  //----------------------------
  //   Configuracao do WiFI
  // ---------------------------
  WiFi.mode(WIFI_STA); 
  WiFi.disconnect(); 
  delay(100); 


  // Tentativa de reconexão ao WiFi 
  Serial.println("[WIFI] Tentativa de conexão ao WiFi: "); 
  Serial.print("[WIFI]"); 
  Serial.println(ssid); 
  WiFi.begin(ssid, password); 
  
  // Loop de conexão 
  /*while(WiFi.status() != WL_CONNECTED){
    Serial.print("*");
    delay(DELAY_S);   
  }*/

  while ((WiFi.status() != WL_CONNECTED)){
    Serial.print('.'); 
        wait(200);
  }

  Serial.println("[WIFI]");
  Serial.println("[WIFI] WiFi conectado!");
  Serial.println("[WIFI] Endereco IP: ");
  IPAddress ip = WiFi.localIP(); 
  Serial.print("[WIFI] ");
  Serial.println(ip);
  
  // Se você não precisa de checar o fingerprint do servidor
  client.setInsecure(); 

  // Se você quiser checar o fingerprint do servidor
  //client.setFingerprint(HOST_FINGERPRINT);
  
}

void loop(){

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println("\n[ACS-RFID] ");
  yield(); 

  /*confereAcesso(content.substring(1));
  delay(10000);
  Serial.println(); */
  String id = content.substring(1); 
  /*if (id == "04 20 49 0A ED 49 85") { //change UID of the card that you want to give access
    Serial.println("[ACS-RFID] Acesso autorizado ");
    Serial.print("[ACS-RFID] Welcome to Garoa Hacker Club ");
    Serial.println(content.substring(1));
    delay(1000);
    Serial.println("[ACS-RFID] Have FUN ");
    Serial.println();
  }
  else {
    Serial.println("[ACS-RFID] Acesso negado! GTFO! ");
    confereAcesso(id);
    delay(3000);
  }*/
}

String confereAcesso(String codigoRFID){
  yield(); 
  Serial.print("Conferência de acesso: "); 
  Serial.println(codigoRFID); 
  delay(3000);
  Serial.println();
    
}

void wait(unsigned long time) {
    unsigned long start=millis();
    while(millis()-start < time) {
        yield();
    };
}
