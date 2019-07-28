#include "Graph.h"
#include <string>
#include <set>
#include <climits>
#include <iostream>
#include <queue>


using namespace std;

Graph::Graph()
{
	//Load up the array with dummy values
	for (auto i = 0; i < MAX_VERTICES; ++i)
	{
		for (auto j = 0; j < MAX_VERTICES; ++j)
		{
			graph[i][j] = INT_MAX;
		}
	}
	numVertices = 0;

}

Graph::~Graph()
{
	//no deletes required because the arrays are static
}

void Graph::AddEdge(std::string source, std::string target, int weight)
{
	graph[GetIndex(source)][GetIndex(target)] = weight;

}

void Graph::AddVertex(std::string label)
{
	if (numVertices < MAX_VERTICES)
	{
		labels[numVertices] = label;
	};
	++numVertices;
}

int Graph::GetIndex(std::string label) const
{
	for (auto i = 0; i < MAX_VERTICES; ++i)
	{
		if (labels[i] == label)
		{
			return i;
		}
	}

	return -1;
}

bool Graph::IsEdge(std::string source, std::string target) const
{
	if (graph[GetIndex(source)][GetIndex(target)] == INT_MAX)
	{
		return false;
	}

	return true;
	
}

//Precondition: Source and Target indices are valid members of the graph
//Postcondition: return the weighted value of the edge between the source and
//target indices
int Graph::GetWeight(int sourceIndex, int targetIndex) const
{
	return graph[sourceIndex][targetIndex];
}

void Graph::BreadthFirstSearch(std::string startingVertex) const
{
	//load up the visited array with -1
	int visited[MAX_VERTICES];
	for (auto i = 0; i < MAX_VERTICES; ++i)
	{
		visited[i] = -1;
	}

	int index = 0;
	queue<int> toVisit;
	toVisit.push(GetIndex(startingVertex));

	//the queue contains the vertices to visit, continue visiting until the queue is empty
	while (!toVisit.empty())
	{
		int vertex = toVisit.front();
		bool beenVisited = false;
		//search visited array to see if it's aready been visited
		for (auto i = 0; i < MAX_VERTICES; ++i)
		{
			//not visited, add to visited array and continue
			if (visited[i] == -1)
			{
				visited[index] = vertex;
				++index;
				break;
			}
			//visited
			else if (visited[i] == vertex)
			{
				beenVisited = true;
				break;
			}
		}
		toVisit.pop();

		//if popped vertex hasn't been visited then check it for neighbors to add to the search
		if (!beenVisited)
		{
			for (auto i = 0; i < numVertices; ++i)
			{
				if (IsEdge(labels[vertex], labels[i]))
				{
					toVisit.push(GetIndex(labels[i]));
				}
			}
		}
	}
	BreadthFirstSearch(startingVertex, visited);

}

void Graph::BreadthFirstSearch(std::string startingVertex, int visited[]) const
{
	cout << "starting BFS with vertex " << startingVertex << endl;
	int i = 0;
	while (visited[i] != -1 && i < MAX_VERTICES)
	{
		cout << "\t" << " visited " << labels[visited[i]] << endl;
		++i;
	}
	cout << endl;
}

//This implements the Dijkstra shortest path algorithm and sends the distances
//values to be printed
void Graph::DijkstraShortestPath(std::string startingVertex) const
{
	//initialize distance array for storing shortest path length
	int* distance = new int[numVertices];
	for (auto i = 0; i < numVertices; ++i)
	{
		distance[i] = INT_MAX;
	}
	//initialize special case of starting index
	distance[GetIndex(startingVertex)] = 0;
	//Initialize array of "used" vertices all set to 0
	int* usedVertices = new int[numVertices];
	for (auto i = 0; i < numVertices; ++i)
	{
		usedVertices[i] = 0;
	}
	//Initialize array for previous vertices, this tracks the vertex visited just before a shortest path was found
	int* prevVertex = new int[numVertices];
	for (auto i = 0; i < numVertices; ++i)
	{
		prevVertex[i] = -1;
	}

	//ALGORITHM to find shortest path
	for (auto i = 0; i < numVertices; ++i)
	{
		//Choose the smallest unused vertex
		auto smallestVertexNum = INT_MAX;
		auto smallestVertex = -1;
		for (auto j = 0; j < numVertices; ++j)
		{
			if ((usedVertices[j] == 0) && (distance[j] < smallestVertexNum))
			{
				smallestVertex = j;
				smallestVertexNum = distance[j];
			}
		}
		//if a new smallest vertex isnt found then we have searched the whole graph
		if (smallestVertex == -1)
		{
			break;
		}
		//Visit each neighbor of the smallestVertex and see if it is a shorter path
		for (auto k = 0; k < numVertices; ++k)
		{
			//Find the neighbors through edge checking
			if (IsEdge(labels[smallestVertex], labels[k]))
			{
				//This vertex hasn't been visited yet
				if (distance[k] == INT_MAX)
				{
					distance[k] = distance[smallestVertex] + graph[smallestVertex][k];
					prevVertex[k] = smallestVertex;
				}
				//This vertex is now being visited with a shorter path
				else if (distance[smallestVertex] + graph[smallestVertex][k] < distance[k])
				{
					distance[k] = distance[smallestVertex] + graph[smallestVertex][k];
					prevVertex[k] = smallestVertex;
				}
			}
		}
		//Mark vertex as used
		usedVertices[smallestVertex] = 1;
	}
	delete[] usedVertices;
	//Run the Print Algorithm
	DijkstraShortestPath(startingVertex, distance, prevVertex);



}

//This function prints the results of the Dijkstra shortest path algorithm
void Graph::DijkstraShortestPath(std::string startingVertex, int distance[], int prevVertex[]) const
{
	//print title
	cout << "Shortest Distance starting from vertex " << startingVertex << endl;

	//Print the path for each vertex
	for (auto i = 0; i < numVertices; ++i)
	{
		//vertex labels
		cout << "\t" << "to: " << labels[i] << "\t";

		//path lengths
		if (distance[i] == INT_MAX)
		{
			cout << "no path" << endl;
			continue;
		}

		else
		{
			cout << distance[i] << "\t" << "Path: ";
		}

		//path routes
		auto j = i;
		while (j != GetIndex(startingVertex))
		{
			cout << labels[j] << ", ";
			j = prevVertex[j];
		}
		cout << startingVertex << endl;
	}
	cout << endl;
	delete[] prevVertex;
	delete[] distance;
}

///<summary>
///prints out the 2D array with the weighted edge values
///</summary>
void Graph::PrintGraph() const
{
	//print header
	cout << "numVertices: " << numVertices << endl;
	
	//print column labels
	for (auto i = 0; i < numVertices; ++i)
	{
		cout << "\t" << labels[i];
	}

	cout << endl;

	//print row labels and contents
	for (auto i = 0; i < numVertices; ++i)
	{
		cout << labels[i];
		for (auto j = 0; j < numVertices; ++j)
		{
			if (graph[i][j] == INT_MAX)
			{
				cout << "\t";
			}
			else
			{
				cout << "\t" << graph[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}
