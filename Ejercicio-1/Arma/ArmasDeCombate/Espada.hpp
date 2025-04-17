#pragma once

#include "../ArmaDeCombate.hpp"
#include "../enumArmas.hpp"

/**
 * @brief Clase Espada que hereda de ArmaDeCombate
 * 
 * Define los atributos y métodos específicos de una espada, como el tipo de hoja,
 * la longitud de la hoja, el material de la guarda, el bonus de estocada y el estilo de esgrima.
 */
class Espada : public ArmaDeCombate {
private:
    TipoHojaEspada tipoHoja; 
    MaterialGuarda materialGuarda; 
    double longitudHoja; 
    int bonusEstocada; 
    EstiloEsgrima estiloEsgrima; 

public:

    // ==========================================
    // CONSTRUCTORES
    // ==========================================

    /**
     * @brief Constructor de la clase Espada
     * @param n Nombre del arma
     * @param df Daño físico
     * @param dm Durabilidad máxima
     * @param p Peso
     * @param r Rareza
     * @param nf Nivel de filo
     * @param th Tipo de hoja
     * @param mg Material de la guarda
     * @param lh Longitud de la hoja
     * @param be Bonus de estocada
     * @param ee Estilo de esgrima
     */
    Espada(string n, int df, int dm, double p, Rarity r, int nf, 
           TipoHojaEspada th, MaterialGuarda mg, double lh, int be, EstiloEsgrima ee);

    // ==========================================
    // METODOS DERIVADOS DE INTERFAZARMAS
    // ==========================================
           
    int usar() override;
    void mostrarInfo() const override;

    // ==========================================
    // METODOS PROPIOS DE LA CLASE ESPADA
    // ==========================================

    int estocar();
    bool parar();
    TipoHojaEspada getTipoHoja() const;
    double getLongitudHoja() const;
    void pulirHoja();
};
