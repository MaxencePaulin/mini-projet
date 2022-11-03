## Initialisation du mini-projet en language C sur github

26/10/2022

---

## Création d'une commande xxd pour afficher le contenu d'un fichier en hexadécimal et en texte

**Chaque ligne est composée de :**

- **L'adresse depuis le début du fichier, en base 16 sur 8 chiffres, suivie d'un double-point.**

- **Une espace, puis les valeurs de 16 octets en base 16 sur deux chiffres, avec une espace pour séparer tous les groupes de deux octets.**

- **Deux espaces, puis les caractères correspondant aux octets. Si le caractère n'est pas imprimable, il est remplacé par un point (.).**

- **Si la taille du fichier n'est pas un multiple de 16, la dernière ligne est tronquée, comme dans l'exemple.**

**Le programme doit prendre le nom du fichier à afficher sur sa ligne de commande. Si aucun nom de fichier n'est donné, le programme doit lire les données sur son entrée standard.**

26/10/2022 - 31/10/2022

---

## Création d'un programme permettant de comparer les deux sorties de deux programme différents

**Ce programme doit fonctionner de la manière suivante :**

- **créer un processus pour exécuter la commande1 avec ses arguments, en redirigeant sa sortie standard dans un fichier A**

- **créer un processus pour exécuter la commande2 avec ses arguments, en redirigeant sa sortie standard dans un fichier B**

- **exécuter la commande « diff -u » pour comparer les fichiers A et B et afficher les différences s'il y en a.**

**Le programme doit se terminer avec le code de retour 0 si les sorties sont identiques, 1 si elles sont différentes, et 2 pour toute autre erreur.**

01/11/2022 - 05/11/2022

---

## Création d'un rapport du mini-projet

**Le projet doit être accompagné d'un court rapport qui doit :**

- **décrire les point forts et les faiblesses de chacun des programmes**

- **indiquer, pour les entrées-sorties, quelle interface a été utilisée (haut-niveau ou bas-niveau)**

- **expliquer comment sont exécutées les différentes commandes dans le deuxième exercice**

- **décrire comment le programme du deuxième exercice peut être utilisé pour vérifier le programme du premier exercice.**

05/11/2022 - 08/11/2022

---