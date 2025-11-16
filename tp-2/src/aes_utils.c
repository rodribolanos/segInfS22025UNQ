#include "aes_utils.h"
#include "array_rotation.h"
#include <stdlib.h>
#include "string.h"

unsigned char s_box[256] = {
    0x63,   0x7c,   0x77,   0x7b,   0xf2,   0x6b,   0x6f,   0xc5,   0x30,   0x01,   0x67,   0x2b,   0xfe,   0xd7,   0xab,   0x76,
    0xca,   0x82,   0xc9,   0x7d,   0xfa,   0x59,   0x47,   0xf0,   0xad,   0xd4,   0xa2,   0xaf,   0x9c,   0xa4,   0x72,   0xc0,
    0xb7,   0xfd,   0x93,   0x26,   0x36,   0x3f,   0xf7,   0xcc,   0x34,   0xa5,   0xe5,   0xf1,   0x71,   0xd8,   0x31,   0x15,
    0x04,   0xc7,   0x23,   0xc3,   0x18,   0x96,   0x05,   0x9a,   0x07,   0x12,   0x80,   0xe2,   0xeb,   0x27,   0xb2,   0x75,
    0x09,   0x83,   0x2c,   0x1a,   0x1b,   0x6e,   0x5a,   0xa0,   0x52,   0x3b,   0xd6,   0xb3,   0x29,   0xe3,   0x2f,   0x84,
     
    0x53,   0xd1,   0x00,   0xed,   0x20,   0xfc,   0xb1,   0x5b,   0x6a,   0xcb,   0xbe,   0x39,   0x4a,   0x4c,   0x58,   0xcf,
    0xd0,   0xef,   0xaa,   0xfb,   0x43,   0x4d,   0x33,   0x85,   0x45,   0xf9,   0x02,   0x7f,   0x50,   0x3c,   0x9f,   0xa8,
    0x51,   0xa3,   0x40,   0x8f,   0x92,   0x9d,   0x38,   0xf5,   0xbc,   0xb6,   0xda,   0x21,   0x10,   0xff,   0xf3,   0xd2,
    0xcd,   0x0c,   0x13,   0xec,   0x5f,   0x97,   0x44,   0x17,   0xc4,   0xa7,   0x7e,   0x3d,   0x64,   0x5d,   0x19,   0x73,
    0x60,   0x81,   0x4f,   0xdc,   0x22,   0x2a,   0x90,   0x88,   0x46,   0xee,   0xb8,   0x14,   0xde,   0x5e,   0x0b,   0xdb,
    0xe0,   0x32,   0x3a,   0x0a,   0x49,   0x06,   0x24,   0x5c,   0xc2,   0xd3,   0xac,   0x62,   0x91,   0x95,   0xe4,   0x79,
    0xe7,   0xc8,   0x37,   0x6d,   0x8d,   0xd5,   0x4e,   0xa9,   0x6c,   0x56,   0xf4,   0xea,   0x65,   0x7a,   0xae,   0x08,
    0xba,   0x78,   0x25,   0x2e,   0x1c,   0xa6,   0xb4,   0xc6,   0xe8,   0xdd,   0x74,   0x1f,   0x4b,   0xbd,   0x8b,   0x8a,
    0x70,   0x3e,   0xb5,   0x66,   0x48,   0x03,   0xf6,   0x0e,   0x61,   0x35,   0x57,   0xb9,   0x86,   0xc1,   0x1d,   0x9e,
    0xe1,   0xf8,   0x98,   0x11,   0x69,   0xd9,   0x8e,   0x94,   0x9b,   0x1e,   0x87,   0xe9,   0xce,   0x55,   0x28,   0xdf,
    0x8c,   0xa1,   0x89,   0x0d,   0xbf,   0xe6,   0x42,   0x68,   0x41,   0x99,   0x2d,   0x0f,   0xb0,   0x54,   0xbb,   0x16
};
 
unsigned char mix_col_matrix[BLOCK_DIM][BLOCK_DIM] = {
    { 0x02, 0x03, 0x01, 0x01 },  
    { 0x01, 0x02, 0x03, 0x01 }, 
    { 0x01, 0x01, 0x02, 0x03 }, 
    { 0x03, 0x01, 0x01, 0x02 } 
};

