#include <stdio.h>
typedef int keytype;
typedef float othertype;
typedef struct{
	keytype key;
	othertype otherfields;
}recordtype;
void Read_Data(recordtype a[], int *n){
	int i=0;
	FILE *f=fopen("data.txt", "r");
	if(f!=NULL){
		while(!feof(f)){
			fscanf(f, "%d %f",&a[i].key, &a[i].otherfields);
			i++;
		}	
	}
	fclose(f);
	*n=i;
};
void Print_Data(recordtype a[], int n){
	for(int i=0;i<=n-1;i++){
		printf("%3d%5d%8.2f\n",i+1, a[i].key, a[i].otherfields);
	}
}
Swap(recordtype *x, recordtype *y){
	recordtype temp=*x;
	*x=*y;
	*y=temp;
}
void PushDown(recordtype a[], int first, int last){
	int r=first;
	while(r<=(last-1)/2){
		if(last==2*r+1){
			if(a[r].key<a[last].key) Swap(&a[r], &a[last]);
			r=last;
		}
		else if(a[r].key<a[2*r+1].key && a[2*r+1].key>=a[2*r+2].key){
			Swap(&a[r], &a[2*r+1]);
			r=2*r+1;
		}
		else if(a[r].key<a[2*r+2].key){
			Swap(&a[r], &a[2*r+2]);
			r=2*r+2;
		}
		else r=last;
	}
}
void HeapSort(recordtype a[], int n){
	for(int i=(n-2)/2;i>=0;i--){
		PushDown(a, i, n-1);
		
	}
	for(int i=n-1;i>=2;i--){
		Swap(&a[0], &a[i]);
		PushDown(a, 0, i-1);
	}
	Swap(&a[0], &a[1]);
}
int main(){
	recordtype a[100];
	int n;
	printf("Thuat Toan HeapSort\n\n");
	Read_Data(a, &n);
	printf("Du lieu truoc khi sap xep\n");
	Print_Data(a, n);
	printf("Du lieu sau khi sap xep\n");
	HeapSort(a, n);
	Print_Data(a, n);
	return 0;
}

