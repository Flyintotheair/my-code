#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define MAX 100//最大玩家数
#define MAX_CHAR 10//控制输入字符的数量
#define EPS 1e-6

//玩家信息
typedef struct
{
    char playername[MAX_CHAR];//玩家游戏名
    char password[MAX_CHAR];//玩家密码
}Player;
//玩家排名
typedef struct
{
    char rankname[MAX_CHAR];
    int rankgrade;
}R;
typedef int Status;
//函数外的全局变量定义
char selection;//开始菜单的选项
int judge;//判断游戏是否结束
char game_leval;//判断游戏模式
int high, width;//画面的尺寸
int left, up;//控制画面的坐标
int position_x, position_y;//飞机的坐标
char planesize;//飞机的类型
int bullet_x[3], bullet_y[3];//子弹位置
int bullet_num;//子弹数量
int enemy_x[5], enemy_y[5];//敌机位置
int enemy_num;//敌机数量
int score;//游戏得分
int last;//飞走的敌机
int speed_max;//敌机速度
int s_m;//控制速度的一个参数
int score_max;//最大得分
int last_max;//最大失分
Player player;//玩家
Player P[MAX + 1];//用于存储所有用户
int total_player;//总玩家数
Player adm;//管理员
int on_line;//判断是否登录
R rank[MAX + 1];//排名

void HideCursor();//隐藏光标
void print_evaluate();//打印评价
void mainmenu();//菜单
void startup();//数据初始化
void Run_the_game();//运行游戏
void change_game_leval();//选择游戏内容
void selection_pattern();//选择模式
void selection_plane();//选择飞机
void show();//显示画面
Status print_plane(int i, int j);//输出飞机
Status print_bullet(int i, int j);//输出子弹
Status print_enemy(int i, int j);//输出敌机
void gotoxy(int x, int y);//光标移动到(x,y)位置
void ypdateWithoutInput();//与用户输入无关的更新
void updateWithInput();//与用户输入有关的更新
void endmenu();//结束菜单
void flash();//更新数据
void selectionSort(int n);//选择排序
void Rank();//输出玩家的成绩及自己的得分
void start_page();//登录页面
void TotalPlayer();//计算总玩家数
void Register();//注册
void Login();//登录
void Administrator();//管理员登录
void find(int p);//查找特定的信息
void _Login();//退出登录
Status Out_of_range(char str[]);//判断是否超出范围
void Evaluate();//评价函数

//主函数
int main ()
{
    on_line = 0;
    strcpy(adm.playername, "hacker");
    strcpy(adm.password, "bug");
    strcpy(player.playername, "游客");
    HideCursor();//隐藏光标
    puts("\n\n\n\n\n\n\n\n\n\n\t\t\t欢迎来到打飞机小游戏1.0正式版本(登录后丝滑单色彩)");
    print_evaluate();
    printf("\n\n\n\n\n\n\n\t\t\t\t\t\t");
    system("pause");
    system("cls");
    mainmenu();//菜单
    while(1)
    {
        system("cls");
        switch (selection)
        {
        case '1':
            startup(); //数据初始化
            Run_the_game();//运行游戏
            endmenu();//结束菜单
            if (on_line && game_leval == '1')
                flash();
            break;
        case '2':
            Rank();//输出玩家的成绩及自己的得分
            break;
        case '3':
            start_page();//登录页面
            break;
        case 0x1b:
            Evaluate();//评价函数
            puts("感谢你的游玩和评价！！！期待与你再次相遇！");
            return 0;

        default:
            break;
        }
        system("cls");
        mainmenu();//菜单
    }
    return 0;
}

//隐藏光标
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//打印评价
void print_evaluate()
{
    FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\evaluate.txt", "r");
    float good = 0, medium = 0, bad = 0;
    float sum;
    char elt;
    do
    {
        fscanf(fp, "%c\n", &elt);
        switch (elt)
        {
            case '1':  
                good += 1;
                break;
            case '2':
                medium += 1;
                break;
            case '3':
                bad += 1;
                break;
            default:
                break;
        }
    }while(!feof(fp));
    fclose(fp);
    sum = good + medium + bad + EPS;
    printf("\n\n\n                                 好评度%.2f%%                     差评度%.2f%%\n", good / sum * 100, bad / sum * 100);
    printf("\n\n\n总评价数为:%.0f", sum);
}

