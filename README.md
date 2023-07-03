# PORTA RFID - Controle de Acesso por rádio identificação 

<div align="center">
    <img src="./images/Logo.png">
</div>

Colaboração para desenvolvimento do projeto Porta RFID. Conteúdo inicial copiado da página [Porta RFID, do Garoa Hacker Clube](https://garoa.net.br/wiki/Porta_RFID). 

O novo conteúdo deste README.md será editado na branch [features/inicial](https://github.com/torjc01/PortaRFID/tree/features/inicial) e graduado para a branch `prod` gradualmente. 

# Tabela de conteúdo



## Visão geral 


## O que é RFID?
Um sistema RFID (`Radio Frequency Identification`) é composto de dois componentes principais: uma tag, que é apresentada ao sistema, e uma leitora, que faz a identificação da tag e encaminha os dados para tratamento adequado em um computador ou microcontroladora. 

A leitora é constituida por um módulo de rádio emissor de um sinal de alta frequência e de uma antena. Por possuir alimentação elétrica própria é conhecido como dispositivo ativo da comunicação. 

A tag, por sua vez, é chamada de dispositivo passivo da comunicação, pois não dispõe de nenhuma fonte de energia própria. Ela é composta por um microchip que registra e processa informação, além de uma antena. Ela depende do campo magnético criado pela aproximação com a leitora para energizar o seu circuito e assim estabelecer a conexão e a troca de mensagens. 

Em seguida há o processo conhecido como `backscatter`, quando o circuito da leitora detecta e decifra a informação emitida pela tag. A troca de informação se completa aí.


**RFID: Frequências, usos e distâncias típicas**

|Frequência|Tipo|Uso|Pros and contras|Distância|
|---------------|------|----------|---------------|--------|
|125-148 KHz|Passivo|Rastreio animal (ISO11784/11785), control de acesso, e aplicações OEM| Sinal negocia bem em liquidos e metais. Maoir custo da tag por causa do longo tamanho da antena de cobre. |1/2 to 4" is typica. 6" to 12" or more may be possible with specialized equipment|
|13.56 MHz|Passivo|EAS(anti-theft), book and document management, access control, OEM applications|Antennas can be printed on substrate or labels, lowering tag costs. Serious interference from metals.|Can range from inches to several feet depending on reader hardware and tag type.|
|433 MHz (and 2.5 GHz)|Ativo|Highway toll payment systems, vehicle/fleet management, asset tracking, and so on. | Very long range. Very high tag cost. Uses a battery, so tags have a finite lifespan (typically 5 years). | Typically around 30 feet, but can range up to hundreds of feet.|
|915 MHz|Passivo|Supply chain tracking and OEM applications|Very low cost tag. Long range. Anti-collision capabilities allow simultaneous tag reads. Serious interference from liquids and human body| About 10' from a single antenna and 20' between two antennas. Longer ranges can be realized with special hardware. |




## Porta RFID 

- Proposta: criar um sistema que permita a abertura de uma porta (ou qualquer outra coisa) através de uma tag rfid, como visto no London Hackspace
- Ideia basica: um leitor RFID (touchatag) é ligado via USB a um computador. O computador lê o serial number da tag e consulta um banco de dados de membros com seu serial associado. Se o serial for válido, o computador, através de um arduino (ou qualquer outra coisa), aciona um relê, que por sua vez aciona uma trava eletrônica (tipo portão eletrônico), abrindo a porta
- Caveat: em Londres eles usavam o Oyster (tipo bilhete único) como tag. Podemos ver se o bilhete único pode servir ao mesmo propósito (nao, nao serve, eu ja testei. O bilhete unico usa 13MHz e tecnologia MiFare, diferentaço e com direito a encriptacao. Obviamente moooito mais caro. (tabajaralabs))
- Software: librfidiot
- Possíveis problemas: clonagem de tag rfid. Qual a segurança na leitura do serial? Associar com outro meio, como senha?
- Vantagens: se alguém perder a chave não é preciso trocar a de todos


## Arquitetura geral do sistema 

Um ACS (Access Control System) ou sistema de controle de acesso é um elemento essencial à segurança física de imóveis ou escritórios. Ele permite a entrada de pessoas autorizadas, sob certas condições, e bloqueia o acesso de quem não está autorizado. Além disso, um ACS pode tipicamente monitorar os movimentos de entrada/saída de pessoas, assim como fornecer parâmetros de pesquisa para a criação de relatórios. Um sistema ACS avançado pode, além destas características, enviar notificações quando houver ocorrências anormais de eventos de autenticação, bem como integrar vigilância por vídeo.

O sistema de ideal será composto por três componentes básicos: 

- `USU`  : componente visível ao usuário; 
- `ADM`  : componente visível ao administrador; 
- `INFRA`: componente de infra-estrutura. 

### USU

A componente `USU` é composta pela fechadura; pelas tags, cartões ou keyfobs; pelo sensor RFID e pelo cabeamento que a liga aos outros componentes. É a parte mais visível de todo o sistema, e que é exposta ao público geral. Proteções contra `tampering` e vandalismo devem ser adotadas nesta componente para evitar que o sistema seja hackeado ou inutilizado. 

### ADM

A componente `ADM` é basicamente composta pelo software que permite a pilotagem do sistema. Tipicamente ela engloba uma interface de provisionamento dos acessos (concessão, suspensão, retirada e revogação); um portal de gerenciamento dos parâmetros do sistema, com um dashboard de acompanhamento (acessos permitidos, acessos negados, quantidade de leituras, delta entre entradas e saídas, etc). Todos estes componentes são de uso dos responsáveis pela gestão de segurança física, sejam eles administradores da empresa, chefe de segurança, gerente de TI, etc, mas nunca são de acesso geral aos usuários da empresa. 

### INFRA 

A componente `INFRA` engloba componentes que dependem da infra-estrutura das instalações físicas para funcionar: fechaduras, o controlador, o servidor e o cabeamento de baixa tensão. 

- **A fechadura eletrônica** abre a porta seguindo uma mensagem de um comando elétrico recebido do controlador; o cabeamento de baixa tensão deve ser instalado entre os dois componentes para viabilizar esta troca de mensagens. As fechaduras funcionam basicamente em dois modos distintos. `Fail safe` quando a fechadura fecha ao receber corrente elétrica; `Fail secure` a fechadura abre quando recebe corrente elétrica. Para ser conforme a diversas regulamentações e códigos de construção, portas de entrada devem utilizar o modo `fail safe` pois as pessoas devem ser capazes de sair das instalações em caso de emergência, mesmo no evento de pane de energia elétrica.    

- **O controlador**, também conhecido como painél de controle de campo, ou ainda controlador inteligente, não é visível para a maior parte das pessoas. EM geral, é instalado em uma sala de TI, ou um em um painél elétrico, de telefone ou de comunicações. O acesso físico ao controlador deve ser protegido, pois ele possui todas as ligações das quais partem os comandos para as fechaduras elétricas. 


- **O servidor** é o "cérebro" do conjunto, onde as credenciais são recebidas, avaliadas e a decisão de abrir ou não a fechadura é tomada. No servidor também são armazenadas as permissões de acesso no banco de dados. Este servidor pode ser uma máquina local rodando preferencialmente Linux; porém, se este for o caso, será necessário a presença de um administrador de dados on-site, e isso podera causar problemas em caso de ter uma empresa multi-instalação. A alternativa seria um servidor cloud, o que oferece mais vantagens em termos de manutenibilidade, disponibilidade de acesso e facilidade para atualização dos dados. 


## Requisitos 

- Emissão imediata de novos acessos
- Emissão de tag de acesso permanente para membros do Garoa 
- Emissão de tag de acesso temporária com data/hora de expiração
- Revogação de tags de acesso emitidas  
- Casos de uso : 
    - MEMBROS: acesso principal; sem expiração 
    - VISITANTE: visita (acesso temporário)
    - PRESTADOR DE SERVIÇO: sob rendez-vous 


## Features

- Segurança e proteção criptográficas. 
- Verificação rápida dp acesso do cliente
- Mensageria: troca de mensagens com cliente que possui credendial de acesso
- Gestão de acessos facilitada 

## Benefícios

- Gestão e apresentação simples e intuitiva de cartões de acesso:
    - atribuição de novos acessos 
    - controle de acessos temporários 
    - revogação de acessos
- As tags são personalizadas e ligadas a um usuario; todo evento de abertura de porta pode ser mapeado à pessoa associada a ele. 
- Flexibilidade: A solução pode ser usada pelos membros, trabalhadores, fornecedores e visitantes. Também permite a gestão de acessos baseada em atributos ou papéis a diferentes tipos de locais ou recursos físicos
- Eficiência de custos: 
    - Elimina necessidade de trocar a chave de todos quando alguém perde sua chave pessoal, o que implica em economia em compra de material 
    - Não há a necessidade de gerenciar cartões de plástico ou desenvolver uma aplicação separada para este objetivo.
- Duplicatas podem ser geradas para os que desejarem possuir uma tag de backup 
- Mais de uma porta ou dispositivo podem ser controlados por uma mesma tag 
- Possibilidade de fazer `BYOT` `Bring your own tag`: se a pessoa possuir uma tag pessoal, com frequência compatível ao sistema, é possivel atribuir acessos a esta tag



## Tecnologias utilizadas 

# Produto 

## Iterações 

# Hardware

##    Diagrama de blocos 
<div align="center">
    <img src="./images/DiagBlocs.png" width="800" />
</div>

## Schematics e PCB 

##    Lista de Materiais 

[Arduino Uno](https://ca.robotshop.com/products/arduino-uno-r3-usb-microcontroller?pr_prod_strat=collection_fallback&pr_rec_id=9e1056120&pr_rec_pid=7729821548695&pr_ref_pid=7728911941783&pr_seq=uniform) CAD 35.99

[Node MCU](https://www.electromike.com/plaquette-nodemcu-v3-lua-iot-esp8266-wifi-arduino-nodemcu-lua.html) CAD 9.99

[Módulo RFID RC522](https://ca.robotshop.com/products/mifare-rc522-module-rfid-reader) CAD 13.75

    **Especificações técnicas** 

        Frequência: 125 MHz  
        Interface com host: SPI  
        Voltagem operacional: 2.5 - 3.3V    
        Distância de leitura: até 3cm  

[Módulo Relê HL-525 v1.0](https://www.canadarobotix.com/products/1347) CAD 5.09

Conector Jack 2.5mm 

Adaptador de corrente 9V 2A 

Buzzer ou Speaker 8 Ohms 

Fechadura elétrica Solenóide 12 V 

Led 5mm vermelho 

Led 5mm verde 

##    Custos 

    Arduino: ~ R$100 --> Já temos (pra que arduino? Um atmega 8 resolve com um pé nas costas e custa 10 mangos!(tabajaralabs))  
    Trava eletrônica: ~ R$200 --> Tem uma na CCD  
    Leitor RFID Touchatag: ~ €30 ---> Comprado! Está na caixa do pitanga. (foi caro, tem aqui no BR por 50 reais (tabajaralabs))  
    Pacote de 25 tags RFID; ~ €25 (caso bilhete unico nao funcione) (tem chaveiros a 3 reais cada um (tabajaralabs))  

# Software 

##   Aplicação de Gestão de Acessos (Front-End, API, Banco de dados)

O software da aplicação de Gestão de Acessos é formado por três componentes principais: 
- a base de dados PostgreSQL; 
 responsavel por armazenar todas as entidades de dados geridas pelo sistema;
 - uma API NestJS, 
 responsavel por realizar a leitura dos dados disponiveis no banco de dados de acesso, bem como a atualizaçao desta base por pessoas autorizadas; 
- aplicaçao front-end,
 em framework a escolher, para facilitar o acesso dos usuários às informações mantidas na BD.

Para simplificar o desenvolvimento e a manutenibilidade da aplicaçao a longo prazo, ela sera desenvolvida e entregue conteneirizada, colocando em containers docker cada um dos componentes do sistema. Abaixo está ilustrada uma arquitetura proposta para o software.

<div align="center">
    <img src="./images/ArqSoftware.png" width="800" />
</div>


###        Dependências  

- Docker 
- Docker-compose 
- Node.js
- NestJS


###        Instalação

Os dados do sistema são mantidos em uma base de dados PostgreSQL, e acessados via uma API backend em NestJS. Uma interface de usuário deverá ser criada para facilitar o acesso a estes dados. 

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

###  Utilização 
###  Implantação produção 
###  Screenshots e fotos 
##   Firmware 
###  Dependências 

- Arduino IDE 
- Biblioteca RFID 
- Biblioteca WiFi 

###  Instalação
###  Utilização 
###  Implantação produção 
###  Screenshots e fotos

# FINAL 
##    Gestão de versões 
##    Outros recursos e docs importantes 
##    Troubleshooting
##    Problemas conhecidos
##    Onde encontrar ajuda 
##    Contribuir 
##    Interessados 

    --Pitanga 12h34min de 3 de Agosto de 2010 (UTC)  
    --Aleph 01h58min de 4 de Agosto de 2010 (UTC)  
    --Felipe Bueno 10h38min de 29 de Abril de 2011 (UTC)  
    --Alexandre Souza 16h04min de 26 de Julho de 2011 (UTC)  
    --Haoji 04h32min de 11 de Agosto de 2013 (UTC)  
    -- Paulo F. Manasia 10h48min de 22 de Setembro de 2014 (UTC)  

##    Licença


##    Agradecimentos


##    Referências 