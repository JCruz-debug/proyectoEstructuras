#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TITULO_MAX_LENGTH 100
#define AUTOR_MAX_LENGTH 100


//------------------------------------
//-------FUNCIONES DE ESTRUCTURAS-----
//------------------------------------




// Estructura Libro
struct Libro {
    int id;
    char titulo[TITULO_MAX_LENGTH];
    char autor[AUTOR_MAX_LENGTH];
    float precio;
    struct Libro* siguiente;
};

// Estructura Pila
struct Pila {
    struct Libro* tope;
};

// Estructura Cola
struct Cola {
    struct Libro* frente;
    struct Libro* final;
};

// Función para crear una pila vacía
struct Pila* crearPila(){
    struct Pila* pila = (struct Pila*)malloc(sizeof(struct Pila));
    pila->tope = NULL;
    return pila;
}

// Función para verificar si la pila está vacía
int estaVacia(struct Pila* pila){
    return (pila->tope == NULL);
}

// Función para insertar un libro en la pila
void push(struct Pila* pila){
    struct Libro* nuevoLibro = (struct Libro*)malloc(sizeof(struct Libro));
    
    printf("Ingrese el ID del libro: ");
    scanf("%d", &nuevoLibro->id);

    printf("Ingrese el título del libro: ");
    scanf(" %[^\n]", nuevoLibro->titulo);

    printf("Ingrese el autor del libro: ");
    scanf(" %[^\n]", nuevoLibro->autor);

    printf("Ingrese el precio del libro: ");
    scanf("%f", &nuevoLibro->precio);

    nuevoLibro->siguiente = pila->tope;
    pila->tope = nuevoLibro;
    printf("Libro insertado en la pila.\n");
}

// Función para imprimir la pila de libros
void imprimirPila(struct Pila* pila){
    if (estaVacia(pila)) {
        printf("La pila está vacía.\n");
        return;
    }
    struct Libro* temp = pila->tope;
    printf("Contenido de la pila:\n");
    while (temp != NULL) {
        printf("ID: %d\nTítulo: %s\nAutor: %s\nPrecio: %.2f\n\n", temp->id, temp->titulo, temp->autor, temp->precio);
        temp = temp->siguiente;
    }
}

// Función para crear una cola vacía
struct Cola* crearCola(){
    struct Cola* cola = (struct Cola*)malloc(sizeof(struct Cola));
    cola->frente = cola->final = NULL;
    return cola;
}

// Función para verificar si la cola está vacía
int estaVaciaCola(struct Cola* cola){
    return (cola->frente == NULL);
}

// Función para insertar un libro en la cola
void encolar(struct Cola* cola){
    struct Libro* nuevoLibro = (struct Libro*)malloc(sizeof(struct Libro));
    
    printf("Ingrese el ID del libro: ");
    scanf("%d", &nuevoLibro->id);

    printf("Ingrese el título del libro: ");
    scanf(" %[^\n]", nuevoLibro->titulo);

    printf("Ingrese el autor del libro: ");
    scanf(" %[^\n]", nuevoLibro->autor);

    printf("Ingrese el precio del libro: ");
    scanf("%f", &nuevoLibro->precio);

    nuevoLibro->siguiente = NULL;

    if (estaVaciaCola(cola)) {
        cola->frente = cola->final = nuevoLibro;
    } else {
        cola->final->siguiente = nuevoLibro;
        cola->final = nuevoLibro;
    }

    printf("Libro insertado en la cola.\n");
}

// Función para imprimir la cola de libros
void imprimirCola(struct Cola* cola){
    if (estaVaciaCola(cola)) {
        printf("La cola está vacía.\n");
        return;
    }
    struct Libro* temp = cola->frente;
    printf("Contenido de la cola:\n");
    while (temp != NULL) {
        printf("ID: %d\nTítulo: %s\nAutor: %s\nPrecio: %.2f\n\n", temp->id, temp->titulo, temp->autor, temp->precio);
        temp = temp->siguiente;
    }
}

// Función para agregar un libro al final de la lista
void agregarLibro(struct Libro** lista){
    struct Libro* nuevoLibro = (struct Libro*)malloc(sizeof(struct Libro));
    
    printf("Ingrese el ID del libro: ");
    scanf("%d", &nuevoLibro->id);

    printf("Ingrese el título del libro: ");
    scanf(" %[^\n]", nuevoLibro->titulo);

    printf("Ingrese el autor del libro: ");
    scanf(" %[^\n]", nuevoLibro->autor);

    printf("Ingrese el precio del libro: ");
    scanf("%f", &nuevoLibro->precio);
    nuevoLibro->siguiente = NULL;

    if (*lista == NULL) {
        *lista = nuevoLibro;
    } else {
        struct Libro* tmp = *lista;
        while (tmp->siguiente != NULL) {
            tmp = tmp->siguiente;
        }
        tmp->siguiente = nuevoLibro;
    }
}

