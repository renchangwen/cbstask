#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <conio.h>
#define N 25
using namespace std;
int x1=0,y1=0;
long start;
int gameover;
int x,y;
class snake_position//铔囦綅缃?
{
    public:
     int x=1,y=4;
    snake_position(){};
};
 snake_position position[(N-2)*(N-2)+1];
class snake_map//妫嬬洏
{
    private:
    char s[N][N];//妫嬬洏锛屽寘鎷澹?
    int grade,length;//绛夌骇
    int gamespeed;//时间间隔
    char direction;//鏂瑰悜
    int head,tail;
    int record=0;
    int score;//鍒嗘暟
    public:
    snake_map()
    {
        length=4;
        direction='d';
        head=4;
        tail=1;
        score=0;
    }
    void intialize();//鍒濆鍦板浘
    void show_game();
    int up_game();
    void setpoint();
    void getgrade();
    void display();
};

void snake_map::intialize()
{
    int i,j;
    for(i=1;i<=N-2;i++)
    for(j=1;j<=N-2;j++)
    s[i][j]=' ';
    // for(i=1;i<=3;i++)
    // s[1][i]='*';
    // s[1][4]='#';
    for(i=0;i<=N-1;i++)
    {s[i][0]='+'; s[i][N-1]='+';}
    for(i=0;i<=N-1;i++)
    {s[0][i]='+'; s[N-1][i]='+';}
    // for(i=0;i<=N-1;i++)//娴嬭瘯鍦板浘鍒濆鍖栨垚鍔?,test1
    // for(j=0;j<=N-1;j++)
    // {cout<<s[i][j];
    // if(j==N-1) cout<<endl;
    // }
}
void snake_map::getgrade()
{
    int grade=3;
    cin>>grade;
    while(grade<1||grade>6)
    {
        cout<<"输入等级"<<endl;
        cin>>grade;
    }
    switch(grade)
    {
        case 1:gamespeed=1000;break;
        case 2:gamespeed=800;break;
        case 3:gamespeed=600;break;
        case 4:gamespeed=400;break;
        case 5:gamespeed=200;break;
        case 6:gamespeed=100;break;
    }
}
void snake_map::show_game()//
{
    system("cls");
    cout<<"游戏开始。。。"<<endl;
    int i,j;
    for(i=0;i<N;i++)
    {
        // cout<<'\t';
        for(j=0;j<N;j++)
        {
        cout<<s[i][j]<<' ';
        if(j==N-1) cout<<endl;
        }
    }
    cout<<endl;
}

void snake_map::setpoint()
{
    srand(time(0));
    do
    {
    x1=rand()%(N-2)+1;
    y1=rand()%(N-2)+1;
    } while(s[x1][y1]!=' ');
    s[x1][y1]='*'; 
}

int snake_map::up_game()
{
    gameover=1;
    start=clock();
    while((gameover==(clock()-start<=gamespeed))&&!kbhit()) {};
    int key=direction;
    if(gameover)
    {
         key=getch();
    }
    if(key==' ') 
    while(key==' ') key=getch();
    else{
        direction=key;
        switch(direction)
        {
            case 'a': ::x=position[head].x; ::y=position[head].y-1;break;
            case 'd': ::x=position[head].x; ::y=position[head].y+1;break;
            case 's': ::x=position[head].x+1; ::y=position[head].y;break;
            case 'w': ::x=position[head].x-1; ::y=position[head].y;break;
        }
    }
    if((::x==0)||(::x==N-1)||(::y==0)||(::y==N-1))
    gameover=0;
    else if(s[::x][::y]!=' '&&!(::x==x1&&::y==y1))
    gameover=0;
    else if(::x==x1&&::y==y1){//吃米
        length++;
        if(length>=8)
        {
            length-=8;
            grade++;
            if(gamespeed>=200) 
            gamespeed-=200;
            else
            gamespeed=100;
        }
    
        //     switch(direction)
        // {
        //     case 'a': 
        //     // s[position[head].x][position[head].y-1]='#';
        //     ::y-=1;break;
        //     case 'd': 
        //     // s[position[head].x][position[head].y+1]='#';
        //     ::y+=1;break;
        //     case 's': 
        //     // s[position[head].x+1][position[head].y]='#';
        //     ::x+=1;break;
        //     case 'w': 
        //     // s[position[head].x-1][position[head].y]='#';
        //     ::x-=1;break;
        // }
    s[position[head].x][position[head].y]='*';
    head=head+1;
     position[head].x =::x;
     position[head].y =::y;
    show_game();
    gameover=1;
    score+=grade*1;
    if(snake_map::score>record)
    {
        record=score;
    }
    setpoint();
    }
    else
    {//不吃米
        s[position[tail].x][position[tail].y]=' ';
        tail=tail+1;
        s[position[head].x][position[head].y]='*';
        head=head+1;
           position[head].x =::x;
            position[head].y =::y;
            s[position[head].x][position[head].y]='#'; //更新蛇头
            gameover = 1; 
    }
    return gameover;
}

int main()
{
//    snake_map test1;
//     test1.intialize();//鍦板浘鍒濆鍖栨垚鍔燂紝test1
char ctn='y';
cout<<"按'y'继续"<<endl;
int gg=getch();


while(ctn==gg)
{
    system("cls");
    snake_map snake;
    snake.intialize();
    cout<<"选择游戏等级";
    snake.getgrade();
    int nodead=0;
    snake.setpoint();
    do
    {
        snake.show_game();
        nodead=snake.up_game();
    } while (nodead);
    system("cls");
    cout<<"按y继续,按其余键退出"<<endl;
    cin>>ctn;    
}
}