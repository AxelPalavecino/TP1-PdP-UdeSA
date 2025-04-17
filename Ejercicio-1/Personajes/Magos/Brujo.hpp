#pragma once

#include "../Mago.hpp"
#include <vector>  // Añadir inclusión para vector

/**
 * @brief Clase que representa un personaje de tipo Brujo
 * 
 * Implementa una especialización de Mago enfocada en pactos con entidades
 * superiores, maleficios oscuros y sacrificios de vida por poder.
 */
class Brujo : public Mago {
private:
    string nombrePatron;
    int pactoDemoniaco;
    vector<string> maleficiosConocidos;
    int corrupcionAlma;
    bool maldicionActiva;

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Brujo
     * @param n Nombre del brujo
     * @param nivel Nivel del personaje
     * @param hp Puntos de vida máximos
     * @param r Raza del personaje
     * @param fue Puntos de fuerza
     * @param des Puntos de destreza
     * @param con Puntos de constitución
     * @param inte Puntos de inteligencia
     * @param manaMax Maná máximo
     * @param esc Escuela de magia
     * @param fp Fuente de poder
     * @param patron Nombre del patrón del brujo
     * @param pacto Nivel de pacto demoníaco
     * @param corrupcion Nivel de corrupción del alma
     * @param maldicion Indica si tiene una maldición activa
     */
    Brujo(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
          int manaMax, EscuelaMagia esc, FuentePoder fp,
          string patron, int pacto, int corrupcion, bool maldicion);
    
    // ==========================================
    // HABILIDADES DE BRUJO
    // ==========================================
    
    /**
     * @brief Invoca el poder del patrón del brujo
     * @return Valor numérico que representa el daño causado
     */
    int invocarPatron();
    
    /**
     * @brief Lanza un maleficio específico
     * @param nombreMaleficio Nombre del maleficio a lanzar
     * @return Valor numérico que representa el daño causado
     */
    int lanzarMaleficio(const string& nombreMaleficio);
    
    /**
     * @brief Aprende un nuevo maleficio
     * @param nombreMaleficio Nombre del maleficio a aprender
     * @return true si se aprendió el maleficio, false si ya lo conocía
     */
    bool aprenderMaleficio(const string& nombreMaleficio);
    
    /**
     * @brief Sacrifica puntos de vida para obtener maná
     * @param cantidad Cantidad de vida a sacrificar
     */
    void sacrificarVida(int cantidad);
    
    /**
     * @brief Drena poder vital de un objetivo
     * @return Valor numérico que representa el daño causado y vida absorbida
     */
    int drenajeDePoder();
    
    // ==========================================
    // SOBRESCRITURAS DE MÉTODOS BASE
    // ==========================================
    
    /**
     * @brief Muestra información detallada sobre el brujo
     */
    void mostrarInfo() const override;
    
    /**
     * @brief Implementación especializada de gasto de maná
     * 
     * Los brujos pueden optar por sacrificar vida si no tienen maná suficiente.
     * 
     * @param cantidad Cantidad de maná a gastar
     * @return true si pudo gastar el maná o sacrificar vida, false en caso contrario
     */
    bool gastarMana(int cantidad) override;
    
    /**
     * @brief Implementación especializada de lanzamiento de hechizos
     * 
     * Los brujos potencian sus hechizos con la corrupción de su alma.
     * 
     * @param nombreHechizo Nombre del hechizo a lanzar
     * @return Valor numérico que representa el efecto del hechizo
     */
    int lanzarHechizo(const string& nombreHechizo) override;
};
