#include "input.h"

using namespace std;


void clear_data(int &vertices_num,std::vector<int> &edge)
{
    vertices_num = 0;
    edge.clear();
}


int check_input(int vertices_num,vector<int> edge)
{

    for(int i = 0;i < edge.size(); i += 2)
   {      
        if(edge[i] >= vertices_num || edge[i+1] >= vertices_num)
        {   
            cerr << "Error: vertex " << (edge[i] >= vertices_num? edge[i] : edge[i+1]) << " does not exist" << endl << endl;
            return ERROR;
        }

        if(edge[i] == edge[i+1])
        {
            cerr << "Error: vertices on an edge should be different" << endl << endl;
        }
    }
    return V_E_INFO;
}


int get_input(int &vertices_num,vector<int> &edge)
{
    string vertices_info;
    string edge_info;

    getline(cin,vertices_info);

    if(vertices_info == "")
        exit(0);

    if(vertices_info[0] == 'V')
    {
        clear_data(vertices_num,edge);

        getline(cin,edge_info);
        vertices_num = atoi(&vertices_info[2]);

        regex reg1("\\d+");
        
        sregex_iterator it(edge_info.begin(), edge_info.end(), reg1);
        sregex_iterator end;


        for(; it != end; ++it)
        {
            edge.push_back(stoi(it-> str()));
        }

        return check_input(vertices_num,edge);
    }        
}


int get_txt_input(int &vertices_num,vector<int> &edge,ifstream &in)
{
    string vertices_info;
    string edge_info;
    

    if(!(getline (in,vertices_info)))
    {
        return -1;
    }

    getline(in, edge_info);

    if(vertices_info[0] == 'V')
    {
        clear_data(vertices_num,edge);

        vertices_num = atoi(&vertices_info[2]);

        regex reg1("\\d+");
        
        sregex_iterator it(edge_info.begin(), edge_info.end(), reg1);
        sregex_iterator end;

        for(; it != end; ++it)
        {
            edge.push_back(stoi(it-> str()));
        }
    }        
}
