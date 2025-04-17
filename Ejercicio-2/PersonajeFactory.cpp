#include "PersonajeFactory.hpp"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <array>

/**
 * @brief Implementación del método crearPersonaje
 * 
 * Crea un personaje específico según el tipo proporcionado, generando
 * atributos aleatorios apropiados para cada clase de personaje.
 * 
 * @param tipo Tipo de personaje a crear de la enumeración TipoPersonaje
 * @return Puntero compartido al personaje creado
 */
shared_ptr<InterfazPersonaje> PersonajeFactory::crearPersonaje(TipoPersonaje tipo) {
    string nombre = obtenerNombreAleatorio(
        tipo == TipoPersonaje::Hechicero || 
        tipo == TipoPersonaje::Conjurador || 
        tipo == TipoPersonaje::Brujo || 
        tipo == TipoPersonaje::Nigromante
    );

    // Valores aleatorios para los atributos
    int nivel = obtenerNumeroAleatorio(5, 10);
    int hp = obtenerNumeroAleatorio(80, 130);
    Raza raza = static_cast<Raza>(obtenerNumeroAleatorio(0, 4)); // 0-4 corresponden a los valores de la enum Raza
    int fuerza, agilidad, constitucion, inteligencia;

    // Crear personaje según tipo
    switch (tipo) {
        case TipoPersonaje::Hechicero:
            // Valores típicos para hechicero (alta inteligencia)
            fuerza = obtenerNumeroAleatorio(7, 12);
            agilidad = obtenerNumeroAleatorio(10, 15);
            constitucion = obtenerNumeroAleatorio(8, 14);
            inteligencia = obtenerNumeroAleatorio(15, 20);
            return make_shared<Hechicero>(
                nombre, nivel, hp, raza, fuerza, agilidad, constitucion, inteligencia,
                obtenerNumeroAleatorio(100, 150), // mana
                EscuelaMagia::Evocacion, FuentePoder::Arcana,
                obtenerNumeroAleatorio(10, 20), // poderArcano
                false, // barrierArcana
                obtenerNumeroAleatorio(5, 10), // controTemporal
                "Sombra" // nombreFamiliar
            );
            
        case TipoPersonaje::Conjurador:
            fuerza = obtenerNumeroAleatorio(6, 11);
            agilidad = obtenerNumeroAleatorio(9, 14);
            constitucion = obtenerNumeroAleatorio(7, 13);
            inteligencia = obtenerNumeroAleatorio(16, 20);
            return make_shared<Conjurador>(
                nombre, nivel, hp, raza, fuerza, agilidad, constitucion, inteligencia,
                obtenerNumeroAleatorio(100, 140), // mana
                EscuelaMagia::Conjuracion, FuentePoder::Elemental,
                obtenerNumeroAleatorio(10, 15), // poderCanalizar
                false, // circuloActivo
                obtenerNumeroAleatorio(15, 30), // poderElemental
                "Elemental de Fuego" // nombreInvocacionPrincipal
            );
            
        case TipoPersonaje::Brujo:
            fuerza = obtenerNumeroAleatorio(8, 13);
            agilidad = obtenerNumeroAleatorio(7, 12);
            constitucion = obtenerNumeroAleatorio(9, 15);
            inteligencia = obtenerNumeroAleatorio(14, 19);
            return make_shared<Brujo>(
                nombre, nivel, hp, raza, fuerza, agilidad, constitucion, inteligencia,
                obtenerNumeroAleatorio(80, 120), // mana
                EscuelaMagia::Necromancia, FuentePoder::Infernal,
                "Señor del Abismo", // nombrePatron
                obtenerNumeroAleatorio(15, 25), // poderPacto
                obtenerNumeroAleatorio(10, 20), // reservaInfernal
                true // pactoSangre
            );
            
        case TipoPersonaje::Nigromante:
            fuerza = obtenerNumeroAleatorio(7, 11);
            agilidad = obtenerNumeroAleatorio(6, 12);
            constitucion = obtenerNumeroAleatorio(10, 14);
            inteligencia = obtenerNumeroAleatorio(16, 20);
            return make_shared<Nigromante>(
                nombre, nivel, hp, raza, fuerza, agilidad, constitucion, inteligencia,
                obtenerNumeroAleatorio(90, 130), // mana
                EscuelaMagia::Necromancia, FuentePoder::Infernal,
                obtenerNumeroAleatorio(15, 25), // poderNoMuerto
                obtenerNumeroAleatorio(20, 40), // energiaNegativa
                false, // filacteriasActiva
                obtenerNumeroAleatorio(10, 20) // esenciasAlmas
            );
            
        case TipoPersonaje::Barbaro:
            // Valores típicos para bárbaro (alta fuerza y constitución)
            fuerza = obtenerNumeroAleatorio(16, 20);
            agilidad = obtenerNumeroAleatorio(12, 16);
            constitucion = obtenerNumeroAleatorio(14, 18);
            inteligencia = obtenerNumeroAleatorio(6, 10);
            return make_shared<Barbaro>(
                nombre, nivel, hp, raza, fuerza, agilidad, constitucion, inteligencia,
                obtenerNumeroAleatorio(90, 120), // aguante
                EstiloCombate::Berserker, TipoArmadura::Media,
                obtenerNumeroAleatorio(8, 15), // bonusDanio
                obtenerNumeroAleatorio(10, 15), // bonusDefensa
                obtenerNumeroAleatorio(10, 20), // nivelFuria
                obtenerNumeroAleatorio(15, 30), // resistenciaDolor
                "¡Por mi clan!", // gritoGuerra
                obtenerNumeroAleatorio(10, 20) // intimidacion
            );
            
        case TipoPersonaje::Paladin:
            fuerza = obtenerNumeroAleatorio(15, 19);
            agilidad = obtenerNumeroAleatorio(10, 14);
            constitucion = obtenerNumeroAleatorio(13, 17);
            inteligencia = obtenerNumeroAleatorio(12, 16);
            return make_shared<Paladin>(
                nombre, nivel, hp, raza, fuerza, agilidad, constitucion, inteligencia,
                obtenerNumeroAleatorio(80, 110), // aguante
                EstiloCombate::Defensivo, TipoArmadura::Pesada,
                obtenerNumeroAleatorio(10, 15), // bonusDanio
                obtenerNumeroAleatorio(12, 18), // bonusDefensa
                obtenerNumeroAleatorio(30, 50), // poderDivino
                "Luz del Alba", // oracionSagrada
                obtenerNumeroAleatorio(15, 25), // poderCurativo
                true, // juramentoActivo
                obtenerNumeroAleatorio(20, 40) // auraLuz
            );
            
        case TipoPersonaje::Caballero:
            fuerza = obtenerNumeroAleatorio(14, 18);
            agilidad = obtenerNumeroAleatorio(11, 15);
            constitucion = obtenerNumeroAleatorio(13, 17);
            inteligencia = obtenerNumeroAleatorio(10, 14);
            return make_shared<Caballero>(
                nombre, nivel, hp, raza, fuerza, agilidad, constitucion, inteligencia,
                obtenerNumeroAleatorio(85, 110), // aguante
                EstiloCombate::Equilibrado, TipoArmadura::Pesada,
                obtenerNumeroAleatorio(10, 15), // bonusDanio
                obtenerNumeroAleatorio(10, 15), // bonusDefensa
                obtenerNumeroAleatorio(25, 40), // honorCaballero
                "Por el Reino", // juramento
                true, // tieneCorcel
                obtenerNumeroAleatorio(15, 25), // bonusCarga
                "Orden del Dragón" // orden
            );
            
        case TipoPersonaje::Mercenario:
            fuerza = obtenerNumeroAleatorio(13, 17);
            agilidad = obtenerNumeroAleatorio(14, 18);
            constitucion = obtenerNumeroAleatorio(10, 14);
            inteligencia = obtenerNumeroAleatorio(8, 12);
            return make_shared<Mercenario>(
                nombre, nivel, hp, raza, fuerza, agilidad, constitucion, inteligencia,
                obtenerNumeroAleatorio(70, 100), // aguante
                EstiloCombate::Agresivo, TipoArmadura::Media,
                obtenerNumeroAleatorio(12, 18), // bonusDanio
                obtenerNumeroAleatorio(8, 12), // bonusDefensa
                obtenerNumeroAleatorio(50, 200), // oro
                obtenerNumeroAleatorio(10, 20), // sigilo
                obtenerNumeroAleatorio(8, 15), // bonusSorpresa
                "Compañía Negra" // gremioActual
            );
            
        case TipoPersonaje::Gladiador:
            fuerza = obtenerNumeroAleatorio(15, 19);
            agilidad = obtenerNumeroAleatorio(13, 17);
            constitucion = obtenerNumeroAleatorio(14, 18);
            inteligencia = obtenerNumeroAleatorio(7, 11);
            return make_shared<Gladiador>(
                nombre, nivel, hp, raza, fuerza, agilidad, constitucion, inteligencia,
                obtenerNumeroAleatorio(80, 110), // aguante
                EstiloCombate::Agresivo, TipoArmadura::Media,
                obtenerNumeroAleatorio(12, 18), // bonusDanio
                obtenerNumeroAleatorio(8, 12), // bonusDefensa
                obtenerNumeroAleatorio(10, 20), // fama
                obtenerNumeroAleatorio(5, 15), // victorias
                obtenerNumeroAleatorio(0, 5), // derrotas
                "Arena del León", // arenaPrincipal
                "El Implacable" // titulo
            );
            
        default:
            // Por defecto, crear un personaje básico
            return make_shared<Hechicero>(
                "Personaje Genérico", 1, 100, Raza::Humano, 
                10, 10, 10, 10, 100, 
                EscuelaMagia::Evocacion, FuentePoder::Arcana,
                10, false, 5, "Familiar"
            );
    }
}

