#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <vector>
#include <stdlib.h>
using namespace std;
typedef struct {
  int start;
  int final;
  int weight;

}Edge;
typedef struct {
   int num_nodes, num_edges;
   Edge *edge;

}Graph;

int main(){
   //init variables
   string line;
   string content;
   int i = -1;
   vector<int> v;
   Graph *G = (Graph*) malloc(sizeof(Graph));
   int temp[4096][3];

   while(getline(cin, line)){
     G->num_edges++;
     if (i == -1)
     {
        G->num_nodes = stoi(line);
     }
     else{
       stringstream ss(line);
       int num;
       //add each line to edges
       while(ss >> num){
          v.push_back(num);
          if(ss.peek() == ',')
             ss.ignore();
       }
       temp[i][0] = v.at(0);
       temp[i][1] = v.at(1);
       temp[i][2] = v.at(2);

     }
     i++;
     v.clear();
   }

   G->num_edges--;
   G->edge = (Edge*) malloc(G->num_edges * sizeof(Edge));
   for(int j = 0; j < i; j++){
      G->edge[j].start = temp[j][0];
      G->edge[j].final = temp[j][1];
      G->edge[j].weight = temp[j][2];
      cout << "start at " << j << " is " << G->edge[j].start << endl;
      cout << "final at " << j << " is " << G->edge[j].final << endl;
      cout << "weight at " << j << " is " << G->edge[j].weight << endl;
   }

}
