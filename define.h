#include "GraphElements.h"
#include <string.h>

using namespace std;

extern BasePath ***b;
extern BasePath **mb;
extern int request_number;
extern request* r;
extern int node_number;
extern void recursive(BasePath** h, int c, int index);
extern void testDijkstraGraph();
extern void testYenAlg();
extern void init();
extern void testDjiktra();
extern void testProposed();
extern int calculate(BasePath** h);
extern void display();
extern bool assign_node(BasePath* p, int r);
extern bool increm_node(BasePath* p, int r);

extern void kspYen();
extern bool gan(int slot, BasePath **v);
extern void increment(BasePath **v);
void mark_as_used(unsigned long long &s, int d);
void mark_as_un_used(unsigned long long &s, int d);
void display_long_long(unsigned long long a);
bool set_bw(int i, int sn);
bool check_used(unsigned long long &s, int d);
