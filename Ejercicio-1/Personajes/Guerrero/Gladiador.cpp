#include "Gladiador.hpp"
#include <algorithm>

/**
 * @brief Implementacion del constructor de Gladiador
 * 
 * Inicializa un gladiador con sus atributos basicos heredados de Guerrero
 * y sus atributos especificos como fama, victorias, derrotas, arena y título.
 */
Gladiador::Gladiador(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
                     int estMax, EstiloCombate est, TipoArmadura ta, int defBase, int resFis,
                     int fam, int vict, int derr, string arena, string tit)
    : Guerrero(n, nivel, hp, r, fue, des, con, inte, estMax, est, ta, defBase, resFis),
      fama(fam), victorias(vict), derrotas(derr), arenaPrincipal(arena), titulo(tit) {
    
    // Ajustes basados en la experiencia de arena
    int totalCombates = victorias + derrotas;
    if (totalCombates > 0) {
        resistenciaFisica += totalCombates / 5; // Cada 5 combates aumenta la resistencia
        destreza += victorias / 3; // Cada 3 victorias aumenta la destreza
    }
}

/**
 * @brief Implementacion del metodo ganarFama
 * 
 * Aumenta la fama del gladiador, lo que puede otorgar
 * beneficios en intimidacion y apoyo del publico.
 * 
 * @param cantidad Cantidad de fama a ganar
 */
void Gladiador::ganarFama(int cantidad) {
    if (cantidad <= 0) return;
    
    int famaAnterior = fama;
    fama += cantidad;
    
    cout << nombre << " ha ganado " << cantidad << " puntos de fama. Fama total: " << fama << endl;
    
    // Beneficios por alcanzar ciertos umbrales de fama
    if (famaAnterior < 50 && fama >= 50) {
        cout << "¡" << nombre << " ha alcanzado gran reconocimiento!" << endl;
        titulo = "el Reconocido " + titulo;
    } else if (famaAnterior < 100 && fama >= 100) {
        cout << "¡" << nombre << " se ha convertido en una celebridad!" << endl;
        titulo = "el Famoso " + titulo;
    }
}

/**
 * @brief Implementacion del metodo registrarVictoria
 * 
 * Registra una victoria en combate, aumentando el contador
 * y la fama del gladiador.
 * 
 * @return Cantidad de fama ganada por la victoria
 */
int Gladiador::registrarVictoria() {
    victorias++;
    
    cout << nombre << " ha conseguido su victoria número " << victorias << " en la arena!" << endl;
    
    // La fama ganada depende de victorias vs derrotas
    int famaGanada = 10;
    if (victorias > derrotas * 2) {
        famaGanada += 5; // Bonus por ser claramente dominante
    }
    
    ganarFama(famaGanada);
    return famaGanada;
}

/**
 * @brief Implementacion del metodo registrarDerrota
 * 
 * Registra una derrota en combate, aumentando el contador
 * y reduciendo ligeramente la fama del gladiador.
 */
void Gladiador::registrarDerrota() {
    derrotas++;
    
    cout << nombre << " ha sufrido su derrota número " << derrotas << " en la arena." << endl;
    
    // Pierde un poco de fama
    int famaPerdida = min(5, fama / 10);
    
    if (famaPerdida > 0) {
        fama -= famaPerdida;
        cout << nombre << " pierde " << famaPerdida << " puntos de fama. Fama actual: " << fama << endl;
    }
}

/**
 * @brief Implementacion del metodo aprenderTecnica
 * 
 * Añade una nueva tecnica especial al repertorio del gladiador,
 * verificando que no la conozca ya.
 * 
 * @param nombreTecnica Nombre de la tecnica a aprender
 * @return true si se aprendio la tecnica, false si ya la conocia
 */
bool Gladiador::aprenderTecnica(const string& nombreTecnica) {
    if (nombreTecnica.empty()) {
        cout << "No se puede aprender una técnica sin nombre." << endl;
        return false;
    }
    
    // Verifica si ya conoce la técnica
    if (find(tecnicasEspeciales.begin(), tecnicasEspeciales.end(), nombreTecnica) != tecnicasEspeciales.end()) {
        cout << nombre << " ya conoce la técnica \"" << nombreTecnica << "\"." << endl;
        return false;
    }
    
    tecnicasEspeciales.push_back(nombreTecnica);
    cout << nombre << " ha aprendido la técnica \"" << nombreTecnica << "\"." << endl;
    return true;
}

/**
 * @brief Implementacion del metodo usarTecnica
 * 
 * Permite al gladiador utilizar una de sus tecnicas especiales
 * en combate, causando daño basado en sus atributos.
 * Requiere gastar estamina.
 * 
 * @param nombreTecnica Nombre de la tecnica a utilizar
 * @return Valor numerico que representa el daño causado
 */
