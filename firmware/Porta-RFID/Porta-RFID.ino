/*
 * 
 * Auteur: Julio Cesar Torres (torj01)
 * SPDX-License-Identifier: LiLiQ-R-v.1.1
 * License-Filename: /LICENSE
 * Copyright (c) 2023
 */

// Bibliotecas standard
#include <SPI.h>

//  Wifi Libs
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UrlEncode.h> 

//   RFID Libs 
#include <MFRC522.h>

// --------------------------------
// Arquivos header personalizados
// --------------------------------
#include "Porta-RFID.h"
#include "arduino_secrets.h"
#include "thingProperties.h"



// -----------------------------
// Variáveis globais
// -----------------------------

// Client HTTPS
WiFiClientSecure client;

// Variaveis RFID
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Cria instância MFRC522.

void setup(){
    Serial.print("Configurando baud rate: ");
    Serial.begin(BAUD_RATE);
    
    Serial.println("");
    Serial.println("");
    
    Serial.println("[RFID] Inicializando a comunicacao SPI");
    SPI.begin();      // Inicializa  SPI bus
    Serial.println("[RFID] Inicializando MRC522");
    mfrc522.PCD_Init();   // Inicializa MFRC522
    Serial.println("[RFID] Leitora inicializada.");
    
    Serial.println("[WIFI] Setup de l'application");
    setupWiFi();
  
}

void setupWiFi(){
    Serial.println("[WIFI] Setup doWiFi");
  
    // -----------------------------
    // Configuration du WiFi 
    // -----------------------------

    // Connecter au WiFi
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);  

    // Tentativa de reconexão ao WiFi 
    Serial.print("\n[WIFI] Tentativa de conexão ao WiFi:  ");
    Serial.print("[WIFI] ");
    Serial.println(ssid); 
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
    
    Serial.println("[WIFI] ");
    Serial.println("[WIFI] WiFi conectado!");
    Serial.println("[WIFI] Endereco IP: ");
    IPAddress ip = WiFi.localIP();
    Serial.print("[WIFI] ");
    Serial.println(ip);
    
    // Se você não precisa de checar o fingerprint do servidor
    client.setInsecure();

    // Se você quiser checar o fingerprint do servidor
    // client.setFingerprint(HOST_FINGERPRINT);
    // client = server.available();  

    Serial.println("[RFID] ...... Sistema pronto para validar acessos RFID! ......");
}


void loop(){

  // Procura por cartões 
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Seleciona um dos cartões
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Mostra o UID no serial monitor
  Serial.println();
  //Serial.print("[RFID] UID tag : ");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  yield(); 

  String idCartao = content.substring(1); 
  boolean temAcesso = validarCartao(idCartao.c_str());

  /**
   * Se o acesso existir, executar a rotina de abertura; senao, avisar ao usuário na porta. 
   */
  if(temAcesso == 1){     // possui acesso 
    acessoValido();
  } else {                // não possui acesso
    acessoInvalido();
  }
  
  delay(1000);
}

boolean validarCartao(String idCartao){

    Serial.println("\n***********************************************");
    Serial.println("     Validacao do cartao " + idCartao);
    Serial.println("***********************************************");

  
  // Abre a conexão com o servidor (utilizar a porta 80 ao invés de [HTTPS_PORT] se HTTP)
    if (!client.connect(HOST_ADDRESS, HTTPS_PORT)){
        Serial.println(F("[WIFI] Connexion non réussie"));
        return "";
    }

    // Constrói a url e faz o URL encoding dos parâmetros
    char urlParam[100]; 
    strcpy(urlParam, ENDPOINT);
    strcat(urlParam, "?codigoRFID=");
    strcat(urlParam, urlEncode(idCartao).c_str());
    strcat(urlParam, "&codigoIdPorta="); 
    strcat(urlParam, urlEncode(LOCAL_ID).c_str());

    // laisse un peu de temps à l'ESP
    yield(); 

    // Envoie la requête HTTP 
    client.print(F("GET "));
    
    // Endpoint: c'est la deuxième partie de la requête (tout ce qui vient après l'URL de base)
    // por exemplo: /acesso/filtra?codigoRFID=64%20EC%204B%2051&codigoIdPorta=A01
    client.print(urlParam);  
    
    // HTTP 1.0 est l'ideal 
    client.println(F(" HTTP/1.0")); 

    // Headers
    client.print(F("Host: "));
    client.println(HOST_ADDRESS);

    client.println(F("Cache-Control: no-cache"));

    if (client.println() == 0){
        Serial.println(F("[WIFI] L'envoi de la requête n'est pas réussie"));
        return "";
    }

    // Check HTTP status
    char status[32] = {0};
    client.readBytesUntil('\r', status, sizeof(status));

    Serial.print("[WIFI] Status: ");
    Serial.println(status); 

    // Saute les HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)){
        Serial.println(F("[WIFI] Réponse invalide"));
        return "";
    }

    // Les APIs qui répondent avec HTTP/1.1, on doit enlever les données
    //
    // peek() va lire le character, mais ne vas pas l'enlever de la queue
    String acesso = ""; 
    while (client.available() && client.peek() != '{' && client.peek() != '['){
        char c = 0;
        client.readBytes(&c, 1);
        acesso += c; 
    }

    // Lorsque le client sera disponible, on lira chaque byte encore disponible
    // et on l'imprimera dans le serial monitor
    while (client.available()){
        char c = 0;
        client.readBytes(&c, 1);
        Serial.print(c);
    }

    int check = strcmp(status, "HTTP/1.1 200 OK");
    
    Serial.print("\nSTATUS válido? ");
    Serial.println(check);
    
    if (check == 0){
      return true;
    } else {
      return false;  
    }
}

void acessoValido(){
  Serial.println("acessoValido()");
  Serial.println("==================================================");
  Serial.println("\nAcesso autorizado. Bem vindo ao Garoa!\n");
  Serial.println("==================================================");
}

void acessoInvalido(){
  Serial.println("acessoInvalido()");
  Serial.println("==================================================");
  Serial.println("\nAcesso não autorizado. Vá embora.\n"); 
  Serial.println("==================================================");
}
