#include "Garrote.hpp"

/**
 * @brief Implementación del constructor de Garrote
 * 
 * Inicializa un garrote con sus propiedades específicas como tipo de madera,
 * si tiene clavos, circunferencia de la cabeza, bonus de aturdimiento y origen.
 */
Garrote::Garrote(string n, int df, int dm, double p, Rarity r, int nf, 
                 TipoMadera tm, bool tc, double cc, int ba, OrigenGarrote org)
    : ArmaDeCombate(n, df, dm, p, r, nf), tipoMadera(tm), tieneClavos(tc), 
      circunferenciaCabeza(cc), bonusAturdimiento(ba), origen(org) {}

/**
 * @brief Implementación del método usar para Garrote
 * 
 * Utiliza la implementación básica de ataque de ArmaDeCombate.
 * El daño ya se ajusta en métodos como ponerQuitarClavos.
 * 
 * @return Valor numérico que representa el daño causado
 */
int Garrote::usar() {
    int danoBase = ArmaDeCombate::usar();
    if (tieneClavos) {
        danoBase += 5;
    }
    if (durabilidadActual > 0) {
        danoBase += calcularBonoPorFilo();
    } else {
        cout << "El garrote está roto." << endl;
        return 0;
    }

    if (bonusAturdimiento > 0) {
        cout << nombre << " causa un aturdimiento adicional!" << endl;
        danoBase += bonusAturdimiento;
    }
    reducirDurabilidad(1);
    return danoBase;
}

/**
 * @brief Implementación del método mostrarInfo para Garrote
 * 
 * Muestra la información básica del arma y añade las características
 * específicas del garrote como tipo de madera, si está claveteado,
 * circunferencia de la cabeza, etc.
 */
void Garrote::mostrarInfo() const {
    ArmaDeCombate::mostrarInfo();
    cout << "  Atributos Específicos (Garrote):" << endl;
    cout << "    Madera: " << tipoMaderaToString(tipoMadera) << endl;
    cout << "    Claveteado: " << (tieneClavos ? "Sí" : "No") << endl;
    cout << "    Circunferencia Cabeza: " << circunferenciaCabeza << "cm" << endl;
    cout << "    Bonus Aturdimiento: " << bonusAturdimiento << endl;
    cout << "    Origen: " << origenGarroteToString(origen) << endl;
}

/**
 * @brief Implementación del método aplastar
 * 
 * Realiza un ataque aplastante que causa daño aumentado y tiene
 * potencial para aturdir al objetivo basado en bonusAturdimiento.
 * 
 * @return Daño causado por el aplastamiento, o 0 si el garrote está roto
 */
int Garrote::aplastar() {
    if (durabilidadActual <= 0) { 
        cout << "El garrote está roto." << endl; 
        return 0; 
    }
    cout << nombre << " intenta aplastar al objetivo!" << endl;
    reducirDurabilidad(2);

    if (durabilidadActual > 0) {
        // Daño aumentado en un 20%
        int danoAplastar = (danioFisico + calcularBonoPorFilo()) * 1.2;
        // En un sistema completo, aquí podríamos calcular la probabilidad
        // de aturdir al objetivo basado en bonusAturdimiento
        return danoAplastar;
    } else {
        return 0;
    }
}

/**
 * @brief Implementación del método estaClaveteado
 * 
 * @return true si el garrote tiene clavos, false en caso contrario
 */
bool Garrote::estaClaveteado() const { 
    return tieneClavos; 
}

/**
 * @brief Implementación del método ponerQuitarClavos
 * 
 * Permite colocar o quitar clavos del garrote, lo que afecta al daño
 * y nivel de filo del arma.
 * 
 * @param poner true para colocar clavos, false para quitarlos
 */
void Garrote::ponerQuitarClavos(bool poner) {
    if (poner && !tieneClavos) {
        tieneClavos = true;
        danioFisico += 5; // Clavos añaden daño
        nivelFilo += 2; // Representa la capacidad de desgarrar
        cout << "Se han añadido clavos a " << nombre << ". Daño y filo aumentados." << endl;
    } else if (!poner && tieneClavos) {
        tieneClavos = false; 
        danioFisico -= 5;
        nivelFilo -= 2;
        cout << "Se han quitado los clavos de " << nombre << ". Daño y filo reducidos." << endl;
    } else if (poner && tieneClavos) {
        cout << nombre << " ya tiene clavos." << endl;
    } else {
        cout << nombre << " no tenía clavos para quitar." << endl;
    }
    
    // Asegurar valores mínimos
    if (danioFisico < 1) danioFisico = 1;
    if (nivelFilo < 0) nivelFilo = 0;
}

/**
 * @brief Implementación del método getBonusAturdimiento
 * 
 * @return Valor numérico que representa el bonus de aturdimiento del garrote
 */
int Garrote::getBonusAturdimiento() const { 
    return bonusAturdimiento; 
}

/**
 * @brief Implementación del método reforzarMadera
 * 
 * Refuerza la madera del garrote con resina y bandas, aumentando
 * su durabilidad máxima y reparando parcialmente el arma.
 */
void Garrote::reforzarMadera() {
    cout << "Refuerzas la madera de " << nombre << " con resina y bandas." << endl;
    int aumentoDur = durabilidadMaxima / 5; // Aumenta un 20% la durabilidad max
    durabilidadMaxima += aumentoDur;
    // Reparar un poco al reforzar
    reparar(aumentoDur / 2);
    cout << "Durabilidad máxima aumentada a " << durabilidadMaxima << "." << endl;
}