int Gladiador::usarTecnica(const string& nombreTecnica) {
    // Verifica si conoce la técnica
    auto it = find(tecnicasEspeciales.begin(), tecnicasEspeciales.end(), nombreTecnica);
    if (it == tecnicasEspeciales.end()) {
        cout << nombre << " no conoce la técnica \"" << nombreTecnica << "\"." << endl;
        return 0;
    }
    
    int costoEstamina = 15;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    cout << nombre << " ejecuta la técnica especial \"" << nombreTecnica << "\"!" << endl;
    
    // Daño basado en fuerza, nivel, destreza y posición de la técnica (más antiguas, más poderosas)
    int posicionTecnica = distance(tecnicasEspeciales.begin(), it);
    int danio = fuerza + nivelPersonaje + destreza / 2 + (tecnicasEspeciales.size() - posicionTecnica);
    
    cout << "La técnica causa " << danio << " puntos de daño!" << endl;
    
    // Gana algo de fama al usar técnicas espectaculares
    ganarFama(1);
    
    return danio;
}

/**
 * @brief Implementacion del metodo intimidar
 * 
 * El gladiador intenta intimidar al oponente usando su fama y presencia.
 * El efecto depende de su fama, nivel y cantidad de victorias.
 * Requiere gastar estamina.
 * 
 * @return Valor numerico que representa el efecto de intimidacion
 */
int Gladiador::intimidar() {
    cout << titulo << " " << nombre << " intenta intimidar al adversario..." << endl;
    
    int costoEstamina = 8;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    // El efecto depende de la fama, victorias y nivel
    int efectoIntimidacion = fama / 10 + victorias / 5 + nivelPersonaje / 3;
    
    cout << "La presencia intimidante de " << nombre << " afecta al oponente con un valor de " 
         << efectoIntimidacion << "." << endl;
    
    return efectoIntimidacion;
}

/**
 * @brief Implementacion del metodo saludarPublico
 * 
 * El gladiador saluda al publico para ganar su favor,
 * lo que aumenta su fama y puede proporcionar beneficios
 * en intimidacion y apoyo.
 * 
 * @return Cantidad de fama ganada por el saludo
 */
int Gladiador::saludarPublico() {
    cout << nombre << " saluda al público de la arena " << arenaPrincipal << "!" << endl;
    
    // La respuesta del público depende de la fama actual
    int respuestaPublico = min(10, max(1, fama / 20 + victorias / 10));
    
    if (respuestaPublico >= 8) {
        cout << "¡El público ruge de emoción!" << endl;
        recuperarEstamina(respuestaPublico); // Recupera estamina por el apoyo del público
    } else if (respuestaPublico >= 4) {
        cout << "El público aplaude con entusiasmo." << endl;
        recuperarEstamina(respuestaPublico / 2);
    } else {
        cout << "El público reconoce a " << nombre << " con algunos aplausos." << endl;
    }
    
    ganarFama(respuestaPublico / 2);
    return respuestaPublico / 2; // Retorna la fama ganada
}

/**
 * @brief Implementacion del metodo mostrarInfo
 * 
 * Muestra informacion detallada sobre el gladiador y sus caracteristicas
 * especificas, ademas de la informacion base de guerrero.
 */
void Gladiador::mostrarInfo() const {
    Guerrero::mostrarInfo();
    cout << "  Tipo: Gladiador" << endl;
    cout << "  Título: " << titulo << endl;
    cout << "  Fama: " << fama << endl;
    cout << "  Record: " << victorias << " victorias, " << derrotas << " derrotas" << endl;
    cout << "  Arena Principal: " << arenaPrincipal << endl;
    cout << "  Técnicas Especiales: " << tecnicasEspeciales.size() << endl;
    
    if (!tecnicasEspeciales.empty()) {
        cout << "    - ";
        for (size_t i = 0; i < tecnicasEspeciales.size(); ++i) {
            cout << tecnicasEspeciales[i] << (i == tecnicasEspeciales.size() - 1 ? "" : ", ");
        }
        cout << endl;
    }
}

/**
 * @brief Implementacion especializada del metodo atacar
 * 
 * Modifica el comportamiento base para añadir posibles bonificaciones
 * basadas en la fama y experiencia del gladiador.
 * 
 * @param movimiento Tipo de movimiento de ataque a realizar
 * @return Valor numerico que representa el daño causado
 */
int Gladiador::atacar(MovimientoCombate movimiento) {
    // Obtiene el daño base del método de la clase padre
    int danioBase = Guerrero::atacar(movimiento);
    
    // Bonus por experiencia en la arena
    if (danioBase > 0) {
        int bonusExperiencia = min(5, (victorias + derrotas) / 10);
        if (bonusExperiencia > 0) {
            cout << "La experiencia de arena añade " << bonusExperiencia << " al daño." << endl;
            danioBase += bonusExperiencia;
        }
    }
    
    return danioBase;
}
