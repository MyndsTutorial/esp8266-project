// importando a biblioteca de rotas
const router = require("express").Router();
// importando o controlador
const SensorController = require("../controllers/SensorController");
// rota para checar se está funcionando
router.get("/", SensorController.init);
// rota para criar o sensor
router.post("/acesso", SensorController.sensorAtivado);
// exportando a rota
module.exports = router;
