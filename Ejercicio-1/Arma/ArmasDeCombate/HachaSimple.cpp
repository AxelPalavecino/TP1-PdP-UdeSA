#include "HachaSimple.hpp"
#include <cstdlib> // Para rand()

/**
 * @brief Implementación del constructor de HachaSimple
 * 
 * Inicializa un hacha simple con sus propiedades específicas como tipo de mango,
 * longitud, si es arrojadiza, bonus contra madera y marca del herrero.
 */
HachaSimple::HachaSimple(string n, int df, int dm, double p, Rarity r, int nf, 
                         TipoMango tm, double lm, bool ea, int bvm, string mh)
    : ArmaDeCombate(n, df, dm, p, r, nf), tipoMango(tm), longitudMango(lm), 
      esArrojadiza(ea), bonusVsMadera(bvm), marcaHerrero(mh) {}

/**
 * @brief Implementación del método usar para HachaSimple
 * 
 * Utiliza la implementación básica de ataque de ArmaDeCombate.
 * 
 * @return Valor numérico que representa el daño causado
 */
int HachaSimple::usar() {
    return ArmaDeCombate::usar();
}

/**
 * @brief Implementación del método mostrarInfo para HachaSimple
 * 
 * Muestra la información básica del arma y añade las características
 * específicas del hacha simple como mango, si es arrojadiza, etc.
 */
void HachaSimple::mostrarInfo() const {
    ArmaDeCombate::mostrarInfo();
    cout << "  Atributos Específicos (Hacha Simple):" << endl;
    cout << "    Mango: " << tipoMangoToString(tipoMango) << " (" << longitudMango << "m)" << endl;
    cout << "    Arrojadiza: " << (esArrojadiza ? "Sí" : "No") << endl;
    cout << "    Bonus vs Madera: " << bonusVsMadera << endl;
    cout << "    Marca Herrero: " << marcaHerrero << endl;
}

/**
 * @brief Implementación del método talar
 * 
 * Usa el hacha para talar madera, aprovechando su bonus específico contra madera.
 * Este método desgasta más el hacha que un ataque normal.
 * 
 * @return Daño efectivo para talar madera, o 0 si el hacha está rota
 */
int HachaSimple::talar() {
    if (durabilidadActual <= 0) { 
        cout << "El hacha está rota." << endl; 
        return 0; 
    }
    cout << "Intentas talar con " << nombre << "." << endl;
    reducirDurabilidad(3);

    if (durabilidadActual > 0) {
        return danioFisico + bonusVsMadera + calcularBonoPorFilo();
    } else {
        return 0;
    }
}

/**
 * @brief Implementación del método lanzar
 * 
 * Permite lanzar el hacha como un proyectil si tiene la propiedad de ser arrojadiza.
 * El lanzamiento desgasta considerablemente el hacha.
 * 
 * @return Daño causado por el lanzamiento, o 0 si el hacha no es arrojadiza o está rota
 */
int HachaSimple::lanzar() {
    if (!esArrojadiza) {
        cout << nombre << " no es un hacha arrojadiza." << endl;
        return 0;
    }
    if (durabilidadActual <= 0) { 
        cout << "El hacha está rota y no se puede lanzar." << endl; 
        return 0; 
    }

    cout << "Lanzas " << nombre << "!" << endl;

    int desgasteLanzar = 5 + (rand() % 6);
    reducirDurabilidad(desgasteLanzar);

    if (durabilidadActual > 0) {
        return (danioFisico + calcularBonoPorFilo()) / 2;
    } else {
        return 0;
    }
}

/**
 * @brief Implementación de los getters para acceder a las propiedades del hacha
 */
double HachaSimple::getLongitudMango() const { return longitudMango; }
bool HachaSimple::puedeArrojarse() const { return esArrojadiza; }
string HachaSimple::getMarcaHerrero() const { return marcaHerrero; }
