#include <stdlib.h>
#include <stdio.h>

#include "points.h"

void init_point(point *p, int x, int y){
    p->x = x;
    p->y = y;
}

void print_point(point *p){
    printf("(%d,%d)\n",p->x,p->y);
}

int point_manhattan_distance(point *p1, point *p2){
    return abs(p1->x - p2->x) + abs(p1->y - p2->y);
}

void add_point(point *p1, point *p2){
    p1->x += p2->x;
    p1->y += p2->y;
}

int equals_point(point *p1, point *p2){
    return p1->x == p2->x && p1->y == p2->y;
}
