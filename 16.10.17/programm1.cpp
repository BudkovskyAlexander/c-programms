#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>
using namespace std;
 
struct Node
{
	int data = 0;
	bool used = false;
	bool valueChanged = false;
	vector<int> childs;
	vector<int> changers;
 
	bool isChanger(int index)
	{
		for (int i=0; i<changers.size(); ++i)
			if (changers[i] == index) return true;
		return false;
	}
};
 
int main() {
	int n = 0, startIndex = 0, endIndex = 0;
	cin >> n >> startIndex >> endIndex;;
	Node a[n];
	queue<int> q;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			int data; cin >> data;
			a[i].childs.push_back(data);
		}
	}
	q.push(startIndex);
	while (q.size() != 0)
	{
		int index = q.front();
		q.pop();
		if (index == endIndex) break;
		a[index].used = true;
		Node *node = &a[index];
		for (int i=0; i < node -> childs.size(); i++)
		{
			if (node -> childs[i] != 0)
			{
				if (!node -> isChanger(i))
				{
					int temp = node -> data + node -> childs[i];
					if (a[i].data > temp || !a[i].valueChanged)
					{
						a[i].data = temp;
						a[i].changers.push_back(index);
						a[i].valueChanged = true;
					}
				}
				if (!a[i].used)
				{
					q.push(i);
					a[i].used = true;
				}
			}
		}
	}
	int index = endIndex;
	vector<int> path;
	path.push_back(index);
	while (index != startIndex)
	{
		int min = INT_MAX;
		int nextIndex = 0;
		for (int i=0; i<a[index].childs.size(); i++)
		{
			if (a[index].childs[i] != 0)
			{
				int temp = a[index].childs[i] + a[i].data;
				if (min >= temp)
				{
					min = temp;
					nextIndex = i;
				}
			}
		}
		index = nextIndex;
		path.push_back(index);
	}
	cout << a[endIndex].data << endl;
	for (int i=path.size() - 1; i>=0; i--)
	{
		cout << path[i] + 1;
		if (i != 0)
			cout << " -> ";
	}
	return 0;
}
