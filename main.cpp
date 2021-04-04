#include <graphics.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14

typedef struct {
	int Dau;
	int Duoi;
	int TrongSo;
}CauTrucCanh;
//void DocDuLieuDauVao()
int main()
{
	int SoDinh, SoCanh;
	int Dinh[100], Canh[100];
	FILE *input = fopen("D:\\HocC\\DoAnLTTT\\input.txt", "r");
	if (input == NULL) {
		printf("Loi khong tim thay file! ");
		return 0;
	}
	fscanf(input, "%d %d", &SoDinh, &SoCanh);
	printf("%d %d", SoDinh, SoCanh);
	CauTrucCanh *canh = (CauTrucCanh*)malloc(SoCanh * sizeof(CauTrucCanh));
	for(int i=0; i< SoCanh; i++)
	{
		fscanf(input, "%d %d %d", (canh+i)->Dau, (canh+i)->Duoi, (canh+i)->TrongSo);
		printf("%d %d %d", (canh+i)->Dau, (canh+i)->Duoi, (canh+i)->TrongSo);
	}
	fclose(input);
	return 0;
	
}
