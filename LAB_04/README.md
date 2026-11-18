# Laboratorio N.° 4 — Rectificación de precisión y extracción de envolvente de señales sEMG

**Curso:** Instrumentación Biomédica I  
**Integrantes:** Condor Caruajulca Evelin-23190118  
**Docente:** Armas Alvaraado Maria

---

## 1. Objetivo
Implementar y caracterizar una etapa analógica de acondicionamiento para señales electromiográficas de superficie (sEMG) generadas mediante el DAC de un ESP32, evaluando el efecto de la componente continua (*offset* DC), el acoplamiento capacitivo (filtro pasa-altos RC), la rectificación de precisión de media onda y la extracción de envolvente mediante un filtro pasa-bajos RC.

---

## 2. Materiales y equipos
* Microcontrolador **ESP32** (`GPIO25` como salida DAC a 2048 Hz, secuencia de 15 s).
* Circuito integrado **TL084N** (cuádruple amplificador operacional con entradas JFET).
* Diodo de conmutación rápida **1N4148**.
* Resistencias: $10\ \text{k}\Omega$ (×3) y $1\ \text{M}\Omega$ (×1).
* Capacitores: cerámico de $100\text{ nF}$ (×3, incluyendo desacoplo de alimentación) y electrolítico de $10\ \mu\text{F}$ (×1).
* Fuente de alimentación DC dual en modo *tracking* ($\pm 9\text{ V}$).
* Osciloscopio digital **GW Instek** de dos canales, protoboard y cables de conexión.

---

## 3. Estructura del repositorio
* **[`Firmware/`](./Firmware/)**: Código fuente del simulador sEMG en Arduino (`Simulador_sEMG.ino` y archivo de muestras `semg.h`).
* `README.md`: Documentación del desarrollo experimental, mediciones por etapa y análisis de resultados.

---

## 4. Desarrollo experimental por etapas

### Etapa A — Señal de entrada (`GPIO25`)

Se energizó el ESP32 para reproducir la secuencia completa de 15 s (30 720 muestras a 2048 Hz) y se midió con el osciloscopio en `GPIO25` respecto a `GND` (acoplamiento DC, escala horizontal de $2\text{ s/div}$), verificando los tres tramos de actividad muscular montados sobre el nivel continuo del DAC.

* **Valores medidos en `GPIO25`:**
  * **Valor medio ($V_{\text{medio}}$):** $2.17\text{ V}$
  * **Tensión máxima ($V_{\text{máx}}$):** $3.14\text{ V}$
  * **Tensión mínima ($V_{\text{mín}}$):** $80.0\text{ mV}$

* **Evidencia:**

<p align="center">
  <img width="750" alt="20261031_141044" src="https://github.com/user-attachments/assets/dce7c73e-53a0-4e55-ba29-df00558fd432" />
</p>

> 🎥 **Video de reproducción de la secuencia completa (Etapa A):** [Ver grabación en Google Photos](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipNxO0_Rj69rjVSDuEO5cn5kDmwT-yixhfqbSEnA?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn)

* **Análisis de la etapa:**
  La señal generada por el ESP32 presenta los tres tramos esperados (reposo, cierre de mano y extensión del índice), pero oscila completamente montada sobre un nivel de tensión continua (*offset* DC) positivo de **$2.17\text{ V}$**, sin cruzar por cero. Esto se debe a que el conversor digital-analógico (DAC) de 8 bits del ESP32 es unipolar ($0\text{ V}$ a $3.3\text{ V}$). Este desplazamiento continuo demuestra la necesidad de incorporar un filtro pasa-altos de acoplamiento capacitivo antes de la rectificación para evitar que el nivel DC sea interpretado como actividad muscular permanente.

---

### Etapa B — Rectificador y filtro de envolvente (sin acoplamiento AC)

Se polarizó el circuito integrado TL084N con $\pm 9\text{ V}$ (con capacitores de desacoplo de $100\text{ nF}$ a `GND`), conectando `GPIO25` directamente a la entrada no inversora $V_{IN}$ del rectificador de precisión de media onda (`A1` + 1N4148), seguido por el seguidor de tensión (`A2`) y el filtro pasa-bajos RC ($10\ \text{k}\Omega$ y $10\ \mu\text{F}$).

* **Valores medidos:**
  * **Entrada $V_{IN}$ (`CH1`):** $V_{\text{medio}} = 2.19\text{ V}$, $V_{\text{máx}} = 3.16\text{ V}$, $V_{\text{mín}} = 80.0\text{ mV}$.
  * **Salida rectificada $V_R$ (`CH2`):** $V_{\text{medio}} = 2.24\text{ V}$, $V_{\text{máx}} = 3.22\text{ V}$.
  * **Nivel de envolvente $V_E$ en los tres tramos:** Permanece anclado alrededor de $\approx 2.2\text{ V}$ con variaciones mínimas respecto al nivel continuo de entrada.