/**
 * @brief Implementación del método crearMagoAleatorio
 * 
 * Crea un personaje mago de subtipo aleatorio (Hechicero, Conjurador, 
 * Brujo o Nigromante) con atributos aleatorios.
 * 
 * @return Puntero compartido al mago aleatorio creado
 */
shared_ptr<InterfazPersonaje> PersonajeFactory::crearMagoAleatorio() {
    // Generar un subtipo de mago aleatorio
    int tipoMago = obtenerNumeroAleatorio(0, 3);
    switch (tipoMago) {
        case 0: return crearPersonaje(TipoPersonaje::Hechicero);
        case 1: return crearPersonaje(TipoPersonaje::Conjurador);
        case 2: return crearPersonaje(TipoPersonaje::Brujo);
        case 3: return crearPersonaje(TipoPersonaje::Nigromante);
        default: return crearPersonaje(TipoPersonaje::Hechicero); // Coloco como valor default el Hechicero
    }
}

/**
 * @brief Implementación del método crearGuerreroAleatorio
 * 
 * Crea un personaje guerrero de subtipo aleatorio (Bárbaro, Paladín,
 * Caballero, Mercenario o Gladiador) con atributos aleatorios.
 * 
 * @return Puntero compartido al guerrero aleatorio creado
 */
