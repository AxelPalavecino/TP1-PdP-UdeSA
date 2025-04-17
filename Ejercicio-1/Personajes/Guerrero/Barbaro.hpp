#pragma once

#include "../Guerrero.hpp"

/**
 * @brief Clase que representa un personaje de tipo Barbaro
 * 
 * Implementa una especializacion de Guerrero enfocada en combate salvaje,
 * frenesi de batalla y resistencia al dolor.
 */
class Barbaro : public Guerrero {
private:
    bool frenesi;
    int resistenciaDolor;
    int furiaCombate;
    string gritoBatalla;
    int superacionLimites;

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Barbaro
     * @param n Nombre del barbaro
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
     * @param resDolor Resistencia al dolor
     * @param furia Furia de combate inicial
     * @param grito Grito de batalla del barbaro
     * @param supLimites Capacidad de superacion de limites
     */
    Barbaro(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
            int estMax, EstiloCombate est, TipoArmadura ta, int defBase, int resFis,
            int resDolor, int furia, string grito, int supLimites);
    
    // ==========================================
    // HABILIDADES DE BARBARO
    // ==========================================
    
    /**
     * @brief Activa el estado de frenesi del barbaro
     * 
     * En estado de frenesi, el barbaro aumenta su fuerza y resistencia,
     * pero pierde control sobre sus acciones.
     * 
     * @return true si entro en frenesi, false si ya estaba o no pudo
     */
    bool entrarEnFrenesi();
    
    /**
     * @brief Aumenta el contador de furia del barbaro
     * @param cantidad Cantidad de furia a aumentar
     */
    void aumentarFuria(int cantidad);
    
    /**
     * @brief Lanza el grito de batalla del barbaro
     * 
     * El grito atemoriza a los enemigos reduciendo su moral.
     * 
     * @return Valor numerico que representa el efecto del grito
     */
    int gritarEnBatalla();
    
    /**
     * @brief Permite al barbaro ignorar parte de sus heridas
     * 
     * Utiliza su resistencia al dolor para recuperar puntos de vida.
     */
    void resistirDolor();
    
    /**
     * @brief Realiza un ataque salvaje y descontrolado
     * @return Valor numerico que representa el daño causado
     */
    int golpeSalvaje();
    
    // ==========================================
    // SOBRESCRITURAS DE METODOS BASE
    // ==========================================
    
    /**
     * @brief Muestra informacion detallada sobre el barbaro
     */
    void mostrarInfo() const override;
    
    /**
     * @brief Implementacion especializada para recibir daño
     * 
     * En estado de frenesi, reduce el daño recibido y aumenta su furia.
     * 
     * @param cantidad Cantidad de daño a recibir
     * @param esCombatePPT Indica si es un combate PPT
     * @return true si sigue vivo, false si ha muerto
     */
    bool recibirDanio(int cantidad, bool esCombatePPT) override;
};
