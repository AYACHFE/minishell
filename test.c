#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char *expand_variable(char *variable) {
    // Implémentez ici la logique d'expansion de variable
    // Pour chaque variable, recherchez sa valeur dans l'environnement ou dans vos variables personnalisées
    // Effectuez le traitement nécessaire pour obtenir la valeur de la variable
    // Allouez de la mémoire pour la valeur de la variable et retournez-la
    
    // Exemple simplifié :
    if (strcmp(variable, "$HOME") == 0) {
        // Allouer de la mémoire pour la valeur de $HOME
        char *expanded = malloc(sizeof(char) * (strlen("/chemin/vers/home") + 1));
        strcpy(expanded, "/chemin/vers/home");
        return expanded;
    }

    // Si la variable n'est pas une variable connue, retournez-la telle quelle
    return strdup(variable);
}

char *expand_command(char *command) {
    char *expanded_command = malloc(strlen(command) + 1);
    char *token;
    char *expanded_token;
    char *result = expanded_command;

    // Parcourt chaque token de la commande
    token = strtok(command, " ");
    while (token != NULL) {
        expanded_token = expand_variable(token); // Expansion de variable pour chaque token
        strcpy(result, expanded_token);
        result += strlen(expanded_token);
        *result = ' '; // Ajoute un espace entre chaque token
        result++;
        token = strtok(NULL, " ");
    }

    *(result - 1) = '\0'; // Remplace le dernier espace par le caractère de fin de chaîne
    return expanded_command;
}

void apply_expansion(char **commands, int command_count) {
    int i;
    char *expanded_command;

    for (i = 0; i < command_count; i++) {
        expanded_command = expand_command(commands[i]); // Expansion de chaque commande
        strcpy(commands[i], expanded_command);
        free(expanded_command);
    }
}

int main() {
    char *commands[] = {
        "echo $HOME",
        "ls -l $PWD",
        "cd $HOME"
    };
    int command_count = sizeof(commands) / sizeof(commands[0]);
    int i;

    apply_expansion(commands, command_count);

    for (i = 0; i < command_count; i++) {
        printf("%s\n", commands[i]);
    }

    return 0;
}