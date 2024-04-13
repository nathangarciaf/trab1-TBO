#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "point.h"
#include "edge.h"

int main(int argc, char *argv[]){
    //Verificar se há quantidade de argumentos necessários para rodar o programa.
    if(argc < 4){
        printf("ERRO\n");
        return 0;
    }
    
    //Verificando se o arquivo a ser lido existe
    FILE *file = fopen(argv[1], "r");
    if(!file){
        printf("ARQUIVO DE ENTRADA INEXISTENTE!\n");
        return 0;
    }

    int vec_size = 0, vec_tam = 0;
    PointVec *pv = point_vec_create(&vec_size,&vec_tam);

    pv = points_reader(pv,&vec_size, &vec_tam, file);

    point_vec_free(pv, vec_size);
    return 0;
}