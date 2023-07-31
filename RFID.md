
<!-- Header --> 

# Visão geral da tecnologia RFID

<div align="center">
    <img src="./images/Logo.png">
</div>
<!-- Fim do Header -->

## Tecnologia RFID - Visão geral 

## O que é RFID?

A tecnologia de Identificação por Radiofrequência, conhecida como RFID (`Radio Frequency Identification`), tem se tornado cada vez mais relevante e presente em diversos setores.  Esta tecnologia permite a identificação e o rastreamento de pessoas, objetos e animais por meio de tags eletrônicas, proporcionando benefícios significativos em áreas como logística, cadeia de suprimentos, varejo, saúde, controle de acesso, e muito mais. 

Um sistema RFID é a soma de alguns componentes principais: tags, antenas, leitoras e sistemas de informação.  que é apresentada ao sistema, e uma leitora que faz a identificação da tag e encaminha os dados para tratamento adequado em um computador ou microcontrolador. 

A leitora é constituida por um módulo de rádio emissor de sinal de determinada frequência e de uma antena. Por possuir alimentação elétrica própria é conhecida como dispositivo ativo da comunicação. Ela recebe a onda de rádio e a converte em dados digitais que serão tratados e armazenados por um sistema de informação. Existem dois tipos de leitoras: fixas, que são instaladas em um ambiente, e móveis, que podem ser levadas para ... 

A tag, por sua vez, é chamada de dispositivo passivo da comunicação, pois normalmente não dispõe de nenhuma fonte de energia própria. Ela é composta por um microchip que registra e processa informação, além de uma antena. Ela depende do campo magnético criado pela aproximação com a leitora para energizar o seu circuito e assim estabelecer a conexão e a troca de dados, de sua ID e de dados programáveis caso estejam disponíveis. Existem tags ativas, mas elas são utilizadas para casos de uso especiais em que a tag deve ser localizada a uma longa distância. 

As antenas permitem o estabelecimento da comunicação entre tags e leitoras. Elas podem ser integradas ao circuito da leitora, ou podem ser externas, para facilitar a instalação física. Sem uma antena, a leitora não seria capaz de receber as ondas de rádio, nem transmitir informação. 

O sistema de informação é necessário para fazer o tratamento dos dados e armazená-los em banco de dados. Ele deve ser capaz de programar tags, gerenciar dispositivos e dados, de fazer monitoramento remoto de tags e a configuração do hardware. 

Neste documento vamos explorar em detalhes os conceitos fundamentais de comunicação RFID, incluindo as diferentes frequências utilizadas, os padrões de comunicação, os tipos de tags disponíveis, o alcance da tecnologia e os principais normativos relacionados. 


## RFID: tags, frequências, categorias, padrões de comunicação e aplicações 

### Tags 

<div align="center">
    <img src="./images/RFID-tag.png" />
</div>

As tags RFID estão disponíveis em diferentes formatos e funcionalidades, cada uma adequada para diferentes aplicações. As tags podem ser classificadas em três categorias principais: passivas, semi-passivas e ativas. 

`Tags passivas` não possuem uma fonte interna de energia e dependem da energia fornecida pelo leitor para alimentar suas operações. Elas são pequenas, de baixo custo e são amplamente utilizadas em aplicações como controle de estoque e identificação de produtos. No entanto, seu alcance de leitura é limitado em comparação com outros tipos de tags. 

`Tags semi-passivas`, também conhecidas como tags com bateria assistida, possuem uma bateria interna que fornece energia para alguns componentes internos, como sensores. Essas tagssão comumente emopregadas em aplicações que requerem funcionalidades adicionais, como monitoramento de temperatura ou detecção de movimento. 

`Tags ativas` são alimentadas por uma fonte de energia interna, como uma bateria. Elas possuem um alcance de leitura estendido e podem suportar uma ampla variedade de recursos, como transmissão contínua de dados, sensores avançados e comunicação bidirecional. Essas tags são usadas em aplicações que demandam longo tempo de leitura e monitoramento constante, como rastreamento de ativos e logística. 


