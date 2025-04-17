#include "ArmaDeCombate.hpp"
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

// ==========================================
// IMPLEMENTACION DE METODOS CLASE ARMADECOMBATE
// ==========================================

/**
 * @brief Implementación del constructor de ArmaDeCombate
 * 
 * Inicializa todos los atributos del arma con los valores proporcionados.
 * Si la durabilidad máxima es menor o igual a cero, se establece en 1 
 * para evitar armas inutilizables desde el inicio.
 */
ArmaDeCombate::ArmaDeCombate(string n, int df, int dm, double p, Rarity r, int nf) {
    this->nombre = n;
    this->danioFisico = df;
    this->durabilidadMaxima = dm;
    this->durabilidadActual = dm;
    this->peso = p;
    this->rareza = r;
    this->nivelFilo = nf;
    if (dm <= 0) {
        this->durabilidadMaxima = 1;
        this->durabilidadActual = 1;
    }
}

// Implementación de getters y setters (ya documentados en el .hpp)
void ArmaDeCombate::setNombre(const string& nombreArg) { nombre = nombreArg; }
string ArmaDeCombate::getNombre() const { return nombre; }
int ArmaDeCombate::getPoder() const { return danioFisico; }
int ArmaDeCombate::getDurabilidadActual() const { return durabilidadActual; }
int ArmaDeCombate::getDurabilidadMaxima() const { return durabilidadMaxima; }
Rarity ArmaDeCombate::getRareza() const { return rareza; }
double ArmaDeCombate::getPeso() const { return peso; }
int ArmaDeCombate::getNivelFilo() const { return nivelFilo; }

/**
 * @brief Implementación del método reparar
 * 
 * Verifica que la cantidad a reparar sea positiva antes de aplicarla.
 * Incrementa la durabilidad actual sin superar el máximo y muestra
 * información sobre el estado resultante del arma.
 */
void ArmaDeCombate::reparar(int cantidad) {
    if (cantidad <= 0) return;
    durabilidadActual = min(durabilidadMaxima, durabilidadActual + cantidad);
    cout << nombre << " reparada. Durabilidad actual: " << durabilidadActual << "/" << durabilidadMaxima << endl;
}

/**
 * @brief Implementación del método afilar
 * 
 * Verifica las condiciones necesarias para afilar el arma:
 * - La cantidad debe ser positiva
 * - El nivel de filo no debe estar al máximo (100)
 * 
 * Incrementa el nivel de filo del arma hasta un máximo de 100 y
 * muestra el nuevo estado del nivel de filo.
 */
bool ArmaDeCombate::afilar(int cantidad) {
    if (cantidad <= 0) return false;
    if (nivelFilo >= 100) {
        cout << nombre << " ya está afilada al máximo." << endl;
        return false;
    }
    nivelFilo = min(100, nivelFilo + cantidad);
    cout << nombre << " afilada. Nivel de filo: " << nivelFilo << "/100" << endl;
    return true;
}

/**
 * @brief Implementación del método mostrarInfo
 * 
 * Muestra información detallada sobre el arma incluyendo:
 * nombre, rareza, tipo, daño, durabilidad y nivel de filo.
 * Utiliza las funciones de conversión para mostrar valores legibles.
 */
void ArmaDeCombate::mostrarInfo() const {
    cout << "Nombre: " << nombre << " [" << rarityToString(rareza) << "]" << endl;
    cout << "  Tipo: Arma de Combate" << endl;
    cout << "  Daño Físico: " << danioFisico << endl;
    cout << "  Durabilidad: " << durabilidadActual << "/" << durabilidadMaxima << endl;
    cout << "  Nivel de Filo: " << nivelFilo << endl;
    cout << "  Peso: " << peso << endl;
}

