#include "Paladin.hpp"

/**
 * @brief Implementación del constructor de Paladín
 * 
 * Inicializa un paladín con sus atributos básicos heredados de Guerrero
 * y sus atributos específicos como fe, deidad, poder sagrado,
 * aura divina y nivel de devoción.
 */
Paladin::Paladin(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
                 int estMax, EstiloCombate est, TipoArmadura ta, int defBase, int resFis,
                 int fePts, string deity, int poderSag, bool aura, int devocion)
    : Guerrero(n, nivel, hp, r, fue, des, con, inte, estMax, est, ta, defBase, resFis),
      fe(fePts), deidad(deity), poderSagrado(poderSag), auraDivina(aura), nivelDevocion(devocion) {
}

/**
 * @brief Implementación del método invocarLuzSagrada
 * 
 * El paladín invoca la luz de su deidad para causar daño a criaturas
 * malvadas. Requiere puntos de fe suficientes.
 * 
 * @return Valor numérico que representa el daño causado
 */
int Paladin::invocarLuzSagrada() {
    cout << nombre << " invoca la luz sagrada de " << deidad << "..." << endl;
    
    if (fe < 10) {
        cout << nombre << " no tiene suficiente fe para completar la invocación." << endl;
        return 0;
    }
    
    fe -= 10;
    cout << "Una luz brillante emana de " << nombre << ", iluminando el área." << endl;
    
    int poderLuz = poderSagrado + nivelDevocion / 2;
    cout << "La luz sagrada causa " << poderLuz << " puntos de daño a las criaturas malvadas cercanas." << endl;
    
    return poderLuz;
}

/**
 * @brief Implementación del método castigarMalvados
 * 
 * El paladín canaliza su fe para castigar a seres malvados con poder divino.
 * Requiere puntos de estamina y fe suficientes.
 * 
 * @return Valor numérico que representa el daño causado
 */
int Paladin::castigarMalvados() {
    cout << nombre << " canaliza su fe para castigar a los malvados..." << endl;
    
    int costoEstamina = 15;
    int costoFe = 5;
    
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    if (fe < costoFe) {
        cout << nombre << " no tiene suficiente fe (necesita " << costoFe << ")." << endl;
        return 0;
    }
    
    fe -= costoFe;
    
    int danioCastigo = fuerza + poderSagrado + nivelDevocion / 3;
    cout << "¡El castigo divino causa " << danioCastigo << " puntos de daño!" << endl;
    cout << "Fe restante: " << fe << endl;
    
    return danioCastigo;
}

/**
 * @brief Implementación del método imponerManos
 * 
 * El paladín usa su poder divino para curar a un objetivo mediante
 * la imposición de manos. Requiere puntos de fe suficientes.
 * 
 * @param objetivo Nombre del objetivo a curar
 * @return Cantidad de puntos de vida curados
 */
int Paladin::imponerManos(string objetivo) {
    cout << nombre << " impone sus manos sobre " << objetivo << " para sanar..." << endl;
    
    int costoFe = 8;
    
    if (fe < costoFe) {
        cout << nombre << " no tiene suficiente fe (necesita " << costoFe << ")." << endl;
        return 0;
    }
    
    fe -= costoFe;
    
    int curacion = poderSagrado + nivelDevocion / 2 + constitucion / 4;
    cout << nombre << " cura " << curacion << " puntos de vida a " << objetivo << "." << endl;
    cout << "Fe restante: " << fe << endl;
    
    return curacion;
}

/**
 * @brief Implementación del método rezar
 * 
 * El paladín reza a su deidad para recuperar puntos de fe
 * y algo de estamina.
 */
void Paladin::rezar() {
    cout << nombre << " se arrodilla y reza a " << deidad << "..." << endl;
    
    int recuperacionFe = 5 + nivelDevocion / 5;
    int feAnterior = fe;
    
    // Recuperar fe
    fe += recuperacionFe;
    
    // También recupera un poco de estamina al rezar
    recuperarEstamina(5);
    
    cout << nombre << " recupera " << (fe - feAnterior) << " puntos de fe. Fe actual: " << fe << endl;
}

/**
 * @brief Implementación del método activarAuraDivina
 * 
 * El paladín activa un aura de protección divina que reduce
 * el daño recibido. Requiere puntos de fe suficientes.
 * 
 * @return true si se activó con éxito, false si ya estaba activa o no hay fe suficiente
 */
bool Paladin::activarAuraDivina() {
    if (auraDivina) {
        cout << "El aura divina ya está activa." << endl;
        return false;
    }
    
    int costoFe = 15;
    
    if (fe < costoFe) {
        cout << nombre << " no tiene suficiente fe (necesita " << costoFe << ")." << endl;
        return false;
    }
    
    fe -= costoFe;
    auraDivina = true;
    
    cout << "¡" << nombre << " activa su aura divina! Un resplandor sagrado lo rodea." << endl;
    cout << "Fe restante: " << fe << endl;
    
    return true;
}

/**
 * @brief Implementación del método mostrarInfo
 * 
 * Muestra información detallada sobre el paladín y sus características
 * específicas, además de la información base de guerrero.
 */
void Paladin::mostrarInfo() const {
    Guerrero::mostrarInfo(); // Llamamos al método de la clase base
    
    cout << "  Tipo: Paladín" << endl;
    cout << "  Fe: " << fe << endl;
    cout << "  Deidad: " << deidad << endl;
    cout << "  Poder Sagrado: " << poderSagrado << endl;
    cout << "  Aura Divina: " << (auraDivina ? "Activa" : "Inactiva") << endl;
    cout << "  Nivel de Devoción: " << nivelDevocion << endl;
}

/**
 * @brief Implementación especializada del método recibirDanio
 * 
 * Modifica el comportamiento base para reducir el daño recibido
 * cuando el paladín tiene su aura divina activa.
 * 
 * @param cantidad Cantidad de daño a recibir
 * @param esCombatePPT Indica si es un combate PPT
 * @return true si sigue vivo, false si ha muerto
 */
bool Paladin::recibirDanio(int cantidad, bool esCombatePPT) {
    if (!esCombatePPT) {
        if (auraDivina && cantidad > 0) {
            // El aura divina reduce el daño recibido
            int reduccion = min(cantidad / 3, poderSagrado / 2);
            if (reduccion > 0) {
                cout << "El aura divina de " << nombre << " reduce el daño en " << reduccion << " puntos." << endl;
                cantidad -= reduccion;
            }
        }
        return Guerrero::recibirDanio(cantidad, esCombatePPT);
    }
    return Guerrero::recibirDanio(cantidad, esCombatePPT); // Llamamos al método base con el daño ajustado
}

/**
 * @brief Implementación especializada del método curar
 * 
 * Modifica el comportamiento base para potenciar la curación recibida
 * gracias al nivel de devoción del paladín.
 * 
 * @param cantidad Cantidad de puntos de vida a curar
 */
void Paladin::curar(int cantidad) {
    // Los paladines reciben un bonus a la curación recibida
    if (cantidad > 0) {
        int bonus = cantidad * nivelDevocion / 20; // 5% extra por cada nivel de devoción
        
        if (bonus > 0) {
            cout << "La fe de " << nombre << " potencia la curación en " << bonus << " puntos adicionales." << endl;
            cantidad += bonus;
        }
    }
    
    Guerrero::curar(cantidad); // Llamamos al método base con la curación ajustada
}
