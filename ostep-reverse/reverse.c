#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linkitetyy listaa nodet 
typedef struct Node {
    char *line;         // Pointterit tekstirivii,
    struct Node *next; // solmuihin
} Node;

int main(int argc, char *argv[]) //Argumentit ja virhetarkastuss
{
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    FILE *in = stdin;
    FILE *out = stdout;

    if (argc >= 2) {
        in = fopen(argv[1], "r");
        if (in == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }

    if (argc == 3) {
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }
        out = fopen(argv[2], "w");
        if (out == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
    }

    // Itse listan rakennus ja lukeminen. Lista null alkuun.
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    
    Node *head = NULL;

    while ((nread = getline(&line, &len, in)) != -1) {
        // Muistivaraus, uudelle solmulle
        Node *new_node = malloc(sizeof(Node));
        if (new_node == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        
        // strdup komennolla autom. taustaprosessi 
        // (oikeamäärä muistia varataan riville jonne kopioi sen) 
        new_node->line = strdup(line);
        if (new_node->line == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        
        //Uus solmu listan alkuu (kääntää/reverse siittö)
        new_node->next = head;
        head = new_node;
    }
    free(line); //Getline vapaaks

    // Lista valmiiks käännetty ni tulostaminen
    Node *current = head;
    while (current != NULL) {
        fprintf(out, "%s", current->line);
        current = current->next; // Siirrytään seuraavaan solmuun
    }

    // Muistin vapautus
    current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->line); // strdup:n vapautus
        free(temp);       // Noden vapautus
    }


    if (in != stdin) fclose(in);
    if (out != stdout) fclose(out);//sulkemiset! 

    return 0;
}