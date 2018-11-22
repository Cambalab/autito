// Incluimos las librería
#include <AFMotor.h>
#include <NewPing.h>

int velocidad = 0;
int sonar_data = 0;
int masterTiempoActual = 0;
int masterTiempoInicial = 0;
int masterTiempoRetardo = 1000;

int accionTiempoActual = 0;
int accionTiempoInicial = 0;

int sonar_umbral = 15; // en centimetros

// Crea el objeto Motor y selecciona el 'puerto' ('port' en inglés) M1, M2, M3 or M4. En este caso, M1
AF_DCMotor motor_izq(1);
AF_DCMotor motor_der(3);
NewPing sonar(A0, A1, 200);

void setup() {
  Serial.begin(9600);
  // Definimos la velocidad para el motor
  motor_izq.setSpeed(255);
  motor_der.setSpeed(255);
 // Prendemos el motor
  motor_izq.run(RELEASE);
  motor_der.run(RELEASE);
}

void girar_izquierda(int delayTime) {
  accionTiempoActual = millis();
  if (accionTiempoActual - accionTiempoInicial >= delayTime) {
    Serial.println("girar_izquierda");
    motor_izq.run(FORWARD);
    motor_der.run(RELEASE);
    accionTiempoInicial = accionTiempoActual;
  }
}

void girar_derecha(int delayTime) {
  accionTiempoActual = millis();
  if (accionTiempoActual - accionTiempoInicial >= delayTime) {
    Serial.println("girar_derecha");
    motor_izq.run(RELEASE);
    motor_der.run(FORWARD);
    accionTiempoInicial = accionTiempoActual;
  }
}

void avanzar(int delayTime) {
  accionTiempoActual = millis();
  if (accionTiempoActual - accionTiempoInicial >= delayTime) {
    Serial.println("avanzar");
    motor_izq.run(BACKWARD);
    motor_der.run(FORWARD);
    accionTiempoInicial = accionTiempoActual;
  }
}

void retroceder(int delayTime) {
  accionTiempoActual = millis();
  if (accionTiempoActual - accionTiempoInicial >= delayTime) {
    Serial.println("retroceder");
    motor_izq.run(FORWARD);
    motor_der.run(BACKWARD);
    accionTiempoInicial = accionTiempoActual;
  }
}

void parar(int delayTime) {
  accionTiempoActual = millis();
  if (accionTiempoActual - accionTiempoInicial >= delayTime) {
    Serial.println("parar");
    motor_izq.run(RELEASE);
    motor_der.run(RELEASE);
    accionTiempoInicial = accionTiempoActual;
  }
}

bool camino_despejado() { // TRUE = camino libre
  Serial.println("camino_despejado");
    sonar_data = sonar.ping_cm();
    Serial.println(sonar_data);
    if (sonar_data > sonar_umbral) {
      return true;
    } else {
      return false;
    }
}

void buscar_salida() {
  Serial.println("buscar_salida");
  retroceder(500);
  girar_izquierda(1000);
  if (!camino_despejado()) {
    buscar_salida();
  }
}

void loop() {
  masterTiempoActual = millis();
  if (masterTiempoActual - masterTiempoInicial >= masterTiempoRetardo) {
    if(camino_despejado()) {
      avanzar(600);  
    } else {
      buscar_salida();
      parar(600);
    }
    masterTiempoInicial = masterTiempoActual;
  }
}
