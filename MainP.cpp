/************************************************************************/
/* $Id: MainP.cpp 65 2010-09-08 06:48:36Z yan.qi.asu $                                                                 */
/************************************************************************/
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
using namespace std;
/*extern BasePath ***b;
extern int request_number;
extern request* r;
extern BasePath ***b;
extern int request_number;
extern int calculate(BasePath** h);
extern void display();
extern request* r;
extern void recursive(BasePath** h, int c, int index);
extern void testDijkstraGraph();
extern void testYenAlg();
extern void init();
extern void kspYen();*/
extern BasePath **minPaths;
extern BasePath **mb;
int main(...)
{
	cout << "Welcome to the real world!";
	cout << "Enter 0/1. O for Dijktra-based, 1 for my proposed method" << endl;
	int c;
	cin >> c;
	if(c == 0)
	{
		testDjiktra();
		increment(mb);
	}
	else
	{
		testProposed();
		increment(minPaths);
	}
	return 0;

}
