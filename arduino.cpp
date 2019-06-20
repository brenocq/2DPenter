#include <iostream>
#include <math.h>
#include <string>
#define SIZE 50
#define ld long double
using namespace std;

ld pot(ld x, int k);
ld mod(ld k);
ld f(string s, ld x);
void graph(int** a, string s, ld prop);
void cross(int** a);
void limpa(int** a);
void imprime(int** a);
int** aloca(void);
void seta(int** a);

int main(){
	int** a;
	string s; 
	printf("Digite sua função.\nEla deve estar no formato de somas \"+ax^b\" (ou -\"-ax^b\"), onde a e b são naturais menores que 10.\nEx: \"+2x^2-5x^0\".\n");
	cin >> s;
	ld zoom;
	printf("Agora digite um zoom. um zoom de valor 1 indica que cada pixel vale 1. Um zoom de valor 10 indica que cada pixel vale 1/10, etc.\n");
	cin >> zoom;
	zoom*=SIZE/2;	
	a = aloca();
	seta(a);
	cross(a);
	graph(a, s, zoom);
	imprime(a);
	limpa(a);
	return 0;
}

ld mod(ld k){
	if (k<0) k*=-1;
	return k;
}

ld pot(ld x, int k){
	if (k==0) return 1;
	else return pot(x, k-1)*x;
}

ld f(string s, ld x){
	int l = 0;
	ld sum = 0, act;
	while (s[l]!='\0') {
		act = (ld)(s[l+1]-'0')*pot(x, s[l+4]-'0');
		if (s[l]=='+') sum+=act;
		else sum-=act;
		l+=5;
	}
	return sum;
}

void graph(int** a, string s, ld prop){
	ld x;
	ld y;
	for (x=-(SIZE/2); x<SIZE/2; x++){
		y = prop*f(s, x/prop);
		if (mod(y)<SIZE/2) a[SIZE/2-(int)y][(int)x+SIZE/2]=0;
	}
	return;
}

void cross(int** a){
	int  i;
	for (i=0; i<SIZE; i++){
		a[SIZE/2][i]=0;
		a[i][SIZE/2]=0;
	}
}

void limpa(int** a){
	int i;
	for (i=0; i<SIZE; i++) free(a[i]);
	free(a);
}

void imprime(int** a){
	int i, j;
	for (i=0; i<SIZE; i++){
		for (j=0; j<SIZE; j++){
			if (a[i][j]==2) cout << " ";
			else cout << "#";
		}
		cout << endl;
	}
}

int** aloca(void){
	int i; 
	int** a;
	a = (int**) malloc(SIZE*(sizeof(int*)));
	for (i=0; i<SIZE; i++) a[i] = (int*) malloc(SIZE*(sizeof(int)));
	return a;
}

void seta(int** a){
	int i, j;
	for (i=0; i<SIZE; i++) for (j=0; j<SIZE; j++) a[i][j]=2;
}