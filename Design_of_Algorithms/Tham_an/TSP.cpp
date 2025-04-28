#include <stdio.h>
typedef struct{
	int dau, cuoi;
	float do_dai;
}Canh;
void Read_Data(Canh a[], int *n){
	FILE *f=fopen("TSP.txt", "r");
	if(f==NULL){
		printf("Khong the mo file\n");
		return;
	}
	float temp;
	int k=0;
	fscanf(f,"%d", n);
	for(int i=0;i<=*n-1;i++){
		for(int j=i;j<=*n-1;j++){
			if(i==j) for(int t=0;t<=j;t++) fscanf(f,"%f", &temp);
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
void Print_DS(Canh a[], int n, int laPA){
	float Sum=0;
	int k=0;
	for(int i=0;i<n;i++){
		printf("%2d %c%c=%8.2f\n",k+1, a[i].dau+65, a[i].cuoi+65, a[i].do_dai);
		k++;
		if(laPA) Sum+=a[i].do_dai;
	}
	if(laPA) printf("Tong do dai quang duong: %8.2f\n", Sum);
}
void Swap(Canh *x, Canh *y){
	Canh temp=*x;
	*x=*y;
	*y=temp;
}
void BubbleSort(Canh a[], int n){
	for(int i=0;i<=n-2;i++){
		for(int j=n-1;j>=i+1;j--){
			if(a[j].do_dai<a[j-1].do_dai)
			   Swap(&a[j], &a[j-1]);
		}
	}
}
int chu_trinh(int r_dau, int r_cuoi){
	return r_dau==r_cuoi;
}
int DinhCap3(Canh PA[], int j, Canh moi){
	int i, dem;
	i=0;
	dem=1;
	while(i<j&&dem<3){
		if(moi.dau==PA[i].dau||moi.dau==PA[i].cuoi) dem++;
		i++;
	}
	if(dem==3) return 1;
	i=0;
	dem=1;
	while(i<j&&dem<3){
		if(moi.cuoi==PA[i].dau||moi.cuoi==PA[i].cuoi) dem++;
		i++;
	}
	if(dem==3) return 1;
	return 0;
}
void init_forest(int parent[], int n){
	for(int u=0;u<=n-1;u++){
		parent[u]=u;
	}
}
void update_forest(int parent[], int r1, int r2){
	parent[r2]=r1;
}
int find_root(int parent[], int u){
	while(u!=parent[u]){
		u=parent[u];
	}
	return u;
}
void Greedy(Canh a[], int n, Canh PA[]){
	int parent[n];
	init_forest(parent, n);
	int j=0, i;
	for(i=0;i<n*(n-1)/2 && j<n-1;i++){
		int r_dau=find_root(parent, a[i].dau);
		int r_cuoi=find_root(parent, a[i].cuoi);
		if(!DinhCap3(PA, j, a[i]) && !chu_trinh(r_dau, r_cuoi)){
			PA[j]=a[i];
			j++;
			update_forest(parent, r_dau, r_cuoi);
		}
	}
	
	for( ;i<n*(n-1)/2;i++){
		int r_dau=find_root(parent, a[i].dau);
		int r_cuoi=find_root(parent, a[i].cuoi);
		if(!DinhCap3(PA, j, a[i]) && chu_trinh(r_dau, r_cuoi)){
			PA[j]=a[i];
			break;
		}
	}
}
int main(){
	Canh a[100];
	int n;
	Read_Data(a, &n);
	printf("Danh sach cac canh:\n");
	Print_DS(a, n*(n-1)/2, 0);
	printf("Danh sach sau khi sap xep: \n");
	BubbleSort(a, n*(n-1)/2);
	Print_DS(a, n*(n-1)/2, 0);
	printf("Ket Qua:\n");
	Canh PA[n];
	Greedy(a, n, PA);
	Print_DS(PA, n, 1);
	return 0;
}