//菜单
void mainmenu()
{
    puts("-----------------------------------------------------------------------------------------------------------------------");
    printf("|你好！%s 请选择以下选项:\n", player.playername);
    puts("|                                                 主菜单                                                               |");
    puts("|                                                                                                                      |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                        1.玩游戏;                                               输入1                                 |");
    puts("|                        2.查看排名;                                             输入2                                 |");
    puts("|                        3.登录或注册或退出登录;                                 输入3                                 |");
    puts("|                                            登录可以改变颜色哦                                                        |");
    puts("|                     ***如果不登录会以游客身份开始游戏,将不会有成绩记录到排名***                                      |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                      退出游戏,输入ESC.                                                               |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    selection = getch();
}

//数据初始化
void startup()
{
    judge = 1;

    left = 30;
    up = 0;
    high = 20;
    width = 34;
    position_x = (high + up) / 2;
    position_y = (width + left) / 2;

    enemy_num = 5;
    for (int i = 0; i < enemy_num; ++i)
    {
        enemy_x[i] = up;
        enemy_y[i] = rand() * (i + 1) % width + 1 + left;
        if (enemy_y[i] == left)
        ++enemy_y[i];
        if (enemy_y[i] == width + left)
        --enemy_y[i];
    }

    score = 0;
    last = 0;
}

//运行游戏
void Run_the_game()
{
    change_game_leval();//改变敌机最大速度
    system("cls");
    while (1)
    {
        show(); //显示画面
        ypdateWithoutInput(); //与用户输入无关的更新
        if (judge)
        {
            updateWithInput(); //与用户输入有关的更新
            if (!judge)
            {
                judge = -1;
                return;
            }
        }
        else break;
    }
}

//选择游戏内容
void change_game_leval()
{
    for (int i = 0; i < bullet_num; ++i)
    {
        bullet_y[i] = -1;
        bullet_x[i] = 0;
    }
    selection_pattern();//选择模式
}

//选择模式
void selection_pattern()
{
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                                      选择模式                                                        |");
    puts("|                                     ***建议体验过常规模式了解操作后再尝试其他模式***                                 |");
    puts("|                                   ***当场上存在的敌人少于应该有的敌人时，敌人会合体***                               |");
    puts("|                                   ***有概率出现敌机合体现象,此时要射击三次才能击毁***                                |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                           1.常规模式(得分20获胜或失去5分,存在两架敌机);                    输入1                     |");
    puts("|                           2.自定义模式(得分不计入排名,可以自定义游戏属性);                 输入2                     |");
    puts("|                           3.禅模式(得分不计入排名，无限模式);                              输入3                     |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    game_leval = getch();
    while (1)
    {
        switch (game_leval)
        {
            case '1':
                system("cls");
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                                             WARNING!!!下面是操作！！！                                               |");
                puts("|                                                                                                                      |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                                           1.^*^是玩家飞机(一次双发).                                                 |");
                puts("|                                           2.$敌人飞机.                                                               |");
                puts("|                                           3.w,a,s,d控制前后左右方向.                                                 |");
                puts("|                                           4.空格发射子弹.                                                            |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                                结束条件1.如果得到20分或失去5分或与敌机相撞都会导致游戏结束.                          |");
                puts("|                                结束条件2.在游戏中输入ESC后退出.                                                      |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                system("pause");
                system("cls");
                planesize = '2';
                bullet_num = 2;
                speed_max = 25;
                score_max = 40;
                last_max = 5;
                s_m = 2;
                enemy_num = 3;
                return;
            case '2':
                system("cls");
                selection_plane();//选择飞机
                system("cls");
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                                                  自定义模式                                                          |");
                puts("|                                                                                                                      |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                printf("                            1.输入自定义最大速度(速度在正整数范围内,且数字越大速度越小):");
                scanf("%d", &speed_max);
                printf("                            2.输入自定义最大得分:");
                scanf("%d", &score_max);
                printf("                            3.输入自定义最大失分:");
                scanf("%d", &last_max);
                printf("                            4.请选择敌机数量(1~5):");
                scanf("%d", &enemy_num);
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                             结束条件1.如果得到最大得分或失去最大失分或与敌机相撞都会导致游戏结束.                    |");
                puts("|                             结束条件2.在游戏中输入ESC后退出.                                                        |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                for (int i = 0; i < enemy_num; ++i)//初始化敌机
                {
                    enemy_x[i] = up;
                    enemy_y[i] = rand() * (i + 1) % width + 1 + left;
                    if (enemy_y[i] == left)
                    ++enemy_y[i];
                    if (enemy_y[i] == width + left)
                    --enemy_y[i];
                }
                system("pause");
                return;
            case '3':
                system("cls");
                selection_plane();//选择飞机
                system("cls");
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                                                  禅(无限)模式                                                        |");
                puts("|                                                                                                                      |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                printf("                     1.输入禅模式速度(仅限整数(5, 10, 15, 20, 25),数字越大速度越小):");
                scanf("%d", &speed_max);
                printf("                     2.请选择敌机数量(1~5):");
                scanf("%d", &enemy_num);
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                                          结束条件.在游戏中输入ESC后退出.                                             |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                for (int i = 0; i < enemy_num; ++i)//初始化敌机
                {
                    enemy_x[i] = up;
                    enemy_y[i] = rand() * (i + 1) % width + 1 + left;
                    if (enemy_y[i] == left)
                    ++enemy_y[i];
                    if (enemy_y[i] == width + left)
                    --enemy_y[i];
                }
                score_max = -1;
                last = -1;
                system("pause");
                return;
            default:
                break;
        }
        game_leval = getch();
    }
}

//选择飞机
void selection_plane()
{
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                                   ***选择飞机***                                                     |");
    puts("|                                                                                                                      |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                           1.单发飞机(*^*);                              输入1                        |");
    puts("|                                           2.双发飞机(^*^);                              输入2                        |");
    puts("|                                           3.三发飞机(^^^);                              输入3                        |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    while (1)
    {
        planesize = getch();
        switch (planesize)
        {
        case '1':
            bullet_num = 1;
            return;
        case '2':
            bullet_num = 2;
            return;
        case '3':
            bullet_num = 3;
            return;
        default:
            break;
        }
    }
}

//显示画面
void show()
{
    int i, j, p;
    gotoxy(0, 0);//清屏
    for (i = 0; i <= high + up + 1; ++i)
    {
        for (j = 0; j <= width + left + 1; ++j)
        {
            if (p = print_plane(i, j))//输出飞机
            {
                j = p;
                continue;
            }
            if (print_bullet(i, j))//输出子弹
            continue;
            if (print_enemy(i, j))//输出敌机
            continue;
            if ((i == up - 1 || i == up + high) && (j > left - 1 && j < width + left + 1))
            {
                printf("-");
                continue;
            }
            if ((j == left - 1 || j == width + left + 1) && (i >= up - 1 && i <= up + high))
            {
                printf("|");
                continue;
            }
            printf(" ");//输出空格
        }
        puts("");
    }
    printf("                              得分 = %d\n", score);
    printf("                              失分 = %d\n", last);
    printf("                              应该有的敌人 = %d", enemy_num);
}

//输出飞机
Status print_plane(int i, int j)
{
    switch (planesize)
    {
    case '1'://飞机1号
        if (i == position_x && j == position_y)
        {
            printf("*^*");//输出飞机
            return j + 2;
        }
        break;
    case '2'://飞机2号
        if (i == position_x && j == position_y)
        {
            printf("^*^");//输出飞机
            return j + 2;
        }
        break;
    case '3'://飞机3号
        if (i == position_x && j == position_y)
        {
            printf("^^^");//输出飞机
            return j + 2;
        }
        break;
    }
    return 0;
}

//输出子弹
Status print_bullet(int i, int j)
{
    for (int p = 0; p < bullet_num; ++p)
    if (i == bullet_x[p] && j == bullet_y[p])
    {
        printf("|");//输出子弹
        return 1;
    }
    return 0;
}

//输出敌机
Status print_enemy(int i, int j)
{
    for(int p = 0; p < enemy_num; ++p)
    if (i == enemy_x[p] && j == enemy_y[p])
    {
        printf("$");//输入敌机
        return 1;
    }
    return 0;
}

//光标移动到(x,y)位置
void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

//与用户输入无关的更新
void ypdateWithoutInput()
{
    static int speed = 0;//控制敌机机速度
    for (int i = 0; i < enemy_num; ++i)
    {
        for (int j = 0; j < 3; ++j)//检测是否撞机
        if (position_y + j == enemy_y[i] && position_x == enemy_x[i])
        {
            judge = 0;
            return;
        }
        for (int j = 0; j < bullet_num; ++j)//检测子弹是否击中
        if (bullet_x[j] == enemy_x[i] && bullet_y[j] == enemy_y[i] || bullet_x[j] + 1 == enemy_x[i] && bullet_y[j] == enemy_y[i])
        {
            ++score;//得分增加
            switch (game_leval)
            {
                case '1':
                    if (!(score % s_m))
                    {
                        speed_max -= 1;
                        speed = 0;
                    }
                    if (score == score_max)
                    {
                        judge = 0;
                        return;
                    }
                    break;
                case '2':
                    if (score == score_max)
                    {
                        judge = 0;
                        return;
                    }
                    break;
                default:
                    break;
            }
            srand((unsigned)time(NULL));
            enemy_y[i] = rand() * (i + 1) % width + 1 + left;
            if (enemy_y[i] == left)
            ++enemy_y[i];
            if (enemy_y[i] == width + left)
            --enemy_y[i];
            enemy_x[i] = up;
            bullet_y[j] = -1;
        }
    }
    for (int p = 0; p < bullet_num; ++p)//子弹的前进
    if (bullet_x[p] > up - 1)
        --bullet_x[p];
    if (speed < speed_max)
        ++speed;
    if (speed == speed_max)//敌机前进
    {
        for (int i = 0; i < enemy_num; ++i)
        if (enemy_x[i] > high + up)//判断敌机是否飞走
        {
            srand((unsigned)time(NULL));
            enemy_y[i] = rand() * (i + 1) % width + left + 1;
            if (enemy_y[i] == left)
            ++enemy_y[i];
            if (enemy_y[i] == width + left)
            --enemy_y[i];
            enemy_x[i] = up;
            ++last;
            if (last == last_max)//判断是否因为满足last_max而退出
            {
                judge = 0;
                return;
            }
        }
        else
            ++enemy_x[i];
        speed = 0;
    }
}

//与用户输入有关的更新
void updateWithInput()
{
    char input;
    if (kbhit())//当按键时执行判断键入的字符
    {
        input = getch();
        if (input == 0x1b)//当输入ESC时退出
        {
            system("cls");
            judge = 0;
            return;
        }
        switch (input)//控制边界和发射子弹
        {
        case 'a'://左
            if (position_y != left)
            --position_y;
            break;
        case 'd'://右
            if (position_y != width - 2 + left)
            ++position_y;
            break;
        case 'w'://上
            if (position_x != up)
            --position_x;
            break;
        case 's'://下
            if (position_x != high - 1 + up)
            ++position_x;
            break;
        case ' '://发射子弹
            switch (bullet_num)
            {
            case 1:
                bullet_x[0] = position_x;
                bullet_y[0] = position_y + 1;
                break;
            case 2:
                for (int p = 0; p < bullet_num; ++p)
                {
                    bullet_x[p] = position_x;
                    bullet_y[p] = position_y + p * 2;
                }
                break;
            case 3:
                for (int p = 0; p < bullet_num; ++p)
                {
                    bullet_x[p] = position_x;
                    bullet_y[p] = position_y + p;
                }
                break;
            }
            break;
        default:
            break;
        }
    }
}

//结束菜单
void endmenu()
{
    system("cls");
    puts("-------------------------------------------------*****游戏结束*****-----------------------------------------------------");
    if (judge != -1)
    {
        printf("                                     得分 = %d                           失分 = %d\n", score, last);
        if (score_max != -1)
        if (score != score_max)
        puts("--------------------------------------------------*****失败*****-------------------------------------------------------");
        else
        puts("---------------------------------------------------*****胜利*****-------------------------------------------------------");
    }
    puts("|                                               输入ESC后返回主菜单.                                                  |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    while(1)
        if (getch() == 0x1b)
            break;
}

//更新数据
void flash()
{
    memset(rank, 0, sizeof(rank));
    FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_rank.txt", "r");
    char name[10];
    int grade, i, p = -1, n = 0;
    while(!feof(fp))//读入数据
    {
        fscanf(fp, "%s %d\n", name, &grade);
        strcpy(rank[n].rankname, name);
        if (!strcmp(name, player.playername)) 
        {
            p = i;
            n--;
        }
        else
            rank[n].rankgrade = grade;
        ++n;
    }
    fclose(fp);
    if (p != -1)
    {
        for (i = p; i < n - 1; ++i)
        {
            rank[i].rankgrade = rank[i + 1].rankgrade;
            strcpy(rank[i].rankname, rank[i + 1].rankname);
        }
    }
    rank[n].rankgrade = score;
    strcpy(rank[n].rankname, player.playername);
    selectionSort(n);//排名
    FILE *fq = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_rank.txt", "w+");
    for (i = 0; i <= n; ++i)//存入排名数据
        fprintf(fq, "%s\t%d\n", rank[i].rankname, rank[i].rankgrade);
    fclose(fq);
}

//选择排序
void selectionSort(int n)
{
    R rr;
    rr.rankgrade = rank[n].rankgrade;
    strcpy(rr.rankname, rank[n].rankname);
    for(int i = 0; i < n; ++i)//标记
    {
        if(rank[i].rankgrade < rank[n].rankgrade)
        {
            for (int j = n; j > i; --j)
            {
                rank[j].rankgrade = rank[j - 1].rankgrade;
                strcpy(rank[j].rankname, rank[j - 1].rankname);
            }
            rank[i].rankgrade = rr.rankgrade;
            strcpy(rank[i].rankname, rr.rankname);
            break;
        }
    }
}

//输出玩家的成绩及自己的得分
void Rank()
{
    FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_rank.txt", "r");
    char name[MAX_CHAR], ch;
    int grade, i = 1;
    puts("----------------------------------------------------常规模式排名-------------------------------------------------------");
    do //输出排名
    {
        fscanf(fp, "%s%d\n", name, &grade);
        printf("         排名: %d,   用户名: %-10s,   历史得分: %d\n\n", i, name, grade);
        ++i;
    }while (!feof(fp));
    fclose(fp);
    printf("         %s当前的成绩: %d\n", player.playername, score);//输出当前用户的成绩
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                       输入ESC后退出到主菜单,或输入f查找用户排名.                                    |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    while (1)
    {
        ch = getch();
        if (ch == 0x1b)
            break;
        else if (ch == 'f')
        {
            find(1);
            break;
        }
    }
}

//登录页面
void start_page()
{
    system("cls");
    TotalPlayer();
    puts("-----------------------------------------------------------------------------------------------------------------------");
    printf("|当前共有 %d 个用户已创建了账号.你好！%s 请选择以下选项:\n", total_player, player.playername);
    puts("|                                                 登录菜单                                                             |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                        1.如果你有账号并想要登录;                                   输入1                             |");
    puts("|                        2.进行免费的注册;                                           输入2                             |");
    puts("|                        3.管理员登录;                                               输入3                             |");
    puts("|                        4.退出登录;                                                 输入0                             |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                      退回主菜单,输入ESC.                                                             |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    while (1)
    {
        switch (getch())
        {
            case '1':
                Login();
                return;
            case '2':
                Register();
                start_page();//返回登录页面
                return;
            case '3':
                Administrator();
                start_page();//返回登录页面
                return;
            case '0':
                _Login();
                return;
            case 0x1b:
                return;
            default:
                break;
        }
    }
}

//计算总玩家数
void TotalPlayer()
{
    total_player = 0;
    char name[10], password[10];
    FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_information.txt", "r");
    while (!feof(fp))
    {
        fscanf(fp, "%s%s\n", name, password);
        ++total_player;
    }
    fclose(fp);
}

//注册
void Register()
{
    FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_information.txt", "a+");
    char name[MAX_CHAR], password[MAX_CHAR];
    while(1)
    {   
        system("cls");
        printf("1.输入你的名字(最大可以有9个字符或4个汉字):");
        scanf("%s", name);
        if (Out_of_range(name))
            break;
        else
        {
            puts("-------------------------------------------WARNING!你的输出超限,请重新输入---------------------------------------------");
            system("pause");
        }
    }
    while(!feof(fp)) //检测是否有重名
    {
        fscanf(fp, "%s%s\n", player.playername, player.password);
        if (!strcmp(name, player.playername))
            while(1)
            {   
                system("cls");
                puts("----------------------------------------------WARNING!这个用户名已存在!------------------------------------------------");
                printf("1.再次输入你的名字(最大可以有9个字符或4个汉字):");
                scanf("%s", name);
                if (Out_of_range(name))
                    break;
                else
                {
                    puts("-------------------------------------------WARNING!你的输出超限,请重新输入---------------------------------------------");
                }
            }
    }
    strcpy(player.playername, name);
    while (1)//检测两次输入的密码是否相同
    {
        while(1)
        {   
            system("cls");
            printf("1.输入你的名字(最大可以有9个字符或4个汉字):%s\n", player.playername);
            printf("2.这个名字是有效的,输入你的密码(最大可以有9个字符或4个汉字):");
            scanf("%s", password);
            if (Out_of_range(password))
                break;
            else
            {
                puts("-------------------------------------------WARNING!你的输出超限,请重新输入---------------------------------------------");
                system("pause");
            }
        }
        strcpy(player.password, password);
        printf("3.再次输入你的密码(最大可以有9个字符或4个汉字):");
        scanf("%s", password);
        if (!strcmp(password, player.password))
            break;
        else
        {
            puts("WARNING!你两次输入的密码不一样,按任意键后重新输入.");
            system("pause");
            system("cls");
        }
    }
    printf("                                            你的用户名:%s\n", player.playername);
    printf("                                            你的密码:%s\n", player.password);
    puts("-----------------------------------------------------------------------------------------------------------------------");
        puts("|                                 账户一旦创建,不能修改和删除，如有必要联系管理员操作                                 |");
    puts("|                                        你已经成功创建了一个账号,快去登录吧!!!                                       |");
    puts("|                                             输入ESC后返回登录页面.                                                  |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    fprintf(fp, "%s\t%s\n", player.playername, player.password);
    fclose(fp);
    strcpy(player.playername, "游客");//没有登陆都是游客身份
    while (1)
        if (getch() == 0x1b)
            break;
}

//登录
void Login()
{
    char name[MAX_CHAR], password[MAX_CHAR];
    system("cls");
    while (1)
    {
        puts("------------------------------------------------------------------------------------------------------------------------");
        puts("|                                   tips:如果你想要退出选择ESC,否则按任意键继续登录.                                  |");
        puts("------------------------------------------------------------------------------------------------------------------------");
        if (getch() == 0x1b)
            return;
        else
        {
            while(1)
            {
                system("cls");
                printf("                                    1.输入用户名:");
                scanf("%s", name);
                if (Out_of_range(name))
                    break;
                else
                {
                    puts("-------------------------------------------WARNING!你的输出超限,请重新输入---------------------------------------------");
                    system("pause");
                }
            }
            strcpy(player.playername, name);
            while(1)
            {
                system("cls");
                printf("                                    1.输入用户名:%s\n", player.playername);
                printf("                                    2.输入密码:");
                scanf("%s", password);
                if (Out_of_range(password))
                    break;
                else
                {
                    puts("-------------------------------------------WARNING!你的输出超限,请重新输入---------------------------------------------");
                    system("pause");
                }
            }
            strcpy(player.password, password);
            system("cls");
            FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_information.txt", "r");
            while(!feof(fp))
            {
                fscanf(fp, "%s %s", name, password);
                if (!strcmp(name, player.playername) && !strcmp(password, player.password))
                {
                    on_line = 1;
                    score = 0;
                    puts("------------------------------------------------------登录成功---------------------------------------------------------");
                    puts("|                                                 变蓝色       输入1                                                  |");
                    puts("|                                                                                                                     |");
                    puts("|                                                 不变色       输入其他键                                             |");
                    puts("-----------------------------------------------------------------------------------------------------------------------");
                    if (getch() == '1')
                        system("color 03");
                    return;
                }
            }
            fclose(fp);
        }
        puts("-------------------------------------------WARNING!你的用户名或密码是错误的--------------------------------------------");
        puts("-----------------------------------------------------重新输入！--------------------------------------------------------");
        strcpy(player.playername, "游客");
    }
}

//管理员登录
void Administrator()
{
    char name[MAX_CHAR], password[MAX_CHAR];
    if (strcmp(player.playername, "管理员"))
    while(1)
    {
        system("cls");
        puts("*****************************************************管理员登录********************************************************\n");
        printf("                                    1.输入管理员名字:");
        scanf("%s", name);
        printf("                                    2.输入管理员密码:");
        scanf("%s", password);
        if (!strcmp(name, adm.playername) && !strcmp(password, adm.password))
        {
            score = 0;
            puts("************************************你已经成功登录管理员,将以管理员身份更改用户信息.***********************************");
            puts("------------------------------------------------------登录成功---------------------------------------------------------");
            puts("|                                                 变金色       输入1                                                  |");
            puts("|                                                                                                                     |");
            puts("|                                                 不变色       输入其他键                                             |");
            puts("-----------------------------------------------------------------------------------------------------------------------");
            if (getch() == '1')
                system("color 06");
            strcpy(player.playername, "管理员");
            break;
        }
        else
        {
            puts("-------------------------------------------WARNING!你的用户名或密码是错误的--------------------------------------------");
            puts("|                                    输入ESC退回登录页面,或输入其他键再次尝试登录.                                    |");
            puts("-----------------------------------------------------------------------------------------------------------------------");
            if (getch() == 0x1b)
                return;
        }
    }
    else system("cls");
    int p = 0, i;
    FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\hello.txt", "r");
    while(!feof(fp))
    {
        fscanf(fp, "%s%s\n", P[p].playername, P[p].password);
        printf("                             序号: %d,   用户名: %-10s,   成绩: %-10s\n", p + 1, P[p].playername, P[p].password);
        ++p;
    }
    fclose(fp);
    system("pause");
    while(p)
    {
        int t = 0;
        puts("-----------------------------------------------------------------------------------------------------------------------");
        puts("|你好！管理员 请选择以下选项:                                                                                         |");
        puts("|                                                管理员菜单                                                           |");
        puts("|                                                                                                                     |");
        puts("-----------------------------------------------------------------------------------------------------------------------");
        puts("|                        1.修改用户信息;                                          输入1                               |");
        puts("|                        2.删除用户信息;                                          输入2                               |");
        puts("|                        3.增加用户信息;                                          输入3                               |");
        puts("|                        4.查找用户信息;                                          输入4                               |");
        puts("|                                                                                                                     |");
        puts("-----------------------------------------------------------------------------------------------------------------------");
        puts("|                                            退出游戏,输入ESC.                                                        |");
        puts("-----------------------------------------------------------------------------------------------------------------------");
        switch (getch())
        {
            case '1':
                system("cls");
                puts("************************************************修改用户信息***********************************************************");
                printf("                         1.修改用户的序号:");
                scanf("%d", &t);
                printf("                         2.修改后第%d个用户的用户名:", t);
                scanf("%s", name);
                printf("                         3.修改后第%d个用户的密码:", t);
                scanf("%s", password);
                strcpy(P[t - 1].playername, name);
                strcpy(P[t - 1].password, password);
                t = 1;
                break;
            case '2':
                system("cls");
                puts("************************************************删除用户信息***********************************************************");
                printf("                         删除用户的序号:");
                scanf("%d", &t);
                for (i = t; i < p; ++i)
                {
                    strcpy(P[i - 1].playername, P[i].playername);
                    strcpy(P[i - 1].password, P[i].password);
                }
                --p;
                t = 1;
                break;
            case '3':
                int sum;
                system("cls");
                puts("************************************************增加用户信息***********************************************************");
                printf("                         增加用户的数量:");
                scanf("%d", &sum);
                for (i = p; i - p < sum; i++)
                {
                    printf("                         增加的第%d个用户的用户名:", i - p + 1);
                    scanf("%s", name);
                    printf("                         增加的第%d个用户的密码:", i - p + 1);
                    scanf("%s", password);
                    strcpy(P[i].playername, name);
                    strcpy(P[i].password, password);
                }
                p = i;
                t = 1;
                break;
            case '4':
                find(0);
                break;
            case 0x1b:
                while(1)
                {
                    system("cls");
                    puts("***************************************************WARNING!************************************************************");
                    puts("|                  是否将更改的数据保存,如是则原来的数据改为更改后的,如不是则原来的数据不发生改变.                    |");
                    puts("|                              请输入: 'Y'/'y'(代表是) 或者 'N'/'n'(代表否).                                          |");
                    puts("-----------------------------------------------------------------------------------------------------------------------");
                    i = 0;
                    char ch;
                    fclose(fp);
                    ch = getch();
                    if (ch == 'y' || ch == 'Y')
                    {
                        FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\hello.txt", "r");
                        FILE *fq = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_information.txt", "w");
                        while(!feof(fp))
                        {
                            fscanf(fp, "%s%s\n", P[i].playername, P[i].password);
                            printf("                             序号: %d,   用户名: %-10s,   成绩: %-10s\n", i + 1, P[i].playername, P[i].password);
                            fprintf(fq, "%s\t%s\n", P[i].playername, P[i].password);
                            ++i;
                        }
                        fclose(fp);
                        fclose(fq);        
                        puts("*************************************************数据已更改!***********************************************************");
                        system("pause");
                        return;
                    }
                    else if (ch == 'N' || ch == 'n')
                    {
                        FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\hello.txt", "w");
                        FILE *fq = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_information.txt", "r");
                        while(!feof(fq))
                        {
                            fscanf(fq, "%s%s\n", P[i].playername, P[i].password);
                            printf("                             序号: %d,   用户名: %-10s,   成绩: %-10s\n", i + 1, P[i].playername, P[i].password);
                            fprintf(fp, "%s\t%s\n", P[i].playername, P[i].password);
                            ++i;
                        }
                        fclose(fp);
                        fclose(fq);
                        puts("***********************************************数据未发生更改!*********************************************************");
                        system("pause");
                        return;
                    }              
                }
            default:
                system("cls");
                t = 1;
                break;
        }
        if (t)
        {
            FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\hello.txt", "w");
            for (i = 0; i < p; ++i)
            {
                fprintf(fp, "%s\t%s\n", P[i].playername, P[i].password);
                printf("                             序号: %d,   用户名: %-10s,   成绩: %-10s\n", i + 1, P[i].playername, P[i].password);
            }
            fclose(fp);
        }
    }
}

//查找特定的信息
void find(int p)
{
    char _name[10];
    while(1)
    {
        system("cls");
        int t = 0;
        puts("-----------------------------------------------------------------------------------------------------------------------");
        printf("                输入查找的人的用户名:");
        scanf("%s", _name);
        if (p)
        {
            FILE *fp = fopen ("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_rank.txt", "r");
            char name[10];
            int grade, i = 1;
            while (!feof(fp))
            {
                fscanf(fp, "%s%d\n", name, &grade);
                if (!strcmp(name, _name))
                {
                    t = 1;
                    break;
                }
                ++i;
            }
            if (t)
                printf("                             用户名: %-10s,   成绩: %d,   排名: %d\n", name, grade, i);
            else
                puts("|                                                  没有找到该用户!                                                    |");
            puts("-----------------------------------------------------------------------------------------------------------------------");
            puts("|                                       输入ESC后退出到主菜单,或输入其他键继续.                                       |");
            puts("-----------------------------------------------------------------------------------------------------------------------");
            fclose(fp);
            if (getch() == 0x1b)
                return;
        }
        else
        {
            FILE *fp = fopen ("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_information.txt", "r");
            char name[10], password[10];
            while (!feof(fp))
            {
                fscanf(fp, "%s%s\n", name, password);
                if (!strcmp(name, _name))
                {
                    t = 1;
                    break;
                }
            }
            if (t)
                printf("          用户名:%-10s,   密码:%s\n", name, password);
            else
                puts("|                                                  没有找到该用户!                                                    |");
            puts("-----------------------------------------------------------------------------------------------------------------------");
            puts("|                                       输入ESC后退出到主菜单,或输入其他键继续.                                    |");
            puts("-----------------------------------------------------------------------------------------------------------------------");
            fclose(fp);
            if (getch() == 0x1b)
                return;
        }
        
    }
}

//退出登录
void _Login()
{
    system("color 07");
    on_line = 0;
    score = 0;
    strcpy(player.playername, "游客");
}

//判断是否超出范围
Status Out_of_range(char str[])
{
    int p = MAX_CHAR;
    while (p--)
    {
        if (str[p] == '\000')
        return 1;
    }
    return 0;
}

//评价函数
void Evaluate()
{
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                              对该程序的体验如何?                                                    |");
    puts("|                                             请选择下面的一种评价.                                                   |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                            o(￣▽￣)ｄ(好评)            输入1                                       |");
    puts("|                                                                                                                     |");
    puts("|                                            (ˉ▽￣～) 切~~)(中评)       输入2                                       |");
    puts("|                                                                                                                     |");
    puts("|                                            X﹏X(差评)                   输入3                                       |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                              直接退出游戏,输入ESC.                                                  |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\evaluate.txt", "a+");
    while(1)
    {
        switch (getch())
        {
            case '1':
                puts("\n                                         Hi~ o(*￣▽￣*)ブ(感谢!!!)");
                fprintf(fp, "1\n");
                fclose(fp);
                return;
            case '2':
                puts("\n                                              (⊙﹏⊙)(好吧~)");
                fprintf(fp, "2\n");
                fclose(fp);
                return;
            case '3':
                puts("\n                                           ○|￣|_(会继续努力的!)");
                fprintf(fp, "3\n");
                fclose(fp);
                return;
            case 0x1b:
                fclose(fp);
                return;
            default:
                break;
        }
    }
}