shared_ptr<InterfazPersonaje> PersonajeFactory::crearGuerreroAleatorio() {
    // Generar un subtipo de guerrero aleatorio
    int tipoGuerrero = obtenerNumeroAleatorio(0, 4);
    switch (tipoGuerrero) {
        case 0: return crearPersonaje(TipoPersonaje::Barbaro);
        case 1: return crearPersonaje(TipoPersonaje::Paladin);
        case 2: return crearPersonaje(TipoPersonaje::Caballero);
        case 3: return crearPersonaje(TipoPersonaje::Mercenario);
        case 4: return crearPersonaje(TipoPersonaje::Gladiador);
        default: return crearPersonaje(TipoPersonaje::Barbaro); // Por defecto
    }
}

/**
 * @brief Implementación del método crearArma
 * 
 * Crea un arma específica según el tipo proporcionado, generando
 * atributos aleatorios apropiados para cada tipo de arma.
 * 
 * @param tipo Tipo de arma a crear de la enumeración TipoArma
 * @return Puntero único al arma creada
 */
unique_ptr<InterfazArmas> PersonajeFactory::crearArma(TipoArma tipo) {
    // Variables comunes para todas las armas
    string nombre;
    int poder, durabilidad;
    double peso;
    Rarity rareza = static_cast<Rarity>(obtenerNumeroAleatorio(0, 4)); // 0-4 para los valores de enum Rarity
    
    // Generar valores aleatorios básicos
    poder = obtenerNumeroAleatorio(10, 50);
    durabilidad = obtenerNumeroAleatorio(50, 150);
    peso = 0.5 + static_cast<double>(obtenerNumeroAleatorio(1, 100)) / 20.0; // Entre 0.5 y 5.5 kg

    switch (tipo) {
        case TipoArma::Baston: {
            nombre = "Bastón de " + obtenerNombreAleatorio(true);
            TipoMadera tipoMadera = static_cast<TipoMadera>(obtenerNumeroAleatorio(0, 4));
            TipoGema tipoGema = static_cast<TipoGema>(obtenerNumeroAleatorio(0, 5));
            ElementoMagico elemento = static_cast<ElementoMagico>(obtenerNumeroAleatorio(0, 5));
            
            return make_unique<Baston>(
                nombre, poder, durabilidad, peso, rareza,
                obtenerNumeroAleatorio(30, 100), // energía arcana máxima
                tipoMadera, tipoGema, 
                obtenerNumeroAleatorio(1, 15), // nivel de encantamiento
                elemento
            );
        }
        case TipoArma::LibroHechizos: {
            nombre = "Grimorio de " + obtenerNombreAleatorio(true);
            IdiomaLibro idioma = static_cast<IdiomaLibro>(obtenerNumeroAleatorio(0, 4));
            MaterialCubierta material = static_cast<MaterialCubierta>(obtenerNumeroAleatorio(0, 3));
            
            auto libro = make_unique<LibroHechizos>(
                nombre, poder, durabilidad, peso, rareza,
                obtenerNumeroAleatorio(50, 150), // energía arcana máxima
                obtenerNumeroAleatorio(100, 500), // páginas totales
                idioma, material
            );
            
            // Añadir algunos hechizos aleatorios
            const array<string, 10> hechizos = {
                "Bola de Fuego", "Rayo de Hielo", "Curación", "Teleportación", "Invisibilidad",
                "Pared de Fuego", "Escudo Mágico", "Misiles Mágicos", "Dormir", "Imagen Ilusoria"
            };
            
            int numHechizos = obtenerNumeroAleatorio(1, 5);
            for (int i = 0; i < numHechizos; ++i) {
                libro->aprenderHechizo(hechizos[obtenerNumeroAleatorio(0, 9)]);
            }
            
            return libro;
        }
        case TipoArma::Pocion: {
            nombre = "Poción de " + obtenerNombreAleatorio(true);
            EfectoPocion efecto = static_cast<EfectoPocion>(obtenerNumeroAleatorio(0, 6));
            ColorPocion color = static_cast<ColorPocion>(obtenerNumeroAleatorio(0, 6));
            
            return make_unique<Pocion>(
                nombre, poder, durabilidad, peso, rareza,
                0, // Las pociones no usan energía arcana
                efecto,
                obtenerNumeroAleatorio(10, 50), // potencia del efecto
                obtenerNumeroAleatorio(1, 5), // dosis restantes
                color,
                obtenerNumeroAleatorio(0, 1) == 1 // 50% de probabilidad de ser permanente
            );
        }
        case TipoArma::Amuleto: {
            nombre = "Amuleto de " + obtenerNombreAleatorio(true);
            MaterialAmuleto material = static_cast<MaterialAmuleto>(obtenerNumeroAleatorio(0, 4));
            
            // Posibles bonus pasivos
            const array<string, 5> tipoBonus = {
                "Protección", "Poder", "Agilidad", "Sabiduría", "Fortaleza"
            };
            
            return make_unique<Amuleto>(
                nombre, poder, durabilidad, peso, rareza,
                obtenerNumeroAleatorio(20, 80), // energía arcana máxima
                tipoBonus[obtenerNumeroAleatorio(0, 4)],
                obtenerNumeroAleatorio(5, 25), // valor del bonus
                material,
                obtenerNumeroAleatorio(0, 1) == 1 // 50% de probabilidad de requerir sintonización
            );
        }
        case TipoArma::HachaSimple: {
            nombre = "Hacha de " + obtenerNombreAleatorio(false);
            TipoMango tipoMango = static_cast<TipoMango>(obtenerNumeroAleatorio(0, 3));
            
            return make_unique<HachaSimple>(
                nombre, poder, durabilidad, peso, rareza,
                obtenerNumeroAleatorio(30, 100), // nivel de filo
                tipoMango,
                0.8 + static_cast<double>(obtenerNumeroAleatorio(0, 20)) / 10.0, // longitud mango 0.8-2.8m
                obtenerNumeroAleatorio(0, 1) == 1, // 50% de probabilidad de ser arrojadiza
                obtenerNumeroAleatorio(5, 15), // bonus vs madera
                "Forjada por " + obtenerNombreAleatorio(false) // marca del herrero
            );
        }
        case TipoArma::HachaDoble: {
            nombre = "Hacha Doble de " + obtenerNombreAleatorio(false);
            
            return make_unique<HachaDoble>(
                nombre, poder, durabilidad, peso, rareza,
                obtenerNumeroAleatorio(40, 90), // nivel de filo
                0.5 + static_cast<double>(obtenerNumeroAleatorio(0, 10)) / 10.0, // balance 0.5-1.5
                obtenerNumeroAleatorio(3, 10), // penalización de parada
                true, // siempre requiere dos manos
                "Inscripción rúnica antigua", // inscripción
                obtenerNumeroAleatorio(10, 25) // bonus vs armadura
            );
        }
        case TipoArma::Espada: {
            nombre = "Espada de " + obtenerNombreAleatorio(false);
            TipoHojaEspada tipoHoja = static_cast<TipoHojaEspada>(obtenerNumeroAleatorio(0, 4));
            MaterialGuarda matGuarda = static_cast<MaterialGuarda>(obtenerNumeroAleatorio(0, 3));
            EstiloEsgrima estilo = static_cast<EstiloEsgrima>(obtenerNumeroAleatorio(0, 3));
            
            return make_unique<Espada>(
                nombre, poder, durabilidad, peso, rareza,
                obtenerNumeroAleatorio(50, 100), // nivel de filo
                tipoHoja, matGuarda,
                0.7 + static_cast<double>(obtenerNumeroAleatorio(0, 15)) / 10.0, // longitud hoja 0.7-2.2m
                obtenerNumeroAleatorio(5, 20), // bonus estocada
                estilo
            );
        }
        case TipoArma::Lanza: {
            nombre = "Lanza de " + obtenerNombreAleatorio(false);
            MaterialPuntaLanza matPunta = static_cast<MaterialPuntaLanza>(obtenerNumeroAleatorio(0, 3));
            
            return make_unique<Lanza>(
                nombre, poder, durabilidad, peso, rareza,
                obtenerNumeroAleatorio(30, 80), // nivel de filo
                1.5 + static_cast<double>(obtenerNumeroAleatorio(0, 25)) / 10.0, // longitud asta 1.5-4.0m
                matPunta,
                obtenerNumeroAleatorio(0, 1) == 1, // 50% de probabilidad de tener bandera
                obtenerNumeroAleatorio(3, 10), // alcance
                obtenerNumeroAleatorio(0, 1) == 1 // 50% de probabilidad de ser desmontable
            );
        }
        case TipoArma::Garrote: {
            nombre = "Garrote de " + obtenerNombreAleatorio(false);
            TipoMadera tipoMadera = static_cast<TipoMadera>(obtenerNumeroAleatorio(0, 4));
            OrigenGarrote origen = static_cast<OrigenGarrote>(obtenerNumeroAleatorio(0, 3));
            
            return make_unique<Garrote>(
                nombre, poder, durabilidad, peso, rareza,
                obtenerNumeroAleatorio(20, 60), // nivel de filo (en este caso, dureza)
                tipoMadera,
                obtenerNumeroAleatorio(0, 1) == 1, // 50% de probabilidad de tener clavos
                15.0 + static_cast<double>(obtenerNumeroAleatorio(0, 50)), // circunferencia cabeza 15-65cm
                obtenerNumeroAleatorio(10, 30), // bonus aturdimiento
                origen
            );
        }
        default:
            // Por defecto, crear una espada básica
            return make_unique<Espada>(
                "Espada Común", 20, 100, 2.0, Rarity::Comun, 
                50, TipoHojaEspada::Recta, MaterialGuarda::Acero, 
                1.0, 5, EstiloEsgrima::UnaMano
            );
    }
}

