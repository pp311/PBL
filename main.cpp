#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14

typedef struct Dinh{
	int chiSoDinh;
	Dinh *next;
}Dinh;
Dinh *taoDinh()
{
	Dinh *dinhMoi = (Dinh*)malloc(sizeof(Dinh));
	dinhMoi->next = NULL;
	return dinhMoi;
}
int docDuLieuDauVao(Dinh **dinh, int SoDinh, FILE *input)
{
	char str[100], *s;
	fseek(input, SEEK_CUR+1, SEEK_CUR);						//dua con tro ao trong file xuong dong
	*dinh = (Dinh*)malloc(SoDinh * SoDinh * sizeof(Dinh));
	printf("Danh sach ke: \n");
	for(int i=1; i <= SoDinh; i++)
	{
		(*dinh)[i].chiSoDinh = i;
		Dinh *temp = (*dinh+i);
		fgets(str, 1024, input);
		s = str;
		printf("%d -> ", i);
		while(1)
		{
			if(*s  == '\n') break;
			Dinh *dinhMoi = taoDinh();
			temp->next = dinhMoi;
			temp = dinhMoi;
			(*dinhMoi).chiSoDinh = strtol(s, &s, 10);
			printf("%d -> ", (*dinhMoi).chiSoDinh);
		}
		printf("NULL \n");
	}
} 
void veCanh(int x1, int y1, int x2, int y2)
{
	setcolor(WHITE);								//dat mau cho duong ke noi
	int r = 30;
	float doDaiCanh = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));			//tinh do dai duong ke noi
	float cosA = abs(x1 - x2) / doDaiCanh;						//tinh goc nghieng cua duong ke noi
	float sinA = abs(y1 - y2) / doDaiCanh;
	int xTo = (x1 > x2) ? x1 : x2, xNho = (x1 < x2) ? x1 : x2;
	int yTo = (y1 > y2) ? y1 : y2, yNho = (y1 < y2) ? y1 : y2;
	if(x1 == x2)									//duong ke noi cho chieu  | 
	{
		if(y1 == yTo) line(x1, y1 - r, x2, y2 + r);
		else line(x1, y1 + r, x2, y2 - r);
	}
	else if(y1 == y2)								//duong ke noi co chieu  -- 
	{
		if(x1 == xTo) line(x1 - r, y1, x2 + r, y2);
		else line(x1 + r, y1, x2 - r, y2);
	}
	else if((x1 < x2) && (y1 < y2) || (x1 > x2) && (y1 > y2))			//duong ke noi cho chieu \ . 
	{
		line(xTo - r*cosA, yTo - r*sinA, xNho + r*cosA, yNho + r*sinA);
	}
	else if((x1 < x2) && (y1 > y2) || (x1 > x2) && (y1 < y2))			// duong ke noi co chieu  / 
	{
		line(xNho + r*cosA, yTo - r*sinA, xTo - r*sinA, yNho + r*cosA);
	}
}
void veCanhBanDau(Dinh *dinh, int SoDinh, int x[], int y[])
{
	int m, n;   
	for(int i =1; i <= SoDinh; i++)
	{
		Dinh *temp = (dinh+i); 
		while(temp->next != NULL)
		{
		temp = temp->next;
		m = (dinh+i)->chiSoDinh;
		n = temp->chiSoDinh;
		veCanh(x[m], y[m], x[n], y[n]);
		}
	}
}
void veCanhKetQua(int DinhDau[], int DinhDuoi[], int soDinh, int x[], int y[])
{
	int n, m;
	for(int i=1; i < soDinh; i++)
	{
		m = DinhDau[i];
		n = DinhDuoi[i];
		veCanh(x[m], y[m], x[n], y[n]);
	}
}
void veDoThi(Dinh *dinh, int SoDinh, int xTT, int yTT, int x[], int y[])
{
	int r = 300, num=1;
	char str[10];
	setbkcolor(LIGHTGRAY);		//mau nen
	setfillstyle(SOLID_FILL, LIGHTGRAY);  //cach to nen va mau to (nen cung mau voi floodfill)
	for(int i = 1; i <= SoDinh; i++)
	{
		x[i] = xTT + r * cos((2*PI/SoDinh)*i);
		y[i] = yTT + r * sin((2*PI/SoDinh)*i);
		setcolor(LIGHTGRAY);							//mau vien vong tron
		circle(x[i], y[i], 30);  						// moi dinh la 1 vong tron co ban kinh 15
		floodfill(x[i], y[i], LIGHTGRAY);					//to mau vong tron
		setcolor(BLACK);							//mau chu
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 3); 				//chinh kieu chu
		sprintf(str, "%d", num);						//chuyen kieu int sang char
		outtextxy(x[i]-12, y[i]-12, str);					//ghi chu
		num++;
	} 
} 
void DFS(Dinh *dinh, int ChuaXet[], int i, int DinhDau[], int DinhDuoi[],int *dem)
{
	int n, k=0;
	ChuaXet[i] = 0;
	Dinh *temp = (dinh+i);
	while(temp->next != NULL)
	{
		temp = temp->next;
		n=temp->chiSoDinh;
		if(ChuaXet[n] == 1)
		{	
			k = ++*dem;
			DinhDau[k]=i;
			DinhDuoi[k]=n;
			DFS(dinh, ChuaXet, n, DinhDau, DinhDuoi, dem);
		}
	}
}
void inKetQua(int DinhDau[], int DinhDuoi[], int SoDinh)
{
	printf("\nCac canh cua cay khung: \n");
	for(int i = 1; i < SoDinh; i++)
	{
		printf("Canh thu %d: %d - %d\n", i, DinhDau[i], DinhDuoi[i]);
	}
}
int main()
{
	int SoDinh, xTT = 350, yTT = 350, dem=0;					//xTT va yTT: toa do tam do thi
	int x[100], y[100], ChuaXet[100], DinhDau[100], DinhDuoi[100];
	FILE *input = fopen("D:\\HocC\\DoAnLTTT\\input.txt", "r"); //lay file input o che do chi doc
	if (input == NULL) 
	{
		printf("Loi khong tim thay file!");
		return 0;
	}
	fscanf(input, "%d", &SoDinh); 
	printf("So dinh: %d\n", SoDinh);
	Dinh *dinh;
	docDuLieuDauVao(&dinh, SoDinh, input);
	for(int i = 1; i <= SoDinh; i++) ChuaXet[i] = 1;
 	DFS(dinh, ChuaXet, 1, DinhDau, DinhDuoi, &dem);	
	inKetQua(DinhDau, DinhDuoi, SoDinh);
	initwindow(1500,700); 									//dat kich thuoc cho cua so
	veDoThi(dinh, SoDinh, xTT, yTT, x, y);
	veCanhBanDau(dinh, SoDinh, x,y);
	xTT = 1100;										//di chuyen tam do thi de ve do thi thu 2
	veDoThi(dinh, SoDinh, xTT, yTT, x, y);
	veCanhKetQua(DinhDau, DinhDuoi, SoDinh, x, y);
	getch();
	closegraph();
	free(dinh);
	fclose(input);
	return 0;
}

