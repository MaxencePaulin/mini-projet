#include <stdio.h>
#include <stdlib.h>

void writeOnFich(FILE *f_entree, FILE *f_sortie)
{
    int c;
    while ((c = fgetc(f_entree)) != EOF)
    {
        fputc(c, f_sortie);
    }
    fputc('\n', f_sortie);
}

int main(int argc, char *argv[])
{
    FILE *f_entree;
    // copie d'un fichier sur la sortie standart
    if (argc == 1)
    {
        writeOnFich(stdin, stdout);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            f_entree = fopen(argv[i], "r");
            if (f_entree == NULL)
            {
                perror("erreur fopen");
                return -1;
            }
            writeOnFich(f_entree, stdout);
            if (fclose(f_entree) != 0)
            {
                perror("erreur fclose");
                return -1;
            }
        }
    }
    return 0;
}