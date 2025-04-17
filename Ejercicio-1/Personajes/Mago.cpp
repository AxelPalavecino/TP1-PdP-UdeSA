#include "Mago.hpp"
#include <algorithm>

/**
 * @brief Implementacion del constructor de Mago
 * 
 * Inicializa un mago con sus atributos basicos y especificos.
 * Ajusta valores no validos a minimos aceptables.
 */
Mago::Mago(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
           int manaMax, EscuelaMagia esc, FuentePoder fp)
    : nombre(n), nivelPersonaje(nivel), hpMax(hp), hpActual(hp), raza(r), 
      fuerza(fue), destreza(des), constitucion(con), inteligencia(inte), 
      armaEquipadaPos(-1), hpOriginalParaCombatePPT(hp), enModoCombatePPT(false),
      manaMaximo(manaMax), manaActual(manaMax), escuela(esc), fuentePoder(fp) {
    
    if (nivel < 1) nivelPersonaje = 1;
    if (hpMax < 1) hpMax = 1;
    hpActual = hpMax;
    if (manaMaximo < 0) manaMaximo = 0;
    manaActual = manaMaximo;
}

// ==========================================
// GESTION DE MAGIA
// ==========================================

/**
 * @brief Implementacion del metodo getMana
 * @return Mana actual del mago
 */
int Mago::getMana() const { return manaActual; }

/**
 * @brief Implementacion del metodo gastarMana
 * 
 * Verifica si hay suficiente mana antes de gastar.
 * Muestra un mensaje informativo.
 * 
 * @param cantidad Mana a gastar
 * @return true si se gasto correctamente, false si no hay suficiente
 */
bool Mago::gastarMana(int cantidad) {
    if (cantidad <= 0) return true;
    
    if (manaActual < cantidad) {
        cout << nombre << " no tiene suficiente maná para realizar esta acción." << endl;
        return false;
    }
    
    manaActual -= cantidad;
    cout << nombre << " gasta " << cantidad << " puntos de maná. Maná: " << manaActual << "/" << manaMaximo << endl;
    return true;
}

/**
 * @brief Implementacion del metodo recuperarMana
 * 
 * Incrementa el mana actual sin superar el maximo.
 * Muestra un mensaje informativo.
 * 
 * @param cantidad Mana a recuperar
 */
void Mago::recuperarMana(int cantidad) {
    if (cantidad <= 0) return;
    
    int manaPrevio = manaActual;
    manaActual = min(manaMaximo, manaActual + cantidad);
    
    cout << nombre << " recupera " << (manaActual - manaPrevio) << " puntos de maná. Maná: " << manaActual << "/" << manaMaximo << endl;
}

/**
 * @brief Implementacion de getters para escuela y fuente de poder
 */
EscuelaMagia Mago::getEscuelaMagia() const { return escuela; }
FuentePoder Mago::getFuentePoder() const { return fuentePoder; }

// ==========================================
// HABILIDADES DE MAGO
// ==========================================

/**
 * @brief Implementacion del metodo lanzarHechizo
 * 
 * Verifica si el mago conoce el hechizo y si tiene suficiente mana.
 * Calcula el efecto basado en nivel e inteligencia.
 * 
 * @param nombreHechizo Nombre del hechizo a lanzar
 * @return Valor numerico que representa el efecto del hechizo
 */
int Mago::lanzarHechizo(const string& nombreHechizo) {
    if (!conoceHechizo(nombreHechizo)) {
        cout << nombre << " no conoce el hechizo \"" << nombreHechizo << "\"." << endl;
        return 0;
    }
    
    int costoMana = 10; // Costo base, podría variar por hechizo
    
    if (!gastarMana(costoMana)) {
        return 0;
    }
    
    cout << nombre << " lanza el hechizo \"" << nombreHechizo << "\"!" << endl;
    
    // Simplificado: cada hechizo tiene un daño base + nivel + inteligencia
    int efectoHechizo = 5 + nivelPersonaje + inteligencia / 2;
    
    return efectoHechizo;
}

/**
 * @brief Implementacion del metodo meditar
 * 
 * Permite al mago recuperar mana mediante meditacion.
 * La cantidad recuperada se basa en la inteligencia.
 */
void Mago::meditar() {
    cout << nombre << " medita profundamente..." << endl;
    
    int recuperacion = 5 + inteligencia / 2;
    recuperarMana(recuperacion);
}

/**
 * @brief Implementacion del metodo aprenderHechizo
 * 
 * Añade un nuevo hechizo a la lista de hechizos conocidos.
 * Verifica que el nombre no este vacio y que no se conozca ya.
 * 
 * @param nombreHechizo Nombre del hechizo a aprender
 * @return true si se aprendio el hechizo, false en caso contrario
 */
