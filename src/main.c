#include <stdio.h>  
#include <stdlib.h>
#include "aes_utils.h"
#include "string.h"


void printHex(const unsigned char *buf, int len) {
    for (int i = 0; i < len; i++)
        printf("%02x", buf[i]);
    printf("\n");
}

/*
    TODO:
        - ver de implementar otros modos de encriptacion: 
            actualmente el block cipher es ECB pero se puede llegar a 
            hacer CBC y CTR
        - leer archivos para encriptar y ver de escribir la salida en un 
            file
        - manejar mejro los numeros "hardcodeados"
*/
int main(int argc, char** argv){

    char* input_filename = argv[1];
    // unsigned char* key = argv[2];

    if(input_filename == NULL){
        printf("No se ingreso un nombre de archivo");
        exit(1);
    }

    FILE *input_fileptr = fopen(input_filename, "rb");

    unsigned char text[20];

    if (input_fileptr == NULL){
        fprintf(stderr, "No se pudo abrir el file\n");
        exit(1);
    } 
    fgets(text, sizeof(text), input_fileptr);
    if(!1){
        fprintf(stderr, "Error leyendo el archivo \n");
        exit(1);
    }

    fclose(input_fileptr);

    unsigned char *key = "00112233445566778899AABBCCDDEEFF";
    unsigned char *out = NULL;

    int outlen = cipher(text, 15, key, &out);

    char* output_ext = ".bin";

    int input_filename_len = strlen(input_filename);
    int output_ext_len = strlen(output_ext);

    char* output_filename = malloc((input_filename_len + output_ext_len + 1) * sizeof(char));

    if(!output_filename){
        printf("error creando extension");
        exit(1);
    }

    memcpy(output_filename, input_filename, input_filename_len);
    memcpy(output_filename + input_filename_len, output_ext, output_ext_len + 1);

    FILE *output_fileptr = fopen(output_filename, "wb");
    free(output_filename);

    if(!output_fileptr){
        printf("error creando archivo ext");
        exit(1);
    }

    fwrite(out, sizeof(unsigned char), outlen, output_fileptr);
    fclose(output_fileptr);


    printf("Texto cifrado: ");
    printHex(out, outlen);
    printf("Longitud del cifrado: %d\n", outlen);

    unsigned char *out_inv = NULL;
    int outlen_inv = inv_cipher(out, outlen, key, &out_inv);

    printf("Texto descifrado: %s\n", out_inv);

    return 0;
}
