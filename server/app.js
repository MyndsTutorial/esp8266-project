// importando a biblioteca de appa
const express = require("express");
// importando biblioteca de permissão
const cors = require("cors");
// criando o backend
const app = express();
// criando a variável da porta
const port = 3000;
// importando a váriavel da rota de led
const LedRouter = require("./routes/ledRoutes");
// importando a váriavel da rota de sensores
const SensorRouter = require("./routes/sensorRoutes");
// importando as configurações do de privacidade
require("dotenv").config();
// usando a proteção de rede
app.use(cors());
// permitindo comunicação com jsons
app.use(express.json());
// usando a rota de led no endereço /led
app.use("/led", LedRouter);
// usando a rota de sensor no endereço /sensor
app.use("/sensor", SensorRouter);
// criando a rota de api
app.get("/api", (req, res) => {
  const response = {message: "success", led: true};
  res.json(response);
});
// fazendo o app rodar na porta escolhida e dizendo aonde ele está rodando
app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
// executando a conexão do banco de dados
require("./database/connection");
