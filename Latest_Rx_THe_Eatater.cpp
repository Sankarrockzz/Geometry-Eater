#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<snk/rx.h>
using namespace std;

void gotoxy(int r, int c)
{
 c*=2;
 COORD co={c,r};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),co);
}

char p2[15][15]={{' '}} ,sig;;
int flg=0,sv_c,svM_c=0,s_tym=0; /// c= count; m= moves no.; tym= time;
class rx
{
    char (*ar)[15];
    int x,y,lf;
    char F_s;  /// Mk_s = Mark_ate, F_s= To be find( '#') ;
 public:
    clock_t s,e;
    int tym;
    static int lv_n,w1,w2;
    int c,Mv_c;
    rx();
    void disp();
    int inRange(int,int);
    void _move(char);
    void disp_scr();
    void quit();
    void win_levl();
    void print(char);
    ~rx();
};

int rx::lv_n=1; int rx:: w1=0; int rx:: w2=0; /// Initializing all Static members;

rx::rx()
{
   /// Initializing Things
  x=7; y=7;
  if(flg%2==0)
     {
      flg++;
      ar=(char (*)[15]) levl(lv_n,c); sv_c=c; /// sv to save 'c' for P2;
      if(ar==0)
        {
         system("cls");
         cout<<"\n\n \t GAME OVER \n";
         (w1>w2)? printf("\tPlayer 1 WIN "):(w1==w2)? printf("\t DRAW "): printf("\tPlayer 2 WIN ");
         cout<<"\n\n";
         delete ar;
         //delete x;
         getch();
         exit(0);
        }
      system("cls");
      cout<<"\n\n";
      cout<<"   Player 1\tLevel "<<lv_n;

      for(int i=0;i<15;i++)
         {
          for(int j=0;j<15;j++)

              if(ar[i][j]=='#')
                 p2[i][j]='#';
              else if(ar[i][j]=='*')
                 p2[i][j]=' ';
              else
                 p2[i][j]=ar[i][j];

         }
      }
  else
   {
     system("cls");
     cout<<"\n\n";
     cout<<"   Player 2\tLevel "<<lv_n;
     flg++;
     ar=p2; c=sv_c; tym=0;
   }

  ar[7][7]='*'; /** initialize Start point as '*'; */
  F_s='#'; /// To Find_Symbol;
  Mv_c=0;/// To count moves;
}

rx::~rx()
{
    delete ar;
}

void rx:: disp()
{
    system("cls");
    for(int i=0;i<15;i++)
        {
         for(int j=0;j<15;j++)
             cout<<ar[i][j]<<" ";
         cout<<endl;
        }
}

void disp_demo(char (*r)[15])
{
    system("cls");
    for(int i=0;i<15;i++)
        {
         for(int j=0;j<15;j++)
             cout<<r[i][j]<<" ";
         cout<<endl;
        }
}

int rx:: inRange(int i,int j)
{
/** best Way to check till */
 if(i>=1&&j>=1)             /// ">=1" becoz the boundary takes 1 pixel i.e boundary of 1 pixel;
    {
     if(i<14&&j<14)
	     return 1;
     else
	     return 0;
    }
 return 0;
}

/** To print the mark, after a move( w a s d);*/
void rx:: print(char ch)
{
 gotoxy(x,y);
 cout<<ch;
}

void rx::_move(char m)
{
 Mv_c++;
    switch(m)
     {
        case 'w':
        {
         if(inRange(x-1,y)==0)
            break;
         ar[x][y]=' ';
         print(' ');
         x-=1;
         if(ar[x][y]==F_s)
            c--;
         ar[x][y]='*';
         print('*');
         break;
        }

        case 's':
        {
         if(inRange(x+1,y)==0)
            break;
         ar[x][y]=' ';
         print(' ');
         x+=1;
         if(ar[x][y]==F_s)
            c--;
         ar[x][y]='*';
         print('*');
         break;
        }

        case 'd':
        {
         if(inRange(x,y+1)==0)
            break;
         ar[x][y]=' ';
         print(' ');
         y+=1;
         if(ar[x][y]==F_s)
            c--;
         ar[x][y]='*';
         print('*');
         break;
        }

        case 'a':
        {
         if(inRange(x,y-1)==0)
            break;
         ar[x][y]=' ';
         print(' ');
         y-=1;
         if(ar[x][y]==F_s)
            c--;
         ar[x][y]='*';
         print('*');
         break;
        }
        default:
        {
          break;
        }
    }
  gotoxy(17,0);
}