unsigned char closedMult(unsigned char a, unsigned char b){

    unsigned char p = 0;

    for(int i = 0; i < 8; i++){
        /* 
            La invariante es que a*b + p va a ser el producto en cada instancia del loop
            y solo se suma en los casos en que b sea impar
        */

        if(b & 0x01){ 
           p ^= a; 
        } 

        b >>= 1; // divide por x


        unsigned char carry = a & 0x80;
        a <<= 1; // multiplica por x
        
        // si x^7 era 1 entonces se esta saliendo de los 8 bits al multiplicar por x por lo que se aplica el modulo con el primitivo
        if (carry){ 
            a ^= AES_PRIMITIVE; 
        }
    }
    /*
    0001 1010 1000
    0001 0001 1011
    como + = - = mod = xor
    0000 1011 0011
    */
    
    return p;

}


void addRoundKey(unsigned char state[BLOCK_DIM][BLOCK_DIM], unsigned char expanded_key[BLOCK_DIM][BLOCK_DIM]){
    // la suma de la clave al bloque cifrado
    for(int i = 0; i < BLOCK_DIM; i++){
        for(int j = 0; j < BLOCK_DIM; j++){
            state[i][j] ^= expanded_key[i][j]; 
        }
    }
}

void subBytes(unsigned char state[BLOCK_DIM][BLOCK_DIM]){
    // sustitucion de byte por el inverso multiplicativo
    for(int i = 0; i < BLOCK_DIM; i++){
        for(int j = 0; j < BLOCK_DIM; j++){
            state[i][j] = s_box[state[i][j]]; 
        }
    }
}


void shiftRows(unsigned char state[BLOCK_DIM][BLOCK_DIM]){
    for(int i = 1; i < BLOCK_DIM; i++){
        leftRotate(state[i], i, BLOCK_DIM); 
    }
}


void mixColumns(unsigned char state[BLOCK_DIM][BLOCK_DIM]){
    // mix_col_matrix * state
    unsigned char acc[BLOCK_DIM][BLOCK_DIM];

    for(int i = 0; i < BLOCK_DIM; i++){
        for(int j = 0; j < BLOCK_DIM; j++){
            
            acc[i][j] = 0x00;

            for(int h = 0; h < BLOCK_DIM; h++){
                acc[i][j] ^= closedMult(mix_col_matrix[i][h], state[h][j]);
            }

        }
    }

    memcpy(state, acc, BLOCK_DIM * BLOCK_DIM * sizeof(unsigned char)); // se podria usar un for tmb
}




void generateKeySchedule256(unsigned char *key, unsigned char subkeys[15][BLOCK_DIM][BLOCK_DIM]){

    int block;
    for(block = 0; block < 8; block++){

        int round  = block >> 2;
        /*
            van a ir 16 bytes en un round y 16 en otro porque es la division por 4
        */

        int j = block & 0x03; // 0000 0011
        /*
          es el resto de la division anterior
        */

        for(int i = 0; i< BLOCK_DIM; i++){
            subkeys[round][i][j] = key[block * BLOCK_DIM + i];
        }
    }
    

    unsigned char rcon = 0x01;
    
    // Este es el ultimo byte guardado
    int last_round = 1, last_col = 3;

    for(block = 8; block < 60; block++){
        int round = block >> 2; 
        int j = block & 0x03;

        int xor_last_round = round - 2; // como block arranca en 8 entonces round siempre es >= 2
        int xor_last_col = j;


        /*
            block = 8 = 1000
            1000 & 0111 = 0000
            ! 0000 = 1111
        */

        if(!(block & 0x07)){ // Si el resto del bloque actual dividido 8 es 0
            unsigned char temp[4] = {
                s_box[subkeys[last_round][1][last_col]] ^ rcon,
                s_box[subkeys[last_round][2][last_col]],
                s_box[subkeys[last_round][3][last_col]],
                s_box[subkeys[last_round][0][last_col]] 
                // no vale la pena usar shiftrows aca, es un bardo
            };

            for (int i = 0; i < BLOCK_DIM; i++){
                subkeys[round][i][j] = subkeys[xor_last_round][i][xor_last_col] ^ temp[i];
            }

            rcon = closedMult(rcon, 0x02); // se multiplica rcon por x

          // la condicion de nk > 6 se ignora porque es 256
        } else if (!(block & 0x03)){ // Idem pero con 4 
            for(int i = 0; i < BLOCK_DIM; i++){
                subkeys[round][i][j] = subkeys[xor_last_round][i][xor_last_col] ^ s_box[subkeys[last_round][i][last_col]];
            }
        } else {
            for(int i = 0; i < BLOCK_DIM; i++){
                subkeys[round][i][j] = subkeys[xor_last_round][i][xor_last_col] ^ subkeys[last_round][i][last_col];
            }
        }

        last_round = round;
        last_col = j;
        // estos dos serian el w[i - 1]
    }
    /*
    pseudocodigo del paper de AES
    procedure KEY EXPANSION (key)
        i ← 0
        while i ≤ Nk − 1 do
            w[i] ← key[4 ∗ i..4 ∗ i + 3]
            i ← i + 1
        end while . When the loop concludes, i = Nk.
        while i ≤ 4 ∗ Nr + 3 do
            temp ← w[i − 1]
            if i mod Nk = 0 then
                temp ← SUB WORD(R OT W ORD(temp)) ⊕ Rcon[i/Nk]
            else if Nk > 6 and i mod Nk = 4 then
                temp ← SUB WORD(temp)
            end if
            w[i] ← w[i − Nk] ⊕ temp
            i ← i + 1
        end while
        return w
    end procedure
    
    
    */
}



