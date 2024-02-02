// importando o modelo do banco de dados
const Sensor = require("../models/sensor");
// exportando o controller do sensor
module.exports = class SensorController {
  // sempre conferindo se está funcionando
  static async init(req, res) {
    res.send({message: "funcionando"});
  }
  // Sempre que ele receber um sinal dizendo que o sensor está ativado
  // ele irá gravar no banco de dados as informações recebidas
  static async sensorAtivado(req, res) {
    // recebe o nome e a distância
    const {nome, distancia} = req.body;
    // cria um sensor novo para o banco de dados
    const sensor = new Sensor({
      nome,
      distancia,
    });
    // tenta salvar, caso salve ele irá salvar o projeto no banco
    try {
      await sensor.save();
      // depois de salvar envia uma resposta para o esp8266
      res
        .status(201)
        .json({message: "Sensor enviado com sucesso", sensor: sensor});
    } catch (error) {
      // caso ele ache um erro ele envia uma mensagem dizendo que deu errado
      res.status(500).json({
        message:
          "Ocorreu um erro ao cadastrar o dado do sensor, tente novamente mais tarde",
      });
    }
  }
};
