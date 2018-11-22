# Vehículo controlado con Arduino
## Hacklab Camba

### **Resumen**
El objetivo del taller es hacer un vehiculo utilizando Arduino, 2 motores de corriente continua, un shield para controlar los motores y un sensor de ultrasonido.

![Imagen Ilustrativa](arduinoponia_bb.png "Imagen ilustrativa")

### **Elementos necesarios**
- Arduino UNO
- Shield L239

**Medidor de Humedad del sustrato: **
- Clavos, preferentemente galvanizados, para evitar que se oxiden.


**Sistema de riego por goteo:**
- Botella de agua o un tetrabrick a modo de tanque de agua.
- Mangueras de plastica de 6mm de diametro externo y 4mm interno.
- Conecciones de 3 vias (tambien de acuario gg)
- Pistola de calor para sellar la union de la manguera con el tanque.

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
