#include <stdio.h>  
#include "aes_utils.h"
#include "string.h"



void printHexArray(unsigned char* hexString){
    int i = 0;
    while(i != '\0'){
        printf("%x", hexString[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]){

    char *text = "EstaEsMiClaveDe32AAAABITSsldslds";
    char *key = "clavesupersecretade32bitsdelarga";

    unsigned char *out = NULL;
    
    
    cipher(text, strlen(text), key, strlen(key), &out);

    printHexArray(out);

}
