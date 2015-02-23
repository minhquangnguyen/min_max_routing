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
#define SN 10 //slot number


using namespace std;

typedef struct trans
{
	int tr;
	int re;
}trans;

extern BasePath **mb;
extern BasePath **minPaths;
extern int request_number;
extern int node_number;
unsigned long long state[SN];
std::vector<trans> sch[SN];

std::vector<pair<trans, vector<int> > >* _req = new std::vector<pair<trans, vector<int> > >[request_number];
bool gan(int slot, BasePath **v)
{
	int stt = 0;
	std::vector<pair<trans, vector<int> > >* req = new std::vector<pair<trans, vector<int> > >[request_number];
	std::vector<pair<trans, vector<int> > >::iterator it;
	pair<trans, vector<int> > t;
	//t.second = -1;
	for(int i = 0; i < request_number; i++)
	{
		t.first.tr = v[i]->m_vtVertexList[0]->getID();
		for(int j = 1; j < v[i]->m_vtVertexList.size(); j++)
		{
			t.first.re = v[i]->m_vtVertexList[j]->getID();
			req[i].push_back(t);
			it = req[i].end();
			t.first.tr = t.first.re;
		}
	}
	int s = 0;
	int count = 0, j;
	bool *vertex = new bool[node_number];
	memset(vertex, 0x00, node_number*sizeof(bool));
	do
	{
		if(slot*(s + 1) - 1 > SN)
			return false;
		for(int i = 0; i < request_number; i++)
		{
			//for(j = 0; j < req[i].size(); j++)
			j = 0;
			while(req[i][j].second.size() != 0 && j < req[i].size())
				j++;
				
			if(req[i][j].second.size() == 0 && j < req[i].size())
			{
				if(!vertex[req[i][j].first.tr] && !vertex[req[i][j].first.re])
				{
					for(int k = 0; k < slot; k++)
						req[i][j].second.push_back(slot*s + k);
					vertex[req[i][j].first.tr] = vertex[req[i][j].first.re] = true;
					j++;
				}
			}
			if(j == req[i].size())
				count++;
			
		}
		memset(vertex, 0x00, node_number*sizeof(bool));
		s++;
	}
	while(count < request_number);
	//std::vector<pair<trans, vector<int> > >::iterator t_it;
	for(int i = 0; i < request_number; i++)
	{
		//t_it = req[i].begin();
		//_req[i].assign(req[i].begin(), req[i].end());
		//req[i].assign(_req[i].begin(), _req[i].end());
		_req[i].swap(req[i]);
		
	}
	cout << "Hello" << endl;
	return true;
}

void display_long_long(unsigned long long a)
{
	for(int i = 0; i < 64; i++)
	{
		int j = a % 2;
		cout << j;
		a = a >> 1;
	}
}
void increment(BasePath **v)
{
	int bw = 1;
	while(gan(bw, v))
	{
		bw++;
	};
	memset(state, 0x00, SN*sizeof(unsigned long long));
	
	cout << "-------- Final -------------" << endl;
	for(int i = 0; i < request_number; i++)
	{
		for(int j = 0; j < _req[i].size(); j++)
		{
			cout << _req[i][j].first.tr << "-" << _req[i][j].first.re << ": ";
			for(int k = 0; k < _req[i][j].second.size(); k++)
			{
				mark_as_used(state[_req[i][j].second[k]], _req[i][j].first.tr);
				mark_as_used(state[_req[i][j].second[k]], _req[i][j].first.re);
				cout << _req[i][j].second[k] << ", ";
			}
			cout << "\t\t";
		}
		cout << endl;
	}	
	
	cout << "-------- long long -------------" << endl;
	for(int i = 0; i < SN; i++)
	{
		display_long_long(state[i]);
		//cout << state[i];
		cout << endl;
	}
}


bool set_bw(int i, int sn)
{
	//clear past assignment
	for(int j = 0; j < _req[i].size(); j++)
	{
		for(int k = 0; k < _req[i][j].second.size(); k++)
		{
			mark_as_un_used(state[_req[i][j].second[k]], _req[i][j].first.tr);
			mark_as_un_used(state[_req[i][j].second[k]], _req[i][j].first.re);
		}
		_req[i][j].second.clear();
	}
	
	for(int j = 0; j < _req[i].size(); j++)
	{
		//_req[i][j].first
		int c = 0;
		for(int k = 0; k < SN; k++)
		{
			if(!check_used(state[k], _req[i][j].first.tr) && !check_used(state[k], _req[i][j].first.re))
			{
				_req[i][j].second.push_back(k);
				c++;
			}
		}
	}
	return true;
}

bool check_used(unsigned long long s, int d) //Kiem tra xem, slot cua thiet bi d da su dung chua
{
	unsigned long long t = 1;
	t = t << (64 - d - 1);
	t = ~t;
	s = s & t;
	if(s != 0)
		return true;
	return false;
}

void mark_as_used(unsigned long long &s, int d)
{
	unsigned long long t = 1;
	t = t << (64 - d - 1);
	s = s | t;
	return;
}

void mark_as_un_used(unsigned long long &s, int d)
{
	unsigned long long t = 1;
	t = t << (64 - d - 1);
	t = ~t;
	s = s & t;
	return;
}