### Frequências

A comunicação RFID utiliza diferentes faixas de radiofrequência para estabelecer a comunicação entre os leitores e as tags.

As três principais faixas de frequências empregadas são: baixa frequência (`low frequency - LF`), alta frequência (`high frequency - HF`) e ultra-alta frequência (`ultra-high frequency - UHF`). 

No mercado existem múltiplas opções de tags, que variam conforme as frequências dos diferentes campos eletromagnéticos que elas foram projetadas para operar. A escolha da frequência adequada depende das necessidades específicas da aplicação, levando em consideração fatores como alcance, tamanho das tags, interferências possíveis e custos associados. 


1. **Low frequency tags (LF)** 

Opera na faixa de 125KHz a 134KHz e é amplamente utilizado em aplicações de curto alcance. Essa frequência é menos suscetível a interferências e possui uma capacidade razoável de penetração em materiais, tornando-a ideal para aplicações como controle de acesso, identificação animal e sistemas de pagamento sem contato. 

- campo geral de frequência: de 30 KHz até 300 KHz
- campo primário de frequência: de 125 KHz até 134 KHz
- campo de leiura: quase contato até 10cm  
- tem a menor capacidade de transferência de dados de todas as tags RFID
- armazena uma pequena quantidade de dados 
- custo médio da tag: de $0,75 a $5,00  

Aplicações: rastreio animal, controle de acesso, keyfob de carros, rastreio de bens. 

2. **High frequency tags (HF)**

Opera na faixa de 13,56KHz e é comumente empregada em aplicações que exigem um alcance de leitura moderado. Essa frequência é amplamente adotada em cartões de identificação, etiquetas inteligentes para varejo e sistemas de pagamento por proximidade.  

- campo primário de frequência: 13,56 MHz
- campo de leitura: quase contato até 30cm 
- podem ser lidas múltiplas tags simultaneamente
- armazenam até 4Kb de dados 
- podem ser facilmente lidas próximo a água, tecidos, metais, madeira, corpo humano.    
- custo médio da tag: $0,20 a $10,00 

Aplicações: Livros de biblioteca, cartões de identificação pessoal, bagagem despachada, cartões de crédito, chips de poker, aplicações NFC. 

3. **Ultra-high frequency tags (UHF)**

Opera nas faixas de 860MHz a 960MHz e é conhecida por seu alcance de leitura estendido. Essa faixa de frequência é comumente utilizada em aplicações de cadeia de suprimentos, rastreamento de ativos, logística e inventário, devido à sua capacidade de leitura rápida de várias tags em longas distâncias. 

Existem dois padrões diferentes de tags UFH: ativas e passivas 

3.1. **UHF passive tags**

- campo primário de frequência: de 860 MHz a 960 MHz
- campo de leitura: quase contato até 25m 
- alta capacidade de transferência de dados 
- grande variedade de encapsulamento e tamanhos 
- custo médio da tag: $0,09 a $20,00

Aplicações: rastreio de supply chain, manufatura, indústria farmaceutica, pedágio eletrônico, rastreio de estoque, contagem de tempo em corridas, rastreio de bens. 

3.2 **UHF active tags** 

- campo primário de frequência: de 433 MHz
- campo de leitura: quase contato até mais de 100m 
- grande capacidade de memória 
- alta capacidade de transferência de dados 
- custo médio da tag: $25,00 a $50,00

Aplicações: rastreio de veículos, manufatura automobilistica, construção, mineiração, rastreio de bens. 


### Padrões de comunicação 

Os padrões de comunicação RFID estabelecem regras e os protocolos para troca de dados entre leitores e tags. Dois dos principais padrões são o `EPC - Electronic Product Code` e o `ISO International Standards Organization`. 

