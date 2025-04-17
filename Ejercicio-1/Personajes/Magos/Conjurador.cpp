#include "Conjurador.hpp"
#include <algorithm>

/**
 * @brief Implementación del constructor de Conjurador
 * 
 * Inicializa un conjurador con sus atributos básicos heredados de Mago
 * y sus atributos específicos como poder de invocación, círculo de protección,
 * energía elemental y pacto actual. Si se proporciona un pacto inicial,
 * lo añade a la lista de criaturas pactadas.
 */
Conjurador::Conjurador(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
                       int manaMax, EscuelaMagia esc, FuentePoder fp, 
                       int poderInv, bool circulo, int energiaElem, string pacto)
    : Mago(n, nivel, hp, r, fue, des, con, inte, manaMax, esc, fp),
      poderInvocacion(poderInv), circuloProteccion(circulo), energiaElemental(energiaElem), pactoActual(pacto) {
    
    if (!pactoActual.empty()) {
        criaturasPactadas.push_back(pactoActual);
    }
}

/**
 * @brief Implementación del método realizarPacto
 * 
 * Establece un nuevo pacto místico con una criatura, añadiéndola
 * a la lista de criaturas pactadas y estableciéndola como pacto actual.
 * Requiere gastar maná.
 * 
 * @param nombreCriatura Nombre de la criatura para el pacto
 * @return true si se realiza el pacto, false si ya existía o faltó maná
 */
bool Conjurador::realizarPacto(const string& nombreCriatura) {
    if (nombreCriatura.empty()) {
        cout << "No se puede realizar un pacto con una criatura sin nombre." << endl;
        return false;
    }
    
    if (find(criaturasPactadas.begin(), criaturasPactadas.end(), nombreCriatura) != criaturasPactadas.end()) {
        cout << nombre << " ya tiene un pacto con " << nombreCriatura << "." << endl;
        return false;
    }
    
    int costoMana = 20;
    if (!gastarMana(costoMana)) {
        return false;
    }
    
    criaturasPactadas.push_back(nombreCriatura);
    pactoActual = nombreCriatura;
    
    cout << nombre << " realiza un pacto místico con " << nombreCriatura << "." << endl;
    return true;
}

/**
 * @brief Implementación del método invocarCriatura
 * 
 * Invoca a una criatura pactada para que ataque a los enemigos.
 * Verifica que exista un pacto con la criatura y gasta maná.
 * 
 * @param nombreCriatura Nombre de la criatura a invocar
 * @return Valor numérico que representa el daño causado por la criatura
 */
int Conjurador::invocarCriatura(const string& nombreCriatura) {
    if (find(criaturasPactadas.begin(), criaturasPactadas.end(), nombreCriatura) == criaturasPactadas.end()) {
        cout << nombre << " no tiene un pacto con " << nombreCriatura << "." << endl;
        return 0;
    }
    
    int costoMana = 15;
    if (!gastarMana(costoMana)) {
        return 0;
    }
    
    cout << nombre << " invoca a " << nombreCriatura << "!" << endl;
    
    int poderInvocado = poderInvocacion + inteligencia / 2 + nivelPersonaje;
    cout << nombreCriatura << " causa " << poderInvocado << " puntos de daño!" << endl;
    
    return poderInvocado;
}

/**
 * @brief Implementación del método dibujarCirculoProteccion
 * 
 * Crea un círculo mágico de protección alrededor del conjurador.
 * Requiere gastar maná y no tener ya un círculo activo.
 * 
 * @return true si se dibuja el círculo, false si ya existía o faltó maná
 */
bool Conjurador::dibujarCirculoProteccion() {
    if (circuloProteccion) {
        cout << "Ya hay un círculo de protección activo." << endl;
        return false;
    }
    
    int costoMana = 10;
    if (!gastarMana(costoMana)) {
        return false;
    }
    
    circuloProteccion = true;
    cout << nombre << " dibuja un círculo de protección mágica a su alrededor." << endl;
    return true;
}

/**
 * @brief Implementación del método canalizarElementos
 * 
 * Acumula energía elemental que puede ser utilizada para potenciar
 * hechizos o habilidades. Requiere gastar maná.
 */
void Conjurador::canalizarElementos() {
    cout << nombre << " comienza a canalizar energías elementales..." << endl;
    
    int costoMana = 8;
    if (!gastarMana(costoMana)) {
        return;
    }
    
    energiaElemental += 10 + inteligencia / 3;
    cout << nombre << " acumula energía elemental. Energía elemental total: " << energiaElemental << endl;
}

/**
 * @brief Implementación del método romperPacto
 * 
 * Rompe el pacto actual con una criatura de forma violenta,
 * liberando energía explosiva que causa daño. Consume toda
 * la energía elemental acumulada.
 * 
 * @return Valor numérico que representa el daño causado por la explosión
 */
int Conjurador::romperPacto() {
    if (pactoActual.empty()) {
        cout << nombre << " no tiene ningún pacto activo para romper." << endl;
        return 0;
    }
    
    cout << nombre << " rompe violentamente su pacto con " << pactoActual << "!" << endl;
    
    int explosionEnergia = poderInvocacion * 2 + energiaElemental;
    cout << "¡La ruptura del pacto libera " << explosionEnergia << " de energía explosiva!" << endl;
    
    // Remover la criatura de la lista
    auto it = find(criaturasPactadas.begin(), criaturasPactadas.end(), pactoActual);
    if (it != criaturasPactadas.end()) {
        criaturasPactadas.erase(it);
    }
    
    // Reiniciar variables
    pactoActual = "";
    energiaElemental = 0;
    
    return explosionEnergia;
}

/**
 * @brief Implementación del método mostrarInfo
 * 
 * Muestra información detallada sobre el conjurador y sus características
 * específicas, además de la información base de mago.
 */
void Conjurador::mostrarInfo() const {
    Mago::mostrarInfo(); // Llamamos al método de la clase base
    
    cout << "  Tipo: Conjurador" << endl;
    cout << "  Poder de Invocación: " << poderInvocacion << endl;
    cout << "  Círculo de Protección: " << (circuloProteccion ? "Activo" : "Inactivo") << endl;
    cout << "  Energía Elemental: " << energiaElemental << endl;
    cout << "  Pacto Actual: " << (pactoActual.empty() ? "Ninguno" : pactoActual) << endl;
    
    cout << "  Criaturas Pactadas: ";
    if (criaturasPactadas.empty()) {
        cout << "Ninguna" << endl;
    } else {
        cout << endl;
        for (const auto& criatura : criaturasPactadas) {
            cout << "    - " << criatura << endl;
        }
    }
}

/**
 * @brief Implementación especializada del método lanzarHechizo
 * 
 * Potencia los hechizos básicos con energía elemental acumulada,
 * consumiendo parte de esta energía en el proceso.
 * 
 * @param nombreHechizo Nombre del hechizo a lanzar
 * @return Valor numérico que representa el efecto del hechizo
 */
int Conjurador::lanzarHechizo(const string& nombreHechizo) {
    int danioBase = Mago::lanzarHechizo(nombreHechizo); // Llamamos al método base
    
    if (danioBase <= 0) return 0;
    
    // Bonus por energía elemental si hay suficiente
    if (energiaElemental >= 5) {
        int bonus = energiaElemental / 5;
        energiaElemental -= 5;
        
        cout << nombre << " canaliza energía elemental en el hechizo, añadiendo " << bonus << " al daño!" << endl;
        danioBase += bonus;
    }
    
    return danioBase;
}
