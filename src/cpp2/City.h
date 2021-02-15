
#ifndef CITY_H
#define CITY_H

#include "Road.h"
#include "Node.h"
#include <list>
#include <cmath>
#include<iterator>

#define MIN_PATH_LENGTH 2*MIN_ROAD_LENGTH

class City 
{
    Road** _adj_matrix;
    Node** _path;
    short** _distance;
    std::list<Node> _print_path(Node source, Node destination);
    short _n_rows;
    short _n_coloumns;
    Node* _node_set;
    void _floyd_warshall();
  public:
    City();
    City(short n_rows, short n_coloumns, float oneway_fraction);
};

#endif