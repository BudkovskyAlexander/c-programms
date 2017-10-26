#include <iostream>
#include <vector>
using namespace std;
 
int **a;
int n;
vector <bool> visited;
vector <int> path;
 
bool hamilton(int curr)
{
    path.push_back(curr);
    if (path.size() == n)
    {
        if (a[path[0]][path.back()] == 1)
            return true;
        else
        {
            path.pop_back();
            return false;
        }
    }
    visited[curr] = true;
 
    for (int nxt = 0; nxt < n; ++nxt)
        if (a[curr][nxt] == 1 && !visited[nxt]) 
            if (hamilton(nxt))
                return true;
    visited[curr] = false;
    path.pop_back();
 
    return false;
}
 
int main() {
	cin >> n;
	a = new int *[n];
	for (int i=0; i<n; ++i)
	{
		a[i] = new int[n];
		visited.push_back(false);
	}
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			cin >> a[i][j];
	int i = 0;
	while (i < n && !hamilton(i++));
 
	for (int i=0; i<path.size(); ++i)
	{
		if (i != path.size() - 1)
			cout << path[i] + 1 << " -> ";
		else
			cout << path[i] + 1;
	}
	return 0;
}
