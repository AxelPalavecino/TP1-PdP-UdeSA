#include "Pocion.hpp"
#include <algorithm>

/**
 * @brief Implementación del constructor de Pocion
 * 
 * Inicializa una poción con sus propiedades específicas como efecto,
 * potencia, dosis, color y si es permanente. También actualiza la
 * durabilidad para que coincida con las dosis restantes.
 */
Pocion::Pocion(string n, int pm, int dm, double p, Rarity r, int eam, 
               EfectoPocion ef, int pe, int dr, ColorPocion cl, bool perm)
    : ObjetoMagico(n, pm, dm, p, r, eam), efecto(ef), potenciaEfecto(pe), 
      dosisRestantes(dr), colorLiquido(cl), esPermanente(perm) {
    
    durabilidadMaxima = dm;
    durabilidadActual = dosisRestantes;
    if (durabilidadActual > durabilidadMaxima) durabilidadActual = durabilidadMaxima;
    if (durabilidadActual < 0) durabilidadActual = 0;
    dosisRestantes = durabilidadActual;
}

/**
 * @brief Implementación del método usar para Pocion
 * 
 * Consume una dosis de la poción para aplicar su efecto.
 * Verifica si quedan dosis disponibles antes de usar.
 * 
 * @return Valor numérico que representa el efecto aplicado, o 0 si está vacía
 */
int Pocion::usar() {
    if (estaVacia()) {
        cout << nombre << " está vacía." << endl;
        return 0;
    }

    cout << "Bebes una dosis de " << nombre << ". ";
    int efectoValor = aplicarEfecto();

    dosisRestantes--;
    durabilidadActual = dosisRestantes;

    cout << "Dosis restantes: " << dosisRestantes << "/" << durabilidadMaxima << "." << endl;

    if (estaVacia()) {
        cout << "La poción '" << nombre << "' se ha terminado." << endl;
    }

    return efectoValor;
}

/**
 * @brief Implementación del método mostrarInfo para Pocion
 * 
 * Muestra la información básica del objeto y añade las características
 * específicas de la poción como efecto, potencia, dosis restantes, etc.
 */
void Pocion::mostrarInfo() const {
    ObjetoMagico::mostrarInfo();
    cout << "  Atributos Específicos (Pocion):" << endl;
    cout << "    Efecto: " << efectoPocionToString(efecto) << (esPermanente ? " [Permanente]" : " [Temporal]") << endl;
    cout << "    Potencia: " << potenciaEfecto << endl;
    cout << "    Dosis Restantes: " << dosisRestantes << "/" << durabilidadMaxima << endl;
    cout << "    Color: " << colorPocionToString(colorLiquido) << endl;
}

/**
 * @brief Implementación de los getters para acceder a las propiedades de la poción
 */
EfectoPocion Pocion::getEfecto() const { return efecto; }
int Pocion::getPotenciaEfecto() const { return potenciaEfecto; }
int Pocion::getDosisRestantes() const { return dosisRestantes; }
bool Pocion::estaVacia() const { return dosisRestantes <= 0; }

/**
 * @brief Implementación del método aplicarEfecto
 * 
 * Aplica el efecto específico de la poción según su tipo,
 * mostrando información sobre el efecto producido.
 * 
 * @return Valor numérico que representa la magnitud del efecto
 */
int Pocion::aplicarEfecto() {
    cout << "Sientes el efecto de " << efectoPocionToString(efecto) << ". ";
    switch (efecto) {
        case EfectoPocion::Curacion:
            cout << "(+" << potenciaEfecto << " Salud)" << endl;
            return potenciaEfecto;
        case EfectoPocion::Mana:
            cout << "(+" << potenciaEfecto << " Maná)" << endl;
            return potenciaEfecto;
        case EfectoPocion::Fuerza:
            cout << "(+" << potenciaEfecto << " Fuerza Temporal)" << endl;
            return potenciaEfecto;
        case EfectoPocion::Veneno:
            cout << "(-" << potenciaEfecto << " Salud)" << endl;
            return -potenciaEfecto;
        case EfectoPocion::Invisibilidad:
            cout << "(Invisibilidad Temporal)" << endl;
            return 1;
        default:
            cout << "(Efecto desconocido)" << endl;
            return 0;
    }
}

/**
 * @brief Implementación del método combinar
 * 
 * Permite combinar esta poción con otra del mismo tipo.
 * Si son compatibles, se suman sus potencias y dosis.
 * Si no son compatibles, la poción actual queda inutilizable.
 * 
 * @param otraPocion La poción con la que se intenta combinar
 */
void Pocion::combinar(const Pocion& otraPocion) {
    cout << "Intentas combinar " << nombre << " con " << otraPocion.getNombre() << "." << endl;
    if (efecto == otraPocion.getEfecto() && !esPermanente && !otraPocion.esPermanente) {
        potenciaEfecto += otraPocion.getPotenciaEfecto() / 2;
        int dosisMaxCombinadas = durabilidadMaxima + otraPocion.durabilidadMaxima;
        int dosisActualesCombinadas = dosisRestantes + otraPocion.dosisRestantes;
        durabilidadMaxima = dosisMaxCombinadas;
        dosisRestantes = min(dosisMaxCombinadas, dosisActualesCombinadas);
        durabilidadActual = dosisRestantes;
        cout << "¡Combinación exitosa! Nueva potencia: " << potenciaEfecto << 
                ", Dosis: " << dosisRestantes << "/" << durabilidadMaxima << endl;
    } else {
        cout << "¡La combinación resulta inestable y explota!" << endl;
        dosisRestantes = 0;
        durabilidadActual = 0;
        potenciaEfecto = 0;
        efecto = EfectoPocion::Curacion;
    }
}

/**
 * @brief Implementación del método calcularCostoEnergia
 * 
 * Calcula el costo de energía arcana basado en el poder mágico
 * y la rareza de la poción.
 * 
 * @return Valor numérico que representa el costo de energía
 */
int Pocion::calcularCostoEnergia() const {
    int costoBase = 1 + (poderMagico / 20);
    costoBase += static_cast<int>(rareza);
    return max(1, costoBase);
}
