#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
// Jos ei tiedostoja, virhetulostumine ja poistumine
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) //Käydään läpi annetut pakatut tiedostot
    {
        FILE *fp = fopen(argv[i], "r"); //Lukeminen 
        if (fp == NULL) {
            printf("my-unzip: cannot open file\n");
            exit(1);
        }

        int count;
        char character;

        // fread:illa luettujen alkioiden määrä
        while (fread(&count, sizeof(int), 1, fp) == 1) {    // ja kokonaisluvun lukeminen
            
            // Jos luvun lukeminen onnistui, niin perään luetaan merkki
            if (fread(&character, sizeof(char), 1, fp) == 1) {
                for (int j = 0; j < count; j++) //tulostus count määrän verta
                {
                    printf("%c", character);
                }
            }
        }
        fclose(fp);
    }
    return 0;
}