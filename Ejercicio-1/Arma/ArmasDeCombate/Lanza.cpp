#include "Lanza.hpp"

/**
 * @brief Implementación del constructor de Lanza
 * 
 * Inicializa una lanza con sus propiedades específicas como longitud del asta,
 * material de la punta, si tiene bandera, alcance y si es desmontable.
 */
Lanza::Lanza(string n, int df, int dm, double p, Rarity r, int nf, 
             double la, MaterialPuntaLanza mp, bool tb, int al, bool ed)
    : ArmaDeCombate(n, df, dm, p, r, nf), longitudAsta(la), materialPunta(mp), 
      tieneBandera(tb), alcance(al), esDesmontable(ed) {}

/**
 * @brief Implementación del método usar para Lanza
 * 
 * Modifica el comportamiento básico de ataque para aprovechar si la lanza
 * está preparada contra carga, aumentando significativamente el daño en ese caso.
 * 
 * @return Valor numérico que representa el daño causado
 */
int Lanza::usar() {
    int danoBase = 0;
    if (preparadaContraCarga) {
        cout << nombre << " estaba preparada y golpea con fuerza extra!" << endl;
        danoBase = (danioFisico + calcularBonoPorFilo()) * 2 + alcance * 2;
        preparadaContraCarga = false;
        reducirDurabilidad(3);
    } else {
        danoBase = ArmaDeCombate::usar();
        if (danoBase > 0) {
            danoBase += alcance / 2;
        }
    }
    return danoBase;
}

/**
 * @brief Implementación del método mostrarInfo para Lanza
 * 
 * Muestra la información básica del arma y añade las características
 * específicas de la lanza como longitud del asta, material de la punta,
 * si tiene bandera, alcance, etc.
 */
void Lanza::mostrarInfo() const {
    ArmaDeCombate::mostrarInfo();
    cout << "  Atributos Específicos (Lanza):" << endl;
    cout << "    Longitud Asta: " << longitudAsta << "m" << endl;
    cout << "    Punta: " << materialPuntaLanzaToString(materialPunta) << endl;
    cout << "    Bandera: " << (tieneBandera ? "Sí" : "No") << endl;
    cout << "    Alcance: " << alcance << endl;
    cout << "    Desmontable: " << (esDesmontable ? "Sí" : "No") << endl;
}

/**
 * @brief Implementación del método barrer
 * 
 * Realiza un ataque de barrido que afecta a varios objetivos pero
 * causa menos daño que un ataque normal.
 * 
 * @return Daño causado por el barrido, o 0 si la lanza está rota
 */
int Lanza::barrer() {
    if (durabilidadActual <= 0) { 
        cout << "La lanza está rota." << endl; 
        return 0; 
    }
    cout << nombre << " realiza un barrido amplio." << endl;
    reducirDurabilidad(2);

    if (durabilidadActual > 0) {
        return (danioFisico + calcularBonoPorFilo()) / 2;
    } else {
        return 0;
    }
}

/**
 * @brief Implementación del método prepararContraCarga
 * 
 * Prepara la lanza para recibir una carga enemiga, lo que aumenta
 * significativamente el daño en el próximo ataque.
 * 
 * @return true si la lanza se preparó correctamente, false si no se pudo (rota o ya preparada)
 */
bool Lanza::prepararContraCarga() {
    if (durabilidadActual <= 0) { 
        cout << "La lanza está rota." << endl; 
        return false; 
    }
    if (preparadaContraCarga) {
        cout << nombre << " ya está preparada." << endl;
        return false;
    }
    cout << "Preparas " << nombre << " para recibir una carga. ¡El daño contra enemigos que cargan aumenta!" << endl;
    preparadaContraCarga = true;
    return true;
}

/**
 * @brief Implementación del método getAlcance
 * 
 * @return Valor numérico que representa el alcance de la lanza
 */
int Lanza::getAlcance() const { 
    return alcance; 
}

/**
 * @brief Implementación del método ponerQuitarBandera
 * 
 * Permite colocar o quitar una bandera de la lanza para usos
 * ceremoniales o de señalización.
 * 
 * @param poner true para colocar una bandera, false para quitarla
 */
void Lanza::ponerQuitarBandera(bool poner) {
    if (poner && !tieneBandera) {
        tieneBandera = true;
        cout << "Se ha colocado una bandera en " << nombre << "." << endl;
    } else if (!poner && tieneBandera) {
        tieneBandera = false;
        cout << "Se ha quitado la bandera de " << nombre << "." << endl;
    } else if (poner && tieneBandera) {
        cout << nombre << " ya tiene una bandera." << endl;
    } else {
        cout << nombre << " no tenía bandera para quitar." << endl;
    }
}

/**
 * @brief Implementación del método desmontarPunta
 * 
 * Permite desmontar la punta de la lanza si esta tiene esa capacidad,
 * lo que podría ser útil para transporte, reparación o reemplazo.
 */
void Lanza::desmontarPunta() {
    if (!esDesmontable) {
        cout << nombre << " no es desmontable." << endl;
        return;
    }
    if (durabilidadActual <= 0) { 
        cout << "La lanza está rota." << endl; 
        return; 
    }

    cout << "Desmontas la punta de " << nombre << ". Ahora tienes el asta y la punta por separado." << endl;
    // En una implementación completa, esto podría generar dos objetos nuevos
}
