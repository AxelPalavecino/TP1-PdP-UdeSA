#pragma once

#include "../Guerrero.hpp"
#include <vector>

/**
 * @brief Clase que representa un personaje de tipo Mercenario
 * 
 * Implementa una especialización de Guerrero enfocada en contratos,
 * recompensas, habilidades de sigilo y negociación.
 */
class Mercenario : public Guerrero {
private:
    int oro;
    vector<string> contratos;
    int reputacion;
    int bonusSigilo;
    string ultimoEmpleador;

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Mercenario
     * @param n Nombre del mercenario
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
     * @param monedas Cantidad inicial de oro
     * @param rep Puntos de reputación iniciales
     * @param sigilo Bonus de sigilo del mercenario
     * @param empleador Nombre del último empleador
     */
    Mercenario(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
               int estMax, EstiloCombate est, TipoArmadura ta, int defBase, int resFis,
               int monedas, int rep, int sigilo, string empleador);
    
    // ==========================================
    // GESTIÓN DE CONTRATOS
    // ==========================================
    
    /**
     * @brief Acepta un nuevo contrato para el mercenario
     * @param objetivo Nombre del objetivo del contrato
     * @param recompensa Cantidad de oro ofrecida como recompensa
     * @return true si se acepta el contrato, false si ya lo tenía o es inválido
     */
    bool aceptarContrato(string objetivo, int recompensa);
    
    /**
     * @brief Marca un contrato como completado
     * @param objetivo Nombre del objetivo del contrato completado
     * @return true si se completa el contrato, false si no lo tenía
     */
    bool completarContrato(string objetivo);
    
    /**
     * @brief Añade oro al mercenario por una recompensa cobrada
     * @param cantidad Cantidad de oro a cobrar
     */
    void cobrarRecompensa(int cantidad);
    
    // ==========================================
    // HABILIDADES DE MERCENARIO
    // ==========================================
    
    /**
     * @brief Realiza un ataque desde las sombras
     * @return Valor numérico que representa el daño causado
     */
    int atacarPorSorpresa();
    
    /**
     * @brief Mejora el precio de una transacción mediante negociación
     * @param precioBase Precio base antes de negociar
     * @return Valor numérico que representa el precio mejorado
     */
    int negociarMejorPrecio(int precioBase);
    
    // ==========================================
    // SOBRESCRITURAS DE MÉTODOS BASE
    // ==========================================
    
    /**
     * @brief Muestra información detallada sobre el mercenario
     */
    void mostrarInfo() const override;
    
    /**
     * @brief Implementación especializada de ataque para mercenarios
     * @param movimiento Tipo de movimiento de ataque a realizar
     * @return Valor numérico que representa el daño causado
     */
    int atacar(MovimientoCombate movimiento) override;
};
