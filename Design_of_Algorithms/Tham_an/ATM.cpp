#include <stdio.h>
typedef struct{
	char Ten[20];
	int MG;
	int PA;
}Tien;
void Read_Data(Tien a[], int *n){
    int i=0;
	FILE *f=fopen("ATM.txt", "r");
	if(f==NULL){
		return;
	}	
	while(!feof(f)){
		fscanf(f,"%d%[^\n]", &a[i].MG, &a[i].Ten);
		a[i].PA=0;
		i++;
	}
	fclose(f);
	*n=i;
}
void Print_Data(Tien a[], int n){
	int TienTra=0;
	printf("|%3s|%8s|%20s|%3s|\n", "STT", "MG", "TenTien", "SL");
	for(int i=0;i<n;i++){
		if(a[i].PA>0){
			TienTra+=a[i].MG*a[i].PA;
	        printf("|%3d|%8d|%20s|%3d|\n", i+1, a[i].MG, a[i].Ten, a[i].PA);
		}
		
	}
	printf("So tien da tra: %d\n", TienTra);
}
void Swap(Tien *x, Tien *y){
	Tien temp=*x;
	*x=*y;
	*y=temp;
}
void Sort(Tien a[], int n){
	for(int i=0;i<=n-2;i++){
		for(int j=n-1;j>=i+1;j--){
			if(a[j].MG>a[j-1].MG)
			   Swap(&a[j], &a[j-1]);
		}
	}
}
void Greedy(Tien a[], int n, int TienRut){
	Sort(a, n);
	for(int i=0;i<n;i++){
		a[i].PA=TienRut/a[i].MG;
		TienRut=TienRut-a[i].PA*a[i].MG;
	}
}
int main(){
	Tien a[100];
	int n, TienRut;
	printf("Bai toan rut tien ATM\n");
	Read_Data(a, &n);
	printf("Nhap vao so tien can rut: ");
	scanf("%d", &TienRut);
	printf("Danh sach tien sau khi\n");
	Greedy(a, n, TienRut);
	Print_Data(a, n);
}