/**
 * @brief Implementación del método usar
 * 
 * Este método simula el uso del arma en combate:
 * 1. Comprueba si el arma está rota y lanza excepciones si es así
 * 2. Calcula el daño total sumando el daño base y el bono por filo
 * 3. Reduce la durabilidad del arma
 * 4. Simula el posible desgaste aleatorio del filo con una probabilidad
 *    inversamente proporcional al nivel de filo
 * 5. Devuelve el daño total calculado
 * 
 * @return El daño total causado, o 0 si el arma no puede usarse
 */
int ArmaDeCombate::usar() {
    try {
        if (durabilidadActual <= 0) {
            throw std::runtime_error("El arma " + nombre + " está rota.");
        }

        cout << nombre << " ataca!" << endl;

        // Calculo el daño base (esto se puede domificar dependiendo del arma)
        int danioBase = danioFisico;
        int bonoFilo = calcularBonoPorFilo();
        int danioTotal = danioBase + bonoFilo;

        cout << "Daño base: " << danioBase << (bonoFilo > 0 ? " + " + std::to_string(bonoFilo) + " (filo)" : "") << " = " << danioTotal << endl;

        reducirDurabilidad(1);

        if (nivelFilo > 0 && (rand() % (10 + nivelFilo / 10) == 0)) {
            nivelFilo = max(0, nivelFilo - (1 + rand() % 3));
            cout << "El filo de " << nombre << " se desgasta. Nivel de filo: " << nivelFilo << "/100" << endl;
        }

        return danioTotal;

    } catch (const std::runtime_error& e) {
        cerr << "Error al usar " << nombre << ": " << e.what() << endl;
        return 0;
    }
}

/**
 * @brief Implementación del método reducirDurabilidad
 * 
 * Disminuye la durabilidad del arma y proporciona mensajes descriptivos
 * según el estado resultante:
 * - Si se rompe completamente, muestra mensajes especiales
 * - Si está por debajo del 10%, avisa que necesita reparación urgente
 * - Si está por debajo del 25%, indica graves signos de desgaste
 * - Si cae por debajo del 50%, indica daños significativos
 * 
 * Para armas raras o superiores, muestra un mensaje adicional si se rompen.
 */
void ArmaDeCombate::reducirDurabilidad(int cantidad) {
     if (cantidad <= 0 || durabilidadActual <= 0) return;

    int durabilidadPrevia = durabilidadActual;
    durabilidadActual = max(0, durabilidadActual - cantidad);

    cout << nombre << " sufre " << cantidad << " punto(s) de desgaste. ";

    if (durabilidadActual == 0 && durabilidadPrevia > 0) {
        cout << "¡Se ha roto con un sonido estruendoso!" << endl;
        if (rareza >= Rarity::Raro) {
            cout << "Un arma tan valiosa... ¡Qué pérdida!" << endl;
        }
    }
    else if (durabilidadActual <= durabilidadMaxima * 0.1 && durabilidadActual > 0) {
        cout << "Está a punto de romperse. ¡Necesita reparación urgente!" << endl;
    }
    else if (durabilidadActual <= durabilidadMaxima * 0.25 && durabilidadActual > 0) {
        cout << "Muestra graves signos de desgaste." << endl;
    }
    else if (durabilidadActual <= durabilidadMaxima * 0.5 && durabilidadPrevia > durabilidadMaxima * 0.5) {
        cout << "Está comenzando a mostrar daños significativos." << endl;
    }
    cout << "Durabilidad: " << durabilidadActual << "/" << durabilidadMaxima << endl;
}

/**
 * @brief Implementación del método calcularBonoPorFilo
 * 
 * Calcula el bono de daño adicional basado en el nivel de filo.
 * El bono es igual al nivel de filo dividido por 10, con un límite máximo de 10.
 * Esto significa que un arma con filo 100 tendrá un bono de +10 al daño.
 * 
 * @return El bono de daño, limitado a un máximo de 10 puntos
 */
int ArmaDeCombate::calcularBonoPorFilo() const {
    return min(10, nivelFilo / 10);
}