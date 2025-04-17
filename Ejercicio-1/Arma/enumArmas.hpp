 #pragma once

#include <string>
#include <stdexcept>

using namespace std;

// ==========================================
// ENUMS PARA OBJETOS Y ARMAS
// ==========================================

/**
 * @enum Rarity
 * @brief Define los niveles de rareza de los objetos y armas del juego
 */
enum class Rarity {
    Comun,
    PocoComun,
    Raro,
    Epico,
    Legendario
};

/**
 * @brief Convierte un valor de rareza a su representacion en texto
 * @param r La rareza a convertir
 * @return String con el nombre de la rareza
 */
string rarityToString(Rarity r);

// ==========================================
// ENUMS PARA BASTONES
// ==========================================

/**
 * @enum TipoMadera
 * @brief Define los tipos de madera disponibles para crear bastones
 */
enum class TipoMadera { Roble, Fresno, Tejo, Sauce, Ebano};

/**
 * @brief Convierte un tipo de madera a su representacion en texto
 * @param tm El tipo de madera a convertir
 * @return String con el nombre del tipo de madera
 */
string tipoMaderaToString(TipoMadera tm);

/**
 * @enum TipoGema
 * @brief Define los tipos de gemas que pueden incrustarse en bastones
 */
enum class TipoGema { Ninguna, Rubi, Zafiro, Esmeralda, Diamante, Amatista };

/**
 * @brief Convierte un tipo de gema a su representacion en texto
 * @param tg El tipo de gema a convertir
 * @return String con el nombre del tipo de gema
 */
string tipoGemaToString(TipoGema tg);

/**
 * @enum ElementoMagico
 * @brief Define los elementos magicos que pueden canalizar los bastones
 */
enum class ElementoMagico { Arcano, Fuego, Hielo, Rayo, Naturaleza, Sombra };

/**
 * @brief Convierte un elemento magico a su representacion en texto
 * @param em El elemento magico a convertir
 * @return String con el nombre del elemento magico
 */
string elementoMagicoToString(ElementoMagico em);

// ==========================================
// ENUMS PARA LIBROS DE HECHIZOS
// ==========================================

/**
 * @enum IdiomaLibro
 * @brief Define los idiomas en los que pueden estar escritos los libros de hechizos
 */
enum class IdiomaLibro { Comun, Elfico, Enano, Draconico, Antiguo };

/**
 * @brief Convierte un idioma de libro a su representacion en texto
 * @param il El idioma a convertir
 * @return String con el nombre del idioma
 */
string idiomaLibroToString(IdiomaLibro il);

/**
 * @enum MaterialCubierta
 * @brief Define los materiales para las cubiertas de los libros de hechizos
 */
enum class MaterialCubierta { Cuero, PielDragon, MaderaRunica, MetalEstelar };

/**
 * @brief Convierte un material de cubierta a su representacion en texto
 * @param mc El material de cubierta a convertir
 * @return String con el nombre del material de cubierta
 */
string materialCubiertaToString(MaterialCubierta mc);

// ==========================================
// ENUMS PARA POCIONES
// ==========================================

/**
 * @enum EfectoPocion
 * @brief Define los efectos que pueden tener las pociones
 */
enum class EfectoPocion { Curacion, Mana, Fuerza, Agilidad, Invisibilidad, Veneno, Antidoto };

/**
 * @brief Convierte un efecto de pocion a su representacion en texto
 * @param ep El efecto de pocion a convertir
 * @return String con el nombre del efecto
 */
string efectoPocionToString(EfectoPocion ep);

/**
 * @enum ColorPocion
 * @brief Define los colores que pueden tener las pociones
 */
enum class ColorPocion { Rojo, Azul, Verde, Amarillo, Transparente, Negro, Morado };

/**
 * @brief Convierte un color de pocion a su representacion en texto
 * @param cp El color de pocion a convertir
 * @return String con el nombre del color
 */
string colorPocionToString(ColorPocion cp);

// ==========================================
// ENUMS PARA AMULETOS
// ==========================================

/**
 * @enum MaterialAmuleto
 * @brief Define los materiales con los que pueden crearse amuletos
 */
enum class MaterialAmuleto { Oro, Plata, Hueso, Obsidiana, Cristal };

/**
 * @brief Convierte un material de amuleto a su representacion en texto
 * @param ma El material de amuleto a convertir
 * @return String con el nombre del material
 */
string materialAmuletoToString(MaterialAmuleto ma);

// ==========================================
// ENUMS PARA ARMAS DE COMBATE
// ==========================================

/**
 * @enum TipoMango
 * @brief Define los tipos de mango para hachas simples
 */
enum class TipoMango { Madera, Hueso, Metal, Reforzado };

/**
 * @brief Convierte un tipo de mango a su representacion en texto
 * @param tm El tipo de mango a convertir
 * @return String con el nombre del tipo de mango
 */
string tipoMangoToString(TipoMango tm);

/**
 * @enum TipoHojaEspada
 * @brief Define los tipos de hoja para espadas
 */
enum class TipoHojaEspada { Recta, Curva, Estoque, Mandoble, Cimitarra };

/**
 * @brief Convierte un tipo de hoja de espada a su representacion en texto
 * @param th El tipo de hoja a convertir
 * @return String con el nombre del tipo de hoja
 */
string tipoHojaEspadaToString(TipoHojaEspada th);

/**
 * @enum MaterialGuarda
 * @brief Define los materiales para guardas de espadas
 */
enum class MaterialGuarda { Acero, Bronce, Hierro, PlataDecorativa };

/**
 * @brief Convierte un material de guarda a su representacion en texto
 * @param mg El material de guarda a convertir
 * @return String con el nombre del material
 */
string materialGuardaToString(MaterialGuarda mg);

/**
 * @enum EstiloEsgrima
 * @brief Define los estilos de combate para espadas
 */
enum class EstiloEsgrima { UnaMano, ManoYMedia, DosManos, DobleEmpunadura };

/**
 * @brief Convierte un estilo de esgrima a su representacion en texto
 * @param ee El estilo de esgrima a convertir
 * @return String con el nombre del estilo
 */
string estiloEsgrimaToString(EstiloEsgrima ee);

/**
 * @enum MaterialPuntaLanza
 * @brief Define los materiales para las puntas de lanzas
 */
enum class MaterialPuntaLanza { Acero, Obsidiana, Bronce, HuesoAfilado };

/**
 * @brief Convierte un material de punta de lanza a su representacion en texto
 * @param mp El material de punta a convertir
 * @return String con el nombre del material
 */
string materialPuntaLanzaToString(MaterialPuntaLanza mp);

/**
 * @enum OrigenGarrote
 * @brief Define los posibles origenes para fabricar garrotes
 */
enum class OrigenGarrote { RamaArbol, PataMesa, HuesoGrande, Improvisado };

/**
 * @brief Convierte un origen de garrote a su representacion en texto
 * @param og El origen de garrote a convertir
 * @return String con la descripcion del origen
 */
string origenGarroteToString(OrigenGarrote og);