/**
 * @brief Implementación del método crearArmaAleatoria
 * 
 * Genera un arma de tipo aleatorio entre las disponibles.
 * 
 * @return Puntero único al arma aleatoria creada
 */
unique_ptr<InterfazArmas> PersonajeFactory::crearArmaAleatoria() {
    // Generar un tipo de arma aleatorio (0-8)
    int tipoArma = obtenerNumeroAleatorio(0, 8);
    return crearArma(static_cast<TipoArma>(tipoArma));
}

/**
 * @brief Implementación del método crearArmaParaMago
 * 
 * Crea un arma mágica adecuada para un personaje mago.
 * 
 * @return Puntero único al arma mágica creada
 */
unique_ptr<InterfazArmas> PersonajeFactory::crearArmaParaMago() {
    // Los magos prefieren armas mágicas (0-3)
    int tipoArma = obtenerNumeroAleatorio(0, 3);
    return crearArma(static_cast<TipoArma>(tipoArma));
}

/**
 * @brief Implementación del método crearArmaParaGuerrero
 * 
 * Crea un arma de combate adecuada para un personaje guerrero.
 * 
 * @return Puntero único al arma de combate creada
 */
unique_ptr<InterfazArmas> PersonajeFactory::crearArmaParaGuerrero() {
    // Los guerreros prefieren armas de combate (4-8)
    int tipoArma = obtenerNumeroAleatorio(4, 8);
    return crearArma(static_cast<TipoArma>(tipoArma));
}

