#include "ObjetoMagico.hpp"
#include <algorithm>
#include <stdexcept>

/**
 * @brief Constructor que inicializa un objeto mágico con propiedades básicas
 * 
 * Inicializa un objeto mágico verificando que los parámetros sean válidos.
 * Lanza excepciones si los valores no son apropiados.
 */
ObjetoMagico::ObjetoMagico(string n, int pm, int dm, double p, Rarity r, int eam) {
    if (n.empty()) {
        throw std::invalid_argument("El nombre no puede estar vacío.");
    }
    if (pm < 0) { 
        throw std::invalid_argument("El poder mágico no puede ser negativo.");
    }
    if (dm <= 0) {
        throw std::invalid_argument("La durabilidad máxima debe ser positiva.");
    }
    if (p < 0) {
        throw std::invalid_argument("El peso no puede ser negativo.");
    }
    if (eam < 0) {
        throw std::invalid_argument("La energía arcana máxima no puede ser negativa.");
    }
    nombre = n;
    poderMagico = pm;
    durabilidadMaxima = dm;
    durabilidadActual = dm;
    peso = p;
    rareza = r;
    energiaArcanaMaxima = eam;
    energiaArcanaActual = eam; 
}

void ObjetoMagico::setNombre(const string& nombreArg) { nombre = nombreArg; }
string ObjetoMagico::getNombre() const { return nombre; }
int ObjetoMagico::getPoder() const { return poderMagico; }
int ObjetoMagico::getDurabilidadActual() const { return durabilidadActual; }
int ObjetoMagico::getDurabilidadMaxima() const { return durabilidadMaxima; }
Rarity ObjetoMagico::getRareza() const { return rareza; }
double ObjetoMagico::getPeso() const { return peso; }
int ObjetoMagico::getEnergiaArcanaActual() const { return energiaArcanaActual; }
int ObjetoMagico::getEnergiaArcanaMaxima() const { return energiaArcanaMaxima; }

/**
 * @brief Repara el objeto mágico, aumentando su durabilidad
 * 
 * Incrementa la durabilidad actual sin superar la máxima.
 */
void ObjetoMagico::reparar(int cantidad) {
    if (cantidad <= 0) return;
    durabilidadActual = min(durabilidadMaxima, durabilidadActual + cantidad);
    cout << nombre << " reparado. Durabilidad actual: " << durabilidadActual << "/" << durabilidadMaxima << endl;
}

void ObjetoMagico::recargarEnergia(int cantidad) {
     if (cantidad <= 0) return;
    energiaArcanaActual = min(energiaArcanaMaxima, energiaArcanaActual + cantidad);
    cout << nombre << " recargado. Energía arcana: " << energiaArcanaActual << "/" << energiaArcanaMaxima << endl;
}

/**
 * @brief Muestra información detallada del objeto mágico
 * 
 * Imprime características como nombre, rareza, poder mágico, durabilidad, etc.
 */
void ObjetoMagico::mostrarInfo() const {
    cout << "Nombre: " << nombre << " [" << rarityToString(rareza) << "]" << endl;
    cout << "  Tipo: Objeto Mágico" << endl;
    cout << "  Poder Mágico: " << poderMagico << endl;
    cout << "  Durabilidad: " << durabilidadActual << "/" << durabilidadMaxima << endl;
    cout << "  Energía Arcana: " << energiaArcanaActual << "/" << energiaArcanaMaxima << endl;
    cout << "  Peso: " << peso << endl;
}

/**
 * @brief Usa el objeto mágico para realizar su efecto
 * 
 * Verifica si el objeto puede usarse, aplica su efecto mágico
 * y reduce durabilidad y energía arcana.
 * 
 * @return Valor numérico que representa el efecto del uso
 */
int ObjetoMagico::usar() {
    try {
        if (durabilidadActual <= 0) {
            throw std::runtime_error("El objeto " + nombre + " está roto y no puede usarse.");
        }

        int costoEnergia = calcularCostoEnergia();
        if (energiaArcanaMaxima > 0 && energiaArcanaActual < costoEnergia) {
            throw std::runtime_error("Energía arcana insuficiente para usar " + nombre +
                                   " (Requiere: " + std::to_string(costoEnergia) +
                                   ", Disponible: " + std::to_string(energiaArcanaActual) + ")");
        }

        cout << "Usas " << nombre << "..." << endl;
        int efectoValor = aplicarEfecto(); 

        if (energiaArcanaMaxima > 0) {
             energiaArcanaActual -= costoEnergia;
        }
        reducirDurabilidad(1);

        cout << "Energía arcana restante: " << energiaArcanaActual << "/" << energiaArcanaMaxima << endl;

        return efectoValor; 

    } catch (const std::runtime_error& e) {
        cerr << "No se pudo usar " << nombre << ": " << e.what() << endl;
        return 0; 
    } catch (const std::exception& e) {
        cerr << "Error inesperado al usar " << nombre << ": " << e.what() << endl;
        return 0;
    }
}

/**
 * @brief Aplica el efecto base del objeto mágico
 * 
 * Este método puede ser sobreescrito por clases derivadas para
 * implementar efectos mágicos específicos.
 * 
 * @return Valor numérico que representa el efecto del objeto
 */
int ObjetoMagico::aplicarEfecto() {
    cout << "El objeto " << nombre << " brilla brevemente." << endl;
    return poderMagico / 10; 
}

/**
 * @brief Calcula el costo de energía arcana al usar el objeto
 * 
 * El costo base se calcula según el poder mágico y la rareza del objeto.
 * 
 * @return Valor numérico que representa el costo de energía
 */
int ObjetoMagico::calcularCostoEnergia() const {
    int costoBase = 1 + (poderMagico / 20);
    costoBase += static_cast<int>(rareza);
    return max(1, costoBase);
}

/**
 * @brief Reduce la durabilidad del objeto mágico
 * 
 * Disminuye la durabilidad actual y muestra mensajes según
 * el estado resultante del objeto.
 */
void ObjetoMagico::reducirDurabilidad(int cantidad) {
    if (cantidad <= 0 || durabilidadActual <= 0) return;

    int durabilidadPrevia = durabilidadActual;
    durabilidadActual = max(0, durabilidadActual - cantidad);

    cout << nombre << " sufre " << cantidad << " punto(s) de desgaste. ";

    if (durabilidadActual == 0 && durabilidadPrevia > 0) {
        cout << "¡Se ha roto!" << endl;
    } else if (durabilidadActual <= durabilidadMaxima * 0.1 && durabilidadActual > 0) {
        cout << "Está a punto de romperse." << endl;
    } else if (durabilidadActual <= durabilidadMaxima * 0.25 && durabilidadActual > 0) {
        cout << "Está gravemente dañado." << endl;
    } else if (durabilidadActual <= durabilidadMaxima * 0.5 && durabilidadPrevia > durabilidadMaxima * 0.5) {
        cout << "Muestra daños significativos." << endl;
    }
    cout << "Durabilidad: " << durabilidadActual << "/" << durabilidadMaxima << endl;
}
