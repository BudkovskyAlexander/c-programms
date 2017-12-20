#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;
 
struct Path
{
	long int data;
	int from;
	int to;
	int phase;
 
	Path(int _data = 0, int _from = -1, int _to = -1, int _phase = -1): data(_data), phase(_phase), from(_from), to(_to)
	{};
 
	vector<int> get_path()
	{
		generate_path(from, to);
		vertices.push_back(to);
		return vertices;	
	}
 
	void set_pathways(Path ** _pathways) { pathways = _pathways; }
 
	private:
 
	vector<int> vertices;
	Path **pathways;
 
	void generate_path(int start, int end)
	{
		if (pathways[start][end].phase == -1)
		{
			vertices.push_back(start);
			return;
		}
		generate_path(start, pathways[start][end].phase);
		generate_path(pathways[start][end].phase, end);
	}
 
};
 
Path ** floyd_warshall(int **g, int n)
{
	Path** path = new Path*[n];
	for (int i=0; i<n; ++i)
	{
		path[i] = new Path[n];
		for (int j=0; j<n; ++j)
			path[i][j] = (g[i][j] <= 0) ? Path(INT_MAX, i, j) : Path(g[i][j], i, j);
	}
	for (int phase = 0; phase<n; ++phase)
	{
		for (int i=0; i<n; ++i)
		{
			for (int j=0; j<n; ++j)
			{
				if (path[i][j].data > path[i][phase].data + path[phase][j].data)
				{
					path[i][j].data = path[i][phase].data + path[phase][j].data;
					path[i][j].phase = phase;
				}
			}
		}
	}
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			path[i][j].set_pathways(path);
	return path;
}
 
int main() {
	int n, ** g, from, to;
	cin >> n >> from >> to;
	g = new int*[n];
	for (int i=0; i<n; i++)
	{
		g[i] = new int[n];
		for (int j=0; j<n; ++j)
			cin >> g[i][j];
	}
	Path** distances = floyd_warshall(g, n);
	cout << distances[from][to].data << endl; // length
	vector<int> path = distances[from][to].get_path(); // path
	for (int i=0; i<path.size(); i++)
		cout << path[i] << ((i == path.size() - 1) ? "" : "->");
	return 0;
}
