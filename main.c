#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "edge.h"
#include "algorithm.h"

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

    //Cria um tipo PointList com um vetor que armazena todos os pontos no arquivo de entrada
    PointList *pl = point_list_create();
    //Le os pontos do arquivo
    pl = points_reader(pl, file);

    //Cria uma lista para armazenar todas as arestas
    EdgeList *el = edge_list_create(point_list_used(pl));
    //Calcula as arestas
    edge_weight_calculator(el, pl);
    //Ordena a lista de arestas
    edge_list_sort(el);
    
    //Criando a arvóre minima como um vetor de arestas
    EdgeList *mst = edge_list_create(point_list_used(pl));
    kruskal_algoritm(mst, el, point_list_used(pl));

    //Numero de grupos
    int k = atoi(argv[2]);
    //Agrupamento final
    clustering(mst, pl, k);
    //Ordenar os pontos em ordem alfabética
    point_list_sort(pl);
    
    //Abre o arquivo de saida
    FILE *saida = fopen(argv[3],"w");
    if(!saida){
        printf("ARQUIVO DE SAIDA NÃO CONSEGUIU SER CRIADO!\n");
        return 0;
    }
    //Imprime os respectivos pontos dos grupos no arquivo saida
    print_groups_file(pl, k, saida);
    
    //Desaloco a memória das estruturas criadas
    point_list_free(pl);
    edge_list_free(el);
    mst_free(mst);
    return 0;
}