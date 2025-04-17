#pragma once

#include "../Guerrero.hpp"

/**
 * @brief Clase que representa un personaje de tipo Gladiador
 * 
 * Implementa una especializacion de Guerrero enfocada en combate
 * de arena, intimidacion del publico y tecnicas de combate espectaculares.
 */
class Gladiador : public Guerrero {
private:
    int fama;
    int victorias;
    int derrotas;
    string arenaPrincipal;
    string titulo;
    vector<string> tecnicasEspeciales;

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Gladiador
     * @param n Nombre del gladiador
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
     * @param fam Puntos de fama iniciales
     * @param vict Cantidad de victorias
     * @param derr Cantidad de derrotas
     * @param arena Nombre de la arena principal donde combate
     * @param tit Titulo del gladiador
     */
    Gladiador(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
              int estMax, EstiloCombate est, TipoArmadura ta, int defBase, int resFis,
              int fam, int vict, int derr, string arena, string tit);
    
    // ==========================================
    // GESTION DE FAMA Y COMBATES
    // ==========================================
    
    /**
     * @brief Aumenta la fama del gladiador
     * @param cantidad Cantidad de fama a ganar
     */
    void ganarFama(int cantidad);
    
    /**
     * @brief Registra una victoria en la arena
     * @return Cantidad de fama ganada por la victoria
     */
    int registrarVictoria();
    
    /**
     * @brief Registra una derrota en la arena
     */
    void registrarDerrota();
    
    // ==========================================
    // HABILIDADES DE GLADIADOR
    // ==========================================
    
    /**
     * @brief Aprende una nueva tecnica especial de combate
     * @param nombreTecnica Nombre de la tecnica a aprender
     * @return true si se aprendio con exito, false si ya la conocia
     */
    bool aprenderTecnica(const string& nombreTecnica);
    
    /**
     * @brief Usa una tecnica especial en combate
     * @param nombreTecnica Nombre de la tecnica a utilizar
     * @return Valor numerico que representa el daño causado
     */
    int usarTecnica(const string& nombreTecnica);
    
    /**
     * @brief Intenta intimidar al oponente con su fama y presencia
     * @return Valor numerico que representa el efecto de intimidacion
     */
    int intimidar();
    
    /**
     * @brief Saluda al publico para ganar su favor
     * @return Cantidad de fama ganada por el saludo
     */
    int saludarPublico();
    
    // ==========================================
    // SOBRESCRITURAS DE METODOS BASE
    // ==========================================
    
    /**
     * @brief Muestra informacion detallada sobre el gladiador
     */
    void mostrarInfo() const override;
    
    /**
     * @brief Implementacion personalizada del ataque para gladiadores
     * @param movimiento Tipo de movimiento de ataque a realizar
     * @return Valor numerico que representa el daño causado
     */
    int atacar(MovimientoCombate movimiento) override;
};
