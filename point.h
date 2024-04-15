#ifndef POINT_H
#define POINT_H
#include <stdio.h>
#define INIT_TAM 5

typedef struct Point Point;
typedef struct Point* PointPointer;

PointPointer *points_reader(PointPointer *pv, int *size, int *tam, FILE *f);
PointPointer *point_vec_create(int *size, int *tam);
void point_vec_reset_groups(PointPointer *pv, int size);
void point_vec_print(PointPointer *pv, int size);
void print_groups(PointPointer *pv, int size, int k);
void print_groups_file(PointPointer *pv, int size, int k, FILE *saida);
void point_vec_free(PointPointer *pv, int size);

Point *point_create();
void point_add_id(Point *p, char* id);
void point_add_coord(Point *p, char *value);
void point_print(Point *p);
void point_free(Point *p);
char *point_get_id(Point *p);
int point_get_group(Point *p);

int point_group_find(Point *p, PointPointer *pv, int pv_size, int *height);
void point_union(Point *p1, Point *p2, PointPointer *pv, int pv_size);

double euclid_dist(Point *p1, Point *p2);

#endif