// Función para imprimir la lista de libros
void imprimirLista(struct Libro* lista){
    if (lista == NULL) {
        printf("La lista está vacía.\n");
        return;
    }
    printf("Contenido de la lista:\n");
    while (lista != NULL) {
        printf("ID: %d\nTítulo: %s\nAutor: %s\nPrecio: %.2f\n\n", lista->id, lista->titulo, lista->autor, lista->precio);
        lista = lista->siguiente;
    }
}



//---------------------------------------------------
//--------------FUNCIONES DE ARBOL-------------------
//---------------------------------------------------

// Estructura para el nodo del árbol binario de búsqueda
struct NodoArbol{
    struct Libro libro;
    struct NodoArbol* izquierda;
    struct NodoArbol* derecha;
};

// Función para crear un nuevo nodo del árbol
struct NodoArbol* nuevoNodo(struct Libro libro){
    struct NodoArbol* nodo = (struct NodoArbol*)malloc(sizeof(struct NodoArbol));
    nodo->libro = libro;
    nodo->izquierda = nodo->derecha = NULL;
    return nodo;
}

// Función para insertar un libro en el árbol
struct NodoArbol* insertarLibro(struct NodoArbol* nodo, struct Libro libro){
    // Si el árbol está vacío, se crea un nuevo nodo
    if (nodo == NULL) {
        return nuevoNodo(libro);
    }

    // Recursivamente se inserta el libro en el subárbol izquierdo o derecho
    if (libro.id < nodo->libro.id) {
        nodo->izquierda = insertarLibro(nodo->izquierda, libro);
    } else if (libro.id > nodo->libro.id) {
        nodo->derecha = insertarLibro(nodo->derecha, libro);
    }

    return nodo;
}

// Función para buscar un libro por su ID en el árbol
struct NodoArbol* buscarLibro(struct NodoArbol* nodo, int id){
    // Si el nodo es nulo o el libro está en el nodo actual
    if (nodo == NULL || nodo->libro.id == id){
        return nodo;
    }

    // Si el ID es mayor, se busca en el subárbol derecho; si es menor, en el izquierdo
    if(id > nodo->libro.id){
        return buscarLibro(nodo->derecha, id);
    } else{
        return buscarLibro(nodo->izquierda, id);
    }
}

// Función para imprimir el árbol
void imprimirArbol(struct NodoArbol* nodo){
    if(nodo != NULL){
        imprimirArbol(nodo->izquierda);
        printf("ID: %d\nTítulo: %s\nAutor: %s\nPrecio: %.2f\n\n", nodo->libro.id, nodo->libro.titulo, nodo->libro.autor, nodo->libro.precio);
        imprimirArbol(nodo->derecha);
    }
}

//--------------------------------------------
//------FUNCIONES DE ORDENAMIENTO-------------
//--------------------------------------------

void ordenarPorID(struct Libro libros[], int n){
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if(libros[j].id < libros[min_idx].id){
                min_idx = j;
            }
        }
        if(min_idx != i) {
            struct Libro temp = libros[min_idx];
            libros[min_idx] = libros[i];
            libros[i] = temp;
        }
    }
}


// Función para añadir libros manualmente a la lista
void agregarLibrosManual(struct Libro libros[], int *numLibros){
    int opcion;
    do {
        printf("Ingrese el ID del libro: ");
        scanf("%d", &libros[*numLibros].id);

        printf("Ingrese el título del libro: ");
        scanf(" %[^\n]", libros[*numLibros].titulo);

        printf("Ingrese el autor del libro: ");
        scanf(" %[^\n]", libros[*numLibros].autor);

        printf("Ingrese el precio del libro: ");
        scanf("%f", &libros[*numLibros].precio);

        (*numLibros)++;

        printf("¿Desea agregar otro libro? (1 - Sí, 0 - No): ");
        scanf("%d", &opcion);
    } while (opcion != 0);
}



//----------------------------------------------
//-------------FUNCIONES BUSQUEDA---------------
//----------------------------------------------



// Función para buscar un libro por ID usando búsqueda secuencial
int buscarPorID(struct Libro libros[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (libros[i].id == id) {
            return i; // Se encontró el libro, se devuelve su posición en el arreglo
        }
    }
    return -1; // El libro no fue encontrado
}




