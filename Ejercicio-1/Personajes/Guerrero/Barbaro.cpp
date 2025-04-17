#include "Barbaro.hpp"

/**
 * @brief Implementacion del constructor de Barbaro
 * 
 * Inicializa un barbaro con sus atributos basicos heredados de Guerrero
 * y sus atributos especificos como frenesi, resistencia al dolor,
 * furia de combate, grito de batalla y superacion de limites.
 */
Barbaro::Barbaro(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
                 int estMax, EstiloCombate est, TipoArmadura ta, int defBase, int resFis,
                 int resDolor, int furia, string grito, int supLimites)
    : Guerrero(n, nivel, hp, r, fue, des, con, inte, estMax, est, ta, defBase, resFis),
      frenesi(false), resistenciaDolor(resDolor), furiaCombate(furia), 
      gritoBatalla(grito), superacionLimites(supLimites) {
}

/**
 * @brief Implementacion del metodo entrarEnFrenesi
 * 
 * Permite al barbaro entrar en un estado de frenesi, aumentando su
 * furia de combate. Requiere gastar estamina.
 * 
 * @return true si pudo entrar en frenesi, false si ya estaba o no tenia estamina
 */
bool Barbaro::entrarEnFrenesi() {
    if (frenesi) {
        cout << nombre << " ya está en frenesí." << endl;
        return false;
    }
    
    int costoEstamina = 20;
    if (!gastarEstamina(costoEstamina)) {
        return false;
    }
    
    frenesi = true;
    furiaCombate += 5;
    
    cout << nombre << " entra en un estado de frenesí!" << endl;
    cout << "¡Su fuerza y resistencia aumentan, pero pierde control!" << endl;
    
    return true;
}

/**
 * @brief Implementacion del metodo aumentarFuria
 * 
 * Incrementa el contador de furia del barbaro, lo que potencia
 * sus ataques y habilidades especiales.
 * 
 * @param cantidad Cantidad de furia a aumentar
 */
void Barbaro::aumentarFuria(int cantidad) {
    if (cantidad <= 0) return;
    
    furiaCombate += cantidad;
    cout << nombre << " aumenta su furia en " << cantidad << ". Furia total: " << furiaCombate << endl;
}

/**
 * @brief Implementacion del metodo gritarEnBatalla
 * 
 * El barbaro lanza su grito de batalla, atemorizando a los enemigos.
 * El efecto depende de su furia de combate y fuerza.
 * Requiere gastar estamina.
 * 
 * @return Valor numerico que representa el efecto del grito
 */
int Barbaro::gritarEnBatalla() {
    cout << nombre << " lanza un potente grito de batalla: \"" << gritoBatalla << "\"!" << endl;
    
    int costoEstamina = 10;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    int efectoGrito = furiaCombate / 2 + fuerza / 3;
    cout << "¡El grito atemoriza a los enemigos, reduciendo su moral en " << efectoGrito << " puntos!" << endl;
    
    return efectoGrito;
}

/**
 * @brief Implementacion del metodo resistirDolor
 * 
 * Permite al barbaro ignorar parte de sus heridas mediante
 * pura fuerza de voluntad, recuperando puntos de vida.
 * Requiere gastar estamina.
 */
void Barbaro::resistirDolor() {
    cout << nombre << " se concentra para ignorar el dolor..." << endl;
    
    int costoEstamina = 5;
    if (!gastarEstamina(costoEstamina)) {
        return;
    }
    
    int hpRecuperados = resistenciaDolor / 2 + constitucion / 3;
    curar(hpRecuperados);
    
    cout << nombre << " ignora parte de sus heridas y continúa luchando con renovado vigor." << endl;
}

/**
 * @brief Implementacion del metodo golpeSalvaje
 * 
 * Realiza un ataque poderoso pero poco preciso, causando
 * mayor daño si el barbaro esta en frenesi.
 * Requiere gastar estamina.
 * 
 * @return Valor numerico que representa el daño causado
 */
int Barbaro::golpeSalvaje() {
    cout << nombre << " prepara un golpe salvaje y descontrolado..." << endl;
    
    int costoEstamina = 15;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    cout << "¡" << nombre << " lanza un ataque devastador!" << endl;
    
    int danioGolpe = fuerza + furiaCombate / 2;
    if (frenesi) {
        danioGolpe += furiaCombate;
    }
    
    cout << "¡El golpe salvaje causa " << danioGolpe << " puntos de daño!" << endl;
    return danioGolpe;
}

/**
 * @brief Implementacion del metodo mostrarInfo
 * 
 * Muestra informacion detallada sobre el barbaro y sus caracteristicas
 * especificas, ademas de la informacion base de guerrero.
 */
void Barbaro::mostrarInfo() const {
    Guerrero::mostrarInfo(); // Llamamos al método de la clase base
    
    cout << "  Tipo: Bárbaro" << endl;
    cout << "  Frenesí: " << (frenesi ? "Activo" : "Inactivo") << endl;
    cout << "  Resistencia al Dolor: " << resistenciaDolor << endl;
    cout << "  Furia de Combate: " << furiaCombate << endl;
    cout << "  Grito de Batalla: \"" << gritoBatalla << "\"" << endl;
    cout << "  Superación de Límites: " << superacionLimites << endl;
}

/**
 * @brief Implementacion especializada del metodo recibirDanio
 * 
 * Modifica el comportamiento base para aplicar la resistencia al dolor
 * cuando el barbaro esta en frenesi, reduciendo el daño recibido.
 * Ademas, aumenta su furia al recibir daño.
 * 
 * @param cantidad Cantidad de daño a recibir
 * @param esCombatePPT Indica si es un combate PPT
 * @return true si sigue vivo, false si ha muerto
 */
bool Barbaro::recibirDanio(int cantidad, bool esCombatePPT) {
    if (!esCombatePPT) {
        if (frenesi && cantidad > 0) {
            int reduccion = min(cantidad / 2, resistenciaDolor);
            if (reduccion > 0) {
                cout << nombre << " resiste " << reduccion << " puntos de daño gracias a su frenesí." << endl;
                cantidad -= reduccion;
            }
            
            // En frenesí, cada vez que recibe daño aumenta su furia
            aumentarFuria(max(1, cantidad / 5));
        }
        return Guerrero::recibirDanio(cantidad, esCombatePPT);
    }
    return Guerrero::recibirDanio(cantidad, esCombatePPT); // Llamar al método base con el daño ajustado
}
