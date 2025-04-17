# Makefile para Ejercicio-2

CXX = g++
CXXFLAGS = -std=c++20 -Wall -g

TARGET = personaje_factory_demo

SRCS_MAIN = mainEjercicio2.cpp PersonajeFactory.cpp

SRCS_ENUMS = ../Ejercicio-1/Personajes/enumPersonajes.cpp \
             ../Ejercicio-1/Arma/enumArmas.cpp

SRCS_PERSONAJES = ../Ejercicio-1/Personajes/Mago.cpp \
                  ../Ejercicio-1/Personajes/Guerrero.cpp \
                  ../Ejercicio-1/Personajes/Magos/Brujo.cpp \
                  ../Ejercicio-1/Personajes/Magos/Conjurador.cpp \
                  ../Ejercicio-1/Personajes/Magos/Hechicero.cpp \
                  ../Ejercicio-1/Personajes/Magos/Nigromante.cpp \
                  ../Ejercicio-1/Personajes/Guerrero/Barbaro.cpp \
                  ../Ejercicio-1/Personajes/Guerrero/Caballero.cpp \
                  ../Ejercicio-1/Personajes/Guerrero/Gladiador.cpp \
                  ../Ejercicio-1/Personajes/Guerrero/Mercenario.cpp \
                  ../Ejercicio-1/Personajes/Guerrero/Paladin.cpp

SRCS_ARMAS = ../Ejercicio-1/Arma/ArmaDeCombate.cpp \
             ../Ejercicio-1/Arma/ObjetoMagico.cpp \
             ../Ejercicio-1/Arma/ArmasDeCombate/Espada.cpp \
             ../Ejercicio-1/Arma/ArmasDeCombate/Garrote.cpp \
             ../Ejercicio-1/Arma/ArmasDeCombate/HachaDoble.cpp \
             ../Ejercicio-1/Arma/ArmasDeCombate/HachaSimple.cpp \
             ../Ejercicio-1/Arma/ArmasDeCombate/Lanza.cpp \
             ../Ejercicio-1/Arma/ItemsMagico/Amuleto.cpp \
             ../Ejercicio-1/Arma/ItemsMagico/Baston.cpp \
             ../Ejercicio-1/Arma/ItemsMagico/LibroHechizos.cpp \
             ../Ejercicio-1/Arma/ItemsMagico/Pocion.cpp

ALL_SRCS = $(SRCS_MAIN) $(SRCS_ENUMS) $(SRCS_PERSONAJES) $(SRCS_ARMAS)

OBJS = $(ALL_SRCS:.cpp=.o)

VALGRIND = valgrind
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

debug:
	@echo "Target: $(TARGET)"
	@echo "Object files: $(OBJS)"

valgrind: $(TARGET)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(TARGET)
valgrind-suppressed: $(TARGET)
	$(VALGRIND) $(VALGRIND_FLAGS) --suppressions=valgrind.supp ./$(TARGET)

.PHONY: all clean run debug
