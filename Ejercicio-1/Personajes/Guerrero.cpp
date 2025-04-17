#include "Guerrero.hpp"

/**
 * @brief Implementacion del constructor de Guerrero
 * 
 * Inicializa un guerrero con sus atributos basicos y especificos.
 * Ajusta valores no validos a minimos aceptables y aumenta los HP
 * basados en la resistencia fisica.
 */
Guerrero::Guerrero(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
                   int estMax, EstiloCombate est, TipoArmadura ta, int defBase, int resFis)
    : nombre(n), nivelPersonaje(nivel), hpMax(hp), hpActual(hp), raza(r), 
      fuerza(fue), destreza(des), constitucion(con), inteligencia(inte), 
      armaEquipadaPos(-1), hpOriginalParaCombatePPT(hp), enModoCombatePPT(false),
      estaminaMaxima(estMax), estaminaActual(estMax), estilo(est), tipoArmadura(ta),
      defensaBase(defBase), resistenciaFisica(resFis) {
    
    if (nivel < 1) nivelPersonaje = 1;
    if (hpMax < 1) hpMax = 1;
    hpActual = hpMax;
    if (estaminaMaxima < 0) estaminaMaxima = 0;
    estaminaActual = estaminaMaxima;
    
    // Aumentamos el HP base por la resistencia física
    hpMax += resistenciaFisica * 2;
    hpActual = hpMax;
}

// ==========================================
// IMPLEMENTACIONES DE INTERFAZPERSONAJE
// ==========================================

/**
 * @brief Implementacion de getters y setters basicos
 */
string Guerrero::getNombre() const { return nombre; }
void Guerrero::setNombre(const string& nuevoNombre) { nombre = nuevoNombre; }

int Guerrero::getHP() const { return hpActual; }

/**
 * @brief Implementacion del metodo recibirDanio
 * 
 * Reduce los HP del guerrero segun el daño recibido.
 * En modo combate PPT, el daño siempre es 10.
 * 
 * @param cantidad Cantidad de daño a recibir
 * @param esCombatePPT Indica si es un combate PPT
 * @return true si sigue vivo, false si ha muerto
 */
