#include "HachaDoble.hpp"

/**
 * @brief Implementación del constructor de HachaDoble
 * 
 * Inicializa un hacha doble con sus propiedades específicas como balance,
 * penalización para parada, si requiere dos manos, inscripción rúnica y
 * bonus contra armaduras.
 */
HachaDoble::HachaDoble(string n, int df, int dm, double p, Rarity r, int nf, 
                       double b, int pp, bool rdm, string ir, int bva)
    : ArmaDeCombate(n, df, dm, p, r, nf), balance(b), penalizacionParada(pp), 
      requiereDosManos(rdm), inscripcionRuna(ir), bonusVsArmadura(bva) {}

/**
 * @brief Implementación del método usar para HachaDoble
 * 
 * Utiliza la implementación básica de ataque de ArmaDeCombate.
 * 
 * @return Valor numérico que representa el daño causado
 */
int HachaDoble::usar() {
    int danoBase = ArmaDeCombate::usar();
    return danoBase;
}

/**
 * @brief Implementación del método mostrarInfo para HachaDoble
 * 
 * Muestra la información básica del arma y añade las características
 * específicas del hacha doble como balance, penalización de parada,
 * si requiere dos manos, etc.
 */
void HachaDoble::mostrarInfo() const {
    ArmaDeCombate::mostrarInfo();
    cout << "  Atributos Específicos (Hacha Doble):" << endl;
    cout << "    Balance: " << balance << endl;
    cout << "    Penalización Parada: " << penalizacionParada << endl;
    cout << "    A Dos Manos: " << (requiereDosManos ? "Sí" : "No") << endl;
    cout << "    Inscripción: " << (inscripcionRuna.empty() ? "Ninguna" : inscripcionRuna) << endl;
    cout << "    Bonus vs Armadura: " << bonusVsArmadura << endl;
}

/**
 * @brief Implementación del método hendidura
 * 
 * Realiza un ataque de hendidura diseñado para penetrar armaduras,
 * aprovechando el bonus contra armaduras del hacha doble.
 * 
 * @return Daño causado por la hendidura, o 0 si el hacha está rota
 */
int HachaDoble::hendidura() {
    if (durabilidadActual <= 0) { 
        cout << "El hacha está rota." << endl; 
        return 0; 
    }
    cout << nombre << " realiza un ataque de hendidura!" << endl;
    reducirDurabilidad(2);

    if (durabilidadActual > 0) {
        return danioFisico + calcularBonoPorFilo() + bonusVsArmadura / 2;
    } else {
        return 0;
    }
}

/**
 * @brief Implementación del método leerInscripcion
 * 
 * Devuelve la inscripción rúnica grabada en el hacha doble o 
 * un mensaje si no tiene inscripción.
 * 
 * @return String con el texto de la inscripción o mensaje por defecto
 */
string HachaDoble::leerInscripcion() const {
    if (inscripcionRuna.empty()) {
        return "(Sin inscripción)";
    }
    return "La runa dice: '" + inscripcionRuna + "'";
}

/**
 * @brief Implementación del método ataqueTorbellino
 * 
 * Realiza un poderoso ataque giratorio que causa daño aumentado
 * pero desgasta considerablemente el arma.
 * 
 * @return Daño causado por el torbellino, o 0 si el hacha está rota
 */
int HachaDoble::ataqueTorbellino() {
    if (durabilidadActual <= 0) { 
        cout << "El hacha está rota." << endl; 
        return 0; 
    }
    cout << "¡Lanzas un ataque torbellino con " << nombre << "!" << endl;
    reducirDurabilidad(6);

    if (durabilidadActual > 0) {
        return (danioFisico + calcularBonoPorFilo()) * 1.5;
    } else {
        return 0;
    }
}

/**
 * @brief Implementación de los getters para acceder a las propiedades del hacha doble
 */
bool HachaDoble::esADosManos() const { return requiereDosManos; }
double HachaDoble::getBalance() const { return balance; }
