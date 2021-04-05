#include <graphics.h>
#include <math.h>
#include <time.h>
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
	int tam, demCanh=0, i=0;
	char str[100], *s;
	fseek(input,SEEK_CUR+1,SEEK_CUR);
	*dinh = (Dinh*)malloc(SoDinh * SoDinh * sizeof(Dinh));
	for(i=1; i <= SoDinh; i++)
	{
		(*dinh)[i].chiSoDinh = i;
		Dinh *temp = (*dinh+i);
		fgets(str, 1024, input);
		s = str;
		
		while(1)
		{
			if(*s  == '\n') break;
			Dinh *dinhMoi = taoDinh();
			temp->next = dinhMoi;
			temp = dinhMoi;
			(*dinhMoi).chiSoDinh = strtol(s, &s, 10);
			printf("%d ", (*dinhMoi).chiSoDinh);
			demCanh++;
		}
		printf("\n");
	}
	return demCanh;
} 

void veCanh(Dinh *dinh, int SoDinh, int x[], int y[])
{
	int m, n;
	setcolor(GREEN);       //mau cho duong ke noi
	for(int i =1; i <= SoDinh; i++)
	{
		Dinh *temp = (dinh+i); 
		while(temp->next != NULL)
		{
		temp = temp->next;
		m = (dinh+i)->chiSoDinh;
		n = temp->chiSoDinh;
		line(x[m], y[m], x[n], y[n]);

	}
}
}

void veDoThi(Dinh *dinh, int SoDinh, int xTT, int yTT, int x[], int y[])
{
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
} 

int main()
{
	int SoDinh, xTT, yTT, x[100], y[100];
	FILE *input = fopen("D:\\HocC\\DoAnLTTT\\input.txt", "r"); //lay file input o che do chi doc
	if (input == NULL) 
	{
		printf("Loi khong tim thay file!");
		return 0;
	}
	fscanf(input, "%d", &SoDinh); 
	printf("%d\n", SoDinh);
	Dinh *dinh;
	int soCanh = docDuLieuDauVao(&dinh, SoDinh, input)/2; 
	initwindow(1800,1000); 									//dat kich thuoc cho cua so
	xTT = 500, yTT = 500;
	veDoThi(dinh, SoDinh, xTT, yTT, x, y);
	veCanh(dinh, SoDinh, x,y);
	xTT = 1300;
	veDoThi(dinh, SoDinh, xTT, yTT, x, y);
	getch();
	closegraph();
	fclose(input);
	return 0;
}

