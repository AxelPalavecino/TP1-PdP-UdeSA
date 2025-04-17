#pragma once

#include "../Mago.hpp"
#include <vector>

/**
 * @brief Clase que representa un personaje de tipo Nigromante
 * 
 * Implementa una especialización de Mago enfocada en necromancia,
 * control de no-muertos y manipulación de energías de muerte.
 */
class Nigromante : public Mago {
private:
    int poderNecromantico;
    vector<string> servidoresNoMuertos;
    int energiaMuerte;
    bool filacteria;
    int resistenciaMuerte;

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase Nigromante
     * @param n Nombre del nigromante
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
     * @param poderNec Nivel de poder necromántico
     * @param energiaMuerte Cantidad inicial de energía de muerte
     * @param filact Indica si posee una filacteria
     * @param resistenciaMuerte Resistencia a energías de muerte
     */
    Nigromante(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
               int manaMax, EscuelaMagia esc, FuentePoder fp,
               int poderNec, int energiaMuerte, bool filact, int resistenciaMuerte);
    
    // ==========================================
    // HABILIDADES DE NIGROMANTE
    // ==========================================
    
    /**
     * @brief Crea y anima un servidor no-muerto
     * @param nombreNoMuerto Nombre del servidor no-muerto a crear
     * @return Valor numérico que representa el poder del no-muerto creado
     */
    int levantarNoMuerto(string nombreNoMuerto);
    
    /**
     * @brief Refuerza el control sobre un no-muerto existente
     * @param nombreNoMuerto Nombre del no-muerto a controlar
     * @return true si el control fue exitoso, false si no tenía el no-muerto o faltó maná
     */
    bool controlarNoMuerto(string nombreNoMuerto);
    
    /**
     * @brief Realiza un ataque de energía necrótica
     * @return Valor numérico que representa el daño causado
     */
    int tocoDeLaMuerte();
    
    /**
     * @brief Absorbe energía vital de un servidor no-muerto
     * @param nombreNoMuerto Nombre del no-muerto del que drenar energía
     * @return Cantidad de puntos de vida absorbidos
     */
    int drenarVidaNoMuerto(string nombreNoMuerto);
    
    /**
     * @brief Crea una filacteria para almacenar parte de su alma
     */
    void crearFilacteria();
    
    // ==========================================
    // SOBRESCRITURAS DE MÉTODOS BASE
    // ==========================================
    
    /**
     * @brief Muestra información detallada sobre el nigromante
     */
    void mostrarInfo() const override;
    
    /**
     * @brief Implementación especializada para recibir daño
     * 
     * La filacteria puede salvar al nigromante de la muerte una vez.
     * También tiene resistencia a daños necróticos.
     * 
     * @param cantidad Cantidad de daño a recibir
     * @param esCombatePPT Indica si es un combate PPT
     * @return true si sigue vivo, false si ha muerto
     */
    bool recibirDanio(int cantidad, bool esCombatePPT) override;
    
    /**
     * @brief Implementación especializada de meditación
     * 
     * Además de recuperar maná, también recupera energía de muerte.
     */
    void meditar() override;
};
