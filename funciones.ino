/* ---- FUNCIONES DE UTILIDAD ---- */
#include "variable.h" // esto añade los pines a la ventana es opcional esto pero lo dejo por las dudas xd

void ReadQTR() {
  /* -- LECTURA QTRSensors -- */
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

/* Aqui dejo algunos comentarios si deseas adaptar esta funcion a tu codigo */
void TestAll(){
  for(int i = 0; i < 3; i++){ // <--- ejecuta 3 veces el siguente codigo
    motores(100, 100); // <--- Esta parte cambia dependiendo del nombre de la funcion de los motores
    delay(500);
    motores(50, 100);
    delay(500);
    motores(100, 50);
    delay(500);
    motores(-100, -100);
    delay(500);
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

void DynamicPosition(){ // arregla la variable para q lea posiciones xd
  QTR.read(sensorValues);
  posicion = QTR.readLineBlack(sensorValues);

  posicion = map(posicion, 0, 7000, -255, 255);

  SerialBT.println(posicion);
  delay(250);
}

/* ---- FUNCIONES PARA SEGUIDORES DE LINEA ---- */

void PositionFollow(){ // el seguidor de linea usando posiciones
   if(posicion>-40 && posicion<20){
    motores(30,30);
    SerialBT.println("<- Avanzando ->");
  } else if(posicion>20){
    motores(25,5);
    SerialBT.println("<- Derecha ->");
  } else if(posicion>-130 && posicion<-40){
    motores(5,25);
    SerialBT.println("<- Izquierda ->");
  }
}

/*
void seguidor6() {
  if(sensorValues[0]<umbral && sensorValues[1]<umbral && sensorValues[2]<umbral && sensorValues[3]>umbral && sensorValues[4]>umbral && sensorValues[5]<umbral && sensorValues[6]<umbral && sensorValues[7]<umbral){
  motores(50, 50);
  SerialBT.println("<- Avanzando ->");
  }
  else if(sensorValues[0]<umbral && sensorValues[1]>umbral && sensorValues[2]>umbral && sensorValues[3]>umbral && sensorValues[4]<umbral && sensorValues[5]<umbral && sensorValues[6]<umbral && sensorValues[7]<umbral
  ){
  motores(60, 40);
  SerialBT.println("izquierda suave");
  }else if(sensorValues[0]>umbral && sensorValues[1]>umbral && sensorValues[2]<umbral && sensorValues[3]<umbral && sensorValues[4]<umbral && sensorValues[5]<umbral && sensorValues[6]<umbral && sensorValues[7]<umbral){
  motores(70, 30);
  SerialBT.println("izquierda fuerte");
  }
  else if(sensorValues[0]<umbral && sensorValues[1]<umbral && sensorValues[2]<umbral && sensorValues[3]<umbral && sensorValues[4]<umbral && sensorValues[5]>umbral && sensorValues[6]>umbral && sensorValues[7]<umbral){
  motores(40, 60);
  SerialBT.println("derecha suave");
  }
  else if(sensorValues[0]<umbral && sensorValues[1]<umbral && sensorValues[2]<umbral && sensorValues[3]<umbral && sensorValues[4]<umbral && sensorValues[5]<umbral && sensorValues[6]>umbral && sensorValues[7]>umbral){
  motores(30, 70);
  SerialBT.println("derecha fuerte");
  }
  else{
    motores(0,0);
    SerialBT.println("stop");
    error();
    }
  delay(100);
}
*/

void error(){ // funcion para avisar de un error de manera visual
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
