/**
 * @file main.cpp
 * @brief Programa principal del juego de combate Piedra-Papel-Tijera
 * 
 * Este archivo contiene el punto de entrada del programa y la lógica para
 * mostrar menús, configurar el juego y gestionar la interacción del usuario
 * con el sistema de combate.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "CombatePPT.hpp"

using namespace std;
bool usarDañoFijo = true;

/**
 * @brief Limpia la pantalla del terminal
 * 
 * Utiliza comandos específicos del sistema para limpiar la pantalla
 * del terminal, mejorando la experiencia del usuario.
 */
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Muestra un mensaje decorado con un borde
 * 
 * @param mensaje Texto a mostrar dentro del borde
 */
void bordeDecorado(const string& mensaje) {
    int ancho = mensaje.length() + 4;
    
    cout << "╔";
    for (int i = 0; i < ancho; i++) cout << "═";
    cout << "╗" << endl;
    
    cout << "║  " << mensaje << "  ║" << endl;
    
    cout << "╚";
    for (int i = 0; i < ancho; i++) cout << "═";
    cout << "╝" << endl;
}

/**
 * @brief Muestra el título del juego y las reglas
 */
void mostrarTitulo() {
    mostrarAsciiArt();
    
    cout << "\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║             \033[1;33m⚔️  BATALLA DE LEYENDAS  🛡️\033[0m             ║" << endl;
    cout << "╠════════════════════════════════════════════════════════╣" << endl;
    cout << "║ \033[1;32m➤\033[0m Golpe Fuerte \033[1;31m⚔️\033[0m vence a Golpe Rápido \033[1;36m🌪️\033[0m       ║" << endl;
    cout << "║ \033[1;32m➤\033[0m Golpe Rápido \033[1;36m🌪️\033[0m vence a Defensa y Golpe \033[1;34m🛡️\033[0m   ║" << endl;
    cout << "║ \033[1;32m➤\033[0m Defensa y Golpe \033[1;34m🛡️\033[0m vence a Golpe Fuerte \033[1;31m⚔️\033[0m   ║" << endl;
    
    if (usarDañoFijo) {
        cout << "║ \033[1;32m➤\033[0m El perdedor recibe siempre \033[1;31m10\033[0m puntos de daño    ║" << endl;
    } else {
        cout << "║ \033[1;32m➤\033[0m El perdedor recibe \033[1;31m10\033[0m puntos de daño + bonus    ║" << endl;
        cout << "║   según el arma utilizada                             ║" << endl;
    }
    
    cout << "║ \033[1;32m➤\033[0m Pierde el primero que se queda sin HP (\033[1;32m100\033[0m inicial) ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
}

/**
 * @brief Configura el sistema de daño del combate
 * 
 * Permite al usuario elegir entre usar un sistema de daño fijo
 * de 10 puntos por ataque, o incluir bonificaciones según el arma.
 */
