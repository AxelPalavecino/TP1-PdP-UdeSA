#pragma once

#include "InterfazArmas.hpp"
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Clase abstracta para implementar objetos mágicos
 * 
 * Define la base para todos los objetos mágicos como pociones, amuletos, bastones, etc.
 * Implementa la interfaz básica para armas/objetos y añade funcionalidades específicas
 * para manejar la energía arcana.
 */
class ObjetoMagico : public InterfazArmas {
protected:
    string nombre;
    int poderMagico; 
    int durabilidadMaxima; 
    int durabilidadActual; 
    double peso; 
    Rarity rareza; 
    int energiaArcanaMaxima; 
    int energiaArcanaActual; 

public:

    // ==========================================
    // CONSTRUCTORES Y DESTRUCTORES
    // ==========================================

    /**
     * @brief Constructor de la clase ObjetoMagico
     * @param n Nombre del objeto
     * @param pm Poder mágico base
     * @param dm Durabilidad máxima
     * @param p Peso del objeto
     * @param r Rareza del objeto
     * @param eam Energía arcana máxima
     */
    ObjetoMagico(string n, int pm, int dm, double p, Rarity r, int eam);
    
    /**
     * @brief Destructor virtual de la clase ObjetoMagico
     */
    virtual ~ObjetoMagico() = default;

    // ==========================================
    // METODOS DERIVADOS DE INTERFAZARMAS
    // ==========================================

    void setNombre(const string& nombreArg) override;
    string getNombre() const override;
    int getPoder() const override;
    int getDurabilidadActual() const override;
    int getDurabilidadMaxima() const override; 
    Rarity getRareza() const override;
    void reparar(int cantidad) override;
    int usar() override;
    void mostrarInfo() const override;

    // ==========================================
    // METODOS PROPIOS DE LA CLASE ABSTRACTA
    // ==========================================

    /**
     * @brief Obtiene el peso del objeto mágico
     * @return Valor numérico que representa el peso
     */
    double getPeso() const;
    
    /**
     * @brief Obtiene la energía arcana actual del objeto
     * @return Valor numérico de la energía arcana actual
     */
    int getEnergiaArcanaActual() const;
    
    /**
     * @brief Obtiene la energía arcana máxima del objeto
     * @return Valor numérico de la energía arcana máxima
     */
    int getEnergiaArcanaMaxima() const;
    
    /**
     * @brief Recarga la energía arcana del objeto
     * @param cantidad La cantidad de energía arcana a recargar
     */
    virtual void recargarEnergia(int cantidad);

protected:
    /**
     * @brief Aplica el efecto mágico específico del objeto
     * @return Valor numérico que representa el efecto aplicado
     */
    virtual int aplicarEfecto();
    
    /**
     * @brief Calcula el costo de energía arcana al usar el objeto
     * @return Valor numérico que representa el costo de energía
     */
    virtual int calcularCostoEnergia() const;
    
    /**
     * @brief Reduce la durabilidad del objeto mágico
     * @param cantidad La cantidad de durabilidad a reducir
     */
    virtual void reducirDurabilidad(int cantidad);
};
