#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#define BLK "\e[1;30m"
#define RED "\e[1;31m"
#define BLU "\e[1;34m"
#define ORI "\e[0m"
#define spade "\u2660"
#define club "\u2663"
#define heart "\u2665"
#define diamond "\u2666"
int printf_flower(int a)
{
    a=rand()%4;

	if(a==0)
		printf(BLK "%s ",club);
	else if(a==1)
		printf(RED "%s ",diamond);
	else if(a==2)
		printf(RED "%s ",heart);
	else if(a==3)
		printf(BLK "%s ",spade);
}
void SetColor(int color )
{
  HANDLE hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole,color);
}
int setnum(int f, int n)
//給牌花色(1~4)、數字(1~13)，回傳編號(1~52)
{
	int cardnum;
	return cardnum=(f-1)*13+n;
}

int get_N(int cardnum)
//給牌編號(1~52)，回傳數字(1~13)
{
	int N;
	return N=((cardnum-1)%13)+1;
}

int get_F(int cardnum)
//給牌編號(1~52)，回傳花色(1~4)
{
	int F;
	return F=((cardnum-1)/13)+1;
}

void build_matrix(int player_card[5],int flower_count[4],int num_count[13])
//將玩家手牌變成num_count、flower_count兩個陣列
{
	int card[4][13];
	int i,j,f,n,total;
	for(i=0;i<4;i++)
    {
		for(j=0;j<13;j++)
        {
			card[i][j]=0;
      	}
	}
	for(i=0;i<5;i++)
    {
		f=get_F(   player_card[i]   );
        n=get_N(   player_card[i]   );
        card[f-1][n-1]= 1;
    }
    for(i=0;i<4;i++)
    {
		total =0;
        for (j=0;j<13;j++)
		{
			total+=card[i][j];
     	}
		flower_count[i]=total;
    }
    for(j=0;j<13;j++)
    {
		total =0;
        for (i=0;i<4;i++)
        {
			total+=card[i][j];
       	}
		num_count[j]=total;
    }
}

void print_card(int cardnum)
//印出手牌花色
{
	int F,N;
	F=get_F(cardnum);
	N=get_N(cardnum);
	if(F==1)
		printf(BLK "%s ",club);
	else if(F==2)
		printf(RED "%s ",diamond);
	else if(F==3)
		printf(RED "%s ",heart);
	else if(F==4)
		printf(BLK "%s ",spade);
	if(N==11)
		printf("J ");
	else if(N==12)
		printf("Q ");
	else if(N==13)
		printf("K ");
	else if(N==1)
		printf("A ");
	else
		printf("%d ",N);
}

int straight(int player_card[5])
//判斷是不是順子(連續5張牌)
{
    int flower_count[4]={0};
    int num_count[13]={0};
    int i,j,f,n,total;
    int is_stright=0;
    build_matrix(player_card,flower_count,num_count);
	for(i=0;i<9;i++)
    {
		if(((((num_count[i]==1) && num_count[i+1]==1) && num_count[i+2]==1) && num_count[i+3]==1) && num_count[i+4]==1)
		is_stright=1;
    }
	return is_stright;
}

int flush(int player_card[5])
//判斷是不是同花(5張牌都是同一種花色)
{
    int F,N,i,j,total;
    int isflush=0;
    int flower_count[4]={0};
    int num_count[13]={0};
    build_matrix(player_card,flower_count,num_count);
    for(i=0;i<4;i++)
    {
        if(flower_count[i]==5)
            isflush=1;
    }
    return isflush;
}

int four_kind(int player_card[5])
//判斷是不是鐵支(4張牌都是一樣的數字)
{
    int flower_count[4]={0};
    int num_count[13]={0};
    int i,j,f,n,total,isfour=0;
	build_matrix(player_card,flower_count,num_count);
    for(i=0;i<13;i++)
    {
    	if(num_count[i]==4)
        	isfour=1;
    }
    return isfour;
}

