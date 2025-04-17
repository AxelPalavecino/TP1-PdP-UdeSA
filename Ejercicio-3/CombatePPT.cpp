/**
 * @file CombatePPT.cpp
 * @brief Implementación de la clase CombatePPT para el sistema de combate Piedra-Papel-Tijera
 * 
 * Este archivo contiene la implementación de la clase CombatePPT definida en CombatePPT.hpp,
 * que gestiona todo el sistema de combate por turnos basado en el juego Piedra-Papel-Tijera.
 */

#include "CombatePPT.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <typeinfo>

using namespace std;

/**
 * @brief Implementación del constructor de CombatePPT
 * 
 * Inicializa los atributos de la clase y la semilla para números aleatorios.
 * 
 * @param configManual Indica si el usuario selecciona manualmente su personaje
 * @param usarDañoFijo Indica si se usa siempre 10 puntos de daño fijo
 */
CombatePPT::CombatePPT(bool configManual, bool usarDañoFijo)
    : jugador1(nullptr), jugador2(nullptr), 
      combateTerminado(false), configManual(configManual),
      usarDañoFijo(usarDañoFijo) {
    // Inicializar la semilla para números aleatorios
    srand(static_cast<unsigned int>(time(nullptr)));
}

/**
 * @brief Implementación del destructor de CombatePPT
 * 
 * Restaura el HP original de los personajes y libera la memoria.
 */
CombatePPT::~CombatePPT() {
    // Restaurar HP original antes de destruir
    restablecerEstadoOriginal();
    
    // Liberar memoria
    delete jugador1;
    delete jugador2;
}

/**
 * @brief Implementación del método prepararPersonajeParaCombate
 * 
 * Establece el HP del personaje a 100 para el modo de combate PPT.
 * 
 * @param personaje Puntero compartido al personaje a preparar
 */
void CombatePPT::prepararPersonajeParaCombate(shared_ptr<InterfazPersonaje>& personaje) {
    cout << "Preparando a " << personaje->getNombre() << " para combate PPT..." << endl;
    cout << "HP antes: " << personaje->getHP() << endl;
    
    bool resultado = personaje->setHPParaCombatePPT();
    
    if (resultado) {
        cout << "HP después (debe ser 100): " << personaje->getHP() << endl;
    } else {
        cout << "Error al establecer HP para combate. HP actual: " << personaje->getHP() << endl;
    }
}

/**
 * @brief Implementación del método inicializar
 * 
 * Configura los personajes para el combate y los prepara estableciendo su HP a 100.
 * Muestra una animación de cuenta regresiva antes de comenzar.
 * 
 * @return true si la inicialización fue exitosa, false en caso contrario
 */
bool CombatePPT::inicializar() {
    try {
        // Configurar personajes según la preferencia
        if (configManual) {
            configurarJugador1();
        } else {
            // Configuración automática del jugador 1
            auto personaje = PersonajeFactory::crearPersonajeModoCombtePPT(TipoPersonaje::Caballero, 1);
            auto arma = personaje->getArma(0);
            jugador1 = new Combatiente(personaje, arma);
        }
        
        configurarJugador2();

        // Establecer HP exactamente a 100 usando el método específico
        cout << "\n╔═══════════════════════════════════════╗" << endl;
        cout << "║     PREPARANDO COMBATIENTES            ║" << endl;
        cout << "╚═══════════════════════════════════════╝" << endl;
        prepararPersonajeParaCombate(jugador1->personaje);
        prepararPersonajeParaCombate(jugador2->personaje);
        
        // Animación de cuenta regresiva
        cout << "\n\033[1;33m¡PREPARANDO COMBATE!\033[0m" << endl;
        for (int i = 3; i > 0; i--) {
            cout << "\r\033[1;31m" << i << "...\033[0m" << flush;
            this_thread::sleep_for(chrono::milliseconds(800));
        }
        cout << "\r\033[1;32m¡LUCHA!\033[0m     " << endl;
        this_thread::sleep_for(chrono::milliseconds(800));

        cout << "\nPresione Enter para comenzar el combate...";
        cin.get();
        
        return true;
    } catch (const exception& e) {
        cerr << "\033[1;31m✗ Error al inicializar el combate: " << e.what() << "\033[0m" << endl;
        return false;
    }
}

