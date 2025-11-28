#include <stdio.h>  
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

    unsigned char *text = "0123456789abcdef";
    unsigned char *key = "00112233445566778899AABBCCDDEEFF";
    unsigned char *out = NULL;


    int outlen = cipher(text, 16, key, &out);

    printf("Texto cifrado: ");
    printHex(out, outlen);
    printf("Longitud del cifrado: %d\n", outlen);

    unsigned char *out_inv = NULL;
    int outlen_inv = inv_cipher(out, outlen, key, &out_inv);

    printf("Texto descifrado: %s\n", out_inv);
    printf("Longitud descifrado: %d\n", outlen_inv);

    return 0;
}