/**
 * @brief Implementación del método crearPersonajeArmado con cantidad de armas aleatorias
 * 
 * Crea un personaje de tipo específico y le equipa una cantidad aleatoria
 * de armas entre 0 y 2.
 * 
 * @param tipo Tipo de personaje a crear de la enumeración TipoPersonaje
 * @return Puntero compartido al personaje armado
 */
shared_ptr<InterfazPersonaje> PersonajeFactory::crearPersonajeArmado(TipoPersonaje tipo) {
    // Número aleatorio de armas (0-2)
    int numArmas = obtenerNumeroAleatorio(0, 2);
    return crearPersonajeArmado(tipo, numArmas);
}

/**
 * @brief Implementación del método crearPersonajeArmado con cantidad específica de armas
 * 
 * Crea un personaje de tipo específico y le equipa una cantidad determinada
 * de armas, seleccionando armas apropiadas según el tipo de personaje.
 * 
 * @param tipo Tipo de personaje a crear
 * @param numArmas Número de armas para equipar al personaje
 * @return Puntero compartido al personaje armado
 */
shared_ptr<InterfazPersonaje> PersonajeFactory::crearPersonajeArmado(TipoPersonaje tipo, int numArmas) {
    // Primero crear el personaje
    auto personaje = crearPersonaje(tipo);
    
    // Determinar si es mago o guerrero
    bool esMago = (tipo == TipoPersonaje::Hechicero || 
                  tipo == TipoPersonaje::Conjurador || 
                  tipo == TipoPersonaje::Brujo || 
                  tipo == TipoPersonaje::Nigromante);
    
    // Añadir armas según sea apropiado para el tipo
    for (int i = 0; i < numArmas; ++i) {
        unique_ptr<InterfazArmas> arma;
        
        if (esMago) {
            // 80% de probabilidad de arma mágica, 20% de arma de combate
            if (obtenerNumeroAleatorio(1, 100) <= 80) {
                arma = crearArmaParaMago();
            } else {
                arma = crearArmaParaGuerrero();
            }
        } else {
            // 80% de probabilidad de arma de combate, 20% de arma mágica
            if (obtenerNumeroAleatorio(1, 100) <= 80) {
                arma = crearArmaParaGuerrero();
            } else {
                arma = crearArmaParaMago();
            }
        }
        
        // Equipar el arma al personaje usando move para transferir la propiedad
        personaje->agregarArma(move(arma));
    }
    
    return personaje;
}

