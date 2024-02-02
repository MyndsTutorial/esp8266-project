# Aula 2 - Servidor

### Primeiro vamos dividir a aula em 5 partes

<ol>
    <li><a href="#part1">Explicação da dinamica da aula</a></li>
    <li><a href="#part2">Código</a></li>
    <li><a href="#part3">Explicações extras</a></li>
    <li><a href="#part4">Como criar a pasta server:</a></li>
    <li><a href="#part5">Como criar o banco de dados:</a></li>
    <li><a href="#part6">Testando a api</a></li>
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

### 4 <span id="part4"> Como criar a pasta server: </span>

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

### 5 <span id="part5"> Como criar o banco de dados: </span>

Precisamos ir até o site do <a href="https://www.mongodb.com/atlas/database"> mongoDB </a> e registrar com o GMAIL do aluno, caso o aluno não tenha um gmail próprio o professor pode criar

Criar um banco de dados <b>SEMPRE GRATUITO</b>

<img src="./slides/mongo1.png">

Escolher a região de são paulo e dar um nome:

<img src="./slides/mongo2.png">

Caso já tenha um banco criado etc para criar um novo é só ir ali no novo projeto:

<img src="./slides/mongo3.png">

Crie um usuário para usar o banco de dados. Não adianta usar o meu usuário irei deletar o banco após o tutorial

<img src="./slides/mongo4.png">

Permita que qualquer IP possa acessar o banco de dados, assim o esp8266 pode se comunicar com o banco:

<img src="./slides/mongo5.png">

Agora clique para se conectar ao banco

<img src="./slides/mongo6.png">

Vamos clicar em drivers

<img src="./slides/mongo7.png">

Copiar o link do banco:

<img src="./slides/mongo8.png">

E configurar o .env do projeto:

<img src="./slides/mongo9.png">

Agora para finalizar quando iniciar o servidor, se tudo deu certo verá que o banco de dados está conectado:

<img src="./slides/mongo10.png">

### 6 <span id="part6"> Testando a api </span>

Para Testar a api vamos usar o app <a href="https://insomnia.rest/download">insomnia</a>:

Vamos primeiro de tudo criar uma requisição do tipo GET para pegar os dados em http://localhost:3000/api . Não podemos esquecer que o servidor tem que estar rodando:

<img src="./slides/insomnia1.png">

Agora vamos testar se a rota do led está funcionando:

<img src="./slides/insomnia2.png">

Vamos checar agora o sinal do led se está apagado(false) ou aceso(true)

<img src="./slides/insomnia3.png">

Repare que também poderá trocar o valor recebido na direita:

<img src="./slides/insomnia4.png">

Agora vamos testar se a rota do sensor está funcionando:

<img src="./slides/insomnia5.png">

Vamos criar um tipo de requisição POST igual está na <a href="./server/routes/sensorRoutes.js"> rota de acesso do sensor</a> para isso precisamos de um body, para colocar um corpo na requisição, ou seja as informações que queremos passar, que será um formato conhecido como json:

<img src="./slides/insomnia6.png">

Preenchendo o json e enviando já recebemos a confirmação que foi salvo no banco:

<img src="./slides/insomnia7.png">

Para confirmar se realmente foi salvo no banco vamos até ele checar, e já vemos que realmente agora existe um gráfico de mensagens:

<img src="./slides/insomnia8.png">

E por fim indo até as collections do banco, aonde é armazenado os dados já temos o dado lá:

<img src="./slides/insomnia9.png">
