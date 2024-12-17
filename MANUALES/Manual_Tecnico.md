# Manual Técnico del Sistema de Gestión de Activos

## Introducción
Este manual está dirigido a programadores y desarrolladores que necesiten comprender la implementación técnica del **Sistema de Gestión de Activos**. Se describen las clases más importantes, sus atributos, métodos y cómo interactúan entre sí para lograr la funcionalidad completa del programa.

---

## 1. Estructura General del Sistema
El programa utiliza **C++** como lenguaje de programación y organiza sus datos mediante:

- **Matriz Dispersa** para organizar empresas y departamentos.
- **Árbol AVL** para manejar activos de forma eficiente.
- **Lista Circular Doblemente Enlazada** para gestionar transacciones.

La estructura principal está organizada en clases y se sigue un modelo orientado a objetos (OOP).

---

## 2. Clases Principales

### 2.1 Clase `Usuario`
**Descripción:** Representa a un usuario del sistema, ya sea **administrador** o **usuario normal**.

#### Atributos:
- `string nombre_usuario`: Nombre único del usuario.
- `string nombre_completo`: Nombre completo del usuario.
- `string contrasena`: Contraseña del usuario.
- `string departamento`: Departamento asociado.
- `string empresa`: Empresa asociada.
- `AVL* activos`: Puntero a un árbol AVL que almacena los activos.

#### Métodos:
- **Constructor:** Inicializa un usuario con datos básicos.
- **getNombreUsuario()**: Retorna el nombre de usuario.
- **getActivos()**: Retorna el árbol AVL de activos.
- **imprimirInformacion()**: Muestra la información del usuario.

---

### 2.2 Clase `AVL` (Árbol AVL)
**Descripción:** Implementa un árbol AVL para manejar y organizar los activos de cada usuario.

#### Atributos:
- `NodoAVL* raiz`: Puntero a la raíz del árbol AVL.

#### Métodos:
- **insertar(Activo activo)**: Inserta un activo en el árbol manteniendo el balance.
- **eliminar(int id_activo)**: Elimina un activo según su ID.
- **buscar(int id_activo)**: Busca un activo en el árbol.
- **graficar()**: Genera una representación visual del árbol AVL en formato DOT.

---

### 2.3 Clase `Activo`
**Descripción:** Representa un activo en el sistema.

#### Atributos:
- `int id`: Identificador único del activo.
- `string nombre`: Nombre del activo.
- `float valor`: Valor monetario del activo.

#### Métodos:
- **Constructor:** Inicializa el activo con ID, nombre y valor.
- **imprimir()**: Muestra la información del activo.

---

### 2.4 Clase `Transaccion`
**Descripción:** Representa una transacción registrada en el sistema.

#### Atributos:
- `int id`: Identificador único de la transacción.
- `string fecha`: Fecha de la transacción.
- `string descripcion`: Descripción de la transacción.
- `float monto`: Monto asociado a la transacción.

#### Métodos:
- **Constructor:** Inicializa una nueva transacción.
- **imprimir()**: Muestra los detalles de la transacción.

---

### 2.5 Clase `DoublyCircular` (Lista Circular Doblemente Enlazada)
**Descripción:** Maneja las transacciones registradas en el sistema.

#### Atributos:
- `Nodo* head`: Puntero al nodo principal de la lista circular.

#### Métodos:
- **insertar(Transaccion t)**: Inserta una nueva transacción en la lista.
- **eliminar(int id)**: Elimina una transacción según su ID.
- **imprimirLista()**: Imprime todas las transacciones almacenadas.
- **graficar()**: Genera una representación DOT de la lista circular.

---

### 2.6 Clase `MatrizDispersa`
**Descripción:** Implementa la estructura de matriz dispersa que organiza los datos por **Empresas** y **Departamentos**.

#### Atributos:
- `NodoMatriz* raiz`: Nodo raíz de la matriz dispersa.

#### Métodos:
- **insertar(Usuario u)**: Inserta un usuario en la matriz.
- **eliminar(string nombre_usuario)**: Elimina un usuario de la matriz.
- **buscar(string empresa, string departamento)**: Busca un usuario en una celda específica.
- **graficar()**: Genera la representación DOT de la matriz dispersa.

---

## 3. Interacción entre las Clases
A continuación, se describe cómo interactúan las clases entre sí:

1. **Usuario**:
    - Almacena activos en un árbol AVL.
    - Se organiza en la **Matriz Dispersa**.

2. **Transaccion**:
    - Se almacena en la **Lista Circular Doblemente Enlazada**.
    - Cada usuario puede registrar múltiples transacciones.

3. **MatrizDispersa**:
    - Permite acceder rápidamente a usuarios según su empresa y departamento.

4. **AVL**:
    - Permite gestionar activos de forma eficiente para cada usuario.

---

## 4. Graficación con Graphviz
El programa utiliza **Graphviz** para generar representaciones gráficas de las estructuras:

- **Matriz Dispersa**: Representación de la organización de empresas y departamentos.
- **Árbol AVL**: Visualización de los activos.
- **Lista Circular Doblemente Enlazada**: Representación de transacciones.

### Generación de Gráficos:
1. Utilice los métodos `graficar()` de las clases correspondientes.
2. El método generará un archivo `.dot`.
3. Use **Graphviz** para visualizar el archivo con el comando:
   ```bash
   dot -Tpng archivo.dot -o salida.png
   ```

---

## 5. Flujo de Ejecución
1. **Inicio de sesión**:
    - Se verifica el tipo de usuario y se muestra el menú correspondiente.

2. **Gestión de usuarios y activos** (Administrador):
    - Inserción y eliminación de usuarios en la **Matriz Dispersa**.
    - Manejo de activos mediante el **Árbol AVL**.

3. **Gestión de transacciones** (Usuarios normales):
    - Registro de transacciones en la **Lista Circular Doblemente Enlazada**.

4. **Graficación**:
    - Generación de gráficos de estructuras para validación.

---

## 6. Recomendaciones Técnicas
- Asegúrese de compilar el código con un compilador que soporte **C++11** o superior.
- Verifique que **Graphviz** esté instalado correctamente para generar las representaciones gráficas.
- Mantenga las estructuras balanceadas para evitar pérdida de rendimiento (especialmente en el **Árbol AVL**).

---

## Conclusión
Este manual proporciona una visión detallada de la implementación técnica del **Sistema de Gestión de Activos**. Siguiendo esta documentación, otros desarrolladores podrán entender, mantener y extender el código sin dificultad.

**¡Feliz codificación!**
