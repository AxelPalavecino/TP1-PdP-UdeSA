#pragma once

#include "../ArmaDeCombate.hpp"
#include "../enumArmas.hpp"

/**
 * @brief Clase Lanza que hereda de ArmaDeCombate
 * 
 * Define los atributos y métodos específicos de una lanza, incluyendo
 * sus habilidades especiales como barrer y preparar contra carga, además
 * de sus propiedades físicas y sus opciones de personalización.
 */
class Lanza : public ArmaDeCombate {
private:
    double longitudAsta; 
    MaterialPuntaLanza materialPunta; 
    bool tieneBandera; 
    int alcance; 
    bool esDesmontable; 
    bool preparadaContraCarga = false; 

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Lanza
     * @param n Nombre de la lanza
     * @param df Daño físico base
     * @param dm Durabilidad máxima
     * @param p Peso de la lanza
     * @param r Rareza de la lanza
     * @param nf Nivel de filo inicial
     * @param la Longitud del asta
     * @param mp Material de la punta
     * @param tb Indica si tiene bandera
     * @param al Alcance de la lanza
     * @param ed Indica si la lanza es desmontable
     */
    Lanza(string n, int df, int dm, double p, Rarity r, int nf, 
          double la, MaterialPuntaLanza mp, bool tb, int al, bool ed);

    // ==========================================
    // MÉTODOS DERIVADOS DE INTERFAZARMAS
    // ==========================================
    
    int usar() override;
    void mostrarInfo() const override;

    // ==========================================
    // MÉTODOS PROPIOS DE LA CLASE LANZA
    // ==========================================
    
    /**
     * @brief Realiza un ataque de barrido con la lanza
     * @return Valor numérico que representa el daño causado
     */
    int barrer();
    
    /**
     * @brief Prepara la lanza para recibir una carga enemiga
     * @return true si la lanza se preparó correctamente, false en caso contrario
     */
    bool prepararContraCarga();
    
    /**
     * @brief Obtiene el alcance de la lanza
     * @return Valor numérico que representa el alcance
     */
    int getAlcance() const;
    
    /**
     * @brief Coloca o quita una bandera en la lanza
     * @param poner true para colocar bandera, false para quitarla
     */
    void ponerQuitarBandera(bool poner);
    
    /**
     * @brief Desmonta la punta de la lanza si es posible
     */
    void desmontarPunta();
};
