#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void writeOnFich(FILE *f_entree)
{
    int c;
    int c2;
    int octet=0;
    char *tab = malloc(16*sizeof(char));
    int nbSpace=0;
    if (f_entree == stdin) {
        // TODO: read from stdin and write to stdout when octet%16 == 0
        printf("TODO: stdin xxd");
    }else {
        while ((c = fgetc(f_entree)) != EOF) {
            if ((c2 = fgetc(f_entree)) != EOF) {
                if (octet == 0) {
                    fprintf(stdout, "%08x: ", 0);
                }
                fprintf(stdout, "%02x%02x ", c, c2);
                if (isprint(c) != 0) {
                    tab[octet%16] = c;
                }else {
                    tab[octet%16] = '.';
                }
                if (isprint(c2) != 0) {
                    tab[(octet%16)+1] = c2;
                }else {
                    tab[(octet%16)+1] = '.';
                }
                octet=octet+2;
                if (octet%16 == 0) {
                    fprintf(stdout, " %s", tab);
                    fprintf(stdout, "\n%08x: ", octet);
                }
                if (tab[15] != '\0') {
                    for (int i=0; i<=15; i++){
                        tab[i] = '\0';
                    } 
                }
            }else {
                nbSpace = 16 - (octet%16);
                fprintf(stdout, "%02x   ", c);
                for (int i=0; i<=nbSpace; i++) {
                    fprintf(stdout, "  ");
                }
                if (isprint(c) != 0) {
                    tab[octet%16] = c;
                }else {
                    tab[octet%16] = '.';
                }
                fprintf(stdout, " %s", tab);
            }
        }
    }
    fprintf(stdout, "\n");
}

int main(int argc, char *argv[])
{
    FILE *f_entree;
    if (argc >2) {
        fprintf(stderr, "Usage: %s or %s [file]\n", argv[0], argv[0]);
        return -1;
    }else if (argc == 1) {
        writeOnFich(stdin);
    }else {
        f_entree = fopen(argv[1], "r");
        if (f_entree == NULL){
            perror("erreur fopen");
            return -1;
        }
        writeOnFich(f_entree);
        if (fclose(f_entree) != 0) {
            perror("erreur fclose");
            return -1;
        }
    }
    return 0;
}