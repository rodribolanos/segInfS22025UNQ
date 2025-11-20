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


int main(int argc, char* argv[]){

    unsigned char text[16] = "0123456789ABCDEF";

    unsigned char key[33] = "0123456789ABCDEF0123456789ABCDEF";
    unsigned char *out = NULL;

    int nmbBlocks = cipher(text, 16, key, 32, &out);

    printf("Texto cifrado: ");
    printHex(out, 16); 
    printf("Bloques: %d\n", nmbBlocks);

    unsigned char *out_inv = NULL;
    int outlen_inv = inv_cipher(out, nmbBlocks, key, 32, &out_inv);

    printf("Texto descifrado: ");
    printStr(out_inv, 16);
    printf("Longitud: %d\n", outlen_inv);
}
