
#ifndef CITY_H
#define CITY_H

#include "road.h"
#include "node.h"
#include <list>
#include <cmath>
#include <iterator>

class City 
{
    Node** _path;
    int** _distance;
    Node* _node_set;
    void _floyd_warshall();
    Road** _adj_matrix;
    int _n_rows;
    int _n_coloumns;
    float _oneway_fraction;
  public:
    City();
    City(int n_rows, int n_coloumns, float oneway_fraction, int gaussian_mean, int gaussian_sigma, int min_road_length, int max_road_length);
    std::list<Node> print_path(Node source, Node destination);
    Road get_road(int i, int j)const;
    Road* get_road_ptr(int i, int j)const;
    int get_n_rows()const;
    int get_n_coloumns()const;
    float get_oneway_fraction()const;
    Node get_node(int i)const;
    Node get_path(int i, int j)const;
    int get_distance(int i, int j)const;
    Road** get_adj_matrix();

    City(short n_rows, short n_coloumns, float oneway_fraction);
};

#endif