/**
 * @brief Implementación del método ejecutarTurno
 * 
 * Ejecuta un turno completo del combate: muestra el estado actual,
 * obtiene las elecciones de los jugadores, resuelve el enfrentamiento
 * y aplica el daño correspondiente.
 * 
 * @return true si el turno se completó correctamente, false en caso contrario
 */
bool CombatePPT::ejecutarTurno() {
    if (haTerminado()) return false;
    
    // Mostrar estado actual
    mostrarEstadoActual();
    
    // Obtener elección del jugador 1 (usuario)
    OpcionAtaque opcionJ1 = obtenerEleccionJugador();
    
    // Generar elección aleatoria para jugador 2 (IA)
    OpcionAtaque opcionJ2 = generarEleccionAleatoria();
    
    // Mostrar elecciones
    cout << "\n" << jugador1->personaje->getNombre() << " elige: " 
         << dibujarIconoMovimiento(opcionJ1) << endl;
    cout << jugador2->personaje->getNombre() << " elige: " 
         << dibujarIconoMovimiento(opcionJ2) << endl;
    
    // Resolver el enfrentamiento
    if (opcionJ1 == opcionJ2) {
        cout << "\n\033[1;33m¡Ambos eligieron la misma opción! No hay daño.\033[0m" << endl;
    } else if (resolverEnfrentamiento(opcionJ1, opcionJ2)) {
        // Jugador 1 gana
        aplicarDanio(*jugador1, *jugador2, opcionJ1);
    } else {
        // Jugador 2 gana
        aplicarDanio(*jugador2, *jugador1, opcionJ2);
    }
    
    // Verificar si ha terminado el combate
    if (jugador1->personaje->getHP() <= 0 || jugador2->personaje->getHP() <= 0) {
        combateTerminado = true;
    }
    
    // Esperar a que el usuario presione Enter para continuar
    cout << "\n\033[1;36m➤\033[0m Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return true;
}

/**
 * @brief Implementación del método obtenerEleccionJugador
 * 
 * Solicita al usuario que elija una opción de ataque y valida la entrada.
 * 
 * @return Opción de ataque elegida por el usuario
 */
OpcionAtaque CombatePPT::obtenerEleccionJugador() const {
    int eleccion;
    bool entradaValida = false;
    
    while (!entradaValida) {
        cout << "╔══════════════════════════════════════════════╗" << endl;
        cout << "║          \033[1;36mELIGE TU MOVIMIENTO\033[0m              ║" << endl;
        cout << "║                                              ║" << endl;
        cout << "║  \033[1;31m1. ⚔️  Golpe Fuerte\033[0m                       ║" << endl;
        cout << "║  \033[1;36m2. 🌪️  Golpe Rápido\033[0m                       ║" << endl;
        cout << "║  \033[1;34m3. 🛡️  Defensa y Golpe\033[0m                    ║" << endl;
        cout << "╚══════════════════════════════════════════════╝" << endl;
        
        cout << "\n\033[1;32m➤\033[0m Tu elección: ";
        cin >> eleccion;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[1;31m✗ Entrada inválida. Intente de nuevo.\033[0m\n" << endl;
        } else if (eleccion >= 1 && eleccion <= 3) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            entradaValida = true;
        } else {
            cout << "\033[1;31m✗ Opción fuera de rango. Intente de nuevo.\033[0m\n" << endl;
        }
    }
    
    return static_cast<OpcionAtaque>(eleccion);
}

/**
 * @brief Implementación del método generarEleccionAleatoria
 * 
 * Genera una elección aleatoria para el jugador controlado por la IA.
 * 
 * @return Opción de ataque generada aleatoriamente
 */
OpcionAtaque CombatePPT::generarEleccionAleatoria() const {
    // Generar un número aleatorio entre 1 y 3
    return static_cast<OpcionAtaque>(rand() % 3 + 1);
}

