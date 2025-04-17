#include "Brujo.hpp"
#include <algorithm>

/**
 * @brief Implementación del constructor de Brujo
 * 
 * Inicializa un brujo con sus atributos básicos heredados de Mago
 * y sus atributos específicos como patrón, pacto demoníaco, corrupción
 * del alma y estado de maldición. Proporciona bonus de maná basado
 * en la corrupción del alma.
 */
Brujo::Brujo(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
             int manaMax, EscuelaMagia esc, FuentePoder fp,
             string patron, int pacto, int corrupcion, bool maldicion)
    : Mago(n, nivel, hp, r, fue, des, con, inte, manaMax, esc, fp),
      nombrePatron(patron), pactoDemoniaco(pacto), corrupcionAlma(corrupcion), maldicionActiva(maldicion) {
    
    // Bonus por corrupción del alma
    manaMaximo += corrupcionAlma * 2;
    manaActual = manaMaximo;
}

/**
 * @brief Implementación del método invocarPatron
 * 
 * Invoca el poder del patrón sobrenatural del brujo para atacar.
 * Aumenta la corrupción del alma como efecto secundario.
 * Requiere gastar maná.
 * 
 * @return Valor numérico que representa el daño causado
 */
int Brujo::invocarPatron() {
    cout << nombre << " invoca el poder de su patrón " << nombrePatron << "..." << endl;
    
    int costoMana = 20;
    if (!gastarMana(costoMana)) {
        return 0;
    }
    
    cout << "Una presencia siniestra se hace sentir cuando " << nombrePatron << " responde a la llamada." << endl;
    
    int poder = pactoDemoniaco * 2 + corrupcionAlma;
    cout << "El poder del patrón causa " << poder << " puntos de daño de energía oscura." << endl;
    
    // Aumentar corrupción del alma al invocar al patrón
    corrupcionAlma += 1;
    cout << "La corrupción del alma de " << nombre << " aumenta a " << corrupcionAlma << "." << endl;
    
    return poder;
}

/**
 * @brief Implementación del método lanzarMaleficio
 * 
 * Lanza un maleficio específico contra un objetivo, causando daño
 * basado en el pacto demoníaco, nivel y corrupción del alma.
 * Requiere conocer el maleficio y gastar maná.
 * 
 * @param nombreMaleficio Nombre del maleficio a lanzar
 * @return Valor numérico que representa el daño causado
 */
int Brujo::lanzarMaleficio(const string& nombreMaleficio) {
    auto it = find(maleficiosConocidos.begin(), maleficiosConocidos.end(), nombreMaleficio);
    if (it == maleficiosConocidos.end()) {
        cout << nombre << " no conoce el maleficio \"" << nombreMaleficio << "\"." << endl;
        return 0;
    }
    
    int costoMana = 10 + corrupcionAlma / 2; // Más corrupción, más coste
    if (!gastarMana(costoMana)) {
        return 0;
    }
    
    cout << nombre << " lanza el maleficio \"" << nombreMaleficio << "\"!" << endl;
    
    int poderMaleficio = pactoDemoniaco + nivelPersonaje + corrupcionAlma / 2;
    cout << "El maleficio causa " << poderMaleficio << " puntos de daño oscuro." << endl;
    
    return poderMaleficio;
}

/**
 * @brief Implementación del método aprenderMaleficio
 * 
 * Añade un nuevo maleficio al repertorio del brujo.
 * Aumenta la corrupción del alma como efecto secundario.
 * 
 * @param nombreMaleficio Nombre del maleficio a aprender
 * @return true si se aprendió el maleficio, false si ya lo conocía
 */
bool Brujo::aprenderMaleficio(const string& nombreMaleficio) {
    if (nombreMaleficio.empty()) {
        cout << "No se puede aprender un maleficio sin nombre." << endl;
        return false;
    }
    
    auto it = find(maleficiosConocidos.begin(), maleficiosConocidos.end(), nombreMaleficio);
    if (it != maleficiosConocidos.end()) {
        cout << nombre << " ya conoce el maleficio \"" << nombreMaleficio << "\"." << endl;
        return false;
    }
    
    maleficiosConocidos.push_back(nombreMaleficio);
    cout << nombre << " ha aprendido el maleficio \"" << nombreMaleficio << "\"." << endl;
    
    // Aprender maleficios aumenta la corrupción
    corrupcionAlma += 1;
    cout << "La corrupción del alma aumenta a " << corrupcionAlma << "." << endl;
    
    return true;
}

/**
 * @brief Implementación del método sacrificarVida
 * 
 * Sacrifica puntos de vida del brujo para obtener maná.
 * Aumenta la corrupción del alma como efecto secundario.
 * 
 * @param cantidad Cantidad de vida a sacrificar
 */
