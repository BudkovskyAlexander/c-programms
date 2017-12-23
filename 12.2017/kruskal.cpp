#include <iostream>
#include <vector>
using namespace std;
 
struct Edge
{
	int weight, from, to;
 
	Edge(int _weight = -1, int _from = -1, int _to = -1) : weight(_weight), from(_from), to(_to) {}
};
 
void quickSort(vector<Edge> &g, int left, int right) 
{
	int i = left, j = right;
	Edge tmp;
	int pivot = g[(left + right) / 2].weight;
	while (i <= j) 
	{
            	while (g[i].weight < pivot)
            		i++;
            	while (g[j].weight > pivot)
            		j--;
            	if (i <= j) 
            	{
            	tmp = g[i];
            	g[i] = g[j];
            	g[j] = tmp;
            	i++;
            	j--;
            	}
	}
	if (left < j)
            	quickSort(g, left, j);
	if (i < right)
            	quickSort(g, i, right);
 
}
 
vector<Edge> Kruskal (vector<Edge> g, int n)
{
	quickSort(g, 0, g.size() - 1);
	vector <Edge> MST;
	int tree_id[n];
	for (int i=0; i<n; ++i)
		tree_id[i] = i;
	for (int i = 0; i<g.size(); i++)
	{
		if (tree_id[g[i].from] != tree_id[g[i].to])
		{
			MST.push_back(g[i]);
			int new_id = tree_id[g[i].from], old_id = tree_id[g[i].to];
			for (int j=0; j<n; ++j)
				if (tree_id[j] == old_id)
					tree_id[j] = new_id;	
		}
	}
	return MST;
}
 
int main() {
	int n = 5; int m = 7;
	vector <Edge> g;
	for (int i=0; i<m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		Edge t(a, b - 1, c - 1);
		g.push_back(t);
	}
	g = Kruskal(g, n);
	for (int i=0; i<g.size(); i++)
		cout << g[i].from + 1 << " - " << g[i].to + 1 << endl;
	return 0;
}
