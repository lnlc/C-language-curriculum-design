#include"acllib.h"
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

#define MAX 55//���ֵ54
#define MIN 1//��Сֵ1
#define N 54//����54����ͬ�������ע��������ĸ������ܳ��������С��֮��ķ�Χ����Ȼ�ᵼ����ѭ��
#define se RGB(166,211,130)

//----------------�˿��ƽṹ����----------------//
struct CardCombo
{
	char Player;
	int id;
	int class;
	struct CardCombo* next;
};

struct card_temp
{
	int num;//��¼��������
	int tc[10];//��¼�������ݣ�class��
};
//------------------------------------------------//

//----------------��������----------------//

void sort(int a[], int n);//--------------------------------------------------------------  ѡ������
int change(int id);//-------------------------------------------------------------------  ID->Class
void addcard(int a[], int b[]);//-------------------------------------------------------------  ���ӵ�����
struct CardCombo* createlist(int player[], int n, char Player);//-----------------------  �˿���������
void fpai(int* player_1[], int* player_2[], int* player_3[], int* landlord[]);//-------------  ͨ���˿���IDϴ�ơ�����
struct CardCombo* deletem(struct CardCombo* L, int m);//-------------------------  ɾ��ָ��ID����
int estimate(int num, int tc[], struct CardCombo* player, int n);//---------------------  �ж��Ƿ�Ҫ����
int outcard(int* num, int tc[], struct CardCombo* player, int* n);//--------------------  ����
void change_card(struct CardCombo* p, struct CardCombo* L);//-------------------  �޸��ѳ��Ƶ�����
int random(void);//--------------------------------------------------------------------  ������ɳ����� 1~4
void out(int* number, int* add, struct CardCombo** head, int* num, int tc[], char op);
void showcard(struct CardCombo* p_0, struct CardCombo* p_1, struct CardCombo* p_2);
void host(void);
void timeListener(int id)
{
	host();
}

//-----------------------------------------//
ACL_Image image[54];
ACL_Image background;
ACL_Image player[3];

int C[54];
char* card_num[54] = { "image/1.jpg","image/2.jpg","image/3.jpg","image/4.jpg","image/5.jpg","image/6.jpg","image/7.jpg","image/8.jpg", "image/9.jpg","image/10.jpg","image/11.jpg","image/12.jpg","image/13.jpg","image/14.jpg","image/15.jpg","image/16.jpg","image/17.jpg","image/18.jpg", "image/19.jpg","image/20.jpg", "image/21.jpg","image/22.jpg","image/23.jpg","image/24.jpg","image/25.jpg","image/26.jpg","image/27.jpg","image/28.jpg", "image/29.jpg","image/30.jpg", "image/31.jpg","image/32.jpg","image/33.jpg","image/34.jpg","image/35.jpg","image/36.jpg","image/37.jpg","image/38.jpg", "image/39.jpg","image/40.jpg","image/41.jpg","image/42.jpg","image/43.jpg","image/44.jpg","image/45.jpg","image/46.jpg","image/47.jpg","image/48.jpg", "image/49.jpg","image/50.jpg","image/51.jpg","image/52.jpg","image/53.jpg","image/54.jpg" };
char* back = "image/back.jpg";
char* PLAYER[3] = { "image/playerA.jpg","image/playerB.jpg" ,"image/playerC.jpg" };

int player_1[21] = { 0 };
int player_2[21] = { 0 };
int player_3[21] = { 0 };
int landlord[4] = { 0 };
int number[3] = { 17,17,17 };//��¼ʣ������
struct CardCombo* p, * head[3];
struct CardCombo* head_4 = NULL;//��¼���Ƶ�����δʵ�֣�
struct card_temp tempC;//��¼��һ�������߳����ƣ������Ʋ��ı�����
int r = 0;//�ж��Ƿ����
int add = 0;
char op[3] = { 'C','A','B' };
int i = 0;// 0--C  1--A  2--B