- EPC: o pardão EPC é amplamente utilizado em aplicações de logística e de varejo. Ele define uma estrutura de dados e permite a identificação única de itens e o compartilhamento eficiente de informações ao longo da cadeia de suprimentos. O EPC utiliza o protocolo de comunicação EPCGlobal, que permite uma interação consistente entre os dispositivos RFID. 

- ISO: o padrão ISO é adotado em diversos setores, como transporte, saúde e indústria. Os padrões ISO mais comuns para RFID incluem a séria `ISO 14443`, utilizada em cartões de identificação e sistemas de pagamento por proximidade; e a série `ISO 18000`, que abrange especificações para dierentes frequências e aplicações de RFID.  


### Normativos 

Diversas organizações e normativos regulam o uso do RFID em diferentes regiões do mundo. Esses normativos estabelecem limites de potência, frequências permitidas e outras regulamentações para garantir a operação adequada da tecnologia RFID e evitar interferências prejudiciais a outros sistemas de comunicação. Alguns dos principais órgãos reguladores incluem: 

- `Federal Communicatios Commission (FCC)`: responsável pela regulamentação das comunicações nos Estados Unidos, incluindo a utilização de frequências RFID. 

- `European Telecommunications Standards Institute (ETSI)`: responsável pela definição dos padrões de comunicação para a Europa, incluindo os regulamentos para RFID. 

- `Agência Nacional de Telecomunicações (ANATEL)`: é o órgão regulador das telecomunicações no Brasil e estabelece as diretrizes para o uso da RFID no país. 

- Outros órgãos reguladores, como o `International Telecommunication Union (ITU)` e o `Japan RFID Promotion Council (JRC)`, também desempenham papéis importantes no estabelecimento de normativos e padrões para a tecnologia RFID.  



**RFID: resumo**

|Frequência|Tipo|Uso|Pros and contras|Distância|
|---------------|------|----------|---------------|--------|
|125-148 KHz|Passivo|Rastreio animal (ISO11784/11785), controle de acesso, e aplicações OEM| Sinal negocia bem em liquidos e metais. Maoir custo da tag por causa do longo tamanho da antena de cobre. |1,5cm a 10cm é típico. 15cm a 30cm ou mais é possível com equipamento especializado.|
|13.56 MHz|Passivo|EAS(anti-furto), livros e gestão documental, controle de acesso, aplicações OEM |Antenas podem ser impressas em substrato, diminuindo os custos da tag. Interferência severa causada por metal.| Pode ser de alguns centímetros até vários metros, dependendo do hardware da leitora e do tipo de tag.|
|433 MHz (and 2.5 GHz)|Ativo|Sistemas de pagamento de pedágio, gestão de veículos/frota, acompanhamento de bens etc. | Longa distância. Custo da tag muito alto. Utiliza bateria, portanto tags têm uma vida útil definida (geralmente 5 anos). | Normalmente ao redor de 10 metros, mas pode alcançar até uma centena de metros.|
|915 MHz|Passivo|Acompanhamento de supply chain e aplicações OEM|Tags muito baratas. Longa distância. Recurso anti-colisão permite a leitura de diversas tags simultâneas. Interferência grave de líquidos e do corpo humano| Em torno de 3m de uma antena única ou de 6m entre duas antenas. Distâncias mais longas podem ser feitas com hardware especial.

## Conclusão 

Neste documento exploramos os conceitos fundamentais da comunicação RFID, abrangendo as diferentes frequências utilizadas, os padrões de comunicação, os tipos de tags disponíveis, o alcance da tecnologia e os principais normativos relacionados. Essa tecnologia oferece uma solução poderosa para a identificação e o rastreamento em diversos setores, proporcionando maior eficiência e precisão em  processos como logística, cadeia de suprimentos, varejo, saúide e muito mais. Compreender esses conceitos é essencial para explorar e implementar soluções de RFID de forma eficaz em uma ampla gama de aplicações técnicas e práticas.   