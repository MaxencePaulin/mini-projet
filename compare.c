#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int compare(FILE *A, FILE *B)
{
    int c1, c2;
    int i = 0;
    while ((c1 = fgetc(A)) != EOF && (c2 = fgetc(B)) != EOF) {
        if (c1 != c2) {
            printf("\nLes fichiers sont differents a la ligne %d\n", i);
            return 1;
        }
        i++;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s commande1 [arguments...] -- commande2 [arguments...]\n", argv[0]);
        return 2;
    }
    // create two fich and open it with the mkstemp function without core dumped
    char fichierA[] = "/tmp/exo2/myTmpFileA-XXXXXX";
    char fichierB[] = "/tmp/exo2/myTmpFileB-XXXXXX";
    int fdA = mkstemp(fichierA);
    int fdB = mkstemp(fichierB);
    if (fdA == -1 || fdB == -1) {
        perror("mkstemp");
        return 2;
    }
    // create two process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 2;
    }
    if (pid == 0) {
        // the son exec commande 1
        close(fdA);
        close(fdB);
        dup2(fdA, 1);
        execlp(argv[1], argv[1], NULL);
        perror("execlp");
        return 2;
    }else {
        // the dad exec commande2
        close(fdA);
        close(fdB);
        dup2(fdB, 1);
        execlp(argv[3], argv[3], NULL);
        perror("execlp");
        return 2;
    }
    // Bon le code passe pas la, il faut delete fichier A et fichier B aussi 
    // close fich A and fich B
    close(fdA);
    close(fdB);
    // open fich A and fich B
    FILE *foA = fopen(fichierA, "r");
    FILE *foB = fopen(fichierB, "r");
    if (foA == NULL || foB == NULL) {
        perror("fopen");
        return 2;
    }
    // compare
    compare(foA, foB);
    printf("\nLes fichiers sont identiques\n");
    return 0;
}