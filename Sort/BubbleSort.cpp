#include <stdio.h>
typedef int keytype;
typedef float othertype;
typedef struct{
	keytype key;
	othertype otherfields;
}recordtype;
void Read_Data(recordtype a[], int *n){
	FILE *f=fopen("data.txt", "r");
	int i=0;
	if(f!=NULL){
		while(!feof(f)){
			fscanf(f,"%d%f",&a[i].key, &a[i].otherfields);
			i++;
		}
	}
	fclose(f);
	*n=i;
}
void Print_Data(recordtype a[], int n){
	for(int i=0;i<=n-1;i++){
		printf("%3d%5d%8.2f\n",i+1, a[i].key, a[i].otherfields);
	}
}
void Swap(recordtype *x, recordtype *y){
	recordtype temp = *x;
	*x=*y;
	*y=temp;
}
void BubbleSort(recordtype a[], int n){
	for(int i=0;i<=n-2;i++){
		for(int j=n-1;j>=i+1;j--){
			if(a[j].key<a[j-1].key){
				Swap(&a[j], &a[j-1]);
			}
		}
	}
}
int main(){
	recordtype a[100];
	int n;
	printf("Thuat toan BubbleSort\n\n");
	Read_Data(a,&n);
	printf("Du lieu truoc khi sap xep\n");
	Print_Data(a, n);
	BubbleSort(a, n);
	printf("Du lieu sau khi sap xep\n");
	Print_Data(a, n);
	return 0;
}

