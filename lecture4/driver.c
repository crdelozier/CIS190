#include <stdlib.h>
#include <stdio.h>

#include "points.h"

int main(){
    point p1;
    point p2;
    point *p3 = (point*)malloc(sizeof(point));

    init_point(&p1,1,0);
    init_point(&p2,2,2);
    init_point(p3,1,0);
    
    print_point(&p1);
    print_point(&p2);

    printf("Distance: %d\n",point_manhattan_distance(&p1,&p2));

    if(equals_point(&p1,p3)){
        printf("Points are equal!\n");
    }

    add_point(&p1,&p2);

    print_point(&p1);

    free(p3);

    return 0;
}
