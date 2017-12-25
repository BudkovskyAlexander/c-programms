#include <iostream>
#include <limits.h>
#include <queue>
using namespace std;
 
int * Dijkstra(int **a, int n, int from)
{
	int INF = INT_MAX; 
	int *d = new int[n];
	bool *used = new bool[n];
	queue<int> q;
	for (int i=0; i<n; i++)
		d[i] = INF;
	d[from] = 0;
	q.push(from);
	used[from] = true;
	while (!q.empty())
	{
		int vertex = q.front();
		q.pop();
		for (int i=0; i<n; i++)
			if (a[vertex][i] > 0 && d[i] > a[vertex][i] + d[vertex])
			{
				d[i] = a[vertex][i] + d[vertex];
				q.push(i);
				used[i] = true;
			}
	}
	return d;
}
 
int main() {
	int n = 5;
	int **a = new int*[n];
	for (int i=0; i<n; i++)
		a[i] = new int[n];
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			cin >> a[i][j];
	int *d = Dijkstra(a, n, 0);
	for (int i=0; i<n; i++)
		cout << d[i] << " ";
	return 0;
}