//--------------------------------------------
//---------FUNCIONES FUNDAMENTALES------------
//--------------------------------------------

// Función principal para la sección de estructuras fundamentales
void estructurasFundamentales(){
    printf("Tema 1: Listas, colas y pilas.\n");
    printf("Las estructuras son utilizadas para almacenar y orgaizar datos en una computadora.\n");
    printf("Listas: Son conjuntos de elementos ordenados donde cada elemento tiene una posición o índice.\nPuedes agregar, eliminar o acceder a elementos en cualquier posición de la lista.\nEs como una lista de compras donde puedes agregar, quitar o ver elementos en cualquier orden.\n");
    printf("\n");
    printf("Colas: Funcionan bajo el principio primero en entrar, primero en salir (FIFO, por sus siglas en inglés).\nImagina una fila en un supermercado: la primera persona que llega es la primera en salir después de pagar.\nEn una cola, los elementos se agregan al final y se eliminan desde el principio.\n");
    printf("\n");
    printf("Pilas: Operan bajo el principio último en entrar, primero en salir (LIFO, por sus siglas en inglés).\nEs como una pila de platos: el último que se coloca es el primero que se saca.\nEn una pila, los elementos se agregan y eliminan del mismo extremo, llamado la cima (o tope).\n");
    printf("\n");
    // Lista de libros
    struct Libro* listaLibros = NULL;

    int numLibros;
    printf("Ingrese el número de libros que desea agregar a la lista: ");
    scanf("%d", &numLibros);

    for (int i = 0; i < numLibros; ++i) {
        printf("Ingrese los datos del libro %d para la lista:\n", i + 1);
        agregarLibro(&listaLibros);
    }

    printf("Lista de libros:\n");
    imprimirLista(listaLibros);

    // Pila de libros
    struct Pila* miPila = crearPila();

    int numPila;
    printf("\nIngrese el número de libros que desea agregar a la pila: ");
    scanf("%d", &numPila);

    printf("\nIngrese los datos de los libros para la pila:\n");
    for (int i = 0; i < numPila; ++i) {
        printf("Ingrese los datos del libro %d para la pila:\n", i + 1);
        push(miPila);
    }

    printf("\nPila de libros:\n");
    imprimirPila(miPila);

    // Cola de libros
    struct Cola* miCola = crearCola();

    int numCola;
    printf("\nIngrese el número de libros que desea agregar a la cola: ");
    scanf("%d", &numCola);

    printf("\nIngrese los datos de los libros para la cola:\n");
    for (int i = 0; i < numCola; ++i) {
        printf("Ingrese los datos del libro %d para la cola:\n", i + 1);
        encolar(miCola);
    }

    printf("\nCola de libros:\n");
    imprimirCola(miCola);
}


void estructurasAvanzadas(){

    printf("Tema 2: Árboles binarios de búsqueda\n");
    printf("Los árboles binarios de búsqueda son estructuras de datos que siguen un orden jerárquico y están compuestos por nodos.\nCada nodo tiene, como máximo, dos nodos secundarios: uno izquierdo y uno derecho.\n");
    printf("\n");
    printf("Los árboles binarios de búsqueda son útiles para búsquedas rápidas y eficientes, ya que permiten descartar una gran cantidad de datos en cada paso del proceso de búsqueda debido a su estructura ordenada.\nSu implementación eficiente los hace valiosos en aplicaciones que requieren operaciones de búsqueda, inserción y eliminación con tiempos de ejecución óptimos.\n");
    printf("\n");

    struct NodoArbol* arbolLibros = NULL;

    int numLibros;
    printf("Ingrese el número de libros que desea agregar al árbol: ");
    scanf("%d", &numLibros);

    for (int i = 0; i < numLibros; ++i) {
        printf("Ingrese los datos del libro %d para el árbol:\n", i + 1);
        struct Libro nuevoLibro;
        printf("Ingrese el ID del libro: ");
        scanf("%d", &nuevoLibro.id);
        printf("Ingrese el título del libro: ");
        scanf(" %[^\n]", nuevoLibro.titulo);
        printf("Ingrese el autor del libro: ");
        scanf(" %[^\n]", nuevoLibro.autor);
        printf("Ingrese el precio del libro: ");
        scanf("%f", &nuevoLibro.precio);

        arbolLibros = insertarLibro(arbolLibros, nuevoLibro);
    }

    printf("Árbol de libros creado.\n");
    printf("Contenido del arbol de libros: \n");
    imprimirArbol(arbolLibros);

    // Ahora el árbol 'arbolLibros' contiene los libros ingresados
    // Puedes realizar operaciones como búsqueda, impresión del árbol, etc.
    

    // Función principal para la sección de algoritmos de ordenamiento

}