/**
 * @brief Implementación del método generarGruposPersonajes
 * 
 * Genera grupos aleatorios de magos y guerreros, cada uno con un número
 * aleatorio de armas, y devuelve estadísticas sobre los grupos generados.
 * 
 * @return Estructura ResultadoGeneracion con los personajes y estadísticas
 */
ResultadoGeneracion PersonajeFactory::generarGruposPersonajes() {
    ResultadoGeneracion resultado;
    
    // Inicializar correctamente los contadores
    resultado.totalArmas = 0;
    resultado.totalPersonajes = 0;
    
    // 2.1 y 2.2: Generar cantidad aleatoria de personajes
    int cantidadMagos = obtenerNumeroAleatorio(3, 7);
    int cantidadGuerreros = obtenerNumeroAleatorio(3, 7);
    
    cout << "Generando " << cantidadMagos << " magos y " << cantidadGuerreros 
         << " guerreros..." << endl;
    
    // Generar magos
    for (int i = 0; i < cantidadMagos; ++i) {
        // Número aleatorio de armas (0-2)
        int numArmas = obtenerNumeroAleatorio(0, 2);
        
        // Tipo de mago aleatorio
        TipoPersonaje tipoMago = static_cast<TipoPersonaje>(obtenerNumeroAleatorio(0, 3)); // 0-3 para los cuatro tipos de mago
        
        // Crear y guardar el mago armado
        auto mago = crearPersonajeArmado(tipoMago, numArmas);
        resultado.magos.push_back(mago);
        
        // Contabilizar armas
        resultado.totalArmas += numArmas;
    }
    
    // Generar guerreros
    for (int i = 0; i < cantidadGuerreros; ++i) {
        // Número aleatorio de armas (0-2)
        int numArmas = obtenerNumeroAleatorio(0, 2);
        
        // Tipo de guerrero aleatorio (offset +4 para acceder a los guerreros en la enum)
        TipoPersonaje tipoGuerrero = static_cast<TipoPersonaje>(obtenerNumeroAleatorio(4, 8)); // 4-8 para los cinco tipos de guerrero
        
        // Crear y guardar el guerrero armado
        auto guerrero = crearPersonajeArmado(tipoGuerrero, numArmas);
        resultado.guerreros.push_back(guerrero);
        
        // Contabilizar armas
        resultado.totalArmas += numArmas;
    }
    
    // Actualizar estadísticas finales
    resultado.totalPersonajes = cantidadMagos + cantidadGuerreros;
    
    return resultado;
}

