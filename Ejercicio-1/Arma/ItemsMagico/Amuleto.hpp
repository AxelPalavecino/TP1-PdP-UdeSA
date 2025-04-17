#pragma once

#include "../ObjetoMagico.hpp"
#include "../enumArmas.hpp"

/**
 * @brief Clase Amuleto que hereda de ObjetoMagico
 * 
 * Define los atributos y métodos específicos de un amuleto mágico,
 * incluyendo su bonus pasivo y la capacidad de sintonizarse con él.
 */
class Amuleto : public ObjetoMagico {
private:
    string bonusPasivo; 
    int valorBonus; 
    MaterialAmuleto material; 
    bool requiereSintonizacion; 
    bool estaSintonizado; 

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Amuleto
     * @param n Nombre del amuleto
     * @param pm Poder mágico base
     * @param dm Durabilidad máxima
     * @param p Peso del amuleto
     * @param r Rareza del amuleto
     * @param eam Energía arcana máxima
     * @param bp Descripción del bonus pasivo
     * @param vb Valor numérico del bonus
     * @param m Material del amuleto
     * @param rs Indica si requiere sintonización
     */
    Amuleto(string n, int pm, int dm, double p, Rarity r, int eam, 
            string bp, int vb, MaterialAmuleto m, bool rs);

    // ==========================================
    // MÉTODOS DERIVADOS DE INTERFAZARMAS
    // ==========================================
    
    int usar() override;
    void mostrarInfo() const override;

    // ==========================================
    // MÉTODOS PROPIOS DE LA CLASE AMULETO
    // ==========================================
    
    /**
     * @brief Obtiene la descripción del bonus pasivo
     * @return String con la descripción del bonus
     */
    string getBonusPasivo() const;
    
    /**
     * @brief Obtiene el valor numérico del bonus
     * @return Valor del bonus
     */
    int getValorBonus() const;
    
    /**
     * @brief Verifica si el amuleto requiere sintonización
     * @return true si requiere sintonización, false en caso contrario
     */
    bool necesitaSintonizacion() const;
    
    /**
     * @brief Intenta sintonizar con el amuleto
     * 
     * Si el amuleto requiere sintonización, establece la conexión
     * para permitir su uso completo.
     * 
     * @return true si se realizó la sintonización o ya estaba sintonizado, false en caso contrario
     */
    bool sintonizar();
    
    /**
     * @brief Rompe la sintonización con el amuleto
     * @return true si se rompió la sintonización, false si no estaba sintonizado
     */
    bool desintonizar();
};
