
#ifndef AES_H
#define AES_H

#define BLOCK_LEN 16 // Tamaño total del bloque de bytes
#define BLOCK_DIM 4 // Dimension del bloque de bytes


// Matriz de sustitución que funciona como map con el inverso multiplicativo de cada valor dentro del cuerpo de 8 bits 
extern unsigned char s_box[256];
// Matriz de multiplicación al momento de mezclar las columnas del bloque a cifrar
extern unsigned char mix_col_matrix[BLOCK_DIM][BLOCK_DIM];



// Multiplicación cerrada entre dos bytes en el cuerpo  
unsigned char closedMult(unsigned char b1, unsigned char b2);




// ====== OPERACIONES DEFINIDAS PARA EL CIFRADO ======

void addRoundKey(unsigned char state[BLOCK_DIM][BLOCK_DIM], unsigned char expanded_key[BLOCK_DIM][BLOCK_DIM]);
void shiftRows(unsigned char state[BLOCK_DIM][BLOCK_DIM]);
void subByte(unsigned char state[BLOCK_DIM][BLOCK_DIM]);
void mixColumns(unsigned char state[BLOCK_DIM][BLOCK_DIM]);

// ====== OPERACIONES DEFINIDAS PARA EL CIFRADO ======



#endif