# PortaRFID - Controle de Acesso por rádio 

<div align="center">
    <img src="./images/Logo.png">
</div>


Colaboração para desenvolvimento de o do projeto Porta RFID. Conteúdo inicial copiado da página [Porta RFID, do Garoa Hacker Clube](https://garoa.net.br/wiki/Porta_RFID). 

O novo conteúdo deste README.md será editado na branch [features/inicial](https://github.com/torjc01/PortaRFID/tree/features/inicial). 

## O que é RFID

Um sistema RFID `Radio Frequency Identification` é composto de dois componentes principais: uma tag, que se apresenta ao sistema, e uma leitora, que faz a identificaçao da tag e encaminha os dados para tratamento adequado. 

A leitora é constituida de um modulo de radio, emissor de um sinal de alta frequencia e de uma antena. Por possuir alimentaçao elétrica propria é conhecido como dispositivo ativo da comunicacao. 

A tag, por sua vez, é chamada de dispositivo passivo da comunicaçao, pois nao dispoe de nenhuma fonte de energia propria. Ela depende do campo magnético criado pelo sinal emitido pela leitora para energizar o seu circuito e assim estabelecer a conexao e a troca de mensagens. 

## Porta RFID
- Proposta: criar um sistema que permita a abertura de uma porta (ou qualquer outra coisa) através de uma tag rfid, como visto no London Hackspace
- Ideia basica: um leitor RFID (touchatag) é ligado via USB a um computador. O computador lê o serial number da tag e consulta um banco de dados de membros com seu serial associado. Se o serial for válido, o computador, através de um arduino (ou qualquer outra coisa), aciona um relê, que por sua vez aciona uma trava eletrônica (tipo portão eletrônico), abrindo a porta
- Caveat: em Londres eles usavam o Oyster (tipo bilhete único) como tag. Podemos ver se o bilhete único pode servir ao mesmo propósito (nao, nao serve, eu ja testei. O bilhete unico usa 13MHz e tecnologia MiFare, diferentaço e com direito a encriptacao. Obviamente moooito mais caro. (tabajaralabs))
- Software: librfidiot
- Possíveis problemas: clonagem de tag rfid. Qual a segurança na leitura do serial? Associar com outro meio, como senha?
- Vantagens: se alguém perder a chave não é preciso trocar a de todos

## Requisitos 
 
- Emissao de tag de acesso permanente para membros do Garoa 
- Emissao de tag de acesso temporaria com data/hora de expiraçao
- Revogaçao de tags emitidas  
- Casos de uso : 
    - MEMBROS: acesso principal 
    - VISITANTE: visita (acesso temporario)
    - PRESTADOR DE SERVIÇO: rendez-vous 

## Beneficios 

- Gestao simplificada da gestao de acessos 
    - atribuicao de novos acessos 
    - controle de acessos temporarios 
    - revogacao de acessos
- Elimina necessidade de trocar a chave de todos quando alguém perde sua chave pessoal >> economia em compra de material 
- Duplicatas podem ser geradas para os que desejarem possuir uma tag de backup 
- Mais de um tipo de acesso pode ser controlado pela mesma tag 
- Possibilidade de fazer `BYOT` Bring your own tag: se a pessoa possuir uma tag, é possivel atribuir acessos a esta tag. 



### Diagrama de blocos 

<div align="center">
    <img src="./images/DiagBlocs.png" width="800" />
</div>

## Lista de Materiais 

[Arduino Uno](https://ca.robotshop.com/products/arduino-uno-r3-usb-microcontroller?pr_prod_strat=collection_fallback&pr_rec_id=9e1056120&pr_rec_pid=7729821548695&pr_ref_pid=7728911941783&pr_seq=uniform) CAD 35.99

[Node MCU](https://www.electromike.com/plaquette-nodemcu-v3-lua-iot-esp8266-wifi-arduino-nodemcu-lua.html) CAD 9.99

[Módulo RFID RC522](https://ca.robotshop.com/products/mifare-rc522-module-rfid-reader) CAD 13.75

[Módulo Relê HL-525 v1.0](https://www.canadarobotix.com/products/1347) CAD 5.09

Conector Jack 2.5mm 

Adaptador de corrente 9V 2A 

Buzzer ou Speaker 8 Ohms 

Fechadura elétrica Solenóide 12 V 

Led 5mm vermelho 

Led 5mm verde 


Iteração 2: 
Placa de circuito impresso 
(Material para a integração do módulo relê)
(Material para a integração do arduino)


## Aplicação de Gestão de Acessos 

O software da aplicação de Gestão de Acessos é formado por três componentes principais: a base de dados PostgreSQL, responsavel por armazenar todas as entidades de dados geridas pelo sistema; uma API NestJS, responsavel por realizar a leitura dos dados disponiveis no banco de dados de acesso, bem como a atualizaçao desta base por pessoas autorizadas; 3. aplicaçao front-end, em framework a escolher, para facilitar o acesso dos usuarios às informaçoes mantidas na BD.

Para simplificar o desenvolvimento e a manutenibilidade da aplicaçao a longo prazo, ela sera desenvolvida e entregue conteneirizada, colocando em containers docker 

<div align="center">
    <img src="./images/ArqSoftware.png" width="800" />
</div>

## Instalaçao 

O software componente do sistema é mantido em uma base de dados PostgreSQL, e acessado via uma API backend em NestJS. Uma interface de usuario devera ser criada para facilitar o acesso aos dados. 

Para a execução da aplicação nos containers, primeiro é necessário criar um arquivo chamado `.env` no diretório `docker/`, e informe os valores que você preferir para as variáveis de ambiente abaixo, que serão utilizadas para completar o docker-compose: 

```
APP=porta-
SUFFIX=
NETWORK=
POSTGRES_USER=
POSTGRES_PASSWORD=
POSTGRES_DB=
```

Após a criação do arquivo, lance a aplicação com o comando seguinte: 

```
docker-compose up 
```

Logo após iniciar o container pela primeira vez, execute o comando seguinte para criar as credenciais no OmniDB: 

```
docker exec -it my_container python omnidb-server.py --createsuperuser=<nome usuario> <password>
```



## Custos:  
    Arduino: ~ R$100 --> Já temos (pra que arduino? Um atmega 8 resolve com um pé nas costas e custa 10 mangos!(tabajaralabs))  
    Trava eletrônica: ~ R$200 --> Tem uma na CCD  
    Leitor RFID Touchatag: ~ €30 ---> Comprado! Está na caixa do pitanga. (foi caro, tem aqui no BR por 50 reais (tabajaralabs))  
    Pacote de 25 tags RFID; ~ €25 (caso bilhete unico nao funcione) (tem chaveiros a 3 reais cada um (tabajaralabs))  
    
## Interessados:    
    --Pitanga 12h34min de 3 de Agosto de 2010 (UTC)  
    --Aleph 01h58min de 4 de Agosto de 2010 (UTC)  
    --Felipe Bueno 10h38min de 29 de Abril de 2011 (UTC)  
    --Alexandre Souza 16h04min de 26 de Julho de 2011 (UTC)  
    --Haoji 04h32min de 11 de Agosto de 2013 (UTC)  
    -- Paulo F. Manasia 10h48min de 22 de Setembro de 2014 (UTC)  