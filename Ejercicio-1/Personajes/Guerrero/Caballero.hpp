#pragma once

#include "../Guerrero.hpp"

/**
 * @brief Clase que representa un personaje de tipo Caballero
 * 
 * Implementa una especializacion de Guerrero enfocada en honor,
 * juramentos, combate montado y defensa de aliados.
 */
class Caballero : public Guerrero {
private:
    int honor;
    string juramento;
    bool montado;
    int habilidadEcuestre;
    string orden;

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Caballero
     * @param n Nombre del caballero
     * @param nivel Nivel del personaje
     * @param hp Puntos de vida maximos
     * @param r Raza del personaje
     * @param fue Puntos de fuerza
     * @param des Puntos de destreza
     * @param con Puntos de constitucion
     * @param inte Puntos de inteligencia
     * @param estMax Estamina maxima
     * @param est Estilo de combate
     * @param ta Tipo de armadura
     * @param defBase Defensa base
     * @param resFis Resistencia fisica
     * @param hon Puntos de honor iniciales
     * @param jur Juramento del caballero
     * @param mont Indica si está montado inicialmente
     * @param habEc Habilidad ecuestre
     * @param ord Orden de caballeria a la que pertenece
     */
    Caballero(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
              int estMax, EstiloCombate est, TipoArmadura ta, int defBase, int resFis,
              int hon, string jur, bool mont, int habEc, string ord);
    
    // ==========================================
    // GESTION DE HONOR
    // ==========================================
    
    /**
     * @brief Aumenta los puntos de honor del caballero
     * @param cantidad Cantidad de honor a ganar
     */
    void ganarHonor(int cantidad);
    
    /**
     * @brief Reduce los puntos de honor del caballero
     * @param cantidad Cantidad de honor a perder
     */
    void perderHonor(int cantidad);
    
    // ==========================================
    // HABILIDADES DE CABALLERO
    // ==========================================
    
    /**
     * @brief Realiza una carga a caballo contra el enemigo
     * 
     * Solo disponible si el caballero está montado.
     * 
     * @return Valor numerico que representa el daño causado
     */
    int cargarAcaballo();
    
    /**
     * @brief Defiende a un aliado, otorgandole proteccion
     * @param nombreAliado Nombre del aliado a defender
     * @return Valor numerico que representa el bonus de defensa otorgado
     */
    int defenderAliado(string nombreAliado);
    
    /**
     * @brief Invoca el juramento sagrado del caballero
     * @return Valor numerico que representa el efecto del juramento
     */
    int juramentoSagrado();
    
    // ==========================================
    // SOBRESCRITURAS DE METODOS BASE
    // ==========================================
    
    /**
     * @brief Muestra informacion detallada sobre el caballero
     */
    void mostrarInfo() const override;
    
    /**
     * @brief Implementacion especializada para recibir daño
     * 
     * Los caballeros pueden tener bonificaciones defensivas especiales.
     * 
     * @param cantidad Cantidad de daño a recibir
     * @param esCombatePPT Indica si es un combate PPT
     * @return true si sigue vivo, false si ha muerto
     */
    bool recibirDanio(int cantidad, bool esCombatePPT) override;
};