bool Mago::aprenderHechizo(const string& nombreHechizo) {
    if (nombreHechizo.empty()) {
        cout << "No se puede aprender un hechizo sin nombre." << endl;
        return false;
    }
    
    if (conoceHechizo(nombreHechizo)) {
        cout << nombre << " ya conoce el hechizo \"" << nombreHechizo << "\"." << endl;
        return false;
    }
    
    hechizosConocidos.push_back(nombreHechizo);
    cout << nombre << " ha aprendido el hechizo \"" << nombreHechizo << "\"." << endl;
    return true;
}

/**
 * @brief Implementacion del metodo listarHechizos
 * 
 * Muestra todos los hechizos conocidos por el mago.
 */
void Mago::listarHechizos() const {
    cout << "Hechizos conocidos por " << nombre << ":" << endl;
    
    if (hechizosConocidos.empty()) {
        cout << "  (Ninguno)" << endl;
        return;
    }
    
    for (size_t i = 0; i < hechizosConocidos.size(); ++i) {
        cout << "  " << (i + 1) << ". " << hechizosConocidos[i] << endl;
    }
}

/**
 * @brief Implementacion del metodo conoceHechizo
 * 
 * Verifica si un hechizo esta en la lista de hechizos conocidos.
 * 
 * @param nombreHechizo Nombre del hechizo a verificar
 * @return true si el hechizo es conocido, false en caso contrario
 */
bool Mago::conoceHechizo(const string& nombreHechizo) const {
    return find(hechizosConocidos.begin(), hechizosConocidos.end(), nombreHechizo) != hechizosConocidos.end();
}

/**
 * @brief Implementacion del metodo mostrarInfo
 * 
 * Muestra informacion detallada sobre el mago y sus caracteristicas.
 */
void Mago::mostrarInfo() const {
    cout << "  Clase: Mago" << endl;
    cout << "  Especialización: " << escuelaMagiaToString(escuela) << endl;
    cout << "  Fuente de Poder: " << fuentePoderToString(fuentePoder) << endl;
    cout << "  Maná: " << manaActual << "/" << manaMaximo << endl;
    cout << "  Hechizos conocidos: " << hechizosConocidos.size() << endl;
}

/**
 * @brief Implementacion del metodo resolverMovimiento
 * 
 * Calcula el daño de un ataque basado en el movimiento y el arma.
 * Los magos tienen bonus en Golpe Rapido por su inteligencia.
 * 
 * @param movimiento Tipo de ataque a realizar
 * @param armaUsada Arma con la que se realiza el ataque
 * @return Valor numerico que representa el daño calculado
 */
int Mago::resolverMovimiento(MovimientoCombate movimiento, InterfazArmas* armaUsada) const {
    if (!armaUsada) return 0;
    
    int danioBase = armaUsada->usar(); // Usar el arma para su efecto básico
    
    // Los magos son mejores con Golpe Rápido (bonus de inteligencia)
    if (movimiento == MovimientoCombate::GolpeRapido) {
        int bonus = inteligencia / 4;
        if (bonus > 0) {
            cout << "¡Bonus de inteligencia: +" << bonus << " al daño!" << endl;
            danioBase += bonus;
        }
    }
    
    return danioBase;
}

/**
 * @brief Implementacion del metodo invocarElemental
 * 
 * El mago invoca un elemental que causa daño.
 * Requiere mana para ser lanzado.
 * 
 * @return Valor numerico que representa el daño causado
 */
int Mago::invocarElemental() {
    cout << nombre << " comienza a invocar un elemental..." << endl;
    
    int costoMana = 20;
    if (!gastarMana(costoMana)) {
        return 0;
    }
    
    cout << "¡Un elemental aparece para ayudar a " << nombre << "!" << endl;
    
    // Daño basado en nivel e inteligencia
    return 15 + nivelPersonaje + inteligencia;
}

/**
 * @brief Implementacion del metodo proyectilMagico
 * 
 * El mago lanza un proyectil de energia magica.
 * Requiere menos mana que invocar un elemental pero causa menos daño.
 * 
 * @return Valor numerico que representa el daño causado
 */
int Mago::proyectilMagico() {
    cout << nombre << " conjura un proyectil mágico..." << endl;
    
    int costoMana = 5;
    if (!gastarMana(costoMana)) {
        return 0;
    }
    
    cout << "¡El proyectil mágico vuela velozmente hacia el objetivo!" << endl;
    
    // Daño basado en nivel e inteligencia
    return 8 + nivelPersonaje / 2 + inteligencia / 2;
}

// ==========================================
// IMPLEMENTACIONES DE INTERFAZPERSONAJE
// ==========================================

string Mago::getNombre() const { return nombre; }
void Mago::setNombre(const string& nuevoNombre) { nombre = nuevoNombre; }

