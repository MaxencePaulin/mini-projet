#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int deleteFich(char *cheminA, char *cheminB){
    // delete fich A and fich B
    if (remove(cheminA) == -1 || remove(cheminB) == -1) {
        perror("remove");
        return 2;
    }
    return 0;
    // if you want delete with a fork =>
    // pid_t pid3 = fork();
    // if (pid3 == 0) {
    //     execlp("rm", "rm", fichierA, fichierB, NULL);
    //     perror("execlp");
    //     return 2;
    // }
    // return attente();
    //
}

int attente()
{
    int status;
    pid_t fils;
    do {
        fils = wait(&status);
        if (fils == -1) {
            if (WIFEXITED(status)) {
                return WEXITSTATUS(status);
            }
        }
    } while (fils != -1);
    return 0;
}

int compare(char *A, char *B)
{
    pid_t fils;
    fils = fork();
    if (fils == 0) {
        execlp("diff", "diff", "-u", A, B, NULL);
        perror("execlp");
        return 2;
    }
    // return value of WEXITSTATUS in attente()
    return attente();
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
    char fichierA[] = "/tmp/commande1A-XXXXXX";
    char fichierB[] = "/tmp/commande2B-XXXXXX";
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
        // the son of son exec commande 1
        if ((pid2 = fork()) == 0) {
            close(fdB);
            dup2(fdA, 1);
            execvp(commande1[0], commande1);
            perror("execvp");
            return 2;
        }
        // the son exec commande 2
        close(fdA);
        dup2(fdB, 1);
        execvp(commande2[0], commande2);
        perror("execvp");
        return 2;
    }
    // wait the son and the son of son if they are finish without error
    if (attente() > 1) {
        if ((deleteFich(fichierA, fichierB) != 0)) {
            perror("deleteFich");
        };        
        return 2;
    }
    // close fich A and fich B openned with mkstemp
    close(fdA);
    close(fdB);
    // compare fich A and fich B
    int res;
    switch (compare(fichierA, fichierB)) {
        case 0:
            printf("Les fichiers sont identiques\n");
            res = 0;
            break;
        case 1:
            printf("Les fichiers sont differents (différences ci-dessus)\n");
            res = 1;
            break;
        default:
            res = 2;
            break;
    }
    if ((deleteFich(fichierA, fichierB) != 0)) {
        perror("deleteFich");
        return 2;
    };
    return res;
}