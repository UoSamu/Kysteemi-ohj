#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])    //Jos ei tiedostoa, ni returni 0
{
    if (argc == 1) {
        return 0;
    }

    //Annetut tiedostot annetut tiedostot läpikäynti, indeksi 1 (0 olis ohj nimi.)
    for (int i = 1; i < argc; i++) {
        
        FILE *fp = fopen(argv[i], "r"); //lukutila tiedostolle
        
        if (fp == NULL) {
            printf("my-cat: cannot open file\n");
            exit(1); // virhetarkistus, jos ei löudu tiedostoa/ei avaa
        }

    // Pala kerrallaan bufferiin ja tulostetaan
        char buffer[4096]; //riittävästi väliaikamuistia
        
        while (fgets(buffer, sizeof(buffer), fp) != NULL) { //fgets tehtävänantosuositus
            printf("%s", buffer);
        }
        fclose(fp);
    }
    return 0;
}