#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void writeOnFich(FILE *f_entree)
{
    int c;
    int c2;
    int octet=0;
    int nbSpace=0;
    char *tab = malloc(16*sizeof(char));
    bool startLine=true;
    if (f_entree == stdin) {
        // TODO: read from stdin and write to stdout when octet%16 == 0
        printf("TODO: stdin xxd\n");
    }else {
        while ((c = fgetc(f_entree)) != EOF) {
            // if we are at the beginning of a line
            if (startLine == true) {
                fprintf(stdout, "%08x:", octet);
            }
            startLine=false;
            // if we have 2 char possible
            if ((c2 = fgetc(f_entree)) != EOF) {

                fprintf(stdout, " %02x%02x", c, c2);
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
                    fprintf(stdout, "  %s\n", tab);
                    startLine = true;
                }
                if (tab[15] != 0) {
                    for (int i=0; i<=15; i++){
                        tab[i] = 0;
                    }
                }
            // else if we have only one char left
            }else {
                fprintf(stdout, " %02x", c);
                nbSpace = 40 - (((octet+1)%16)*2 + ((octet+1)%16)%2 + ((octet+1)%16)/2);
                for (int i=0; i<nbSpace; i++) {
                    fprintf(stdout, " ");
                }
                if (isprint(c) != 0) {
                    tab[octet%16] = c;
                }else { 
                    tab[octet%16] = '.';
                };
                octet++;
                fprintf(stdout, "  %s\n", tab);
            }
        }
        // if the the EOF is when you haven't start a group of two octets
        if (octet%2 == 0 && octet%16 != 0) {
            nbSpace = 40-(((octet%16)*2)+((octet%16)/2));
            for (int i=0; i<nbSpace; i++) {
                fprintf(stdout, " ");
            }
            fprintf(stdout, "  %s\n", tab);
        }
    }
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