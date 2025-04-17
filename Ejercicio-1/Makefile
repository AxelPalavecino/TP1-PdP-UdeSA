# Makefile para Ejercicio 1 (Interzas, clases abstractas, metodos, sobre las armas y personajes pedidos)

CXX = g++
CXXFLAGS = -std=c++20 -Wall -g

TARGET = juego_rol_demo
MAIN_SRC = main.cpp

# Directorios

SRCS_ENUMS = Personajes/enumPersonajes.cpp \
             Arma/enumArmas.cpp

SRCS_PERSONAJES = Personajes/Mago.cpp \
                  Personajes/Guerrero.cpp \
                  Personajes/Magos/Brujo.cpp \
                  Personajes/Magos/Conjurador.cpp \
                  Personajes/Magos/Hechicero.cpp \
                  Personajes/Magos/Nigromante.cpp \
                  Personajes/Guerrero/Barbaro.cpp \
                  Personajes/Guerrero/Caballero.cpp \
                  Personajes/Guerrero/Gladiador.cpp \
                  Personajes/Guerrero/Mercenario.cpp \
                  Personajes/Guerrero/Paladin.cpp

SRCS_ARMAS = Arma/ArmaDeCombate.cpp \
             Arma/ObjetoMagico.cpp \
             Arma/ArmasDeCombate/Espada.cpp \
             Arma/ArmasDeCombate/Garrote.cpp \
             Arma/ArmasDeCombate/HachaDoble.cpp \
             Arma/ArmasDeCombate/HachaSimple.cpp \
             Arma/ArmasDeCombate/Lanza.cpp \
             Arma/ItemsMagico/Amuleto.cpp \
             Arma/ItemsMagico/Baston.cpp \
             Arma/ItemsMagico/LibroHechizos.cpp \
             Arma/ItemsMagico/Pocion.cpp

ALL_SRCS = $(MAIN_SRC) $(SRCS_ENUMS) $(SRCS_PERSONAJES) $(SRCS_ARMAS)

VALGRIND = valgrind
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

OBJS = $(ALL_SRCS:.cpp=.o)

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
