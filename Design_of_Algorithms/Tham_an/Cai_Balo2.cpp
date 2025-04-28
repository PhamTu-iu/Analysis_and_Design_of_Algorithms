#include <stdio.h>
typedef struct{
	char Ten[25];
	float Trong_luong, Gia_tri, Don_gia;
	int PA, max;
}Do_vat;
void Read_Data(Do_vat ds_do_vat[], int *T, int *n){
	FILE *f=fopen("Caibalo2.txt", "r");
	if(f==NULL){
		printf("Khong the mo file\n");
		return;
	}
	int i=0;
	fscanf(f,"%d", T);
	while(!feof(f)){
		fscanf(f,"%f%f%d%[^\n]",&ds_do_vat[i].Trong_luong, &ds_do_vat[i].Gia_tri, &ds_do_vat[i].max, &ds_do_vat[i].Ten);
		ds_do_vat[i].Don_gia=ds_do_vat[i].Gia_tri/ds_do_vat[i].Trong_luong;
		ds_do_vat[i].PA=0;
		i++;
	}
	fclose(f);
	*n=i;
}
void Swap(Do_vat *x, Do_vat *y){
	Do_vat temp=*x;
	*x=*y;
	*y=temp;
}
void BubbleSort(Do_vat a[], int n){
	for(int i=0;i<=n-2;i++){
		for(int j=n-1;j>=i+1;j--){
			if(a[j].Don_gia>a[j-1].Don_gia)
			Swap(&a[j], &a[j-1]);
		}
	}
}
void Print_Data(Do_vat a[], int n, int t){
	float Tong_TL=0, Tong_GT=0;
	printf("|%3s|%8s|%8s|%5s|%8s|%20s|","STT","TrongLuong", "GiaTri","max","DonGia","Ten");
	if(t==1) printf("%8s|", "SoLuong");
	printf("\n");
	int i;
	for(i=0; i<n;i++){
			printf("|%3d|%10.f|%8.f|%5d|%8.2f|%-20s|",i+1,a[i].Trong_luong,a[i].Gia_tri,a[i].max,a[i].Don_gia,a[i].Ten);
			if(t==1){
				printf("%-8d|", a[i].PA);	
				Tong_TL+=a[i].Trong_luong*a[i].PA;
		        Tong_GT+=a[i].Gia_tri*a[i].PA;
			}
			printf("\n");
	}
	if(t==1){
		printf("Tong trong luong: %-8.f\n", Tong_TL);
	    printf("Tong gia tri: %-8.f\n", Tong_GT);
	}
}
void Greedy(Do_vat a[], int TL_Balo, int n){
	int i;
	for(i=0;i<n;i++){
		a[i].PA=TL_Balo/a[i].Trong_luong;
		if(a[i].PA>a[i].max) a[i].PA=a[i].max;
		TL_Balo-=a[i].PA*a[i].Trong_luong;
	}
}
int main(){
	Do_vat ds_do_vat[100];
	int TL_balo;
	int n;
	Read_Data(ds_do_vat, &TL_balo, &n);
	printf("%d\n", n);
	printf("Du lieu do vat da them\n");
	Print_Data(ds_do_vat, n, 0);
	printf("Du lieu do vat sau khi sap xep don gia\n");
	BubbleSort(ds_do_vat, n);
	Print_Data(ds_do_vat, n, 0);
	printf("Ket Qua\n");
	Greedy(ds_do_vat, TL_balo, n);
	Print_Data(ds_do_vat, n, 1);
	return 0;
}