int choose_four(int player_card[5])
//從鐵支中挑出四張一樣的那張牌的數字(任取三張只要有兩張一樣就是)
{
	int a,b,d;
	int flower_count[4]={0};
    int num_count[13]={0};
    int i,j,f,n,total,isfour=0;
	build_matrix(player_card,flower_count,num_count);
	a=get_N(player_card[0]);
	b=get_N(player_card[1]);
	d=get_N(player_card[2]);
	if(a==b)
		return a;
	else if(b==d)
		return b;
	else
		return d;
}

int full_house(int player_card[5])
//判斷是不是葫蘆(3張牌一樣的數字+2張牌一樣的數字)
{
	int flower_count[4]={0};
    int num_count[13]={0};
    int i,j,f,n,total;
    int is_full_house=0;
    int is_three =0;
    int is_two=0;
	build_matrix(player_card,flower_count,num_count);
    for(i=0;i<13;i++)
    {
    	if(num_count[i]==3)
    	{
    		is_three =1;
		}
		else if(num_count[i]==2)
		{
			is_two=1;
		}

	}
	if((is_three==1)&&(is_two==1))
		is_full_house=1;
	return is_full_house;
}

int three_kind(int player_card[5])
//判斷是不是三條(3張牌一樣的數字)
{
	int flower_count[4]={0};
    int num_count[13]={0};
    int i,j,f,n,total;
    int is_three_kind=0;
    int is_three =0;
    int is_two=0;
	build_matrix(player_card,flower_count,num_count);
    for(i=0;i<13;i++)
    {
    	if(num_count[i]==3)
    	{
    		is_three =1;
		}
		else if(num_count[i]==2)
		{
			is_two=1;
		}

	}
	if((is_three==1)&&(is_two==0))
		is_three_kind=1;
	return is_three_kind;
}

int compare_four_kind(int player_card[])
//從鐵支中挑出4張一樣的那張牌的數字(有一種數字重複4張就是)
{
	int flower_count[4]={0};
    int num_count[13]={0};
    int i;
    build_matrix(player_card,flower_count,num_count);
    for(i=0;i<13;i++)
    {
    	if(num_count[i]==4)
    	{
    		return player_card[i];
		}
	}

}

int straight_flush(int player_card[5])
//判斷是不是同花大順(5張牌都是同一種花色、5張牌都連續)
{
    int s,i,j,f,n,total,is_straight_flush=0;
    s=straight(player_card);
    f=flush(player_card);
    if((straight(player_card))&& (flush(player_card)))
    {
    	is_straight_flush=1;
	}
    is_straight_flush;
}

int two_pair(int num_count[13])
//判斷是不是兩對(2個2張一樣的)
{
	int i,is_two_pair=0,is_pair=0;
	for(i=0;i<13;i++)
	{
		if(num_count[i]==2)
			is_pair++;
	}
	if(is_pair==2)
		is_two_pair=1;

	return is_two_pair;
}

int one_pair(int player_card[5])
//判斷是不是一對(2張一樣的)
{
	int flower_count[4]={0};
    int num_count[13]={0};
    int i,j,f,n,total;
    int is_three=0;
    int first_pair=0;
    int second_pair=0;
	build_matrix(player_card,flower_count,num_count);
/*	for(n=0;n<13;n++)
	{
		printf("%d",num_count[n]);
	}
*/	for(i=0;i<13;i++)
	{
		if(num_count[i]==2)
			first_pair++;
		else if (num_count[i]==3)
			is_three=1;
	}
	if(first_pair==1&&is_three==0)
		return 1;
	else
		return 0;

}

int small_straight(int player_card[5])
//判斷是不是小順(連續4張牌)(自己的牌型)
{
	int flower_count[4]={0};
    int num_count[13]={0};
    int i,j,f,n,total;
   	int	small_straight=0;
	build_matrix(player_card,flower_count,num_count);
	for(i=0;i<13;i++)
	{
		if(((((num_count[i]==1) && num_count[i+1]==1) && num_count[i+2]==1) && num_count[i+3]==1))
			small_straight=1;
	}
	return small_straight;
}

