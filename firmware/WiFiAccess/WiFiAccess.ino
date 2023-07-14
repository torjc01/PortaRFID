#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid="NOKIA-5A11"; 
const char* password="83YF6xFkku"; 
const char* serverAddress = "https://b898-67-221-61-19.ngrok-free.app";
const char* endpoint = "/acesso/filtra";
const int serverPort=443;

void setup(){
    Serial.begin(115200); 

    // Conecte-se à rede WiFi 
    WiFi.begin(ssid, password); 

    while(WiFi.status() != WL_CONNECTED){
        delay(1000); 
        Serial.println("Conectando ao WiFI...");
    }

    Serial.println("Conectado ao WiFi");

    // Inicialize a conexao com o servidor
    WiFiClientSecure client; 
    client.setInsecure();
    Serial.print("Vai se conectar ao servidor: ");
    Serial.println(serverAddress); 
    Serial.print("Vai se conectar a porta: ");
    Serial.println(serverPort);
     
    if(!client.connect(serverAddress, serverPort)){
        Serial.println("Falha na conexao com o servidor");
        return; 
    }

    //Envie uma solicitacao GET para o servidor 
    client.print("GET /acesso/filtro HTTP/1.1\r\n"); 
    client.print("Host: "); 
    client.print(serverAddress);
    client.print("\r\n");
    client.print("Connection: close\r\n\r\n");

    // Aguarde a resposta do servidor 
    bool bodyStarted = false; 
    while(client.connected()){
        if(client.available()){
            String line = client.readStringUntil('\n'); 
            Serial.println(line); 

            // Verifique a primeira linha da resposta 
            if(line.startsWith("HTTP/1.1")){
                int statusCode = line.substring(9,12).toInt(); 
                String statusText = line.substring(13); 
                Serial.println("Codigo de retorno HTTP: "); 
                Serial.println(statusCode);
                Serial.println("Mensagem HTTP: ");
                Serial.println(statusText);

                // Faca algo com o codigo e o texto do codigo HTTP 
            }

            // Verifique se o corpo da resposta comecou
            if(!bodyStarted && line == "\r"){
                bodyStarted = true;
                Serial.println("Inicio do corpo da resposta");
            }

            // Leia e imprima o corpo da resposta 
            if(bodyStarted){
                Serial.println(line);
                // Faça algo com o conteudo do corpo da resposta 
            }
        }
    } 

    // Encerre a conexao
    client.stop(); 
}

void loop(){
    // Codigo principal aqui, se necessario
}
