#include "Espada.hpp"
#include <cstdlib> // Para rand()

/**
 * @brief Implementación del constructor de Espada
 * 
 * Inicializa una espada con sus propiedades específicas como tipo de hoja,
 * material de la guarda, longitud de la hoja, bonus de estocada y estilo de esgrima.
 */
Espada::Espada(string n, int df, int dm, double p, Rarity r, int nf, 
               TipoHojaEspada th, MaterialGuarda mg, double lh, int be, EstiloEsgrima ee)
    : ArmaDeCombate(n, df, dm, p, r, nf), tipoHoja(th), materialGuarda(mg), 
      longitudHoja(lh), bonusEstocada(be), estiloEsgrima(ee) {}

/**
 * @brief Implementación del método usar para Espada
 * 
 * Utiliza la implementación básica de ataque de ArmaDeCombate.
 * 
 * @return Valor numérico que representa el daño causado
 */
int Espada::usar() {
    return ArmaDeCombate::usar();
}

/**
 * @brief Implementación del método mostrarInfo para Espada
 * 
 * Muestra la información básica del arma y añade las características
 * específicas de la espada como tipo de hoja, material de la guarda,
 * longitud de la hoja, etc.
 */
void Espada::mostrarInfo() const {
    ArmaDeCombate::mostrarInfo();
    cout << "  Atributos Específicos (Espada):" << endl;
    cout << "    Tipo Hoja: " << tipoHojaEspadaToString(tipoHoja) << endl;
    cout << "    Guarda: " << materialGuardaToString(materialGuarda) << endl;
    cout << "    Longitud Hoja: " << longitudHoja << "m" << endl;
    cout << "    Bonus Estocada: " << bonusEstocada << endl;
    cout << "    Estilo: " << estiloEsgrimaToString(estiloEsgrima) << endl;
}

/**
 * @brief Implementación del método estocar
 * 
 * Realiza un ataque de estocada que aprovecha el bonus específico
 * para este tipo de ataque.
 * 
 * @return Daño causado por la estocada, o 0 si la espada está rota
 */
int Espada::estocar() {
    if (durabilidadActual <= 0) { 
        cout << "La espada está rota." << endl; 
        return 0; 
    }
    cout << nombre << " realiza una estocada precisa!" << 
           (bonusEstocada > 0 ? " (Bonus: +" + to_string(bonusEstocada) + ")" : "") << endl;
    reducirDurabilidad(1);

    if (durabilidadActual > 0) {
        return danioFisico + calcularBonoPorFilo() + bonusEstocada;
    } else {
        return 0;
    }
}

/**
 * @brief Implementación del método parar
 * 
 * Intenta bloquear un ataque entrante utilizando la espada.
 * La probabilidad de éxito depende del nivel de filo.
 * 
 * @return true si la parada tuvo éxito, false en caso contrario
 */
bool Espada::parar() {
    if (durabilidadActual <= 0) { 
        cout << "La espada está rota y no puedes parar." << endl; 
        return false; 
    }
    cout << "Intentas parar un ataque con " << nombre << "." << endl;

    bool exitoParada = (rand() % 100) < (50 + nivelFilo / 2);

    if (exitoParada) {
        if (rand() % 3 == 0) {
           reducirDurabilidad(1);
           if (durabilidadActual == 0) {
               cout << "¡" << nombre << " se ha roto al parar!" << endl;
               return false;
           }
        } else {
           cout << "Parada exitosa sin desgaste aparente." << endl;
        }
        return true;
    } else {
        cout << "¡Fallaste la parada!" << endl;
        reducirDurabilidad(1);
        return false;
    }
}

/**
 * @brief Implementación de los getters para acceder a las propiedades de la espada
 */
TipoHojaEspada Espada::getTipoHoja() const { return tipoHoja; }
double Espada::getLongitudHoja() const { return longitudHoja; }

/**
 * @brief Implementación del método pulirHoja
 * 
 * Mejora ligeramente el nivel de filo de la espada mediante pulido.
 * Tiene menos efecto que afilar pero no desgasta el arma.
 */
void Espada::pulirHoja() {
    cout << "Pules la hoja de " << nombre << "." << endl;
    if (nivelFilo < 100) {
        nivelFilo = min(100, nivelFilo + 5);
        cout << "El filo mejora ligeramente. Nivel de filo: " << nivelFilo << endl;
    } else {
        cout << "La hoja ya está perfectamente afilada." << endl;
    }
}
