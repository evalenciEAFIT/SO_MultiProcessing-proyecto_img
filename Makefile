# Compilador
CXX = g++

# Flags de compilación
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic

# Librerías
LIBS = -ljpeg

# Nombre del ejecutable
TARGET = procesador_imagen

# Archivos fuente y objeto
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Archivos de cabecera
HEADERS = $(wildcard *.h)

# Regla por defecto
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Regla para compilar archivos objeto
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Regla para recompilar todo
rebuild: clean all

# Phony targets
.PHONY: all clean run rebuild