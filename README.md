# Procesador de Imágenes JPEG

Este programa es un procesador de imágenes JPEG que permite realizar varias operaciones de manipulación de imágenes, incluyendo inversión de colores, binarización, efecto espejo y aplicación de kernel de convolución.

## Requisitos

- C++ 11 o superior
- Biblioteca libjpeg

## Instalación de Librerías

### En sistemas basados en Debian/Ubuntu:

```bash
sudo apt-get update
sudo apt-get install libjpeg-dev
```

### En sistemas basados en Red Hat/Fedora:

```bash
sudo dnf install libjpeg-devel
```

### En macOS (usando Homebrew):

```bash
brew install libjpeg
```

## Compilación

Para compilar el programa, usa el siguiente comando:

```bash
make
```

## Uso del Programa

Para ejecutar el programa:

```bash
./procesador_imagen
```

Sigue las instrucciones en pantalla para seleccionar una imagen JPEG y aplicar las diferentes operaciones de procesamiento.

## Funciones de Procesamiento de Imágenes

### 1. Inversión de Colores

Esta función invierte los colores de la imagen, creando un efecto de "negativo".

Pseudocódigo:
```
Para cada píxel en la imagen:
    Para cada componente de color del píxel:
        nuevo_valor = 255 - valor_actual
```

### 2. Binarización

Esta función convierte la imagen a blanco y negro basándose en un umbral.

Pseudocódigo:
```
Para cada píxel en la imagen:
    Calcular el promedio de los componentes de color
    Si promedio > umbral (128):
        Establecer todos los componentes a 255 (blanco)
    Sino:
        Establecer todos los componentes a 0 (negro)
```

### 3. Efecto Espejo

Esta función crea un efecto de espejo horizontal en la imagen.

Pseudocódigo:
```
Para cada fila de la imagen:
    Para x desde 0 hasta ancho/2:
        Intercambiar píxel en posición x con píxel en posición (ancho - 1 - x)
```

### 4. Aplicación de Kernel de Convolución

Esta función aplica un kernel de convolución a la imagen para detectar bordes.

Pseudocódigo:
```
Definir kernel de convolución (ejemplo para detección de bordes):
    [-1 -1 -1]
    [-1  8 -1]
    [-1 -1 -1]

Para cada píxel en la imagen (excluyendo bordes):
    Para cada componente de color:
        Suma = 0
        Para cada elemento del kernel:
            Suma += valor_píxel_correspondiente * valor_kernel
        nuevo_valor = limitar(Suma, 0, 255)
```

## Notas Adicionales

- Todas las operaciones crean una nueva imagen, dejando la original sin modificar.
- Los tiempos de procesamiento se registran en un archivo "tiempos_procesamiento.txt".
- Las imágenes procesadas se guardan con un sufijo que indica la operación realizada.

## Licencia

[MIT License](https://opensource.org/licenses/MIT)
