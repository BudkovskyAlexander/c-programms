#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sym {
	char ch;
	float freq;
	char code[255];
	struct sym *left;
	struct sym *right;
} sym;

sym *makeTree(sym *psym[],int k) {
		int i;
		sym *temp;
		temp=(sym*)malloc(sizeof(sym));
		temp->freq=psym[k-1]->freq+psym[k-2]->freq;
		temp->code[0]=0;
		temp->left=psym[k-1];
		temp->right=psym[k-2];
		if(k==2) { return temp;
        } else {
			for(i=0;i<k;i++)
				if (temp->freq>psym[i]->freq) {
					int j;
					for(j=k-1;j>i;j--)
					psym[j]=psym[j-1];
					psym[i]=temp;
					break;
				}
        }
return makeTree(psym,k-1);
}

void makeCodes(sym *root) {
		if(root->left) {
			strcpy(root->left->code,root->code);
			strcat(root->left->code,"0");
			makeCodes(root->left);
		}
		if(root->right) {
			strcpy(root->right->code,root->code);
			strcat(root->right->code,"1");
			makeCodes(root->right);
        }
}


int main () {
        int k=26; //kolichestvo simvolov
	int i, j = 0;
        sym simbols[26]; //inizializaziia massiva zapisei
		char ch[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
		float freq[] = {7.96,1.6,2.84,4.01,12.86,2.62,1.99,5.39,7.77,0.16,0.41,3.51,2.43,7.51,6.62,1.81,0.17,6.83,6.62,9.72,2.48,1.15,1.8,0.17,1.52,0.05};
	for (i=0;i<k;i++){
		simbols[i].ch=ch[i];
		simbols[i].freq=freq[i];
		simbols[i].code[0] = '\0';
		simbols[i].left = simbols[i].right = 0;
	}
        sym *psym[256]; //inizializiryem massiv ykazatelei na zapisi
		sym **psum=(sym**)malloc(k*sizeof(sym*));
		for(i=0;i<k;i++) psym[i]=&simbols[i];
		sym temp;
		for(i=1;i<k;i++) {
			for(j=0;j<k-1;j++) {
				if(simbols[j].freq<simbols[j+1].freq) {
					temp=simbols[j];
					simbols[j]=simbols[j+1];
					simbols[j+1]=temp;
				}
			}
		}

for(i=0;i<k;i++) {
        printf("Ch= %c\tFreq= %f\t\n",simbols[i].ch,simbols[i].freq);
}
		sym *root=makeTree(psym,k);//visov fynkzii sozdaniia dereva
		makeCodes(root);//visov fynkzii polychenia koda
        for(i=0;i<k;i++){
            printf("%s ",simbols[i].code);
}
return 0;
}
