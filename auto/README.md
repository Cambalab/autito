# Vehículo controlado con Arduino
## Hacklab Camba

### **Resumen**
El objetivo del taller es hacer un vehiculo utilizando Arduino, 2 motores de corriente continua, un shield para controlar los motores y un sensor de ultrasonido.

![Imagen Ilustrativa](arduinoponia_bb.png "Imagen ilustrativa")

### **Elementos necesarios**

### Lista de materiales

- [ ] [2 motores con sus respectivas ruedas](https://electronica.mercadolibre.com.ar/componentes-electronicos/arduino/motor-con-rueda-arduino)
- [ ] [1 Arduino Uno](https://listado.mercadolibre.com.ar/arduino-uno#D[A:arduino%20uno])
- [ ] [ 1 Shield Motor L293](https://listado.mercadolibre.com.ar/shield-motor-l293#D[A:shield%20motor%20l293])
- [ ] [1 Sensor HC-SR04](https://listado.mercadolibre.com.ar/hc-sr04#D[A:hc%20sr04])
- [ ] [1 jack de Bateria 9v para arduino](https://listado.mercadolibre.com.ar/jack-de-bateria-arduino#D[A:jack%20de%20bateria%20arduino])
- [ ]["Rueda Loca"](https://articulo.mercadolibre.com.ar/MLA-647108487-rueda-loca-arduino-_JM?quantity=1)
- [ ] [Base-"Chasis" del auto](assets/baseMadera.jpg)
- [ ] [4 Cables "Hembra-Macho" pin](assets/cableMH.jpg)
- [ ] [4 Cables  para conectar el motor con el shield]()

##### Documentación
* [Libreria HC-SR04](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home)
* [Libreria Motor](https://learn.adafruit.com/adafruit-motor-shield/af-dcmotor-class)



**A**


**Interfaz de usuario:**

- **3 leds Amarillos** representan la lista de los *sensores disponibles*. El led apagado indica que el sensor esta desconectado. El led encendido indica que el sensor esta conectado y el led titilante indica que el sensor esta *seleccionado*.
- **3 leds Verdes** representan el *valor actual* que esta midiendo el *sensor seleccionado* en una medida de 0 a 100%.
- **1 leds azules** representa el *Actuador*, de igual manera que los sensores, titilara para indicar que ese *esta Activo*.
- **1 boton** nos permitira *seleccionar* los diferentes sensores.
- **1 shift-registers (74HC595)** nos permitira utilizar unos pocos pines del arduino para controlar todos los leds.
- **7 resistencias de 470ohm** para protejer los leds.
- **1 resistencias de 1Kohm** para protejer los leds.

### **Links utiles**
https://playground.arduino.cc/Code/NewPing
