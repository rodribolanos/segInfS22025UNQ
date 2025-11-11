#include "aes_utils.h"
#include "array_rotation.h"


void shiftRows(unsigned char state[BLOCK_SIDE][BLOCK_SIDE]){
    leftRotate(state[1], 1, BLOCK_SIDE);
    leftRotate(state[2], 2, BLOCK_SIDE);
    rightRotate(state[3], 1, BLOCK_SIDE);
} // tambien se puede hacer como

void shiftRows2(unsigned char state[BLOCK_SIDE][BLOCK_SIDE]){
    for(int i = 1; i < BLOCK_SIDE; i++){
        leftRotate(state[i], i, BLOCK_SIDE); 
        // de esta forma se rota 1, 2 y 3 veces a la izquierda respectivamente como esta especificado en el algoritmo
    }
}


/*
    state = [[]
                []
                    []
                        []]
*/

int main(int argc, char* argv[]){

    key[BLOCK_SIDE][BLOCK_SIDE];
    // el main va a quedar algo como:
    state[BLOCK_SIDE][BLOCK_SIDE]; // TODO: ejemplo
    addRoundKey(state, key);

    for(int round = 0; round < N; n++){
        subBytes(state);
        shiftRows(state);
    }



}