/**
 * @brief Implementación del método resolverEnfrentamiento
 * 
 * Implementa la lógica piedra-papel-tijera para determinar el ganador:
 * - Golpe Fuerte vence a Golpe Rápido
 * - Golpe Rápido vence a Defensa y Golpe
 * - Defensa y Golpe vence a Golpe Fuerte
 * 
 * @param op1 Opción elegida por el jugador 1
 * @param op2 Opción elegida por el jugador 2
 * @return true si gana el jugador 1, false si gana el jugador 2
 */
bool CombatePPT::resolverEnfrentamiento(OpcionAtaque op1, OpcionAtaque op2) const {
    // Implementar lógica piedra-papel-tijera
    if (op1 == OpcionAtaque::GolpeFuerte && op2 == OpcionAtaque::GolpeRapido)
        return true;  // Golpe Fuerte gana a Golpe Rápido
    
    if (op1 == OpcionAtaque::GolpeRapido && op2 == OpcionAtaque::DefensaYGolpe)
        return true;  // Golpe Rápido gana a Defensa y Golpe
    
    if (op1 == OpcionAtaque::DefensaYGolpe && op2 == OpcionAtaque::GolpeFuerte)
        return true;  // Defensa y Golpe gana a Golpe Fuerte
    
    return false;  // En cualquier otro caso, el jugador 1 pierde
}

/**
 * @brief Implementación del método aplicarDanio
 * 
 * Calcula el daño a aplicar al perdedor, muestra una animación de ataque
 * y actualiza el HP del perdedor.
 * 
 * @param ganador Combatiente que ganó el enfrentamiento
 * @param perdedor Combatiente que perdió el enfrentamiento
 * @param opGanadora Opción de ataque utilizada por el ganador
 */
