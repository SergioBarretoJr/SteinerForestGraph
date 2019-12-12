//
//  Forest_Steiner.hpp
//  Steiner_Tree
//
//  Created by sergio junior on 12/11/19.
//  Copyright © 2019 sergio junior. All rights reserved.
//

#ifndef Forest_Steiner_hpp
#define Forest_Steiner_hpp
#include<iostream>
#include <list>
#include <limits.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <list>
#include <algorithm>
#include <stack>
#include <dirent.h>
#include <sstream>
#include <sstream>
#include <ostream>


using namespace std;


vector<string> list_dir(const char *path) {
    struct dirent *entry;
   vector<string> s;
   DIR *dir = opendir(path);
    
   if (dir == NULL) {
      return s;
   }

   while ((entry = readdir(dir)) != NULL) {
       s.push_back(entry->d_name);
   }
   closedir(dir);
   return s;
}

std::string IntToString(int a)
{
    std::ostringstream temp;
    temp << a;
    return temp.str();
}

typedef  pair<int, int> iPair;


class Grafo
{
public:
    int V,E;
    vector< pair<int, iPair> > edges;
    list<int> *adj; // adjacent list
    Grafo(int V); // constructor
    void adicionarAresta(int v1, int v2);
    int kruskalMST(Grafo *g, int n);
    void DFSUtil(int v, bool visited[], list<int> &nos);
    void connectedComponents();
    void ConnecComp(stack<int> &CompConex, int *ncomp,Grafo *gFinal);
    void fillOrder(int v, bool visited[], stack<int> &Stack);
    void primsMST(list<int> nos, int start,Grafo *gFinal);
    int get_cost_edge(int u, int v);
    Grafo getTranspose();
    void addEdge(int u, int v, int w){ edges.push_back({w, {u, v}});}
};
 
Grafo::Grafo(int V)
{
    this->V = V; // atribui o número de vértices
    adj = new list<int>[V]; // cria as listas
}

 template <typename T>
 bool contains(std::list<T> & listOfElements, const T & element)
 {
     auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
     return it != listOfElements.end();
 }

Grafo Grafo::getTranspose()
{
    Grafo g(V);
    for (int v = 0; v < V; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void Grafo::fillOrder(int v, bool visited[], stack<int> &Stack)
{
    // Mark the current node as visited and print it
    visited[v] = true;
  
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            fillOrder(*i, visited, Stack);
  
    // All vertices reachable from v are processed by now, push v
    Stack.push(v);
}

void print_struct(const char *path,Grafo *g){
    ofstream myfile;
    myfile.open (string(path) +"Solution.txt", std::ios_base::app);
    printf("Printing Graph\n");
    int finalCost=0;
    vector< pair<int, iPair> >::iterator it;
    for (it=g->edges.begin(); it!=g->edges.end(); it++)
    {
        if(it->first!=9999){
            //myfile << IntToString(it->second.first)+"\t"+IntToString(it->second.second)+"\t"+IntToString(it->first)+"\n";
            printf("%d\t%d\t%d\n",it->second.first,it->second.second,it->first);
            finalCost=finalCost+it->first;
        }
    }
    printf("Final Cost - %d\n",finalCost);
}
// The main function that finds and prints all strongly connected
// components
void Grafo::ConnecComp(stack<int> &CompConex, int *ncomp,Grafo *gFinal)
{
    
    stack<int> Stack;
    bool *visited = new bool[V];
    
    for(int i = 0; i < V; i++)
        visited[i] = false;
  
    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            fillOrder(i, visited, Stack);
    
    for(int i = 0; i < V; i++)
        visited[i] = false;
    
    while (Stack.empty() == false)
    {
        list<int>nos;
        int v = Stack.top();
        Stack.pop();
        if (visited[v] == false)
        {
            DFSUtil(v, visited,nos);
            if (adj[v].size()!=0){
                primsMST(nos,v,gFinal);
                (*ncomp)++;
            }
        }
    }
    
    printf("N componente conexas %d\n",(*ncomp));
}

void Grafo::adicionarAresta(int v1, int v2)
{
    // adiciona vértice v2 à lista de vértices adjacentes de v1
    if ((contains(adj[v1], v2)) || (contains(adj[v2], v1)) ){
    }else{
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }
}
 
void Grafo::DFSUtil(int v, bool visited[], list<int> &nos)
{ 
    visited[v] = true;
    if (adj[v].size()!=0){
        nos.push_back(v);
        cout << v << " ";
    }
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
            DFSUtil(*i, visited,nos);
} 

vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
 
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
 
  return internal;
}

void read_file(const char *path,const char *path2,Grafo *g){
    std::string buf(string(path)+path2);
    std::ifstream file(buf.c_str());
    std::string delimiter = " ";
    ofstream myfile;
    myfile.open (string(path) +"Solution.txt", std::ios_base::app);
    int lines=0;
    std::string token;  
    int token1,token2,token3;
    
    if (file.is_open()){
        
        std::string line;
        while (getline(file, line)){
            if(lines>=2){
                vector<string> sep = split(line, ' ');
                token1 = std::atoi(sep[1].c_str());
                token2 = std::atoi(sep[2].c_str());
                token3 = std::atoi(sep[3].c_str());
                myfile << IntToString(token1)+"\t"+IntToString(token2)+"\t"+IntToString(token3)+"\n";
                g->adicionarAresta(token1, token2);
                g->addEdge(token1, token2,token3);
            }
            lines++;
        }
        file.close();
        myfile.close();
    }else{
        printf("Solutions file with error!\n");
    }
}

typedef  pair<int, int> iPair;
struct DisjointSets
{
    int *parent, *rnk;
    int n;
  
    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
  
        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;
  
            //every element is parent of itself
            parent[i] = i;
        }
    }
  
    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
  
    // Union by rank
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
  
        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
  
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};
 /* Functions returns weight of the MST*/
  
