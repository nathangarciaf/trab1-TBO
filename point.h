#ifndef POINT_H
#define POINT_H
#include <stdio.h>
#define INIT_TAM 5

typedef struct Point Point;
typedef struct PointList PointList;
typedef struct Point* PointPointer;

Point *point_create();
void point_set_id(Point *p, char* id);
void point_set_group(Point *p, int group);
void point_add_coord(Point *p, char *value);

PointList *point_list_create();
PointList *points_reader(PointList *pl, FILE *f);
Point *point_list_get(PointList *pl, int i);
int point_list_used(PointList *pl);

int point_cmp(const void *point1, const void *point2);
void point_list_sort(PointList *pl);

double euclid_dist(PointList *pl, int p1, int p2);

void point_list_print(PointList *pl);
void print_groups_file(PointList *pl, int k, FILE *saida);

void point_list_free(PointList *pl);
void point_free(Point *p);

#endif