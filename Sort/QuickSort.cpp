#include <stdio.h>
typedef int keytype;
typedef float othertype;
typedef struct{
	keytype key;
	othertype otherfields;
}recordtype;
void Read_Data(recordtype a[], int *n){
	FILE *f=fopen("data.txt","r");
	if(f==NULL) return;
	int i=0;
	while(!feof(f)){
		fscanf(f,"%d%f",&a[i].key, &a[i].otherfields);
		i++;
	}
	fclose(f);
	*n=i;
}
void Print_Data(recordtype a[], int n){
	for(int i=0;i<n;i++){
		printf("%3d %5d %8.2f\n", i+1, a[i].key, a[i].otherfields);
	}
}
void Swap(recordtype *x, recordtype *y){
	recordtype temp=*x;
	*x=*y;
	*y=temp;
}
int FindPivot(recordtype a[], int i, int j){
	keytype firstkey=a[i].key;
	int k=i+1;
	while(k<=j && a[k].key==firstkey) k++;
	if(k>j) return -1;
	if(a[k].key>firstkey) return k;
	else return i;
}
int Partition(recordtype a[], int i, int j, int Pivot){
	int L=i;
	int R=j;
	while(L<=R){
		while(a[L].key<Pivot) L++;
		while(a[R].key>=Pivot) R--;
		if(L<R) Swap(&a[L], &a[R]);
	}
	return L;
}
void QuickSort(recordtype a[], int i, int j){
	keytype pivot;
	int pivotindex=FindPivot(a, i, j);
	if(pivotindex!=-1){
		pivot=a[pivotindex].key;
		int k=Partition(a,i, j, pivot);
		QuickSort(a, i, k-1);
		QuickSort(a, k, j);
	}
}
int main(){
	printf("Thuat toan sap xep QuickSort\n");
	recordtype a[100];
	int n;
	Read_Data(a, &n);
	printf("Du lieu truoc khi sap xep\n");
	Print_Data(a, n);
	printf("Du lieu sau khi sap xep\n");
	QuickSort(a, 0, n-1);
	Print_Data( a, n);
	
}
