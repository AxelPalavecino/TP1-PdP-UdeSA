#pragma once

#include "../ObjetoMagico.hpp"
#include "../enumArmas.hpp"

/**
 * @brief Clase Pocion que hereda de ObjetoMagico
 * 
 * Define los atributos y métodos específicos de una poción, incluyendo
 * su efecto, potencia, dosis y opciones para combinarla con otras pociones.
 */
class Pocion : public ObjetoMagico {
private:
    EfectoPocion efecto; 
    int potenciaEfecto; 
    int dosisRestantes; 
    ColorPocion colorLiquido; 
    bool esPermanente; 

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Pocion
     * @param n Nombre de la poción
     * @param pm Poder mágico base
     * @param dm Durabilidad máxima (dosis máximas)
     * @param p Peso de la poción
     * @param r Rareza de la poción
     * @param eam Energía arcana máxima
     * @param ef Efecto que produce la poción
     * @param pe Potencia del efecto
     * @param dr Dosis restantes iniciales
     * @param cl Color del líquido
     * @param perm Indica si el efecto es permanente
     */
    Pocion(string n, int pm, int dm, double p, Rarity r, int eam, EfectoPocion ef, 
           int pe, int dr, ColorPocion cl, bool perm);

    // ==========================================
    // MÉTODOS DERIVADOS DE INTERFAZARMAS
    // ==========================================
    
    int usar() override;
    void mostrarInfo() const override;

    // ==========================================
    // MÉTODOS PROPIOS DE LA CLASE POCION
    // ==========================================
    
    /**
     * @brief Obtiene el efecto de la poción
     * @return Tipo de efecto que produce la poción
     */
    EfectoPocion getEfecto() const;
    
    /**
     * @brief Obtiene la potencia del efecto de la poción
     * @return Valor numérico que representa la potencia
     */
    int getPotenciaEfecto() const;
    
    /**
     * @brief Obtiene la cantidad de dosis restantes de la poción
     * @return Número de dosis que quedan
     */
    int getDosisRestantes() const;
    
    /**
     * @brief Verifica si la poción está vacía (sin dosis)
     * @return true si no quedan dosis, false en caso contrario
     */
    bool estaVacia() const;
    
    /**
     * @brief Combina esta poción con otra del mismo efecto
     * 
     * Si las pociones tienen el mismo efecto y no son permanentes,
     * se combinan sumando sus dosis y potencias.
     * 
     * @param otraPocion La poción con la que se va a combinar
     */
    void combinar(const Pocion& otraPocion);

protected:
    // ==========================================
    // MÉTODOS PROTEGIDOS
    // ==========================================
    
    /**
     * @brief Implementación específica del efecto de la poción
     * @return Valor numérico que representa la magnitud del efecto
     */
    int aplicarEfecto() override;
    
    /**
     * @brief Calcula el costo de energía arcana para usar la poción
     * @return Valor numérico del costo de energía
     */
    int calcularCostoEnergia() const override;
};
