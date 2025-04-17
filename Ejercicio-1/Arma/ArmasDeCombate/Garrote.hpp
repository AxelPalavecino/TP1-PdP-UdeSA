#pragma once

#include "../ArmaDeCombate.hpp"
#include "../enumArmas.hpp"

/**
 * @brief Clase Garrote que hereda de ArmaDeCombate
 * 
 * Define los atributos y métodos específicos de un garrote, incluyendo
 * su capacidad para aplastar, opciones para personalizarlo con clavos, 
 * y su bonus de aturdimiento.
 */
class Garrote : public ArmaDeCombate {
private:
    TipoMadera tipoMadera; 
    bool tieneClavos; 
    double circunferenciaCabeza; 
    int bonusAturdimiento; 
    OrigenGarrote origen; 

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Garrote
     * @param n Nombre del garrote
     * @param df Daño físico base
     * @param dm Durabilidad máxima
     * @param p Peso del garrote
     * @param r Rareza del garrote
     * @param nf Nivel de filo inicial
     * @param tm Tipo de madera
     * @param tc Indica si tiene clavos
     * @param cc Circunferencia de la cabeza
     * @param ba Bonus de aturdimiento
     * @param org Origen del garrote
     */
    Garrote(string n, int df, int dm, double p, Rarity r, int nf, 
            TipoMadera tm, bool tc, double cc, int ba, OrigenGarrote org);

    // ==========================================
    // MÉTODOS DERIVADOS DE INTERFAZARMAS
    // ==========================================
    
    int usar() override;
    void mostrarInfo() const override;

    // ==========================================
    // MÉTODOS PROPIOS DE LA CLASE GARROTE
    // ==========================================
    
    /**
     * @brief Realiza un ataque de aplastamiento con el garrote
     * @return Valor numérico que representa el daño causado
     */
    int aplastar();
    
    /**
     * @brief Verifica si el garrote tiene clavos
     * @return true si tiene clavos, false en caso contrario
     */
    bool estaClaveteado() const;
    
    /**
     * @brief Coloca o quita clavos del garrote
     * @param poner true para colocar clavos, false para quitarlos
     */
    void ponerQuitarClavos(bool poner);
    
    /**
     * @brief Obtiene el bonus de aturdimiento del garrote
     * @return Valor numérico que representa el bonus de aturdimiento
     */
    int getBonusAturdimiento() const;
    
    /**
     * @brief Refuerza la madera del garrote para aumentar su durabilidad
     */
    void reforzarMadera();

};
