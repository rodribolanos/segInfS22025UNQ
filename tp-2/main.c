#include "aes_utils.h"
#include "array_rotation.h"


int main(int argc, char* argv[]){

    key[BLOCK_DIM][BLOCK_DIM];
    // el main va a quedar algo como:
    state[BLOCK_DIM][BLOCK_DIM]; // TODO: ejemplo
    addRoundKey(state, key);

    for(int round = 0; round < N; n++){
        subBytes(state);
        shiftRows(state);
    }



}