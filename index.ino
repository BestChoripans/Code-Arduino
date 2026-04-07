// Librerias y Variable.h
#include <QTRSensors.h>
#include "variable.h"

// -- Activar/Desactivar BLUETOOTH (PARA ENTORNO DE COMPETENCIA) -- //
#define USE_BLUETOOTH  // Comentar esta linea para usar el Serial via USB antes que el bluetooth

#ifdef USE_BLUETOOTH
  #include <BluetoothSerial.h>
  BluetoothSerial SerialBT;
  // No se si funciona luego probare que tal anda XD
  #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
  #error Fallo de Bluetooth
  #endif
#else
  #define SerialBT Serial
#endif


/* Variable QTR */
QTRSensors QTR;

/* -- Variabless -- */
int umbral = 3000;
int posicion;

/* --- Variables Sensores --- */
const uint8_t SensorNum = 8;
uint16_t sensorValues[SensorNum];

/* --- Config para ESP32 --- */
const int freq = 5000;
const int resolution = 8;

/* --- PID Variables --- */
const float kp = 0.15;
const int tp = 20;

int error;
int izq;
int der;
int giro;

void setup() {
  motorSetup();
  SerialBT.begin("Balatro Dinamico");
  Serial.begin(9600);
  /* QTR Setup */
  QTR.setTypeAnalog();
  QTR.setSensorPins((const uint8_t[]){36, 39, 34, 35, 32, 33, 25, 26}, SensorNum);
  QTR.setEmitterPin(27);
  /* QTR CALIBRAR */
  pinMode(LED, OUTPUT);
  pinMode(BOTON, INPUT);
  digitalWrite(LED, HIGH);
  for(int i = 0; i < 200; i++) {
    QTR.calibrate();
    delay(10);
  }
  digitalWrite(LED, LOW);
  while(digitalRead(BOTON) == 0) {
    delay(10);
  }
  SerialBT.println("Se ha presionado el BOTON");
  delay(1000);
}

void loop() {
  DynamicPosition();
  PositionFollow();
}
