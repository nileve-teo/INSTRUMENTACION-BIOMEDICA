# Laboratorio N.° 4 — Extracción de la envolvente de la sEMG simulada

**Universidad Nacional Mayor de San Marcos (UNMSM)**  
Facultad de Ingeniería Electrónica y Eléctrica — Escuela Profesional de Ingeniería Biomédica  
**Curso:** Instrumentación Biomédica I

---

## 1. Descripción y contexto

En este laboratorio se procesa de forma analógica la señal de electromiografía superficial (**sEMG**) simulada por el ESP32 (generada en el Laboratorio N.° 3 con tres tramos de 5 s: **reposo**, **cierre de mano** y **extensión del índice**) para extraer su **envolvente lineal**, la cual servirá como señal de entrada para el Laboratorio N.° 5.

Dado que la señal del DAC del ESP32 está montada sobre una componente continua (offset DC entre 0 V y 3.3 V) y que las amplitudes en reposo son inferiores al umbral de conducción de un diodo convencional ($\approx 0.6\text{ V}$), el sistema implementa:
1. **Acoplamiento capacitivo (filtro pasa-altos RC):** elimina la componente DC previa a la rectificación.
2. **Rectificador de precisión de media onda (superdiodo):** compensa la caída directa del diodo mediante realimentación negativa con amplificador operacional.
3. **Seguidor de tensión y filtro pasa-bajos RC:** aísla impedancias y suaviza el rizado de alta frecuencia para entregar una tensión continua proporcional a la actividad muscular ($V_E$).

---

## 2. Objetivos

* Obtener la envolvente de la sEMG simulada con un rectificador de precisión de media onda y un filtro RC pasa-bajos.
* Comparar la envolvente obtenida antes y después de eliminar la componente continua de la señal de entrada.
* Medir el nivel de la envolvente ($V_E$) en los tramos de reposo, cierre de mano y extensión del índice.

---

## 3. Estructura del repositorio

| Ruta / Archivo | Descripción |
| :--- | :--- |
| [`Firmware/`](./Firmware) | Carpeta con el código fuente del ESP32 (`Simulador_sEMG.ino` y la cabecera de datos `semg.h` a 2048 Hz). |
| [`README.md`](./README.md) | Documentación del desarrollo experimental, montaje y evidencias en osciloscopio. |

---

## 4. Componentes y equipos utilizados

* **Microcontrolador:** ESP32 DevKit V1 (salida DAC en `GPIO25`).
* **Amplificador operacional:** 1 × TL084N (A1: rectificador de precisión; A2: seguidor de tensión; A3 y A4: seguidores con entrada a GND).
* **Diodo:** 1 × 1N4148.
* **Resistencias:** 2 × $10\ \text{k}\Omega$ (rectificador y filtro de envolvente) y 1 × $1\ \text{M}\Omega$ (acoplamiento AC).
* **Capacitores:** 3 × $100\ \text{nF}$ cerámicos (dos de desacoplo en $\pm 9\text{ V}$ y uno de acoplamiento AC) y 1 × $10\ \mu\text{F}$ electrolítico (filtro pasa-bajos de envolvente).
* **Equipos:** Fuente de alimentación DC dual ($\pm 9\text{ V}$), osciloscopio digital de dos canales (acoplamiento DC) y protoboard.

---

## 5. Desarrollo experimental por etapas

### Etapa A — Señal de entrada (`GPIO25`)
Se energizó el ESP32 para reproducir la secuencia completa de 15 s (30 720 muestras a 2048 Hz) y se midió con el osciloscopio en `GPIO25` respecto a GND, verificando los tres tramos de actividad muscular montados sobre el nivel continuo del DAC.

### Etapa B — Rectificador y filtro de envolvente (sin acoplamiento AC)
Con el TL084N polarizado a $\pm 9\text{ V}$, se conectó directamente `GPIO25` a $V_{IN}$ pasando por el rectificador de precisión (A1), el seguidor de tensión (A2) y el filtro pasa-bajos RC ($10\ \text{k}\Omega$ y $10\ \mu\text{F}$), observando que la componente DC del DAC eleva el nivel base de $V_E$ en todos los tramos.

### Etapa C — Acoplamiento capacitivo
Se intercaló el filtro pasa-altos ($100\ \text{nF}$ en serie y $1\ \text{M}\Omega$ a GND) entre `GPIO25` y $V_{IN}$, eliminando el offset continuo y centrando la señal sEMG en $0\text{ V}$.

### Etapa D — Rectificación y envolvente con acoplo
Se registró la señal rectificada ($V_R$) y la envolvente final ($V_E$) tras eliminar la componente DC, midiendo mediante cursores el nivel de $V_E$ en reposo, cierre de mano y extensión del índice.

---

## 6. Evidencias experimentales

### Montaje en protoboard y registro audiovisual
* [Ver video del funcionamiento y montaje del simulador sEMG](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipNxO0_Rj69rjVSDuEO5cn5kDmwT-yixhfqbSEnA?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn)

### Mediciones en osciloscopio por tramos (cursores vertical y horizontal)

#### Secuencia completa de sEMG y envolvente (15 segundos)

<div align="center">
  <img width="720" alt="Secuencia completa de 15 segundos" src="https://github.com/user-attachments/assets/788507e7-11b4-4084-9562-3a65224b1011" />
  <br>
  <em>Captura general de los tres tramos consecutivos (15 s totales).</em>
</div>

<br>

#### Detalle por tramos de actividad muscular

| Tramo y actividad | Medición 1 | Medición 2 |
| :--- | :---: | :---: |
| **Primer tramo**<br>**Reposo** | <img width="380" alt="Tramo 1 - Reposo (1)" src="https://github.com/user-attachments/assets/ce3e971e-7b3c-4406-aed5-f771693dbf34" /> | <img width="380" alt="Tramo 1 - Reposo (2)" src="https://github.com/user-attachments/assets/2b30e4fb-7021-4081-9803-66948561a352" /> |
| **Segundo tramo**<br>**Cierre de mano** | <img width="380" alt="Tramo 2 - Cierre de mano (1)" src="https://github.com/user-attachments/assets/4351a693-8a23-4a86-adf3-c082f0800d29" /> | <img width="380" alt="Tramo 2 - Cierre de mano (2)" src="https://github.com/user-attachments/assets/d3e188b3-bc72-4f15-83c7-12d66cf9a25f" /> |
| **Tercer tramo**<br>**Extensión del índice** | <img width="380" alt="Tramo 3 - Extensión del índice (1)" src="https://github.com/user-attachments/assets/da73be69-b273-4cb4-8e24-083402ddb7f0" /> | <img width="380" alt="Tramo 3 - Extensión del índice (2)" src="https://github.com/user-attachments/assets/b8b8252d-fa7d-4095-8506-e804ba4fa41f" /> |
