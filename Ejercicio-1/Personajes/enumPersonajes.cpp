#include "enumPersonajes.hpp"

/**
 * @brief Implementa la conversion de Raza a texto
 * 
 * Convierte el valor de enumeracion a su representacion en cadena de texto.
 * Si se proporciona un valor invalido, lanza una excepcion.
 */
string razaToString(Raza r) {
    switch (r) {
        case Raza::Humano: return "Humano";
        case Raza::Elfo: return "Elfo";
        case Raza::Enano: return "Enano";
        case Raza::Orco: return "Orco";
        case Raza::Gnomo: return "Gnomo";
        default: throw std::out_of_range("Raza desconocida");
    }
}

/**
 * @brief Implementa la conversion de EscuelaMagia a texto
 * 
 * Convierte el valor de enumeracion a su representacion en cadena de texto.
 * Si se proporciona un valor invalido, lanza una excepcion.
 */
string escuelaMagiaToString(EscuelaMagia em) {
    switch (em) {
        case EscuelaMagia::Evocacion: return "Evocación";
        case EscuelaMagia::Abjuracion: return "Abjuración";
        case EscuelaMagia::Conjuracion: return "Conjuración";
        case EscuelaMagia::Adivinacion: return "Adivinación";
        case EscuelaMagia::Encantamiento: return "Encantamiento";
        case EscuelaMagia::Ilusionismo: return "Ilusionismo";
        case EscuelaMagia::Necromancia: return "Necromancia";
        case EscuelaMagia::Transmutacion: return "Transmutación";
        default: throw std::out_of_range("Escuela de magia desconocida");
    }
}

/**
 * @brief Implementa la conversion de FuentePoder a texto
 * 
 * Convierte el valor de enumeracion a su representacion en cadena de texto.
 * Si se proporciona un valor invalido, lanza una excepcion.
 */
string fuentePoderToString(FuentePoder fp) {
    switch (fp) {
        case FuentePoder::Arcana: return "Arcana";
        case FuentePoder::Divina: return "Divina";
        case FuentePoder::Natural: return "Natural";
        case FuentePoder::Infernal: return "Infernal";
        case FuentePoder::Elemental: return "Elemental";
        case FuentePoder::Mental: return "Mental";
        default: throw std::out_of_range("Fuente de poder desconocida");
    }
}

/**
 * @brief Implementa la conversion de EstiloCombate a texto
 * 
 * Convierte el valor de enumeracion a su representacion en cadena de texto.
 * Si se proporciona un valor invalido, lanza una excepcion.
 */
string estiloCombateToString(EstiloCombate ec) {
    switch (ec) {
        case EstiloCombate::Defensivo: return "Defensivo";
        case EstiloCombate::Agresivo: return "Agresivo";
        case EstiloCombate::Equilibrado: return "Equilibrado";
        case EstiloCombate::Berserker: return "Berserker";
        case EstiloCombate::Tactico: return "Táctico";
        default: throw std::out_of_range("Estilo de combate desconocido");
    }
}

/**
 * @brief Implementa la conversion de TipoArmadura a texto
 * 
 * Convierte el valor de enumeracion a su representacion en cadena de texto.
 * Si se proporciona un valor invalido, lanza una excepcion.
 */
string tipoArmaduraToString(TipoArmadura ta) {
    switch (ta) {
        case TipoArmadura::Ligera: return "Ligera";
        case TipoArmadura::Media: return "Media";
        case TipoArmadura::Pesada: return "Pesada";
        case TipoArmadura::Magica: return "Mágica";
        case TipoArmadura::Ninguna: return "Ninguna";
        default: throw std::out_of_range("Tipo de armadura desconocido");
    }
}

/**
 * @brief Implementa la conversion de MovimientoCombate a texto
 * 
 * Convierte el valor de enumeracion a su representacion en cadena de texto.
 * Si se proporciona un valor invalido, lanza una excepcion.
 */
string movimientoCombateToString(MovimientoCombate mc) {
    switch (mc) {
        case MovimientoCombate::GolpeFuerte: return "Golpe Fuerte";
        case MovimientoCombate::GolpeRapido: return "Golpe Rápido";
        case MovimientoCombate::DefensaYGolpe: return "Defensa y Golpe";
        default: throw std::out_of_range("Movimiento de combate desconocido");
    }
}