int Grafo::kruskalMST(Grafo *g, int n)
{
    int mst_wt = 0; // Initialize result
  
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());
  
    // Create disjoint sets
    DisjointSets ds(V);
  
    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
  
        int set_u = ds.find(u);
        int set_v = ds.find(v);
  
        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v)
        {
            // Current edge will be in the MST
            // so print it
            cout << u << " - " << v << endl;
            g->addEdge(u, v, it->first);
            // Update MST weight
            mst_wt += it->first;
  
            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }
    printf("Novo custo da Floresta %d\n",mst_wt);
    return mst_wt;
}

int find_list(list<int>nos, int v){
    
    // Check if an element exists in list
    
       // Create a list Iterator
       std::list<int>::iterator it;
    
       // Fetch the iterator of element with value 'the'
       it = std::find(nos.begin(), nos.end(), v);
    
       // Check if iterator points to end or not
       if(it != nos.end())
       {
           // It does not point to end, it means element exists in list
           return 1;
       }
       else
       {
           // It points to end, it means element does not exists in list
           return 0;
       }
}

list<int> difference(list<int> first, list<int> second) {
   list<int> :: iterator it;
   list<int> res;
   
   for(it = first.begin(); it != first.end(); it++) {
      if(find_list(second, *it)==0)
         res.push_back(*it);    //add those item which are not in the second list
   }

   return res;    //the set (first-second)
}

int Grafo:: get_cost_edge(int u, int v ){
    int cont=0;
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        if((it->second.first==u && it->second.second==v)||(it->second.first==v && it->second.second==u)){
            cont++;
            break;
        }
    }
    if(cont==1){
        return it->first;
    }else{
        return 999;
    }
}

void Grafo:: primsMST(list<int> nos, int start,Grafo *gFinal) {
    printf("Starting Prim\n");
    int n = V;
   list<int> B;
   list<int> diff;
   
   B.push_back(start);
   diff = difference(nos, B);
   while(diff.empty()==0) {
      int min = 9999; 
      int v = 0, par = 0;
      diff = difference(nos, B);
      for(int u = 0; u < n; u++) {
         if(find_list(B, u)==1) {
            list<int>::iterator it;
            for(it = adj[u].begin(); it != adj[u].end(); it++) {
               if(find_list(diff,*it)==1) {
                  int cost =get_cost_edge(u, *it);
                  if(min > cost) {
                     min = cost;
                     par = u;
                     v = *it;
                  }
               }
            }
         }
      }
      B.push_back(v);
      gFinal->adicionarAresta(par, v);
      gFinal->addEdge(par, v, min);
   }
    //std::string str_path_sol="/Users/sergiojunior/Steiner_Tree/Steiner_Tree/Solution";
    //print_struct(str_path_sol.c_str(), gFinal);
}
  
#endif
