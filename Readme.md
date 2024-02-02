# Aula 2

### Primeiro vamos dividir a aula em 5 partes

<ol>
    <li><a href="#part1">Explicação da dinamica da aula</a></li>
    <li><a href="#part2">Código</a></li>
    <li><a href="#part3">Explicações extras</a></li>
    <li><a href="#part4">Testando a api</a></li>
    <li><a href="#part5">Como criar a pasta server:</a></li>
</ol>

### 1 <span id="part1"> Explicação da dinamica da aula </span>

Vamos criar o servidor para poder salvar os sensores de contato do nosso carrinho, então nesta aula vamos rodar um servidor na porta 3000 e tentar se comunicaar com ele

<img src="./slides/introduction.png"/>

Agora que quando nós trabalhamos com servidores, existem tipos de conexão que se pode fazer, um dos jeitos de se comunicar é via métodos HTTP que são requisições de web:

<img src="./slides/requests.png"/>

Nesta aula usaremos 2 tipos de requisição o GET e o POST

### 2 <span id="part2"> Código </span>

As explicações sobre o que o código faz em especifico estão documentadas em comentários então é só ir até o <a href="./server/app.js"> código</a> e olhar as pastas que estão dentro do server. As unicas desnecessárias são os packages e tudo dentro do node_modules

### 3 <span id="part3"> Explicações extras: </span>

O servidor será um servidor nodejs que iremos subir na aula sempre precisará estar online, não é muito amigável subir o servidor no localhost:3000 e tentar acessar ele via rede wifi com placa e posicionamento de endereço, para facilitar o endereço dos alunos vamos subir online no render e acessar via http requests

### 4 <span id="part4"> Testando a api </span>

### 5 <span id="part5"> Como criar a pasta server: </span>

Primeiro precisamos ir para uma pasta vazia:

<img src="./slides/server1.png">

Depois precisamos iniciar o arquivo de configuração:

<img src="./slides/server2.png">

Instalar todas as bibliotecas que vamos precisar:

<img src="./slides/server3.png">

Criar os scripts para executar o servidor:

<img src="./slides/server4.png">

E iniciar o servidor:

<img src="./slides/server5.png">