/**
 * @brief Implementación del método crearPersonajeModoCombtePPT
 * 
 * Crea un personaje configurado para el modo de combate Piedra-Papel-Tijera,
 * estableciendo su HP en 100 y equipándolo con armas específicas.
 * 
 * @param tipo Tipo de personaje a crear
 * @param numArmas Número de armas para equipar al personaje
 * @return Puntero compartido al personaje configurado para PPT
 */
shared_ptr<InterfazPersonaje> PersonajeFactory::crearPersonajeModoCombtePPT(TipoPersonaje tipo, int numArmas) {
    auto personaje = crearPersonaje(tipo);
    
    // Configurar el personaje para el modo de combate PPT
    // Esto establecerá el HP a 100 y marcará que está en modo combate PPT
    personaje->setHPParaCombatePPT();
    
    bool esMago = (tipo == TipoPersonaje::Hechicero || 
                   tipo == TipoPersonaje::Conjurador || 
                   tipo == TipoPersonaje::Brujo || 
                   tipo == TipoPersonaje::Nigromante);
    
    for (int i = 0; i < numArmas; ++i) {
        unique_ptr<InterfazArmas> arma;
        
        if (esMago) {
            arma = crearArmaParaMago();
        } else {
            arma = crearArmaParaGuerrero();
        }
        
        // Equipar el arma al personaje
        personaje->agregarArma(move(arma));
    }
    
    return personaje;
}

