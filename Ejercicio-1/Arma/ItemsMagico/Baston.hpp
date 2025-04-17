#pragma once

#include "../ObjetoMagico.hpp"
#include "../enumArmas.hpp"

/**
 * @brief Clase Baston que hereda de ObjetoMagico
 * 
 * Define los atributos y métodos específicos de un bastón mágico,
 * incluyendo su capacidad para lanzar rayos mágicos y su elemento preferido.
 */
class Baston : public ObjetoMagico {
private:
    TipoMadera tipoMadera; 
    TipoGema gemaIncrustada; 
    int nivelEncantamiento; 
    ElementoMagico elementoPreferido; 

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Baston
     * @param n Nombre del bastón
     * @param pm Poder mágico base
     * @param dm Durabilidad máxima
     * @param p Peso del bastón
     * @param r Rareza del bastón
     * @param eam Energía arcana máxima
     * @param tm Tipo de madera
     * @param gi Gema incrustada
     * @param ne Nivel de encantamiento
     * @param elem Elemento mágico preferido
     */
    Baston(string n, int pm, int dm, double p, Rarity r, int eam, 
           TipoMadera tm, TipoGema gi, int ne, ElementoMagico elem);

    // ==========================================
    // MÉTODOS DERIVADOS DE INTERFAZARMAS
    // ==========================================
    
    int usar() override;
    void mostrarInfo() const override;

    // ==========================================
    // MÉTODOS PROPIOS DE LA CLASE BASTON
    // ==========================================
    
    /**
     * @brief Lanza un rayo mágico del elemento preferido
     * @return Valor numérico que representa el daño causado
     */
    int lanzarRayoMagico();
    
    /**
     * @brief Mejora el nivel de encantamiento del bastón
     * @param cantidad Cantidad en que se mejora el encantamiento
     */
    void mejorarEncantamiento(int cantidad);
    
    /**
     * @brief Obtiene el nivel de encantamiento del bastón
     * @return Valor numérico del nivel de encantamiento
     */
    int getNivelEncantamiento() const;
    
    /**
     * @brief Verifica si el bastón tiene una gema incrustada
     * @return true si tiene gema, false si no tiene
     */
    bool tieneGema() const;
    
    /**
     * @brief Cambia la gema incrustada en el bastón
     * 
     * También puede modificar el elemento preferido y otras
     * estadísticas dependiendo de la nueva gema.
     * 
     * @param nuevaGema Tipo de la nueva gema a incrustar
     */
    void cambiarGema(TipoGema nuevaGema);
    
    /**
     * @brief Obtiene el elemento mágico preferido del bastón
     * @return Elemento mágico preferido
     */
    ElementoMagico getElementoBaston(); 
};
