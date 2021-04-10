#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.14

typedef struct Dinh{
	int ChiSoDinh;
	Dinh *next;
}Dinh;
Dinh *taoDinh();
void docDuLieuDauVao(Dinh **dinh, int *SoDinh, FILE *input);
void inKetQua(int DinhDau[], int DinhDuoi[], int SoDinh);
void DFS(Dinh *dinh, int ChuaXet[], int i, int DinhDau[], int DinhDuoi[],int *dem);
void veCanhBanDau(Dinh *dinh, int SoDinh, int x[], int y[]);
void veCanhKetQua(int DinhDau[], int DinhDuoi[], int SoDinh, int x[], int y[]);
void veDoThi(Dinh *dinh, int SoDinh, int xTT, int yTT, int x[], int y[]);
void veCanh(int x1, int y1, int x2, int y2);

Dinh *taoDinh()
{
	Dinh *dinhMoi = (Dinh*)malloc(sizeof(Dinh));
	dinhMoi->next = NULL;
	return dinhMoi;
}
void docDuLieuDauVao(Dinh **dinh, int *SoDinh, FILE *input)
{
	char str[100], *s;
fscanf(input, "%d", &(*SoDinh)); 
	printf("So dinh: %d\n", *SoDinh);
	fseek(input, SEEK_CUR+1, SEEK_CUR);	//cho con tro ao trong file xuong dong
	*dinh = (Dinh*)malloc(pow(*SoDinh, 2) * sizeof(Dinh));
	printf("Danh sach ke: \n");
	for(int i=1; i <= *SoDinh; i++)
	{
		(*dinh+i)->ChiSoDinh = i; 		//tao con tro temp de giu (*dinh+i) la con
		Dinh *temp = (*dinh+i);		//tro chi toi dau moi danh sach dinh ke i
		fgets(str, 1024, input);			//doc 1 dong trong file input, luu vao str
		s = str;
		printf("%d -> ", i);
		while(*s != '\n')
		{
			Dinh *dinhMoi = taoDinh();
			temp->next = dinhMoi;
			temp = dinhMoi;
			dinhMoi->ChiSoDinh = strtol(s, &s, 10);
			printf("%d -> ", dinhMoi->ChiSoDinh);
		}
		printf("NULL \n");
	}
} 
void veCanh(int x1, int y1, int x2, int y2)
{
	setcolor(WHITE);					//mau duong ke noi		
	int r = 30;
	float DoDaiCanh = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));			
	float cosA = abs(x1 - x2) / DoDaiCanh;						
	float sinA = abs(y1 - y2) / DoDaiCanh;
	int xTo = (x1 > x2) ? x1 : x2, xNho = (x1 < x2) ? x1 : x2;
	int yTo = (y1 > y2) ? y1 : y2, yNho = (y1 < y2) ? y1 : y2;
	if(x1 == x2)							//duong noi co chieu |	
	{
		if(y1 == yTo) line(x1, y1 - r, x2, y2 + r);
		else line(x1, y1 + r, x2, y2 - r);
	}
	else if(y1 == y2)						//duong noi co chieu -- 
	{
		if(x1 == xTo) line(x1 - r, y1, x2 + r, y2);
		else line(x1 + r, y1, x2 - r, y2);
	}
	else if((x1 < x2) && (y1 < y2) || (x1 > x2) && (y1 > y2))	//duong noi co chieu \ 	.
		line(xTo - r * cosA, yTo - r * sinA, xNho + r * cosA, yNho + r * sinA);
	else if((x1 < x2) && (y1 > y2) || (x1 > x2) && (y1 < y2))	//duong noi co chieu /	
		line(xNho + r * cosA, yTo - r * sinA, xTo - r * cosA, yNho + r * sinA);
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
		m = (dinh+i)->ChiSoDinh;
		n = temp->ChiSoDinh;
		veCanh(x[m], y[m], x[n], y[n]);
		}
	}
}
void veCanhKetQua(int DinhDau[], int DinhDuoi[], int SoDinh, int x[], int y[])
{
	int m, n;
	for(int i=1; i < SoDinh; i++)
	{
		m = DinhDau[i];
		n = DinhDuoi[i];
		veCanh(x[m], y[m], x[n], y[n]);
	}
}
void veDoThi(Dinh *dinh, int SoDinh, int xTT, int yTT, int x[], int y[])
{
	int r = 300, num = 1;					//ban kinh do thi, chi so dinh
	char str[10];
	setbkcolor(LIGHTGRAY);				//mau nen
	setfillstyle(SOLID_FILL, LIGHTGRAY);  		//cach to nen va mau to 
	for(int i = 1; i <= SoDinh; i++)
	{
		x[i] = xTT + r * cos((2*PI/SoDinh)*i);
		y[i] = yTT + r * sin((2*PI/SoDinh)*i);
		setcolor(LIGHTGRAY);				//mau vien vong tron	
		circle(x[i], y[i], 30);  						
		floodfill(x[i], y[i], LIGHTGRAY);			//to mau vong tron	
		setcolor(BLACK);					//mau chu	
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 3); 	//chinh kieu chu	
		sprintf(str, "%d", num);				//chuyen int -> char	
		outtextxy(x[i]-12, y[i]-12, str);			//ghi chi so dinh	
		num++;
	} 
} 
void DFS(Dinh *dinh, int ChuaXet[], int i, int DinhDau[], int DinhDuoi[],int *dem)
{
	int j, k=0;
	ChuaXet[i] = 0;
	Dinh *temp = (dinh+i);
	while(temp->next != NULL)
	{
		temp = temp->next;
		j = temp->ChiSoDinh;
		if(ChuaXet[j] == 1)
		{	
			k = ++*dem;
			DinhDau[k]=i;
			DinhDuoi[k]=j;
			DFS(dinh, ChuaXet, j, DinhDau, DinhDuoi, dem);
		}
	}
}
void inKetQua(int DinhDau[], int DinhDuoi[], int SoDinh)
{
	printf("\nCac canh cua cay khung: \n");
	for(int i = 1; i < SoDinh; i++)
		printf("Canh thu %d: %d - %d\n", i, DinhDau[i], DinhDuoi[i]);
}
int main()
{
	int SoDinh, xTT = 350, yTT = 350, dem=0;		//xTT, yTT: toa do trung tam do thi
	int x[100], y[100], ChuaXet[100], DinhDau[100], DinhDuoi[100];
	FILE *input = fopen("D:\\HocC\\DoAnLTTT\\input.txt", "r");  
	if (input == NULL) 
	{
		printf("Loi khong tim thay file!");
		return 0;
	}
	Dinh *dinh;
	docDuLieuDauVao(&dinh, &SoDinh, input);
	for(int i = 1; i <= SoDinh; i++) ChuaXet[i] = 1;
 	DFS(dinh, ChuaXet, 1, DinhDau, DinhDuoi, &dem);	
	inKetQua(DinhDau, DinhDuoi, SoDinh);
	initwindow(1500,700); 			//Thiet lap kich thuoc cua so do hoa
	veDoThi(dinh, SoDinh, xTT, yTT, x, y);
	veCanhBanDau(dinh, SoDinh, x,y);
	xTT = 1100;					//Di chuyen xTT de ve do thi moi
	veDoThi(dinh, SoDinh, xTT, yTT, x, y);
	veCanhKetQua(DinhDau, DinhDuoi, SoDinh, x, y);
	getch();
	closegraph();
	free(dinh);
	fclose(input);
	return 0;
}
