#pragma once

#include "InterfazPersonaje.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>

/**
 * @brief Clase que representa un personaje de tipo Mago
 * 
 * Implementa la interfaz de personaje con funcionalidades especificas
 * para magos, como mana, hechizos y escuelas de magia.
 */
class Mago : public InterfazPersonaje {
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
    // ATRIBUTOS ESPECIFICOS DE MAGO
    // ==========================================
    
    int manaMaximo;
    int manaActual;
    EscuelaMagia escuela;
    FuentePoder fuentePoder;
    vector<string> hechizosConocidos;
    
public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Mago
     * @param n Nombre del mago
     * @param nivel Nivel del personaje
     * @param hp Puntos de vida maximos
     * @param r Raza del personaje
     * @param fue Puntos de fuerza
     * @param des Puntos de destreza
     * @param con Puntos de constitucion
     * @param inte Puntos de inteligencia
     * @param manaMax Mana maximo
     * @param esc Escuela de magia
     * @param fp Fuente de poder
     */
    Mago(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
         int manaMax, EscuelaMagia esc, FuentePoder fp);
    
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
     * @brief Verifica si el personaje esta en modo combate PPT
     * @return true si esta en modo combate PPT, false en caso contrario
     */
    bool getEsCombatePPT() const;
    
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
    // GESTION DE MAGIA
    // ==========================================
    
    /**
     * @brief Obtiene el mana actual del mago
     * @return Cantidad de mana actual
     */
    int getMana() const;
    
    /**
     * @brief Consume mana para lanzar hechizos
     * @param cantidad Cantidad de mana a gastar
     * @return true si se pudo gastar el mana, false si no hay suficiente
     */
    virtual bool gastarMana(int cantidad);
    
    /**
     * @brief Recupera mana
     * @param cantidad Cantidad de mana a recuperar
     */
    void recuperarMana(int cantidad);
    
    /**
     * @brief Obtiene la escuela de magia del mago
     * @return Escuela de magia del mago
     */
    EscuelaMagia getEscuelaMagia() const;
    
    /**
     * @brief Obtiene la fuente de poder del mago
     * @return Fuente de poder del mago
     */
    FuentePoder getFuentePoder() const;
    
    // ==========================================
    // HABILIDADES DE MAGO
    // ==========================================
    
    /**
     * @brief Lanza un hechizo conocido
     * @param nombreHechizo Nombre del hechizo a lanzar
     * @return Valor numerico que representa el efecto del hechizo
     */
    virtual int lanzarHechizo(const string& nombreHechizo);
    
    /**
     * @brief Medita para recuperar mana
     */
    virtual void meditar();
    
    /**
     * @brief Aprende un nuevo hechizo
     * @param nombreHechizo Nombre del hechizo a aprender
     * @return true si se aprendio el hechizo, false si ya se conocia o hubo un error
     */
    virtual bool aprenderHechizo(const string& nombreHechizo);
    
    /**
     * @brief Muestra la lista de hechizos conocidos
     */
    virtual void listarHechizos() const;
    
    /**
     * @brief Verifica si el mago conoce un hechizo
     * @param nombreHechizo Nombre del hechizo a verificar
     * @return true si conoce el hechizo, false en caso contrario
     */
    virtual bool conoceHechizo(const string& nombreHechizo) const;
    
    /**
     * @brief Invoca un elemental para atacar
     * @return Valor numerico que representa el daño causado por el elemental
     */
    virtual int invocarElemental();
    
    /**
     * @brief Lanza un proyectil magico
     * @return Valor numerico que representa el daño causado por el proyectil
     */
    virtual int proyectilMagico();
};