void Brujo::sacrificarVida(int cantidad) {
    if (cantidad <= 0) return;
    
    if (hpActual <= cantidad) {
        cout << nombre << " no puede sacrificar tanta vida, se desmayaría." << endl;
        return;
    }
    
    cout << nombre << " sacrifica " << cantidad << " puntos de vida para obtener poder..." << endl;
    
    // Reducir vida
    hpActual -= cantidad;
    
    // Ganar maná basado en el sacrificio
    int manaGanado = cantidad * 2;
    manaActual = min(manaMaximo, manaActual + manaGanado);
    
    cout << nombre << " pierde " << cantidad << " PV (HP: " << hpActual << "/" << hpMax << ")";
    cout << " pero gana " << manaGanado << " de maná (Maná: " << manaActual << "/" << manaMaximo << ")." << endl;
    
    // Aumentar corrupción
    corrupcionAlma += 1;
    cout << "La corrupción del alma aumenta a " << corrupcionAlma << "." << endl;
}

/**
 * @brief Implementación del método drenajeDePoder
 * 
 * Drena energía vital de un objetivo, causando daño y recuperando
 * parte de ese daño como puntos de vida para el brujo.
 * Requiere gastar maná.
 * 
 * @return Valor numérico que representa el daño causado
 */
int Brujo::drenajeDePoder() {
    cout << nombre << " comienza a drenar poder vital..." << endl;
    
    int costoMana = 15;
    if (!gastarMana(costoMana)) {
        return 0;
    }
    
    int poderDrenaje = pactoDemoniaco + inteligencia / 2;
    cout << "¡" << nombre << " drena " << poderDrenaje << " puntos de vida del objetivo!" << endl;
    
    // Recuperar parte como vida
    int recuperacion = poderDrenaje / 3;
    if (recuperacion > 0) {
        curar(recuperacion);
        cout << nombre << " absorbe " << recuperacion << " puntos de vida drenados." << endl;
    }
    
    return poderDrenaje;
}

/**
 * @brief Implementación del método mostrarInfo
 * 
 * Muestra información detallada sobre el brujo y sus características
 * específicas, además de la información base de mago.
 */
void Brujo::mostrarInfo() const {
    Mago::mostrarInfo(); // Llamamos al método de la clase base
    
    cout << "  Tipo: Brujo" << endl;
    cout << "  Patrón: " << nombrePatron << endl;
    cout << "  Pacto Demoníaco: " << pactoDemoniaco << endl;
    cout << "  Corrupción del Alma: " << corrupcionAlma << endl;
    cout << "  Maldición Activa: " << (maldicionActiva ? "Sí" : "No") << endl;
    
    cout << "  Maleficios conocidos: ";
    if (maleficiosConocidos.empty()) {
        cout << "Ninguno" << endl;
    } else {
        cout << endl;
        for (const auto& maleficio : maleficiosConocidos) {
            cout << "    - " << maleficio << endl;
        }
    }
}

/**
 * @brief Implementación especializada del método gastarMana
 * 
 * Los brujos pueden optar por sacrificar vida cuando no tienen
 * suficiente maná para lanzar un hechizo o habilidad.
 * 
 * @param cantidad Cantidad de maná a gastar
 * @return true si pudo gastar el maná o sacrificar vida, false en caso contrario
 */
bool Brujo::gastarMana(int cantidad) {
    if (manaActual < cantidad && hpActual > 10) {
        int deficit = cantidad - manaActual;
        cout << nombre << " no tiene suficiente maná. ¿Desea sacrificar " << deficit << " puntos de vida para compensar?" << endl;
        
        string respuesta;
        cin >> respuesta;

        while (respuesta != "si" && respuesta != "no") {
            cout << "Respuesta inválida. Por favor, responda 'si' o 'no': ";
            cin >> respuesta;
        }

        if (respuesta == "si") {
            sacrificarVida(deficit);
        }
        else {
            cout << nombre << " no sacrifica vida y no puede lanzar el hechizo." << endl;
            return false;
        }
    }
    
    return Mago::gastarMana(cantidad);
}

/**
 * @brief Implementación especializada del método lanzarHechizo
 * 
 * Potencia los hechizos básicos con la corrupción del alma del brujo,
 * aumentando su poder destructivo.
 * 
 * @param nombreHechizo Nombre del hechizo a lanzar
 * @return Valor numérico que representa el efecto del hechizo
 */
int Brujo::lanzarHechizo(const string& nombreHechizo) {
    int efectoBase = Mago::lanzarHechizo(nombreHechizo);
    
    // Los brujos tienen bonus por su corrupción
    if (efectoBase > 0 && corrupcionAlma > 0) {
        int bonus = corrupcionAlma / 3;
        
        if (bonus > 0) {
            cout << "La corrupción del alma potencia el hechizo, añadiendo " << bonus << " al efecto." << endl;
            efectoBase += bonus;
        }
    }
    
    return efectoBase;
}
