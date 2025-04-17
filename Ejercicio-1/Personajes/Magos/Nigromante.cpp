#include "Nigromante.hpp"
#include <algorithm>

/**
 * @brief Implementación del constructor de Nigromante
 * 
 * Inicializa un nigromante con sus atributos básicos heredados de Mago
 * y sus atributos específicos como poder necromántico, energía de muerte,
 * filacteria y resistencia a la muerte.
 */
Nigromante::Nigromante(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
                       int manaMax, EscuelaMagia esc, FuentePoder fp,
                       int poderNec, int energia, bool filact, int resistencia)
    : Mago(n, nivel, hp, r, fue, des, con, inte, manaMax, esc, fp),
      poderNecromantico(poderNec), energiaMuerte(energia), filacteria(filact), resistenciaMuerte(resistencia) {
}

/**
 * @brief Implementación del método levantarNoMuerto
 * 
 * Ejecuta un ritual para crear un servidor no-muerto bajo el control
 * del nigromante. Requiere suficiente maná y energía de muerte.
 * 
 * @param nombreNoMuerto Nombre del servidor no-muerto a crear
 * @return Valor numérico que representa el poder del no-muerto creado
 */
int Nigromante::levantarNoMuerto(string nombreNoMuerto) {
    cout << nombre << " comienza el ritual para levantar un no-muerto..." << endl;
    
    int costoMana = 20;
    if (!gastarMana(costoMana)) {
        return 0;
    }
    
    if (energiaMuerte < 10) {
        cout << "Energía de muerte insuficiente (necesitas al menos 10)." << endl;
        return 0;
    }
    
    energiaMuerte -= 10;
    
    // Añadir a la lista de servidores
    servidoresNoMuertos.push_back(nombreNoMuerto);
    
    cout << "¡" << nombre << " ha levantado a " << nombreNoMuerto << " de entre los muertos!" << endl;
    cout << "Energía de muerte restante: " << energiaMuerte << endl;
    
    int poderServidor = poderNecromantico + nivelPersonaje;
    return poderServidor; // Representa el poder del no-muerto
}

/**
 * @brief Implementación del método controlarNoMuerto
 * 
 * Refuerza el control sobre un servidor no-muerto ya existente.
 * Verifica que el no-muerto esté en la lista de control y gasta maná.
 * 
 * @param nombreNoMuerto Nombre del no-muerto a controlar
 * @return true si el control fue exitoso, false si no tenía el no-muerto o faltó maná
 */
bool Nigromante::controlarNoMuerto(string nombreNoMuerto) {
    auto it = find(servidoresNoMuertos.begin(), servidoresNoMuertos.end(), nombreNoMuerto);
    if (it == servidoresNoMuertos.end()) {
        cout << nombre << " no controla a ningún no-muerto llamado " << nombreNoMuerto << "." << endl;
        return false;
    }
    
    int costoMana = 5;
    if (!gastarMana(costoMana)) {
        return false;
    }
    
    cout << nombre << " refuerza su control sobre " << nombreNoMuerto << "." << endl;
    return true;
}

/**
 * @brief Implementación del método tocoDeLaMuerte
 * 
 * Canaliza energía necrótica para realizar un ataque de contacto
 * que inflige daño basado en poder necromántico e inteligencia.
 * También genera energía de muerte como subproducto.
 * 
 * @return Valor numérico que representa el daño causado
 */
int Nigromante::tocoDeLaMuerte() {
    cout << nombre << " canaliza energía necromántica en sus manos..." << endl;
    
    int costoMana = 15;
    if (!gastarMana(costoMana)) {
        return 0;
    }
    
    int poderToco = poderNecromantico + inteligencia / 2;
    cout << "¡" << nombre << " inflige " << poderToco << " puntos de daño necrótico con su toco!" << endl;
    
    // Ganar energía de muerte
    energiaMuerte += 5;
    cout << "Energía de muerte aumentada a " << energiaMuerte << "." << endl;
    
    return poderToco;
}

/**
 * @brief Implementación del método drenarVidaNoMuerto
 * 
 * Absorbe energía vital residual de un servidor no-muerto para
 * curar al nigromante. El no-muerto puede ser destruido en el proceso.
 * 
 * @param nombreNoMuerto Nombre del no-muerto del que drenar energía
 * @return Cantidad de puntos de vida absorbidos
 */
