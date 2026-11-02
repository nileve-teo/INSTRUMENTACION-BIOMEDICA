#include "semg.h"

// Pin DAC del ESP32 clásico
const int DAC_PIN = 25;

// Variables de reproducción
uint32_t indice = 0;
uint32_t siguienteMuestra;
uint32_t resto = 0;

void setup() {
  Serial.begin(115200);

  // Inicializar temporización
  siguienteMuestra = micros();

  Serial.println("Simulador sEMG iniciado");
  Serial.println("Frecuencia: 2048 Hz");
  Serial.println("Duracion: 15 segundos");
}

void loop() {

  if ((int32_t)(micros() - siguienteMuestra) >= 0) {

    // Enviar muestra al DAC
    dacWrite(DAC_PIN, SEMG[indice]);

    // Avanzar al siguiente instante programado
    siguienteMuestra += 1000000UL / FS_SEMG;

    // Compensar la fracción de microsegundo
    resto += 1000000UL % FS_SEMG;

    if (resto >= FS_SEMG) {
      siguienteMuestra++;
      resto -= FS_SEMG;
    }

    // Avanzar índice
    indice++;

    // Reiniciar al finalizar las 30720 muestras
    if (indice >= N_SEMG) {
      indice = 0;
      Serial.println("Reproduccion reiniciada");
    }
  }
}