#pragma once
#include "InterfazArmas.hpp"
#include <string>
#include <iostream>

using namespace std;

/**
 * @brief Clase abstracta describe las funcionalidades basicas de un Arma de Combate, hereda de InterfazArmas
 */
class ArmaDeCombate : public InterfazArmas {

protected:
    string nombre;
    int danioFisico;
    int durabilidadMaxima; 
    int durabilidadActual; 
    double peso;
    Rarity rareza;
    int nivelFilo;

public:

    // ==========================================
    // CONSTRUCTORES Y DESTRUCTORES
    // ==========================================

    /** 
     * @brief Constructor de la clase ArmaDeCombate
     * @param n Nombre del arma
     * @param df Daño físico base
     * @param dm Durabilidad máxima
     * @param p Peso del arma
     * @param r Rareza del arma
     * @param nf Nivel de filo del arma
     */
    ArmaDeCombate(string n, int df, int dm, double p, Rarity r, int nf);

    /**
     * @brief Destructor de la clase ArmaDeCombate
     */
    virtual ~ArmaDeCombate() = default;

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
     * @brief Obtiene el peso correspondiente a un arma
     * @return El peso correspondiente a un arma
     */
    double getPeso() const;

    /**
     * @brief Obtiene el nivel de filo correspondiente a un arma
     * @return El nivel de filo correspondiente a un arma
     */
    int getNivelFilo() const;
    
    /**
     * @brief Afila un arma una cantidad finita (puede no ser positiva) y devuelve true si se afilo correctamente
     * @param cantidad La cantidad de filo que se le quiere agregar al arma
     * @return true si se afilo correctamente, false si no se pudo afilar (por ejemplo, si el filo es negativo o si el arma ya tiene el filo maximo)
     */
    virtual bool afilar(int cantidad);

protected:
    
    /**
     * @brief Reduce la durabilidad del arma en una cantidad finita (puede no ser positiva) y devuelve true si se redujo correctamente
     * @param cantidad La cantidad de durabilidad que se le quiere reducir al arma
     */
    virtual void reducirDurabilidad(int cantidad);
    
    /**
     * @brief Calcula el bono de daño que tiene el arma por su filo
     * @return El bono de daño que tiene el arma por su filo
     */
    virtual int calcularBonoPorFilo() const;
};
