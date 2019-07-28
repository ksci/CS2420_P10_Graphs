#ifndef __Graph__
#define __GRAPH__
#include <string>


class Graph
{
public:
	Graph();
	~Graph();
	void AddEdge(std::string source, std::string target, int weight);
	void AddVertex(std::string label);
	int GetIndex(std::string label) const;
	bool IsEdge(std::string source, std::string target) const;
	int GetWeight(int sourceIndex, int targetIndex) const;
	void BreadthFirstSearch(std::string startingVertex) const;
	void BreadthFirstSearch(std::string startingVertex, int visited[]) const;
	void DijkstraShortestPath(std::string startingVertex) const;
	void DijkstraShortestPath(std::string startingVertex, int distance[], int prevVertex[]) const;
	void PrintGraph() const;
	static const int MAX_VERTICES = 10;		//max size of the graph
private:

	int graph[MAX_VERTICES][MAX_VERTICES];	//The 2D array containing edge weights
	std::string labels[MAX_VERTICES];		//store the labels for each vertex
	int numVertices;						//keep track of how many vertices have been used

};


#endif 
