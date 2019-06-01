# vertex_cover
## (We compare the performance of these three algorithms.For more details, please review the report.)

Use three methods to find the vertex cover of the graph.


## The first method: 

Reduce vertex_cover problem to SAT problem. Then use minisat to find the satisfied assignment. 
This method find the minimum vertex_cover.



## The second method:

Find the vertex with biggest degree, remove edges related to it and add this vertex to vertex_cover set. Keep doning this
until all the edges are removed.



## The third method:

Randomly pick a edge<u,v>. Remove edges related to u and v and add u, v to vertex_cover set. Keep doing this until all the 
edges are removed. 
