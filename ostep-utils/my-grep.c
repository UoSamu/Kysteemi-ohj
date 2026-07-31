#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Apufunktio lukemisia (tiedostot ja näppäimet(stdin)) varten
void grep_stream(FILE *stream, const char *searchterm) {
    char *line = NULL;
    size_t len = 0;
    
    // getline, rivilukumuistivaraus
    while (getline(&line, &len, stream) != -1) {
        
        // strstr tarkistaa, jos searchtermi line-rivillä, löytyessä printti
        if (strstr(line, searchterm) != NULL) {
            printf("%s", line);
        }
    }
    free(line);// getline vapautus
}

int main(int argc, char *argv[])    //argumenttie tarkastamine
{
    if (argc < 2) {
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }

    const char *searchterm = argv[1]; //searchtermi nimenjälkee eka argumentti

    if (argc == 2) {
        grep_stream(stdin, searchterm); //Jos ei annettu tiedostoja, standardisyötteesee
    } 
    // Muuten käydään läpi kaikki cmdline luetellut tiedostot
    else {
        //Jos tiedosto alkaa indeksistä 2
        for (int i = 2; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            
            if (fp == NULL) {
                printf("my-grep: cannot open file\n");
                exit(1);
            }
            
            grep_stream(fp, searchterm);         
            fclose(fp);
        }
    }

    return 0;
}