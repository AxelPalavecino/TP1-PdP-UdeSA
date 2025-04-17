#pragma once

#include "../ObjetoMagico.hpp"
#include "../enumArmas.hpp"
#include <vector>
#include <algorithm>

/**
 * @brief Clase LibroHechizos que hereda de ObjetoMagico
 * 
 * Define los atributos y métodos específicos de un libro de hechizos,
 * permitiendo almacenar, aprender y olvidar hechizos.
 */
class LibroHechizos : public ObjetoMagico {
private:
    vector<string> hechizos; 
    int paginasTotales; 
    IdiomaLibro idioma; 
    MaterialCubierta materialCubierta; 

public:
    // ==========================================
    // CONSTRUCTORES
    // ==========================================
    
    /**
     * @brief Constructor de la clase LibroHechizos
     * @param n Nombre del libro
     * @param pm Poder mágico base
     * @param dm Durabilidad máxima
     * @param p Peso del libro
     * @param r Rareza del libro
     * @param eam Energía arcana máxima
     * @param pt Páginas totales del libro
     * @param i Idioma en que está escrito
     * @param mc Material de la cubierta
     */
    LibroHechizos(string n, int pm, int dm, double p, Rarity r, int eam,
                  int pt, IdiomaLibro i, MaterialCubierta mc);

    // ==========================================
    // MÉTODOS DERIVADOS DE INTERFAZARMAS
    // ==========================================
    
    int usar() override;
    void mostrarInfo() const override;

    // ==========================================
    // MÉTODOS PROPIOS DE LA CLASE LIBROHECHIZOS
    // ==========================================
    
    /**
     * @brief Añade un nuevo hechizo al libro
     * @param hechizo Nombre del hechizo a añadir
     * @return true si se añadió correctamente, false si ya existe o no hay espacio
     */
    bool aprenderHechizo(const string& hechizo);
    
    /**
     * @brief Elimina un hechizo del libro
     * @param hechizo Nombre del hechizo a eliminar
     * @return true si se eliminó correctamente, false si no existía
     */
    bool olvidarHechizo(const string& hechizo);
    
    /**
     * @brief Verifica si un hechizo está en el libro
     * @param hechizo Nombre del hechizo a buscar
     * @return true si el hechizo está en el libro, false en caso contrario
     */
    bool tieneHechizo(const string& hechizo) const;
    
    /**
     * @brief Obtiene la cantidad de hechizos almacenados
     * @return Número de hechizos en el libro
     */
    int cantidadHechizos() const;
    
    /**
     * @brief Muestra todos los hechizos contenidos en el libro
     */
    void listarHechizos() const;
};
