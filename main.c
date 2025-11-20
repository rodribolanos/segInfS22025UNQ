#include <stdio.h>  
#include "aes_utils.h"
#include "string.h"



void printHex(const unsigned char *buf, int len) {
    for (int i = 0; i < len; i++)
        printf("%02x", buf[i]);
    printf("\n");
}

void printStr(const unsigned char *out, int len){
    for(int i = 0; i < len; i++)
        printf("%c", out[i]);
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
int main(int argc, char* argv[]){

    unsigned char *text = "hola.-E";

    unsigned char key[32] = "0123456789ABCDEF0123456789ABCDEF";
    unsigned char *out = NULL;

    int outlen = cipher(text, 8, key, 32, &out);

    printf("Texto ENCRIPTADO: ");
    printHex(out, 16); 
    printf("Longitud del cifrado: %d\n", outlen);

    unsigned char *out_inv = NULL;
    int outlen_inv = inv_cipher(out, outlen, key, 32, &out_inv);

    printf("Texto DESENCRIPTADO: ");
    printStr(out_inv, outlen_inv);
    printf("Longitud del original: %d\n", outlen_inv);
}
