// Incluimos las librería
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

int sonar_data = 0; // Esta variable guardara el valor de sensado del ultrasonido.
int mirandoDerecha = false; // Usamos esta variable para recordar en que direccion giro el robot por ultima vez.
int mirandoAtras = false; // Usamos esta variable para recordar en que direccion el robot esta mirando.
int pos = 0;    // Guarda la posicion del Servo
int sonarUmbral = 40; // en centimetros

// Creamos los objetos Motor_izq y Motor_der y selecciona el 'puerto' ('port' en inglés) M1, M2, M3 or M4. En este caso, M1 y M3
AF_DCMotor motorIzq(1);
AF_DCMotor motorDer(3);
NewPing sonar(A0, A1, 200); // Creamos un objeto sonar.
Servo myservo;  // Creamos un objeto servo.

void setup() {
  Serial.begin(9600);
  // Definimos la velocidad para el motor
  motorIzq.setSpeed(70);
  motorDer.setSpeed(110);
 // Prendemos los motores
  motorIzq.run(RELEASE);
  motorDer.run(RELEASE);

  myservo.attach(9);  // Vinculamos el servo al pin 9 (Servo #2 en el shield)
}

void girarIzquierda(int delayTime) {
  Serial.println("girarIzquierda");
  mirandoDerecha = false;
  motorIzq.run(FORWARD);
  motorDer.run(RELEASE);
  delay(delayTime);
}

void girarDerecha(int delayTime) {
  Serial.println("girarDerecha");
  mirandoDerecha = true;
  motorIzq.run(RELEASE);
  motorDer.run(FORWARD);
  delay(delayTime);
}

void avanzar(int delayTime) {
  Serial.println("avanzar");
  mirandoAtras = false;
  if (caminoDespejado()) {
    motorIzq.run(BACKWARD);
    motorDer.run(FORWARD);
    delay(delayTime);
  } else {
    parar(500);
    retroceder(delayTime);
    buscarSalida();
  }
}

void retroceder(int delayTime) {
  Serial.println("retroceder");
  mirandoAtras = true;
  if (caminoDespejado()) {
    motorIzq.run(FORWARD);
    motorDer.run(BACKWARD);
    delay(delayTime);
  } else {
    parar(500);
    buscarSalida();
  }
}

void parar(int delayTime) {
  Serial.println("parar");
  motorIzq.run(RELEASE);
  motorDer.run(RELEASE);
  delay(delayTime);
}

bool caminoDespejado() { // TRUE = camino libre
    if (mirandoAtras) {
      Serial.println("mirandoAtras");
      myservo.write(180);  // MIRAR ATRAS
    } else {
      Serial.println("mirandoAdelante");
      myservo.write(0); // MIRAR ADELANTE
    }
    sonarData = sonar.ping_cm();
    if (sonarData > 0) { // FILTRA LOS CEROS DE LAS LECTURAS.
     Serial.println(sonarData);
     if (sonarData > sonarUmbral) {
        Serial.println("caminoDespejado");
        return true;
      } else {
        Serial.println("camino_bloqueado");
        return false;
      }
    } else {
      return true;
    }
}

void buscarSalida() {
  if (mirandoDerecha) {
    girarIzquierda(500);
    parar(1000);
  } else {
    girarDerecha(500);
    parar(1000);
  }
}

void loop() {
  avanzar(200);
}
