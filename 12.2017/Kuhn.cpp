#include <iostream>
#include <vector>
 
using namespace std;
 
 
int n, k;
vector < vector<int> > g;
vector<int> match;
vector<char> used;
 
bool kuhn (int v) {
	if (used[v])  return false;
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (match[to] == -1 || kuhn (match[to])) {
			match[to] = v;
			return true;
		}
	}
	return false;
}
 
int main() {
	for (int i=0; i<n; i++)
	{
		int a,b,c;
		cin >> a >> b >> c;
		g[i].push_back(a);
		g[i].push_back(b);
		g[i].push_back(c);
	}
 
	match.assign (k, -1);
	for (int v=0; v<n; ++v) {
		used.assign (n, false);
		kuhn (v);
	}
 
	for (int i=0; i<k; ++i)
		if (match[i] != -1)
			printf ("%d %d\n", match[i]+1, i+1);
}