int small_straight_flush(int player_card[5])
//判斷是不是同花小順(連續4張牌、4張都是同一種花色)(自己的牌型)
{
	int flower_count[4]={0};
    int num_count[13]={0};
    int i,j,f,n,total;
   	int	small_straight_flush=0;
	build_matrix(player_card,flower_count,num_count);
	for(i=0;i<13;i++)
	{
		if((flower_count[i]==4) && (small_straight(player_card)))
			small_straight_flush=1;
	}
	return small_straight_flush;
}

int compare_small_straight(int player_card[5])
//從小順、同花小順中挑出4張連續中最大的那張牌
{
	int flower_count[4]={0};
    int num_count[13]={0};
    int i,j,f,n,total;
   	int	small_straight=0;
	build_matrix(player_card,flower_count,num_count);
	for(i=0;i<13;i++)
	{
		if(((((num_count[i]==1) && num_count[i+1]==1) && num_count[i+2]==1) && num_count[i+3]==1))
			small_straight=num_count[i+3];
	}

	return small_straight;
}

int choose_three(int num_count[13])
//從三條中挑出3張一樣的那張牌的數字(有一種數字重複3張就是)
{
    int i;
    for(i=0;i<13;i++)
    {
    	if(num_count[i]==3)
        	return i+1;
    }
}

int choose_pair(int c[])
//從對中挑出要比較的
{
 int i,r=0;
 int flower_count_c[4]={0},num_count_c[13]={0};
 build_matrix(c,flower_count_c,num_count_c);
 for(i=0;i<13;i++)
 {
   if(num_count_c[i]==2)
    r=i+1;
 }
 return r;
}

int compare(int c_A,int c_B)//n_A,n_B 1~52 if A>B return 1 else return 0
//比較牌的大小(先數字再花色)
{
	int f_A,f_B,n_A,n_B;
	int flower_count_A[4]={0};
    int num_count_A[13]={0};
    int flower_count_B[4]={0};
    int num_count_B[13]={0};
	f_A=get_F(c_A);
	n_A=get_N(c_A);
	f_B=get_F(c_B);
	n_B=get_N(c_B);
	if ((n_A > n_B)||((n_A==n_B)&&(f_A > f_B)))
		return 1;
	else
		return 0;
}

void sortcard(int card[])
//排序牌(左邊的牌假如比右邊大就交換)
{
    int i,j, temp;
    for (i=1;i<5;i++)
	{

	  for(j=0;j<(5-i);j++)
	    if(compare(card[j],card[j+1]))
	       {
	       	  temp=card[j];
	       	  card[j]=card[j+1];
	       	  card[j+1] = temp;
		   }
	}
}

void sortp(int array[],int sizep)
//排大小(左邊的數假如比右邊大就交換)
{
    int i,j,temp,temp1;
    for (i=1;i<sizep;i++)
	{

	  for(j=0;j<(sizep-i);j++)
      {
          if(array[j]>array[j+1])
	       {
                temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
		   }
      }

	}
}

int show_card(int card[])
//印出手牌
{
	int i;
	for(i=0;i<5;i++)
		print_card(card[i]);

	printf("\n")  ;
}


