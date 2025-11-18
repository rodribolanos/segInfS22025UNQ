#include <stdio.h>  
#include "aes_utils.h"
#include "string.h"



void printHex(const unsigned char *buf, int len) {
    for (int i = 0; i < len; i++)
        printf("%02x", buf[i]);
    printf("\n");
}




int main(int argc, char* argv[]){

    unsigned char text[16] = "0123456789ABCDEF";

    unsigned char key[33] = "0123456789ABCDEF0123456789ABCDEF";
    unsigned char *out = NULL;

    cipher(text, 16, key, 32, &out);

    
    printHex(out, 16); 
}
