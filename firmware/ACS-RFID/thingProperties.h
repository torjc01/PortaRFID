/*
 * 
 * Copyright (c) 2023 Gouvernement du Québec
 * Auteur: Julio Cesar Torres (torj01)
 * SPDX-License-Identifier: LiLiQ-R-v.1.1
 * License-Filename: /LICENSE
 */

/**
 * Definicão dos pins ligados à leitora RFID. O número do pin usado é o #GPIO do pin, ao invés do 
 * pin marcado no silkscreen do NodeMCU. Portanto, para o pin D.., o #gpio é 4, e para o pin D.., 
 * o #GPIO é 5. 
 */
#define SS_PIN 4  
#define RST_PIN 5

// Definicao do local da porta
#define LOCAL_ID A10

#define WIFI_RETRIES 30
// ----------------------------
// Configurations de connexion au site 
// ----------------------------

// Mettre just l'addresse base de l'URL qu'on veut se connecter.
#define HOST_ADDRESS "http://192.168.10.18"

// Le reste de l'adresse qui vient après l'URL de base
#define ENDPOINT "/acesso/filtra"

// OPTIONEL - Le finferprint du site qu'on veut se connecter.
// Le fingerprint changera dans une base regulière, selon les 
// rénovations du certificat. Il faut être conscient que cela 
// peut briser l'application
// #define HOST_FINGERPRINT "C1 B5 F2 29 27 9B 46 14 EB 80 3E B3 0F 35 AC 68 26 40 5C 81"

// ----------------------------
// Configurations de tag NFC 
// ----------------------------

// Adresse de l'URL qui sera broadcasté par le NFC
// #define didcommInvite   "https://exp-port-e-invitant.apps.exp.openshift.cqen.ca/index.html"

// ----------------------------
// Variables diverses 
// ----------------------------
#define ADDRESS_NON_DISP    0
#define ADDRESS_DISP        1

#define HTTP_PORT           80
#define HTTPS_PORT          443
#define NFC_BUFFER_SIZE     512

#define SIG_INI     "0xAA"
#define SIG_FIN     "0xAB"
#define SIG_ACK     "0xBA"
#define SIG_NACK    "0xBB"

#define SIG_GEN     "0x10"
#define SIG_RENV    "0x11"
#define SIG_CAN     "0x12"

#define DELAY_S     1000
#define DELAY_M     3000
#define DELAY_L     5000