int Nigromante::drenarVidaNoMuerto(string nombreNoMuerto) {
    auto it = find(servidoresNoMuertos.begin(), servidoresNoMuertos.end(), nombreNoMuerto);
    if (it == servidoresNoMuertos.end()) {
        cout << nombre << " no controla a ningún no-muerto llamado " << nombreNoMuerto << "." << endl;
        return 0;
    }
    
    cout << nombre << " drena la energía vital residual de " << nombreNoMuerto << "..." << endl;
    
    int vidaDrenada = poderNecromantico / 2 + nivelPersonaje;
    cout << nombre << " absorbe " << vidaDrenada << " puntos de vida." << endl;
    
    // Curar al nigromante
    curar(vidaDrenada);
    
    // El no-muerto se debilita o destruye
    if (rand() % 3 == 0) { // 33% de probabilidad de destrucción
        cout << nombreNoMuerto << " se desintegra tras ser drenado." << endl;
        servidoresNoMuertos.erase(it);
    } else {
        cout << nombreNoMuerto << " se debilita pero sigue en pie." << endl;
    }
    
    return vidaDrenada;
}

/**
 * @brief Implementación del método crearFilacteria
 * 
 * Realiza un ritual para crear una filacteria que almacena parte del alma
 * del nigromante, permitiéndole evitar la muerte una vez. El ritual tiene
 * un costo permanente de vida máxima.
 */
void Nigromante::crearFilacteria() {
    if (filacteria) {
        cout << nombre << " ya posee una filacteria." << endl;
        return;
    }
    
    int costoMana = 50;
    if (!gastarMana(costoMana)) {
        return;
    }
    
    if (energiaMuerte < 30) {
        cout << "Energía de muerte insuficiente (necesitas al menos 30)." << endl;
        return;
    }
    
    energiaMuerte -= 30;
    
    cout << nombre << " realiza un oscuro ritual para crear una filacteria..." << endl;
    cout << "Una parte del alma de " << nombre << " es transferida a un receptáculo." << endl;
    
    filacteria = true;
    // Reducir HP máximo como costo permanente
    hpMax -= hpMax / 10;
    if (hpActual > hpMax) hpActual = hpMax;
    
    cout << "¡Filacteria creada! " << nombre << " ha dado un paso hacia la inmortalidad." << endl;
    cout << "HP reducido permanentemente a " << hpMax << " debido al ritual." << endl;
}

/**
 * @brief Implementación del método mostrarInfo
 * 
 * Muestra información detallada sobre el nigromante y sus características
 * específicas, además de la información base de mago.
 */
void Nigromante::mostrarInfo() const {
    Mago::mostrarInfo(); // Llamamos al método de la clase base
    
    cout << "  Tipo: Nigromante" << endl;
    cout << "  Poder Necromántico: " << poderNecromantico << endl;
    cout << "  Energía de Muerte: " << energiaMuerte << endl;
    cout << "  Filacteria: " << (filacteria ? "Sí" : "No") << endl;
    cout << "  Resistencia a Muerte: " << resistenciaMuerte << endl;
    
    cout << "  Servidores No-Muertos: ";
    if (servidoresNoMuertos.empty()) {
        cout << "Ninguno" << endl;
    } else {
        cout << endl;
        for (const auto& noMuerto : servidoresNoMuertos) {
            cout << "    - " << noMuerto << endl;
        }
    }
}

/**
 * @brief Implementación especializada del método recibirDanio
 * 
 * Modifica el comportamiento base para aplicar resistencia a daños
 * necróticos. Además, si posee una filacteria y el daño sería mortal,
 * la filacteria se consume para salvarlo.
 * 
 * @param cantidad Cantidad de daño a recibir
 * @param esCombatePPT Indica si es un combate PPT
 * @return true si sigue vivo, false si ha muerto
 */
bool Nigromante::recibirDanio(int cantidad, bool esCombatePPT) {
    if (!esCombatePPT) {
        if (cantidad > 0) {
            // Resistencia a daño necrótico
            int reduccion = min(cantidad / 4, resistenciaMuerte);
            if (reduccion > 0) {
                cout << nombre << " resiste " << reduccion << " puntos de daño gracias a su conexión con la muerte." << endl;
                cantidad -= reduccion;
            }
            
            // Si tiene filacteria y el daño lo mataría, salvarse una vez
            if (filacteria && hpActual <= cantidad) {
                cout << "¡La filacteria de " << nombre << " lo salva de la muerte!" << endl;
                hpActual = hpMax / 3; // Restaurar una parte de la vida
                filacteria = false; // La filacteria se consume
                cout << "La filacteria se ha consumido, pero " << nombre << " sobrevive con " << hpActual << " puntos de vida." << endl;
                return true;
            }
        }
    }
    return Mago::recibirDanio(cantidad, esCombatePPT);
}

/**
 * @brief Implementación especializada del método meditar
 * 
 * Extiende la meditación base para también recuperar energía de muerte,
 * basándose en el poder necromántico y nivel del personaje.
 */
void Nigromante::meditar() {
    Mago::meditar(); // Llamar al método base
    
    // Bonus para nigromantes: también recuperan energía de muerte
    int recuperacion = poderNecromantico / 5 + nivelPersonaje / 2;
    
    energiaMuerte += recuperacion;
    cout << nombre << " absorbe energía necrótica del ambiente. Energía de muerte: " << energiaMuerte << endl;
}
