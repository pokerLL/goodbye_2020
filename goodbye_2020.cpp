#include "goodbye_2020.h"

IMAGE bkimg;

int main()
{

	//initgraph(WND_WIDTH, WND_HEIGHT, EW_NOMINIMIZE | EW_NOCLOSE);
	initgraph(WND_WIDTH, WND_HEIGHT, EW_NOMINIMIZE);
	setbkmode(TRANSPARENT);
	srand((unsigned int)time(NULL));


	_getch();


	mciSendString(L"open ./res/bk.mp3 alias bgm", 0, 0, 0);
	mciSendString(L"play bgm repeat", 0, 0, 0);
	loadimage(&bkimg, L"./res/bk.jpg", 1200, 600);

	showBkImg();

	DWORD t1 = timeGetTime();
	DWORD* pMem = GetImageBuffer();

	saySomething();

	for (int i = 0; i < NUM; i++)	init(i);

	loadimages();

	while (1)
	{
		for (int i = 0; i < 990; i++)
			for (int j = 0; j < 3; j++)
			{
				int px1 = rand() % 1200;
				int py1 = rand() % 600;
				if (py1 < 790)	pMem[py1 * 1200 + px1] = pMem[py1 * 1200 + px1 + 1] = BLACK;
			}
		choice(t1);
		shoot();
		Show(pMem);
	}
	return 0;
}


void showBkImg() {
	cleardevice();
	putimage(0, 0, &bkimg);
}


void saySomething()
{
	settextcolor(YELLOW);
	showBkImg();
	for (int i = 0; i < 50; i++)
	{
		//圆心（500,300） 半径150  60个均匀点的x,y
		int x = 600 + int(150 * sin(PI * 2 * i / 60));
		int y = 300 + int(150 * cos(PI * 2 * i / 60));
		showBkImg();
		settextstyle(i, 0, L"微软雅黑");
		outtextxy(x - 100, y - 150, L"2020"); 
		outtextxy(x, y - 100, L"good bye");
		Sleep(20);
	}

	Sleep(2000);
	showBkImg();
	settextstyle(35, 0, L"华文中宋", 0, 0, 500, false, false, false);
	outtextxy(200, 250, L"希望新的一年里");
	outtextxy(200, 300, L"能瘦下来，");
	outtextxy(200, 350, L"算法不再那么菜");
	outtextxy(200, 400, L"能实现财富自由");
	outtextxy(750, 250, L"最后");
	outtextxy(750, 300, L"希望CF能上2000分");
	outtextxy(750, 350, L"希望下半年的计划一切顺利");

	
	settextcolor(RED);
	Sleep(2000);
	showBkImg();
	settextstyle(35, 0, L"黑体", 0, 0, 500, true, false, false);
	outtextxy(300, 280, L"2021 你好");
	outtextxy(300, 350, L"朝暮与岁月并往，");
	outtextxy(300, 420, L"       愿我们一同行至天光。");

	Sleep(3000);
}

void init(int i)
{
	int r[13] = { 120,120,155,123,130,147,138,138,130,135,140,132,155 };
	int x[13] = { 120,120,110,117,110,93,102,102,110,105,100,108,110 };
	int y[13] = { 120,120,85,118,120,105,103,110,110,120,1201,04,85 };

	fire[i].x = 0;
	fire[i].y = 0;
	fire[i].width = 240;
	fire[i].height = 240;
	fire[i].max_r = r[i];
	fire[i].cen_x = x[i];
	fire[i].cen_y = y[i];
	fire[i].show = false;
	fire[i].dt = 5;
	fire[i].t1 = timeGetTime();
	fire[i].r = 0;

	//初始化  烟花弹
	jet[i].x = 0;
	jet[i].y = 0;
	jet[i].hx = 0;
	jet[i].hy = 0;
	jet[i].height = 0;
	jet[i].t1 = timeGetTime();   //获取系统时间
	jet[i].dt = rand() % 10 + 5;   //0-9的随机时间
	jet[i].n = 0;
	jet[i].isshoot = false;
}

