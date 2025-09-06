/* ---- FUNCIONES DE UTILIDAD ---- */
#include "variable.h" // esto añade los pines a la ventana es opcional esto pero lo dejo por las dudas xd

/* --- FUNCIONES TESTEO --- */

void ReadQTR() {
  /* -- Solo LECTURA del sensor QTR -- */
  QTR.read(sensorValues);
  for(int i=0;i<8;i++){
    if(sensorValues[i]>umbral){
      SerialBT.print("□ (");
      Serial.print("□ (");
      SerialBT.print(sensorValues[i]);
      Serial.print(sensorValues[i]);
      SerialBT.print(")");
      Serial.print(")");
    } else {
      SerialBT.print("■ (");
      Serial.print("■ (");
      SerialBT.print(sensorValues[i]);
      Serial.print(sensorValues[i]);
      SerialBT.print(")");
      Serial.print(")");
    } 
    SerialBT.print("\t");
    Serial.print("\t");
  }
  SerialBT.println();
  delay(100);
}

void TestMotor(){
  /* --- Solo test de los motores */
  for(int i = 0; i < 2; i++){ // <--- ejecuta 3 veces el siguente codigo
    motores(50, 50); // <--- Esta parte cambia dependiendo del nombre de la funcion de los motores
    delay(1500);
    motores(50, 30);
    delay(1500);
    motores(30, 50);
    delay(1500);
    motores(-50, -50);
    delay(1500);
  }
  SerialBT.println("Test Motor TERMINADO - Pulse el boton para seguir con la Lectura QTR");
  while(digitalRead(BOTON) == 0) { // <--- Fijate el nombre de la variable de boton y cambialo si es necesario
    delay(10);
  }
}

/* --- TEST MOTORES Y TEST QTR COMBINADOS --- */
void TestAll(){
  for(int i = 0; i < 2; i++){ // <--- ejecuta 3 veces el siguente codigo
    motores(50, 50);
    delay(1500);
    motores(50, 30);
    delay(1500);
    motores(30, 50);
    delay(1500);
    motores(-50, -50);
    delay(1500);
  }
  SerialBT.println("Test Motor TERMINADO - Pulse el boton para seguir con la Lectura QTR");
  while(digitalRead(BOTON) == 0) { // <--- Fijate el nombre de la variable de boton y cambialo si es necesario
    delay(10);
  }
  for(int t = 0; t < 100; t++){
    QTR.read(sensorValues);
    for(int i=0;i<8;i++){
      if(sensorValues[i]>umbral){
          SerialBT.print("□ (");
          SerialBT.print(sensorValues[i]);
          SerialBT.print(")");
        } else {
          SerialBT.print("■ (");
          SerialBT.print(sensorValues[i]);
          SerialBT.print(")");
        } 
        SerialBT.print("\t");
      }
      SerialBT.println();
      delay(100);
  }
}

/* ---- FUNCIONES DE SEGUIMIENTO DE LINEA ---- */

void DynamicPosition(){ // arregla la variable para q lea posiciones xd
  QTR.read(sensorValues);
  posicion = QTR.readLineBlack(sensorValues);

  posicion = map(posicion, 0, 7000, -255, 255);
  
  SerialBT.println(posicion);
  delay(250);
  error = posicion;
}



void PositionFollow(){ // el seguidor de linea usando posiciones
  giro = kp * error;
  delay(10);
  izq = tp + giro;
  der = tp - giro;
  if(posicion>-40 && posicion<20){
    motores(izq, der);
    SerialBT.println("<- Avanzando ->");
  } else if(posicion>20 && posicion<245){
    motores(izq, der);
    SerialBT.println("<- Derecha ->");
  } else if(posicion>-145 && posicion<-40){
    motores(izq, der);
    SerialBT.println("<- Izquierda ->");
  } else if(posicion==-255 && posicion<-245){
    motores(izq, der);
    SerialBT.println("Izq Potente");
  } else if(posicion>245){
    motores(izq, der);
    SerialBT.println("Der Potente");
  }
  
}

void error(){ // funcion para avisar de un error de manera visual (No esta integrada)
  delay(300);
  digitalWrite(LED, HIGH);
  delay(300);
  digitalWrite(LED, LOW);
  delay(300);
  digitalWrite(LED, HIGH);
  delay(300);
  digitalWrite(LED, LOW);
  delay(300);
  digitalWrite(LED, HIGH);
  delay(300);
  digitalWrite(LED, LOW);
}
