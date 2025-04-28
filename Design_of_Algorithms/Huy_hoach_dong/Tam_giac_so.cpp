#include <stdio.h>
void Read_Data(int a[][30], int *n){
	FILE *f=fopen("tamgiac.txt", "r");
	if(f==NULL) return;
	int i=0;
	while(!feof(f)){
		for(int j=0;j<=i;j++){
			fscanf(f, "%d", &a[i][j]);
		}
		i++;
	}
	fclose(f);
	*n=i;
}
int CSmax(int F[][30], int i, int j){
	if(j==0) return (F[i-1][0]>F[i-1][1])? 0:1;
	if(i==j) return j-1;
	if(j==i-1) return (F[i-1][j-1]>F[i-1][j])? j-1:j;
	if(F[i-1][j-1]>F[i-1][j] && F[i-1][j-1]>F[i-1][j+1]) return j-1;
	if(F[i-1][j]>F[i-1][j-1] && F[i-1][j]>F[i-1][j+1]) return j;
	if(F[i-1][j+1]>F[i-1][j] && F[i-1][j+1]>F[i-1][j-1]) return j+1;
}
void TaoBang(int a[][30], int n, int F[][30]){
	F[0][0]=a[0][0];
	F[1][0]=a[1][0]+F[0][0];
	F[1][1]=a[1][1]+F[0][0];
	for(int i=2;i<n;i++){
		for(int j=0;j<n;j++){
			int CS=CSmax(F, i, j);
			F[i][j]=F[i-1][CS]+a[i][j];
		}
	}
}
int CSmaxDongCuoi(int F[][30], int n){
    int index=-1;
    int max=-1;
    for(int i=0;i<=n-1;i++){
    	if(max<F[n-1][i]){
    		max=F[n-1][i];
    		index=i;
		}
	}
	return index;
}
void TraBang(int a[][30], int n, int x[], int F[][30]){
	int j=CSmaxDongCuoi(F, n);
	x[n-1]=a[n-1][j];
	for(int i=n-1;i>=1;i--){
		j=CSmax(F, i, j);
		x[i-1]=a[i-1][j];
	}
}
void InBang(int a[][30], int n, int F[][30]){
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			printf("|%2d %2d", a[i][j], F[i][j]);
		}
		printf("\n");
	}
}
void PrintPA(int PA[], int n){
	int sum=0;
	for(int i=0;i<n;i++){
		printf("%d ", PA[i]);
		sum+=PA[i];
	}
	printf("\ntong duong di: %d", sum);
}
int main(){
	int a[30][30], F[30][30];
	int n;
	Read_Data(a, &n);
	int PA[n];
	TaoBang(a, n, F);
	InBang(a,  n, F);
	TraBang(a, n, PA, F);
	PrintPA(PA, n);
	return 0;
}