int Mago::getHP() const { return hpActual; }

/**
 * @brief Implementacion del metodo recibirDanio
 * 
 * Reduce los HP del mago segun el daño recibido.
 * En modo combate PPT, el daño siempre es 10.
 * 
 * @param cantidad Cantidad de daño a recibir
 * @param esCombatePPT Indica si es un combate PPT
 * @return true si sigue vivo, false si ha muerto
 */
bool Mago::recibirDanio(int cantidad, bool esCombatePPT) {
    if (cantidad <= 0) return true;
    
    if (!esCombatePPT) {
        hpActual = max(0, hpActual - cantidad);
        cout << nombre << " recibe " << cantidad << " puntos de daño. HP: " << hpActual << "/" << hpMax << endl;
        
        if (hpActual <= 0) {
            cout << "¡" << nombre << " ha caído!" << endl;
            return false; // Ha muerto
        }
        
        return true; // Sigue vivo
    } 
    hpActual = max(0, hpActual - 10);
    cout << nombre << " recibe 10 puntos de daño. HP: " << hpActual << "/" << hpMax << endl;
        
    if (hpActual <= 0) {
        cout << "¡" << nombre << " ha caído!" << endl;
        return false; // Ha muerto
    }
    
    return true;
}

/**
 * @brief Implementacion del metodo curar
 * 
 * Aumenta los HP del mago sin superar el maximo.
 * 
 * @param cantidad Cantidad de HP a recuperar
 */
void Mago::curar(int cantidad) {
    if (cantidad <= 0) return;
    
    int hpPrevio = hpActual;
    hpActual = min(hpMax, hpActual + cantidad);
    
    cout << nombre << " recupera " << (hpActual - hpPrevio) << " puntos de vida. HP: " << hpActual << "/" << hpMax << endl;
}

/**
 * @brief Implementacion del metodo agregarArma
 * 
 * Añade un arma al inventario del mago si hay espacio.
 * 
 * @param arma El arma a añadir (se transfiere la propiedad)
 * @return true si se añadio correctamente, false si no hay espacio
 */
bool Mago::agregarArma(unique_ptr<InterfazArmas> arma) {
    if (!arma) {
        cout << "No se puede agregar un arma nula al inventario." << endl;
        return false;
    }
    
    if (inventarioArmas.size() >= MAX_ARMAS) {
        cout << "El inventario de " << nombre << " está lleno (" << MAX_ARMAS << " armas máximo)." << endl;
        return false;
    }
    
    string nombreArma = arma->getNombre();  // Guardar el nombre antes de mover
    inventarioArmas.push_back(move(arma));  // Transferir propiedad
    cout << "Se ha añadido " << nombreArma << " al inventario de " << nombre << "." << endl;
    
    // Si no tiene arma equipada, equipamos automáticamente la primera
    if (armaEquipadaPos == -1) {
        equiparArma(inventarioArmas.size() - 1);
    }
    
    return true;
}

/**
 * @brief Implementacion del metodo quitarArma
 * 
 * Quita un arma del inventario y transfiere su propiedad.
 * 
 * @param posicion Indice del arma a quitar
 * @return El arma quitada, o nullptr si la posicion es invalida
 */
unique_ptr<InterfazArmas> Mago::quitarArma(int posicion) {
    if (posicion < 0 || posicion >= static_cast<int>(inventarioArmas.size())) {
        cout << "Posición de arma inválida." << endl;
        return nullptr;
    }
    
    // Guardar referencia al arma y su nombre antes de sacarla del vector
    string nombreArma = inventarioArmas[posicion]->getNombre();
    
    // Preparar el puntero para transferir propiedad
    unique_ptr<InterfazArmas> arma = move(inventarioArmas[posicion]);
    
    // Quitar el espacio vacío del vector
    inventarioArmas.erase(inventarioArmas.begin() + posicion);
    
    // Si quitamos el arma equipada, desequipamos
    if (posicion == armaEquipadaPos) {
        armaEquipadaPos = -1;
    }
    // Si quitamos un arma antes del arma equipada, actualizar índice
    else if (posicion < armaEquipadaPos) {
        armaEquipadaPos--;
    }
    
    cout << nombre << " ha quitado " << nombreArma << " de su inventario." << endl;
    return arma;
}

/**
 * @brief Implementacion del metodo getArma
 * 
 * Obtiene una referencia a un arma sin quitar propiedad.
 * 
 * @param posicion Indice del arma deseada
 * @return Puntero al arma o nullptr si la posicion es invalida
 */
InterfazArmas* Mago::getArma(int posicion) const {
    if (posicion < 0 || posicion >= static_cast<int>(inventarioArmas.size())) {
        return nullptr;
    }
    return inventarioArmas[posicion].get();
}

