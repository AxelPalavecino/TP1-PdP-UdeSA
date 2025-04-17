/**
 * @file main.cpp
 * @brief JUEGO DE ROL - PROGRAMA DE PRUEBA
 * 
 * Este programa implementa un sistema de pruebas para todas las clases
 * y métodos del juego de rol.
 * 
 * ES UN PROGRAMA DE MUESTRA, podra ver la jerarquía de clases y la 
 * composición entre personajes y armas, mostrando cómo diferentes 
 * tipos de personajes, pero no interactuar directamente con ellos
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <limits>
#include <iomanip>

// Inclusión de cabeceras para armas
#include "Arma/InterfazArmas.hpp"
#include "Arma/ObjetoMagico.hpp"
#include "Arma/ArmaDeCombate.hpp"
#include "Arma/ItemsMagico/Baston.hpp"
#include "Arma/ItemsMagico/LibroHechizos.hpp"
#include "Arma/ItemsMagico/Pocion.hpp"
#include "Arma/ItemsMagico/Amuleto.hpp"
#include "Arma/ArmasDeCombate/HachaSimple.hpp"
#include "Arma/ArmasDeCombate/HachaDoble.hpp"
#include "Arma/ArmasDeCombate/Espada.hpp"
#include "Arma/ArmasDeCombate/Lanza.hpp"
#include "Arma/ArmasDeCombate/Garrote.hpp"

// Inclusión de cabeceras para personajes
#include "Personajes/InterfazPersonaje.hpp"
#include "Personajes/Mago.hpp"
#include "Personajes/Guerrero.hpp"
#include "Personajes/Magos/Hechicero.hpp"
#include "Personajes/Magos/Conjurador.hpp"
#include "Personajes/Magos/Brujo.hpp"
#include "Personajes/Magos/Nigromante.hpp"
#include "Personajes/Guerrero/Barbaro.hpp"
#include "Personajes/Guerrero/Paladin.hpp"
#include "Personajes/Guerrero/Caballero.hpp"
#include "Personajes/Guerrero/Mercenario.hpp"
#include "Personajes/Guerrero/Gladiador.hpp"

using namespace std;

// ==========================================
// FUNCIONES DE UTILIDAD
// ==========================================

/**
 * @brief Limpia la pantalla de la consola
 * 
 * Utiliza el comando apropiado según el sistema operativo
 * para limpiar la pantalla y mejorar la legibilidad.
 */
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief Pausa la ejecución hasta que el usuario presione Enter
 * 
 * Muestra un mensaje y espera la entrada del usuario antes de continuar,
 * permitiendo leer la información en pantalla antes de avanzar.
 */
