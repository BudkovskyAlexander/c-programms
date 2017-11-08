#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void input(int n,int arr[][2])
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            cin >> arr[i][j];
        }
    }
}

void create_adjacency_list(int m, vector<vector<int> >& adj_list, int arr[][2])
{
    for(int i = 0; i < m; i++)
    {
        adj_list[arr[i][0]].push_back(arr[i][1]);
        adj_list[arr[i][1]].push_back(arr[i][0]);
    }
}

void Find_The_Way(vector<vector<int> >& adj_list, int m, int v0, int v1)
{
    queue<int> q;
    vector<int> p(m);
    bool used[m];

    for(int i = 0; i < m; i++)
    {
        used[i] = 0;
    }

    q.push(v0);
    used[v0] = 1;
    p[v0] = -1;

    while(!q.empty())
    {
        int n = q.front();
        q.pop();

        for(unsigned int i = 0; i < adj_list[n].size(); i++)
        {
            int temp = adj_list[n][i];

            if(!used[temp])
            {
                used[temp] = 1;
                q.push(temp);
                p[temp] = n;
            }
        }
    }

    if(!used[v1])
    {
        cout << "there is no way";
        return;
    }

    vector<int> path;
    int length(0);

    for(int i = v1; i!=-1; i = p[i])
    {
        path.push_back(i);
    }
    reverse (path.begin(), path.end());
    cout << "Path: ";
    for(unsigned int i = 0; i < path.size(); i++)
    {
        cout << path[i] << " ";
        length++;
    }

    for(unsigned int i = 0; i < path.size(); i++)
    {
        for(unsigned int j = 0; j < adj_list[v0].size(); j++)
        {
            if(adj_list[v0][j] == path[i])
            {
                int temp = adj_list[v0][j];
                adj_list[v0].erase(adj_list[v0].begin()+j);
                v0 = temp;
            }
        }
    }

    cout << "length: " << length-1;
    cout << endl;

}

int main()
{
    int NumberOfVerticies;
    int NumberOfRibs;
    int V0;
    int V1;

    cin >> NumberOfVerticies;
    cin >> NumberOfRibs;
    cin >> V0;
    cin >> V1;

    vector<vector<int> > AdjacencyList(NumberOfVerticies);
    int EdgeList[NumberOfRibs][2];

    input(NumberOfRibs, EdgeList);

    create_adjacency_list(NumberOfVerticies, AdjacencyList, EdgeList);
    Find_The_Way(AdjacencyList, NumberOfVerticies, V0, V1);
    Find_The_Way(AdjacencyList, NumberOfVerticies, V0, V1);

    return 0;
}