/**
 * @brief Implementacion del metodo atacar
 * 
 * Realiza un ataque con el arma equipada usando el movimiento especificado.
 * 
 * @param movimiento Tipo de movimiento de ataque
 * @return Valor numerico que representa el daño causado
 */
int Mago::atacar(MovimientoCombate movimiento) {
    auto armaEquipada = getArmaEquipada();
    if (!armaEquipada) {
        cout << nombre << " intenta atacar, pero no tiene ningún arma equipada." << endl;
        return 0;
    }
    
    int danioBase = resolverMovimiento(movimiento, armaEquipada);
    cout << nombre << " utiliza " << movimientoCombateToString(movimiento) 
         << " con " << armaEquipada->getNombre() << "." << endl;
    
    return danioBase;
}

/**
 * @brief Implementacion del metodo mostrarInventario
 * 
 * Muestra todas las armas en el inventario del mago.
 */
void Mago::mostrarInventario() const {
    cout << "Inventario de " << nombre << " (" << inventarioArmas.size() << "/" << MAX_ARMAS << " armas):" << endl;
    
    if (inventarioArmas.empty()) {
        cout << "  (Vacío)" << endl;
        return;
    }
    
    for (size_t i = 0; i < inventarioArmas.size(); ++i) {
        cout << "  [" << i << "] " << inventarioArmas[i]->getNombre() 
             << (static_cast<int>(i) == armaEquipadaPos ? " (Equipada)" : "") << endl;
    }
}

/**
 * @brief Implementacion del metodo equiparArma
 * 
 * Establece un arma del inventario como equipada.
 * 
 * @param posicion Indice del arma a equipar
 * @return true si se equipo correctamente, false si la posicion es invalida
 */
bool Mago::equiparArma(int posicion) {
    if (posicion < 0 || posicion >= static_cast<int>(inventarioArmas.size())) {
        cout << "No se puede equipar un arma en la posición " << posicion << " (posición inválida)." << endl;
        return false;
    }
    
    armaEquipadaPos = posicion;
    cout << nombre << " ha equipado " << inventarioArmas[posicion]->getNombre() << "." << endl;
    return true;
}

// Implementación de getters para atributos básicos
int Mago::getNivel() const { return nivelPersonaje; }
Raza Mago::getRaza() const { return raza; }
int Mago::getFuerza() const { return fuerza; }
int Mago::getDestreza() const { return destreza; }
int Mago::getConstitucion() const { return constitucion; }
int Mago::getInteligencia() const { return inteligencia; }
int Mago::getArmaEquipadaPos() const { return armaEquipadaPos; }

/**
 * @brief Implementacion del metodo getArmaEquipada
 * 
 * @return Puntero al arma equipada o nullptr si no hay arma equipada
 */
InterfazArmas* Mago::getArmaEquipada() const {
    if (armaEquipadaPos >= 0 && armaEquipadaPos < static_cast<int>(inventarioArmas.size())) {
        return inventarioArmas[armaEquipadaPos].get();
    }
    return nullptr;
}

// ==========================================
// METODOS PARA COMBATE PPT
// ==========================================

/**
 * @brief Implementacion del metodo setHPParaCombatePPT
 * 
 * Establece los HP exactamente en 100 para un combate PPT.
 * Guarda el HP actual para restaurarlo despues.
 * 
 * @return true si se configuro correctamente, false si hubo un error
 */
bool Mago::setHPParaCombatePPT() {
    try {
        // Si ya estamos en modo combate PPT, no hacemos nada
        if (enModoCombatePPT) {
            return true;
        }
        
        // Guarda el HP actual para poder restaurarlo después
        hpOriginalParaCombatePPT = hpActual;
        
        // Establece el HP exactamente a 100
        hpActual = 100;
        enModoCombatePPT = true;
        
        return true;
    } catch (const exception& e) {
        cerr << "Error al establecer HP para combate: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Implementacion del metodo restaurarHPOriginal
 * 
 * Restaura el HP original despues de un combate PPT.
 * 
 * @return true si se restauro correctamente, false si hubo un error
 */
bool Mago::restaurarHPOriginal() {
    try {
        // Si no estamos en modo combate PPT, no hacemos nada
        if (!enModoCombatePPT) {
            return true;
        }
        
        // Restaura el HP original
        hpActual = hpOriginalParaCombatePPT;
        enModoCombatePPT = false;
        
        return true;
    } catch (const exception& e) {
        cerr << "Error al restaurar HP original: " << e.what() << endl;
        return false;
    }
}

/**
 * @brief Implementacion del metodo getEsCombatePPT
 * 
 * @return true si el personaje esta en modo combate PPT, false en caso contrario
 */
bool Mago::getEsCombatePPT() const {
    return enModoCombatePPT;
}