void pausar() {
    cout << "\nPresiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ==========================================
// PROTOTIPOS DE FUNCIONES
// ==========================================

void mostrarMenuPrincipal();
void probarArmas();
void probarPersonajes();
void probarInteracciones();

// ==========================================
// VARIABLES GLOBALES PARA PRUEBAS
// ==========================================

/**
 * @brief Almacena las armas creadas durante la ejecución del programa
 */
vector<unique_ptr<InterfazArmas>> armasCreadas;

/**
 * @brief Almacena los personajes creados durante la ejecución del programa
 */
vector<unique_ptr<InterfazPersonaje>> personajesCreados;

// ==========================================
// FUNCIONES PARA CREAR ARMAS
// ==========================================

/**
 * @brief Crea un bastón mágico con propiedades predefinidas
 * 
 * Instancia un objeto Baston con valores específicos para demostración,
 * incluyendo propiedades como gema, nivel de encantamiento y elemento mágico.
 * 
 * @return Puntero único a un objeto Baston implementando InterfazArmas
 */
unique_ptr<InterfazArmas> crearBaston() {
    return make_unique<Baston>(
        "Bastón de Poder", 20, 50, 1.5, Rarity::Raro,
        30, TipoMadera::Ebano, TipoGema::Rubi, 3, ElementoMagico::Fuego
    );
}

/**
 * @brief Crea un libro de hechizos (no implementado aún)
 * 
 * Función reservada para cuando la clase LibroHechizos esté completamente
 * implementada. Actualmente muestra un mensaje y devuelve nullptr.
 * 
 * @return nullptr (pendiente de implementación completa)
 */
unique_ptr<InterfazArmas> crearLibroHechizos() {
    cout << "Función crearLibroHechizos() no implementada aún." << endl;
    return nullptr;
}

/**
 * @brief Crea una poción de curación con propiedades predefinidas
 * 
 * Instancia un objeto Pocion con valores específicos para demostración,
 * configurándola como poción de curación con color rojo.
 * 
 * @return Puntero único a un objeto Pocion implementando InterfazArmas
 */
unique_ptr<InterfazArmas> crearPocion() {
    return make_unique<Pocion>(
        "Poción de Curación", 15, 3, 0.2, Rarity::Comun,
        0, EfectoPocion::Curacion, 20, 3, ColorPocion::Rojo, false
    );
}

/**
 * @brief Crea un amuleto protector con propiedades predefinidas
 * 
 * Instancia un objeto Amuleto con valores específicos para demostración,
 * configurándolo con propiedades protectoras y material de plata.
 * 
 * @return Puntero único a un objeto Amuleto implementando InterfazArmas
 */
unique_ptr<InterfazArmas> crearAmuleto() {
    return make_unique<Amuleto>(
        "Amuleto Protector", 10, 100, 0.1, Rarity::Epico,
        50, "Resistencia Mágica", 5, MaterialAmuleto::Plata, true
    );
}

/**
 * @brief Crea un hacha simple con propiedades predefinidas
 * 
 * Instancia un objeto HachaSimple con valores específicos para demostración,
 * configurándola como arrojadiza con mango de madera.
 * 
 * @return Puntero único a un objeto HachaSimple implementando InterfazArmas
 */
unique_ptr<InterfazArmas> crearHachaSimple() {
    return make_unique<HachaSimple>(
        "Hacha de Leñador", 15, 40, 2.5, Rarity::PocoComun,
        6, TipoMango::Madera, 0.8, true, 5, "Herrero del Valle"
    );
}

/**
 * @brief Crea un hacha doble con propiedades predefinidas
 * 
 * Instancia un objeto HachaDoble con valores específicos para demostración,
 * configurándola con inscripción rúnica y bonus contra armaduras.
 * 
 * @return Puntero único a un objeto HachaDoble implementando InterfazArmas
 */
unique_ptr<InterfazArmas> crearHachaDoble() {
    return make_unique<HachaDoble>(
        "Hacha de Guerra", 25, 35, 4.0, Rarity::Raro,
        8, 1.2, 3, true, "Muerte a mis enemigos", 8
    );
}

/**
 * @brief Crea una espada con propiedades predefinidas
 * 
 * Instancia un objeto Espada con valores específicos para demostración,
 * configurándola con hoja recta y guarda de acero.
 * 
 * @return Puntero único a un objeto Espada implementando InterfazArmas
 */
unique_ptr<InterfazArmas> crearEspada() {
    return make_unique<Espada>(
        "Espada Larga", 20, 50, 1.8, Rarity::PocoComun,
        7, TipoHojaEspada::Recta, MaterialGuarda::Acero, 1.0, 5, EstiloEsgrima::UnaMano
    );
}

/**
 * @brief Crea una lanza con propiedades predefinidas
 * 
 * Instancia un objeto Lanza con valores específicos para demostración,
 * configurándola con punta de acero y características desmontables.
 * 
 * @return Puntero único a un objeto Lanza implementando InterfazArmas
 */
unique_ptr<InterfazArmas> crearLanza() {
    return make_unique<Lanza>(
        "Lanza de Cazador", 18, 30, 2.2, Rarity::Comun,
        5, 2.5, MaterialPuntaLanza::Acero, false, 3, true
    );
}

/**
 * @brief Crea un garrote con propiedades predefinidas
 * 
 * Instancia un objeto Garrote con valores específicos para demostración,
 * configurándolo como un garrote de roble sin clavos.
 * 
 * @return Puntero único a un objeto Garrote implementando InterfazArmas
 */
unique_ptr<InterfazArmas> crearGarrote() {
    return make_unique<Garrote>(
        "Garrote Nudoso", 12, 25, 3.0, Rarity::Comun,
        2, TipoMadera::Roble, false, 15.0, 4, OrigenGarrote::RamaArbol
    );
}

// ==========================================
// FUNCIONES PARA CREAR PERSONAJES
// ==========================================

/**
 * @brief Crea un personaje de tipo Hechicero con un arma equipada
 * 
 * Instancia un objeto Hechicero con valores específicos y le equipa
 * un bastón mágico como arma inicial.
 * 
 * @return Puntero único a un objeto Hechicero implementando InterfazPersonaje
 */
unique_ptr<InterfazPersonaje> crearHechicero() {
    auto hechicero = make_unique<Hechicero>(
        "Gandalf", 5, 80, Raza::Humano, 8, 12, 10, 18,
        100, EscuelaMagia::Abjuracion, FuentePoder::Arcana,
        10, true, 3, "Protección Elemental"
    );
    
    // Añadir un arma al personaje
    hechicero->agregarArma(crearBaston());
    return hechicero;
}

/**
 * @brief Crea un personaje de tipo Conjurador con un arma equipada
 * 
 * Instancia un objeto Conjurador con valores específicos y le equipa
 * un amuleto mágico como arma inicial.
 * 
 * @return Puntero único a un objeto Conjurador implementando InterfazPersonaje
 */
unique_ptr<InterfazPersonaje> crearConjurador() {
    auto conjurador = make_unique<Conjurador>(
        "Elminster", 6, 70, Raza::Elfo, 7, 14, 9, 19,
        120, EscuelaMagia::Conjuracion, FuentePoder::Divina,
        12, false, 25, "Elemental de Fuego"
    );
    
    // Añadir un arma al personaje
    conjurador->agregarArma(crearAmuleto());
    return conjurador;
}

/**
 * @brief Crea un personaje de tipo Brujo con un arma equipada
 * 
 * Instancia un objeto Brujo con valores específicos y le equipa
 * una poción como arma inicial.
 * 
 * @return Puntero único a un objeto Brujo implementando InterfazPersonaje
 */
unique_ptr<InterfazPersonaje> crearBrujo() {
    auto brujo = make_unique<Brujo>(
        "Gul'dan", 4, 60, Raza::Orco, 10, 11, 12, 16,
        80, EscuelaMagia::Evocacion, FuentePoder::Infernal,
        "Asmodeo", 8, 5, false
    );
    
    // Añadir un arma al personaje
    brujo->agregarArma(crearPocion());
    return brujo;
}

/**
 * @brief Crea un personaje de tipo Nigromante con un arma equipada
 * 
 * Instancia un objeto Nigromante con valores específicos y le equipa
 * un bastón mágico como arma inicial.
 * 
 * @return Puntero único a un objeto Nigromante implementando InterfazPersonaje
 */
unique_ptr<InterfazPersonaje> crearNigromante() {
    auto nigromante = make_unique<Nigromante>(
        "Sauron", 7, 75, Raza::Gnomo, 9, 10, 13, 17,
        90, EscuelaMagia::Necromancia, FuentePoder::Arcana,
        15, 30, false, 20
    );
    
    // Añadir un arma al personaje
    nigromante->agregarArma(crearBaston());
    return nigromante;
}

/**
 * @brief Crea un personaje de tipo Barbaro con un arma equipada
 * 
 * Instancia un objeto Barbaro con valores específicos y le equipa
 * un hacha doble como arma inicial.
 * 
 * @return Puntero único a un objeto Barbaro implementando InterfazPersonaje
 */
unique_ptr<InterfazPersonaje> crearBarbaro() {
    auto barbaro = make_unique<Barbaro>(
        "Conan", 6, 120, Raza::Humano, 18, 14, 16, 8,
        80, EstiloCombate::Berserker, TipoArmadura::Media, 12, 15,
        10, 5, "¡Por Crom!", 8
    );
    
    // Añadir un arma al personaje
    barbaro->agregarArma(crearHachaDoble());
    return barbaro;
}

/**
 * @brief Crea un personaje de tipo Paladin con un arma equipada
 * 
 * Instancia un objeto Paladin con valores específicos y le equipa
 * una espada como arma inicial.
 * 
 * @return Puntero único a un objeto Paladin implementando InterfazPersonaje
 */
unique_ptr<InterfazPersonaje> crearPaladin() {
    auto paladin = make_unique<Paladin>(
        "Arthas", 7, 100, Raza::Humano, 16, 12, 14, 10,
        70, EstiloCombate::Defensivo, TipoArmadura::Pesada, 15, 8,
        50, "La Luz", 20, true, 15
    );
    
    // Añadir un arma al personaje
    paladin->agregarArma(crearEspada());
    return paladin;
}

/**
 * @brief Crea un personaje de tipo Caballero con un arma equipada
 * 
 * Instancia un objeto Caballero con valores específicos y le equipa
 * una lanza como arma inicial.
 * 
 * @return Puntero único a un objeto Caballero implementando InterfazPersonaje
 */
unique_ptr<InterfazPersonaje> crearCaballero() {
    auto caballero = make_unique<Caballero>(
        "Lancelot", 8, 95, Raza::Humano, 15, 13, 14, 12,
        65, EstiloCombate::Defensivo, TipoArmadura::Pesada, 16, 10,
        40, "Protegeré al inocente", true, 12, "Caballeros de la Mesa Redonda"
    );
    
    // Añadir un arma al personaje
    caballero->agregarArma(crearLanza());
    return caballero;
}

/**
 * @brief Crea un personaje de tipo Gladiador con un arma equipada
 * 
 * Instancia un objeto Gladiador con valores específicos y le equipa
 * una espada como arma inicial.
 * 
 * @return Puntero único a un objeto Gladiador implementando InterfazPersonaje
 */
unique_ptr<InterfazPersonaje> crearGladiador() {
    auto gladiador = make_unique<Gladiador>(
        "Maximus", 5, 110, Raza::Humano, 17, 15, 14, 9,
        75, EstiloCombate::Agresivo, TipoArmadura::Media, 10, 12,
        15, 30, 5, "Coliseo Romano", "El Implacable"
    );
    
    // Añadir un arma al personaje
    gladiador->agregarArma(crearEspada());
    return gladiador;
}

// ==========================================
// IMPLEMENTACIÓN DEL MENÚ PRINCIPAL
// ==========================================

/**
 * @brief Muestra el menú principal y gestiona la selección de opciones
 * 
 * Presenta un menú interactivo con opciones para probar armas,
 * personajes y combates, y ejecuta la función correspondiente según
 * la selección del usuario.
 */
void mostrarMenuPrincipal() {
    bool salir = false;
    
    while (!salir) {
        limpiarPantalla();
        cout << "┌───────────────────────────────────────┐" << endl;
        cout << "│        JUEGO DE ROL - PRUEBAS         │" << endl;
        cout << "├───────────────────────────────────────┤" << endl;
        cout << "│ 1. Probar Armas y Objetos             │" << endl;
        cout << "│ 2. Probar Personajes                  │" << endl;
        cout << "│ 3. Simulador de Combate               │" << endl;
        cout << "│ 0. Salir                              │" << endl;
        cout << "└───────────────────────────────────────┘" << endl;
        cout << "Seleccione una opción: ";
        
        int opcion;
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (opcion) {
            case 1:
                probarArmas();
                break;
            case 2:
                probarPersonajes();
                break;
            case 3:
                probarInteracciones();
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                salir = true;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                pausar();
                break;
        }
    }
}

// ==========================================
// FUNCIÓN PRINCIPAL
// ==========================================

/**
 * @brief Punto de entrada principal del programa
 * 
 * Inicializa el generador de números aleatorios, muestra un mensaje
 * de bienvenida y ejecuta el menú principal del programa.
 * 
 * @return Código de salida del programa (0 indica ejecución exitosa)
 */
int main() {
    // Inicializar semilla aleatoria para generación de números aleatorios
    srand(static_cast<unsigned int>(time(nullptr)));
    
    cout << "Iniciando programa de prueba del Juego de Rol..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    mostrarMenuPrincipal();
    
    cout << "Programa finalizado." << endl;
    return 0;
}

// ==========================================
// IMPLEMENTACIÓN DE LAS PRUEBAS
// ==========================================

/**
 * @brief Implementa las pruebas para armas y objetos mágicos
 * 
 * Crea instancias de diferentes tipos de armas, muestra su información,
 * prueba sus métodos comunes y específicos, y demuestra cómo se comportan
 * ante diferentes situaciones como daño, reparación y mejoras.
 */
void probarArmas() {
    limpiarPantalla();
    cout << "===== PRUEBA DE ARMAS Y OBJETOS MÁGICOS =====" << endl << endl;

    // Vector para almacenar todas las armas a probar
    vector<unique_ptr<InterfazArmas>> armasTest;

    // 1. CREAR INSTANCIAS DE TODAS LAS ARMAS
    cout << ">> Creando armas..." << endl;
    armasTest.push_back(crearBaston());
    armasTest.push_back(crearPocion());
    armasTest.push_back(crearAmuleto());
    armasTest.push_back(crearHachaSimple());
    armasTest.push_back(crearHachaDoble());
    armasTest.push_back(crearEspada());
    armasTest.push_back(crearLanza());
    armasTest.push_back(crearGarrote());
    cout << "Se han creado " << armasTest.size() << " armas para pruebas." << endl << endl;

    // 2. MOSTRAR INFORMACIÓN DE TODAS LAS ARMAS
    cout << ">> Información de todas las armas:" << endl;
    for (const auto& arma : armasTest) {
        cout << "----------------------------------------" << endl;
        arma->mostrarInfo();
    }
    cout << "----------------------------------------" << endl << endl;

    // 3. PRUEBA DE USO GENÉRICO (método usar())
    cout << ">> Prueba de uso básico de cada arma:" << endl;
    for (const auto& arma : armasTest) {
        cout << "----------------------------------------" << endl;
        cout << "Usando " << arma->getNombre() << ":" << endl;
        int resultado = arma->usar();
        cout << "Resultado: " << resultado << endl;
    }
    cout << "----------------------------------------" << endl << endl;

    // 4. PRUEBAS ESPECÍFICAS DE CADA TIPO DE ARMA
    cout << ">> Pruebas específicas por tipo de arma:" << endl;

    // 4.1 Bastón
    {
        cout << "==== PRUEBA DE BASTÓN ====" << endl;
        auto baston = dynamic_cast<Baston*>(armasTest[0].get());
        if (baston) {
            cout << "Lanzando rayo mágico con " << baston->getNombre() << "..." << endl;
            int danioRayo = baston->lanzarRayoMagico();
            cout << "Daño del rayo: " << danioRayo << endl;
            
            cout << "Mejorando encantamiento del bastón..." << endl;
            baston->mejorarEncantamiento(2);
            
            if (baston->tieneGema()) {
                cout << "El bastón tiene una gema. Cambiándola a Zafiro..." << endl;
                baston->cambiarGema(TipoGema::Zafiro);
            } else {
                cout << "El bastón no tiene gema. Añadiendo una..." << endl;
                baston->cambiarGema(TipoGema::Esmeralda);
            }
            
            cout << "Información actualizada del bastón:" << endl;
            baston->mostrarInfo();
        }
        cout << endl;
    }

    // 4.2 Poción
    {
        cout << "==== PRUEBA DE POCIÓN ====" << endl;
        auto pocion = dynamic_cast<Pocion*>(armasTest[1].get());
        if (pocion) {
            cout << "Bebiendo " << pocion->getNombre() << "..." << endl;
            int efecto1 = pocion->usar();
            cout << "Efecto: " << efecto1 << endl;
            
            cout << "Bebiendo nuevamente la poción..." << endl;
            int efecto2 = pocion->usar();
            cout << "Efecto: " << efecto2 << endl;
            
            cout << "Creando otra poción para combinar..." << endl;
            Pocion pocionExtra("Poción de Maná", 10, 3, 0.2, Rarity::Comun,
                              0, EfectoPocion::Mana, 15, 2, ColorPocion::Azul, false);
            
            cout << "Intentando combinar pociones de diferentes efectos (debería fallar)..." << endl;
            pocion->combinar(pocionExtra);
            
            cout << "Creando una poción del mismo tipo..." << endl;
            Pocion pocionCombinar("Poción de Curación Débil", 8, 2, 0.1, Rarity::Comun,
                                 0, EfectoPocion::Curacion, 12, 2, ColorPocion::Rojo, false);
            
            cout << "Combinando pociones del mismo tipo..." << endl;
            pocion->combinar(pocionCombinar);
            
            cout << "Información actualizada de la poción:" << endl;
            pocion->mostrarInfo();
        }
        cout << endl;
    }

    // 4.3 Amuleto
    {
        cout << "==== PRUEBA DE AMULETO ====" << endl;
        auto amuleto = dynamic_cast<Amuleto*>(armasTest[2].get());
        if (amuleto) {
            cout << "Intentando usar el amuleto sin sintonizar..." << endl;
            int efecto = amuleto->usar();
            cout << "Efecto: " << efecto << endl;
            
            cout << "Sintonizando con el amuleto..." << endl;
            bool sintonizacion = amuleto->sintonizar();
            cout << "Sintonización " << (sintonizacion ? "exitosa" : "fallida") << endl;
            
            cout << "Usando el amuleto sintonizado..." << endl;
            efecto = amuleto->usar();
            cout << "Efecto: " << efecto << endl;
            
            cout << "Desvinculando del amuleto..." << endl;
            amuleto->desintonizar();
            
            cout << "Recargando energía del amuleto..." << endl;
            amuleto->recargarEnergia(20);
            
            cout << "Información actualizada del amuleto:" << endl;
            amuleto->mostrarInfo();
        }
        cout << endl;
    }

    // 4.4 Hacha Simple
    {
        cout << "==== PRUEBA DE HACHA SIMPLE ====" << endl;
        auto hacha = dynamic_cast<HachaSimple*>(armasTest[3].get());
        if (hacha) {
            cout << "Usando " << hacha->getNombre() << " para talar..." << endl;
            int danioTalar = hacha->talar();
            cout << "Daño de tala: " << danioTalar << endl;
            
            cout << "Afilando el hacha..." << endl;
            hacha->afilar(10);
            
            if (hacha->puedeArrojarse()) {
                cout << "Lanzando el hacha arrojadiza..." << endl;
                int danioLanzar = hacha->lanzar();
                cout << "Daño de lanzamiento: " << danioLanzar << endl;
            } else {
                cout << "Esta hacha no puede arrojarse." << endl;
            }
            
            cout << "Reparando el hacha..." << endl;
            hacha->reparar(15);
            
            cout << "Información del fabricante: " << hacha->getMarcaHerrero() << endl;
            
            cout << "Información actualizada del hacha:" << endl;
            hacha->mostrarInfo();
        }
        cout << endl;
    }

    // 4.5 Hacha Doble
    {
        cout << "==== PRUEBA DE HACHA DOBLE ====" << endl;
        auto hachaDoble = dynamic_cast<HachaDoble*>(armasTest[4].get());
        if (hachaDoble) {
            cout << "Realizando ataque de hendidura con " << hachaDoble->getNombre() << "..." << endl;
            int danioHendidura = hachaDoble->hendidura();
            cout << "Daño de hendidura: " << danioHendidura << endl;
            
            cout << "Realizando ataque torbellino..." << endl;
            int danioTorbellino = hachaDoble->ataqueTorbellino();
            cout << "Daño de torbellino: " << danioTorbellino << endl;
            
            cout << "Leyendo inscripción del hacha: " << hachaDoble->leerInscripcion() << endl;
            
            cout << "¿Requiere dos manos? " << (hachaDoble->esADosManos() ? "Sí" : "No") << endl;
            cout << "Balance del arma: " << hachaDoble->getBalance() << endl;
            
            cout << "Reparando el hacha..." << endl;
            hachaDoble->reparar(10);
            
            cout << "Información actualizada del hacha doble:" << endl;
            hachaDoble->mostrarInfo();
        }
        cout << endl;
    }

    // 4.6 Espada
    {
        cout << "==== PRUEBA DE ESPADA ====" << endl;
        auto espada = dynamic_cast<Espada*>(armasTest[5].get());
        if (espada) {
            cout << "Realizando estocada con " << espada->getNombre() << "..." << endl;
            int danioEstocada = espada->estocar();
            cout << "Daño de estocada: " << danioEstocada << endl;
            
            cout << "Intentando parar un ataque..." << endl;
            bool exitoParada = espada->parar();
            cout << "Parada " << (exitoParada ? "exitosa" : "fallida") << endl;
            
            cout << "Puliendo la hoja..." << endl;
            espada->pulirHoja();
            
            cout << "Tipo de hoja: " << tipoHojaEspadaToString(espada->getTipoHoja()) << endl;
            cout << "Longitud de hoja: " << espada->getLongitudHoja() << "m" << endl;
            
            cout << "Información actualizada de la espada:" << endl;
            espada->mostrarInfo();
        }
        cout << endl;
    }

    // 4.7 Lanza
    {
        cout << "==== PRUEBA DE LANZA ====" << endl;
        auto lanza = dynamic_cast<Lanza*>(armasTest[6].get());
        if (lanza) {
            cout << "Realizando barrido con " << lanza->getNombre() << "..." << endl;
            int danioBarrido = lanza->barrer();
            cout << "Daño de barrido: " << danioBarrido << endl;
            
            cout << "Preparando contra carga..." << endl;
            bool preparado = lanza->prepararContraCarga();
            cout << "Preparación " << (preparado ? "exitosa" : "fallida") << endl;
            
            cout << "Usando la lanza preparada..." << endl;
            int danioCarga = lanza->usar();
            cout << "Daño con preparación: " << danioCarga << endl;
            
            cout << "Colocando una bandera en la lanza..." << endl;
            lanza->ponerQuitarBandera(true);
            
            cout << "Alcance de la lanza: " << lanza->getAlcance() << endl;
            
            cout << "Información actualizada de la lanza:" << endl;
            lanza->mostrarInfo();
        }
        cout << endl;
    }

    // 4.8 Garrote
    {
        cout << "==== PRUEBA DE GARROTE ====" << endl;
        auto garrote = dynamic_cast<Garrote*>(armasTest[7].get());
        if (garrote) {
            cout << "Realizando golpe de aplastamiento con " << garrote->getNombre() << "..." << endl;
            int danioAplastar = garrote->aplastar();
            cout << "Daño de aplastamiento: " << danioAplastar << endl;
            
            cout << "¿Está claveteado? " << (garrote->estaClaveteado() ? "Sí" : "No") << endl;
            
            cout << "Añadiendo clavos al garrote..." << endl;
            garrote->ponerQuitarClavos(true);
            
            cout << "Bonus de aturdimiento: " << garrote->getBonusAturdimiento() << endl;
            
            cout << "Reforzando la madera..." << endl;
            garrote->reforzarMadera();
            
            cout << "Información actualizada del garrote:" << endl;
            garrote->mostrarInfo();
        }
        cout << endl;
    }

    cout << "===== PRUEBAS DE ARMAS COMPLETADAS =====" << endl;
    pausar();
}

/**
 * @brief Implementa las pruebas para los diferentes tipos de personajes
 * 
 * Crea instancias de varios tipos de personajes, muestra su información,
 * prueba sus habilidades específicas y demuestra la gestión del inventario
 * de armas, incluyendo cómo equipar, quitar y manipular armas.
 */
void probarPersonajes() {
    limpiarPantalla();
    cout << "===== PRUEBA DE PERSONAJES =====" << endl << endl;

    // Vector para almacenar todos los personajes a probar
    vector<unique_ptr<InterfazPersonaje>> personajesTest;

    // 1. CREAR INSTANCIAS DE PERSONAJES
    cout << ">> Creando personajes..." << endl;
    personajesTest.push_back(crearHechicero());
    personajesTest.push_back(crearBarbaro());
    personajesTest.push_back(crearNigromante());
    personajesTest.push_back(crearPaladin());
    cout << "Se han creado " << personajesTest.size() << " personajes para pruebas." << endl << endl;

    // 2. MOSTRAR INFORMACIÓN BÁSICA DE TODOS LOS PERSONAJES
    cout << ">> Información general de personajes:" << endl;
    for (const auto& personaje : personajesTest) {
        cout << "----------------------------------------" << endl;
        cout << "Nombre: " << personaje->getNombre() << endl;
        cout << "HP: " << personaje->getHP() << endl;
        personaje->mostrarInfo();
        personaje->mostrarInventario();
    }
    cout << "----------------------------------------" << endl << endl;

    // 3. PRUEBAS ESPECÍFICAS PARA CADA TIPO DE PERSONAJE
    cout << ">> Pruebas específicas por tipo de personaje:" << endl;

    // 3.1 Prueba de Hechicero
    {
        cout << "==== PRUEBA DE HECHICERO ====" << endl;
        auto hechicero = dynamic_cast<Hechicero*>(personajesTest[0].get());
        if (hechicero) {
            cout << "Probando habilidades del hechicero " << hechicero->getNombre() << "..." << endl;
            
            cout << "Aprendiendo hechizos..." << endl;
            hechicero->aprenderHechizo("Bola de Fuego");
            hechicero->aprenderHechizo("Escudo Arcano");
            hechicero->aprenderHechizo("Rayo Gélido");
            hechicero->listarHechizos();
            
            cout << "Invocando familiar..." << endl;
            hechicero->invocarFamiliar();
            
            cout << "Lanzando un hechizo..." << endl;
            int dañoHechizo = hechicero->lanzarHechizo("Bola de Fuego");
            cout << "Daño del hechizo: " << dañoHechizo << endl;
            
            cout << "Activando bastión arcano..." << endl;
            hechicero->activarBastionArcano();
            
            cout << "Alterando tiempo..." << endl;
            int efectoAlteracion = hechicero->alterarTiempo();
            cout << "Efecto de alteración temporal: " << efectoAlteracion << endl;
            
            cout << "Aumentando poder arcano..." << endl;
            hechicero->aumentarPoder(5);
            
            cout << "Meditando para recuperar maná..." << endl;
            hechicero->meditar();
            
            cout << "Información actualizada del hechicero:" << endl;
            hechicero->mostrarInfo();
        }
        cout << endl;
    }

    // 3.2 Prueba de Bárbaro
    {
        cout << "==== PRUEBA DE BÁRBARO ====" << endl;
        auto barbaro = dynamic_cast<Barbaro*>(personajesTest[1].get());
        if (barbaro) {
            cout << "Probando habilidades del bárbaro " << barbaro->getNombre() << "..." << endl;
            
            cout << "Aumentando furia..." << endl;
            barbaro->aumentarFuria(10);
            
            cout << "Entrando en frenesí..." << endl;
            barbaro->entrarEnFrenesi();
            
            cout << "Ejecutando grito de batalla..." << endl;
            int efectoGrito = barbaro->gritarEnBatalla();
            cout << "Efecto de intimidación: " << efectoGrito << endl;
            
            cout << "Realizando golpe salvaje..." << endl;
            int dañoGolpe = barbaro->golpeSalvaje();
            cout << "Daño del golpe: " << dañoGolpe << endl;
            
            cout << "Recibiendo daño..." << endl;
            barbaro->recibirDanio(20, false);
            
            cout << "Resistiendo dolor..." << endl;
            barbaro->resistirDolor();
            
            cout << "Información actualizada del bárbaro:" << endl;
            barbaro->mostrarInfo();
        }
        cout << endl;
    }

    // 3.3 Prueba de Nigromante
    {
        cout << "==== PRUEBA DE NIGROMANTE ====" << endl;
        auto nigromante = dynamic_cast<Nigromante*>(personajesTest[2].get());
        if (nigromante) {
            cout << "Probando habilidades del nigromante " << nigromante->getNombre() << "..." << endl;
            
            cout << "Levantando no-muerto..." << endl;
            int poderEsqueleto = nigromante->levantarNoMuerto("Esqueleto Guerrero");
            cout << "Poder del no-muerto: " << poderEsqueleto << endl;
            
            cout << "Aplicando toco de la muerte..." << endl;
            int dañoToco = nigromante->tocoDeLaMuerte();
            cout << "Daño del toco: " << dañoToco << endl;
            
            cout << "Controlando no-muerto..." << endl;
            nigromante->controlarNoMuerto("Esqueleto Guerrero");
            
            cout << "Drenando vida del no-muerto..." << endl;
            int vidaDrenada = nigromante->drenarVidaNoMuerto("Esqueleto Guerrero");
            cout << "Vida drenada: " << vidaDrenada << endl;
            
            cout << "Creando filacteria..." << endl;
            nigromante->crearFilacteria();
            
            cout << "Probando recepción de daño letal..." << endl;
            nigromante->recibirDanio(150, false); // Daño mayor que su HP para probar la filacteria
            
            cout << "Meditando..." << endl;
            nigromante->meditar();
            
            cout << "Información actualizada del nigromante:" << endl;
            nigromante->mostrarInfo();
        }
        cout << endl;
    }

    // 3.4 Prueba de Paladín
    {
        cout << "==== PRUEBA DE PALADÍN ====" << endl;
        auto paladin = dynamic_cast<Paladin*>(personajesTest[3].get());
        if (paladin) {
            cout << "Probando habilidades del paladín " << paladin->getNombre() << "..." << endl;
            
            cout << "Invocando luz sagrada..." << endl;
            int poderLuz = paladin->invocarLuzSagrada();
            cout << "Poder de la luz sagrada: " << poderLuz << endl;
            
            cout << "Castigando malvados..." << endl;
            int dañoCastigo = paladin->castigarMalvados();
            cout << "Daño del castigo: " << dañoCastigo << endl;
            
            cout << "Imponiendo manos para curar..." << endl;
            int curacionManos = paladin->imponerManos("Aliado herido");
            cout << "Curación realizada: " << curacionManos << endl;
            
            cout << "Rezando para recuperar fe..." << endl;
            paladin->rezar();
            
            cout << "Activando aura divina..." << endl;
            paladin->activarAuraDivina();
            
            cout << "Probando recepción de daño con aura divina activa..." << endl;
            paladin->recibirDanio(25, false);
            
            cout << "Curando heridas..." << endl;
            paladin->curar(15);
            
            cout << "Información actualizada del paladín:" << endl;
            paladin->mostrarInfo();
        }
        cout << endl;
    }

    // 4. PRUEBA DE MANIPULACIÓN DE INVENTARIO Y ARMAS
    cout << ">> Prueba de manipulación de inventario:" << endl;
    {
        cout << "Equipando y manipulando armas del personaje " << personajesTest[0]->getNombre() << endl;
        auto& personaje = personajesTest[0];
        
        // Mostrar inventario inicial
        personaje->mostrarInventario();
        
        // Agregar un arma nueva
        cout << "Añadiendo un arma nueva..." << endl;
        personaje->agregarArma(crearEspada());
        
        // Mostrar inventario actualizado
        personaje->mostrarInventario();
        
        // Quitar un arma
        cout << "Quitando arma en posición 0..." << endl;
        auto armaQuitada = personaje->quitarArma(0);
        cout << "Arma quitada: " << (armaQuitada ? armaQuitada->getNombre() : "Ninguna") << endl;
        
        // Mostrar inventario después de quitar
        personaje->mostrarInventario();
        
        // Añadir otra arma diferente
        cout << "Añadiendo otra arma nueva..." << endl;
        personaje->agregarArma(crearPocion());
        
        // Añadir el arma quitada de vuelta
        cout << "Añadiendo el arma original de vuelta..." << endl;
        if (armaQuitada) {
            personaje->agregarArma(move(armaQuitada));
        }
        
        // Mostrar inventario final
        personaje->mostrarInventario();
    }
    cout << endl;

    cout << "===== PRUEBAS DE PERSONAJES COMPLETADAS =====" << endl;
    pausar();
}

/**
 * @brief Implementa pruebas de interacción y combate entre personajes
 * 
 * Simula un combate por turnos entre personajes, demuestra el intercambio
 * de armas entre ellos, la creación de armas nuevas durante la ejecución,
 * y el uso de habilidades especiales en un contexto de combate.
 */
void probarInteracciones() {
    limpiarPantalla();
    cout << "===== SIMULADOR DE COMBATE E INTERACCIONES ENTRE PERSONAJES =====" << endl << endl;

    // 1. CREAR PERSONAJES PARA EL COMBATE
    cout << ">> Creando personajes para el combate..." << endl;
    auto mago = crearHechicero();
    auto guerrero = crearBarbaro();
    auto nigromante = crearNigromante();
    auto paladin = crearPaladin();
    
    vector<InterfazPersonaje*> participantes = {
        mago.get(), guerrero.get(), nigromante.get(), paladin.get()
    };
    
    cout << "Se han creado " << participantes.size() << " personajes para el combate." << endl << endl;
    
    // 2. MOSTRAR INFORMACIÓN INICIAL DE LOS PARTICIPANTES
    cout << ">> Información inicial de los combatientes:" << endl;
    for (auto personaje : participantes) {
        cout << "----------------------------------------" << endl;
        cout << "Nombre: " << personaje->getNombre() << endl;
        cout << "HP: " << personaje->getHP() << endl;
        personaje->mostrarInventario();
    }
    cout << "----------------------------------------" << endl << endl;
    
    // 3. PROBAR INTERCAMBIO DE ARMAS
    cout << ">> Intercambio de armas entre personajes:" << endl;
    
    cout << "Quitando un arma al guerrero..." << endl;
    auto armaGuerrero = guerrero->quitarArma(0);
    cout << "Arma quitada: " << (armaGuerrero ? armaGuerrero->getNombre() : "Ninguna") << endl;
    
    cout << "Quitando un arma al paladín..." << endl;
    auto armaPaladin = paladin->quitarArma(0);
    cout << "Arma quitada: " << (armaPaladin ? armaPaladin->getNombre() : "Ninguna") << endl;
    
    cout << "Dando el arma del guerrero al paladín..." << endl;
    if (armaGuerrero) {
        paladin->agregarArma(move(armaGuerrero));
    }
    
    cout << "Dando el arma del paladín al guerrero..." << endl;
    if (armaPaladin) {
        guerrero->agregarArma(move(armaPaladin));
    }
    
    cout << "Inventarios después del intercambio:" << endl;
    guerrero->mostrarInventario();
    paladin->mostrarInventario();
    cout << endl;
    
    // 4. CREAR NUEVAS ARMAS Y ASIGNARLAS
    cout << ">> Creando nuevas armas para los personajes:" << endl;
    
    cout << "Creando un báculo poderoso para el mago..." << endl;
    auto baculoPoderoso = make_unique<Baston>(
        "Báculo del Poder Arcano", 35, 60, 1.8, Rarity::Epico,
        50, TipoMadera::Ebano, TipoGema::Diamante, 5, ElementoMagico::Arcano
    );
    baculoPoderoso->mostrarInfo();
    
    cout << "Asignando el báculo al mago..." << endl;
    mago->agregarArma(move(baculoPoderoso));
    
    cout << "Creando un garrote para el guerrero..." << endl;
    auto garrotePesado = make_unique<Garrote>(
        "Garrote Demoledor", 25, 40, 4.5, Rarity::Raro,
        4, TipoMadera::Roble, true, 25.0, 8, OrigenGarrote::HuesoGrande
    );
    garrotePesado->mostrarInfo();
    
    cout << "Asignando el garrote al guerrero..." << endl;
    guerrero->agregarArma(move(garrotePesado));
    cout << endl;
    
    // 5. SIMULACIÓN DE COMBATE
    cout << "===== INICIO DEL COMBATE POR TURNOS =====" << endl;
    
    // Preparar HP para el combate
    for (auto personaje : participantes) {
        personaje->setHPParaCombatePPT();
    }
    
    const int RONDAS_TOTALES = 5;
    MovimientoCombate movimientos[] = {
        MovimientoCombate::GolpeFuerte, 
        MovimientoCombate::GolpeRapido, 
        MovimientoCombate::DefensaYGolpe
    };
    
    for (int ronda = 1; ronda <= RONDAS_TOTALES; ++ronda) {
        cout << "\n>> RONDA " << ronda << " <<" << endl;
        
        // Cada personaje ataca al siguiente en la lista
        for (size_t i = 0; i < participantes.size(); ++i) {
            auto atacante = participantes[i];
            auto defensor = participantes[(i + 1) % participantes.size()];
            
            // Elegir un movimiento aleatorio para el atacante
            MovimientoCombate movimiento = movimientos[rand() % 3];
            
            cout << "\n" << atacante->getNombre() << " (" << atacante->getHP() << " HP) ataca a " 
                 << defensor->getNombre() << " (" << defensor->getHP() << " HP)" << endl;
            
            cout << "Usando " << movimientoCombateToString(movimiento) << endl;
            int danio = atacante->atacar(movimiento);
            
            if (danio > 0) {
                cout << "¡Golpe efectivo! Causando " << danio << " puntos de daño." << endl;
                defensor->recibirDanio(danio, false);
                cout << defensor->getNombre() << " queda con " << defensor->getHP() << " HP." << endl;
            } else {
                cout << "¡El ataque no tuvo efecto!" << endl;
            }
        }
        
        // Mostrar estado después de la ronda
        cout << "\nEstado después de la ronda " << ronda << ":" << endl;
        for (auto personaje : participantes) {
            cout << "- " << personaje->getNombre() << ": " << personaje->getHP() << " HP" << endl;
        }
    }
    
    // Restaurar HP original
    for (auto personaje : participantes) {
        personaje->restaurarHPOriginal();
    }
    
    cout << "\n===== COMBATE FINALIZADO =====" << endl;
    
    // 6. PRUEBA DE INTERACCIÓN DE HABILIDADES ESPECIALES
    cout << "\n>> Prueba de interacciones con habilidades especiales:" << endl;
    
    cout << "El hechicero lanza un hechizo potenciado por su báculo:" << endl;
    auto hechicero = dynamic_cast<Hechicero*>(mago.get());
    if (hechicero) {
        hechicero->aprenderHechizo("Meteoro");
        hechicero->invocarFamiliar();
        int danioHechizo = hechicero->lanzarHechizo("Meteoro");
        cout << "El hechizo causa " << danioHechizo << " puntos de daño!" << endl;
    }
    
    cout << "\nEl bárbaro entra en frenesí y ataca:" << endl;
    auto barbaro = dynamic_cast<Barbaro*>(guerrero.get());
    if (barbaro) {
        barbaro->entrarEnFrenesi();
        int danioBarbaro = barbaro->golpeSalvaje();
        cout << "El ataque salvaje causa " << danioBarbaro << " puntos de daño!" << endl;
    }
    
    cout << "\nEl nigromante levanta un no-muerto:" << endl;
    auto nigro = dynamic_cast<Nigromante*>(nigromante.get());
    if (nigro) {
        int poderNoMuerto = nigro->levantarNoMuerto("Esqueleto Oscuro");
        cout << "El no-muerto tiene " << poderNoMuerto << " puntos de poder!" << endl;
        nigro->tocoDeLaMuerte();
    }
    
    cout << "\nEl paladín invoca luz sagrada:" << endl;
    auto pala = dynamic_cast<Paladin*>(paladin.get());
    if (pala) {
        pala->activarAuraDivina();
        int poderLuz = pala->invocarLuzSagrada();
        cout << "La luz sagrada causa " << poderLuz << " puntos de daño a los malvados!" << endl;
    }
    
    cout << "\n===== PRUEBAS DE INTERACCIÓN COMPLETADAS =====" << endl;
    pausar();
}