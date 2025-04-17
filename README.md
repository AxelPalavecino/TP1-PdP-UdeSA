<!-- Imagen de portada del informe -->
<p align="center">
  <img src="portada_tp1.png" alt="Portada Trabajo Práctico 1" width="500"/>
</p>

# Trabajo Práctico 1 - Paradigmas de Programación
**Juego de Rol: Diseño, Implementación y Justificación Técnica**

*Autor: Palavecino Axel David*  

---

## 1. Estructura del Proyecto y Compilación

### 1.1. Organización de Carpetas y Makefiles
El proyecto está dividido en tres carpetas principales, una por cada ejercicio solicitado:
* **Ejercicio-1:** Implementación de armas y personajes, con sus relaciones y métodos.
* **Ejercicio-2:** Generación automática de personajes y armas usando una factoría.
* **Ejercicio-3:** Simulador de combate tipo piedra-papel-tijera entre personajes.

Cada carpeta contiene su propio **Makefile** para compilar y ejecutar el código de manera independiente.

### 1.2. Uso del Makefile
Para compilar y ejecutar cada ejercicio:

```
# Compilar el ejercicio 1
cd Ejercicio-1
make (crea el ejecutable)
make run (ejecuta el programa)
make clean (elimina archivos objeto y ejecutables)

# Compilar el ejercicio 2
cd ../Ejercicio-2
make (crea el ejecutable)
make run (ejecuta el programa)
make clean (elimina archivos objeto y ejecutables)

# Compilar el ejercicio 3
cd ../Ejercicio-3
make (crea el ejecutable)
make run (ejecuta el programa)
make clean (elimina archivos objeto y ejecutables)
```

**Opciones útiles:**
* `make clean`: Elimina archivos objeto y ejecutables.
* `make run`: Compila y ejecuta el programa.
* `make valgrind`: Ejecuta el binario bajo Valgrind para detectar fugas de memoria.

> **Nota:** El Makefile gestiona automáticamente las dependencias y la compilación de todos los archivos fuente, incluyendo los de subcarpetas.

---

## 2. Resolución Detallada de los Ejercicios

### 2.1. Ejercicio 1: Modelado de Armas y Personajes

#### **Descripción General**
El primer ejercicio consistió en modelar un sistema de juego de rol orientado a objetos, implementando dos jerarquías principales: armas y personajes. Cada jerarquía parte de una interfaz común y se ramifica en clases abstractas y concretas, permitiendo una gran extensibilidad y polimorfismo.

#### **Diseño de Armas**
- **InterfazArmas:** Define la API común para todas las armas y objetos mágicos, asegurando que todas las clases derivadas implementen métodos como `usar()`, `mostrarInfo()`, `reparar()`, etc.
- **Clases abstractas:** 
  - `ObjetoMagico` para items mágicos (bastón, libro de hechizos, poción, amuleto).
  - `ArmaDeCombate` para armas físicas (hacha simple, hacha doble, espada, lanza, garrote).
- **Clases concretas:** Cada arma concreta implementa atributos y métodos específicos, por ejemplo:
  - **Bastón:** Puede lanzar rayos mágicos, cambiar gema, mejorar encantamiento.
  - **Poción:** Puede combinarse con otras, tiene dosis, efectos y colores.
  - **Espada:** Permite estocar, parar ataques, pulir hoja.
  - **Garrote:** Puede ser claveteado, reforzado, tiene bonus de aturdimiento.

#### **Diseño de Personajes**
- **InterfazPersonaje:** Define la API común para todos los personajes, asegurando métodos como `atacar()`, `recibirDanio()`, `mostrarInfo()`, etc.
- **Clases abstractas:** 
  - `Mago` para personajes mágicos (hechicero, conjurador, brujo, nigromante).
  - `Guerrero` para personajes físicos (bárbaro, paladín, caballero, mercenario, gladiador).
- **Clases concretas:** Cada personaje concreto implementa habilidades únicas y atributos propios, por ejemplo:
  - **Hechicero:** Puede aprender y lanzar hechizos, invocar familiar, alterar el tiempo.
  - **Brujo:** Puede invocar a su patrón, lanzar maleficios, sacrificar vida por maná.
  - **Barbaro:** Puede entrar en frenesí, resistir dolor, lanzar gritos de batalla.
  - **Paladín:** Puede invocar luz sagrada, imponer manos, activar aura divina.

#### **Justificación de Tipos de Datos**
- **`enum class`:** Se usaron para categorizar atributos como rareza, tipo de arma, raza, escuela de magia, etc. Esto mejora la seguridad de tipo y la legibilidad, evitando errores por valores mágicos.
- **`std::string`:** Para nombres, descripciones, inscripciones, etc., permitiendo flexibilidad y manipulación de texto.
- **`int` y `double`:** Para atributos numéricos como daño, durabilidad, peso, nivel de filo, etc. Se eligió `double` para pesos y longitudes por su naturaleza continua.
- **`std::vector`:** Para listas de hechizos, criaturas pactadas, contratos, etc., permitiendo almacenamiento dinámico y acceso eficiente.
- **`unique_ptr`:** Para la composición entre personajes y armas, garantizando la propiedad exclusiva y la correcta liberación de memoria.

#### **Relación de Composición y Smart Pointers**
La relación de composición (`has-a`) entre personajes y armas se implementó usando `std::unique_ptr`. Esto asegura que:
- Un arma no puede existir sin su dueño (personaje).
- No hay fugas de memoria ni dobles liberaciones.
- El traspaso de armas entre personajes es seguro y explícito usando `std::move`.
- Se aprovecha el polimorfismo sin necesidad de gestionar manualmente la destrucción de objetos.

