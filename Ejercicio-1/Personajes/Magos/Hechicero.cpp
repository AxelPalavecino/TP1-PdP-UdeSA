#include "Hechicero.hpp"

/**
 * @brief Implementación del constructor de Hechicero
 * 
 * Inicializa un hechicero con sus atributos básicos heredados de Mago
 * y sus atributos específicos como poder arcano, bastión arcano,
 * manipulación del tiempo y familiar mágico.
 */
Hechicero::Hechicero(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
                     int manaMax, EscuelaMagia esc, FuentePoder fp, 
                     int poderArc, bool bastion, int manipTiempo, string familiar)
    : Mago(n, nivel, hp, r, fue, des, con, inte, manaMax, esc, fp),
      poderArcano(poderArc), bastionArcano(bastion), manipulacionTiempo(manipTiempo), 
      familiarNombre(familiar), familiarActivo(false) {
}

/**
 * @brief Implementación del método getPoder
 * 
 * Retorna el nivel actual de poder arcano del hechicero.
 * 
 * @return Valor numérico que representa el poder arcano
 */
int Hechicero::getPoder() const { return poderArcano; }

/**
 * @brief Implementación del método aumentarPoder
 * 
 * Incrementa el poder arcano del hechicero en una cantidad especificada.
 * 
 * @param cantidad Cantidad de poder arcano a añadir
 */
void Hechicero::aumentarPoder(int cantidad) {
    if (cantidad <= 0) return;
    
    poderArcano += cantidad;
    cout << nombre << " aumenta su poder arcano en " << cantidad << ". Poder arcano: " << poderArcano << endl;
}

/**
 * @brief Implementación del método activarBastionArcano
 * 
 * Activa una barrera mágica que protege al hechicero contra
 * energías arcanas. Requiere gastar maná.
 * 
 * @return true si se activó el bastión, false si ya estaba activo o faltó maná
 */
bool Hechicero::activarBastionArcano() {
    if (bastionArcano) {
        cout << "El bastión arcano ya está activo." << endl;
        return false;
    }
    
    int costoMana = 15;
    if (!gastarMana(costoMana)) {
        return false;
    }
    
    bastionArcano = true;
    cout << nombre << " activa su bastión arcano, protegiéndose de energías mágicas." << endl;
    return true;
}

/**
 * @brief Implementación del método invocarFamiliar
 * 
 * Invoca al familiar mágico del hechicero para que lo ayude
 * en su próxima acción mágica. Requiere gastar maná.
 */
void Hechicero::invocarFamiliar() {
    if (familiarActivo) {
        cout << familiarNombre << " ya está activo y ayudando a " << nombre << "." << endl;
        return;
    }
    
    int costoMana = 10;
    if (!gastarMana(costoMana)) {
        return;
    }
    
    familiarActivo = true;
    cout << nombre << " invoca a su familiar " << familiarNombre << "." << endl;
    cout << familiarNombre << " ayudará a " << nombre << " en su próxima acción mágica." << endl;
}

/**
 * @brief Implementación del método alterarTiempo
 * 
 * Manipula el flujo temporal para causar daño a los enemigos.
 * Requiere habilidades de manipulación temporal y maná suficiente.
 * 
 * @return Valor numérico que representa el daño causado
 */
int Hechicero::alterarTiempo() {
    if (manipulacionTiempo <= 0) {
        cout << nombre << " no tiene habilidades de manipulación temporal." << endl;
        return 0;
    }
    
    int costoMana = 25;
    if (!gastarMana(costoMana)) {
        return 0;
    }
    
    cout << nombre << " altera el flujo temporal..." << endl;
    
    int efectoMagico = manipulacionTiempo + inteligencia + nivelPersonaje;
    cout << "¡El tiempo se distorsiona alrededor, causando " << efectoMagico << " de daño!" << endl;
    
    return efectoMagico;
}

/**
 * @brief Implementación del método mostrarInfo
 * 
 * Muestra información detallada sobre el hechicero y sus características
 * específicas, además de la información base de mago.
 */
void Hechicero::mostrarInfo() const {
    Mago::mostrarInfo(); // Llamamos al método de la clase base
    
    cout << "  Tipo: Hechicero" << endl;
    cout << "  Poder Arcano: " << poderArcano << endl;
    cout << "  Bastión Arcano: " << (bastionArcano ? "Activo" : "Inactivo") << endl;
    cout << "  Manipulación Temporal: " << manipulacionTiempo << endl;
    cout << "  Familiar: " << familiarNombre << " (" << (familiarActivo ? "Activo" : "Inactivo") << ")" << endl;
}

/**
 * @brief Implementación especializada del método lanzarHechizo
 * 
 * Potencia los hechizos básicos con poder arcano. Si el familiar
 * está activo, otorga un bonus adicional pero se desactiva después
 * del uso.
 * 
 * @param nombreHechizo Nombre del hechizo a lanzar
 * @return Valor numérico que representa el efecto del hechizo
 */
int Hechicero::lanzarHechizo(const string& nombreHechizo) {
    int danioBase = Mago::lanzarHechizo(nombreHechizo); // Llamamos al método base
    
    if (danioBase <= 0) return 0;
    
    // Bonus por poder arcano
    int bonus = poderArcano / 4;
    
    // Bonus adicional si el familiar está activo
    if (familiarActivo) {
        cout << familiarNombre << " potencia el hechizo de " << nombre << "!" << endl;
        bonus += poderArcano / 3;
        familiarActivo = false; // El familiar se "gasta" al potenciar un hechizo
    }
    
    if (bonus > 0) {
        cout << "Bonus de poder arcano: +" << bonus << " al daño!" << endl;
        danioBase += bonus;
    }
    
    return danioBase;
}
