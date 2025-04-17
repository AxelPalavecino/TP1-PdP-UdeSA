<style>
.section {
  border: 2px solid #4A90E2;
  border-radius: 10px;
  padding: 18px;
  margin: 24px 0;
  background: #f8faff;
}
.section-title {
  font-size: 1.7em;
  color: #2d3e50;
  border-bottom: 2px solid #4A90E2;
  margin-bottom: 12px;
  padding-bottom: 4px;
}
.subsection-title {
  font-size: 1.2em;
  color: #4A90E2;
  margin-top: 16px;
  margin-bottom: 6px;
}
.code-block {
  background: #222;
  color: #fff;
  padding: 8px 12px;
  border-radius: 6px;
  font-size: 1em;
  margin: 10px 0;
}
.important {
  background: #fffbe6;
  border-left: 5px solid #ffe564;
  padding: 8px 12px;
  margin: 12px 0;
}
</style>

<div class="section">
  <div class="section-title">Trabajo Práctico 1 - Paradigmas de Programación</div>
  <b>Juego de Rol: Diseño, Implementación y Justificación Técnica</b>
  <br>
  <i>Autor: [Tu Nombre]</i>
  <br>
  <i>Fecha: [Fecha de entrega]</i>
</div>

<div class="section">
  <div class="section-title">1. Estructura del Proyecto y Compilación</div>
  <div class="subsection-title">1.1. Organización de Carpetas y Makefiles</div>
  El proyecto está dividido en tres carpetas principales, una por cada ejercicio solicitado:
  <ul>
    <li><b>Ejercicio-1:</b> Implementación de armas y personajes, con sus relaciones y métodos.</li>
    <li><b>Ejercicio-2:</b> Generación automática de personajes y armas usando una factoría.</li>
    <li><b>Ejercicio-3:</b> Simulador de combate tipo piedra-papel-tijera entre personajes.</li>
  </ul>
  Cada carpeta contiene su propio <b>Makefile</b> para compilar y ejecutar el código de manera independiente.
  <div class="subsection-title">1.2. Uso del Makefile</div>
  Para compilar y ejecutar cada ejercicio:
  <div class="code-block">
    # Compilar el ejercicio 1<br>
    cd Ejercicio-1<br>
    make<br>
    ./juego_rol_demo
  </div>
  <b>Opciones útiles:</b>
  <ul>
    <li><code>make clean</code>: Elimina archivos objeto y ejecutables.</li>
    <li><code>make run</code>: Compila y ejecuta el programa.</li>
    <li><code>make valgrind</code>: Ejecuta el binario bajo Valgrind para detectar fugas de memoria.</li>
  </ul>
  <div class="important">
    <b>Nota:</b> El Makefile gestiona automáticamente las dependencias y la compilación de todos los archivos fuente, incluyendo los de subcarpetas.
  </div>
</div>

<div class="section">
  <div class="section-title">2. Diseño de Clases y Relaciones</div>
  <div class="subsection-title">2.1. Armas</div>
  Se implementaron dos grandes grupos de armas, todos derivados de una interfaz común <b>InterfazArmas</b>:
  <ul>
    <li><b>Items Mágicos:</b> Bastón, Libro de Hechizos, Poción, Amuleto.</li>
    <li><b>Armas de Combate:</b> Hacha Simple, Hacha Doble, Espada, Lanza, Garrote.</li>
  </ul>
  Cada arma concreta tiene al menos 5 atributos y 5 métodos, incluyendo métodos específicos (por ejemplo, <code>lanzarRayoMagico()</code> en Bastón, <code>combinar()</code> en Poción, <code>afilar()</code> en HachaSimple, etc).

  <div class="subsection-title">2.2. Personajes</div>
  Dos grandes grupos de personajes, todos derivados de <b>InterfazPersonaje</b>:
  <ul>
    <li><b>Magos:</b> Hechicero, Conjurador, Brujo, Nigromante.</li>
    <li><b>Guerreros:</b> Bárbaro, Paladín, Caballero, Mercenario, Gladiador.</li>
  </ul>
  Cada personaje concreto implementa al menos 5 atributos y 5 métodos, con habilidades únicas (por ejemplo, <code>lanzarHechizo()</code>, <code>invocarFamiliar()</code>, <code>entrarEnFrenesi()</code>, <code>castigarMalvados()</code>, etc).

  <div class="subsection-title">2.3. Relación de Composición y Uso de Smart Pointers</div>
  <b>Composición:</b> Un personaje <b>tiene</b> armas (<i>has-a</i>), es decir, la vida del arma está ligada a la del personaje. Si el personaje se destruye, también sus armas.
  <br>
  <b>Justificación de <code>unique_ptr</code>:</b> Se utiliza <code>std::unique_ptr</code> para garantizar la propiedad exclusiva de las armas por parte del personaje, evitando fugas de memoria y dobles liberaciones. Además, permite transferir armas entre personajes de forma segura usando <code>std::move</code>.
  <br>
  <b>Tipos de datos:</b> Se emplean <code>enum class</code> para atributos categóricos (raza, tipo de arma, rareza, etc.), <code>std::string</code> para nombres y descripciones, y <code>int/double</code> para valores numéricos.

  <div class="subsection-title">2.4. Diagrama UML</div>
  <div align="center">
    <b>Espacio reservado para el diagrama UML de clases:</b>
    <br>
    <img src="uml_ejercicio1.png" alt="UML Ejercicio 1" width="600px"/>
    <br>
    <i>(Coloque aquí el diagrama UML generado con la herramienta de su preferencia)</i>
  </div>