* **Evidencia:**

<p align="center">
  <img width="750" alt="20261031_152239" src="https://github.com/user-attachments/assets/54edce1b-f2fb-4326-89a9-32f3c2861429" />
</p>

> 🎥 **Video de medición en osciloscopio (Etapa B):** [Ver grabación en Google Photos](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipPoPkU4u93Op4r-G7tUUrkkUbX3RrXWOTsXvl8m?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn)

* **Análisis de la etapa:**
  Al no bloquear previamente la componente continua, toda la señal de entrada permanece en el semiplano positivo ($V_{IN} > 0\text{ V}$), provocando que el diodo 1N4148 conduzca durante todo el ciclo sin recortar semiciclos negativos. Como resultado, $V_R$ replica íntegramente a $V_{IN}$ y la envolvente $V_E$ queda dominada por el *offset* DC cercano a $2.2\text{ V}$, impidiendo discriminar claramente los niveles de contracción muscular.

---

### Etapa C — Acoplamiento capacitivo (filtro pasa-altos RC)

Se intercaló un capacitor cerámico de **$100\text{ nF}$** en serie entre `GPIO25` y $V_{IN}$, junto con una resistencia de **$1\ \text{M}\Omega$** entre $V_{IN}$ y `GND` ($f_c \approx 1.59\text{ Hz}$).

* **Valores medidos:**
  * **Valor medio antes del acoplo (`GPIO25`):** $\approx 2.17\text{ V}$.
  * **Valor medio después del acoplo ($V_{IN}$):** $\approx 0\text{ V}$ (señal centrada simétricamente alrededor de $0\text{ V}$).

* **Análisis de la etapa:**
  El capacitor bloquea la componente continua ($0\text{ Hz}$) mientras que la resistencia de $1\ \text{M}\Omega$ fija la referencia en $0\text{ V}$ sin atenuar las frecuencias útiles de la señal sEMG ($20\text{ Hz} - 500\text{ Hz}$), dejando disponibles semiciclos positivos y negativos reales para el rectificador.

---

### Etapa D — Rectificación y extracción de envolvente con acoplo

Con la señal centrada en $0\text{ V}$, se verificó el recorte de semiciclos negativos en $V_R$ ($2\text{ ms/div}$) y se midió la envolvente resultante $V_E$ mediante cursores en cada tramo de la secuencia completa ($2\text{ s/div}$).

* **Niveles medidos de $V_E$ por tramo:**
  * **Tramo 1 — Reposo (0 – 5 s):** $V_E \approx 200\text{ mV}$ (nivel basal constante)[cite: 4].
  * **Tramo 2 — Cierre de mano (5 – 10 s):** $V_{E,\text{máx}} \approx 1.07\text{ V}$ (pico inicial) y nivel sostenido elevado en el resto del tramo[cite: 4].
  * **Tramo 3 — Extensión del índice (10 – 15 s):** Escalón intermedio claramente diferenciable respecto al reposo y al cierre de mano[cite: 4].

* **Evidencia:**

> 🎥 **Registro de envolvente $V_E$ con acoplamiento AC (Etapa D):** [Ver captura/grabación en Google Photos](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipOx0t31DjrU3ObBoyPQESon_wIOFUEQwWhfNzIK?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn)

* **Análisis de la etapa:**
  Tras eliminar el *offset* DC, el rectificador de precisión elimina los semiciclos negativos ($V_R = 0\text{ V}$ cuando $V_{IN} < 0\text{ V}$) sin caída de tensión por umbral de diodo, permitiendo que el filtro pasa-bajos RC ($f_c \approx 1.59\text{ Hz}$) extraiga una envolvente lineal limpia y proporcional a la intensidad de contracción muscular[cite: 4].
---

## 5. Evidencias experimentales adicionales

### Montaje en protoboard y secuencia completa (15 segundos)
* [Ver video del funcionamiento y montaje del simulador sEMG](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipNxO0_Rj69rjVSDuEO5cn5kDmwT-yixhfqbSEnA?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn)

<div align="center">
  <img width="720" alt="Secuencia completa de 15 segundos" src="https://github.com/user-attachments/assets/788507e7-11b4-4084-9562-3a65224b1011" />
  <br>
  <em>Captura general de los tres tramos consecutivos con acoplamiento AC y envolvente (15 s totales).</em>
</div>
