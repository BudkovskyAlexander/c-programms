#include <iostream>
#include <string>
using namespace std;

class knot{
private:
	string s;
	long long leight;
	long long num;

public:
	knot *parent;
	knot *right;
	knot *left;
	bool was;
	knot(string ss, long long nu){
		num = nu;
		s = ss;
		leight = s.size();
		parent = NULL;
		right = NULL;
		left = NULL;
		was = false;
	}

	knot(string ss){
		num = 0;
		s = ss;
		leight = s.size();
		parent = NULL;
		right = NULL;
		left = NULL;
		was = false;
	}

	~knot(){
		num = NULL;
		s.clear();
		leight = NULL;
		parent = NULL;
		right = NULL;
		left = NULL;

	}

	void setNum(long long New){
		num = New;
	}

	long long getNum(){
		return num;
	}

	long long getLeight(){
		return leight;
	}

	void printSelf(){
		cout << "\"" << s << "\" - "<<num;
	}

	string getString(){
		return s;
	}

	knot& operator= (int copy){
		num = copy;
		return *this;
	}

	knot& operator= (knot &k){
		num = k.num; 
		leight = k.leight;
		s = k.s;
		return *this;
	}
};

class String_dict{
private:
	knot*root;

	void addToTree(string NewString, knot*temp, int n){
		if ((temp->getLeight()) > NewString.size()){
			if (temp->left != NULL)
				addToTree(NewString, temp->left, n);
			else{
				temp->left = new knot(NewString);
				temp->left->parent = temp;
				temp->left->setNum(n);
			}
		}
		else{
			if (temp->right != NULL)
				addToTree(NewString, temp->right, n);
			else{
				temp->right = new knot(NewString);
				temp->right->parent = temp;
				temp->right->setNum(n);
			}
		}

	}

	void Kill(knot*temp){
		temp->was = true;
		if ((temp->right != NULL)){
			Kill(temp->right);
		}
		else{
			if ((temp->left != NULL)){
				Kill(temp->left);
			}
			else{
				if (temp->parent != NULL){
					knot*kill = temp->parent;
					temp->~knot();
					if (kill->left != NULL && kill->left->was)
						kill->left = NULL;
					if (kill->right != NULL && kill->right->was)
						kill->right = NULL;
					Kill(kill);
				}
				else
					temp->~knot();
			}
		}
	}

	void Show(knot*temp){
		if (!(temp->was)){
			temp->printSelf();
			cout << endl;
		}
		temp->was = true;
		if ((temp->right != NULL) && !(temp->right->was)){
			Show(temp->right);
		}
		else{
			if ((temp->left != NULL) && !(temp->left->was)){
				Show(temp->left);
			}
			else{
				if (temp->parent != NULL)
					Show(temp->parent);
			}
		}
	}

	void AfterShow(knot*temp){
		temp->was = false;
		if ((temp->right != NULL) && (temp->right->was)){
			AfterShow(temp->right);
		}
		else{
			if ((temp->left != NULL) && (temp->left->was)){
				AfterShow(temp->left);
			}
			else{
				if (temp->parent != NULL)
					AfterShow(temp->parent);
			}
		}
	}

	knot* FindL(string str, knot*temp){
		if ((temp != NULL) && (str.size() == (temp->getLeight())) && str == temp->getString()){
			return temp;
		}
		else{

			if ((temp != NULL) && (str.size() >= (temp->getLeight()))){
				temp = FindL(str, temp->right);
			}
			else{
				if ((temp != NULL) && (str.size() < (temp->getLeight())))
					temp = FindL(str, temp->left);
				else
					return temp;
			}

		}
		return temp;
	}

	void DeleteZero(knot*del){
		if (del->parent != NULL){
			if (del->getLeight() < del->parent->getLeight()){
				del->parent->left = NULL;
				del->~knot();
			}
			else{
				del->parent->right = NULL;
				del->~knot();
			}
		}
		else{
			del->~knot();
		}
	}

	void DeleteOne(knot*del){
			if (del->right != NULL){
				if (del->getLeight() < del->parent->getLeight()){
					del->parent->left = del->right;
					del->right->parent = del->parent;
					del->~knot();
				}
				else{
					del->parent->right = del->right;
					del->right->parent = del->parent;
					del->~knot();
				}
			}
			else{
				if (del->getLeight() < del->parent->getLeight()){
					del->parent->left = del->left;
					del->left->parent = del->parent;
					del->~knot();
				}
				else{
					del->parent->right = del->left;
					del->left->parent = del->parent;
					del->~knot();
				}
			}
		
	}

	knot* FindSmallest(knot*del){
		if (del->left == NULL){
			return del;
		}
		else{
			return FindSmallest(del->left);
		}

	}

	void DeleteTwo(knot*del){
		knot*con = FindSmallest(del->right);
		del = con;
		Del(con);
	}

	void Del(knot*del){
		if (del->parent != NULL){
			if ((del->right != NULL) && (del->left != NULL)){
				DeleteTwo(del);
			}
			else{
				if ((del->right != NULL) || (del->left != NULL)){
					DeleteOne(del);
				}
				else{
					DeleteZero(del);
				}
			}
		}
		else{
			if ((del->right != NULL) && (del->left != NULL)){
				DeleteTwo(del);
			}
			else{
				if ((del->right != NULL) || (del->left != NULL)){
					if (del->right != NULL){
						root = del->right;
						root->parent = NULL;
						del->~knot();
					}
					else{
						root = del->left;
						root->parent = NULL;
						del->~knot();
					}
				}
				else{
					del->~knot();
				}
			}
		}
	}

public:
	String_dict(){
		root = NULL;
	}

	~String_dict(){
		Kill(root);
	}

	void ShowAllTree(){
		Show(root);
		AfterShow(root);
	}

	void add(string NewString, int n){
		if (root == NULL){
			root = new knot(NewString, n);
		}
		else{
			if (FindL(NewString, root) == NULL)
				addToTree(NewString, root, n);
			else
				operator[](NewString).setNum(n);

		}
	}

	knot &operator[] (string searchS){
		knot* ret = FindL(searchS, root);
		if (ret != NULL)
			return *ret;
		else{
			add(searchS, 0);
			ret = FindL(searchS, root);
			return *ret;
		}


	}

	void Delete(string d){
		knot*del = FindL(d, root);
		if (del != NULL)
			Del(del);
	}

};

int main(){
	String_dict A;
	A.add("Spb", 77);
	A.add("Moscow", 1);
	A.add("Vorkuta", 778);
	A.ShowAllTree();
	cout << endl;
	A["Moscow"] = 2;
	A["Lipetsk"] = 777;
	A.ShowAllTree();
	cout << endl;
	A.Delete("Moscow");
	A.ShowAllTree();
	cout << endl;
	A.Delete("Spb");
	A.ShowAllTree();

	cout << endl;
	system("pause");
	return 0;
}
