/**
 * @file CombatePPT.hpp
 * @brief Define la clase CombatePPT para implementar el sistema de combate Piedra-Papel-Tijera
 * 
 * Este archivo contiene la definición de la clase CombatePPT, que implementa un sistema
 * de combate por turnos basado en el juego Piedra-Papel-Tijera entre dos personajes.
 * También define estructuras auxiliares como Combatiente y OpcionAtaque.
 */

#pragma once

#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../Ejercicio-2/PersonajeFactory.hpp"

using namespace std;

/**
 * @enum OpcionAtaque
 * @brief Define las opciones de ataque disponibles para el combate PPT
 */
enum class OpcionAtaque {
    GolpeFuerte = 1,  ///< Opción Golpe Fuerte (gana a Golpe Rápido)
    GolpeRapido = 2,  ///< Opción Golpe Rápido (gana a Defensa y Golpe)
    DefensaYGolpe = 3 ///< Opción Defensa y Golpe (gana a Golpe Fuerte)
};

/**
 * @struct Combatiente
 * @brief Estructura que almacena información de un combatiente en el sistema PPT
 */
struct Combatiente {
    shared_ptr<InterfazPersonaje> personaje;  ///< Puntero al personaje
    InterfazArmas* arma;                      ///< Puntero al arma equipada
    int hpOriginal;                           ///< HP original antes del combate
    
    /**
     * @brief Constructor de la estructura Combatiente
     * @param p Puntero compartido al personaje
     * @param a Puntero al arma equipada
     */
    Combatiente(shared_ptr<InterfazPersonaje> p, InterfazArmas* a) 
        : personaje(p), arma(a), hpOriginal(p->getHP()) {}
};

/**
 * @class CombatePPT
 * @brief Clase que gestiona la lógica del combate Piedra-Papel-Tijera
 * 
 * Implementa el sistema de combate por turnos basado en el juego Piedra-Papel-Tijera,
 * permitiendo a dos personajes enfrentarse hasta que uno pierda todos sus puntos de vida.
 */
class CombatePPT {
public:
    /**
     * @brief Constructor que configura el combate
     * @param configManual Indica si el usuario selecciona manualmente su personaje
     * @param usarDañoFijo Indica si se usa siempre 10 puntos de daño fijo
     */
    CombatePPT(bool configManual = true, bool usarDañoFijo = true);
    
    /**
     * @brief Destructor que libera recursos y restablece el estado original de los personajes
     */
    ~CombatePPT();
    
    /**
     * @brief Inicializa el combate (selección de personajes, etc.)
     * @return true si la inicialización fue exitosa, false en caso contrario
     */
    bool inicializar();
    
    /**
     * @brief Ejecuta un turno completo de combate
     * @return true si el turno se completó correctamente, false en caso contrario
     */
    bool ejecutarTurno();
    
    /**
     * @brief Muestra el resultado final del combate
     */
    void mostrarResultado() const;
    
    /**
     * @brief Devuelve si el combate ha terminado
     * @return true si el combate ha terminado, false en caso contrario
     */
    bool haTerminado() const;
    
    /**
     * @brief Restablece los HP originales cuando el combate termina
     */
    void restablecerEstadoOriginal();
    
    /**
     * @brief Establece si usar daño fijo de 10 o incluir bonificaciones
     * @param usarDañoFijo true para usar daño fijo, false para incluir bonificaciones
     */
    void setUsarDañoFijo(bool usarDañoFijo);
    
    /**
     * @brief Obtiene si se está usando daño fijo
     * @return true si se usa daño fijo, false en caso contrario
     */
    bool getUsarDañoFijo() const;

private:
    Combatiente* jugador1;        ///< Combatiente controlado por el usuario
    Combatiente* jugador2;        ///< Combatiente controlado por la IA
    bool combateTerminado;        ///< Indica si el combate ha terminado
    bool configManual;            ///< Indica si el usuario selecciona su personaje
    bool usarDañoFijo;            ///< Indica si se usa daño fijo de 10 sin bonificaciones
    
    // Métodos auxiliares de lógica
    
    /**
     * @brief Obtiene la elección de ataque del jugador
     * @return Opción de ataque elegida por el jugador
     */
    OpcionAtaque obtenerEleccionJugador() const;
    
    /**
     * @brief Genera una elección de ataque aleatoria para la IA
     * @return Opción de ataque generada aleatoriamente
     */
    OpcionAtaque generarEleccionAleatoria() const;
    
    /**
     * @brief Prepara un personaje para el combate PPT estableciendo su HP a 100
     * @param personaje Puntero compartido al personaje a preparar
     */
    void prepararPersonajeParaCombate(shared_ptr<InterfazPersonaje>& personaje);
    
    /**
     * @brief Resuelve un enfrentamiento entre dos opciones de ataque
     * @param op1 Opción de ataque del primer jugador
     * @param op2 Opción de ataque del segundo jugador
     * @return true si el primer jugador gana, false si gana el segundo
     */
    bool resolverEnfrentamiento(OpcionAtaque op1, OpcionAtaque op2) const;
    
    /**
     * @brief Aplica daño al perdedor del enfrentamiento
     * @param ganador Combatiente que ganó el enfrentamiento
     * @param perdedor Combatiente que perdió el enfrentamiento
     * @param opGanadora Opción de ataque utilizada por el ganador
     */
    void aplicarDanio(Combatiente& ganador, Combatiente& perdedor, OpcionAtaque opGanadora);
    
    /**
     * @brief Configura manualmente el personaje del jugador 1
     */
    void configurarJugador1();
    
    /**
     * @brief Configura aleatoriamente el personaje del jugador 2
     */
    void configurarJugador2();
    
    /**
     * @brief Convierte una opción de ataque a string para mostrarla
     * @param opcion Opción de ataque a convertir
     * @return String que representa la opción de ataque
     */
    string opcionAtaqueToString(OpcionAtaque opcion) const;

    // Métodos de visualización
    
    /**
     * @brief Muestra información sobre los personajes y el estado actual del combate
     */
    void mostrarEstadoActual() const;
    
    /**
     * @brief Convierte una opción de ataque a un icono visual
     * @param opcion Opción de ataque a convertir
     * @return String que contiene el icono del movimiento con formato de color
     */
    string dibujarIconoMovimiento(OpcionAtaque opcion) const;
};

// Funciones auxiliares para visualización

/**
 * @brief Genera una barra de vida visual basada en el HP actual y máximo
 * @param hpActual HP actual del personaje
 * @param hpMax HP máximo del personaje
 * @return String que contiene la barra de vida con formato de color
 */
string barraDeVida(int hpActual, int hpMax);

/**
 * @brief Genera un icono que representa el tipo de personaje
 * @param personaje Puntero al personaje del que se quiere obtener el icono
 * @return String que contiene el icono del personaje con formato de color
 */
string dibujarIconoPersonaje(InterfazPersonaje* personaje);

/**
 * @brief Muestra arte ASCII decorativo del título del juego
 */
void mostrarAsciiArt();