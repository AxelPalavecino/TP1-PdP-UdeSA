#pragma once

#include <string>
#include "enumArmas.hpp"

using namespace std;

/**
 * @brief Interfaz base para todos los tipos de armas
 * 
 * Define los métodos comunes que deben implementar todas las armas
 * y objetos, como recuperar información básica y funcionalidades
 * de uso y reparación.
 */
class InterfazArmas {
public:

    // ==========================================
    // METODOS VIRTUALES PUROS DE INTERFAZ
    // ==========================================

    /**
     * @brief Establece el nombre del arma u objeto
     * @param nombre El nuevo nombre para asignar
     */
    virtual void setNombre(const string& nombre) = 0;

    /**
     * @brief Obtiene el nombre del arma u objeto
     * @return String con el nombre del arma
     */
    virtual string getNombre() const = 0;

    /**
     * @brief Obtiene el poder base del arma u objeto
     * @return Valor numérico que representa el poder
     */
    virtual int getPoder() const = 0;

    /**
     * @brief Obtiene la durabilidad actual del arma u objeto
     * @return Valor numérico de la durabilidad actual
     */
    virtual int getDurabilidadActual() const = 0;

    /**
     * @brief Obtiene la durabilidad máxima del arma u objeto
     * @return Valor numérico de la durabilidad máxima
     */
    virtual int getDurabilidadMaxima() const = 0;

    /**
     * @brief Obtiene la rareza del arma u objeto
     * @return Valor de enumeración que representa la rareza
     */
    virtual Rarity getRareza() const = 0;
    
    /**
     * @brief Usa el arma u objeto para realizar su acción principal
     * @return Valor numérico que representa el efecto del uso
     */
    virtual int usar() = 0;
    
    /**
     * @brief Muestra información detallada del arma u objeto
     */
    virtual void mostrarInfo() const = 0;
    
    /**
     * @brief Repara el arma u objeto, aumentando su durabilidad
     * @param cantidad La cantidad de puntos de durabilidad a restaurar
     */
    virtual void reparar(int cantidad) = 0;
    
    /**
     * @brief Destructor virtual para permitir la correcta liberación de recursos
     */
    virtual ~InterfazArmas() = default;
};