</div>

<div class="section">
  <div class="section-title">3. Justificación de Decisiones Técnicas</div>
  <div class="subsection-title">3.1. Uso de <code>unique_ptr</code> y composición</div>
  <ul>
    <li>Permite modelar la relación de composición: el arma no puede existir sin el personaje.</li>
    <li>Evita fugas de memoria y facilita la transferencia de armas entre personajes.</li>
    <li>Permite polimorfismo sin necesidad de gestionar manualmente la destrucción de objetos.</li>
  </ul>
  <div class="subsection-title">3.2. Tipos de datos y enums</div>
  <ul>
    <li><b>enum class:</b> Para rareza, tipo de arma, raza, escuela de magia, etc. Mejora la legibilidad y seguridad de tipo.</li>
    <li><b>std::string:</b> Para nombres, descripciones, inscripciones, etc.</li>
    <li><b>int/double:</b> Para atributos numéricos como daño, durabilidad, peso, etc.</li>
  </ul>
  <div class="subsection-title">3.3. Métodos de visualización y librerías utilizadas</div>
  <ul>
    <li>Se utilizan métodos como <code>mostrarInfo()</code> en armas y personajes para imprimir información detallada en consola.</li>
    <li>Para mejorar la visualización, se emplean <b>librerías estándar</b> como <code>&lt;iostream&gt;</code>, <code>&lt;iomanip&gt;</code> (alineación y formato), <code>&lt;thread&gt;</code> y <code>&lt;chrono&gt;</code> (pausas y animaciones), y <code>&lt;limits&gt;</code> (gestión de entradas).</li>
    <li>Se usan <b>frames ASCII</b> y separadores para estructurar la salida y hacerla más legible, ya que no se dispone de interfaces gráficas en consola estándar.</li>
    <li>El menú principal y los submenús están diseñados con bordes y títulos para simular una interfaz de usuario más amigable.</li>
    <li>La función <code>limpiarPantalla()</code> utiliza <code>system("cls")</code> o <code>system("clear")</code> según el sistema operativo, para limpiar la consola y mejorar la experiencia visual.</li>
  </ul>
  <div class="important">
    <b>Justificación:</b> Estas técnicas permiten una experiencia de usuario más rica y profesional en consola, a pesar de las limitaciones de la terminal. Además, facilitan la depuración y el testeo de las funcionalidades implementadas.
  </div>
</div>

<div class="section">
  <div class="section-title">4. Ejecución y Pruebas</div>
  <div class="subsection-title">4.1. Ejercicio 1: Pruebas de armas y personajes</div>
  El menú principal permite probar:
  <ul>
    <li><b>Armas y objetos:</b> Se crean instancias de cada arma, se muestran sus atributos y se prueban sus métodos específicos.</li>
    <li><b>Personajes:</b> Se crean personajes de cada tipo, se muestran sus atributos, se prueban sus habilidades y la gestión de inventario de armas.</li>
    <li><b>Simulador de combate:</b> Se simula un combate por turnos entre varios personajes, con intercambio de armas y uso de habilidades especiales.</li>
  </ul>
  <div class="subsection-title">4.2. Ejercicio 2: Generación automática de personajes y armas</div>
  <ul>
    <li>Se utiliza <code>std::rand()</code> junto con <code>cstdlib</code> y <code>ctime</code> para generar números aleatorios.</li>
    <li>La clase <b>PersonajeFactory</b> permite crear personajes y armas en tiempo de ejecución, devolviendo <code>unique_ptr</code> a los objetos generados.</li>
    <li>La cantidad de personajes y armas por personaje se determina aleatoriamente en los rangos especificados.</li>
  </ul>
  <div class="subsection-title">4.3. Ejercicio 3: Simulador de combate tipo piedra-papel-tijera</div>
  <ul>
    <li>El jugador 1 elige su movimiento por teclado, el jugador 2 lo hace aleatoriamente.</li>
    <li>Se aplican las reglas de daño y defensa según la consigna.</li>
    <li>El combate termina cuando uno de los personajes pierde todos sus puntos de vida.</li>
    <li>El programa indica el tipo de personaje y el arma utilizada en cada ataque.</li>
  </ul>
</div>

<div class="section">
  <div class="section-title">5. Conclusiones y Observaciones</div>
  <ul>
    <li>El uso de composición y <code>unique_ptr</code> garantiza un manejo seguro y eficiente de la memoria.</li>
    <li>La estructura modular y el uso de Makefiles facilitan la compilación y ejecución de cada parte del trabajo práctico.</li>
    <li>La visualización en consola se mejoró significativamente mediante el uso de técnicas de formateo y separación visual.</li>
    <li>El diseño orientado a objetos permite una fácil extensión y mantenimiento del código.</li>
    <li>El diagrama UML (ver sección correspondiente) refleja fielmente las relaciones de herencia, composición y polimorfismo implementadas.</li>
  </ul>
</div>

<!-- Fin del informe -->
