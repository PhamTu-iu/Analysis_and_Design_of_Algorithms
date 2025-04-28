#include <stdio.h>
typedef struct{
	int dau, cuoi, da_dung;
	float do_dai;
}Canh;
void Read_Data(Canh a[][30], int *n){
	FILE *f=fopen("TSP.txt","r");
	if(f==NULL){
		return;
	}
	float temp;
	fscanf(f, "%d", n);
	for(int i=0;i<*n;i++){
		for(int j=0;j<*n;j++){
			fscanf(f,"%f", &a[i][j].do_dai);
			a[i][j].dau=i;
			a[i][j].cuoi=j;
			a[i][j].da_dung=0;
		}
	}
	fclose(f);
}
void PrintPA(Canh PA[], int n){
	float sum=0;
	for(int i=0;i<n;i++){
		printf("%c ->", PA[i].dau+97);
		sum+=PA[i].do_dai;
	}
	printf("%c\n", PA[n-1].cuoi+97);
	
	printf("tong do dai: %5.2f", sum);
}
int ChuTrinh(Canh x[], int k, int ketiep){
	for(int i=0;i<k;i++){
		if(ketiep==x[i].dau) return 1;
	}
	return 0;
}
float CanhNN(Canh a[][30], int n){
	float Cmin=9999;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(j!=i && !a[i][j].da_dung && Cmin>a[i][j].do_dai){
				Cmin=a[i][j].do_dai;
			}
		}
	}
	return Cmin;
}
float CanDuoi(Canh a[][30], float *TGT, int n, int i){
	return *TGT+(n-i)*CanhNN(a, n);
}
void CapNhatGNNTT(Canh a[][30], int n, float TGT, float *GNNTT, Canh x[], Canh PA[]){
	x[n-1]=a[x[n-2].cuoi][x[0].dau];
	TGT+=x[n-1].do_dai;
	if(TGT<*GNNTT){
		*GNNTT=TGT;
		for(int i=0;i<n;i++){
			PA[i]=x[i];
		}
	}
}
void NhanhCan(Canh a[][30], int i, int n, int dau, float *TGT, float *CD, float *GNNTT,  Canh x[], Canh PA[]){
	int j;
	for(j=0;j<n;j++){
		if(j!=dau && !a[dau][j].da_dung && !ChuTrinh(x, i, j)){
			*TGT=*TGT+a[dau][j].do_dai;
			*CD=CanDuoi(a, TGT, n, i+1);
			if(*CD<*GNNTT){
				x[i]=a[dau][j];
				a[dau][j].da_dung=a[j][dau].da_dung=1;
				if(i==n-2){
					CapNhatGNNTT(a, n, *TGT, GNNTT, x, PA);
				}
				else NhanhCan(a, i+1, n, j, TGT, CD, GNNTT, x, PA);
			}
			*TGT=*TGT-a[dau][j].do_dai;
			a[dau][j].da_dung=a[j][dau].da_dung=0;
		}
	}
}
void InMaTran(Canh a[][30], int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("%5.2f ", a[i][j].do_dai);
		}
		printf("\n");
	}
}
void reset(Canh a[][30], int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			a[i][j].da_dung=0;
		}
	}
}
int main(){
	Canh a[30][30];
	int n;
	Read_Data(a, &n);
	Canh x[n], PA[n];
	char yn, tpxp;
	InMaTran(a, n);
	while(1){
		fflush(stdin);
		printf("Nhap vao thanh pho xuat phat. Co the nhap tu a den %c: ", n-1+97);
		float TGT=0, CD=0, GNNTT=9999;
		scanf("%c", &tpxp);
		NhanhCan(a, 0, n, tpxp-97, &TGT, &CD, &GNNTT, x, PA);
		PrintPA(PA, n);
		printf("\nTiep tuc? Y/N: ");
		fflush(stdin);
		scanf("%c", &yn);
		if(yn=='N'||yn=='n') break;
		reset(a, n);
	}
}