#### **Visualización y Librerías Utilizadas**
- **Visualización:** Se implementaron métodos como `mostrarInfo()` en todas las clases para imprimir información detallada y formateada en consola. Se usaron separadores, bordes y títulos ASCII para mejorar la legibilidad.
- **Librerías estándar:** 
  - `<iostream>` para entrada/salida.
  - `<iomanip>` para formateo de texto.
  - `<thread>` y `<chrono>` para pausas y animaciones.
  - `<limits>` para control de entrada.
  - `<algorithm>` para búsquedas y manipulaciones de vectores.
- **Justificación:** Estas técnicas permiten una experiencia de usuario más rica y profesional en consola, a pesar de las limitaciones de la terminal. Además, facilitan la depuración y el testeo de las funcionalidades implementadas.

#### **Aprendizajes y Dificultades**
- Se aprendió a modelar jerarquías complejas usando herencia y polimorfismo.
- Se profundizó en el uso de smart pointers y la gestión automática de memoria.
- Se practicó la separación de interfaz y lógica, y la importancia de la documentación.
- Se enfrentaron desafíos en la gestión de la composición y el traspaso de armas, así como en la visualización amigable en consola.

---

### 2.2. Ejercicio 2: Factoría de Personajes y Armas

#### **Descripción General**
El segundo ejercicio consistió en automatizar la creación de personajes y armas usando una factoría (`PersonajeFactory`). Se requería el uso de números aleatorios para determinar la cantidad y tipo de personajes y armas.

#### **Resolución**
- **Generación aleatoria:** Se utilizó `std::rand()` junto con `<cstdlib>` y `<ctime>` para inicializar la semilla y obtener valores aleatorios en los rangos requeridos.
- **PersonajeFactory:** 
  - Implementada como una clase con métodos estáticos, permitiendo crear personajes y armas en tiempo de ejecución sin necesidad de instanciar la factoría.
  - Devuelve `unique_ptr` a los objetos generados, facilitando la gestión de memoria y el polimorfismo.
  - Permite crear personajes armados, es decir, personajes que ya poseen armas al ser generados.
- **Justificación de diseño:** 
  - El uso de métodos estáticos y smart pointers simplifica la interfaz y evita errores de gestión de memoria.
  - El polimorfismo permite tratar todos los personajes y armas de forma uniforme, facilitando la extensión del sistema.

#### **Aprendizajes**
- Se aprendió a utilizar la generación de números aleatorios para crear escenarios dinámicos.
- Se profundizó en el diseño de factorías y la importancia de la abstracción en la creación de objetos.
- Se reforzó el uso de smart pointers en contextos de creación dinámica y polimorfismo.

---

### 2.3. Ejercicio 3: Simulador de Combate Piedra-Papel-Tijera

#### **Descripción General**
El tercer ejercicio implementa un simulador de combate entre dos personajes, siguiendo una lógica similar a piedra-papel-tijera pero con movimientos personalizados: "Golpe Fuerte", "Golpe Rápido" y "Defensa y Golpe".

#### **Resolución**
- **Elección de movimientos:** 
  - El jugador 1 elige su movimiento por teclado.
  - El jugador 2 elige aleatoriamente usando `std::rand()`.
- **Resolución del combate:** 
  - Se aplican las reglas de daño y defensa según la consigna.
  - El combate es por rondas, y termina cuando uno de los personajes pierde todos sus puntos de vida.
  - El programa indica el tipo de personaje y el arma utilizada en cada ataque.
- **Visualización:** 
  - Se utilizan iconos y colores ANSI para mejorar la experiencia visual.
  - Se muestran los movimientos elegidos y el resultado de cada ronda.

#### **Justificación de Tipos de Datos**
- **Enums:** Para los movimientos de combate, asegurando claridad y evitando errores de entrada.
- **Smart pointers:** Para la gestión de los personajes y armas durante el combate.
- **Funciones auxiliares:** Para la conversión de enums a string y la visualización de iconos.

#### **Aprendizajes**
- Se practicó la integración de lógica de juego con entrada/salida de usuario.
- Se aprendió a manejar la aleatoriedad y la interacción en tiempo real.
- Se reforzó la importancia de la visualización clara y amigable en aplicaciones de consola.

---

## 3. Diagrama UML

**Espacio reservado para el diagrama UML de clases:**

![UML Ejercicio 1]

*(Coloque aquí el diagrama UML generado con la herramienta de su preferencia)*

---

## 4. Conclusiones y Observaciones

- El uso de composición y `unique_ptr` garantiza un manejo seguro y eficiente de la memoria.
- La estructura modular y el uso de Makefiles facilitan la compilación y ejecución de cada parte del trabajo práctico.
- La visualización en consola se mejoró significativamente mediante el uso de técnicas de formateo y separación visual.
- El diseño orientado a objetos permite una fácil extensión y mantenimiento del código.
- El diagrama UML (ver sección correspondiente) refleja fielmente las relaciones de herencia, composición y polimorfismo implementadas.
- Se aprendió a modelar sistemas complejos, a justificar las decisiones de diseño y a documentar adecuadamente el código y el proceso de desarrollo.

---

## 5. Reflexión Final

Este trabajo práctico permitió profundizar en conceptos avanzados de C++ y programación orientada a objetos, tales como:
- Herencia múltiple y jerarquías complejas.
- Uso avanzado de smart pointers y gestión automática de recursos.
- Diseño de factorías y patrones de creación.
- Polimorfismo y extensibilidad.
- Visualización y experiencia de usuario en consola.
- Documentación y justificación de decisiones técnicas.

El resultado es un sistema robusto, extensible y seguro, que puede servir de base para proyectos más ambiciosos en el futuro.

---
