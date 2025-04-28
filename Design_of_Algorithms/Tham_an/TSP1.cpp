#include <stdio.h>
typedef struct{
	int dau, cuoi;
	float do_dai;
}Canh;
void Read_Data(Canh a[], int *n){
	FILE *f=fopen("TSP.txt", "r");
	if(f==NULL) return;
	fscanf(f,"%d", n);
	float temp;
	int k=0;
	for(int i=0;i<*n;i++){
		for(int j=i;j<*n;j++){
			if(j==i) for(int t=0;t<=j;t++) fscanf(f,"%f", &temp);
			else{
				fscanf(f,"%f",&a[k].do_dai);
				a[k].dau=i;
				a[k].cuoi=j;
				k++;
			}
		}
	}
	fclose(f);
}
void Print_Data(Canh PA[], int n){
	float sum=0;
	for(int i=0;i<n;i++){
		printf("Canh %c%c = %5.2f\n", PA[i].dau+97, PA[i].cuoi+97, PA[i].do_dai);
		sum+=PA[i].do_dai;
	}
	printf("Tong chieu dai: %.2f\n", sum);
}
void Sort(Canh a[], int n){
	for(int i=0;i<n-2;i++){
		for(int j=n-1;j>=i+1;j--){
			if(a[j].do_dai<a[j-1].do_dai){
				Canh temp=a[j];
				a[j]=a[j-1];
				a[j-1]=temp;
			}
		}
	}
}
void InitRoot(int parent[], int n){
	for(int i=0;i<n;i++){
		parent[i]=i;
	}
}
void UpdateRoot(int parent[], int u,int v){
	parent[v]=u;
}
int  FindRoot(int parent[], int u){
	while(u!=parent[u]){
		u=parent[u];
	}
	return u;
}
int DinhCap3(Canh PA[], int j, Canh moi){
	int dem=0;
	int i=0;
	while(i<j && dem<2){
		if(moi.dau==PA[i].dau||moi.dau==PA[i].cuoi) dem++;
		i++;
	}
	if(dem==2) return 1;
	i=0;
	dem=0;
	while(i<j && dem<2){
		if(moi.cuoi==PA[i].dau||moi.cuoi==PA[i].cuoi) dem++;
		i++;
	}
	return (dem==2);
}
void ThamAn(Canh a[], int n, Canh PA[]){
	int parent[n];
	InitRoot(parent, n);
	int i, j=0;
	for(i=0;i<n*(n-1)/2 && j<n-1;i++){
		int Rootu=FindRoot(parent, a[i].dau);
		int Rootv=FindRoot(parent, a[i].cuoi);
		if(!DinhCap3(PA, j, a[i]) && !(Rootu==Rootv)){
			PA[j]=a[i];
			j++;
			UpdateRoot(parent, Rootu, Rootv);
		}
	}
	for( ;i<n*(n-1)/2;i++){
		int Rootu=FindRoot(parent, a[i].dau);
		int Rootv=FindRoot(parent, a[i].cuoi);
		if(!DinhCap3(PA, j, a[i]) && (Rootu==Rootv)){
			PA[j]=a[i];
			break;
		}
	}
}
int main(){
	Canh a[100];
	int n;
	Read_Data(a, &n);
	printf("%d\n", n);
	Sort(a,n*(n-1)/2);
	Print_Data(a, n*(n-1)/2);
	Canh PA[n];
	ThamAn(a, n, PA);
	Print_Data(PA, n);
}
