#ifndef POINT_H
#define POINT_H

typedef struct Point Point;
typedef struct Point* PointVec;

PointVec *point_vec_create();

Point *point_create();
void point_add_id(Point *p, char* id);
void point_add_coord(Point *p, char *value);
void point_print(Point *p);
void point_free(Point *p);

#endif