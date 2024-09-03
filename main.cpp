#include "Archivo_jpeg.h"
#include "ProcesadorImagen.h"
#include <iostream>
#include <string>

void imprimirSegmento(const std::vector<std::vector<std::vector<int>>>& segmento) {
    for (const auto& fila : segmento) {
        for (const auto& pixel : fila) {
            std::cout << "(";
            for (size_t i = 0; i < pixel.size(); ++i) {
                std::cout << pixel[i];
                if (i < pixel.size() - 1) std::cout << ",";
            }
            std::cout << ") ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string nombreArchivo;
    std::cout << "Ingrese el nombre del archivo JPEG: ";
    std::cin >> nombreArchivo;

    Archivo_jpeg archivo(nombreArchivo);
    if (!archivo.abrirArchivo()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    int opcion;
    do {
        std::cout << "\nMenú de opciones:" << std::endl;
        std::cout << "1. Invertir colores" << std::endl;
        std::cout << "2. Binarizar imagen" << std::endl;
        std::cout << "3. Aplicar efecto espejo" << std::endl;
        std::cout << "4. Aplicar kernel de convolución" << std::endl;
        std::cout << "5. Ver datos de cabecera" << std::endl;
        std::cout << "6. Ver segmento de matriz de píxeles" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                ProcesadorImagen::invertirColores(archivo);
                break;
            case 2:
                ProcesadorImagen::binarizarImagen(archivo);
                break;
            case 3:
                ProcesadorImagen::espejoImagen(archivo);
                break;
            case 4:
                ProcesadorImagen::aplicarKernelConvolucion(archivo);
                break;
            case 5:
                std::cout << archivo.verDatosCabecera() << std::endl;
                break;
            case 6: {
                int x1, y1, x2, y2;
                std::cout << "Ingrese x1 y1 x2 y2: ";
                std::cin >> x1 >> y1 >> x2 >> y2;
                try {
                    auto segmento = archivo.verSegmentoMatrizPixeles(x1, y1, x2, y2);
                    imprimirSegmento(segmento);
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 0);

    return 0;
}