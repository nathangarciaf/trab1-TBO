#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "point.h"

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

    //PointVec *point_vec = point_vec_create();
    char *entrada = NULL;
    size_t size = 0;

    int len = getline(&entrada, &size, file);
    int cont = 0;
    while(len > 0){
        char *subs = strtok(entrada,",");
        Point *p = point_create();
        while(subs){
            if(cont == 0){
                point_add_id(p,subs);
            }
            else{
                point_add_coord(p,subs);
            }
            cont++;
            subs = strtok(NULL, ",");
        }
        size++;
        cont = 0;
        len = getline(&entrada, &size, file);

        point_print(p);
        point_free(p);
    }
    
    free(entrada);
    fclose(file);
    return 0;
}