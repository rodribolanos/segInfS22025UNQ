/**
 * FUNCIONES DE ROTACIÓN DE ARRAYS
 * 
 * Este módulo proporciona funciones para rotar arrays de bytes (unsigned char).
 * Las rotaciones son útiles en criptografía, especialmente en algoritmos como AES.
 * 
 * Utiliza el algoritmo de inversión triple para lograr rotaciones eficientes en O(n).
 */

/**
 * reverseArray - Invierte un rango de elementos en el array
 * @param array: Array a modificar
 * @param start: Índice inicial del rango
 * @param end: Índice final del rango
 */
void reverseArray(unsigned char *array, int start, int end);

/**
 * leftRotate - Rota el array hacia la izquierda
 * @param array: Array a rotar
 * @param pos: Número de posiciones a rotar hacia la izquierda
 * @param n: Tamaño del array
 */
void leftRotate(unsigned char *array, int pos, int n);

/**
 * rightRotate - Rota el array hacia la derecha
 * @param array: Array a rotar
 * @param pos: Número de posiciones a rotar hacia la derecha
 * @param n: Tamaño del array
 */
void rightRotate(unsigned char *array, int pos, int n);