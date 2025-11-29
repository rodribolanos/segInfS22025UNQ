
#ifndef AES_H
#define AES_H

#define BLOCK_LEN 16 // Tamaño total del bloque de bytes
#define BLOCK_DIM 4 // Dimension del bloque de bytes
#define AES_256_NR 14

#define AES_PRIMITIVE 0x1b // 0001 0001 1011  x^8+x^4+x^3+x+1 es el primitivo, pero se truca el primer 1 por lo que queda 1b

// Tabla de busqueda del "inverso multiplicativo" de cada valor dentro de los 8 bits 
extern unsigned char s_box[256];
// Matriz de multiplicación al momento de mezclar las columnas del bloque 
extern unsigned char mix_col_matrix[BLOCK_DIM][BLOCK_DIM];

extern unsigned char inv_s_box[256];

extern unsigned char inv_mix_col_matrix[BLOCK_DIM][BLOCK_DIM];





// Multiplicación cerrada entre dos bytes 
unsigned char closedMult(unsigned char b1, unsigned char b2);




// ====== ETAPAS DE ENCRIPTACION ======

void addRoundKey(unsigned char state[BLOCK_DIM][BLOCK_DIM], unsigned char expanded_key[BLOCK_DIM][BLOCK_DIM]);
void shiftRows(unsigned char state[BLOCK_DIM][BLOCK_DIM]);
void subByte(unsigned char state[BLOCK_DIM][BLOCK_DIM]);
void mixColumns(unsigned char state[BLOCK_DIM][BLOCK_DIM]);

// ====== ETAPAS DE ENCRIPTACION ======

// === Key schedule ===
void generateKeySchedule(unsigned char *key, unsigned char subkeys[][BLOCK_DIM][BLOCK_DIM]);
void generateKeySchedule256(unsigned char *key, unsigned char subkeys[15][BLOCK_DIM][BLOCK_DIM]);


// Cifrado 
void cipher_block(unsigned char *in, int n, unsigned char subkeys[15][BLOCK_DIM][BLOCK_DIM], int nr, unsigned char out[BLOCK_LEN]);
int cipher(unsigned char *in_text, int n, unsigned char subkeys[15][BLOCK_DIM][BLOCK_DIM], unsigned char **out);



// ====== ETAPAS DE DESENCRIPTACION ======

void inv_shiftRows(unsigned char state[BLOCK_DIM][BLOCK_DIM]);
void inv_subByte(unsigned char state[BLOCK_DIM][BLOCK_DIM]);
void inv_mixColumns(unsigned char state[BLOCK_DIM][BLOCK_DIM]);

// ====== ETAPAS DE DESENCRIPTACION ======


// Descifrado
void inv_cipher_block(unsigned char *in, unsigned char subkeys[15][BLOCK_DIM][BLOCK_DIM], int nr, unsigned char out[BLOCK_LEN]);
int inv_cipher(unsigned char *in_cypher, int n, unsigned char subkeys[15][BLOCK_DIM][BLOCK_DIM], unsigned char **out);



#endif