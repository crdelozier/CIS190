typedef struct point{
    int x;
    int y;
} point;

void init_point(point *p, int x, int y);
void print_point(point *p);
int point_manhattan_distance(point *p1, point *p2);
void add_point(point *p1, point *p2);
int equals_point(point *p1, point *p2);

