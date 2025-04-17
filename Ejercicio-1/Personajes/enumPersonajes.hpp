#pragma once

#include <string>
#include <stdexcept>

using namespace std;

// ==========================================
// ENUMS DE PERSONAJES
// ==========================================

/**
 * @enum Raza
 * @brief Define las razas disponibles para los personajes.
 */
enum class Raza {Humano, Elfo, Enano, Orco, Gnomo};

/**
 * @brief Convierte una raza a su representacion en cadena.
 * @param r Raza a convertir.
 * @return String que representa la raza.
 * @throw std::out_of_range Si la raza no es valida.
 */
string razaToString(Raza r);

// ==========================================
// ATRIBUTOS PARA MAGOS
// ==========================================

/**
 * @enum EscuelaMagia
 * @brief Define las escuelas de magia a las que puede pertenecer un mago.
 */
enum class EscuelaMagia {
    Evocacion, Abjuracion, Conjuracion, Adivinacion, Encantamiento, Ilusionismo, Necromancia, Transmutacion
};

/**
 * @brief Convierte una escuela de magia a su representacion en cadena.
 * @param em Escuela de magia a convertir.
 * @return String que representa la escuela de magia.
 * @throw std::out_of_range Si la escuela de magia no es valida.
 */
string escuelaMagiaToString(EscuelaMagia em);

/**
 * @enum FuentePoder
 * @brief Define las fuentes de poder magico que puede utilizar un mago.
 */
enum class FuentePoder {
    Arcana,
    Divina,
    Natural,
    Infernal,
    Elemental,
    Mental
};

/**
 * @brief Convierte una fuente de poder a su representacion en cadena.
 * @param fp Fuente de poder a convertir.
 * @return String que representa la fuente de poder.
 * @throw std::out_of_range Si la fuente de poder no es valida.
 */
string fuentePoderToString(FuentePoder fp);

// ==========================================
// ATRIBUTOS PARA GUERREROS
// ==========================================

/**
 * @enum EstiloCombate
 * @brief Define los diferentes estilos de combate que puede adoptar un guerrero.
 */
enum class EstiloCombate {
    Defensivo,
    Agresivo,
    Equilibrado,
    Berserker,
    Tactico
};

/**
 * @brief Convierte un estilo de combate a su representacion en cadena.
 * @param ec Estilo de combate a convertir.
 * @return String que representa el estilo de combate.
 * @throw std::out_of_range Si el estilo de combate no es valido.
 */
string estiloCombateToString(EstiloCombate ec);

/**
 * @enum TipoArmadura
 * @brief Define los tipos de armadura que puede usar un guerrero.
 */
enum class TipoArmadura {
    Ligera,
    Media,
    Pesada,
    Magica,
    Ninguna
};

/**
 * @brief Convierte un tipo de armadura a su representacion en cadena.
 * @param ta Tipo de armadura a convertir.
 * @return String que representa el tipo de armadura.
 * @throw std::out_of_range Si el tipo de armadura no es valido.
 */
string tipoArmaduraToString(TipoArmadura ta);

// ==========================================
// MOVIMIENTOS DE COMBATE
// ==========================================

/**
 * @enum MovimientoCombate
 * @brief Define los movimientos basicos de combate disponibles.
 */
enum class MovimientoCombate {
    GolpeFuerte,
    GolpeRapido,
    DefensaYGolpe
};

/**
 * @brief Convierte un movimiento de combate a su representacion en cadena.
 * @param mc Movimiento de combate a convertir.
 * @return String que representa el movimiento de combate.
 * @throw std::out_of_range Si el movimiento de combate no es valido.
 */
string movimientoCombateToString(MovimientoCombate mc);
