#include <limits>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include "GraphElements.h"
#include "Graph.h"
#include "DijkstraShortestPathAlg.h"
#include "YenTopKShortestPathsAlg.h"
#include "define.h"
#define KSP 5
#define BW 10
using namespace std;

BasePath ***b;
BasePath **mb;
BasePath **minPaths;
BasePath** al;
int minCommon = 0x7fffffff;
int *bandwidth_node;
int *_bandwidth_node;
int node_number;
int request_number;
request* r;

Graph *my_graph_pt;

bool increm_node();

void testDijkstraGraph()
{
	Graph* my_graph_pt = new Graph("data/danYen");
	DijkstraShortestPathAlg shortest_path_alg(my_graph_pt);
	BasePath* result =
		shortest_path_alg.get_shortest_path(
			my_graph_pt->get_vertex(0), my_graph_pt->get_vertex(5));
	result->PrintOut(cout);
}
void testYenAlg()
{
	Graph my_graph("data/danYen");
	YenTopKShortestPathsAlg yenAlg(my_graph, my_graph.get_vertex(0),
		my_graph.get_vertex(5));

	int i=0;
	while(yenAlg.has_next())
	{
		++i;
		yenAlg.next()->PrintOut(cout);
	}
}
void init()
{
	my_graph_pt = new Graph("data/danYen");
	node_number = 7;
	ifstream ifs("data/request.txt");
	
	ifs >> request_number;
	r = new request[request_number];

	b = new BasePath**[request_number];
	mb = new BasePath*[request_number];
	al = new BasePath*[request_number];
	
	bandwidth_node = new int[node_number];
	
	
	for(int i = 0; i < request_number; i++)
	{
		b[i] = new BasePath*[KSP];
	}
		
	for(int i = 0; i < request_number; i++)
	{
		ifs >> r[i].source;
		ifs >> r[i].destination;
	}
	
	ifs.close();
	return;
}
void kspYen()
{
	init();
	for(int i = 0; i < request_number; i++)
	{ 
		YenTopKShortestPathsAlg yenAlg(*(my_graph_pt), my_graph_pt->get_vertex(r[i].source), my_graph_pt->get_vertex(r[i].destination));
		int c = 0; 
		while(yenAlg.has_next())
		{
			b[i][c] = new BasePath(yenAlg.next());
			c++;
			if(c >= KSP)
				break;
		}
	}
	
	minPaths = new BasePath*[request_number];
	for(int i = 0; i < KSP; i++)
		if(b[0][i] != NULL)
		{
			al[0] = b[0][i];
			recursive(al, 1, 1);
		}
	
	for(int i = 0; i < request_number; i++)
		{
			for(std::vector<BaseVertex*>::const_iterator pos = minPaths[i]->m_vtVertexList.begin(); 
																				pos!=minPaths[i]->m_vtVertexList.end();++pos)
			{
				cout << (*pos)->getID() << " ";
			}
			cout << endl;
		}
	return;
}
void display()
{
	for(int i = 0; i < request_number; i++)
	{
		cout << "Rout for: " << r[i].source << " - " << r[i].destination << endl;
		for(int j = 0; j < KSP; j++)
		if(b[i][j] != NULL)
		{
			for(std::vector<BaseVertex*>::const_iterator pos = b[i][j]->m_vtVertexList.begin(); 
																				pos!=b[i][j]->m_vtVertexList.end();++pos)
			{
				cout << (*pos)->getID() << " ";
			}
			cout << endl;
		}
	}

}
void recursive(BasePath** h, int c, int index)
{
	if(index == request_number)
	{
		int temp = calculate(h);
		if(temp < minCommon)
		{
			minCommon = temp;
			for(int i = 0; i < request_number; i++)
				minPaths[i] = h[i];
		}
		return;
	}
	for(int j = 0; j < KSP; j++)
	{
		if(b[c][j] != NULL)
		{
			h[index] = b[c][j];
			int id = index + 1;
			recursive(h, c + 1, id);
		}
	}

}

int calculate(BasePath** h) // count the number of intersect points in routs 
{
	int count = 0;
	map<int, int> m;
	std::map<int, int>::iterator it;
	for(int i = 0; i < request_number; i++)
	{
		for(std::vector<BaseVertex*>::const_iterator pos = h[i]->m_vtVertexList.begin(); 
																			pos!=h[i]->m_vtVertexList.end();++pos)
		{
			it = m.find((*pos)->getID());
			if (it != m.end())
			{
				it->second++;
				count++;
			}
			else
			{
				pair<int, int> p((*pos)->getID(), 1);
				m.insert(p);
			}
		}
	
	}
	return count;
}

bool assign_node(BasePath* p, int r)
{
	for(std::vector<BaseVertex*>::const_iterator pos = p->m_vtVertexList.begin(); 
																			pos!=p->m_vtVertexList.end();++pos)
	{
		bandwidth_node[(*pos)->getID()] += r;
		if(bandwidth_node[(*pos)->getID()] > BW)
			return false;
	}
	
	return true;
}


void testDjiktra()
{
	//Graph* my_graph_pt = new Graph("data/danYen");
	
	init();
	
	DijkstraShortestPathAlg shortest_path_alg(my_graph_pt);
	
	for(int i = 0; i < request_number; i++)	
	{
		mb[i] = shortest_path_alg.get_shortest_path(my_graph_pt->get_vertex(r[i].source), my_graph_pt->get_vertex(r[i].destination));
	}
	
	bool bRate = true;
	int rate = 0;
	memset(bandwidth_node, 0x00, node_number * sizeof(int));
	while(bRate)
	{
		for(int i = 0; i < request_number; i++)	
		{
			if(!assign_node(mb[i], rate))
			{
				bRate = false;
				break;
			}
		}
		if(!bRate)
			break;
		rate++;
		memset(bandwidth_node, 0x00, node_number * sizeof(int));
	}
	rate--;
	memset(bandwidth_node, 0x00, node_number * sizeof(int));
	for(int i = 0; i < request_number; i++)	
		assign_node(mb[i], rate);
		
	for(int i = 0; i < request_number; i++)	
	{
		for(std::vector<BaseVertex*>::const_iterator pos = mb[i]->m_vtVertexList.begin(); 
																			pos!=mb[i]->m_vtVertexList.end();++pos)
		{
			cout << (*pos)->getID() << ": " << bandwidth_node[(*pos)->getID()] << "\t";
		}
		cout << endl;
	}
	return;
}

void testProposed()
{
	kspYen();
	bool bRate = true;
	int rate = 0;
	memset(bandwidth_node, 0x00, node_number * sizeof(int));
	while(bRate)
	{
		for(int i = 0; i < request_number; i++)	
		{
			if(!assign_node(minPaths[i], rate))
			{
				bRate = false;
				break;
			}
		}
		if(!bRate)
			break;
		rate++;
		memset(bandwidth_node, 0x00, node_number * sizeof(int));
	}
	rate--;
	memset(bandwidth_node, 0x00, node_number * sizeof(int));
	for(int i = 0; i < request_number; i++)	
		assign_node(minPaths[i], rate);
	
		for(int i = 0; i < request_number; i++)	
	{
		for(std::vector<BaseVertex*>::const_iterator pos = minPaths[i]->m_vtVertexList.begin(); 
																			pos!=minPaths[i]->m_vtVertexList.end();++pos)
		{
			cout << (*pos)->getID() << ": " << bandwidth_node[(*pos)->getID()] << "\t";
		}
		cout << endl;
	}
}