void loadimages()
{
	IMAGE fm, gm;
	loadimage(&fm, L"./res/flower.jpg", 3120, 240);
	for (int i = 0; i < NUM; i++)
	{
		SetWorkingImage(&fm);
		getimage(&gm, i * 240, 0, 240, 240);
		SetWorkingImage(&gm);
		for (int a = 0; a < 240; a++)
			for (int b = 0; b < 240; b++)
				fire[i].xy[a][b] = getpixel(a, b);
	}

	IMAGE jetimg;
	loadimage(&jetimg, L"./res/shoot.jpg", 200, 50);

	for (int i = 0; i < NUM; i++)
	{
		int n = rand() % 5;
		SetWorkingImage(&jetimg);
		getimage(&jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&jet[i].img[1], (n + 5) * 20, 0, 20, 50);
	}
	SetWorkingImage(NULL);

}

void choice(DWORD& t1)
{
	DWORD t2 = timeGetTime();

	if (t2 - t1 > 100) {
		int n = rand() % NUM;
		if (jet[n].isshoot == false && fire[n].show == false)
		{
			jet[n].x = rand() % 1180;
			jet[n].y = rand() % 100 + 600;
			jet[n].hx = jet[n].x + 10;
			jet[n].hy = rand() % 400;       
			jet[n].height = jet[n].y - jet[n].hy;
			jet[n].isshoot = true;

			putimage(jet[n].x, jet[n].y, &jet[n].img[jet[n].n], SRCINVERT);

		}
		t1 = t2;
	}
}

void shoot()
{
	for (int i = 0; i < NUM; i++)
	{
		jet[i].t2 = timeGetTime();
		if (jet[i].t2 - jet[i].t1 > jet[i].dt && jet[i].isshoot == true)
		{

			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);


			if (jet[i].hy < jet[i].y)
			{
				jet[i].n++;
				jet[i].y -= 5;
			}

			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);


			if (jet[i].y - jet[i].hy < jet[i].height)
				jet[i].dt = rand() % 5 + 8;

			if (jet[i].y <= jet[i].hy)
			{

				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

				fire[i].y = jet[i].hy;
				fire[i].x = jet[i].hx;
				fire[i].show = true;
				jet[i].isshoot = false;
			}
			jet[i].t1 = jet[i].t2;
		}
	}
}

void Show(DWORD* pMem)
{
	int drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 65, 65 };

	for (int i = 0; i < NUM; i++)
	{
		fire[i].t2 = timeGetTime();

		if (fire[i].t2 - fire[i].t1 > fire[i].dt && fire[i].show == true)
		{
			if (fire[i].r < fire[i].max_r)
			{
				fire[i].r++;
				fire[i].dt = drt[fire[i].r / 10];
				fire[i].draw = true;
			}

			if (fire[i].r >= fire[i].max_r - 1)
			{
				fire[i].draw = false;
				init(i);
			}
			fire[i].t1 = fire[i].t2;
		}

		if (fire[i].draw)
		{
			for (double a = 0; a <= 6.28; a += 0.01)
			{
				int x1 = (int)(fire[i].cen_x + fire[i].r * cos(a));
				int y1 = (int)(fire[i].cen_y + fire[i].r * sin(a));

				if (x1 > 0 && x1 < fire[i].width && y1>0 && y1 < fire[i].height)
				{
					int b = fire[i].xy[x1][y1] & 0xff;
					int g = (fire[i].xy[x1][y1] >> 8) & 0xff;
					int r = (fire[i].xy[x1][y1] >> 16);
					int xx = (int)(fire[i].x + fire[i].r * cos(a));
					int yy = (int)(fire[i].y + fire[i].r * sin(a));

					if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1200 && yy < 600 && yy>0)
					{
						pMem[yy * 1200 + xx] = BGR(fire[i].xy[x1][y1]);
					}
				}
			}
			fire[i].draw = true;
		}
	}
}