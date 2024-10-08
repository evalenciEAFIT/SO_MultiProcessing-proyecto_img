#include "ProcesadorImagen.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <cmath>

void ProcesadorImagen::invertirColores(Archivo_jpeg& archivo) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::cout << "Invirtiendo colores de la imagen: " << archivo.obtenerNombreArchivo() << std::endl;
    const auto& datosOriginales = archivo.obtenerDatosImagen();
    std::vector<unsigned char> datosModificados = datosOriginales;
    int ancho = archivo.obtenerAncho();
    int alto = archivo.obtenerAlto();
    int numComponentes = archivo.obtenerNumComponentes();

    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < ancho; ++x) {
            for (int c = 0; c < numComponentes; ++c) {
                int indice = (y * ancho + x) * numComponentes + c;
                datosModificados[indice] = 255 - datosOriginales[indice];
            }
        }
    }
    
    Archivo_jpeg archivoModificado = archivo;
    archivoModificado.actualizarDatosImagen(datosModificados);
    archivoModificado.guardarImagen("_invertido");
    
    auto fin = std::chrono::high_resolution_clock::now();
    double tiempo = std::chrono::duration<double, std::milli>(fin - inicio).count();
    guardarTiempoProcesamiento("invertirColores", tiempo);
    std::cout << "Tiempo de procesamiento (invertirColores): " << tiempo << " ms" << std::endl;
}

void ProcesadorImagen::binarizarImagen(Archivo_jpeg& archivo) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::cout << "Binarizando la imagen: " << archivo.obtenerNombreArchivo() << std::endl;
    const auto& datosOriginales = archivo.obtenerDatosImagen();
    std::vector<unsigned char> datosModificados = datosOriginales;
    int ancho = archivo.obtenerAncho();
    int alto = archivo.obtenerAlto();
    int numComponentes = archivo.obtenerNumComponentes();
    
    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < ancho; ++x) {
            int promedio = 0;
            for (int c = 0; c < numComponentes; ++c) {
                promedio += datosOriginales[(y * ancho + x) * numComponentes + c];
            }
            promedio /= numComponentes;
            
            unsigned char valor = (promedio > 128) ? 255 : 0;
            for (int c = 0; c < numComponentes; ++c) {
                datosModificados[(y * ancho + x) * numComponentes + c] = valor;
            }
        }
    }
    
    Archivo_jpeg archivoModificado = archivo;
    archivoModificado.actualizarDatosImagen(datosModificados);
    archivoModificado.guardarImagen("_binarizado");
    
    auto fin = std::chrono::high_resolution_clock::now();
    double tiempo = std::chrono::duration<double, std::milli>(fin - inicio).count();
    guardarTiempoProcesamiento("binarizarImagen", tiempo);
    std::cout << "Tiempo de procesamiento (binarizarImagen): " << tiempo << " ms" << std::endl;
}

void ProcesadorImagen::espejoImagen(Archivo_jpeg& archivo) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::cout << "Aplicando efecto espejo a la imagen: " << archivo.obtenerNombreArchivo() << std::endl;
    const auto& datosOriginales = archivo.obtenerDatosImagen();
    std::vector<unsigned char> datosModificados = datosOriginales;
    int ancho = archivo.obtenerAncho();
    int alto = archivo.obtenerAlto();
    int numComponentes = archivo.obtenerNumComponentes();
    
    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < ancho / 2; ++x) {
            for (int c = 0; c < numComponentes; ++c) {
                std::swap(datosModificados[(y * ancho + x) * numComponentes + c],
                          datosModificados[(y * ancho + (ancho - 1 - x)) * numComponentes + c]);
            }
        }
    }
    
    Archivo_jpeg archivoModificado = archivo;
    archivoModificado.actualizarDatosImagen(datosModificados);
    archivoModificado.guardarImagen("_espejo");
    
    auto fin = std::chrono::high_resolution_clock::now();
    double tiempo = std::chrono::duration<double, std::milli>(fin - inicio).count();
    guardarTiempoProcesamiento("espejoImagen", tiempo);
    std::cout << "Tiempo de procesamiento (espejoImagen): " << tiempo << " ms" << std::endl;
}

void ProcesadorImagen::aplicarKernelConvolucion(Archivo_jpeg& archivo) {
    auto inicio = std::chrono::high_resolution_clock::now();
    
    std::cout << "Aplicando kernel de convolución a la imagen: " << archivo.obtenerNombreArchivo() << std::endl;
    const auto& datosOriginales = archivo.obtenerDatosImagen();
    int ancho = archivo.obtenerAncho();
    int alto = archivo.obtenerAlto();
    int numComponentes = archivo.obtenerNumComponentes();
    
    // Kernel de ejemplo (detección de bordes)
    const int kernel[3][3] = {
        {-1, -1, -1},
        {-1,  8, -1},
        {-1, -1, -1}
    };
    
    std::vector<unsigned char> datosModificados(datosOriginales.size());
    
    for (int y = 1; y < alto - 1; ++y) {
        for (int x = 1; x < ancho - 1; ++x) {
            for (int c = 0; c < numComponentes; ++c) {
                int suma = 0;
                for (int ky = -1; ky <= 1; ++ky) {
                    for (int kx = -1; kx <= 1; ++kx) {
                        int indice = ((y + ky) * ancho + (x + kx)) * numComponentes + c;
                        suma += datosOriginales[indice] * kernel[ky + 1][kx + 1];
                    }
                }
                suma = std::max(0, std::min(suma, 255));
                datosModificados[(y * ancho + x) * numComponentes + c] = static_cast<unsigned char>(suma);
            }
        }
    }
    
    Archivo_jpeg archivoModificado = archivo;
    archivoModificado.actualizarDatosImagen(datosModificados);
    archivoModificado.guardarImagen("_convolucion");
    
    auto fin = std::chrono::high_resolution_clock::now();
    double tiempo = std::chrono::duration<double, std::milli>(fin - inicio).count();
    guardarTiempoProcesamiento("aplicarKernelConvolucion", tiempo);
    std::cout << "Tiempo de procesamiento (aplicarKernelConvolucion): " << tiempo << " ms" << std::endl;
}

void ProcesadorImagen::guardarTiempoProcesamiento(const std::string& nombreFuncion, double tiempo) {
    std::ofstream archivo("tiempos_procesamiento.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << nombreFuncion << ": " << tiempo << " ms" << std::endl;
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para guardar los tiempos de procesamiento." << std::endl;
    }
}