// PRECOND: La key se expandió en subkeys por medio del algoritmo
void cipher_block(unsigned char *in_text, int n, unsigned char subkeys[][BLOCK_DIM][BLOCK_DIM], int nr, unsigned char out[BLOCK_LEN]){
    
    // SETUP 
    unsigned char state[BLOCK_DIM][BLOCK_DIM];
    
    int index = 0;
    for(int i = 0; i < BLOCK_DIM; i++){
        for(int j = 0; j < BLOCK_DIM; j++){
            if(index < n){
                state[i][j] = in_text[index];
                index++;
            } else {
                state[i][j] = 0;
            }
        }
    }

    // ROUND 0
    addRoundKey(state, subkeys[0]);

    // ROUNDS 1 a NR - 1
    for (int i = 1; i < nr; i++){
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state, subkeys[i]);
    }

    // FINAL ROUND
    subBytes(state);
    shiftRows(state);
    addRoundKey(state, subkeys[nr]);


    // retorno
    index = 0;
    // aca se invierten los indices porque la copia es columnar
    // creo que no se puede usar memcpy porque la copia no es 1-1 si no que se traspone la matriz
    for (int j = 0; j < BLOCK_DIM; j++){
        for(int i = 0; i < BLOCK_DIM; i++){
            out[index] = state[i][j];
            index++;
        }
    }
}


int cipher(unsigned char *in_text, int n, unsigned char *in_key, int keylen, unsigned char **out){
    unsigned char (*subkeys)[BLOCK_DIM][BLOCK_DIM] = malloc((AES_256_NR + 1) * sizeof(unsigned char[BLOCK_DIM][BLOCK_DIM]));
    generateKeySchedule256(in_key, subkeys);

    int nmbBlocks = n / BLOCK_LEN;
    int extra = n & 0x0F; // El resto por el bloque final incompleto
    
    int outLen = nmbBlocks * BLOCK_LEN;

    if(extra){
        *out = malloc((nmbBlocks + 1) * BLOCK_LEN * sizeof(unsigned char));
        outLen += BLOCK_LEN;
        int padding_extra_block = nmbBlocks * BLOCK_LEN;
        // cifrar el bloque extra de primera
        cipher_block(in_text + padding_extra_block, extra, subkeys, AES_256_NR,  *out + padding_extra_block);
    }

    *out = malloc(nmbBlocks * BLOCK_LEN * sizeof(unsigned char));
     
    for(int i = 0; i < nmbBlocks; i++){
        cipher_block(in_text + (i * BLOCK_LEN), BLOCK_LEN, subkeys, AES_256_NR,  *out + (i * BLOCK_LEN));
    }

    free(subkeys);

    return outLen;
}