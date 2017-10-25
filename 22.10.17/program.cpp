#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void input(int n, int arr[][2]){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < 2; j++){cin >> arr[i][j];}
	}
}

void createadjmat(int n, int m, int arr[][2], bool **arr2){
	for (int i = 0; i < m; i++){
		for (int j = 0; j < m; j++){arr2[i][j] = 0;}
	}

	for (int i = 0; i < n; i++){
		arr2[arr[i][0]][arr[i][1]] = 1;
		arr2[arr[i][1]][arr[i][0]] = 1;
	}
}

void Find_p(vector<vector<int> >& adj_list, int n, bool **arr){
	int v = 0, cr = 0, cr2 = 0;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (arr[i][j] == 1){ cr2++; }
		}

		if (cr2 % 2 == 1){ v = i; break; }
	}



	for (unsigned int i = 0; i < adj_list.size(); i++){
		if (adj_list[i].size() % 2 == 1){
			v = i;
			break;
		}
	}

	stack<int> _stack;
	_stack.push(v);

	while (!_stack.empty()){
		int p = _stack.top();

		for (int i = 0; i < n; i++){
			if (arr[p][i] == 1){
				_stack.push(i);
				arr[p][i] = 0;
				arr[i][p] = 0;
				break;
			}
		}

		if (p == _stack.top()){
			_stack.pop();
			cout << p << " ";
		}
	}

}

bool Is_Euler(vector<vector<int> >& adj_list, int n, bool **arr){
	int cr = 0;
	int cr2 = 0;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (arr[i][j] == 1){ cr2++; }
		}

		if (cr2 % 2 == 1){
			cr++;
			cr2 = 0;
		}
	}

	if (cr > 2){ return false; }

	return true;
}

int main()
{
	int NumVert, NumR;

	cin >> NumVert >> NumR;

	if (NumR == 0 || NumVert == 0){return 0;}

	vector<vector<int> > AdjList(NumVert);
	int EdgL[NumR][2];
	bool **AdjM = new bool*[NumVert];

	for (int i = 0; i < NumVert; i++){AdjM[i] = new bool[NumVert];}

	input(NumR, EdgL);
	createadjmat(NumR, NumVert, EdgL, AdjM);

	if (Is_Euler(AdjList, NumVert, AdjM)){Find_p(AdjList, NumVert, AdjM);}
	else {return 0;}

	for (int i = 0; i < NumVert; i++){delete[] AdjM[i];}

	return 0;
}
