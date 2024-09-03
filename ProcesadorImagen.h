#ifndef PROCESADOR_IMAGEN_H
#define PROCESADOR_IMAGEN_H

#include "Archivo_jpeg.h"
#include <string>

class ProcesadorImagen {
public:
    static void invertirColores(Archivo_jpeg& archivo);
    static void binarizarImagen(Archivo_jpeg& archivo);
    static void espejoImagen(Archivo_jpeg& archivo);
    static void aplicarKernelConvolucion(Archivo_jpeg& archivo);

private:
    static void guardarTiempoProcesamiento(const std::string& nombreFuncion, double tiempo);
};

#endif // PROCESADOR_IMAGEN_H