int give_value(int player_card[5])
/*
同花大順    (straight flush)       value=11000
同花小順    (small_straight_flush) value=10000
鐵支       (four_kind)            value=09000
葫蘆       (full_house)           value=08000
同花       (flush)                value=07000
順子       (straight)             value=06000
小順       (small_straight)       value=05000
三條       (three_kind)           value=04000
兩對       (two_pair)             value=03000
一對       (one_pair)             value=02000
散牌       (high_card)            value=01000
*/
{
	int value=10000;
	int flower_count[4]={0};
	int num_count[13]={0};
	int c;
	int i,j;
	build_matrix(player_card,flower_count,num_count);
	if(straight_flush(player_card)==1)
    //同花大順
	{
		value=11000;
		SetColor(14);
		printf("straight flush\n");
		value=(get_N(player_card[5]))*10+value;
		value=get_F(player_card[5])+value;
	}
	else if(small_straight_flush(player_card)==1)
	//同花小順
	{
		value=10000;
		SetColor(14);
		printf("small_straight_flush\n");
		c=compare_small_straight(player_card);
		value=c*10+value;
		for(i=0;i<5;i++)
		{
		    if(get_N(player_card[i])==c)
                value=get_F(player_card[i])+value;
		}

	}
	else if(four_kind(player_card)==1)
    //鐵支
	{
		value=9000;
		SetColor(14);
		printf("four_kind\n");
		c=choose_four(player_card);
		value=c*10+value;
		for(i=0;i<5;i++)
		{
		    if(get_N(player_card[i])==c)
                value=get_F(player_card[i])+value;
		}
	}
	else if(full_house(player_card)==1)
    //葫蘆
	{
		value=8000;
		SetColor(14);
		printf("full_house\n");
		c=choose_three(num_count);
		value=c*10+value;
		for(i=0;i<5;i++)
		{
		    if(get_N(player_card[i])==c)
                value=get_F(player_card[i])+value;
		}
	}
	else if(flush(player_card)==1)
    //同花
	{
		value=7000;
		SetColor(14);
		printf("flush\n");
		value=(get_N(player_card[5]))*10+value;
		value=get_F(player_card[5])+value;
	}
	else if(straight(player_card)==1)
	//順子
	{
		value=60000;
		SetColor(14);
		printf("straight\n");
		value=(get_N(player_card[5]))*10+value;
		value=get_F(player_card[5])+value;
	}
	else if(small_straight(player_card)==1)
	//小順
	{
		value=5000;
		SetColor(14);
		printf("small_straight\n");
		c=compare_small_straight(player_card);
		value=c*10+value;
		for(i=0;i<5;i++)
		{
		    if(get_N(player_card[i])==c)
                value=get_F(player_card[i])+value;
		}
	}
	else if(three_kind(player_card)==1)
	//三條
	{
		value=4000;
		SetColor(14);
		printf("three_kind\n");
		c=choose_three(num_count);
		value=c*10+value;
		for(i=0;i<5;i++)
		{
		    if(get_N(player_card[i])==c)
                value=get_F(player_card[i])+value;
		}
	}
	else if(two_pair(num_count)==1)
	//兩對
	{
		value=3000;
		SetColor(14);
		printf("two_pair\n");
		c=choose_pair(player_card);
		value=c*10+value;
		for(i=0;i<5;i++)
		{
		    if(get_N(player_card[i])==c)
                value=get_F(player_card[i])+value;
		}
	}
	else if(one_pair(player_card)==1)
	//一對
	{
		value=2000;
		SetColor(14);
		printf("one_pair\n");
		c=choose_pair(player_card);
		value=c*10+value;
		for(i=0;i<5;i++)
		{
		    if(get_N(player_card[i])==c)
                value=get_F(player_card[i])+value;
		}
	}
	else
	//散牌
		{
		    value=1000;

		    SetColor(14);
		    printf("high card\n");
            value=(get_N(player_card[5]))*10+value;
            value=get_F(player_card[5])+value;
		}
	return value;
}

