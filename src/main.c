#include <stdio.h>  
#include "aes_utils.h"
#include <stdlib.h>
#include <string.h>

void exit_bad_usage(){
    fprintf(stderr,
    "Comandos:\n"
            "\t-e keyfile inputfile outputfile para encriptar\n"
            "\t-d keyfile inputfile outputfile para desencriptar\n");
    exit(EXIT_FAILURE);
}


static void read_key(const char* key_path, unsigned char key[32]){
    FILE* key_file = fopen(key_path, "rb");

    if(!key_file){
        fprintf(stderr, "ERROR LEYENDO KEY\n");
        exit(EXIT_FAILURE);
    }


    size_t keylen = fread(key, sizeof(unsigned char), 32, key_file);
    fclose(key_file);

    if(keylen != 32){
        fprintf(stderr, "La key debe tener una longitud exacta de 32 caracteres/bytes\n");
        exit(EXIT_FAILURE);
    }

} 

void process_encrypt(FILE *in, FILE *out,
                     unsigned char (*subkeys)[BLOCK_DIM][BLOCK_DIM]) {

    unsigned char block[BLOCK_LEN];
    unsigned char outblock[BLOCK_LEN];

    size_t n;
    while ((n = fread(block, 1, BLOCK_LEN, in)) == BLOCK_LEN) {
        cipher_block(block, BLOCK_LEN, subkeys, AES_256_NR, outblock);
        fwrite(outblock, 1, BLOCK_LEN, out);
    }

    if (n > 0) {
        unsigned char *trailing_block = NULL;
        int out_n = cipher(block, n, subkeys, &trailing_block);  
        fwrite(trailing_block, 1, out_n, out);
        free(trailing_block);
    }
}

void process_decrypt(FILE *in_file, FILE *out_file,
                     unsigned char (*subkeys)[BLOCK_DIM][BLOCK_DIM]) {

    unsigned char cur[BLOCK_LEN];
    unsigned char next[BLOCK_LEN];
    unsigned char outblock[BLOCK_LEN];

    size_t ncur = fread(cur, 1, BLOCK_LEN, in_file);
    if (ncur == 0) {
        fprintf(stderr, "Texto cifrado vacio\n");
        return; 
    }


    if (ncur < BLOCK_LEN) {
        fprintf(stderr, "No se puede descifrar el texto ya que el bloque esta incompleto\n");
        exit(EXIT_FAILURE);
    }

    size_t nnext;
    while ((nnext = fread(next, 1, BLOCK_LEN, in_file)) != 0) {

        if (nnext == BLOCK_LEN) {
            inv_cipher_block(cur, subkeys, AES_256_NR, outblock);

            if (fwrite(outblock, 1, BLOCK_LEN, out_file) != BLOCK_LEN) {
                perror("write");
                exit(EXIT_FAILURE);
            }

            memcpy(cur, next, BLOCK_LEN);

        } else {
            fprintf(stderr, "No se puede descifrar el texto ya que el bloque esta incompleto\n");
            exit(EXIT_FAILURE);
        }
    }
    
    unsigned char *out = NULL;
    int out_n = inv_cipher(cur, BLOCK_LEN, subkeys, &out);

    if (!out) {
        fprintf(stderr, "Error al descifrar el padding\n");
        exit(EXIT_FAILURE);
    }

    if (fwrite(out, 1, out_n, out_file) != out_n) {
        perror("write");
        free(out);
        exit(EXIT_FAILURE);
    }


}



int main(int argc, char** argv){

    if(argc != 5){
        exit_bad_usage();
    }

    int is_encrypting = 0;

    if(strcmp(argv[1], "-e") == 0){
        is_encrypting = 1;
    } else if(strcmp(argv[1], "-d") != 0){  // en este caso pasó un arg distinto de desencriptar
        exit_bad_usage();
    }

    const char *key_path = argv[2];
    const char *in_path  = argv[3];
    const char *out_path = argv[4];
    
    unsigned char key[32];
    read_key(key_path, key);

    unsigned char (*subkeys)[BLOCK_DIM][BLOCK_DIM] = malloc((AES_256_NR + 1) * sizeof(unsigned char[BLOCK_DIM][BLOCK_DIM]));;
    generateKeySchedule256(key, subkeys);

    
    FILE *in_file  = fopen(in_path, "rb");
    if (!in_file) { 
        perror("input"); 
        exit(EXIT_FAILURE); 
    }

    FILE *out_file = fopen(out_path, "wb");
    if (!out_file) { 
        perror("output");
        exit(EXIT_FAILURE);
    }

    if(is_encrypting){
        process_encrypt(in_file, out_file, subkeys);
    }else{
        process_decrypt(in_file, out_file, subkeys);
    }

    fclose(in_file);
    fclose(out_file);

    return 0;
}
