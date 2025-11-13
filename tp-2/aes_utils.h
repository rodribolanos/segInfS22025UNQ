
#ifndef AES_H
#define AES_H

#define BLOCK_LEN 16 // Tamaño total del bloque de bytes
#define BLOCK_DIM 4 // Dimension del bloque de bytes

#define AES_PRIMITIVE 0x11b // 0001 0001 1011  x^8+x^4+x^3+x+1 primitivo

// Matriz de sustitución con el inverso multiplicativo de cada valor dentro del cuerpo de 8 bits 
extern unsigned char s_box[256];
// Matriz de multiplicación al momento de mezclar las columnas del bloque 
extern unsigned char mix_col_matrix[BLOCK_DIM][BLOCK_DIM];



// Multiplicación cerrada entre dos bytes 
unsigned char closedMult(unsigned char b1, unsigned char b2);




// ====== ETAPAS DEL CIFRADO ======

void addRoundKey(unsigned char state[BLOCK_DIM][BLOCK_DIM], unsigned char expanded_key[BLOCK_DIM][BLOCK_DIM]);
void shiftRows(unsigned char state[BLOCK_DIM][BLOCK_DIM]);
void subByte(unsigned char state[BLOCK_DIM][BLOCK_DIM]);
void mixColumns(unsigned char state[BLOCK_DIM][BLOCK_DIM]);

// ====== ETAPAS DEL CIFRADO ======

// === Key schedule ===
void generateKeySchedule(unsigned char *key, unsigned char subkeys[][BLOCK_DIM][BLOCK_DIM]);
void generateKeySchedule256(unsigned char *key, unsigned char subkeys[15][BLOCK_DIM][BLOCK_DIM]);

// Cifrado 
// TODO: (capaz pasar a otro header)

void cipher_block(unsigned char *in, int n, unsigned char subkeys[][BLOCK_DIM][BLOCK_DIM], int nr, unsigned char out[BLOCK_LEN]);
void cipher(unsigned char *in_text, int n, unsigned char *in_key, int keylen, unsigned char **out);



#endif