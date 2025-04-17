#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "PersonajeFactory.hpp"

using namespace std;

/**
 * @brief Muestra información detallada sobre un personaje y su inventario
 * 
 * Imprime toda la información del personaje mediante sus métodos mostrarInfo()
 * y mostrarInventario(), separando la salida con encabezados.
 * 
 * @param personaje Puntero compartido al personaje del que se mostrará la información
 */
void mostrarInfoPersonaje(const shared_ptr<InterfazPersonaje>& personaje) {
    cout << "=== PERSONAJE ===" << endl;
    personaje->mostrarInfo();
    
    cout << "\n=== INVENTARIO ===" << endl;
    personaje->mostrarInventario();
    cout << endl;
}

/**
 * @brief Función principal del programa
 * 
 * Demuestra la funcionalidad de la clase PersonajeFactory creando diferentes
 * tipos de personajes y mostrando su información. También genera grupos
 * aleatorios de personajes y muestra estadísticas sobre ellos.
 * 
 * @return 0 si el programa termina correctamente
 */
int main() {
    cout << "===== EJERCICIO 2: CREACIÓN DINÁMICA DE PERSONAJES Y ARMAS =====" << endl << endl;
    
    cout << "Creando un caballero..." << endl;
    auto caballero = PersonajeFactory::crearPersonaje(TipoPersonaje::Caballero);
    mostrarInfoPersonaje(caballero);
    
    cout << "\n\nCreando un hechicero con 2 armas..." << endl;
    auto hechiceroArmado = PersonajeFactory::crearPersonajeArmado(TipoPersonaje::Hechicero, 2);
    mostrarInfoPersonaje(hechiceroArmado);
    
    // Demostrar la creación de un personaje en modo combate PPT (HP=100)
    cout << "\n\n===== DEMOSTRACIÓN DE PERSONAJE PARA COMBATE PPT =====" << endl;
    cout << "Creando un bárbaro para combate PPT con 1 arma..." << endl;
    auto barbaroCombatePPT = PersonajeFactory::crearPersonajeModoCombtePPT(TipoPersonaje::Barbaro, 1);
    cout << "HP establecido para combate PPT: " << barbaroCombatePPT->getHP() << " (debería ser 100)" << endl;
    mostrarInfoPersonaje(barbaroCombatePPT);
    
    cout << "\n\n===== GENERACIÓN DE GRUPOS ALEATORIOS =====" << endl;
    ResultadoGeneracion resultado = PersonajeFactory::generarGruposPersonajes();
    
    cout << "\nGenerados " << resultado.totalPersonajes << " personajes con un total de "
         << resultado.totalArmas << " armas." << endl;
    cout << "Magos: " << resultado.magos.size() << endl;
    cout << "Guerreros: " << resultado.guerreros.size() << endl;
    
    if (!resultado.magos.empty()) {
        cout << "\n=== EJEMPLO DE MAGO GENERADO ===" << endl;
        mostrarInfoPersonaje(resultado.magos[0]);
    }
    
    if (!resultado.guerreros.empty()) {
        cout << "\n=== EJEMPLO DE GUERRERO GENERADO ===" << endl;
        mostrarInfoPersonaje(resultado.guerreros[0]);
    }
    
    cout << "\n===== PROGRAMA FINALIZADO =====" << endl;
    
    return 0;
}
