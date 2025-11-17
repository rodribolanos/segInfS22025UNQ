/**
 * reverseArray - Invierte el orden de los elementos en un rango del array
 * 
 * Esta función invierte los elementos del array entre las posiciones 'start' y 'end' (inclusive).
 * 
 * Paso a paso:
 * 1. Mientras start sea menor que end (no se han cruzado los índices):
 *    a. Guarda temporalmente el valor en la posición start
 *    b. Copia el valor de la posición end a la posición start
 *    c. Copia el valor temporal (original de start) a la posición end
 *    d. Incrementa start para avanzar desde el principio
 *    e. Decrementa end para avanzar desde el final
 * 2. El proceso se repite hasta que start >= end, momento en que el rango está completamente invertido
 * 
 * Ejemplo: array = [1,2,3,4,5], start=0, end=4
 *   - Iteración 1: intercambia array[0] y array[4] -> [5,2,3,4,1]
 *   - Iteración 2: intercambia array[1] y array[3] -> [5,4,3,2,1]
 *   - Iteración 3: start=2, end=2 (terminó)
 * 
 * @param array: Puntero al array de unsigned char a invertir
 * @param start: Índice inicial del rango a invertir
 * @param end: Índice final del rango a invertir
 */
void reverseArray(unsigned char *array, int start, int end){
    while(start < end){
        unsigned char temp = array[start];
        array[start] = array[end];
        array[end] = temp;
        start++;
        end--;
    }
}

/**
 * leftRotate - Rota el array 'pos' posiciones hacia la izquierda
 * 
 * Esta función realiza una rotación del array hacia la izquierda utilizando
 * el algoritmo de inversión triple. Es eficiente y se ejecuta en O(n) tiempo.
 * 
 * Algoritmo de inversión triple:
 * Para rotar un array 'pos' posiciones a la izquierda:
 * 1. Invertir los primeros 'pos' elementos
 * 2. Invertir los elementos restantes (desde pos hasta n-1)
 * 3. Invertir todo el array
 * 
 * Paso a paso con ejemplo: array = [1,2,3,4,5,6], pos=2, n=6
 *   Estado inicial: [1,2,3,4,5,6]
 *   
 *   Paso 1 - reverseArray(array, 0, pos-1):
 *     Invierte los primeros 2 elementos (índices 0 a 1)
 *     Resultado: [2,1,3,4,5,6]
 *   
 *   Paso 2 - reverseArray(array, pos, n-1):
 *     Invierte desde índice 2 hasta el final (índices 2 a 5)
 *     Resultado: [2,1,6,5,4,3]
 *   
 *   Paso 3 - reverseArray(array, 0, n-1):
 *     Invierte todo el array
 *     Resultado final: [3,4,5,6,1,2]
 *   
 *   Los primeros 2 elementos (1,2) se movieron al final -> rotación izquierda de 2 posiciones
 * 
 * @param array: Puntero al array de unsigned char a rotar
 * @param pos: Número de posiciones a rotar hacia la izquierda
 * @param n: Tamaño total del array
 */
void leftRotate(unsigned char *array, int pos, int n){
    reverseArray(array, 0, pos-1);
    reverseArray(array, pos, n-1);
    reverseArray(array, 0, n-1);
}

/**
 * rightRotate - Rota el array 'pos' posiciones hacia la derecha
 * 
 * Esta función realiza una rotación del array hacia la derecha reutilizando
 * la función leftRotate con una conversión matemática inteligente.
 * 
 * Concepto clave:
 * Rotar 'pos' posiciones a la derecha es equivalente a rotar (n-pos) posiciones a la izquierda.
 * 
 * Explicación matemática:
 * - Array de tamaño n
 * - Rotar derecha pos posiciones = mover los últimos pos elementos al inicio
 * - Rotar izquierda (n-pos) posiciones = mover los primeros (n-pos) elementos al final
 * - Ambas operaciones producen el mismo resultado
 * 
 * Paso a paso con ejemplo: array = [1,2,3,4,5,6], pos=2, n=6
 *   Queremos rotar 2 posiciones a la derecha: [1,2,3,4,5,6] -> [5,6,1,2,3,4]
 *   
 *   Conversión: rightRotate(array, 2, 6) = leftRotate(array, 6-2, 6) = leftRotate(array, 4, 6)
 *   
 *   leftRotate con pos=4:
 *     Estado inicial: [1,2,3,4,5,6]
 *     Invierte primeros 4: [4,3,2,1,5,6]
 *     Invierte últimos 2: [4,3,2,1,6,5]
 *     Invierte todo: [5,6,1,2,3,4]
 *   
 *   Resultado: [5,6,1,2,3,4] ✓ Los últimos 2 elementos ahora están al principio
 * 
 * Ventaja: No necesitamos duplicar código; reutilizamos leftRotate con el complemento.
 * 
 * @param array: Puntero al array de unsigned char a rotar
 * @param pos: Número de posiciones a rotar hacia la derecha
 * @param n: Tamaño total del array
 */
void rightRotate(unsigned char *array, int pos, int n){
    leftRotate(array, n-pos, n); 
    // Se puede definir uno en base al otro usando el complemento de la cantidad de posiciones que se quiere rotar
}