void algoritmosOrdenamiento(){
    printf("Tema 3: Algoritmos de ordenamiento\n");
    printf("El algoritmo de búsqueda de selección es un método sencillo para encontrar el elemento más pequeño (o más grande) en una lista y colocarlo en la posición correcta.\n");
    printf(".-Selección del elemento mínimo: El algoritmo recorre la lista y busca el elemento más pequeño (o más grande, dependiendo del tipo de ordenamiento deseado).\n");
    printf(".-Intercambio: Una vez que se encuentra el elemento mínimo, se intercambia con el primer elemento de la lista (si estaban desordenados).\n");
    printf(".-Repeticion: Se repite el proceso con el resto de la lista, excluyendo el elemento ya ordenado. Es decir, se busca el próximo elemento más pequeño (o grande) entre los elementos no ordenados y se intercambia con el segundo lugar de la lista, y así sucesivamente.\n");
    printf("\n");

    struct Libro listaLibros[100]; // Supongamos que tenemos espacio para 100 libros
    int numLibros = 0;

    printf("Agregue los libros a la lista manualmente:\n");
    agregarLibrosManual(listaLibros, &numLibros);

    printf("\nLista de libros antes de la ordenación por ID:\n");
    for (int i = 0; i < numLibros; i++) {
        printf("ID: %d, Título: %s\n", listaLibros[i].id, listaLibros[i].titulo);
    }

    ordenarPorID(listaLibros, numLibros);

    printf("\nLista de libros después de la ordenación por ID:\n");
    for (int i = 0; i < numLibros; i++) {
        printf("ID: %d, Título: %s\n", listaLibros[i].id, listaLibros[i].titulo);
    }
}


// Función principal para la sección de algoritmos de búsqueda
void algoritmosBusqueda() {
    printf("Tema 4: Algoritmos de búsqueda\n");
    printf("La búsqueda secuencial es un método simple para encontrar un elemento específico en una lista.");
    printf("\n");
    printf(".-Recorrido de la lista: El algoritmo comienza desde el principio de la lista y recorre secuencialmente cada elemento.\n");
    printf(".-Comparación: En cada paso, compara el elemento actual de la lista con el elemento que estás buscando.\n");
    printf(".-Coincidencia: Si el elemento actual coincide con el que estás buscando, se ha encontrado el elemento deseado y el algoritmo devuelve su posición en la lista.\n");
    printf(".-Finalización: Si el elemento buscado no se encuentra en la lista, el algoritmo recorre toda la lista y devuelve un valor para indicar que el elemento no está presente.\n");
    printf("\n");

    struct Libro listaLibros[100]; // Supongamos que tenemos espacio para 100 libros
    int numLibros = 0;

    printf("Agregue los libros a la lista manualmente:\n");
    agregarLibrosManual(listaLibros, &numLibros);

    printf("\nLista de libros:\n");
    for (int i = 0; i < numLibros; i++) {
        printf("ID: %d, Título: %s\n", listaLibros[i].id, listaLibros[i].titulo);
    }

    int buscarID;
    printf("\nIngrese el ID del libro que desea buscar: ");
    scanf("%d", &buscarID);

    int posicion = buscarPorID(listaLibros, numLibros, buscarID);

    if (posicion != -1) {
        printf("Libro encontrado en la posición %d\n", posicion);
    } else {
        printf("El libro no fue encontrado en la lista.\n");
    }
}

int main(){
    int noTema = 2;
    
    printf("Bienvenido al curso de estructuras de datos!!!\n");
    printf("En este programa vamos a darle un uso a las estructuras vistas en el curso a un caso práctico en una tienda de libros.\n");
    printf("Cada estructura y algoritmo va a utilizar los datos básicos de un libro para realizar su propia función.");
    printf("Para seleccionar el tema que desea explorar, seleccione entre las siguientes opciones: \nTema 1: Estructuras Fundamentales\nTema 2: Estructuras Avanzadas\nTema 3: Algoritmos de Ordenamiento\nTema 4: Algoritmos de Busqueda\n");
    scanf("%d", &noTema);

    switch(noTema){
        case 1: 
            estructurasFundamentales();
            break;
        case 2:
            estructurasAvanzadas();
            break;
        case 3:
            algoritmosOrdenamiento();
            break;
        case 4:
            algoritmosBusqueda();
            break;
    }

    return 0;
}