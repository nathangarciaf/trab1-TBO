#ifndef POINT_H
#define POINT_H
#include <stdio.h>
#define INIT_TAM 5

typedef struct Point Point;
typedef struct PointList PointList;
typedef struct Point* PointPointer;

PointList *point_list_create();
PointList *points_reader(PointList *pl, FILE *f);
int point_list_used(PointList *pl);
Point *point_list_get_point(PointList *pl, int i);

void point_list_reset_groups(PointList *pl);
void pont_list_sort(PointList *pl);
void point_list_print(PointList *pl);

void print_groups(PointList *pl, int k);
void print_groups_file(PointList *pl, int k, FILE *saida);

Point *point_create();
void point_add_id(Point *p, char* id);
void point_add_coord(Point *p, char *value);
char *point_get_id(Point *p);
void point_set_group(Point *p, int group);
int point_get_group(Point *p);
void point_print(Point *p);
void point_free(Point *p);

int point_group_find(Point *p, PointList *pl, int *height);
void point_union(Point *p1, Point *p2, PointList *pl);
double euclid_dist(Point *p1, Point *p2);
void point_list_free(PointList *pl);

#endif