#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("ERRO\n");
        return 0;
    }

    
    FILE *file = fopen(argv[1], "r");
    if(!file){
        printf("ARQUIVO DE ENTRADA INEXISTENTE!\n");
        return 0;
    }

    FILE *saida = fopen(argv[3], "w");

    char *entrada = NULL;
    char *subs = NULL;
    size_t size = 0;

    int len = getline(&entrada, &size, file);

    while(len > 0){
        subs = strtok(entrada,",");
        while(subs){
            printf("%s\n",subs);
            subs = strtok(NULL, ",");
        }

        size++;
        len = getline(&entrada, &size, file);
    }
    
    free(subs);
    free(entrada);

    fclose(file);
    fclose(saida);
    return 0;
}