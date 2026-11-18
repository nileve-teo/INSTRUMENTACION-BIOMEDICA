# Laboratorio 04: Instrumentación Biomédica I

## Extracción de la envolvente de una señal sEMG simulada

En este laboratorio se realiza el acondicionamiento de una señal de electromiografía superficial (sEMG) simulada mediante un ESP32. Se implementan las etapas de rectificación y filtrado para obtener la envolvente de la señal, que permite observar la variación de la actividad muscular.

## 1. Objetivo

Obtener la envolvente de una señal sEMG simulada mediante etapas de rectificación y filtrado analógico, verificando el comportamiento de las señales en cada etapa con ayuda del osciloscopio.

## 2. Archivos del laboratorio

| Archivo | Descripción |
|---|---|
| `Simulador_sEMG.ino` | Código para generar la señal sEMG mediante el ESP32. |
| `semg.h` | Datos de la señal simulada utilizados por el programa. |
| `imagenes/` | Fotografías y capturas de las evidencias experimentales. |

## 3. Desarrollo experimental

### 3.1. Generación de la señal sEMG

Se utiliza el ESP32 para reproducir la señal sEMG simulada mediante su salida DAC. Esta señal constituye la entrada para las etapas posteriores de acondicionamiento.

![Montaje del simulador sEMG](imagenes/montaje_general.jpg)
*Pie de imagen: [Ver video del funcionamiento y montaje del simulador sEMG](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipNxO0_Rj69rjVSDuEO5cn5kDmwT-yixhfqbSEnA?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn)*

![Señal sEMG generada](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipNxO0_Rj69rjVSDuEO5cn5kDmwT-yixhfqbSEnA?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn)

### 3.2. Etapa de rectificación

Se implementa el circuito rectificador para obtener una señal de polaridad positiva a partir de la señal sEMG original.

### 3.3. Etapa de filtrado

La señal rectificada pasa por un filtro pasa-bajos RC, que permite atenuar las variaciones rápidas y obtener una señal más suave, correspondiente a la envolvente.

### 3.4. Verificación de las señales

Se emplea el osciloscopio para observar y comparar las señales obtenidas en las diferentes etapas del circuito.

![Señal de salida](imagenes/senal_salida.png)

![Visualización en el osciloscopio](imagenes/osciloscopio.png)

#### Mediciones por regiones con cursores (Vertical y Horizontal)

| Región / Tramo | Medición Vertical (Amplitud) | Medición Horizontal (Tiempo) |
|---|---|---|
| **Inicio / Medio** | ![Medición Vertical Inicio/Medio](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipM_7sCpB5XhD6reHcDiGamND1OonVFmbmpKetPG?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn) | ![Medición Horizontal Inicio/Medio](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipN8LoOvoMesAqh9g5fAkarkQ040KZYEmisJbA2T?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn) |
| **Segundo Tramo** | ![Medición Vertical Segundo Tramo](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipOoHIPTw0x-JVYgVPEmZig1sbQJEqtQ-aFWmtfQ?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn) | ![Medición Horizontal Segundo Tramo](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipM6XK4q1qHHzkLeARR9m1R9HLBrRbkuokc6z6NV?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn) |
| **Último Tramo** | ![Medición Vertical Último Tramo](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipNvqvStbK5_NhUBZKjThRCaPSNZI69P8Dz1hBkW?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn) | ![Medición Horizontal Último Tramo](https://photos.google.com/share/AF1QipPYVxlqKkWmjYpuvKkVAwK1hXfqNhgdD015hPB-gud1-3zIoP1r40fK8Wqp9HBNpg/photo/AF1QipNd5Srj4pRAByVIbn4C9fl9iwkvAGvR_JxnWjoN?key=RHVINVA1ZXpQUURLVHdvaVI3T0xkVUU1dFpab0xn) |

## 4. Evidencias del laboratorio

Las fotografías y capturas adicionales del desarrollo experimental se encuentran disponibles en el siguiente álbum:

[Ver evidencias del laboratorio en Google Photos](https://photos.app.goo.gl/HfvXX1tEV1xgZiBr9)

## 5. Repositorio

[Repositorio de Instrumentación Biomédica](https://github.com/nileve-teo/INSTRUMENTACION-BIOMEDICA)

---
**Asignatura:** Instrumentación Biomédica I  
**Laboratorio:** N.° 4 – Extracción de la envolvente de la sEMG simulada  
**Universidad:** Universidad Nacional Mayor de San Marcos

