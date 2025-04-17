#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../Arma/InterfazArmas.hpp"
#include "enumPersonajes.hpp"

using namespace std;

/**
 * @brief Interfaz base para todos los tipos de personajes del juego
 * 
 * Define los metodos comunes que deben implementar todos los personajes,
 * incluyendo gestion de vida, inventario, combate y visualizacion de informacion.
 * Utiliza punteros inteligentes para manejar el ciclo de vida de las armas.
 */
class InterfazPersonaje {
public:
    // ==========================================
    // METODOS BASICOS
    // ==========================================
    
    /**
     * @brief Obtiene el nombre del personaje
     * @return String con el nombre del personaje
     */
    virtual string getNombre() const = 0;
    
    /**
     * @brief Establece un nuevo nombre para el personaje
     * @param nombre El nuevo nombre a asignar
     */
    virtual void setNombre(const string& nombre) = 0;
    
    /**
     * @brief Obtiene los puntos de vida actuales del personaje
     * @return Valor numerico que representa los HP actuales
     */
    virtual int getHP() const = 0;
    
    /**
     * @brief Aplica daño al personaje, reduciendo sus puntos de vida
     * @param cantidad Cantidad de daño a aplicar
     * @param esCombatePPT Este valor indica si el daño es en combate PPT (10)
     * @return true si el personaje sigue vivo, false si ha muerto
     */
    virtual bool recibirDanio(int cantidad, bool esCombatePPT) = 0;
    
    /**
     * @brief Cura al personaje, aumentando sus puntos de vida
     * @param cantidad Cantidad de puntos de vida a restaurar
     */
    virtual void curar(int cantidad) = 0;

    // ==========================================
    // METODOS DE INVENTARIO
    // ==========================================
    
    /**
     * @brief Añade un arma al inventario del personaje
     * @param arma El arma a añadir (transferencia de propiedad)
     * @return true si se pudo añadir, false si el inventario está lleno
     */
    virtual bool agregarArma(unique_ptr<InterfazArmas> arma) = 0;

    /**
     * @brief Quita un arma del inventario por su posicion
     * @param posicion Indice del arma a quitar
     * @return El arma quitada o nullptr si la posicion es invalida
     */
    virtual unique_ptr<InterfazArmas> quitarArma(int posicion) = 0;

    /**
     * @brief Obtiene una referencia a un arma sin quitarla del inventario
     * @param posicion Indice del arma deseada
     * @return Puntero al arma o nullptr si la posicion es invalida
     */
    virtual InterfazArmas* getArma(int posicion) const = 0;

    // ==========================================
    // METODOS DE COMBATE
    // ==========================================
    
    /**
     * @brief Realiza un ataque usando el arma equipada y el movimiento especificado
     * @param movimiento El tipo de movimiento de ataque a realizar
     * @return Valor numerico que representa el daño causado
     */
    virtual int atacar(MovimientoCombate movimiento) = 0;

    // ==========================================
    // METODOS DE VISUALIZACION
    // ==========================================
    
    /**
     * @brief Muestra informacion detallada sobre el personaje
     */
    virtual void mostrarInfo() const = 0;

    /**
     * @brief Muestra el contenido del inventario de armas
     */
    virtual void mostrarInventario() const = 0;

    // ==========================================
    // METODOS PARA COMBATE PPT (PIEDRA-PAPEL-TIJERA)
    // ==========================================
    
    /**
     * @brief Establece los HP exactamente a 100 para un combate PPT
     * @return true si se realizo con exito, false si hubo un error
     */
    virtual bool setHPParaCombatePPT() = 0;
    
    /**
     * @brief Restaura los HP originales despues de un combate PPT
     * @return true si se restauro con exito, false si hubo un error
     */
    virtual bool restaurarHPOriginal() = 0;

    /**
     * @brief Destructor virtual para permitir destruccion polimorfica
     */
    virtual ~InterfazPersonaje() = default;
};
