#include <stdio.h>
typedef struct{
	float TL, GT, DG;
	char Ten[25];
	int SL, PA;
}DoVat;
void Read_Data(DoVat a[], int *n, float *W){
	FILE *f=fopen("Caibalo.txt","r");
	if(f==NULL) return;
	int i=0;
	fscanf(f,"%f", W);
	while(!feof(f)){
		fscanf(f, "%f%f%d%[^\n]", &a[i].TL, &a[i].GT, &a[i].SL, &a[i].Ten);
		a[i].PA=0;
		a[i].DG=a[i].GT/a[i].TL;
		i++;
	}
	fclose(f);
	*n=i;
}
void Print_Data(DoVat a[], int n, float W){
	float TL=0, GT=0;
	printf("|%3s|%5s|%5s|%3s|%25s|%5s|%3s|\n","STT","TL", "GT", "SL", "Ten", "DG", "PA");
	for(int i=0;i<n;i++){
		printf("|%3d|%5.2f|%5.2f|%3d|%25s|%5.2f|%3d|\n",i+1,a[i].TL, a[i].GT, a[i].SL, a[i].Ten, a[i].DG, a[i].PA);
	     TL+=a[i].PA*a[i].TL;
	     GT+=a[i].PA*a[i].GT;
	}
	printf("Trong luong Balo: %5.2f\n", W);
	printf("Trong luong: %5.2f\n", TL);
	printf("Gia tri: %5.2f\n", GT);
}
void Sort(DoVat a[], int n){
	for(int i=0;i<n-2;i++){
		for(int j=n-1;j>=i+1;j--){
			if(a[j].DG>a[j-1].DG){
				DoVat temp=a[j];
				a[j]=a[j-1];
				a[j-1]=temp;
			}
		}
	}
}
void TaoNutGoc(DoVat a[], float W, float *V, float *TGT, float *CT, float *GLNTT, float DGmax){
	*TGT=0;
	*V=W;
	*CT=*V*DGmax;
	*GLNTT=0;
}
int min(int a, int b){
	if(a<b) return a;
	else return b;
}
void CapNhatGLNTT(DoVat a[], int n, float *TGT, float *GLNTT, int x[]){
	if(*TGT>*GLNTT){
		*GLNTT=*TGT;
		for(int i=0;i<n;i++){
			a[i].PA=x[i];
		}
	}
}
void NhanhCan(DoVat a[], int i, int n, float *V, float *TGT, float *CT, float *GLNTT, int x[]){
	int so_luong=min(a[i].SL, *V/a[i].TL);
	int j;
	for(j=so_luong;j>=0;j--){
		*TGT=*TGT+j*a[i].GT;
		*V=*V-j*a[i].TL;
		*CT=*TGT+*V*a[i+1].DG;
		if(*CT>*GLNTT){
			x[i]=j; //printf("%d---", j);
			if((i==n-1)||(*V==0)){
				CapNhatGLNTT(a, n, TGT, GLNTT, x);
			}
			else NhanhCan(a, i+1, n, V, TGT, CT, GLNTT, x);
		}
		*TGT=*TGT-j*a[i].GT;
		*V=*V+j*a[i].TL;
	}
}
int main(){
	DoVat a[100];
	int n;
	float W;
	Read_Data(a, &n, &W);
	float TGT, CT, GLNTT, V;
	int x[n], PA[n];
	Sort(a, n);
	TaoNutGoc(a, W, &V, &TGT, &CT, &GLNTT, a[0].DG);
	NhanhCan(a, 0, n, &V, &TGT, &CT, &GLNTT, x);
	Print_Data(a, n, W);
}
