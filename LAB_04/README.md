
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

### 3.2. Etapa de rectificación

Se implementa el circuito rectificador para obtener una señal de polaridad positiva a partir de la señal sEMG original.

![Etapa de rectificación](imagenes/etapa_rectificacion.jpg)

### 3.3. Etapa de filtrado

La señal rectificada pasa por un filtro pasa-bajos RC, que permite atenuar las variaciones rápidas y obtener una señal más suave, correspondiente a la envolvente.

![Etapa de filtrado](imagenes/etapa_filtrado.jpg)

### 3.4. Verificación de las señales

Se emplea el osciloscopio para observar y comparar las señales obtenidas en las diferentes etapas del circuito.

![Señal de salida](imagenes/senal_salida.png)

![Visualización en el osciloscopio](imagenes/osciloscopio.png)

## 4. Evidencias del laboratorio

Las fotografías y capturas adicionales del desarrollo experimental se encuentran disponibles en el siguiente álbum:

[Ver evidencias del laboratorio en Google Photos](https://photos.app.goo.gl/HfvXX1tEV1xgZiBr9)

## 5. Repositorio

[Repositorio de Instrumentación Biomédica](https://github.com/nileve-teo/INSTRUMENTACION-BIOMEDICA)

---

**Asignatura:** Instrumentación Biomédica I  
**Laboratorio:** N.° 4 – Extracción de la envolvente de la sEMG simulada  
**Universidad:** Universidad Nacional Mayor de San Marcos