int compare_card(int A[],int B[],int C[],int D[])//A>B return 1 else 0
//比較牌型
{
	int i,r,j,af,bf,as,bs,asf,bsf;
	int aop,bop,cop,dop;
	int atp,btp,ctp,dtp;
	int at,bt,ct,dt;
	int c1,c2;
	char o;
	int flower_count_A[4]={0};
    int num_count_A[13]={0};
    int flower_count_B[4]={0};
    int num_count_B[13]={0};
    int flower_count_C[4]={0};
    int num_count_C[13]={0};
    int flower_count_D[4]={0};
    int num_count_D[13]={0};
    int A_value,B_value,C_value,D_value;
    int player_type[4]={0};
    int player_order[4]={1,2,3,4};
    int player_final_order[4]={0};
    build_matrix(A,flower_count_A,num_count_A);
    build_matrix(B,flower_count_B,num_count_B);
    build_matrix(C,flower_count_C,num_count_C);
    build_matrix(D,flower_count_D,num_count_D);
    printf(ORI"A's card: ");
	show_card(A);
    printf(ORI"A's type: ");
    A_value=give_value(A);
    printf("\n");
    printf(ORI"B's card: ");
	show_card(B);
    printf(ORI"B's type: ");
    B_value=give_value(B);
    printf("\n");
    printf(ORI"C's card: ");
	show_card(C);
    printf(ORI"C's type: ");
    C_value=give_value(C);
    printf("\n");
    printf(ORI"D's card: ");
	show_card(D);
    printf(ORI"D's type: ");
    D_value=give_value(D);
    printf("\n");
    player_type[0]=A_value;
    player_type[1]=B_value;
    player_type[2]=C_value;
    player_type[3]=D_value;
    sortp(player_type,4);
    if(player_type[3]==A_value)
    {
        printf(ORI"The winner is:");
        SetColor(206);
        printf(" player_A ");
        printf(ORI"\n");
        printf(ORI"A's type: ");
        A_value=give_value(A);
    }
    else if(player_type[3]==B_value)
    {
        printf(ORI"The winner is:");
        SetColor(206);
        printf(" player_B ");
        printf(ORI"\n");
        printf(ORI"B's type: ");
        B_value=give_value(B);
    }
    else if(player_type[3]==C_value)
    {
        printf(ORI"The winner is:");
        SetColor(206);
        printf(" player_C ");
        printf(ORI"\n");
        printf(ORI"C's type: ");
        C_value=give_value(C);
    }
    else if(player_type[3]==D_value)
    {
        printf(ORI"The winner is:");
        SetColor(206);
        printf(" player_D ");
        printf(ORI"\n");
        printf(ORI"D's type: ");
        D_value=give_value(D);
    }
    printf(ORI"\n");
    if(player_type[0]==A_value)
    {
        printf(ORI"The loser  is:");
        SetColor(177);
        printf(" player_A ");
        printf(ORI"\n");
        printf(ORI"A's type: ");
        A_value=give_value(A);
    }
    else if(player_type[0]==B_value)
    {
        printf(ORI"The loser  is:");
        SetColor(177);
        printf(" player_B ");
        printf(ORI"\n");
        printf(ORI"B's type: ");
        B_value=give_value(B);
    }
    else if(player_type[0]==C_value)
    {
        printf(ORI"The loser  is:");
        SetColor(177);
        printf(" player_C ");
        printf(ORI"\n");
        printf(ORI"C's type: ");
        C_value=give_value(C);
    }
    else if(player_type[0]==D_value)
    {
        printf(ORI"The loser  is:");
        SetColor(177);
        printf(" player_D ");
        printf(ORI"\n");
        printf(ORI"D's type: ");
        D_value=give_value(D);
    }

}

