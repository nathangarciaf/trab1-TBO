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

    //Cria um vetor com todos os pontos no arquivo de entrada
    int pv_size = 0, pv_tam = 0;
    PointVec *pv = point_vec_create(&pv_size,&pv_tam);

    pv = points_reader(pv,&pv_size, &pv_tam, file);

    //ev_size é o número de arestas possíveis em uma matriz NxN triangular inferior, sendo n = pv_size.
    int ev_size = (((pv_size*pv_size)/2) - (pv_size/2));
    EdgeVec *ev = edge_vec_create(ev_size);
    //Cria o vetor de todas as distâncias
    edge_weight_calculator(ev, pv, pv_size);
    edge_vec_sort(ev,ev_size);
    
    //Criando a arvóre minima como um vetor de arestas
    int mst_size = 0, mst_tam = INIT_TAM;
    EdgeVec *mst = edge_vec_create(mst_tam);

    mst = kruskal_algoritm(mst, &mst_size,&mst_tam, ev, ev_size);
    
    point_vec_free(pv, pv_size);
    edge_vec_free(ev, ev_size);
    edge_vec_free(mst, mst_size);
    return 0;
}