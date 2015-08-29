#include <iostream>

#include "points.h"

int main(){
  point p1;
  point p2;
  point *p3 = new point;

  init_point(&p1,1,0);
  init_point(&p2,2,2);
  init_point(p3,1,0);
 
  print_point(&p1);
  print_point(&p2);

  std::cout << "Distance: " << point_manhattan_distance(&p1,&p2) << "\n";

  if(equals_point(&p1,p3)){
    std::cout << "Points are equal!\n";
  }

  add_point(&p1,&p2);

  print_point(&p1);
  
  delete p3;
  
  return 0;
}
