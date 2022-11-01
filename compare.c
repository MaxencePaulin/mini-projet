#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void attente()
{
    int status;
    pid_t fils;
    do {
        fils = wait(&status);
    } while (fils != -1);
}

int compare(char *A, char *B)
{
    // comparer avec diff -u les fichiers A et B
    // retourner 0 si les fichiers sont identiques
    // retourner 1 sinon
    pid_t fils;
    fils = fork();
    if (fils == 0) {
        execlp("diff", "diff", "-u", A,B, NULL);
        perror("execlp");
        return 2;
    }
    attente();
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 4) {
        fprintf(stderr, "Usage: %s commande1 [arguments...] -- commande2 [arguments...]\n", argv[0]);
        return 2;
    }
    /* Lecture des arguments */
    int i = 1;
    char *commande1[argc];
    while (strcmp(argv[i], "--") != 0) {
        commande1[i-1] = argv[i];
        i++;
    }
    commande1[i-1] = NULL;
    i++;
    char *commande2[argc];
    int j = 0;
    while (argv[i] != NULL) {
        commande2[j] = argv[i];
        i++;
        j++;
    }
    commande2[j] = NULL;
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
    pid_t pid2;
    if (pid == -1) {
        perror("fork");
        return 2;
    }
    if (pid == 0) {
        // the son exec commande 1
        if ((pid2 = fork()) == 0) {
            close(fdA);
            close(fdB);
            dup2(fdA, 1);
            execvp(commande1[0], commande1);
            perror("execvp");
            return 2;
        }
        close(fdA);
        close(fdB);
        dup2(fdB, 1);
        execvp(commande2[0], commande2);
        perror("execvp");
        return 2;
    }
    // wait the son
    attente();
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
    if ((compare(fichierA, fichierB) == 0)) {
        printf("Les fichiers sont identiques\n");
    } else {
        printf("Les fichiers sont differents\n");
    }
    // delete fich A and fich B
    if (remove(fichierA) == -1 || remove(fichierB) == -1) {
        perror("remove");
        return 2;
    }
    // if you want delete with a fork =>
    // pid_t pid3 = fork();
    // if (pid3 == 0) {
    //     execlp("rm", "rm", fichierA, fichierB, NULL);
    //     perror("execlp");
    //     return 2;
    // }
    // attente();
    return 0;
}