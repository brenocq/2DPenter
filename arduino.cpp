//Dikson e Breno
#include <iostream>
#include <math.h>
#include <string>
#define SIZE 150
#define ld long double
using namespace std;

ld pot(ld x, int k);
ld mod(ld k);
ld f(string s, ld x);
void graph(bool** a, string s, ld prop);
void cross(bool** a);
void limpa(bool** a);
void imprime(bool** a);
bool** aloca(void);
void seta(bool** a);
void chama (bool** a);
void desenha(float x, float y);

int main(){
	bool** a;
	string s; 
	printf("Digite sua função.\nEla deve estar no formato de somas \"+ax^b\" (ou -\"-ax^b\"), onde a e b são naturais menores que 10.\nEx: \"+2x^2-5x^0\".\n");
	cin >> s;
	ld zoom;
	printf("Agora digite o valor do comprimento dos eixos.\n");
	cin >> zoom;
	zoom=(SIZE/2)/zoom;	
	a = aloca();
	seta (a);
	cross(a);
	graph(a, s, zoom);
	imprime(a);
	chama(a);
	limpa(a);
	return 0;
}

void chama (bool **a){
	int i, j;
	for (i=0; i<SIZE; i++) desenha((float)i, SIZE/2);
	for (i=0; i<SIZE; i++) desenha(SIZE/2, (float)i);
	for (j=0; j<SIZE; j++){
		for (i=0; i<SIZE; i++){
			if (a[i][j]==0 && i != SIZE/2 && j != SIZE/2) desenha((float)i, (float)j); 
		}
	}
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

void graph(bool** a, string s, ld prop){
	ld x;
	ld y;
	for (x=-(SIZE/2); x<SIZE/2; x++){
		y = prop*f(s, x/prop);
		if (mod(y)<SIZE/2) a[SIZE/2-(int)y][(int)x+SIZE/2]=0;
	}
	return;
}

void cross(bool** a){
	int i;
	for (i=0; i<SIZE; i++){
		a[SIZE/2][i]=0;
		a[i][SIZE/2]=0;
	}
}

void limpa(bool** a){
	int i;
	for (i=0; i<SIZE; i++) free(a[i]);
	free(a);
}

void imprime(bool** a){
	int i, j;
	for (i=0; i<SIZE; i++){
		for (j=0; j<SIZE; j++){
			if (a[i][j]==1) cout << " ";
			else cout << "#";
		}
		cout << endl;
	}
}

bool** aloca(void){
	int i; 
	bool** a;
	a = (bool**) malloc(SIZE*(sizeof(bool*)));
	for (i=0; i<SIZE; i++) a[i] = (bool*) malloc(SIZE*(sizeof(bool)));
	return a;
}

void seta(bool** a){
	int i, j;
	for (i=0; i<SIZE; i++) for (j=0; j<SIZE; j++) a[i][j]=1;
}

void desenha(float x, float y){
	//se estiver vazio eh culpa do breno.
}