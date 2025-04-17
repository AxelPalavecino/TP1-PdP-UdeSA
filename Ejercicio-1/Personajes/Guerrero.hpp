#pragma once

#include "InterfazPersonaje.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>

/**
 * @brief Clase que representa un personaje de tipo Guerrero
 * 
 * Implementa la interfaz de personaje con funcionalidades especificas
 * para guerreros, como estamina, estilos de combate y tipo de armadura.
 */
class Guerrero : public InterfazPersonaje {
protected:
    // ==========================================
    // ATRIBUTOS BASICOS
    // ==========================================
    
    string nombre;
    int nivelPersonaje;
    int hpMax;
    int hpActual;
    Raza raza;
    int fuerza;
    int destreza;
    int constitucion;
    int inteligencia;
    vector<unique_ptr<InterfazArmas>> inventarioArmas;
    int armaEquipadaPos; // -1 si no hay arma equipada, 0+ para índice en el inventario
    static const int MAX_ARMAS = 2;
    
    // Atributos para combate PPT
    int hpOriginalParaCombatePPT = 100;
    bool enModoCombatePPT = false;
    
    // ==========================================
    // ATRIBUTOS ESPECIFICOS DE GUERRERO
    // ==========================================
    
    int estaminaMaxima;
    int estaminaActual;
    EstiloCombate estilo;
    TipoArmadura tipoArmadura;
    int defensaBase;
    int resistenciaFisica;
    
public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Guerrero
     * @param n Nombre del guerrero
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
     */
    Guerrero(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
             int estMax, EstiloCombate est, TipoArmadura ta, int defBase, int resFis);
    
    // ==========================================
    // IMPLEMENTACIONES DE INTERFAZPERSONAJE
    // ==========================================
    
    string getNombre() const override;
    void setNombre(const string& nombre) override;
    int getHP() const override;
    bool recibirDanio(int cantidad, bool esCombatePPT) override;
    void curar(int cantidad) override;
    bool agregarArma(unique_ptr<InterfazArmas> arma) override;
    unique_ptr<InterfazArmas> quitarArma(int posicion) override;
    InterfazArmas* getArma(int posicion) const override;
    int atacar(MovimientoCombate movimiento) override;
    void mostrarInfo() const override;
    void mostrarInventario() const override;
    bool setHPParaCombatePPT() override;
    bool restaurarHPOriginal() override;
    
    // ==========================================
    // GETTERS Y SETTERS GENERALES
    // ==========================================
    
    /**
     * @brief Obtiene el nivel del personaje
     * @return Nivel actual del personaje
     */
    int getNivel() const;
    
    /**
     * @brief Obtiene la raza del personaje
     * @return Raza del personaje
     */
    Raza getRaza() const;
    
    /**
     * @brief Obtiene los puntos de fuerza del personaje
     * @return Puntos de fuerza
     */
    int getFuerza() const;
    
    /**
     * @brief Obtiene los puntos de destreza del personaje
     * @return Puntos de destreza
     */
    int getDestreza() const;
    
    /**
     * @brief Obtiene los puntos de constitucion del personaje
     * @return Puntos de constitucion
     */
    int getConstitucion() const;
    
    /**
     * @brief Obtiene los puntos de inteligencia del personaje
     * @return Puntos de inteligencia
     */
    int getInteligencia() const;
    
    // ==========================================
    // GESTION DE ARMAS
    // ==========================================
    
    /**
     * @brief Equipa un arma del inventario
     * @param posicion Indice del arma a equipar
     * @return true si se equipo correctamente, false en caso contrario
     */
    bool equiparArma(int posicion);
    
    /**
     * @brief Obtiene la posicion del arma equipada
     * @return Indice del arma equipada o -1 si no hay arma equipada
     */
    int getArmaEquipadaPos() const;
    
    /**
     * @brief Obtiene una referencia al arma equipada
     * @return Puntero al arma equipada o nullptr si no hay arma equipada
     */
    InterfazArmas* getArmaEquipada() const;
    
    /**
     * @brief Calcula el daño segun el movimiento y el arma usada
     * @param movimiento Tipo de movimiento de ataque
     * @param armaUsada Arma con la que se realiza el ataque
     * @return Valor numerico que representa el daño calculado
     */
    virtual int resolverMovimiento(MovimientoCombate movimiento, InterfazArmas* armaUsada) const;
    
    // ==========================================
    // GESTION DE ESTAMINA Y DEFENSA
    // ==========================================
    
    /**
     * @brief Obtiene la estamina actual del guerrero
     * @return Cantidad de estamina actual
     */
    int getEstamina() const;
    
    /**
     * @brief Consume estamina para realizar acciones
     * @param cantidad Cantidad de estamina a gastar
     * @return true si se pudo gastar la estamina, false si no hay suficiente
     */
    bool gastarEstamina(int cantidad);
    
    /**
     * @brief Recupera estamina
     * @param cantidad Cantidad de estamina a recuperar
     */
    void recuperarEstamina(int cantidad);
    
    /**
     * @brief Obtiene el estilo de combate del guerrero
     * @return Estilo de combate del guerrero
     */
    EstiloCombate getEstiloCombate() const;
    
    /**
     * @brief Obtiene el tipo de armadura del guerrero
     * @return Tipo de armadura del guerrero
     */
    TipoArmadura getTipoArmadura() const;
    
    /**
     * @brief Obtiene la defensa base del guerrero
     * @return Valor numerico que representa la defensa base
     */
    int getDefensaBase() const;
    
    /**
     * @brief Obtiene la resistencia fisica del guerrero
     * @return Valor numerico que representa la resistencia fisica
     */
    int getResistenciaFisica() const;
    
    // ==========================================
    // HABILIDADES DE GUERRERO
    // ==========================================
    
    /**
     * @brief Ejecuta una tecnica especial de combate
     * @return Valor numerico que representa el daño causado
     */
    virtual int ejecutarTecnicaEspecial();
    
    /**
     * @brief Aumenta temporalmente la postura defensiva
     * @return Valor numerico que representa el bonus de defensa obtenido
     */
    virtual int aumentarPosturaDefensiva();
    
    /**
     * @brief Provoca a los enemigos para que lo ataquen
     * @return Valor numerico que representa el efecto de provocacion
     */
    virtual int provocarEnemigo();
    
    /**
     * @brief Realiza una carga contra un enemigo especifico
     * @param nombreEnemigo Nombre del enemigo objetivo
     * @return Valor numerico que representa el daño causado
     */
    virtual int cargarContra(string nombreEnemigo);
    
    /**
     * @brief Bloquea un ataque con el escudo
     * @return Valor numerico que representa la cantidad de daño bloqueado
     */
    virtual int bloquearConEscudo();
};
