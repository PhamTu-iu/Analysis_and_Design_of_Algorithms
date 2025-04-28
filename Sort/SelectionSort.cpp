#include <stdio.h>
typedef float othertype;
typedef int keytype;
typedef struct{
	keytype key;
	othertype otherfields;
}recordtype;
void Read_Data(recordtype a[], int *n){
	FILE *f=fopen("data.txt", "r");
	if(f==NULL ) return;
	int i=0;
	while(!feof(f)){
		fscanf(f,"%d%f", &a[i].key, &a[i].otherfields);
		i++;
	}
	fclose(f);
	*n=i;
}
void Print_Data(recordtype a[], int n){
	for(int i=0;i<n;i++){
		printf("|%3d%|%5d|%8.2f|\n", i+1, a[i].key, a[i].otherfields);
	}
}
void Swap(recordtype *x, recordtype *y){
	recordtype temp=*x;
	*x=*y;
	*y=temp;
}
void SelectionSort(recordtype a[], int n){
	keytype lowkey;
	int lowindex;
	for(int i=0;i<=n-2;i++){
		lowkey=a[i].key;
		lowindex=i;
		for(int j=i+1;j<=n-1;j++){
			if(a[j].key<lowkey){
				lowkey=a[j].key;
				lowindex=j;
			}
		}
		Swap(&a[i], &a[lowindex]);
	}
}
int main(){
	printf("Thuat toan SelectionSort\n");
	recordtype a[100];
	int n;
	Read_Data(a, &n);
	printf("Du lieu truoc khi sap xep\n");
	Print_Data(a, n);
	printf("Du lieu sau khi sap xep\n");
	SelectionSort(a, n);
	Print_Data(a, n);
	
}
