#pragma once

#include "../ArmaDeCombate.hpp"

/**
 * @brief Clase HachaDoble que hereda de ArmaDeCombate
 * 
 * Define los atributos y métodos específicos de un hacha doble, incluyendo
 * sus ataques especiales como hendidura y torbellino, además de sus propiedades
 * como balance, inscripción rúnica y bonificación contra armaduras.
 */
class HachaDoble : public ArmaDeCombate {
private:
    double balance; 
    int penalizacionParada; 
    bool requiereDosManos; 
    string inscripcionRuna; 
    int bonusVsArmadura; 

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase HachaDoble
     * @param n Nombre del hacha doble
     * @param df Daño físico base
     * @param dm Durabilidad máxima
     * @param p Peso del hacha
     * @param r Rareza del hacha
     * @param nf Nivel de filo inicial
     * @param b Balance del hacha
     * @param pp Penalización para parar ataques
     * @param rdm Indica si requiere dos manos para usarse
     * @param ir Inscripción rúnica en el hacha
     * @param bva Bonus de daño contra armaduras
     */
    HachaDoble(string n, int df, int dm, double p, Rarity r, int nf, 
               double b, int pp, bool rdm, string ir, int bva);

    // ==========================================
    // MÉTODOS DERIVADOS DE INTERFAZARMAS
    // ==========================================
    
    int usar() override;
    void mostrarInfo() const override;

    // ==========================================
    // MÉTODOS PROPIOS DE LA CLASE HACHADOBLE
    // ==========================================
    
    /**
     * @brief Realiza un ataque de hendidura con el hacha doble
     * @return Valor numérico que representa el daño causado
     */
    int hendidura();
    
    /**
     * @brief Verifica si el hacha requiere dos manos para usarse
     * @return true si requiere dos manos, false en caso contrario
     */
    bool esADosManos() const;
    
    /**
     * @brief Obtiene el balance del hacha doble
     * @return Valor numérico que representa el balance
     */
    double getBalance() const;
    
    /**
     * @brief Lee la inscripción rúnica del hacha
     * @return String con la inscripción o un mensaje si no tiene
     */
    string leerInscripcion() const;
    
    /**
     * @brief Realiza un ataque giratorio con el hacha doble
     * @return Valor numérico que representa el daño causado
     */
    int ataqueTorbellino();
};
