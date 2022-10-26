//  ॥जय श्री राम ॥
/*  ॥ श्री गणेशाय नमः ॥      */
//it's the WILL not the skill

/*
Author-rishikey yadav
Date-26 jun 2022
Project-(GAL 1.0)graph algorithms library

*/


//Structure of graph 
class gst { 

public:

//check if node visited or not
    map<int, bool> visited;

//USING MAP FOR ADJ LIST=>NO NEED TO DEFINE SIZE OF THE LISTS EXPLICITLY

//adjacency  list.     
    map<int, list<int> > adj;   

 //weighted adjacency list
    map<int,list<pair<int,int> > >adjm;
    
// function to add an edge to graph
    void addEdgeuw(int  v, int  w){

         // Add w to v’s list.
        adj[v].push_back(w);

         // Add v to w’s list.
        adj[w].push_back(v);
    } 

    //add edge in weighted adjacency list
     void addEdgew(int  v, int  w,int wght){

         // Add w to v’s list.
        adjm[v].push_back(make_pair(w,wght));

         // Add v to w’s list.
        adjm[w].push_back(make_pair(v,wght));
    } 
};

//helper class whose functions would be dominated for performing functions as per user
class helpr{
    public:
    virtual void h1(){};
    virtual void h2(){};
    virtual void h3(){};
    virtual void h4(){};
};


//traversal algorithms

class trv:public gst, public helpr{
    public:
 //redefine these helper functions as per your convinience before calling dfs or bfs->use in coloring of nodes
    //helpr functions for dfs
    void h1(int );
    void h2(int );

    //helpr functions for bfs
    void h3(int );
    void h4(int );



   void dfs(int v)
{  
    //check if node is already visited
    map<int, bool> visited;

    // Mark the current node as visited and
    visited[v] = true;

    // helper function to pre-process the current node as per user          eg:->color the current node
     h1(v);
 
    // Recur for all the vertices adjacent to this vertex
    //list<int>::iterator i;
    for (auto i = gst::adj[v].begin(); i != gst::adj[v].end(); ++i)
        if (!visited[*i])
            dfs(*i);

    // helper function to post-process the current node as per user 
      h2(v);
}

    void bfs(int s){
        
    // Mark all the vertices as  unvisited
    vector<bool> visited((int)1e6,false);

    // Create a queue for BFS
    list<int> que;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    que.push_back(s);
 
    while(!que.empty())
    {
        // Dequeue a vertex from queue 
        s = que.front();
        que.pop_front();

        //use helper functions to exploit any function as per user
        h3(s);
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (auto adjecent: gst::adj[s])
        {
            if (!visited[adjecent])
            {
                visited[adjecent] = true;
                que.push_back(adjecent);

                h4(s);
            }
        }
        }
  }
};

//shortest path algorithms
class sp:public trv{
    public:
    const int INFFF = (long long)2e18;

    vector<int> dijkstra(int s) {
   // vector<int>sptset;
    vector<int> dis;
    int n = trv::adjm.size();
    dis.assign(n, INFFF);
    //sptset.assign(n, -1);
    vector<bool> vis(n, false);

    dis[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && (v == -1 || dis[j] < dis[v]))
                v = j;
        }

        if (dis[v] == INFFF)
            break;

        vis[v] = true;
        for (auto edge : trv::adjm[v]) {
            int to = edge.first;
            int len = edge.second;

            if (dis[v] + len < dis[to]) {
                dis[to] = dis[v] + len;
              //  sptset[to] = v;
            }
        }
    }
    return dis;
}
//Bellman-Ford algorithm
vector<int> belf(int n,int m,int v){
    //v -> source
    struct edge
{   
    int a, b, cost;
};
    //put every edge in single list along with their cost

    
vector<edge> e;
vector<int> d (n, INFFF);
for(auto u:adjm)
for(auto uu:u.second){
    edge t;
    t.a=u.first,t.b=uu.first,t.cost=uu.second;
    e.push_back(t);

    
    d[v] = 0;
    for (int i=0; i<n-1; ++i)
        for (int j=0; j<m; ++j)
            if (d[e[j].a] < INFFF)
                d[e[j].b] = min (d[e[j].b], d[e[j].a] + e[j].cost);
                }
    return d;
    }


//Floyd-Warshall
vector<vector<int> >flw(int v){
 //int  dist[v][v];
 int i, j, k;
    vector<vector<int> >dist(v,vector<int>(v));
  for (i = 0; i < v; i++)
    for (j = 0; j < v; j++)
          dist[i][j]=INFFF;

          for(auto u:adjm)
          for(auto uu:u.second)
          dist[u.first][uu.first]=uu.second;

          for (k = 0; k < v; k++) {
        for (i = 0; i < v; i++) {
            for (j = 0; j < v; j++) {
                if (dist[i][k] < INFFF && dist[k][j] < INFFF && dist[i][k] + dist[k][j] < dist[i][j])
                //d[i][k] < INFFF && d[k][j] < INFFF is considered to avoid mis calculations due to negative weight edges->cp algorithms
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
 return dist;
}



};




/*
NOTES:
application-
1)gst-to create the graph structure
gst<int> g;
g.addedge(2,4); adj list is created inside g itself

2)helper object creation
helpr h;

3)trv-grraph travesals
trv *t;
h=&t;//to utilise helper functions(coz for using virtual functions this is required)  
//to utilise helpr functions in dfs,bfs pre define them before using dfs,bfs

//shortest path algorithms would return vectors 1D or 2D as per their functionality
//so for calling these functions assign them to corresponding vectors

//doubt in h=&t
t<ll>::h1(){

}
// similarly for h2,h3,h4
//put bfs ,dfs in gst

//#include<cstdarg>->use it for using varibale no. of parameters for functions.Needed if sptset(path tracing) of dijsktra is needed.
COMMITED:14 Oct
*/
 

 