bool Guerrero::recibirDanio(int cantidad, bool esCombatePPT) {
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
 * Aumenta los HP del guerrero sin superar el maximo.
 * 
 * @param cantidad Cantidad de HP a recuperar
 */
void Guerrero::curar(int cantidad) {
    if (cantidad <= 0) return;
    
    int hpPrevio = hpActual;
    hpActual = min(hpMax, hpActual + cantidad);
    
    cout << nombre << " recupera " << (hpActual - hpPrevio) << " puntos de vida. HP: " << hpActual << "/" << hpMax << endl;
}

/**
 * @brief Implementacion del metodo agregarArma
 * 
 * Añade un arma al inventario del guerrero si hay espacio.
 * 
 * @param arma El arma a añadir (se transfiere la propiedad)
 * @return true si se añadio correctamente, false si no hay espacio
 */
bool Guerrero::agregarArma(unique_ptr<InterfazArmas> arma) {
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
unique_ptr<InterfazArmas> Guerrero::quitarArma(int posicion) {
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
InterfazArmas* Guerrero::getArma(int posicion) const {
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
int Guerrero::atacar(MovimientoCombate movimiento) {
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
 * Muestra todas las armas en el inventario del guerrero.
 */
void Guerrero::mostrarInventario() const {
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

// ==========================================
// GESTION DE ARMAS
// ==========================================

/**
 * @brief Implementacion del metodo equiparArma
 * 
 * Establece un arma del inventario como equipada.
 * 
 * @param posicion Indice del arma a equipar
 * @return true si se equipo correctamente, false si la posicion es invalida
 */
bool Guerrero::equiparArma(int posicion) {
    if (posicion < 0 || posicion >= static_cast<int>(inventarioArmas.size())) {
        cout << "No se puede equipar un arma en la posición " << posicion << " (posición inválida)." << endl;
        return false;
    }
    
    armaEquipadaPos = posicion;
    cout << nombre << " ha equipado " << inventarioArmas[posicion]->getNombre() << "." << endl;
    return true;
}

/**
 * @brief Implementacion de getters para atributos basicos
 */
int Guerrero::getNivel() const { return nivelPersonaje; }
Raza Guerrero::getRaza() const { return raza; }
int Guerrero::getFuerza() const { return fuerza; }
int Guerrero::getDestreza() const { return destreza; }
int Guerrero::getConstitucion() const { return constitucion; }
int Guerrero::getInteligencia() const { return inteligencia; }
int Guerrero::getArmaEquipadaPos() const { return armaEquipadaPos; }

/**
 * @brief Implementacion del metodo getArmaEquipada
 * 
 * @return Puntero al arma equipada o nullptr si no hay arma equipada
 */
InterfazArmas* Guerrero::getArmaEquipada() const {
    if (armaEquipadaPos >= 0 && armaEquipadaPos < static_cast<int>(inventarioArmas.size())) {
        return inventarioArmas[armaEquipadaPos].get();
    }
    return nullptr;
}

// ==========================================
// GESTION DE ESTAMINA Y DEFENSA
// ==========================================

/**
 * @brief Implementacion del metodo getEstamina
 * 
 * @return Estamina actual del guerrero
 */
int Guerrero::getEstamina() const { return estaminaActual; }

/**
 * @brief Implementacion del metodo gastarEstamina
 * 
 * Verifica si hay suficiente estamina antes de gastar.
 * Muestra un mensaje informativo.
 * 
 * @param cantidad Estamina a gastar
 * @return true si se gasto correctamente, false si no hay suficiente
 */
bool Guerrero::gastarEstamina(int cantidad) {
    if (cantidad <= 0) return true;
    
    if (estaminaActual < cantidad) {
        cout << nombre << " no tiene suficiente estamina para realizar esta acción." << endl;
        return false;
    }
    
    estaminaActual -= cantidad;
    cout << nombre << " gasta " << cantidad << " puntos de estamina. Estamina: " 
         << estaminaActual << "/" << estaminaMaxima << endl;
    return true;
}

/**
 * @brief Implementacion del metodo recuperarEstamina
 * 
 * Incrementa la estamina actual sin superar el maximo.
 * Muestra un mensaje informativo.
 * 
 * @param cantidad Estamina a recuperar
 */
void Guerrero::recuperarEstamina(int cantidad) {
    if (cantidad <= 0) return;
    
    int estaminaPrevia = estaminaActual;
    estaminaActual = min(estaminaMaxima, estaminaActual + cantidad);
    
    cout << nombre << " recupera " << (estaminaActual - estaminaPrevia) << " puntos de estamina. Estamina: " 
         << estaminaActual << "/" << estaminaMaxima << endl;
}

/**
 * @brief Implementacion de getters para atributos de defensa
 */
EstiloCombate Guerrero::getEstiloCombate() const { return estilo; }
TipoArmadura Guerrero::getTipoArmadura() const { return tipoArmadura; }
int Guerrero::getDefensaBase() const { return defensaBase; }
int Guerrero::getResistenciaFisica() const { return resistenciaFisica; }

// ==========================================
// HABILIDADES DE GUERRERO
// ==========================================

/**
 * @brief Implementacion del metodo ejecutarTecnicaEspecial
 * 
 * El guerrero ejecuta una tecnica especial que causa más daño.
 * Requiere estamina para ser ejecutada.
 * 
 * @return Valor numerico que representa el daño causado
 */
int Guerrero::ejecutarTecnicaEspecial() {
    cout << nombre << " prepara una técnica especial de combate..." << endl;
    
    int costoEstamina = 15;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    cout << "¡" << nombre << " ejecuta un poderoso golpe!" << endl;
    
    // Daño basado en fuerza
    return 10 + nivelPersonaje + fuerza;
}

/**
 * @brief Implementacion del metodo aumentarPosturaDefensiva
 * 
 * El guerrero aumenta temporalmente su defensa.
 * Requiere estamina para ser ejecutada.
 * 
 * @return Valor numerico que representa el bonus de defensa
 */
int Guerrero::aumentarPosturaDefensiva() {
    cout << nombre << " adopta una postura más defensiva..." << endl;
    
    int costoEstamina = 5;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    int bonusDefensa = defensaBase + constitucion / 2;
    cout << nombre << " aumenta su defensa en " << bonusDefensa << " puntos temporalmente." << endl;
    
    return bonusDefensa; // Retorna el bonus de defensa
}

/**
 * @brief Implementacion del metodo provocarEnemigo
 * 
 * El guerrero provoca a los enemigos para atraer su atencion.
 * Requiere estamina para ser ejecutada.
 * 
 * @return Valor numerico simbolico que representa el exito de la provocacion
 */
int Guerrero::provocarEnemigo() {
    cout << nombre << " provoca al enemigo para que lo ataque..." << endl;
    
    int costoEstamina = 8;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    cout << "Los enemigos ahora están más propensos a atacar a " << nombre << "." << endl;
    
    // Esto podría afectar la IA del enemigo en un sistema más complejo
    return 1; // Valor simbólico para indicar que lo afecto 
}

/**
 * @brief Implementacion del metodo cargarContra
 * 
 * El guerrero embiste contra un enemigo especifico.
 * Requiere estamina para ser ejecutada.
 * 
 * @param nombreEnemigo El nombre del enemigo objetivo
 * @return Valor numerico que representa el daño causado
 */
int Guerrero::cargarContra(string nombreEnemigo) {
    cout << nombre << " carga contra " << nombreEnemigo << "..." << endl;
    
    int costoEstamina = 12;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    cout << "¡" << nombre << " embiste con fuerza!" << endl;
    return 8 + fuerza / 2 + constitucion / 4;
}

/**
 * @brief Implementacion del metodo bloquearConEscudo
 * 
 * El guerrero bloquea un ataque con su escudo si tiene uno.
 * Solo funciona con armaduras media o pesada.
 * Requiere estamina para ser ejecutada.
 * 
 * @return Valor numerico que representa la cantidad de daño bloqueado
 */
int Guerrero::bloquearConEscudo() {
    if (tipoArmadura == TipoArmadura::Ligera || tipoArmadura == TipoArmadura::Ninguna) {
        cout << nombre << " no tiene un escudo para bloquear." << endl;
        return 0;
    }
    
    cout << nombre << " bloquea con su escudo..." << endl;
    
    int costoEstamina = 7;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    int bonusDefensa = defensaBase + constitucion;
    cout << nombre << " bloquea " << bonusDefensa << " puntos de daño." << endl;
    
    return bonusDefensa; // Retorna la cantidad de daño bloqueado
}

/**
 * @brief Implementacion del metodo mostrarInfo
 * 
 * Muestra informacion detallada sobre el guerrero y sus caracteristicas.
 */
void Guerrero::mostrarInfo() const {
    cout << "  Clase: Guerrero" << endl;
    cout << "  Estilo de Combate: " << estiloCombateToString(estilo) << endl;
    cout << "  Armadura: " << tipoArmaduraToString(tipoArmadura) << endl;
    cout << "  Estamina: " << estaminaActual << "/" << estaminaMaxima << endl;
    cout << "  Defensa Base: " << defensaBase << endl;
    cout << "  Resistencia Física: " << resistenciaFisica << endl;
}

/**
 * @brief Implementacion del metodo resolverMovimiento
 * 
 * Calcula el daño de un ataque basado en el movimiento y el arma.
 * Los guerreros tienen bonus en Golpe Fuerte por su fuerza y
 * en Defensa y Golpe por su constitucion.
 * 
 * @param movimiento Tipo de ataque a realizar
 * @param armaUsada Arma con la que se realiza el ataque
 * @return Valor numerico que representa el daño calculado
 */
int Guerrero::resolverMovimiento(MovimientoCombate movimiento, InterfazArmas* armaUsada) const {
    if (!armaUsada) return 0;
    
    int danioBase = armaUsada->usar();
    
    if (movimiento == MovimientoCombate::GolpeFuerte) {
        int bonus = fuerza / 3;
        if (bonus > 0) {
            cout << "¡Bonus de fuerza: +" << bonus << " al daño!" << endl;
            danioBase += bonus;
        }
    }
    // También son buenos en Defensa y Golpe (bonus de constitución)
    else if (movimiento == MovimientoCombate::DefensaYGolpe) {
        int bonus = constitucion / 4;
        if (bonus > 0) {
            cout << "¡Bonus de constitución: +" << bonus << " al daño y defensa!" << endl;
            danioBase += bonus;
        }
    }
    
    return danioBase;
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
bool Guerrero::setHPParaCombatePPT() {
    try {
        if (enModoCombatePPT) {
            return true;
        }
        hpOriginalParaCombatePPT = hpActual;
        
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
bool Guerrero::restaurarHPOriginal() {
    try {
        if (!enModoCombatePPT) {
            return true;
        }
        
        hpActual = hpOriginalParaCombatePPT;
        enModoCombatePPT = false;
        
        return true;
    } catch (const exception& e) {
        cerr << "Error al restaurar HP original: " << e.what() << endl;
        return false;
    }
}
