#pragma once

#include "../Mago.hpp"

/**
 * @brief Clase que representa un personaje de tipo Hechicero
 * 
 * Implementa una especialización de Mago enfocada en poder arcano,
 * manipulación del tiempo y utilización de familiares mágicos.
 */
class Hechicero : public Mago {
private:
    int poderArcano;
    bool bastionArcano;
    int manipulacionTiempo;
    string familiarNombre;
    bool familiarActivo;

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Hechicero
     * @param n Nombre del hechicero
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
     * @param poderArc Nivel de poder arcano
     * @param bastion Indica si tiene bastión arcano activo inicialmente
     * @param manipTiempo Nivel de habilidad para manipulación temporal
     * @param familiar Nombre del familiar mágico
     */
    Hechicero(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
              int manaMax, EscuelaMagia esc, FuentePoder fp, 
              int poderArc, bool bastion, int manipTiempo, string familiar);
    
    // ==========================================
    // ACCESO Y MODIFICACIÓN DE ATRIBUTOS
    // ==========================================
    
    /**
     * @brief Obtiene el nivel de poder arcano del hechicero
     * @return Valor numérico que representa el poder arcano
     */
    int getPoder() const;
    
    /**
     * @brief Aumenta el poder arcano del hechicero
     * @param cantidad Cantidad de poder arcano a añadir
     */
    void aumentarPoder(int cantidad);
    
    // ==========================================
    // HABILIDADES DE HECHICERO
    // ==========================================
    
    /**
     * @brief Activa una barrera mágica que protege contra energías arcanas
     * @return true si se activó el bastión, false si ya estaba activo o faltó maná
     */
    bool activarBastionArcano();
    
    /**
     * @brief Invoca al familiar mágico del hechicero
     */
    void invocarFamiliar();
    
    /**
     * @brief Manipula el flujo temporal para causar daño
     * @return Valor numérico que representa el daño causado
     */
    int alterarTiempo();
    
    // ==========================================
    // SOBRESCRITURAS DE MÉTODOS BASE
    // ==========================================
    
    /**
     * @brief Muestra información detallada sobre el hechicero
     */
    void mostrarInfo() const override;
    
    /**
     * @brief Implementación especializada de lanzamiento de hechizos
     * 
     * Los hechiceros potencian sus hechizos con poder arcano y
     * pueden obtener bonificaciones adicionales de sus familiares.
     * 
     * @param nombreHechizo Nombre del hechizo a lanzar
     * @return Valor numérico que representa el efecto del hechizo
     */
    int lanzarHechizo(const string& nombreHechizo) override;
};
