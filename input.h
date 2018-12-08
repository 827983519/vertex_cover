#ifndef INCLUDE_H
#define INCLUDE_H

#include <regex>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <fstream>

#define ERROR      -1
#define V_E_INFO    1
#define PATH        2
#define TERMINATE   -2

void clear_data(int &vertices_num,std::vector<int> &edge);
int check_input(int vertices_num,std::vector<int> edge);
int get_input(int &vertices_num,std::vector<int> &edge);
int get_txt_input(int &vertices_num,std::vector<int> &edge,std::ifstream &in);


#endif