int Setup(void)
{
	//------�����ն˴���-------//
	//�����������ٳ�����������
	initConsole();
	//--------------------------//DEFAULT
	initWindow("ɳ�񶷵���", DEFAULT,DEFAULT , 1500, 927);//��ʼ�����򴰿ڣ�width:1500 * height:927

	loadImage(back, &background);
	for (int i = 0; i < 54; i++)
	{
		loadImage(card_num[i], &image[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		loadImage(PLAYER[i], &player[i]);
	}

	
	beginPaint();//------��ʼ����------//

	putImageScale(&background, 0, 0, 1500, 927);
	setTextSize(50);
	setTextColor(RED);
	setTextBkColor(se);
	paintText(600, 420, "Welcome !");
	
	//loadImage(card_num[1], &image[1]);
	//putImageScale(&image[1], 10, 10, 100, 150);
	//putImageScale(&image[2], 40, 50, 100, 150);

	endPaint();//------��������------//
	

	fpai(player_1, player_2, player_3, landlord);//���ú������ϴ�Ʒ���
	//----------------����������----------------//
	{
		printf("\n\n\n");
		printf("----------------����������----------------\n\n\n");
		printf("             A     B     C\n\n");
		for (int i = 0; i < 17; i++)
		{
			printf("            %2d    %2d    %2d\n", player_1[i], player_2[i], player_3[i]);
		}
		printf("\n\n                ������\n\n");
		for (int i = 0; i < 3; i++)
		{
			printf("      %2d    ", landlord[i]);
		}
		printf("\n\n\n");
		printf("----------------------------------------------\n");
		//----------------------------------------------//
	}

	addcard(player_3, landlord);//++++++++++++++++++++++++++++++++++Ĭ�����CΪ����
	number[0] += 3;//��������3

	head[1] = createlist(player_1, 17, 'A');
	head[2] = createlist(player_2, 17, 'B');
	head[0] = createlist(player_3, 20, 'C');
	//----------------����������----------------//
	{
		printf("\n\n\n");
		printf("----------------����������----------------\n\n\n");
		for (p = head[1]; p != NULL; p = p->next)
		{
			printf("      player: %c |   Class: %2d |   ID: %2d\n", p->Player, p->class, p->id);
		}
		printf("\n\n\n");
		for (p = head[2]; p != NULL; p = p->next)
		{
			printf("      player: %c |   Class: %2d |   ID: %2d\n", p->Player, p->class, p->id);
		}
		printf("\n\n\n");
		for (p = head[0]; p != NULL; p = p->next)
		{
			printf("      player: %c |   Class: %2d |   ID: %2d\n", p->Player, p->class, p->id);
		}
		printf("\n\n\n");
		printf("----------------------------------------------\n");
		//----------------------------------------------//
	}

	printf("\n\n                  �������\n\n");

	tempC.num = 0;
	tempC.tc[0] = 0;//��id

	showcard(head[0], head[1], head[2]);//ͼ�λ�������ʾ���ƺ����������ƿ�
	/*
	while (r != -1)
	{

		out(&number[i], &add, &head[i], &tempC.num, tempC.tc, op[i]);

		if (add == 0)//add Ϊ 0 ��ʾ�ɹ�����
		{
			i++;
			if (i == 3)
			{
				i = 0;
			}
		}
		if (add == 3)//���˶�������
		{
			i--;
			if (i == -1)
			{
				i = 2;
			}
			tempC.tc[0] = 0;
			tempC.tc[1] = 0;
			tempC.tc[2] = 0;
			tempC.tc[3] = 0;
			tempC.num = random();
			while (estimate(tempC.num, tempC.tc, head[i]) != 1)
			{
				tempC.num = random();
			}

			add = 0;
		}
		beginPaint();
		clearDevice();
		int x, y;
		x = 650;
		y = 280;
		for (int i = 0; i < tempC.num; i++)
		{
			putImageScale(&image[tempC.tc[i]], x, y, 110, 160);
			x + 40;
		}
		endPaint();
		showcard(head[0], head[1], head[2]);//����ͼ�λ�������ҵ���
		//�ж��Ƿ����
		if (number[1] == 0)
		{
			printf("\n\n----------------------------------------------\n\n              The winner is A !\n\n----------------------------------------------\n");
			return 0;
		}
		else if (number[2] == 0)
		{
			printf("\n\n----------------------------------------------\n\n              The winner is B !\n\n----------------------------------------------\n");
			return 0;
		}
		else if (number[0] == 0)
		{
			printf("\n\n----------------------------------------------\n\n              The winner is C !\n\n----------------------------------------------\n");
			return 0;
		}
	}
*/

	
		registerTimerEvent(timeListener);
		startTimer(0, 500);//����ʱ��
	

	return 0;
}

/*------����Ϊ������ʵ��------*//////////////////////////////////////////////////////////////////////////////////////////////



void host(void)
{

	/*
	int player_1[21] = { 0 };
	int player_2[21] = { 0 };
	int player_3[21] = { 0 };
	int landlord[4] = { 0 };

	fpai(player_1, player_2, player_3, landlord);//���ú������ϴ�Ʒ���
	//----------------����������----------------//
	{
		printf("\n\n\n");
		printf("----------------����������----------------\n\n\n");
		printf("             A     B     C\n\n");
		for (int i = 0; i < 17; i++)
		{
			printf("            %2d    %2d    %2d\n", player_1[i], player_2[i], player_3[i]);
		}
		printf("\n\n                ������\n\n");
		for (int i = 0; i < 3; i++)
		{
			printf("      %2d    ", landlord[i]);
		}
		printf("\n\n\n");
		printf("----------------------------------------------\n");
		//----------------------------------------------//
	}


	struct CardCombo* p, * head[3];
	int number[3] = { 17,17,17 };//��¼ʣ������
	add(player_3, landlord);//++++++++++++++++++++++++++++++++++Ĭ�����CΪ����
	number[0] += 3;//��������3
	struct CardCombo* head_4 = NULL;//��¼���Ƶ�����δʵ�֣�
	head[1] = createlist(player_1, 17, 'A');
	head[2] = createlist(player_2, 17, 'B');
	head[0] = createlist(player_3, 20, 'C');
	//----------------����������----------------//
	{
		printf("\n\n\n");
		printf("----------------����������----------------\n\n\n");
		for (p = head[1]; p != NULL; p = p->next)
		{
			printf("      player: %c |   Class: %2d |   ID: %2d\n", p->Player, p->class, p->id);
		}
		printf("\n\n\n");
		for (p = head[2]; p != NULL; p = p->next)
		{
			printf("      player: %c |   Class: %2d |   ID: %2d\n", p->Player, p->class, p->id);
		}
		printf("\n\n\n");
		for (p = head[0]; p != NULL; p = p->next)
		{
			printf("      player: %c |   Class: %2d |   ID: %2d\n", p->Player, p->class, p->id);
		}
		printf("\n\n\n");
		printf("----------------------------------------------\n");
		//----------------------------------------------//
	}

	printf("\n\n                  �������\n\n");

	struct card_temp tempC;//��¼��һ�������߳����ƣ������Ʋ��ı�����
	tempC.num = 0;
	tempC.tc[0] = 0;//��id
	int r = 0;//�ж��Ƿ����
	int add = 0;
	char op[3] = { 'C','A','B' };
	int i = 0;// 0--C  1--A  2--B
	showcard(head[0], head[1], head[2]);//ͼ�λ�������ʾ���ƺ����������ƿ�

	startTimer(0, 1000);//ʱ������
	*/
	
		out(&number[i], &add, &head[i], &tempC.num, tempC.tc, op[i]);

		if (add == 0)//add Ϊ 0 ��ʾ�ɹ�����
		{
			i++;
			if (i == 3)
			{
				i = 0;
			}
		}
		if (add == 3)//���˶�������
		{
			i--;
			if (i == -1)
			{
				i = 2;
			}
			tempC.tc[0] = 0;
			tempC.tc[1] = 0;
			tempC.tc[2] = 0;
			tempC.tc[3] = 0;
			tempC.num = random();
			while (estimate(tempC.num, tempC.tc, head[i], number[i]) != 1)
			{
				tempC.num = random();
			}

			add = 0;
		}
		beginPaint();
		clearDevice();
		putImageScale(&background, 0, 0, 1500, 927);
		int x, y;
		x = 550;
		y = 280;
		for (int i = 0; i < tempC.num; i++)
		{
			putImageScale(&image[tempC.tc[i]-1], x, y, 110, 160);
			x += 120;
		}
		endPaint();
		showcard(head[0], head[1], head[2]);//����ͼ�λ�������ҵ���
		//�ж��Ƿ����
		if (number[1] == 0)
		{
			printf("+---------------------------------------------------+\n");
			printf("|                                                   |\n");
			printf("|                 The winner is A !                 |\n");
			printf("|                                                   |\n");
			printf("+---------------------------------------------------+\n");
			//exit(0);
			cancelTimer(0);
			beginPaint();
			setTextSize(50);
			setTextColor(RED);
			setTextBkColor(se);
			paintText(400, 620, "The winner is A !");

			endPaint();
			return 0;
		}
		else if (number[2] == 0)
		{
			printf("+---------------------------------------------------+\n");
			printf("|                                                   |\n");
			printf("|                 The winner is B !                 |\n");
			printf("|                                                   |\n");
			printf("+---------------------------------------------------+\n");
			//exit(0);
			cancelTimer(0);
			beginPaint();
			beginPaint();
			setTextSize(50);
			setTextColor(RED);
			setTextBkColor(se);
			paintText(400, 620, "The winner is B !");

			endPaint();
			return 0;
		}
		else if (number[0] == 0)
		{
			printf("+---------------------------------------------------+\n");
			printf("|                                                   |\n");
			printf("|                 The winner is C !                 |\n");
			printf("|                                                   |\n");
			printf("+---------------------------------------------------+\n");
			//exit(0);
			cancelTimer(0);
			beginPaint();
			beginPaint();
			setTextSize(50);
			setTextColor(RED);
			setTextBkColor(se);
			paintText(400, 620, "The winner is C !");

			endPaint();
			return 0;
		}
	
	return 0;
}

void showcard(struct CardCombo* p_0, struct CardCombo* p_1, struct CardCombo* p_2)
{
	int x, y;
	beginPaint();//------��ʼ����------//
	putImageScale(&player[2], 450, 650, 130, 280);
	x = 600;
	y = 750;
	while(p_0!=NULL)
	{
		putImageScale(&image[p_0->id-1], x, y, 110, 160);
		x += 25;
		p_0 = p_0->next;
	}
	putImageScale(&player[0], 25, 60, 130, 280);
	x = 227;
	y = 40;
	while (p_1 != NULL)
	{
		putImageScale(&image[p_1->id - 1], x, y, 110, 160);
		y += 30;
		p_1 = p_1->next;
	}
	putImageScale(&player[1], 1345, 60, 130, 280);
	x = 1163;
	y = 40;
	while (p_2 != NULL)
	{
		putImageScale(&image[p_2->id - 1], x, y, 110, 160);
		y += 30;
		p_2 = p_2->next;
	}

	endPaint();//------��������------//
}

void out(int* number, int* add, struct CardCombo** head, int* num, int tc[], char op)
{
	int r;
	if (*number < *num)//�ж������Ƿ�������������
	{
		*add += 1;
		return;
	}
	r = outcard(num, tc, *head, number);//���� 0 �������ƣ����� 1 ������� 
	if (r == 0)
	{
		*add += 1;
	}
	else
	{
		printf("      %c -> ����:%d  |  ", op, *num);
		for (int i = 0; i < *num; i++)
		{
			printf("Class:%2d  |  ID:%2d      ", change(tc[i]), tc[i]);//���
			*head = deletem(*head, tc[i]);//ɾ���ڵ�
		}
		printf("\n");
		add = 0;
	}
}

//----------------ѡ������----------------//
void sort(int a[], int n)
{
	int i, j, t;
	for (i = 1; i < n; i++)
	{
		for (j = 0; j < n - 1; j++)
		{
			if (change(a[j]) > change(a[j + 1]))
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
	}
	//--------------------------------------------//
}

//----------------  ID->Class  ----------------//
int change(int id)
{
	int class = 0;
	switch (id)
	{
	case 0:class = 0; break;//�����
	case 1:class = 12; break;
	case 2:class = 13; break;
	case 3:class = 1; break;
	case 4:class = 2; break;
	case 5:class = 3; break;
	case 6:class = 4; break;
	case 7:class = 5; break;
	case 8:class = 6; break;
	case 9:class = 7; break;
	case 10:class = 8; break;
	case 11:class = 9; break;
	case 12:class = 10; break;
	case 13:class = 11; break;
	case 14:class = 12; break;
	case 15:class = 13; break;
	case 16:class = 1; break;
	case 17:class = 2; break;
	case 18:class = 3; break;
	case 19:class = 4; break;
	case 20:class = 5; break;
	case 21:class = 6; break;
	case 22:class = 7; break;
	case 23:class = 8; break;
	case 24:class = 9; break;
	case 25:class = 10; break;
	case 26:class = 11; break;
	case 27:class = 12; break;
	case 28:class = 13; break;
	case 29:class = 1; break;
	case 30:class = 2; break;
	case 31:class = 3; break;
	case 32:class = 4; break;
	case 33:class = 5; break;
	case 34:class = 6; break;
	case 35:class = 7; break;
	case 36:class = 8; break;
	case 37:class = 9; break;
	case 38:class = 10; break;
	case 39:class = 11; break;
	case 40:class = 12; break;
	case 41:class = 13; break;
	case 42:class = 1; break;
	case 43:class = 2; break;
	case 44:class = 3; break;
	case 45:class = 4; break;
	case 46:class = 5; break;
	case 47:class = 6; break;
	case 48:class = 7; break;
	case 49:class = 8; break;
	case 50:class = 9; break;
	case 51:class = 10; break;
	case 52:class = 11; break;
	case 53:class = 14; break;
	case 54:class = 15; break;
	default:
		break;
	}
	return class;
	//---------------------------------------------//
}

//----------------���ӵ�����----------------//
void addcard(int a[], int b[])
{
	int i;
	int count = 17;
	for (i = 0; i < 3; i++)
	{
		a[count] = *(b + i);
		count++;
	}
	//-------------------------------------------//
}

//----------------�˿���������----------------//
struct CardCombo* createlist(int player[], int n, char Player)
{
	char people = Player;
	sort(player, n);
	struct CardCombo* p, * head = NULL, * tail = NULL;
	int size = sizeof(struct CardCombo);
	int i = 0;
	while (player[i] != 0)
	{

		p = (struct CardCombo*)malloc(size);//�����ڴ�
		p->Player = people;
		p->id = player[i];//���뿨ƬID
		p->class = change(player[i]);
		p->next = NULL;
		if (head == NULL)
		{
			head = p;
			tail = p;
		}
		else
		{
			tail->next = p;
		}
		tail = p;
		i++;
	}
	return head;
	//------------------------------------------------//
}

//----------------ͨ���˿���IDϴ�ơ�����----------------//
void fpai(int* player_1[], int* player_2[], int* player_3[], int* landlord[])
{
	srand(time(NULL));
	int RandNum, card[N] = { 0 };
	int i, j, flag = 0, t = 0;
	while (1)
	{
		flag = 0;//���
		if (t == N)
			break;

		RandNum = (rand() % (MAX - MIN)) + MIN;
		for (i = 0; i < t; i++)//����
		{
			if (card[i] == RandNum)
				flag = 1;
		}
		if (flag != 1)
		{
			card[t] = RandNum;
			printf("      ��%2d����ID��: %d\n", t + 1, card[t]);//����������
			t++;
		}
	}
	//ϴ�ƽ���

	//��ʼ����
	int count = 0;
	for (int i = 0; i < 17; i++)
	{
		player_1[i] = card[count];
		count++;
		player_2[i] = card[count];
		count++;
		player_3[i] = card[count];
		count++;
	}
	landlord[0] = card[51];
	landlord[1] = card[52];
	landlord[2] = card[53];
	//---------------------------------------------------------//
}

//----------------ɾ��ָ��ID����----------------//
struct CardCombo* deletem(struct CardCombo* L, int m)
{
	struct CardCombo* head, * p, * q;
	head = L;
	while ((head->id == m) && (head->next != NULL))
		//Ѱ�Ҵӵ�һ����ʼ�����������һ���ڵ��⣬����M�Ľڵ㶼ɾȥ
	{
		p = head->next;
		free(head);
		head = p;
	}
	if (head->id == m)//������һ�ڵ����m��ֻ��һ���ڵ��Ұ���m
	{
		return NULL;
	}
	p = head;
	q = head->next;
	while (q)
	{
		if (q->id == m)
		{
			p->next = q->next;//��������
			free(q);//�ͷ��ڴ�
			q = p->next;
			continue;
		}
		else
		{
			p = q;
			q = p->next;
		}
	}
	return head;
	//------------------------------------------------//
}

//----------------�ж��Ƿ��ܳ���----------------//
int estimate(int num, int tc[], struct CardCombo* player, int n)
{
	struct CardCombo* p_0, * p_1 = NULL, * p_2 = NULL, * p_3 = NULL, * temp = NULL;

	if (player == NULL)//�������ǿ�
	{
		return 0;
	}

	p_0 = player;
	temp = p_0->next;//��ȡ��һ��

	if (temp != NULL)//��ȡ���漸���ڵ��Ӧ�ĵ�ַ
	{
		p_1 = temp;
		temp = temp->next;
		if (temp != NULL)
		{
			p_2 = temp;
			temp = temp->next;
			if (temp != NULL)
			{
				p_3 = temp;
			}
		}
	}
	int card = change(tc[0]);//��ȡ��һ����һ���Ƶ�class
	if (card == 14 && num == 2)//��һ������ը
	{
		return;
	}

	if (num <= 1)
	{
		while (num<=n)
		{
			if (p_0->class > card)
			{
				return 1;
			}
			else
			{
				if (p_0->next == NULL)
				{
					return 0;//û�п��Գ���
				}
				else
				{
					p_0 = p_0->next;
				}
			}
		}
		return 0;//û�п��Գ���
	}
	else if (num == 2)
	{
		while (num <= n)
		{
			if (p_0->class > card&& p_0->class == p_1->class)
			{
				return 1;
			}
			else
			{
				if (p_1->next == NULL)
				{
					return 0;//û�п��Գ���
				}
				else
				{
					p_0 = p_1;
					p_1 = p_1->next;
				}
			}
		}
		return 0;//û�п��Գ���
	}
	else if (num == 3)
	{
		while (num <= n)
		{
			if (p_0->class > card&& p_0->class == p_1->class && p_0->class == p_2->class)
			{
				return 1;
			}
			else
			{
				if (p_2->next == NULL)
				{
					return 0;//û�п��Գ���
				}
				else
				{
					p_0 = p_1;
					p_1 = p_2;
					p_2 = p_2->next;
				}
			}
		}
		return 0;//û�п��Գ���
	}
	else if (num == 4)
	{
		while (num <= n)
		{
			if (p_0->class > card&& p_0->class == p_1->class && p_0->class == p_2->class && p_0->class == p_3->class)
			{
				return 1;
			}
			else
			{
					
				if (p_3->next == NULL)
				{
					return 0;//û�п��Գ���
				}
				else
				{
					p_0 = p_1;
					p_1 = p_2;
					p_2 = p_3;
					p_3 = p_3->next;
				}
			}
		}
		return 0;//û�п��Գ���
	}

	//���� 0 ������������ 1 �����
}
//------------------------------------------------//

//----------------����----------------//
int outcard(int* num, int tc[], struct CardCombo* player, int* n)//
{
	struct CardCombo* p_0, * p_1 = NULL, * p_2 = NULL, * p_3 = NULL, * temp = NULL;
	p_0 = player;

	if (p_0 == NULL)
	{
		printf("over!!");//=======================================����,����-1
		return-1;
	}
	temp = p_0->next;//��ȡ��һ��
//��ȡ���漸���ڵ��Ӧ�ĵ�ַ
	if (temp != NULL)
	{
		p_1 = temp;
		temp = temp->next;
		if (temp != NULL)
		{
			p_2 = temp;
			temp = temp->next;
			if (temp != NULL)
			{
				p_3 = temp;
			}
		}
	}
	/*
	if (num > count)//�Ƚ��Ƿ����㹻����
	{
		return;//���������㣬����
	}*/
	int card = change(tc[0]);//��ȡ��һ����һ���Ƶ�class
	if (card == 14 && *num == 2)//��һ������ը
	{
		return;
	}

	if (*num <= 1)
	{
		while (1)
		{
			if (p_0->class > card)
			{
				tc[0] = p_0->id;
				*n -= 1;
				*num = 1;
				return 1;
			}
			else
			{
				if (p_0->next == NULL)
				{
					return 0;//û�п��Գ���
				}
				else
				{
					p_0 = p_0->next;
				}
			}
		}
	}
	else if (*num == 2)
	{
		while (1)
		{
			if (p_0->class > card&& p_0->class == p_1->class)
			{
				tc[0] = p_0->id;
				tc[1] = p_1->id;
				*n -= 2;
				return 1;
			}
			else
			{
				if (p_1->next == NULL)
				{
					return 0;//û�п��Գ���
				}
				else
				{
					p_0 = p_1;
					p_1 = p_1->next;
				}
			}
		}
	}
	else if (*num == 3)
	{
		while (1)
		{
			if (p_0->class > card&& p_0->class == p_1->class && p_0->class == p_2->class)
			{
				tc[0] = p_0->id;
				tc[1] = p_1->id;
				tc[2] = p_2->id;
				*n -= 3;
				return 1;
			}
			else
			{
				if (p_2->next == NULL)
				{
					return 0;//û�п��Գ���
				}
				else
				{
					p_0 = p_1;
					p_1 = p_2;
					p_2 = p_2->next;
				}
			}
		}
	}
	else if (*num == 4)
	{
		while (1)
		{
			if (p_0->class > card&& p_0->class == p_1->class && p_0->class == p_2->class && p_0->class == p_3->class)
			{
				tc[0] = p_0->id;
				tc[1] = p_1->id;
				tc[2] = p_2->id;
				tc[3] = p_3->id;
				*n -= 4;
				return 1;
			}
			else
			{
				if (p_3->next == NULL)
				{
					return 0;//û�п��Գ���
				}
				else
				{
					p_0 = p_1;
					p_1 = p_2;
					p_2 = p_3;
					p_3 = p_3->next;
				}
			}
		}
	}

	//���� 0 ������������ 1 ����� 
	//-------------------------------------//
}

//----------------�޸��ѳ��Ƶ�����----------------//
void change_card(struct CardCombo* p, struct CardCombo* L)//p���Գ�������ǰ���һ���ڵ�ĵ�ַ��L��Ҫ����Ľڵ�ĵ�ַ
{
	struct CardCombo* temp = NULL, * tail = NULL;
	int size = sizeof(struct CardCombo);
	temp = (struct CardCombo*)malloc(size);//��Ϊɾ��������free��Ҫ����Ľڵ㣬����Ҫ����һ���µ�
	p->next = temp;
	temp->class = L->class;
	temp->id = L->id;
	temp->Player = L->Player;
	temp->next = NULL;
	p = temp;//�޸ĳ�������ǰ���һ���ڵ�ĵ�ַ

/*
	if (p == NULL)//�ж��Ƿ��Ǳ�ͷ
	{
		p = temp;
	}
	else
	{
		p->next = temp;
	}
	//����������ǣ���������
	*/

	//tail = temp->next;
	//return tail;
}
//--------------------------------------------------//

//----------------������ɳ����� 1~4----------------//
int random(void)
{
	srand(time(NULL));
	int RandNum;
	RandNum = (rand() % (5 - MIN)) + MIN;
	return RandNum;
}