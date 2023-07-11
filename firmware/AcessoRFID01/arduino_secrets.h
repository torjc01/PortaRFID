/* arduino_secrets.h
 * Arquivo de segredos. Contém senhas, API_KEYS, informacoes sobre 
 * credenciais, enfim, toda informacao e configuracao de seguranca 
 * que nao devem ser publicados. 
 * 
 * Este arquivo deve ser incluso no arquivo .gitignore do projeto. 
 * Na documentacao do projeto, orientar novos utilizadores a criar 
 * este arquivo na raiz do sketch e preencher com as variáveis 
 * necessarias ao bom funcionamento do sketch. 
 * 
 * Auteur: Julio Cesar Torres (torj01)
 * SPDX-License-Identifier: LiLiQ-R-v.1.1
 * License-Filename: /LICENSE
 */

// ----------------------------
// Variables de connexion wifi
// ----------------------------

// Réseau local maison 
const char* ssid     = "NOKIA-5A11";             // L'identificateur du réseau
const char* password = "83YF6xFkku";             // Le mot de passe pour se connecter au réseau 

// OPTIONEL - Le fingerprint du site qu'on veut se connecter.
// Le fingerprint changera dans une base regulière, selon les 
// rénovations du certificat. Il faut être conscient que cela 
// peut briser l'application
/**
 * Opcional - o fingerprint do site que vamos nos conectar. Este fingerprint mudará em 
 * uma base regular, seguindo as renovacoes do certificado digital. É preciso estar 
 * consciente que isso pode quebrar a aplicacao
 */
#define HOST_FINGERPRINT "C1 B5 F2 29 27 9B 46 14 EB 80 3E B3 0F 35 AC 68 26 40 5C 81"