void configurarCombate() {
    limpiarPantalla();
    bordeDecorado("CONFIGURACIÓN DEL SISTEMA DE COMBATE");
    cout << endl;
    
    cout << "Sistema de daño actual: " << 
        (usarDañoFijo ? "\033[1;34mDaño FIJO\033[0m (siempre 10 puntos)" : 
                       "\033[1;33mDaño CON BONIFICACIONES\033[0m de arma") << endl << endl;
    
    cout << "╔═══════════════════════════════════════════════════╗" << endl;
    cout << "║  Opciones disponibles:                            ║" << endl;
    cout << "║  \033[1;36m1.\033[0m Usar daño fijo (siempre 10 puntos)          ║" << endl;
    cout << "║  \033[1;36m2.\033[0m Usar daño base + bonificaciones según arma  ║" << endl;
    cout << "║  \033[1;36m0.\033[0m Volver sin cambios                          ║" << endl;
    cout << "╚═══════════════════════════════════════════════════╝" << endl;
    
    int opcion;
    cout << "\n\033[1;32m➤\033[0m Seleccione una opción: ";
    cin >> opcion;
    
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[1;31m✗ Entrada inválida. No se han realizado cambios.\033[0m" << endl;
    } else {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (opcion) {
            case 1:
                usarDañoFijo = true;
                cout << "\033[1;32m✓ Configuración establecida: DAÑO FIJO (10 puntos)\033[0m" << endl;
                break;
            case 2:
                usarDañoFijo = false;
                cout << "\033[1;32m✓ Configuración establecida: DAÑO CON BONIFICACIONES de arma\033[0m" << endl;
                break;
            case 0:
                cout << "\033[1;33m⚠ Configuración sin cambios.\033[0m" << endl;
                break;
            default:
                cout << "\033[1;31m✗ Opción inválida. No se han realizado cambios.\033[0m" << endl;
                break;
        }
    }
    
    cout << "\n\033[1;36m➤\033[0m Presione Enter para continuar...";
    cin.get();
}

/**
 * @brief Muestra el menú principal y obtiene la selección del usuario
 * @return Entero que representa la opción elegida por el usuario
 */
int mostrarMenuPrincipal() {
    limpiarPantalla();
    mostrarTitulo();
    
    cout << "\n╔═══════════════════════════════╗" << endl;
    cout << "║        \033[1;33mMENÚ PRINCIPAL\033[0m        ║" << endl;
    cout << "╠═══════════════════════════════╣" << endl;
    cout << "║  \033[1;36m1.\033[0m Iniciar Nuevo Combate     ║" << endl;
    cout << "║  \033[1;36m2.\033[0m Configurar Sistema de Daño║" << endl;
    cout << "║  \033[1;36m0.\033[0m Salir                     ║" << endl;
    cout << "╚═══════════════════════════════╝" << endl;
    
    int opcion;
    while (true) {
        cout << "\n\033[1;32m➤\033[0m Seleccione una opción (0-2): ";
        cin >> opcion;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[1;31m✗ Entrada inválida. Intente de nuevo.\033[0m" << endl;
        } else if (opcion >= 0 && opcion <= 2) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return opcion;
        } else {
            cout << "\033[1;31m✗ Opción fuera de rango. Intente de nuevo.\033[0m" << endl;
        }
    }
}

/**
 * @brief Muestra los créditos finales del juego
 */
void mostrarCreditos() {
    limpiarPantalla();
    mostrarAsciiArt();
    
    cout << "\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║              \033[1;33mGRACIAS POR JUGAR\033[0m                   ║" << endl;
    cout << "╠════════════════════════════════════════════════════════╣" << endl;
    cout << "║         Desarrollado por Axel David Palavecino         ║" << endl;
    cout << "║                                                        ║" << endl;
    cout << "║          ¡Esperamos que lo hayas disfrutado!           ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
}

/**
 * @brief Función principal del programa
 * 
 * Muestra el menú principal y gestiona las diferentes opciones,
 * incluyendo iniciar combate, configurar el sistema y salir del juego.
 * 
 * @return 0 si el programa finaliza correctamente
 */
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    while (true) {
        int opcion = mostrarMenuPrincipal();
        
        if (opcion == 0) {
            mostrarCreditos();
            cout << "\n\033[1;36m➤\033[0m Presione Enter para finalizar...";
            cin.get();
            break;
        } else if (opcion == 2) {
            configurarCombate();
            continue;
        }
        
        limpiarPantalla();
        CombatePPT combate(true, usarDañoFijo);
        
        if (!combate.inicializar()) {
            cout << "\033[1;31m✗ Error al inicializar el combate. Volviendo al menú principal...\033[0m" << endl;
            cout << "\n\033[1;36m➤\033[0m Presione Enter para continuar...";
            cin.get();
            continue;
        }
        
        while (!combate.haTerminado()) {
            limpiarPantalla();
            if (!combate.ejecutarTurno()) {
                break;
            }
        }
        limpiarPantalla();
        combate.mostrarResultado();
        
        cout << "\n\033[1;36m➤\033[0m Presione Enter para volver al menú principal...";
        cin.get();
    }
    
    return 0;
}

/**
 * @brief Muestra em ASCII Art decorativo el titulo de la Universidad de San Andres
 */
void mostrarAsciiArt() {
    cout << "\n\033[1;36m";
    cout << " _   _     _      ___     _   " << endl;
    cout << "| | | | __| | ___/ __|   / \\  " << endl;
    cout << "| | | |/ _` |/ _ \\__ \\  / _ \\ " << endl;
    cout << "| |_| | (_| |  __/___) / ___ \\" << endl;
    cout << " \\___/ \\__,_|\\___|____/_/   \\_\\" << endl;
    cout << "\033[0m\n";
}
