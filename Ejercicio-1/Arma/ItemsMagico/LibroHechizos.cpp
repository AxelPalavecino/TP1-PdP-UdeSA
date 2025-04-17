#include "LibroHechizos.hpp"
#include <cstdlib> // Para rand()

/**
 * @brief Implementación del constructor de LibroHechizos
 * 
 * Inicializa un libro de hechizos con sus propiedades específicas como
 * páginas totales, idioma y material de la cubierta.
 */
LibroHechizos::LibroHechizos(string n, int pm, int dm, double p, Rarity r, int eam, 
                             int pt, IdiomaLibro i, MaterialCubierta mc)
    : ObjetoMagico(n, pm, dm, p, r, eam), paginasTotales(pt), idioma(i), materialCubierta(mc) {}

/**
 * @brief Implementación del método usar para LibroHechizos
 * 
 * Abre el libro para consultar su contenido, posiblemente
 * desgastándolo un poco en el proceso.
 * 
 * @return 0, ya que un libro no produce efectos directos al usarse
 */
int LibroHechizos::usar() {
    if (durabilidadActual <= 0) {
        cout << nombre << " está demasiado dañado para leerlo." << endl;
        return 0;
    }
    cout << "Abres " << nombre << " (" << idiomaLibroToString(idioma) << "). Contiene " 
         << hechizos.size() << " hechizos." << endl;
    
    if (rand() % 10 == 0) {
        reducirDurabilidad(1);
    }
    return 0;
}

/**
 * @brief Implementación del método mostrarInfo para LibroHechizos
 * 
 * Muestra la información básica del objeto y añade las características
 * específicas del libro como páginas, idioma, material y hechizos contenidos.
 */
void LibroHechizos::mostrarInfo() const {
    ObjetoMagico::mostrarInfo();
    cout << "  Atributos Específicos (Libro Hechizos):" << endl;
    cout << "    Páginas: " << paginasTotales << endl;
    cout << "    Idioma: " << idiomaLibroToString(idioma) << endl;
    cout << "    Cubierta: " << materialCubiertaToString(materialCubierta) << endl;
    cout << "    Hechizos (" << hechizos.size() << "): ";
    if (hechizos.empty()) {
        cout << "Ninguno" << endl;
    } else {
        for (size_t i = 0; i < hechizos.size(); ++i) {
            cout << hechizos[i] << (i == hechizos.size() - 1 ? "" : ", ");
        }
        cout << endl;
    }
}

/**
 * @brief Implementación del método aprenderHechizo
 * 
 * Añade un nuevo hechizo al libro si hay suficiente espacio disponible
 * y el hechizo no existe ya en el libro.
 * 
 * @param hechizo Nombre del hechizo a añadir
 * @return true si se añadió correctamente, false en caso contrario
 */
bool LibroHechizos::aprenderHechizo(const string& hechizo) {
    if (hechizos.size() >= static_cast<size_t>(paginasTotales / 5)) {
        cout << nombre << " no tiene suficientes páginas libres para aprender '" << hechizo << "'." << endl;
        return false;
    }
    if (!tieneHechizo(hechizo)) {
        hechizos.push_back(hechizo);
        cout << "'" << hechizo << "' ha sido añadido a " << nombre << "." << endl;
        
        if (rand() % 20 == 0) reducirDurabilidad(1);
        return true;
    } else {
        cout << nombre << " ya contiene el hechizo '" << hechizo << "'." << endl;
        return false;
    }
}

/**
 * @brief Implementación del método olvidarHechizo
 * 
 * Elimina un hechizo del libro si existe en él.
 * 
 * @param hechizo Nombre del hechizo a eliminar
 * @return true si se eliminó correctamente, false si no existía
 */
bool LibroHechizos::olvidarHechizo(const string& hechizo) {
    auto it = std::find(hechizos.begin(), hechizos.end(), hechizo);
    if (it != hechizos.end()) {
        hechizos.erase(it);
        cout << "'" << hechizo << "' ha sido borrado mágicamente de " << nombre << "." << endl;
        return true;
    } else {
        cout << nombre << " no contiene el hechizo '" << hechizo << "'." << endl;
        return false;
    }
}

/**
 * @brief Implementación del método tieneHechizo
 * 
 * Verifica si un hechizo específico está contenido en el libro.
 * 
 * @param hechizo Nombre del hechizo a buscar
 * @return true si el hechizo está en el libro, false en caso contrario
 */
bool LibroHechizos::tieneHechizo(const string& hechizo) const {
    return std::find(hechizos.begin(), hechizos.end(), hechizo) != hechizos.end();
}

/**
 * @brief Implementación del método cantidadHechizos
 * 
 * @return Número de hechizos almacenados en el libro
 */
int LibroHechizos::cantidadHechizos() const {
    return hechizos.size();
}

/**
 * @brief Implementación del método listarHechizos
 * 
 * Muestra una lista formateada de todos los hechizos
 * contenidos en el libro.
 */
void LibroHechizos::listarHechizos() const {
    cout << "Hechizos en " << nombre << ":" << endl;
    if (hechizos.empty()) {
        cout << "  (Ninguno)" << endl;
        return;
    }
    for (const auto& h : hechizos) {
        cout << "  - " << h << endl;
    }
}
