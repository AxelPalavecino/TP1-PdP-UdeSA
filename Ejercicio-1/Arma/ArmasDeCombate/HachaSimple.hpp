#pragma once

#include "../ArmaDeCombate.hpp"
#include "../enumArmas.hpp"

/**
 * @brief Clase HachaSimple que hereda de ArmaDeCombate
 * 
 * Define los atributos y métodos específicos de un hacha simple, incluyendo
 * su capacidad para talar, ser arrojada y sus propiedades físicas.
 */
class HachaSimple : public ArmaDeCombate {
private:
    TipoMango tipoMango; 
    double longitudMango; 
    bool esArrojadiza; 
    int bonusVsMadera; 
    string marcaHerrero; 

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase HachaSimple
     * @param n Nombre del hacha
     * @param df Daño físico base
     * @param dm Durabilidad máxima
     * @param p Peso del hacha
     * @param r Rareza del hacha
     * @param nf Nivel de filo inicial
     * @param tm Tipo de mango
     * @param lm Longitud del mango
     * @param ea Indica si el hacha es arrojadiza
     * @param bvm Bonus de daño contra madera
     * @param mh Marca del herrero que fabricó el hacha
     */
    HachaSimple(string n, int df, int dm, double p, Rarity r, int nf, 
                TipoMango tm, double lm, bool ea, int bvm, string mh);

    // ==========================================
    // MÉTODOS DERIVADOS DE INTERFAZARMAS
    // ==========================================
    
    int usar() override;
    void mostrarInfo() const override;

    // ==========================================
    // MÉTODOS PROPIOS DE LA CLASE HACHASIMPLE
    // ==========================================
    
    /**
     * @brief Utiliza el hacha para talar madera
     * @return Valor numérico que representa el daño al talar
     */
    int talar();
    
    /**
     * @brief Lanza el hacha como proyectil si es arrojadiza
     * @return Valor numérico que representa el daño causado por el lanzamiento
     */
    int lanzar();
    
    /**
     * @brief Obtiene la longitud del mango del hacha
     * @return Valor numérico que representa la longitud del mango en metros
     */
    double getLongitudMango() const;
    
    /**
     * @brief Verifica si el hacha puede ser arrojada
     * @return true si el hacha es arrojadiza, false en caso contrario
     */
    bool puedeArrojarse() const;
    
    /**
     * @brief Obtiene la marca del herrero que fabricó el hacha
     * @return String con el nombre del herrero
     */
    string getMarcaHerrero() const;
};
