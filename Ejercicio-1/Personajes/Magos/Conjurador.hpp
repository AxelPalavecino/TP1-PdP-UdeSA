#pragma once

#include "../Mago.hpp"
#include <vector>

/**
 * @brief Clase que representa un personaje de tipo Conjurador
 * 
 * Implementa una especialización de Mago enfocada en invocaciones,
 * pactos con criaturas místicas y manipulación de energías elementales.
 */
class Conjurador : public Mago {
private:
    vector<string> criaturasPactadas;
    int poderInvocacion;
    bool circuloProteccion;
    int energiaElemental;
    string pactoActual;

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Conjurador
     * @param n Nombre del conjurador
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
     * @param poderInv Poder de invocación
     * @param circulo Indica si tiene círculo de protección activo inicialmente
     * @param energiaElem Cantidad inicial de energía elemental
     * @param pacto Nombre del pacto actual inicial
     */
    Conjurador(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
               int manaMax, EscuelaMagia esc, FuentePoder fp, 
               int poderInv, bool circulo, int energiaElem, string pacto);
    
    // ==========================================
    // GESTIÓN DE PACTOS Y CRIATURAS
    // ==========================================
    
    /**
     * @brief Establece un nuevo pacto con una criatura mística
     * @param nombreCriatura Nombre de la criatura para el pacto
     * @return true si se realiza el pacto, false si ya existía o faltó maná
     */
    bool realizarPacto(const string& nombreCriatura);
    
    /**
     * @brief Invoca una criatura pactada para que ataque
     * @param nombreCriatura Nombre de la criatura a invocar
     * @return Valor numérico que representa el daño causado por la criatura
     */
    int invocarCriatura(const string& nombreCriatura);
    
    // ==========================================
    // HABILIDADES DE CONJURADOR
    // ==========================================
    
    /**
     * @brief Crea un círculo mágico de protección
     * @return true si se dibuja el círculo, false si ya existía o faltó maná
     */
    bool dibujarCirculoProteccion();
    
    /**
     * @brief Acumula energía elemental para potenciar hechizos
     */
    void canalizarElementos();
    
    /**
     * @brief Rompe un pacto actual liberando energía explosiva
     * @return Valor numérico que representa el daño causado por la explosión
     */
    int romperPacto();
    
    // ==========================================
    // SOBRESCRITURAS DE MÉTODOS BASE
    // ==========================================
    
    /**
     * @brief Muestra información detallada sobre el conjurador
     */
    void mostrarInfo() const override;
    
    /**
     * @brief Implementación especializada de lanzamiento de hechizos
     * 
     * Los conjuradores pueden potenciar sus hechizos con energía elemental.
     * 
     * @param nombreHechizo Nombre del hechizo a lanzar
     * @return Valor numérico que representa el efecto del hechizo
     */
    int lanzarHechizo(const string& nombreHechizo) override;
};
