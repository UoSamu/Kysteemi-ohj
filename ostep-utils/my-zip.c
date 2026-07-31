#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])  //Jos ei tiedostoja annettu, ni käyttöohje ja poistumine:
{

    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    int count = 0;
    int current_char = EOF;
    int previous_char = EOF;

    for (int i = 1; i < argc; i++) {    //Komentorivin tiedostoje läpikäynti
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("my-zip: cannot open file\n");
            exit(1);
        }

        // fgetc, ni tiedostoluku yks merkki kerrallaa
        while ((current_char = fgetc(fp)) != EOF) {
            if (previous_char == EOF) {
                previous_char = current_char;   //ekamerkki
                count = 1;
            } else if (current_char == previous_char) { //jos merkki jatkuu, laskurin kasvatus
                count++;
            } else {
                // Uusi merkki & kirjataa edellise merki määrä ylös (int)
                fwrite(&count, sizeof(int), 1, stdout);
                char c = (char)previous_char; //Edellinen merkki (char) ja yks tavu per
                fwrite(&c, sizeof(char), 1, stdout);
                
                previous_char = current_char;
                count = 1; //nollausjee
            }
        }
        fclose(fp);
    }

// Viimeinen merkkisarja uloskirjattuna
    if (previous_char != EOF) {
        fwrite(&count, sizeof(int), 1, stdout);
        char c = (char)previous_char;
        fwrite(&c, sizeof(char), 1, stdout);
    }
    return 0;
}