#ifndef POINT_H
#define POINT_H
#include <stdio.h>
#define INIT_TAM 5

typedef struct Point Point;
typedef struct Point* PointVec;

PointVec *points_reader(PointVec *pv, int *size, int *tam, FILE *f);
PointVec *point_vec_create(int *size, int *tam);
void point_vec_print(PointVec *pv, int size);
void point_vec_free(PointVec *pv, int size);

Point *point_create();
void point_add_id(Point *p, char* id);
void point_add_coord(Point *p, char *value);
void point_print(Point *p);
void point_free(Point *p);
char *point_get_id(Point *p);
int point_get_group(Point *p);

int point_group_find(Point *p, PointVec *pv, int pv_size, int *height);
void point_union(Point *p1, Point *p2, PointVec *pv, int pv_size);

double euclid_dist(Point *p1, Point *p2);

#endif