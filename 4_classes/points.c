#include <stdlib.h>
#include <stdio.h>

typedef struct point{
    int x;
    int y;
} point;

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
