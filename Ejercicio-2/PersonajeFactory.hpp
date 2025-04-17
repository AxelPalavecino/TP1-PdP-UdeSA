#pragma once

#include <memory>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <iostream>

// Inclusión de cabeceras para personajes y armas
#include "../Ejercicio-1/Personajes/InterfazPersonaje.hpp"
#include "../Ejercicio-1/Personajes/Mago.hpp"
#include "../Ejercicio-1/Personajes/Guerrero.hpp"
#include "../Ejercicio-1/Personajes/Magos/Hechicero.hpp"
#include "../Ejercicio-1/Personajes/Magos/Conjurador.hpp"
#include "../Ejercicio-1/Personajes/Magos/Brujo.hpp"
#include "../Ejercicio-1/Personajes/Magos/Nigromante.hpp"
#include "../Ejercicio-1/Personajes/Guerrero/Barbaro.hpp"
#include "../Ejercicio-1/Personajes/Guerrero/Paladin.hpp"
#include "../Ejercicio-1/Personajes/Guerrero/Caballero.hpp"
#include "../Ejercicio-1/Personajes/Guerrero/Mercenario.hpp"
#include "../Ejercicio-1/Personajes/Guerrero/Gladiador.hpp"

#include "../Ejercicio-1/Arma/InterfazArmas.hpp"
#include "../Ejercicio-1/Arma/ObjetoMagico.hpp"
#include "../Ejercicio-1/Arma/ArmaDeCombate.hpp"
#include "../Ejercicio-1/Arma/ItemsMagico/Baston.hpp"
#include "../Ejercicio-1/Arma/ItemsMagico/LibroHechizos.hpp"
#include "../Ejercicio-1/Arma/ItemsMagico/Pocion.hpp"
#include "../Ejercicio-1/Arma/ItemsMagico/Amuleto.hpp"
#include "../Ejercicio-1/Arma/ArmasDeCombate/HachaSimple.hpp"
#include "../Ejercicio-1/Arma/ArmasDeCombate/HachaDoble.hpp"
#include "../Ejercicio-1/Arma/ArmasDeCombate/Espada.hpp"
#include "../Ejercicio-1/Arma/ArmasDeCombate/Lanza.hpp"
#include "../Ejercicio-1/Arma/ArmasDeCombate/Garrote.hpp"

using namespace std;

/**
 * @brief Enumeración que define los tipos de personajes disponibles
 */
enum class TipoPersonaje {
    Hechicero = 0,
    Conjurador,
    Brujo,
    Nigromante,
    Barbaro,
    Paladin,
    Caballero,
    Mercenario,
    Gladiador
};

/**
 * @brief Enumeración que define los tipos de armas disponibles
 */
enum class TipoArma {
    Baston = 0,
    LibroHechizos,
    Pocion,
    Amuleto,
    HachaSimple,
    HachaDoble,
    Espada,
    Lanza,
    Garrote
};

/**
 * @brief Estructura que almacena los resultados de la generación de personajes
 * 
 * Contiene vectores para almacenar los magos y guerreros generados,
 * así como contadores para el total de personajes y armas creadas.
 */
struct ResultadoGeneracion {
    vector<shared_ptr<InterfazPersonaje>> magos;
    vector<shared_ptr<InterfazPersonaje>> guerreros;
    int totalPersonajes;
    int totalArmas;
};

/**
 * @brief Clase que implementa el patrón Factory para crear personajes y armas
 * 
 * Proporciona métodos estáticos para generar personajes y armas de forma
 * dinámica en tiempo de ejecución, usando smart pointers para la gestión
 * automática de memoria.
 */
class PersonajeFactory {
public:

    // ==========================================
    // METODOS PARA CREACION DINAMICA (EJERCICIO 2)
    // ==========================================

    /**
     * @brief Crea un personaje específico según el tipo proporcionado
     * @param tipo Tipo de personaje a crear
     * @return Puntero compartido al personaje creado
     */
    static shared_ptr<InterfazPersonaje> crearPersonaje(TipoPersonaje tipo);
    
    /**
     * @brief Crea un personaje de tipo mago aleatorio
     * @return Puntero compartido al mago aleatorio creado
     */
    static shared_ptr<InterfazPersonaje> crearMagoAleatorio();
    
    /**
     * @brief Crea un personaje de tipo guerrero aleatorio
     * @return Puntero compartido al guerrero aleatorio creado
     */
    static shared_ptr<InterfazPersonaje> crearGuerreroAleatorio();
    
    /**
     * @brief Crea un arma específica según el tipo proporcionado
     * @param tipo Tipo de arma a crear
     * @return Puntero único al arma creada
     */
    static unique_ptr<InterfazArmas> crearArma(TipoArma tipo);
    
    /**
     * @brief Crea un arma de tipo aleatorio
     * @return Puntero único al arma aleatoria creada
     */
    static unique_ptr<InterfazArmas> crearArmaAleatoria();
    
    /**
     * @brief Crea un arma especializada para un personaje mago
     * @return Puntero único al arma creada para mago
     */
    static unique_ptr<InterfazArmas> crearArmaParaMago();
    
    /**
     * @brief Crea un arma especializada para un personaje guerrero
     * @return Puntero único al arma creada para guerrero
     */
    static unique_ptr<InterfazArmas> crearArmaParaGuerrero();
    
    /**
     * @brief Crea un personaje con un número aleatorio de armas (0-2)
     * @param tipo Tipo de personaje a crear
     * @return Puntero compartido al personaje armado
     */
    static shared_ptr<InterfazPersonaje> crearPersonajeArmado(TipoPersonaje tipo);
    
    /**
     * @brief Crea un personaje con un número específico de armas
     * @param tipo Tipo de personaje a crear
     * @param numArmas Número de armas para equipar al personaje
     * @return Puntero compartido al personaje armado
     */
    static shared_ptr<InterfazPersonaje> crearPersonajeArmado(TipoPersonaje tipo, int numArmas);
    
    /**
     * @brief Genera grupos aleatorios de personajes (magos y guerreros)
     * @return Estructura ResultadoGeneracion con los personajes y estadísticas
     */
    static ResultadoGeneracion generarGruposPersonajes();
    
    // ==========================================
    // MODO COMBATE PPT (EJERCICIO 3)
    // ==========================================

    /**
     * @brief Crea un personaje preparado para el modo de combate (Ejercicio 3)
     * @param tipo Tipo de personaje a crear
     * @param numArmas Número de armas para equipar al personaje
     * @return Puntero compartido al personaje configurado para PPT
     */
    static shared_ptr<InterfazPersonaje> crearPersonajeModoCombtePPT(TipoPersonaje tipo, int numArmas);

private:
    /**
     * @brief Obtiene un nombre aleatorio apropiado para el tipo de personaje
     * @param esMago Indica si el personaje es un mago (true) o guerrero (false)
     * @return Nombre aleatorio del personaje
     */
    static string obtenerNombreAleatorio(bool esMago);
    
    // ==========================================
    // METODO PRIVADO PARA CREAR NUMERO ALEATORIO (EJERCICIO 2 a.)
    // ==========================================

    /**
     * @brief Genera un número aleatorio en el rango especificado
     * @param min Valor mínimo del rango
     * @param max Valor máximo del rango
     * @return Número aleatorio dentro del rango [min, max]
     */
    static int obtenerNumeroAleatorio(int min, int max);
};
