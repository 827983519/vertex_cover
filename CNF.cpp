#include "CNF.h"

using namespace Minisat;


bool calculate_vertex_cover(int vertices_num,std::vector<int> edge,int k,std::vector<int> &vertex_cover)
{
    Solver S;
    Var propositions[vertices_num][k];

    for(int i = 0;i < vertices_num;i++)
    {
        for(int j = 0;j < k;j++)
        {
            propositions[i][j] = S.newVar();
        }
    }

    vec<Lit> clause;
    for(int i = 0;i < k;i++)
    {
        
        for(int j = 0;j < vertices_num;j++)
        {
            clause.push(mkLit(propositions[j][i]));
        }
        S.addClause(clause);
        clause.clear();
    }

    for(int i = 0;i < vertices_num;i++)
    {
        for(int j = 0;j < k - 1;j++)
        {
            for(int h = j + 1;h < k;h++)
            {
                S.addClause(mkLit(propositions[i][j],true),mkLit(propositions[i][h],true));
            }
        }
    }

    for(int i = 0;i < k;i++)
    {
        for(int j = 0;j < vertices_num - 1;j++)
        {
            for(int h = j + 1;h < vertices_num;h++)
            {
                S.addClause(mkLit(propositions[j][i],true),mkLit(propositions[h][i],true));
            }
        }
    }
    
    for(int i = 0;i < edge.size();i+=2)
    {    
  
        for(int j = 0;j < k;j++)
        {
            clause.push(mkLit(propositions[edge[i]][j]));
            clause.push(mkLit(propositions[edge[i+1]][j]));
            
        }
        S.addClause(clause);
        clause.clear();
    }

    if(S.solve())
    {
        vertex_cover.clear();
        for(int i = 0;i < k;i++)
        {
            for(int j = 0;j < vertices_num;j++)
            {   
                if(S.modelValue(propositions[j][i]) == l_True)
                    {
                        vertex_cover.push_back(j);
                        break;
                    }
            }
        }
        return 1;
    }

    return 0;
}


bool binary_calculate_vertex_cover(int vertices_num,std::vector<int> edge,std::vector<int> &vertex_cover)
{
    if(vertices_num == 0)
        std::cout << "CNF-SAT-VC: " << std::endl;

    else if(vertices_num == 1)
        std::cout << "CNF-SAT-VC: " << "0" << std::endl;
            
    else if(edge.size() == 0)
        std::cout << "CNF-SAT-VC: " << std::endl;

    else
    {   
        int hi = vertices_num;
        int lo = 1;
        int mid;
        while(hi >= lo)
        {
            mid = (hi+lo)/2;
            if(calculate_vertex_cover(vertices_num,edge,mid,vertex_cover) != 1)
            {
                lo = mid+1;
            }
            else
            {
                hi = mid - 1;
            }
        }
        //print_vertex_cover(vertex_cover,"CNF-SAT-VC: ");
        return 1;
    }
    return 0;
}


bool approx_vc_1(int vertices_num,std::vector<int> edge,std::vector<int> &vertex_cover)
{
    if(vertices_num == 0)
        std::cout << "APPROX-VC-1: " << std::endl;

    else if(vertices_num == 1)
        std::cout << "APPROX-VC-1: " << "0" << std::endl;
            
    else if(edge.size() == 0)
        std::cout << "APPROX-VC-1: " << std::endl;

    else
    {
        int count[vertices_num];
        int edge_num = edge.size();

        while(edge_num != 0)
        {  
            for(int i = 0;i < vertices_num;i++)
            {
                count[i] = 0;
            }

            for(int i = 0;i < edge.size();i++)
            {
                if(edge[i] != INF)
                    count[edge[i]]++;
            }

            int max = std::max_element(count, count + vertices_num) - count;
            vertex_cover.push_back(max);

            for(int i = 0;i < edge.size();i+=2)
            {
                if(edge[i] == max || edge[i+1] == max)
                {
                    edge[i] = INF;
                    edge[i+1] = INF;
                    edge_num -= 2; 
                }
            }
       }
        //print_vertex_cover(vertex_cover,"APPROX-VC-1: ");
        return 1;
    }

    return 0;
}


bool approx_vc_2(int vertices_num,std::vector<int> edge,std::vector<int> &vertex_cover)
{
    if(vertices_num == 0)
        std::cout << "APPROX-VC-2: " << std::endl;

    else if(vertices_num == 1)
        std::cout << "APPROX-VC-2: " << "0" << std::endl;
            
    else if(edge.size() == 0)
        std::cout << "APPROX-VC-2: " << std::endl;

    else
    {
        for(int i = 0;i < edge.size();i+=2)
        {
            if(edge[i] != INF)
            {
                vertex_cover.push_back(edge[i]);
                vertex_cover.push_back(edge[i+1]);
                for(int j = i + 2;j < edge.size();j+=2)
                {
                    if(edge[j] == edge[i] || edge[j+1] == edge[i] || edge[j] == edge[i+1] || edge[j+1] == edge[i+1])
                    {
                        edge[j] = INF;
                        edge[j+1] = INF;
                    }
                }
                edge[i] = INF;
                edge[i+1] = INF;
            }
        }

        //print_vertex_cover(vertex_cover,"APPROX-VC-2: ");
        return 1;
    }

    return 0;
}

void print_vertex_cover(std::vector<int> vertex_coverC,std::vector<int> vertex_cover1,std::vector<int> vertex_cover2)
{
    std::sort(vertex_coverC.begin(),vertex_coverC.end());
    std::sort(vertex_cover1.begin(),vertex_cover1.end());
    std::sort(vertex_cover2.begin(),vertex_cover2.end());

    std::cout << "CNF-SAT-VC: ";
    for (int i = 0;i < vertex_coverC.size();i++)
    {
        std::cout << vertex_coverC[i];
        if(i != vertex_coverC.size() - 1)
            std::cout << ',';
    }
    std::cout << '\n';

    std::cout << "APPROX-VC-1: ";
    for (int i = 0;i < vertex_cover1.size();i++)
    {
        std::cout << vertex_cover1[i];
        if(i != vertex_cover1.size() - 1)
            std::cout << ',';
    }
    std::cout << '\n';

    std::cout << "APPROX-VC-2: ";
    for (int i = 0;i < vertex_cover2.size();i++)
    {
        std::cout << vertex_cover2[i];
        if(i != vertex_cover2.size() - 1)
            std::cout << ',';
    }
    std::cout << '\n';
}


/*void print_vertex_cover(std::vector<int> vertex_cover,char *name)
{
    std::sort(vertex_cover.begin(),vertex_cover.end());
    std::cout << name;
    for (int i = 0;i < vertex_cover.size();i++)
    {
        std::cout << vertex_cover[i];
        if(i != vertex_cover.size() - 1)
            std::cout << ',';
    }
    std::cout << '\n';
}*/
