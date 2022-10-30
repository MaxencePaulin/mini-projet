## Initialisation du mini-projet en language C sur github

26/10/2022

---

### <u>Initialisation du projet</u>

---

### Création d'une commande xxd pour afficher le contenu d'un fichier en hexadécimal et en texte

**Chaque ligne est composée de :**

- **L'adresse depuis le début du fichier, en base 16 sur 8 chiffres, suivie d'un double-point.**

- **Une espace, puis les valeurs de 16 octets en base 16 sur deux chiffres, avec une espace pour séparer tous les groupes de deux octets.**

- **Deux espaces, puis les caractères correspondant aux octets. Si le caractère n'est pas imprimable, il est remplacé par un point (.).**

- **Si la taille du fichier n'est pas un multiple de 16, la dernière ligne est tronquée, comme dans l'exemple.**

**Le programme doit prendre le nom du fichier à afficher sur sa ligne de commande. Si aucun nom de fichier n'est donné, le programme doit lire les données sur son entrée standard.**

26/10/2022 - 31/10/2022

(optimisation pouvant être faite sur le code pour afficher le contenu d'un fichier prédéfini en hexadécimal et en texte. Mais code fonctionnel)

---