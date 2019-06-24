//#XUPAFEDERAL
/*#include <iostream>
#include <math.h>
#define SIZE 150
#define ld long double
using namespace std;

ld pot(ld x, int k);
ld mod(ld k);
ld f(string s, ld x);
int num(string s, int l, int r);
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

int num(string s, int l, int r){
	int a = 0, i;
	for (i=l; i<r; i++){
		a*=10;
		a+=s[i]-'0';
	}
	return a;
}

ld f(string s, ld x){
	ld sum = 0;
	int a[100], i, l, r, m, coef, exp, flag = 0;
	string aux;
	for (i=0; i<100; i++) a[i]=0;
	if (s[0]!='+' && s[0]!='-') {
		aux="+"+s;
		s=aux;
	}
	l=r=0;
	while(s[l]!='\0'){
		flag = 0;

		if (s[l+1]=='x') {
			coef = 1;
			m = l+1; //m indica a posição do x

		}
		else {
			for (i=l+1; i<=s.size(); i++){
				if (s[i]=='x'){
					coef = num(s, l+1, i); //função num retorna o numero contido entre a substring s[l+1, i]
					m = i;
					break;
				}
				if (s[i]=='\0' || s[i]=='+' || s[i]=='-'){
					if (s[l]=='+') a[0] += num(s, l+1, i);
					else a[0] -= num(s, l+1, i);
					flag = 1;
					r = i;
					l = r;
					break;
				}
			}
		}

		if (flag) continue;

		if (s[m+1]!='^') {
			exp = 1;
			r = m+1;
		}
		else {
			for (i=m+2; i<=s.size(); i++){
				if (s[i]=='+' || s[i]=='-' || s[i]=='\0'){
					exp = num(s, m+2, i);
					r = i;
					break;
				}
			}
		}
		if (s[l]=='+') a[exp] += coef;
		else a[exp] -= coef;
		l = r;
	}

	for (i=0; i<100; i++) sum += a[i]*pot(x, i);
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
	//se estiver vazio eh culpa do dikson.
}
*/
