// incluindo a biblioteca de cron para controlar o led piscar
const cron = require("cron");
// váriavel que diz o estado do led
let ledState = false;
// função responsável por trocar o estado do led
const toggleLED = () => {
  ledState = !ledState;
  // Code to control the LED goes here
  console.log(`LED state: ${ledState}`);
};
// criando um  cronometro para a cada 1 segundo trocar o estado do led
const job = new cron.CronJob("*/1 * * * * *", toggleLED);
// iniciando o cron
job.start();
// expostando o controlador responsável por chamar a função
module.exports = class ProductsController {
  // função inicial para saber que o servidor está funcionando
  static async init(req, res) {
    // enviando a resposta em formato json
    res.send({message: "funcionando"});
  }
  // função para colocar o estado do led para fora
  static async ledState(req, res) {
    res.json({state: ledState});
  }
};
