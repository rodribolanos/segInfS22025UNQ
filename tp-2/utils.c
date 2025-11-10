void reverseArray(unsigned char *array, int start, int end){
    while(start < end){
        unsigned char temp = array[start];
        array[start] = array[end];
        array[end] = temp;
    }
}

void leftRotate(unsigned char *array, int pos, int n){
    reverseArray(array, 0, pos-1);
    reverseArray(array, pos, n-1);
    reverseArray(array, 0, n-1);
}

void rightRotate(unsigned char *array, int pos, int n){
    leftRotate(array, n-pos, n); 
    // Se puede definir uno en base al otro usando el complemento de la cantidad de posiciones que se quiere rotar
}