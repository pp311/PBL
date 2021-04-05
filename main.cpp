#include <graphics.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14

using namespace std;
typedef struct {
	int Dau;
	int Duoi;
	int TrongSo;
}CauTrucCanh;

void docDuLieuDauVao(CauTrucCanh **canh, int SoCanh, FILE *input)
{
	*canh = (CauTrucCanh*)malloc(SoCanh * sizeof(CauTrucCanh));
	for(int i = 0; i < SoCanh; i++)
	{
		fscanf(input, "%d %d %d", &(*canh)[i].Dau, &(*canh)[i].Duoi, &(*canh)[i].TrongSo);
		printf("\n%d %d %d", (*canh)[i].Dau, (*canh)[i].Duoi, (*canh)[i].TrongSo);
	}
} 

void veCanh(CauTrucCanh *canh, int SoCanh, int x[], int y[])
{
	char str[2];
	int num;
	//setcolor(GREEN);       //mau cho duong ke noi
	for(int i=0; i<SoCanh;i++)
	{
		line(x[canh[i].Dau], y[canh[i].Dau], x[canh[i].Duoi], y[canh[i].Duoi]);
		setbkcolor(BLACK);
		num = canh[i].TrongSo;
		sprintf(str, "%d", num);   
		outtextxy((x[canh[i].Dau] + x[canh[i].Duoi]) / 2 -15, (y[canh[i].Dau] + y[canh[i].Duoi]) / 2 -15, str);
	}
}

void veDoThi(CauTrucCanh *canh, int SoDinh, int SoCanh, int xTT, int yTT)
{
	
	int x[100], y[100];
	int r = 300, num=1;
	char str[2];
	setbkcolor(LIGHTGRAY);		//mau nen
	setfillstyle(SOLID_FILL, LIGHTGRAY);  //cach to nen va mau to (nen cung mau voi floodfill)
	for(int i = 1; i <= SoDinh; i++)
	{
		x[i] = xTT + r * cos((2*PI/SoDinh)*i);
		y[i] = yTT + r * sin((2*PI/SoDinh)*i);
		setcolor(LIGHTGRAY);								//mau vien vong tron
		circle(x[i], y[i], 30);  							// moi dinh la 1 vong tron co ban kinh 15
		floodfill(x[i], y[i], LIGHTGRAY);					//to mau vong tron
		setcolor(GREEN);									//mau chu
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 3); 			//chinh kieu chu
		sprintf(str, "%d", num);							//chuyen kieu int sang char
		outtextxy(x[i]-15, y[i]-15, str);					//ghi chu
		num++;
	} 
	veCanh(canh,SoCanh,x,y);
} 

int main()
{
	int SoDinh, SoCanh, xTT, yTT;
	FILE *input = fopen("D:\\HocC\\DoAnLTTT\\input.txt", "r"); //lay file input o che do chi doc
	if (input == NULL) 
	{
		printf("Loi khong tim thay file!");
		return 0;
	}
	fscanf(input, "%d %d", &SoDinh, &SoCanh); 
	printf("%d %d", SoDinh, SoCanh);
	CauTrucCanh *canh;
	docDuLieuDauVao(&canh, SoCanh, input);
	initwindow(1800,1000); //dat kich thuoc cho cua so
	//int gd = DETECT, gm;
   	//initgraph(&gd, &gm, "");
	xTT = 500, yTT = 500;
	veDoThi(canh, SoDinh, SoCanh, xTT, yTT);
	xTT = 1300;
	//veDoThi(canh, SoDinh, SoCanh, xTT, yTT);
	getch();
	closegraph();
	fclose(input);
	return 0;
}


