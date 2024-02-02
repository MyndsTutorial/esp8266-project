// importando a biblioteca de rotas
const router = require("express").Router();
// importando o controlador
const LedController = require("../controllers/LedController");
// na rota / será usada a inicialização
router.get("/", LedController.init);
// no /state-led será usado pra enviar o estado do led
router.get("/state-led", LedController.ledState);
// exportando a rota
module.exports = router;
