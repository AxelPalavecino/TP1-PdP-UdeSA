#pragma once

#include "../Guerrero.hpp"

/**
 * @brief Clase que representa un personaje de tipo Paladín
 * 
 * Implementa una especialización de Guerrero enfocada en fe,
 * poderes sagrados, protección divina y curación.
 */
class Paladin : public Guerrero {
private:
    int fe;
    string deidad;
    int poderSagrado;
    bool auraDivina;
    int nivelDevocion;

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Paladín
     * @param n Nombre del paladín
     * @param nivel Nivel del personaje
     * @param hp Puntos de vida máximos
     * @param r Raza del personaje
     * @param fue Puntos de fuerza
     * @param des Puntos de destreza
     * @param con Puntos de constitución
     * @param inte Puntos de inteligencia
     * @param estMax Estamina máxima
     * @param est Estilo de combate
     * @param ta Tipo de armadura
     * @param defBase Defensa base
     * @param resFis Resistencia física
     * @param fePts Puntos de fe iniciales
     * @param deity Nombre de la deidad a la que sirve
     * @param poderSag Nivel de poder sagrado
     * @param aura Indica si comienza con aura divina activa
     * @param devocion Nivel de devoción inicial
     */
    Paladin(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
            int estMax, EstiloCombate est, TipoArmadura ta, int defBase, int resFis,
            int fePts, string deity, int poderSag, bool aura, int devocion);
    
    // ==========================================
    // HABILIDADES DE PALADÍN
    // ==========================================
    
    /**
     * @brief Invoca un poder de luz sagrada contra enemigos
     * @return Valor numérico que representa el daño causado
     */
    int invocarLuzSagrada();
    
    /**
     * @brief Castiga a enemigos malvados con poder divino
     * @return Valor numérico que representa el daño causado
     */
    int castigarMalvados();
    
    /**
     * @brief Cura heridas mediante imposición de manos
     * @param objetivo Nombre del objetivo a curar
     * @return Cantidad de puntos de vida curados
     */
    int imponerManos(string objetivo);
    
    /**
     * @brief El paladín reza a su deidad para recuperar fe
     */
    void rezar();
    
    /**
     * @brief Activa el aura divina de protección
     * @return true si se activó con éxito, false si ya estaba activa o no hay fe suficiente
     */
    bool activarAuraDivina();
    
    // ==========================================
    // SOBRESCRITURAS DE MÉTODOS BASE
    // ==========================================
    
    /**
     * @brief Muestra información detallada sobre el paladín
     */
    void mostrarInfo() const override;
    
    /**
     * @brief Implementación especializada para recibir daño
     * 
     * El aura divina puede reducir el daño recibido.
     * 
     * @param cantidad Cantidad de daño a recibir
     * @param esCombatePPT Indica si es un combate PPT
     * @return true si sigue vivo, false si ha muerto
     */
    bool recibirDanio(int cantidad, bool esCombatePPT) override;
    
    /**
     * @brief Implementación especializada para curar heridas
     * 
     * La devoción del paladín potencia la curación recibida.
     * 
     * @param cantidad Cantidad de puntos de vida a curar
     */
    void curar(int cantidad) override;
};
