#ifndef _CNF_H
#define _CNF_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <vector>
#include <algorithm>


# define INF 0xFFFFFF

bool approx_vc_2(int vertices_num,std::vector<int> edge,std::vector<int> &vertex_cover);
bool approx_vc_1(int vertices_num,std::vector<int> edge,std::vector<int> &vertex_cover);
bool calculate_vertex_cover(int vertices_num,std::vector<int> edge,int k,std::vector<int> &vertex_cover);
bool binary_calculate_vertex_cover(int vertices_num,std::vector<int> edge,std::vector<int> &vertex_cover);
void print_vertex_cover(std::vector<int> vertex_coverC,std::vector<int> vertex_cover1,std::vector<int> vertex_cover2);
//void print_vertex_cover(std::vector<int> vertex_cover,char *name);


#endif