void Al_lvls()
{
 system("cls");
 int c; char (*ar)[15],ch;
 for(int i=1;i<=8;i++)
    {
     gotoxy(3,0);
     ar=(char (*)[15]) levl(i,c);
     disp_demo(ar);

     cout<<"\n          Level  "<<i<<" \n\n";
     gotoxy(17,0);
     if(ch=getch(), ch==(char)27)
        break;
     //getch();
    }
}

void rx::disp_scr()
{
 system("cls");
 cout<<"\n\n";
 cout<<" *-*-* Your Score is *-*-* \n\n";
 cout<<"     :----------------:~$\n";
 cout<<"     |    "<<Mv_c<<" Moves    |\n";
 tym=(e-s)/CLK_TCK;
 cout<<"     |    "<<tym<<" Sec.   "<<"  | \n";
 cout<<"   $~:----------------:\n";
 cout<<"\n\n";
 cout<<"Esc=Exit      Enter=Next Level";
 cout<<"\n\n";cout<<"\n\n";
}

void rx:: quit()
{
    system("cls");
    cout<<"\n\n";
    cout<<" x-x-x  You Quit  x-x-x \n";
    cout<<"\n\n";
}
/** Winner of Each Level */
void rx:: win_levl()
{

 int s=((s_tym<tym)?((svM_c<=Mv_c)? 1: ((svM_c - Mv_c)<=2)? 1 : 2) : ((tym==s_tym)?((svM_c<Mv_c)?1:((svM_c==Mv_c)? (-1): 2)) :

        ((Mv_c<=svM_c)? 2: ((Mv_c - svM_c)<=2)? 2 : 1))) ;

 if(s==1)
   {
    cout<<"   Player 1 Win Level "<<lv_n-1;
    w1++;
   }
 else if(s==2)
    {
     cout<<"   Player 2 Win Level "<<lv_n-1;
     w2++;
    }
  else
    cout<<"          Draw ";
}

void start()
{
 cout<< "\n    gEomEtry EatEr \n\n";
 cout<<" Press Any key to Start \n\n";
 cout<<" ( L= To see all level )\n";
 if(sig=getch(),sig=='l')    /// if player want to Quit in the beginning;
    Al_lvls();
}

main()
{
 start();

 if(sig=='l')
   {
    system("cls");
    start();
   }
 int f=0;
 rx *x;
 while(sig!=(char)27)
 {
  x=new rx(); /// Every time creating one object for each level, fr P1 nd P2;
  sig=getch();
  if(sig==(char)27)
    {
     x->quit();
     break;
    }

  if(f%2)
     x->lv_n++;
  x->disp();
  x->s=clock();
  sig=getch();
  while(sig!=(char)27)
  {
   x->_move(sig);
   if(x->c==0) /// to end a level after it's completion;
     {
      x->e=clock();
      f++;
      break;
     }
    sig=getch(); /// Signal
  }
  if(sig!=(char)27)
    {
     x->disp_scr();
     if(f%2)
        s_tym=x->tym; /// Saving P1's Completion Time
     else
        {
         sig=getch();
         x->win_levl();
        }
     svM_c=x->Mv_c; /// Saving P1's No. of Moves
    }
  else
     x->quit();

  delete x;
  while(sig=getch())
  {
   if(sig==(char)13||sig==(char)27)
      break;
  }
 }
return 0;
}