int main()
{
	int p1,p2,temp,i,j,card[52]={0};
	int A[5]={0};
	int B[5]={0};
	int C[5]={0};
	int D[5]={0};
	int a;
	int flower_count_A[4]={0};
    int num_count_A[13]={0};
    int flower_count_B[4]={0};
    int num_count_B[13]={0};
    int flower_count_C[4]={0};
    int num_count_C[13]={0};
    int flower_count_D[4]={0};
    int num_count_D[13]={0};
	for(i=0;i<52;i++)
		card[i]=i+1;

	system("chcp 65001")	;

	srand(time(NULL));
	for(i=0;i<16;i++)
	{
		a=rand()%4;

		if(a==0)
			printf(BLK "%s ",club);
		else if(a==1)
			printf(RED "%s ",diamond);
		else if(a==2)
			printf(RED "%s ",heart);
		else if(a==3)
			printf(BLK "%s ",spade);
	}
	printf("\n");
	a=rand()%4;

	printf_flower(a);
	printf(ORI"Welcome to poker card game! ");
	printf_flower(a);
	printf("\n");
	for(i=0;i<16;i++)
	{
		a=rand()%4;

		if(a==0)
			printf(BLK "%s ",club);
		else if(a==1)
			printf(RED "%s ",diamond);
		else if(a==2)
			printf(RED "%s ",heart);
		else if(a==3)
			printf(BLK "%s ",spade);
	}
    printf("\n");
	SetColor(14);
	printf("PRESS ENTER TO CONTINUE!");
    getchar();
	a=rand()%4;
	for(i=0;i<16;i++)
	{
		a=rand()%4;

		if(a==0)
			printf(BLK "%s ",club);
		else if(a==1)
			printf(RED "%s ",diamond);
		else if(a==2)
			printf(RED "%s ",heart);
		else if(a==3)
			printf(BLK "%s ",spade);
	}
	printf("\n");
	printf_flower(a);
	printf(ORI"RULE:                       ");
	printf_flower(a);
	printf("\n");
	printf_flower(a);
	printf(ORI"(straight_flush)>           ");
	printf_flower(a);
	printf("\n");
	printf_flower(a);
	printf(ORI"(small_straight flush)>     ");
	printf_flower(a);
	printf("\n");
	printf_flower(a);
	printf(ORI"(four_kind)>(full_house)>   ");
	printf_flower(a);
	printf("\n");
	printf_flower(a);
	printf(ORI"(flush)>(straight)>         ");
	printf_flower(a);
	printf("\n");
	printf_flower(a);
	printf(ORI"(small_straight)>           ");
	printf_flower(a);
	printf("\n");
	printf_flower(a);
	printf(ORI"(three_kind)>(two_pair)>    ");
	printf_flower(a);
	printf("\n");
	printf_flower(a);
	printf(ORI"(one_pair)>(high_card)      ");
	printf_flower(a);
	printf("\n");
	for(i=0;i<16;i++)
	{
		a=rand()%4;
        printf_flower(a);
	}
	printf("\n");
	SetColor(14);
	SetColor(14);
	printf("PRESS ENTER TO START!");
    getchar();
	for(i=0;i<100;i++)
	{
	    //取隨意兩個數
		p1=rand()%52;
		p2=rand()%52;
		temp=card[p1];//將card[p1]放入暫存位
		card[p1]=card[p2];//將card[p2]放入card[p1]
		card[p2]=temp;//將暫存位放入card[p2]
	}

	printf(ORI"player_A:\n");
	j=0;
 	for(i=0;i<5;i++)//發玩家A的5張牌
		{
            A[j]=card[i];
            j++;
		}
/*   A[0]=1;
	A[1]=7;
	A[2]=20;
	A[3]=21;
	A[4]=34;*/
	sortcard(A);
//	show_card(A);
//	printf(ORI"player_B:\n");
	j=0;
	for(i=6;i<11;i++)//發玩家B的5張牌
		{
        	B[j]=card[i];
          	j++;
		}
/*    B[0]=1;
	B[1]=44;
	B[2]=45;
	B[3]=10;
	B[4]=23;*/
	sortcard(B);
//	printf("\n");
//	show_card(B);
//    printf(ORI"player_C:\n");
	j=0;
	for(i=12;i<17;i++)//發玩家C的5張牌
		{
            C[j]=card[i];
            j++;
		}
 /*   C[0]=14;
	C[1]=4;
	C[2]=48;
	C[3]=51;
	C[4]=26;*/
	sortcard(C);
//	show_card(C);
//    printf(ORI"player_D:\n");
	j=0;
	for(i=18;i<23;i++)//發玩家D的5張牌
		{
            D[j]=card[i];
            j++;
		}
	sortcard(D);
//	show_card(D);
	build_matrix(D,flower_count_D,num_count_D);
	compare_card(A,B,C,D);
	SetColor(1);
	printf(ORI"\n");
	system("pause");
	return 0;
}

