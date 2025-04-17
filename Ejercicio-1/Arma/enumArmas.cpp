#include "enumArmas.hpp"
#include <string>
#include <stdexcept>

using namespace std;

string rarityToString(Rarity r) {
    switch (r) {
        case Rarity::Comun: return "Común";
        case Rarity::PocoComun: return "Poco Común";
        case Rarity::Raro: return "Raro";
        case Rarity::Epico: return "Épico";
        case Rarity::Legendario: return "Legendario";
        default: throw std::out_of_range("Rareza desconocida");
    }
}

string tipoMaderaToString(TipoMadera tm) {
    switch (tm) {
        case TipoMadera::Roble: return "Roble";
        case TipoMadera::Fresno: return "Fresno";
        case TipoMadera::Tejo: return "Tejo";
        case TipoMadera::Sauce: return "Sauce";
        case TipoMadera::Ebano: return "Ébano";
        default: throw std::out_of_range("Tipo de madera desconocido");
    }
}

string tipoGemaToString(TipoGema tg) {
    switch (tg) {
        case TipoGema::Ninguna: return "Ninguna";
        case TipoGema::Rubi: return "Rubí";
        case TipoGema::Zafiro: return "Zafiro";
        case TipoGema::Esmeralda: return "Esmeralda";
        case TipoGema::Diamante: return "Diamante";
        case TipoGema::Amatista: return "Amatista";
        default: throw std::out_of_range("Tipo de gema desconocido");
    }
}

string elementoMagicoToString(ElementoMagico em) {
    switch (em) {
        case ElementoMagico::Arcano: return "Arcano";
        case ElementoMagico::Fuego: return "Fuego";
        case ElementoMagico::Hielo: return "Hielo";
        case ElementoMagico::Rayo: return "Rayo";
        case ElementoMagico::Naturaleza: return "Naturaleza";
        case ElementoMagico::Sombra: return "Sombra";
        default: throw std::out_of_range("Elemento mágico desconocido");
    }
}
string idiomaLibroToString(IdiomaLibro il) {
    switch (il) {
        case IdiomaLibro::Comun: return "Común";
        case IdiomaLibro::Elfico: return "Élfico";
        case IdiomaLibro::Enano: return "Enano";
        case IdiomaLibro::Draconico: return "Dracónico";
        case IdiomaLibro::Antiguo: return "Antiguo";
        default: throw std::out_of_range("Idioma desconocido");
    }
}

string materialCubiertaToString(MaterialCubierta mc) {
    switch (mc) {
        case MaterialCubierta::Cuero: return "Cuero";
        case MaterialCubierta::PielDragon: return "Piel de Dragón";
        case MaterialCubierta::MaderaRunica: return "Madera Rúnica";
        case MaterialCubierta::MetalEstelar: return "Metal Estelar";
        default: throw std::out_of_range("Material de cubierta desconocido");
    }
}

string efectoPocionToString(EfectoPocion ep) {
    switch (ep) {
        case EfectoPocion::Curacion: return "Curación";
        case EfectoPocion::Mana: return "Restauración de Maná";
        case EfectoPocion::Fuerza: return "Fuerza Temporal";
        case EfectoPocion::Veneno: return "Veneno";
        case EfectoPocion::Invisibilidad: return "Invisibilidad";
        case EfectoPocion::Antidoto: return "Antídoto";
        case EfectoPocion::Agilidad: return "Aumento de Agilidad";
        default: throw std::out_of_range("Efecto de poción desconocido");
    }
}
string colorPocionToString(ColorPocion cp) {
    switch (cp) {
        case ColorPocion::Rojo: return "Rojo";
        case ColorPocion::Azul: return "Azul";
        case ColorPocion::Verde: return "Verde";
        case ColorPocion::Amarillo: return "Amarillo";
        case ColorPocion::Transparente: return "Transparente";
        case ColorPocion::Negro: return "Negro";
        case ColorPocion::Morado: return "Morado";
        default: throw std::out_of_range("Color de poción desconocido");
    }
}

string materialAmuletoToString(MaterialAmuleto ma) {
    switch (ma) {
        case MaterialAmuleto::Oro: return "Oro";
        case MaterialAmuleto::Plata: return "Plata";
        case MaterialAmuleto::Hueso: return "Hueso";
        case MaterialAmuleto::Obsidiana: return "Obsidiana";
        case MaterialAmuleto::Cristal: return "Cristal";
        default: throw std::out_of_range("Material de amuleto desconocido");
    }
}

string tipoMangoToString(TipoMango tm) {
    switch (tm) {
        case TipoMango::Madera: return "Madera";
        case TipoMango::Hueso: return "Hueso";
        case TipoMango::Metal: return "Metal";
        case TipoMango::Reforzado: return "Reforzado";
        default: throw std::out_of_range("Tipo de mango desconocido");
    }
}

string tipoHojaEspadaToString(TipoHojaEspada th) {
    switch (th) {
        case TipoHojaEspada::Recta: return "Recta";
        case TipoHojaEspada::Curva: return "Curva";
        case TipoHojaEspada::Estoque: return "Estoque";
        case TipoHojaEspada::Mandoble: return "Mandoble";
        case TipoHojaEspada::Cimitarra: return "Cimitarra";
        default: throw std::out_of_range("Tipo de hoja desconocido");
    }
}
string materialGuardaToString(MaterialGuarda mg) {
    switch (mg) {
        case MaterialGuarda::Acero: return "Acero";
        case MaterialGuarda::Bronce: return "Bronce";
        case MaterialGuarda::Hierro: return "Hierro";
        case MaterialGuarda::PlataDecorativa: return "Plata Decorativa";
        default: throw std::out_of_range("Material de guarda desconocido");
    }
}

string estiloEsgrimaToString(EstiloEsgrima ee) {
    switch (ee) {
        case EstiloEsgrima::UnaMano: return "Una Mano";
        case EstiloEsgrima::ManoYMedia: return "Mano y Media";
        case EstiloEsgrima::DosManos: return "Dos Manos";
        case EstiloEsgrima::DobleEmpunadura: return "Doble Empuñadura";
        default: throw std::out_of_range("Estilo de esgrima desconocido");
    }
}

string materialPuntaLanzaToString(MaterialPuntaLanza mp) {
    switch (mp) {
        case MaterialPuntaLanza::Acero: return "Acero";
        case MaterialPuntaLanza::Obsidiana: return "Obsidiana";
        case MaterialPuntaLanza::Bronce: return "Bronce";
        case MaterialPuntaLanza::HuesoAfilado: return "Hueso Afilado";
        default: throw std::out_of_range("Material de punta de lanza desconocido");
    }
}

string origenGarroteToString(OrigenGarrote og) {
    switch (og) {
        case OrigenGarrote::RamaArbol: return "Rama de Árbol";
        case OrigenGarrote::PataMesa: return "Pata de Mesa";
        case OrigenGarrote::HuesoGrande: return "Hueso Grande";
        case OrigenGarrote::Improvisado: return "Improvisado";
        default: throw std::out_of_range("Origen de garrote desconocido");
    }
}
