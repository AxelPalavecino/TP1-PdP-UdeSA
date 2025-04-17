#include "Amuleto.hpp"
#include <cstdlib> // Para rand()

/**
 * @brief Implementación del constructor de Amuleto
 * 
 * Inicializa un amuleto con sus propiedades específicas como bonus pasivo,
 * valor del bonus, material y si requiere sintonización.
 */
Amuleto::Amuleto(string n, int pm, int dm, double p, Rarity r, int eam, 
                 string bp, int vb, MaterialAmuleto m, bool rs)
    : ObjetoMagico(n, pm, dm, p, r, eam), bonusPasivo(bp), valorBonus(vb), 
      material(m), requiereSintonizacion(rs), estaSintonizado(false) {}

/**
 * @brief Implementación del método usar para Amuleto
 * 
 * Activa el poder del amuleto, verificando primero si está sintonizado
 * en caso de que lo requiera. También comprueba si tiene suficiente
 * energía arcana y durabilidad.
 * 
 * @return Valor numérico que representa el efecto producido, o 0 si falla
 */
int Amuleto::usar() {
    if (requiereSintonizacion && !estaSintonizado) {
        cout << nombre << " no está sintonizado y no puede usarse activamente." << endl;
        return 0;
    }
    if (durabilidadActual <= 0) {
        cout << nombre << " está roto." << endl;
        return 0;
    }

    int costoEnergia = calcularCostoEnergia();
    if (energiaArcanaMaxima > 0 && energiaArcanaActual < costoEnergia) {
        cout << nombre << " no tiene suficiente energía para activarse (" << 
                energiaArcanaActual << "/" << costoEnergia << ")." << endl;
        return 0;
    }

    cout << nombre << " libera una onda de energía (" << bonusPasivo << 
            " potenciado temporalmente)!" << endl;

    if (energiaArcanaMaxima > 0) {
        energiaArcanaActual -= costoEnergia;
        cout << "Energía restante: " << energiaArcanaActual << "." << endl;
    }

    if (rand() % 5 == 0) {
        reducirDurabilidad(1);
        if (durabilidadActual == 0) {
            desintonizar();
        }
    }

    return valorBonus * 2;
}

/**
 * @brief Implementación del método mostrarInfo para Amuleto
 * 
 * Muestra la información básica del objeto y añade las características
 * específicas del amuleto como bonus pasivo, material y estado de sintonización.
 */
void Amuleto::mostrarInfo() const {
    ObjetoMagico::mostrarInfo();
    cout << "  Atributos Específicos (Amuleto):" << endl;
    cout << "    Bonus Pasivo: " << bonusPasivo << " (" << valorBonus << ")" << endl;
    cout << "    Material: " << materialAmuletoToString(material) << endl;
    cout << "    Requiere Sintonización: " << (requiereSintonizacion ? "Sí" : "No") << endl;
    if (requiereSintonizacion) {
        cout << "    Estado: " << (estaSintonizado ? "Sintonizado" : "No Sintonizado") << endl;
    }
}

/**
 * @brief Implementación de los getters para acceder a las propiedades del amuleto
 */
string Amuleto::getBonusPasivo() const { return bonusPasivo; }
int Amuleto::getValorBonus() const { return valorBonus; }
bool Amuleto::necesitaSintonizacion() const { return requiereSintonizacion; }

/**
 * @brief Implementación del método sintonizar
 * 
 * Establece una conexión mágica con el amuleto si este requiere sintonización.
 * 
 * @return true si se sintonizó correctamente o no era necesario, false si no se pudo
 */
bool Amuleto::sintonizar() {
    if (!requiereSintonizacion) {
        return true;
    }
    if (estaSintonizado) {
        return true;
    }
    if (durabilidadActual <= 0) {
        cout << "No puedes sintonizar con " << nombre << " porque está roto." << endl;
        return false;
    }

    cout << "Te concentras en " << nombre << ", sintonizándote con su poder..." << endl;
    bool exito = true;
    if (exito) {
        estaSintonizado = true;  
        cout << "¡Has sintonizado con " << nombre << "!" << endl;
        return true;
    } else {
        cout << "Fallaste al intentar sintonizar con " << nombre << "." << endl;
        return false;
    }
}

/**
 * @brief Implementación del método desintonizar
 * 
 * Rompe la conexión mágica con el amuleto.
 * 
 * @return true si se rompió la sintonización, false si no era necesario o no estaba sintonizado
 */
bool Amuleto::desintonizar() {
    if (!requiereSintonizacion) {
        return false;
    }
    if (estaSintonizado) {
        cout << "Rompes la sintonización con " << nombre << "." << endl;
        estaSintonizado = false;
        return true;
    } else {
        return false;
    }
}
