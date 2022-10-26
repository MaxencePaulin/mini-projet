#include <stdio.h>
#include <stdlib.h>

void writeOnFich(FILE *f_entree, FILE *f_sortie)
{
    int c;
    while ((c = fgetc(f_entree)) != EOF)
    {
        fputc(c, f_sortie);
    }
}

int main(int argc, char *argv[])
{
    FILE *f_entree, *f_sortie;
    if (argc != 3)
    {
        printf("Usage: %s <fichier_entree> <fichier_sortie>\n", argv[0]);
        return -1;
    }
    f_entree = fopen(argv[1], "r");
    if (f_entree == NULL)
    {
        perror("error fopen 1");
        return -1;
    }
    f_sortie = fopen(argv[2], "w");
    if (f_sortie == NULL)
    {
        perror("error fopen 2");
        return -1;
    }
    writeOnFich(f_entree, f_sortie);
    if (fclose(f_entree) != 0)
    {
        perror("error fclose 1");
        return -1;
    }
    if (fclose(f_sortie) != 0) {
        perror("error fclose 2");
        return -1;
    }
    return 0;
}