/**
 * @brief Implementación del método obtenerNombreAleatorio
 * 
 * Genera un nombre aleatorio apropiado según el tipo de personaje,
 * seleccionando de listas predefinidas para magos y guerreros.
 * 
 * @param esMago Indica si el personaje es un mago (true) o guerrero (false)
 * @return Nombre aleatorio seleccionado
 */
string PersonajeFactory::obtenerNombreAleatorio(bool esMago) {
    // Nombres para magos
    const array<string, 20> nombresMagos = {
        "Gandalf", "Merlin", "Morgana", "Radagast", "Elminster", 
        "Raistlin", "Medivh", "Galadriel", "Saruman", "Allanon", 
        "Jaina", "Khadgar", "Ged", "Rincewind", "Polgara", 
        "Elric", "Tenser", "Bigby", "Mordenkainen", "Tasha"
    };
    
    // Nombres para guerreros
    const array<string, 20> nombresGuerreros = {
        "Aragorn", "Conan", "Boromir", "Bronn", "Sandor", 
        "Drizzt", "Geralt", "Gimli", "Legolas", "Turin", 
        "Thorin", "Druss", "Wulfgar", "Caramon", "Sturm", 
        "Éomer", "Fingolfin", "Fëanor", "Beren", "Túrin"
    };
    
    if (esMago) {
        return nombresMagos[obtenerNumeroAleatorio(0, 19)];
    } else {
        return nombresGuerreros[obtenerNumeroAleatorio(0, 19)];
    }
}

/**
 * @brief Implementación del método obtenerNumeroAleatorio
 * 
 * Genera un número entero aleatorio dentro del rango especificado.
 * Inicializa la semilla del generador de números aleatorios solo
 * la primera vez que se llama a la función.
 * 
 * @param min Valor mínimo del rango
 * @param max Valor máximo del rango
 * @return Número aleatorio entre min y max (inclusive)
 */
int PersonajeFactory::obtenerNumeroAleatorio(int min, int max) {
    static bool semillaInicializada = false;
    
    if (!semillaInicializada) {
        srand(static_cast<unsigned int>(time(nullptr)));
        semillaInicializada = true;
    }
    
    if (min > max) {
        std::swap(min, max);
    }
    
    return min + (rand() % (max - min + 1));
}
