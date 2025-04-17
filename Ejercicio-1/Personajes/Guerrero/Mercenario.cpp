#include "Mercenario.hpp"
#include <algorithm>

/**
 * @brief Implementación del constructor de Mercenario
 * 
 * Inicializa un mercenario con sus atributos básicos heredados de Guerrero
 * y sus atributos específicos como oro, reputación, bonus de sigilo
 * y último empleador.
 */
Mercenario::Mercenario(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
                       int estMax, EstiloCombate est, TipoArmadura ta, int defBase, int resFis,
                       int monedas, int rep, int sigilo, string empleador)
    : Guerrero(n, nivel, hp, r, fue, des, con, inte, estMax, est, ta, defBase, resFis),
      oro(monedas), reputacion(rep), bonusSigilo(sigilo), ultimoEmpleador(empleador) {
}

/**
 * @brief Implementación del método aceptarContrato
 * 
 * Registra un nuevo contrato para el mercenario si el objetivo es válido
 * y no lo tenía previamente en su lista.
 * 
 * @param objetivo Nombre del objetivo del contrato
 * @param recompensa Cantidad de oro ofrecida como recompensa
 * @return true si se acepta el contrato, false si ya lo tenía o es inválido
 */
bool Mercenario::aceptarContrato(string objetivo, int recompensa) {
    if (objetivo.empty()) {
        cout << "No se puede aceptar un contrato sin objetivo." << endl;
        return false;
    }
    
    // Verificar si ya tiene este contrato
    if (find(contratos.begin(), contratos.end(), objetivo) != contratos.end()) {
        cout << nombre << " ya tiene un contrato para " << objetivo << "." << endl;
        return false;
    }
    
    contratos.push_back(objetivo);
    cout << nombre << " ha aceptado un contrato para " << objetivo << " por " << recompensa << " monedas de oro." << endl;
    
    return true;
}

/**
 * @brief Implementación del método completarContrato
 * 
 * Marca un contrato como completado, eliminándolo de la lista activa
 * y aumentando la reputación del mercenario.
 * 
 * @param objetivo Nombre del objetivo del contrato completado
 * @return true si se completa el contrato, false si no lo tenía
 */
bool Mercenario::completarContrato(string objetivo) {
    auto it = find(contratos.begin(), contratos.end(), objetivo);
    if (it == contratos.end()) {
        cout << nombre << " no tiene un contrato para " << objetivo << "." << endl;
        return false;
    }
    
    contratos.erase(it);
    cout << nombre << " ha completado el contrato para " << objetivo << "." << endl;
    
    // Aumentar reputación al completar un contrato
    reputacion += 5;
    cout << "Reputación aumentada a " << reputacion << "." << endl;
    
    return true;
}

/**
 * @brief Implementación del método cobrarRecompensa
 * 
 * Añade una cantidad de oro al mercenario como recompensa
 * por un contrato u otro servicio.
 * 
 * @param cantidad Cantidad de oro a cobrar
 */
void Mercenario::cobrarRecompensa(int cantidad) {
    if (cantidad <= 0) return;
    
    oro += cantidad;
    cout << nombre << " cobra " << cantidad << " monedas de oro. Oro total: " << oro << endl;
}

/**
 * @brief Implementación del método atacarPorSorpresa
 * 
 * Realiza un ataque sigiloso que causa daño basado en la destreza,
 * el bonus de sigilo y el nivel del personaje.
 * Requiere gastar estamina.
 * 
 * @return Valor numérico que representa el daño causado
 */
int Mercenario::atacarPorSorpresa() {
    cout << nombre << " se prepara para atacar desde las sombras..." << endl;
    
    int costoEstamina = 12;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    // Daño basado en destreza, sigilo y nivel
    int danio = destreza + bonusSigilo + nivelPersonaje / 2;
    cout << "¡" << nombre << " ataca por sorpresa, causando " << danio << " puntos de daño!" << endl;
    
    return danio;
}

/**
 * @brief Implementación del método negociarMejorPrecio
 * 
 * Utiliza las habilidades de negociación del mercenario para
 * conseguir un mejor precio en una transacción.
 * 
 * @param precioBase Precio base antes de negociar
 * @return Valor numérico que representa el precio mejorado
 */
int Mercenario::negociarMejorPrecio(int precioBase) {
    if (precioBase <= 0) return 0;
    
    int bonusNegociacion = inteligencia / 2 + reputacion / 5;
    int precioFinal = precioBase + bonusNegociacion;
    
    cout << nombre << " negocia un mejor precio. ";
    cout << "Precio base: " << precioBase << " + bonus de negociación: " << bonusNegociacion;
    cout << " = Precio final: " << precioFinal << endl;
    
    return precioFinal;
}

/**
 * @brief Implementación del método mostrarInfo
 * 
 * Muestra información detallada sobre el mercenario y sus características
 * específicas, además de la información base de guerrero.
 */
void Mercenario::mostrarInfo() const {
    Guerrero::mostrarInfo(); // Llamamos al método de la clase base
    
    cout << "  Tipo: Mercenario" << endl;
    cout << "  Oro: " << oro << endl;
    cout << "  Reputación: " << reputacion << endl;
    cout << "  Bonus Sigilo: " << bonusSigilo << endl;
    cout << "  Último Empleador: " << ultimoEmpleador << endl;
    
    cout << "  Contratos activos: ";
    if (contratos.empty()) {
        cout << "Ninguno" << endl;
    } else {
        cout << endl;
        for (const auto& contrato : contratos) {
            cout << "    - " << contrato << endl;
        }
    }
}

/**
 * @brief Implementación especializada del método atacar
 * 
 * Modifica el comportamiento base para añadir bonificaciones
 * específicas cuando el mercenario utiliza Golpe Rápido.
 * 
 * @param movimiento Tipo de movimiento de ataque a realizar
 * @return Valor numérico que representa el daño causado
 */
int Mercenario::atacar(MovimientoCombate movimiento) {
    int danioBase = Guerrero::atacar(movimiento);
    
    // Los mercenarios son especialmente efectivos con el Golpe Rápido
    if (movimiento == MovimientoCombate::GolpeRapido) {
        int bonus = destreza / 4 + bonusSigilo / 2;
        if (bonus > 0) {
            cout << nombre << " aprovecha su velocidad y sigilo para un golpe más eficaz (+";
            cout << bonus << " al daño)." << endl;
            danioBase += bonus;
        }
    }
    
    return danioBase;
}
