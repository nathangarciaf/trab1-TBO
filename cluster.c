#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("ERRO\n");
        return 0;
    }

    
    FILE *file = fopen(argv[1], "r");
    if(file == NULL){
        printf("ARQUIVO DE ENTRADA INEXISTENTE!\n");
        return 0;
    }

    FILE *saida = fopen(argv[3], "w");
    char *s = (char*)calloc(100,sizeof(char));
    while(!feof(file)){
        fscanf(file, "%s\n",s);
        fprintf(saida,"%s\n",s);
    }
    free(s);
    

    fclose(file);
    fclose(saida);
    return 0;
}