void CombatePPT::aplicarDanio(Combatiente& ganador, Combatiente& perdedor, OpcionAtaque opGanadora) {
    // Daño base según las reglas
    int danio = 10;
    int bonusDanio = 0;
    
    // Solo agregar bonus si no estamos usando daño fijo
    if (!usarDañoFijo) {
        // Añadir bonus de daño del arma
        bonusDanio = ganador.arma->usar() / 10; // Usar un valor reducido del arma
    }
    
    // Total de daño a aplicar
    int danioTotal = danio + bonusDanio;
    
    // Animación simple de golpe
    cout << "\n╔═══════════════════════════════════════════════╗" << endl;
    cout << "║              \033[1;31m¡GOLPE EFECTIVO!\033[0m              ║" << endl;
    cout << "╚═══════════════════════════════════════════════╝\n" << endl;
    
    // Descripción del ataque con colores
    cout << "\033[1;32m" << ganador.personaje->getNombre() << "\033[0m usa "
         << "\033[1;33m" << opcionAtaqueToString(opGanadora) << "\033[0m con "
         << "\033[1;36m" << ganador.arma->getNombre() << "\033[0m" << endl;
    
    // Animación de ataque
    string ataqueAnim[] = {"⚔️   ", " ⚔️  ", "  ⚔️ ", "   ⚔️", "    ", "   💥", "  💥 ", " 💥  ", "💥   "};
    for (const auto& frame : ataqueAnim) {
        cout << "\r" << frame << flush;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << endl;
    
    // Aplicar daño al perdedor pasando el parámetro usarDañoFijo como esCombatePPT
    perdedor.personaje->recibirDanio(danioTotal, usarDañoFijo);
    
    // Mostrar información del daño
    cout << "\n\033[1;31m✗ " << perdedor.personaje->getNombre() << " recibe " << danioTotal 
         << " puntos de daño!\033[0m" << endl;
    
    // Si estamos usando bonificaciones, mostrar el desglose
    if (!usarDañoFijo && bonusDanio > 0) {
        cout << "  \033[1;33m➤\033[0m Daño base: " << danio << endl;
        cout << "  \033[1;33m➤\033[0m Bonus del arma: +" << bonusDanio << endl;
    }
    
    // Mostrar barras de HP actualizadas
    cout << "\n\033[1;32m" << ganador.personaje->getNombre() << ":\033[0m HP " 
         << ganador.personaje->getHP() << "/100 " 
         << barraDeVida(ganador.personaje->getHP(), 100) << endl;
         
    cout << "\033[1;31m" << perdedor.personaje->getNombre() << ":\033[0m HP " 
         << perdedor.personaje->getHP() << "/100 " 
         << barraDeVida(perdedor.personaje->getHP(), 100) << endl;
}

/**
 * @brief Implementación del método haTerminado
 * 
 * @return true si el combate ha terminado, false en caso contrario
 */
bool CombatePPT::haTerminado() const {
    return combateTerminado;
}

/**
 * @brief Implementación del método opcionAtaqueToString
 * 
 * Convierte una opción de ataque a un texto descriptivo.
 * 
 * @param opcion Opción de ataque a convertir
 * @return String con el nombre de la opción
 */
string CombatePPT::opcionAtaqueToString(OpcionAtaque opcion) const {
    switch (opcion) {
        case OpcionAtaque::GolpeFuerte:
            return "Golpe Fuerte";
        case OpcionAtaque::GolpeRapido:
            return "Golpe Rápido";
        case OpcionAtaque::DefensaYGolpe:
            return "Defensa y Golpe";
        default:
            return "Desconocido";
    }
}

/**
 * @brief Implementación del método restablecerEstadoOriginal
 * 
 * Restaura el HP original de los personajes cuando el combate termina.
 */
void CombatePPT::restablecerEstadoOriginal() {
    if (jugador1 && jugador1->personaje) {
        jugador1->personaje->restaurarHPOriginal();
    }
    
    if (jugador2 && jugador2->personaje) {
        jugador2->personaje->restaurarHPOriginal();
    }
}

/**
 * @brief Implementación del método configurarJugador1
 * 
 * Permite al usuario seleccionar manualmente su personaje y arma.
 */
void CombatePPT::configurarJugador1() {
    cout << "╔═══════════════════════════════════════════════╗" << endl;
    cout << "║       \033[1;33mCONFIGURACIÓN DE PERSONAJE\033[0m         ║" << endl;
    cout << "╚═══════════════════════════════════════════════╝\n" << endl;
    
    // Mostrar opciones de tipo de personaje
    cout << "╔════════════════════════════════════╗" << endl;
    cout << "║   \033[1;36mSeleccione su personaje:\033[0m      ║" << endl;
    cout << "╠════════════════════════════════════╣" << endl;
    cout << "║  \033[1;35m1. Hechicero\033[0m                   ║" << endl; 
    cout << "║  \033[1;35m2. Conjurador\033[0m                  ║" << endl;
    cout << "║  \033[1;35m3. Brujo\033[0m                       ║" << endl;
    cout << "║  \033[1;35m4. Nigromante\033[0m                  ║" << endl;
    cout << "║  \033[1;31m5. Bárbaro\033[0m                     ║" << endl;
    cout << "║  \033[1;31m6. Paladín\033[0m                     ║" << endl;
    cout << "║  \033[1;31m7. Caballero\033[0m                   ║" << endl;
    cout << "║  \033[1;31m8. Mercenario\033[0m                  ║" << endl;
    cout << "║  \033[1;31m9. Gladiador\033[0m                   ║" << endl;
    cout << "╚════════════════════════════════════╝" << endl;
    
    // Solicitar elección
    int eleccionPersonaje;
    while (true) {
        cout << "\n\033[1;32m➤\033[0m Elija un personaje (1-9): ";
        cin >> eleccionPersonaje;
        
        if (cin.fail() || eleccionPersonaje < 1 || eleccionPersonaje > 9) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[1;31m✗ Opción inválida. Intente de nuevo.\033[0m" << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    
    // Convertir a TipoPersonaje
    TipoPersonaje tipo = static_cast<TipoPersonaje>(eleccionPersonaje - 1);
    
    // Crear personaje para combate PPT, pero con más armas para elegir
    auto personaje = PersonajeFactory::crearPersonajeModoCombtePPT(tipo, 0); // Sin armas iniciales
    
    // Determinar si es mago o guerrero para ofrecer armas apropiadas
    bool esMago = (tipo == TipoPersonaje::Hechicero || 
                  tipo == TipoPersonaje::Conjurador || 
                  tipo == TipoPersonaje::Brujo || 
                  tipo == TipoPersonaje::Nigromante);
    
    // Mostrar opciones de armas
    cout << "\n╔════════════════════════════════════╗" << endl;
    cout << "║   \033[1;36mSeleccione su arma:\033[0m          ║" << endl;
    cout << "╠════════════════════════════════════╣" << endl;
    
    if (esMago) {
        cout << "║  \033[1;35m1. Bastón Arcano\033[0m              ║" << endl;
        cout << "║  \033[1;35m2. Libro de Hechizos\033[0m          ║" << endl;
        cout << "║  \033[1;35m3. Amuleto Mágico\033[0m             ║" << endl;
        cout << "║  \033[1;35m4. Poción\033[0m                     ║" << endl;
    } else {
        cout << "║  \033[1;31m1. Espada\033[0m                     ║" << endl;
        cout << "║  \033[1;31m2. Hacha Doble\033[0m                ║" << endl;
        cout << "║  \033[1;31m3. Lanza\033[0m                      ║" << endl;
        cout << "║  \033[1;31m4. Garrote\033[0m                    ║" << endl;
    }
    cout << "╚════════════════════════════════════╝" << endl;
    
    // Solicitar elección de arma
    int eleccionArma;
    while (true) {
        cout << "\n\033[1;32m➤\033[0m Elija un arma (1-4): ";
        cin >> eleccionArma;
        
        if (cin.fail() || eleccionArma < 1 || eleccionArma > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[1;31m✗ Opción inválida. Intente de nuevo.\033[0m" << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    
    // Crear el arma elegida
    unique_ptr<InterfazArmas> armaElegida;
    
    if (esMago) {
        switch (eleccionArma) {
            case 1: // Bastón
                armaElegida = make_unique<Baston>(
                    "Bastón Arcano", 25, 100, 1.5, Rarity::Raro,
                    50, TipoMadera::Ebano, TipoGema::Rubi, 5, ElementoMagico::Arcano
                );
                break;
            case 2: // Libro de Hechizos
                {
                    auto libro = make_unique<LibroHechizos>(
                        "Grimorio Antiguo", 30, 100, 2.0, Rarity::Raro,
                        60, 300, IdiomaLibro::Antiguo, MaterialCubierta::Cuero
                    );
                    libro->aprenderHechizo("Bola de Fuego");
                    libro->aprenderHechizo("Rayo Arcano");
                    armaElegida = move(libro);
                }
                break;
            case 3: // Amuleto
                armaElegida = make_unique<Amuleto>(
                    "Amuleto de Poder", 20, 100, 0.1, Rarity::Epico,
                    40, "Inteligencia", 10, MaterialAmuleto::Oro, false
                );
                break;
            case 4: // Poción
                armaElegida = make_unique<Pocion>(
                    "Poción de Maná", 15, 100, 0.2, Rarity::PocoComun,
                    0, EfectoPocion::Mana, 30, 3, ColorPocion::Azul, false
                );
                break;
        }
    } else {
        switch (eleccionArma) {
            case 1: // Espada
                armaElegida = make_unique<Espada>(
                    "Espada de Acero", 30, 100, 1.5, Rarity::PocoComun,
                    8, TipoHojaEspada::Recta, MaterialGuarda::Acero, 0.9, 5, EstiloEsgrima::UnaMano
                );
                break;
            case 2: // Hacha Doble
                armaElegida = make_unique<HachaDoble>(
                    "Hacha de Guerra", 35, 100, 3.0, Rarity::Raro,
                    9, 1.0, 2, true, "Muerte a mis enemigos", 7
                );
                break;
            case 3: // Lanza
                armaElegida = make_unique<Lanza>(
                    "Lanza de Caballería", 25, 100, 2.0, Rarity::Comun,
                    7, 2.0, MaterialPuntaLanza::Acero, true, 3, false
                );
                break;
            case 4: // Garrote
                armaElegida = make_unique<Garrote>(
                    "Maza de Combate", 28, 100, 2.5, Rarity::Comun,
                    6, TipoMadera::Roble, true, 20.0, 6, OrigenGarrote::Improvisado
                );
                break;
        }
    }
    
    // Agregar el arma elegida al personaje y equiparla
    InterfazArmas* arma = armaElegida.get(); // Guardar puntero antes de transferir propiedad
    personaje->agregarArma(move(armaElegida));
    
    // Crear el combatiente
    jugador1 = new Combatiente(personaje, arma);
    
    // Mostrar información del personaje y arma elegidos
    cout << "\n\033[1;32m✓\033[0m ¡Personaje y arma configurados correctamente!" << endl;
    cout << "   Nombre: \033[1;36m" << personaje->getNombre() << "\033[0m" << endl;
    cout << "   Arma: \033[1;33m" << arma->getNombre() << "\033[0m" << endl;
    
    // Visualmente mostrar las stats del arma elegida
    cout << "\n\033[1;33m⚔️ Información del arma elegida:\033[0m" << endl;
    cout << "╔═══════════════════════════════════════╗" << endl;
    cout << "║  \033[1;36mNombre:\033[0m " << setw(25) << left << arma->getNombre() << "║" << endl;
    cout << "║  \033[1;36mPoder:\033[0m " << setw(26) << left << arma->getPoder() << "║" << endl;
    cout << "║  \033[1;36mDurabilidad:\033[0m " << setw(20) << left << arma->getDurabilidadActual() << "║" << endl;
    cout << "║  \033[1;36mRareza:\033[0m " << setw(25) << left << rarityToString(arma->getRareza()) << "║" << endl;
    cout << "╚═══════════════════════════════════════╝" << endl;
    
    // Esperar a que el usuario presione Enter
    cout << "\n\033[1;36m➤\033[0m Presione Enter para continuar...";
    cin.get();
}

/**
 * @brief Implementación del método configurarJugador2
 * 
 * Configura aleatoriamente el personaje y arma del jugador controlado por la IA.
 */
void CombatePPT::configurarJugador2() {
    // Obtener un número aleatorio entre 0 y 8 (9 tipos de personajes)
    int tipoAleatorio = rand() % 9;
    TipoPersonaje tipo = static_cast<TipoPersonaje>(tipoAleatorio);
    
    // Crear personaje con 1 arma usando el método específico para combate PPT
    auto personaje = PersonajeFactory::crearPersonajeModoCombtePPT(tipo, 1);
    
    // Usar la primera arma del personaje
    auto arma = personaje->getArma(0);
    
    // Crear el combatiente
    jugador2 = new Combatiente(personaje, arma);
    
    cout << "\n╔═══════════════════════════════════════╗" << endl;
    cout << "║        \033[1;33mOPONENTE ALEATORIO\033[0m        ║" << endl;
    cout << "╠═══════════════════════════════════════╣" << endl;
    cout << "║  Nombre: \033[1;36m" << setw(25) << left << personaje->getNombre() << "\033[0m ║" << endl;
    cout << "║  Arma: \033[1;33m" << setw(27) << left << arma->getNombre() << "\033[0m ║" << endl;
    cout << "╚═══════════════════════════════════════╝" << endl;
    
    // Esperar a que el usuario presione Enter
    cout << "\n\033[1;36m➤\033[0m Presione Enter para continuar...";
    cin.get();
}

/**
 * @brief Implementación del método setUsarDañoFijo
 * 
 * Establece si se debe usar daño fijo (10 puntos) o incluir bonificaciones del arma.
 * 
 * @param valor true para usar daño fijo, false para incluir bonificaciones
 */
void CombatePPT::setUsarDañoFijo(bool valor) {
    usarDañoFijo = valor;
    cout << (usarDañoFijo ? 
        "\033[1;32m✓ Se ha establecido daño fijo de 10 puntos para el combate.\033[0m" : 
        "\033[1;33m⚠ Se usarán bonificaciones de daño según el arma utilizada.\033[0m") << endl;
}

/**
 * @brief Implementación del método getUsarDañoFijo
 * 
 * @return true si se está usando daño fijo, false en caso contrario
 */
bool CombatePPT::getUsarDañoFijo() const {
    return usarDañoFijo;
}

// ==========================================================================
// MÉTODOS DE VISUALIZACIÓN
// ==========================================================================

/**
 * @brief Implementación del método mostrarEstadoActual
 * 
 * Muestra la información actual de los personajes y el combate.
 */
void CombatePPT::mostrarEstadoActual() const {
    cout << "\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║       \033[1;33m⚔️  COMBATE PIEDRA-PAPEL-TIJERA  ⚔️\033[0m        ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝\n" << endl;
    
    // Marco para el jugador 1
    cout << "╔═══════════════════════════════════════════════════════╗" << endl;
    cout << "║  " << dibujarIconoPersonaje(jugador1->personaje.get())
         << "\033[1;36mJUGADOR 1:\033[0m " << jugador1->personaje->getNombre() << setw(36 - jugador1->personaje->getNombre().length()) << " ║" << endl;
    cout << "║  HP: " << setw(3) << jugador1->personaje->getHP() << "/100 " 
         << barraDeVida(jugador1->personaje->getHP(), 100) << " ║" << endl;
    cout << "║  \033[1;33m➤\033[0m Arma: " << jugador1->arma->getNombre() 
         << setw(40 - jugador1->arma->getNombre().length()) << " ║" << endl;
    cout << "╚═══════════════════════════════════════════════════════╝" << endl;
    
    // Versus
    cout << "\n                      \033[1;31mVS\033[0m\n" << endl;
    
    // Marco para el jugador 2
    cout << "╔═══════════════════════════════════════════════════════╗" << endl;
    cout << "║  " << dibujarIconoPersonaje(jugador2->personaje.get())
         << "\033[1;36mJUGADOR 2:\033[0m " << jugador2->personaje->getNombre() << setw(36 - jugador2->personaje->getNombre().length()) << " ║" << endl;
    cout << "║  HP: " << setw(3) << jugador2->personaje->getHP() << "/100 " 
         << barraDeVida(jugador2->personaje->getHP(), 100) << " ║" << endl;
    cout << "║  \033[1;33m➤\033[0m Arma: " << jugador2->arma->getNombre() 
         << setw(40 - jugador2->arma->getNombre().length()) << " ║" << endl;
    cout << "╚═══════════════════════════════════════════════════════╝" << endl;
    
    cout << "\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║                   \033[1;33mELIGE TU MOVIMIENTO\033[0m              ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝\n" << endl;
}

/**
 * @brief Implementación del método mostrarResultado
 * 
 * Muestra el resultado final del combate con efectos visuales.
 */
void CombatePPT::mostrarResultado() const {
    cout << "\n╔═══════════════════════════════════════════════════════════╗" << endl;
    cout << "║                \033[1;33m🏆 FIN DEL COMBATE 🏆\033[0m                 ║" << endl;
    cout << "╚═══════════════════════════════════════════════════════════╝\n" << endl;
    
    // ASCII art de trofeo simple
    cout << "                      ___________" << endl;
    cout << "                     '._==_==_=_.'" << endl;
    cout << "                     .-\\:      /-." << endl;
    cout << "                    | (|:.     |) |" << endl;
    cout << "                     '-|:.     |-'" << endl;
    cout << "                       \\::.    /" << endl;
    cout << "                        '::. .'" << endl;
    cout << "                          ) (" << endl;
    cout << "                        _.' '._" << endl;
    cout << "                       `\"\"\"\"\"\"\"`" << endl << endl;
    
    if (jugador1->personaje->getHP() <= 0) {
        cout << "      \033[1;33m¡" << jugador2->personaje->getNombre() << " es el VENCEDOR!\033[0m" << endl;
        cout << "               El usuario ha caído en batalla." << endl << endl;
        
        // Mostrar barras de HP finales
        cout << "\033[1;31m" << jugador1->personaje->getNombre() << ":\033[0m HP " 
             << jugador1->personaje->getHP() << "/100 " 
             << barraDeVida(jugador1->personaje->getHP(), 100) << endl;
             
        cout << "\033[1;32m" << jugador2->personaje->getNombre() << ":\033[0m HP " 
             << jugador2->personaje->getHP() << "/100 " 
             << barraDeVida(jugador2->personaje->getHP(), 100) << endl;
    } else if (jugador2->personaje->getHP() <= 0) {
        cout << "      \033[1;33m¡" << jugador1->personaje->getNombre() << " es el VENCEDOR!\033[0m" << endl;
        cout << "           ¡Felicidades! Has ganado el combate." << endl << endl;
        
        // Mostrar barras de HP finales
        cout << "\033[1;32m" << jugador1->personaje->getNombre() << ":\033[0m HP " 
             << jugador1->personaje->getHP() << "/100 " 
             << barraDeVida(jugador1->personaje->getHP(), 100) << endl;
             
        cout << "\033[1;31m" << jugador2->personaje->getNombre() << ":\033[0m HP " 
             << jugador2->personaje->getHP() << "/100 " 
             << barraDeVida(jugador2->personaje->getHP(), 100) << endl;
    } else {
        cout << "               El combate ha terminado en empate." << endl;
    }
    
    cout << "\n╔═══════════════════════════════════════════════════════════╗" << endl;
    cout << "║                \033[1;36mESTADÍSTICAS FINALES\033[0m                 ║" << endl;
    cout << "╚═══════════════════════════════════════════════════════════╝" << endl;
}

/**
 * @brief Implementación del método dibujarIconoMovimiento
 * 
 * @param opcion Opción de ataque para la que generar el icono
 * @return String que representa visualmente el movimiento con color
 */
string CombatePPT::dibujarIconoMovimiento(OpcionAtaque opcion) const {
    switch (opcion) {
        case OpcionAtaque::GolpeFuerte:
            return "\033[1;31m⚔️  Golpe Fuerte\033[0m";
        case OpcionAtaque::GolpeRapido:
            return "\033[1;36m🌪️  Golpe Rápido\033[0m";
        case OpcionAtaque::DefensaYGolpe:
            return "\033[1;34m🛡️  Defensa y Golpe\033[0m";
        default:
            return "Desconocido";
    }
}

// ==========================================================================
// FUNCIONES AUXILIARES PARA VISUALIZACIÓN
// ==========================================================================

/**
 * @brief Implementación de la función barraDeVida
 * 
 * @param hpActual Valor actual de HP
 * @param hpMax Valor máximo de HP
 * @return String que representa visualmente la barra de vida con color
 */
string barraDeVida(int hpActual, int hpMax) {
    const int MAX_LONGITUD = 20;
    int longitud = (hpActual * MAX_LONGITUD) / hpMax;
    
    string barra = "[";
    for (int i = 0; i < MAX_LONGITUD; i++) {
        if (i < longitud) {
            // Diferentes colores según nivel de HP
            if (hpActual > hpMax * 0.7)
                barra += "\033[1;32m█\033[0m"; // Verde para HP alto
            else if (hpActual > hpMax * 0.3)
                barra += "\033[1;33m█\033[0m"; // Amarillo para HP medio
            else
                barra += "\033[1;31m█\033[0m"; // Rojo para HP bajo
        } else {
            barra += " ";
        }
    }
    barra += "]";
    
    return barra;
}

/**
 * @brief Implementación de la función dibujarIconoPersonaje
 * 
 * @param personaje Puntero al personaje para el que generar el icono
 * @return String que representa visualmente el tipo de personaje con color
 */
string dibujarIconoPersonaje(InterfazPersonaje* personaje) {
    // Detectar si es mago o guerrero por su nombre de clase
    string info = typeid(*personaje).name();
    bool esMago = (info.find("Hechicero") != string::npos || 
                  info.find("Brujo") != string::npos || 
                  info.find("Conjurador") != string::npos || 
                  info.find("Nigromante") != string::npos);
    
    if (esMago) {
        return "\033[1;35m⚕️  \033[0m"; // Símbolo para magos
    } else {
        return "\033[1;31m⚔️  \033[0m"; // Símbolo para guerreros
    }
}