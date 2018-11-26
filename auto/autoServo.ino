// Incluimos las librería
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>


int velocidad = 0;
int sonar_data = 0;
int sonar_data_frente = 0;
int sonar_data_atras = 0;
int sonar_data_izquierda = 0;
int sonar_data_derecha = 0;
int mirandoDerecha = false;
int mirandoAtras = false;
int pos = 0;    // variable to store the servo position
int sonar_umbral = 40; // en centimetros

// Crea el objeto Motor y selecciona el 'puerto' ('port' en inglés) M1, M2, M3 or M4. En este caso, M1
AF_DCMotor motor_izq(1);
AF_DCMotor motor_der(3);
NewPing sonar(A0, A1, 200);
Servo myservo;  // create servo object to control a servo

void setup() {
  Serial.begin(9600);
  // Definimos la velocidad para el motor
  motor_izq.setSpeed(70);
  motor_der.setSpeed(110);
 // Prendemos el motor
  motor_izq.run(RELEASE);
  motor_der.run(RELEASE);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void girar_izquierda(int delayTime) {
  Serial.println("girar_izquierda");
  mirandoDerecha = false;
  motor_izq.run(FORWARD);
  motor_der.run(RELEASE);
  delay(delayTime);
}

void girar_derecha(int delayTime) {
  Serial.println("girar_derecha");
  mirandoDerecha = true;
  motor_izq.run(RELEASE);
  motor_der.run(FORWARD);
  delay(delayTime);
}

void avanzar(int delayTime) {
  Serial.println("avanzar");
  mirandoAtras = false;
  if (camino_despejado()) {
    motor_izq.run(BACKWARD);
    motor_der.run(FORWARD);
    delay(delayTime);
  } else {
    parar(500);
    retroceder(delayTime);
    buscar_salida();
  }
}

void retroceder(int delayTime) {
  Serial.println("retroceder");
  mirandoAtras = true;
  if (camino_despejado()) {
    motor_izq.run(FORWARD);
    motor_der.run(BACKWARD);
    delay(delayTime);    
  } else {
    parar(500);
    buscar_salida();
  }
}

void parar(int delayTime) {
  Serial.println("parar");
  motor_izq.run(RELEASE);
  motor_der.run(RELEASE);
  delay(delayTime);
}

bool camino_despejado() { // TRUE = camino libre
    if (mirandoAtras) {
      Serial.println("mirandoAtras");
      myservo.write(180);  // MIRAR ATRAS
    } else {
      Serial.println("mirandoAdelante");
      myservo.write(0); // MIRAR ADELANTE
    }
    sonar_data = sonar.ping_cm();
    if (sonar_data > 0) { // FILTRA LOS CEROS DE LAS LECTURAS.
     Serial.println(sonar_data);
     if (sonar_data > sonar_umbral) {
        Serial.println("camino_despejado");
        return true;
      } else {
        Serial.println("XXX camino_bloqueado");
        return false;
      }
    } else {
      return true;
    }
}

void buscar_salida() {
  if (mirandoDerecha) {
    girar_izquierda(500);
    parar(1000);
  } else {
    girar_derecha(500);
    parar(1000);
  }
}

void loop() {
  avanzar(200);
  
}
