#include <iostream>
#include <string>
using namespace std;

class knot{
private :
	string s;
	long long leight;
	
	
public:
	int color; //RED=1; BLACK=0;
	knot *parent;
	knot *right;
	knot *left;
	bool was;
	knot(string ss){
		s = ss;
		leight = s.size();
		color = 1;
		parent = NULL;
		right = NULL;
		left = NULL;
		was = false;
	}
	
	~knot(){
		s.clear();
		leight = NULL;
		color = NULL;
		parent = NULL;
		right = NULL;
		left = NULL;
		
	}

	int getLeight(){
		return leight;
	}
	void printString(){
		cout << s;
	}
	string getString(){
		return s;
	}

	void operator= (knot*k){
		s = k->s;
		leight = k->leight;
		color = k->color;
	}
	
};

class String_set{
private:
	knot *root;

	void addToTree(string NewString, knot*temp){
		if ((temp->getLeight()) > NewString.size()){
			if (temp->left != NULL)
				addToTree(NewString, temp->left);
			else{
				temp->left = new knot(NewString);
				temp->left->color = 1;
				temp->left->parent = temp;
				repairTree(temp->left);
			}
		}
		else{
			if (temp->right != NULL)
				addToTree(NewString, temp->right);
			else{
				temp->right = new knot(NewString);
				temp->right->color = 1;
				temp->right->parent = temp;
				repairTree(temp->right);
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

	void copy(knot*org, knot*Cop){
		if (!(org->was)){
			Cop->operator=(org);
		}
		org->was = true;
		if ((org->right != NULL) && !(org->right->was)){
			if (Cop->right == NULL){
				Cop->right = new knot("");
				Cop->right->parent = Cop;
			}
			copy(org->right, Cop->right);
		}
		else{
			if ((org->left != NULL) && !(org->left->was)){
				if (Cop->left == NULL){
					Cop->left = new knot("");
					Cop->left->parent = Cop;
				}
				copy(org->left, Cop->left);
			}
			else{
				if (org->parent != NULL){
					copy(org->parent, Cop->parent);
				}
			}
		}
	}

	void Show(knot*temp){
		if (!(temp->was)){
			temp->printString();
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

	knot* FindL(string str, knot*temp){
		if ((temp!=NULL)&&(str.size() == (temp->getLeight())) && str == temp->getString()){
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


	void RotLeft(knot*Newroot){
		knot*temp = Newroot->left;
		Newroot->parent->right = temp;
		if (temp != NULL){
			temp->parent = Newroot->parent;
			Newroot->left = temp->parent;
			Newroot->parent = temp->parent->parent;
			Newroot->left->parent = Newroot;
			Newroot->parent->right = Newroot;
		}
		else{
			temp = Newroot->parent;
			Newroot->parent = temp->parent;
			temp->parent = Newroot;
			Newroot->left = temp;
			Newroot->parent->left = Newroot;
		}
		if (Newroot->parent == NULL)
			root = Newroot;
	}

	void RotRight(knot*Newroot){
		knot*temp = Newroot->right;
		Newroot->parent->left = temp;
		if (temp != NULL){
			temp->parent = Newroot->parent;
			Newroot->right = temp->parent;
			Newroot->parent = temp->parent->parent;
			Newroot->right->parent = Newroot;
			Newroot->parent->left = Newroot;
		}
		else{
			temp = Newroot->parent;
			Newroot->parent = temp->parent;
			temp->parent = Newroot;
			Newroot->right = temp;
			Newroot->parent->right = Newroot;
		}
		if (Newroot->parent == NULL)
			root = Newroot;
	}

	void repairTree(knot*temp){
		bool b = true;
		if (temp->parent->parent != NULL){
			if ((temp->color == 1) && (temp->parent->color == 1)){
				if (temp->parent->getLeight() > temp->parent->parent->getLeight()){
					if ((temp->parent->parent->left == NULL) || ((temp->parent->parent->left->color) == 0)){
						RotLeft(temp->parent);
						temp->parent->parent->color = 0;
						if (temp->parent->left != NULL)
							temp->parent->left->color = 1;
						b = false;
					}
					else{
						temp->parent->color = 0;
						temp->parent->parent->left->color = 0;
						temp->parent->parent->color = 1;
						b = false;
					}
				}
				if ((temp->parent->getLeight() <= temp->parent->parent->getLeight()) && b){
					if ((temp->parent->parent->right == NULL) || ((temp->parent->parent->right->color) == 0)){
						RotRight(temp->parent);
						temp->parent->parent->color = 0;
						if (temp->parent->right != NULL)
							temp->parent->right->color = 1;
					}
					else{
						temp->parent->color = 0;
						temp->parent->parent->right->color = 0;
						temp->parent->parent->color = 1;
					}
				}
			}
		}

		if (temp->parent->parent != NULL){
			repairTree(temp->parent);
		}
		root->color = 0;
	}

	int WeGotThePower(int res, knot*temp){
		if (!(temp->was)){
			res++;
		}
		temp->was = true;
		if ((temp->right != NULL) && !(temp->right->was)){
			WeGotThePower(res, temp->right);
		}
		else{
			if ((temp->left != NULL) && !(temp->left->was)){
				WeGotThePower(res, temp->left);
			}
			else{
				if (temp->parent != NULL)
					WeGotThePower(res, temp->parent);
				else
					return res;
			}
		}

	}

	/*knot* Leftest(knot*temp){
		if (temp->left != NULL)
			Leftest(temp->left);
		else
			return temp;
	
}*/

	/*void Cut(knot*target){
		if (target->left == NULL&&target->right == NULL){
			if (target->getLeight() < target->parent->getLeight()){
				target->parent->left = NULL;
				target->~knot();
			}
			else{
				target->parent->right = NULL;
				target->~knot();
			}
		}
	/*	if (target->left != NULL && target->right == NULL){
			if (target->getLeight() < target->parent->getLeight()){
				if (target->color == 0){
					if (target->parent->right!=NULL && target->parent->right->color == 1){
						RotLeft(target->parent->right);
						target->parent->left = target->left;
					}
					else{
						if (target->parent->right == NULL)
							target->parent->left = target->left;
						else{
							if ((target->parent->right->right==NULL && target->parent->right->left==NULL)||(target->parent->right->right->color == 0 && target->parent->right->left->color == 0)){
								target->parent->right->color == 1;
							}
						}
					}
				}
			}
			else{
				if (target->color == 0){
					if (target->parent->left->color == 1){
						RotLeft(target->parent->left);
						target->parent->right = target->left;
					}
				}
				
			}
		}
		if (target->left == NULL && target->right != NULL){
			if (target->getLeight() < target->parent->getLeight()){
				if (target->color == 0){
					if (target->parent->right->color == 1){
						RotLeft(target->parent->right);
						target->parent->left = target->right;
					}
				}
			}
			else{
				if (target->color == 0){
					if (target->parent->left->color == 1){
						RotLeft(target->parent->left);
						target->parent->right = target->right;
					}
				}
			}
		} 
		if (target->left != NULL && target->right != NULL){
			knot*zzz;
			if (target->right != NULL)
				 zzz= Leftest(target->right);
			else
				zzz = NULL;
			target = zzz;
			Cut(zzz);
		}
 }*/


public:
	String_set(){
		root = NULL;
	}

	~String_set(){
		Kill(root);
	}

	void add(string NewString){
		if (root == NULL){
			root = new knot(NewString);
			root->color = 0;
		}
		else{
			addToTree(NewString, root);
			
		}
	}

	void ShowAllTree(){
		Show(root);
		AfterShow(root);
	}
	
	knot* operator[](string searchS){
		knot* ret = FindL(searchS, root);
		if (ret!=NULL)
			return ret;
		else{
			string ans="Ýëåìåíòà \""+searchS+"\" íå ñóùåñòâóåò!";
			ret = new knot(ans);
			return ret;
		}
			

	}

	void operator= (String_set &ans){
		if (root == NULL)
			root = new knot("");
		
		copy(ans.root, root);
		ans.AfterShow(ans.root);
	}

	int Power(){
		return WeGotThePower(0, root);
	}

	/*void Delete(string target){
		Cut(FindL(target, root));
	}*/   //çà÷àäêè ôóíêöèè óäàëåíèÿ óçëà ïî çíà÷åíèþ

};

int main(){
	setlocale(0, "");
	String_set God;
	String_set Father; //îáúÿâëåíèå êîíòåéíåðîâ
	God.add("4444"); 
	God.add("666666");
	God.add("22");
	God.add("333");
	God.add("55555");
	God.add("4004");
	God.add("7777777");
	God.add("6----6");
	God.add("--66--"); //èíèöèàëèçàöèÿ God 
	Father = God; //êîïèðóåì God -> Father
	cout << endl;
	Father.ShowAllTree(); //âûâîäèì ìàññèâ Father, óáåæäàåìñÿ, ÷òî îí ñêîðïèðîâàëñÿ (âàæíî, ÷òî ýòî íîâûé êîíòåéíåð, à íå íàáîð ññûëîê íà óæå ñóùåñòâóþùèé)
	cout<<Father.Power()<<endl; //âûâîäèì ìîùíîñòü Father
	Father["1234"]->printString(); //èùåì ýëåìåíò ñî çíà÷åíèåì "1234", óáåæäàåìñÿ, ÷òî òàêîãî íåò
	cout << endl;
	God["22"]->printString(); //èùåì ýëåìåíò ñî çíà÷åíèåì "22", óáåæäàåìñÿ, ÷òî îí åñòü è âûâîäèì åãî
	cout << endl;
	system("pause");
	return 0;
}
