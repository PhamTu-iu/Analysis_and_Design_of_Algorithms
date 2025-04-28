#include <stdio.h>
typedef struct{
    int TL, GT, SL, PA;
	char Ten[25];	
}DoVat;
typedef int Bang[30][100];
void Read_Data(DoVat a[], int *n, int *W){
	FILE *f=fopen("Caibalo.txt", "r");
	if(f==NULL) return;
	int i=0;
	fscanf(f,"%d", W);
	while(!feof(f)){
		fscanf(f,"%d%d%d%[^\n]",&a[i].TL, &a[i].GT, &a[i].SL, &a[i].Ten);
		a[i].PA=0;
		i++;
	}
	fclose(f);
	*n=i;
}
void Print_Data(DoVat a[], int n, int W){
	printf("|%3s|%5s|%5s|%3s|%25s|%3s|\n", "STT", "TL","GT","SL","Ten","PA");
	int TL=0;
	int GT=0;
	for(int i=0;i<n;i++){
		printf("|%3d|%5d|%5d|%3d|%25s|%3d|\n", i+1, a[i].TL,a[i].GT,a[i].SL,a[i].Ten,a[i].PA);
	    TL+=a[i].PA*a[i].TL;
	    GT+=a[i].PA*a[i].GT;
	}
	printf("Trong luong Balo: %d\n", W);
	printf("Tong trong luong: %d\n", TL);
	printf("Tong gia tri: %d\n", GT);
}

int min(int a,int b){
	if(a<b) return a;
	return b;
}
void TaoBang(DoVat a[], int n, int W, Bang X, Bang F){
	int V, x, y;
	int Xmax, Fmax;
	for(V=0;V<=W;V++){
		X[0][V]=min(a[0].SL, V/a[0].TL);
		F[0][V]=X[0][V]*a[0].GT;
	}
	for(int k=1;k<n;k++){
		for(V=0;V<=W;V++){
			Fmax=F[k-1][V];
			Xmax=0;
			y=min(a[k].SL, V/a[k].TL);
			for(x=1;x<=y;x++){
				if(Fmax<F[k-1][V-x*a[k].TL]+x*a[k].GT){
					Fmax=F[k-1][V-x*a[k].TL]+x*a[k].GT;
					Xmax=x;
				}
			}
			F[k][V]=Fmax;
			X[k][V]=Xmax;
		}
	}
}
InBang(Bang X, Bang F, int n, int W){
	for(int i=0;i<n;i++){
		for(int j=0;j<=W;j++){
			printf("|%2d %2d", X[i][j], F[i][j]);
		}
		printf("\n");
	}
}
void TraBang(DoVat a[], Bang X, int n, int W){
	int V=W;
	for(int i=n-1; i>=0;i--){
		a[i].PA=X[i][V];
		V=V-a[i].PA*a[i].TL;
	}
}
int main(){
	DoVat a[100];
	Bang X, F;
	int n, W;
	Read_Data(a, &n, &W);
	TaoBang(a, n, W, X, F);
	TraBang(a, X, n, W);
	InBang(X, F, n, W);
	Print_Data(a, n, W);
}
