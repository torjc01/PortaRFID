/* thingsProperties.h 
 * Arquivo de header personalizado para definicao de propriedades 
 * do firmware. Definicao de constantes, funcoes comuns, etc. 
 * 
 * Auteur: Julio Cesar Torres (torj01)
 * SPDX-License-Identifier: LiLiQ-R-v.1.1
 * License-Filename: /LICENSE
 */

/**
 * Definicao da funcao de escrita no serial monitor. Se a variavel DEBUG estiver 
 * definida, o texto é escrito na saida; senao, by-passa. 
 */
#define DEBUG 
#ifdef DEBUG
  #define DBG(str) Serial.println(str); 
#else 
  #define DBG(str) // nada 
#endif

/**
 * Código de identificacao da porta.
 */
#define LOCAL_ID A01

/**
 * Informacoes sobre o servidor da API 
 */
const char* host = "192.168.18.14"; 
const int port = 3000; 
#define API "/acesso/filtra"


// Mettre just l'addresse base de l'URL qu'on veut se connecter.
#define HOST_ADDRESS "port-e-daemon.apps.exp.openshift.cqen.ca"
#define HTTP_PORT           80
#define HTTPS_PORT           443

// Le reste de l'adresse qui vient après l'URL de base
#define ENDPOINT "/connection"

/**
 * Definicão dos pins ligados à leitora RFID. O número do pin usado é o #GPIO do pin, ao invés do 
 * pin marcado no silkscreen do NodeMCU. Portanto, para o pin D.., o #gpio é 4, e para o pin D.., 
 * o #GPIO é 5. 
 */
#define SS_PIN  4 // GPIO#4, pin D.. no NodeMCU
#define RST_PIN 5 // GPIO#5, pin D.. no NodeMCU 


/**
 * Definicao dos pins do relê. 
 */
#define RELAY_PIN 00
