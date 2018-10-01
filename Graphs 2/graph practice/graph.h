#include <iostream>
#include <vector>
#include <queue>


using namespace std;

class Graph{

	int v;
	bool adj[20][20];
	
	public:
		Graph(int vcount);
		void addEdge(int source, int dest);
		void deleteEdge(int source, int dest);
		void BFS(int s);

};




	Graph::Graph(int vcount){
		this->v=vcount;
		for(int i=0; i<v;i++){

			for(int j=0; j<v; j++){
				adj[i][j]=false;
			}
		}


	}


	void Graph::addEdge(int source, int dest){
		adj[source][dest]=true;
		adj[dest][source]=true;
	}

	void Graph::deleteEdge(int source, int dest){
		adj[source][dest]=false;
		adj[dest][source]=false;
	}

	void Graph::BFS(int s){
		bool *visited= new bool[this->v];
		int *bfsOrder= new int[this->v];
		int q[100];
		int front=0;
		int back=0;

		visited[s]=true;
		q[front]=s;
		while(false){


		}

	}
	











