#include "Caballero.hpp"

/**
 * @brief Implementacion del constructor de Caballero
 * 
 * Inicializa un caballero con sus atributos basicos heredados de Guerrero
 * y sus atributos especificos como honor, juramento, estado de montado,
 * habilidad ecuestre y orden de caballería. Añade bonus de defensa si usa
 * armadura pesada.
 */
Caballero::Caballero(string n, int nivel, int hp, Raza r, int fue, int des, int con, int inte,
                     int estMax, EstiloCombate est, TipoArmadura ta, int defBase, int resFis,
                     int hon, string jur, bool mont, int habEc, string ord)
    : Guerrero(n, nivel, hp, r, fue, des, con, inte, estMax, est, ta, defBase, resFis),
      honor(hon), juramento(jur), montado(mont), habilidadEcuestre(habEc), orden(ord) {
    
    // Bonus especial por ser caballero con armadura pesada
    if (tipoArmadura == TipoArmadura::Pesada) {
        defensaBase += 5;
    }
}

/**
 * @brief Implementacion del metodo ganarHonor
 * 
 * Aumenta los puntos de honor del caballero y otorga beneficios 
 * adicionales cuando alcanza ciertos umbrales.
 * 
 * @param cantidad Cantidad de honor a ganar
 */
void Caballero::ganarHonor(int cantidad) {
    if (cantidad <= 0) return;
    
    honor += cantidad;
    cout << nombre << " ha ganado " << cantidad << " puntos de honor. Honor total: " << honor << endl;
    
    // El honor podría dar algún beneficio adicional
    if (honor % 10 == 0) {
        cout << "¡" << nombre << " alcanza un nuevo umbral de honor!" << endl;
        defensaBase += 1;
        cout << "Defensa base aumentada a " << defensaBase << "." << endl;
    }
}

/**
 * @brief Implementacion del metodo perderHonor
 * 
 * Reduce los puntos de honor del caballero. Si el honor llega a cero,
 * el caballero sufre penalizaciones morales.
 * 
 * @param cantidad Cantidad de honor a perder
 */
void Caballero::perderHonor(int cantidad) {
    if (cantidad <= 0) return;
    
    int honorAnterior = honor;
    honor = max(0, honor - cantidad);
    
    cout << nombre << " ha perdido " << (honorAnterior - honor) << " puntos de honor. Honor actual: " << honor << endl;
    
    if (honor == 0) {
        cout << "¡" << nombre << " ha perdido todo su honor! Su espíritu está quebrantado." << endl;
        // Penalización moral
        int penalizacion = nivelPersonaje / 2;
        fuerza = max(1, fuerza - penalizacion);
        cout << "La fuerza de " << nombre << " se reduce a " << fuerza << " debido a la vergüenza." << endl;
    }
}

/**
 * @brief Implementacion del metodo cargarAcaballo
 * 
 * Realiza un ataque poderoso a caballo contra el enemigo.
 * Solo disponible si el caballero esta montado.
 * Requiere gastar estamina.
 * 
 * @return Valor numerico que representa el daño causado
 */
int Caballero::cargarAcaballo() {
    if (!montado) {
        cout << nombre << " no está montado y no puede realizar una carga a caballo." << endl;
        return 0;
    }
    
    cout << nombre << " carga a caballo contra el enemigo!" << endl;
    
    int costoEstamina = 15;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    // Daño basado en fuerza, habilidad ecuestre y nivel
    int danio = fuerza + habilidadEcuestre + nivelPersonaje / 2;
    cout << "¡La carga a caballo causa " << danio << " puntos de daño!" << endl;
    
    return danio;
}

/**
 * @brief Implementacion del metodo defenderAliado
 * 
 * El caballero se posiciona para proteger a un aliado, otorgando
 * un bonus de defensa basado en su propia defensa base y honor.
 * Requiere gastar estamina.
 * 
 * @param nombreAliado Nombre del aliado a defender
 * @return Valor numerico que representa el bonus de defensa otorgado
 */
int Caballero::defenderAliado(string nombreAliado) {
    cout << nombre << " se posiciona para defender a " << nombreAliado << "." << endl;
    
    int costoEstamina = 10;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    int bonusDefensa = defensaBase + honor / 5;
    cout << nombre << " proporciona " << bonusDefensa << " puntos de defensa a " << nombreAliado << "." << endl;
    
    // El heroísmo aumenta el honor
    ganarHonor(1);
    
    return bonusDefensa;
}

/**
 * @brief Implementacion del metodo juramentoSagrado
 * 
 * El caballero invoca su juramento personal, recibiendo un poderoso
 * efecto basado en su honor y nivel.
 * Requiere gastar estamina.
 * 
 * @return Valor numerico que representa el efecto del juramento
 */
int Caballero::juramentoSagrado() {
    cout << nombre << " invoca su juramento sagrado: \"" << juramento << "\"" << endl;
    
    int costoEstamina = 25;
    if (!gastarEstamina(costoEstamina)) {
        return 0;
    }
    
    // Efecto basado en honor y nivel
    int efecto = honor / 2 + nivelPersonaje * 2;
    cout << "El juramento sagrado fortalece a " << nombre << ", otorgándole +" << efecto << " a su próximo ataque." << endl;
    
    // El juramento sagrado fortalece el honor
    ganarHonor(3);
    
    return efecto;
}

/**
 * @brief Implementacion del metodo mostrarInfo
 * 
 * Muestra informacion detallada sobre el caballero y sus caracteristicas
 * especificas, ademas de la informacion base de guerrero.
 */
void Caballero::mostrarInfo() const {
    Guerrero::mostrarInfo();    
    cout << "  Tipo: Caballero" << endl;
    cout << "  Honor: " << honor << endl;
    cout << "  Juramento: \"" << juramento << "\"" << endl;
    cout << "  Montado: " << (montado ? "Sí" : "No") << endl;
    cout << "  Habilidad Ecuestre: " << habilidadEcuestre << endl;
    cout << "  Orden: " << orden << endl;
}

/**
 * @brief Implementacion especializada del metodo recibirDanio
 * 
 * Modifica el comportamiento base para aplicar posibles bonificaciones
 * defensivas especiales del caballero basadas en su honor o estado.
 * 
 * @param cantidad Cantidad de daño a recibir
 * @param esCombatePPT Indica si es un combate PPT
 * @return true si sigue vivo, false si ha muerto
 */
bool Caballero::recibirDanio(int cantidad, bool esCombatePPT) {
    if (!esCombatePPT) {
        // Posible reducción de daño basada en honor
        if (honor > 20 && cantidad > 0) {
            int reduccion = min(cantidad / 4, honor / 10);
            if (reduccion > 0) {
                cout << "El honor de " << nombre << " reduce el daño en " << reduccion << " puntos." << endl;
                cantidad -= reduccion;
            }
        }
    }
    return Guerrero::recibirDanio(cantidad, esCombatePPT);
}
