#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;
 
struct Edge 
{
	int from, to, weight;
	Edge (int _from, int _to, int _weight) : from(_from), to(_to), weight(_weight) {}
};
 
vector<int> Ford_Bellman(vector <Edge> g, int n, int m, int v) 
{
	int INF = INT_MAX;
	vector<int> d (n, INF);
	d[v] = 0;
	for (int i=0; i<n-1; ++i)
		for (int j=0; j<m; ++j)
			if (d[g[j].from] < INF)
				d[g[j].to] = min (d[g[j].to], d[g[j].from] + g[j].weight);
	return d;			
}
 
int main() {
 
	return 0;
}
