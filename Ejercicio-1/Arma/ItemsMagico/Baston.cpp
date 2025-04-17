#include "Baston.hpp"
#include <stdexcept>

/**
 * @brief Implementación del constructor de Baston
 * 
 * Inicializa un bastón con sus propiedades específicas como tipo de madera,
 * gema incrustada, nivel de encantamiento y elemento preferido.
 */
Baston::Baston(string n, int pm, int dm, double p, Rarity r, int eam, 
               TipoMadera tm, TipoGema gi, int ne, ElementoMagico elem)
    : ObjetoMagico(n, pm, dm, p, r, eam), tipoMadera(tm), gemaIncrustada(gi), 
      nivelEncantamiento(ne), elementoPreferido(elem) {}

/**
 * @brief Implementación del método usar para Baston
 * 
 * Canaliza energía mágica del elemento preferido para realizar
 * un ataque básico. Verifica si hay suficiente energía y durabilidad.
 * 
 * @return Valor numérico que representa el daño causado, o 0 si falla
 */
int Baston::usar() {
    try {
        if (durabilidadActual <= 0) {
            throw std::runtime_error("está roto");
        }
        int costoEnergia = calcularCostoEnergia();
        if (energiaArcanaMaxima > 0 && energiaArcanaActual < costoEnergia) {
            throw std::runtime_error("energía insuficiente (" + std::to_string(energiaArcanaActual) + 
                                    "/" + std::to_string(costoEnergia) + ")");
        }

        cout << nombre << " canaliza energía mágica (" << elementoMagicoToString(elementoPreferido) << ")." << endl;

        if (energiaArcanaMaxima > 0) {
            energiaArcanaActual -= costoEnergia;
        }
        reducirDurabilidad(1);

        cout << "Energía restante: " << energiaArcanaActual << "/" << energiaArcanaMaxima << "." << endl;

        // Devuelve daño base del bastón
        return poderMagico / 2 + nivelEncantamiento;

    } catch (const std::runtime_error& e) {
        cerr << "No se pudo usar " << nombre << ": " << e.what() << "." << endl;
        return 0;
    }
}

/**
 * @brief Implementación del método mostrarInfo para Baston
 * 
 * Muestra la información básica del objeto y añade las características
 * específicas del bastón como madera, gema, encantamiento y elemento.
 */
void Baston::mostrarInfo() const {
    ObjetoMagico::mostrarInfo();
    cout << "  Atributos Específicos (Baston):" << endl;
    cout << "    Madera: " << tipoMaderaToString(tipoMadera) << endl;
    cout << "    Gema: " << tipoGemaToString(gemaIncrustada) << endl;
    cout << "    Encantamiento: Nivel " << nivelEncantamiento << endl;
    cout << "    Elemento: " << elementoMagicoToString(elementoPreferido) << endl;
}

/**
 * @brief Implementación del método lanzarRayoMagico
 * 
 * Lanza un poderoso rayo del elemento preferido, causando
 * más daño que un ataque normal pero consumiendo más energía.
 * 
 * @return Daño causado por el rayo, o 0 si no hay suficiente energía o está roto
 */
int Baston::lanzarRayoMagico() {
    try {
        if (durabilidadActual <= 0) {
            throw std::runtime_error("está roto");
        }
        int costoEnergia = 10 + nivelEncantamiento * 2 + static_cast<int>(gemaIncrustada);
        if (energiaArcanaMaxima > 0 && energiaArcanaActual < costoEnergia) {
            throw std::runtime_error("energía insuficiente para el rayo (" + 
                                    std::to_string(energiaArcanaActual) + "/" + 
                                    std::to_string(costoEnergia) + ")");
        }

        cout << nombre << " dispara un potente rayo de " << 
                elementoMagicoToString(elementoPreferido) << "!" << endl;

        if (energiaArcanaMaxima > 0) {
            energiaArcanaActual -= costoEnergia;
        }
        reducirDurabilidad(2);

        cout << "Energía restante: " << energiaArcanaActual << "." << endl;

        int danoRayo = poderMagico + nivelEncantamiento * 5;
        if (gemaIncrustada != TipoGema::Ninguna) danoRayo += 10;
        return danoRayo;

    } catch (const std::runtime_error& e) {
        cerr << "No se pudo lanzar el rayo con " << nombre << ": " << e.what() << "." << endl;
        return 0;
    }
}

/**
 * @brief Implementación del método mejorarEncantamiento
 * 
 * Aumenta el nivel de encantamiento del bastón, incrementando
 * también su poder mágico.
 * 
 * @param cantidad Cantidad en que se mejora el encantamiento
 */
void Baston::mejorarEncantamiento(int cantidad) {
    if (cantidad <= 0) return;
    nivelEncantamiento += cantidad;
    poderMagico += cantidad * 5;
    cout << nombre << " ha sido mejorado. Nivel de encantamiento: " << nivelEncantamiento << 
            ". Poder Mágico: " << poderMagico << "." << endl;
}

/**
 * @brief Implementación del método getNivelEncantamiento
 * 
 * @return Valor numérico del nivel de encantamiento
 */
int Baston::getNivelEncantamiento() const {
    return nivelEncantamiento;
}

/**
 * @brief Implementación del método tieneGema
 * 
 * @return true si el bastón tiene una gema, false si no tiene
 */
bool Baston::tieneGema() const {
    return gemaIncrustada != TipoGema::Ninguna;
}

/**
 * @brief Implementación del método cambiarGema
 * 
 * Cambia la gema incrustada en el bastón, ajustando también
 * su elemento preferido y algunas estadísticas según el tipo.
 * 
 * @param nuevaGema El tipo de gema a colocar
 */
void Baston::cambiarGema(TipoGema nuevaGema) {
    cout << "Se reemplaza la gema '" << tipoGemaToString(gemaIncrustada) << 
            "' por '" << tipoGemaToString(nuevaGema) << "' en " << nombre << "." << endl;

    // Resetear stats de la gema anterior
    if (gemaIncrustada == TipoGema::Rubi) poderMagico -= 10;
    else if (gemaIncrustada == TipoGema::Zafiro) energiaArcanaMaxima -= 20;

    // Aplicar stats de la nueva gema
    if (nuevaGema == TipoGema::Rubi) {
        elementoPreferido = ElementoMagico::Fuego;
        poderMagico += 10;
    } else if (nuevaGema == TipoGema::Zafiro) {
        elementoPreferido = ElementoMagico::Hielo;
        energiaArcanaMaxima += 20;
    } else if (nuevaGema == TipoGema::Esmeralda) {
        elementoPreferido = ElementoMagico::Naturaleza;
    } else if (nuevaGema == TipoGema::Ninguna) {
        elementoPreferido = ElementoMagico::Arcano;
    } else {
        elementoPreferido = ElementoMagico::Arcano;
    }

    gemaIncrustada = nuevaGema;
    cout << "Stats actualizados. Elemento: " << elementoMagicoToString(elementoPreferido) << 
            ", Poder: " << poderMagico << ", Energía Max: " << energiaArcanaMaxima << "." << endl;
}

/**
 * @brief Implementación del método getElementoBaston
 * 
 * @return Elemento mágico preferido del bastón
 */
ElementoMagico Baston::getElementoBaston() {
    return this->elementoPreferido;
}