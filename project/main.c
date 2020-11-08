#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define MAX 100//��������
#define MAX_CHAR 10//���������ַ�������
#define EPS 1e-6

//�����Ϣ
typedef struct
{
    char playername[MAX_CHAR];//�����Ϸ��
    char password[MAX_CHAR];//�������
}Player;
//�������
typedef struct
{
    char rankname[MAX_CHAR];
    int rankgrade;
}R;
typedef int Status;
//�������ȫ�ֱ�������
char selection;//��ʼ�˵���ѡ��
int judge;//�ж���Ϸ�Ƿ����
char game_leval;//�ж���Ϸģʽ
int high, width;//����ĳߴ�
int left, up;//���ƻ��������
int position_x, position_y;//�ɻ�������
char planesize;//�ɻ�������
int bullet_x[3], bullet_y[3];//�ӵ�λ��
int bullet_num;//�ӵ�����
int enemy_x[5], enemy_y[5];//�л�λ��
int enemy_num;//�л�����
int score;//��Ϸ�÷�
int last;//���ߵĵл�
int speed_max;//�л��ٶ�
int s_m;//�����ٶȵ�һ������
int score_max;//���÷�
int last_max;//���ʧ��
Player player;//���
Player P[MAX + 1];//���ڴ洢�����û�
int total_player;//�������
Player adm;//����Ա
int on_line;//�ж��Ƿ��¼
R rank[MAX + 1];//����

void HideCursor();//���ع��
void print_evaluate();//��ӡ����
void mainmenu();//�˵�
void startup();//���ݳ�ʼ��
void Run_the_game();//������Ϸ
void change_game_leval();//ѡ����Ϸ����
void selection_pattern();//ѡ��ģʽ
void selection_plane();//ѡ��ɻ�
void show();//��ʾ����
Status print_plane(int i, int j);//����ɻ�
Status print_bullet(int i, int j);//����ӵ�
Status print_enemy(int i, int j);//����л�
void gotoxy(int x, int y);//����ƶ���(x,y)λ��
void ypdateWithoutInput();//���û������޹صĸ���
void updateWithInput();//���û������йصĸ���
void endmenu();//�����˵�
void flash();//��������
void selectionSort(int n);//ѡ������
void Rank();//�����ҵĳɼ����Լ��ĵ÷�
void start_page();//��¼ҳ��
void TotalPlayer();//�����������
void Register();//ע��
void Login();//��¼
void Administrator();//����Ա��¼
void find(int p);//�����ض�����Ϣ
void _Login();//�˳���¼
Status Out_of_range(char str[]);//�ж��Ƿ񳬳���Χ
void Evaluate();//���ۺ���

//������
int main ()
{
    on_line = 0;
    strcpy(adm.playername, "hacker");
    strcpy(adm.password, "bug");
    strcpy(player.playername, "�ο�");
    HideCursor();//���ع��
    puts("\n\n\n\n\n\n\n\n\n\n\t\t\t��ӭ������ɻ�С��Ϸ1.0��ʽ�汾(��¼��˿����ɫ��)");
    print_evaluate();
    printf("\n\n\n\n\n\n\n\t\t\t\t\t\t");
    system("pause");
    system("cls");
    mainmenu();//�˵�
    while(1)
    {
        system("cls");
        switch (selection)
        {
        case '1':
            startup(); //���ݳ�ʼ��
            Run_the_game();//������Ϸ
            endmenu();//�����˵�
            if (on_line && game_leval == '1')
                flash();
            break;
        case '2':
            Rank();//�����ҵĳɼ����Լ��ĵ÷�
            break;
        case '3':
            start_page();//��¼ҳ��
            break;
        case 0x1b:
            Evaluate();//���ۺ���
            puts("��л�����������ۣ������ڴ������ٴ�������");
            return 0;

        default:
            break;
        }
        system("cls");
        mainmenu();//�˵�
    }
    return 0;
}

//���ع��
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//��ӡ����
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
    printf("\n\n\n                                 ������%.2f%%                     ������%.2f%%\n", good / sum * 100, bad / sum * 100);
    printf("\n\n\n��������Ϊ:%.0f", sum);
}

//�˵�
void mainmenu()
{
    puts("-----------------------------------------------------------------------------------------------------------------------");
    printf("|��ã�%s ��ѡ������ѡ��:\n", player.playername);
    puts("|                                                 ���˵�                                                               |");
    puts("|                                                                                                                      |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                        1.����Ϸ;                                               ����1                                 |");
    puts("|                        2.�鿴����;                                             ����2                                 |");
    puts("|                        3.��¼��ע����˳���¼;                                 ����3                                 |");
    puts("|                                            ��¼���Ըı���ɫŶ                                                        |");
    puts("|                     ***�������¼�����ο���ݿ�ʼ��Ϸ,�������гɼ���¼������***                                      |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                      �˳���Ϸ,����ESC.                                                               |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    selection = getch();
}

//���ݳ�ʼ��
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

//������Ϸ
void Run_the_game()
{
    change_game_leval();//�ı�л�����ٶ�
    system("cls");
    while (1)
    {
        show(); //��ʾ����
        ypdateWithoutInput(); //���û������޹صĸ���
        if (judge)
        {
            updateWithInput(); //���û������йصĸ���
            if (!judge)
            {
                judge = -1;
                return;
            }
        }
        else break;
    }
}

//ѡ����Ϸ����
void change_game_leval()
{
    for (int i = 0; i < bullet_num; ++i)
    {
        bullet_y[i] = -1;
        bullet_x[i] = 0;
    }
    selection_pattern();//ѡ��ģʽ
}

//ѡ��ģʽ
void selection_pattern()
{
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                                      ѡ��ģʽ                                                        |");
    puts("|                                     ***�������������ģʽ�˽�������ٳ�������ģʽ***                                 |");
    puts("|                                   ***�����ϴ��ڵĵ�������Ӧ���еĵ���ʱ�����˻����***                               |");
    puts("|                                   ***�и��ʳ��ֵл���������,��ʱҪ������β��ܻ���***                                |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                           1.����ģʽ(�÷�20��ʤ��ʧȥ5��,�������ܵл�);                    ����1                     |");
    puts("|                           2.�Զ���ģʽ(�÷ֲ���������,�����Զ�����Ϸ����);                 ����2                     |");
    puts("|                           3.��ģʽ(�÷ֲ���������������ģʽ);                              ����3                     |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    game_leval = getch();
    while (1)
    {
        switch (game_leval)
        {
            case '1':
                system("cls");
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                                             WARNING!!!�����ǲ���������                                               |");
                puts("|                                                                                                                      |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                                           1.^*^����ҷɻ�(һ��˫��).                                                 |");
                puts("|                                           2.$���˷ɻ�.                                                               |");
                puts("|                                           3.w,a,s,d����ǰ�����ҷ���.                                                 |");
                puts("|                                           4.�ո����ӵ�.                                                            |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                                ��������1.����õ�20�ֻ�ʧȥ5�ֻ���л���ײ���ᵼ����Ϸ����.                          |");
                puts("|                                ��������2.����Ϸ������ESC���˳�.                                                      |");
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
                selection_plane();//ѡ��ɻ�
                system("cls");
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                                                  �Զ���ģʽ                                                          |");
                puts("|                                                                                                                      |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                printf("                            1.�����Զ�������ٶ�(�ٶ�����������Χ��,������Խ���ٶ�ԽС):");
                scanf("%d", &speed_max);
                printf("                            2.�����Զ������÷�:");
                scanf("%d", &score_max);
                printf("                            3.�����Զ������ʧ��:");
                scanf("%d", &last_max);
                printf("                            4.��ѡ��л�����(1~5):");
                scanf("%d", &enemy_num);
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                             ��������1.����õ����÷ֻ�ʧȥ���ʧ�ֻ���л���ײ���ᵼ����Ϸ����.                    |");
                puts("|                             ��������2.����Ϸ������ESC���˳�.                                                        |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                for (int i = 0; i < enemy_num; ++i)//��ʼ���л�
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
                selection_plane();//ѡ��ɻ�
                system("cls");
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                                                  ��(����)ģʽ                                                        |");
                puts("|                                                                                                                      |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                printf("                     1.������ģʽ�ٶ�(��������(5, 10, 15, 20, 25),����Խ���ٶ�ԽС):");
                scanf("%d", &speed_max);
                printf("                     2.��ѡ��л�����(1~5):");
                scanf("%d", &enemy_num);
                puts("------------------------------------------------------------------------------------------------------------------------");
                puts("|                                          ��������.����Ϸ������ESC���˳�.                                             |");
                puts("------------------------------------------------------------------------------------------------------------------------");
                for (int i = 0; i < enemy_num; ++i)//��ʼ���л�
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

//ѡ��ɻ�
void selection_plane()
{
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                                   ***ѡ��ɻ�***                                                     |");
    puts("|                                                                                                                      |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                           1.�����ɻ�(*^*);                              ����1                        |");
    puts("|                                           2.˫���ɻ�(^*^);                              ����2                        |");
    puts("|                                           3.�����ɻ�(^^^);                              ����3                        |");
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

//��ʾ����
void show()
{
    int i, j, p;
    gotoxy(0, 0);//����
    for (i = 0; i <= high + up + 1; ++i)
    {
        for (j = 0; j <= width + left + 1; ++j)
        {
            if (p = print_plane(i, j))//����ɻ�
            {
                j = p;
                continue;
            }
            if (print_bullet(i, j))//����ӵ�
            continue;
            if (print_enemy(i, j))//����л�
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
            printf(" ");//����ո�
        }
        puts("");
    }
    printf("                              �÷� = %d\n", score);
    printf("                              ʧ�� = %d\n", last);
    printf("                              Ӧ���еĵ��� = %d", enemy_num);
}

//����ɻ�
Status print_plane(int i, int j)
{
    switch (planesize)
    {
    case '1'://�ɻ�1��
        if (i == position_x && j == position_y)
        {
            printf("*^*");//����ɻ�
            return j + 2;
        }
        break;
    case '2'://�ɻ�2��
        if (i == position_x && j == position_y)
        {
            printf("^*^");//����ɻ�
            return j + 2;
        }
        break;
    case '3'://�ɻ�3��
        if (i == position_x && j == position_y)
        {
            printf("^^^");//����ɻ�
            return j + 2;
        }
        break;
    }
    return 0;
}

//����ӵ�
Status print_bullet(int i, int j)
{
    for (int p = 0; p < bullet_num; ++p)
    if (i == bullet_x[p] && j == bullet_y[p])
    {
        printf("|");//����ӵ�
        return 1;
    }
    return 0;
}

//����л�
Status print_enemy(int i, int j)
{
    for(int p = 0; p < enemy_num; ++p)
    if (i == enemy_x[p] && j == enemy_y[p])
    {
        printf("$");//����л�
        return 1;
    }
    return 0;
}

//����ƶ���(x,y)λ��
void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

//���û������޹صĸ���
void ypdateWithoutInput()
{
    static int speed = 0;//���Ƶл����ٶ�
    for (int i = 0; i < enemy_num; ++i)
    {
        for (int j = 0; j < 3; ++j)//����Ƿ�ײ��
        if (position_y + j == enemy_y[i] && position_x == enemy_x[i])
        {
            judge = 0;
            return;
        }
        for (int j = 0; j < bullet_num; ++j)//����ӵ��Ƿ����
        if (bullet_x[j] == enemy_x[i] && bullet_y[j] == enemy_y[i] || bullet_x[j] + 1 == enemy_x[i] && bullet_y[j] == enemy_y[i])
        {
            ++score;//�÷�����
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
    for (int p = 0; p < bullet_num; ++p)//�ӵ���ǰ��
    if (bullet_x[p] > up - 1)
        --bullet_x[p];
    if (speed < speed_max)
        ++speed;
    if (speed == speed_max)//�л�ǰ��
    {
        for (int i = 0; i < enemy_num; ++i)
        if (enemy_x[i] > high + up)//�жϵл��Ƿ����
        {
            srand((unsigned)time(NULL));
            enemy_y[i] = rand() * (i + 1) % width + left + 1;
            if (enemy_y[i] == left)
            ++enemy_y[i];
            if (enemy_y[i] == width + left)
            --enemy_y[i];
            enemy_x[i] = up;
            ++last;
            if (last == last_max)//�ж��Ƿ���Ϊ����last_max���˳�
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

//���û������йصĸ���
void updateWithInput()
{
    char input;
    if (kbhit())//������ʱִ���жϼ�����ַ�
    {
        input = getch();
        if (input == 0x1b)//������ESCʱ�˳�
        {
            system("cls");
            judge = 0;
            return;
        }
        switch (input)//���Ʊ߽�ͷ����ӵ�
        {
        case 'a'://��
            if (position_y != left)
            --position_y;
            break;
        case 'd'://��
            if (position_y != width - 2 + left)
            ++position_y;
            break;
        case 'w'://��
            if (position_x != up)
            --position_x;
            break;
        case 's'://��
            if (position_x != high - 1 + up)
            ++position_x;
            break;
        case ' '://�����ӵ�
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

//�����˵�
void endmenu()
{
    system("cls");
    puts("-------------------------------------------------*****��Ϸ����*****-----------------------------------------------------");
    if (judge != -1)
    {
        printf("                                     �÷� = %d                           ʧ�� = %d\n", score, last);
        if (score_max != -1)
        if (score != score_max)
        puts("--------------------------------------------------*****ʧ��*****-------------------------------------------------------");
        else
        puts("---------------------------------------------------*****ʤ��*****-------------------------------------------------------");
    }
    puts("|                                               ����ESC�󷵻����˵�.                                                  |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    while(1)
        if (getch() == 0x1b)
            break;
}

//��������
void flash()
{
    memset(rank, 0, sizeof(rank));
    FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_rank.txt", "r");
    char name[10];
    int grade, i, p = -1, n = 0;
    while(!feof(fp))//��������
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
    selectionSort(n);//����
    FILE *fq = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_rank.txt", "w+");
    for (i = 0; i <= n; ++i)//������������
        fprintf(fq, "%s\t%d\n", rank[i].rankname, rank[i].rankgrade);
    fclose(fq);
}

//ѡ������
void selectionSort(int n)
{
    R rr;
    rr.rankgrade = rank[n].rankgrade;
    strcpy(rr.rankname, rank[n].rankname);
    for(int i = 0; i < n; ++i)//���
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

//�����ҵĳɼ����Լ��ĵ÷�
void Rank()
{
    FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_rank.txt", "r");
    char name[MAX_CHAR], ch;
    int grade, i = 1;
    puts("----------------------------------------------------����ģʽ����-------------------------------------------------------");
    do //�������
    {
        fscanf(fp, "%s%d\n", name, &grade);
        printf("         ����: %d,   �û���: %-10s,   ��ʷ�÷�: %d\n\n", i, name, grade);
        ++i;
    }while (!feof(fp));
    fclose(fp);
    printf("         %s��ǰ�ĳɼ�: %d\n", player.playername, score);//�����ǰ�û��ĳɼ�
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                       ����ESC���˳������˵�,������f�����û�����.                                    |");
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

//��¼ҳ��
void start_page()
{
    system("cls");
    TotalPlayer();
    puts("-----------------------------------------------------------------------------------------------------------------------");
    printf("|��ǰ���� %d ���û��Ѵ������˺�.��ã�%s ��ѡ������ѡ��:\n", total_player, player.playername);
    puts("|                                                 ��¼�˵�                                                             |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                        1.��������˺Ų���Ҫ��¼;                                   ����1                             |");
    puts("|                        2.������ѵ�ע��;                                           ����2                             |");
    puts("|                        3.����Ա��¼;                                               ����3                             |");
    puts("|                        4.�˳���¼;                                                 ����0                             |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                      �˻����˵�,����ESC.                                                             |");
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
                start_page();//���ص�¼ҳ��
                return;
            case '3':
                Administrator();
                start_page();//���ص�¼ҳ��
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

//�����������
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

//ע��
void Register()
{
    FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\player_information.txt", "a+");
    char name[MAX_CHAR], password[MAX_CHAR];
    while(1)
    {   
        system("cls");
        printf("1.�����������(��������9���ַ���4������):");
        scanf("%s", name);
        if (Out_of_range(name))
            break;
        else
        {
            puts("-------------------------------------------WARNING!����������,����������---------------------------------------------");
            system("pause");
        }
    }
    while(!feof(fp)) //����Ƿ�������
    {
        fscanf(fp, "%s%s\n", player.playername, player.password);
        if (!strcmp(name, player.playername))
            while(1)
            {   
                system("cls");
                puts("----------------------------------------------WARNING!����û����Ѵ���!------------------------------------------------");
                printf("1.�ٴ������������(��������9���ַ���4������):");
                scanf("%s", name);
                if (Out_of_range(name))
                    break;
                else
                {
                    puts("-------------------------------------------WARNING!����������,����������---------------------------------------------");
                }
            }
    }
    strcpy(player.playername, name);
    while (1)//�����������������Ƿ���ͬ
    {
        while(1)
        {   
            system("cls");
            printf("1.�����������(��������9���ַ���4������):%s\n", player.playername);
            printf("2.�����������Ч��,�����������(��������9���ַ���4������):");
            scanf("%s", password);
            if (Out_of_range(password))
                break;
            else
            {
                puts("-------------------------------------------WARNING!����������,����������---------------------------------------------");
                system("pause");
            }
        }
        strcpy(player.password, password);
        printf("3.�ٴ������������(��������9���ַ���4������):");
        scanf("%s", password);
        if (!strcmp(password, player.password))
            break;
        else
        {
            puts("WARNING!��������������벻һ��,�����������������.");
            system("pause");
            system("cls");
        }
    }
    printf("                                            ����û���:%s\n", player.playername);
    printf("                                            �������:%s\n", player.password);
    puts("-----------------------------------------------------------------------------------------------------------------------");
        puts("|                                 �˻�һ������,�����޸ĺ�ɾ�������б�Ҫ��ϵ����Ա����                                 |");
    puts("|                                        ���Ѿ��ɹ�������һ���˺�,��ȥ��¼��!!!                                       |");
    puts("|                                             ����ESC�󷵻ص�¼ҳ��.                                                  |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    fprintf(fp, "%s\t%s\n", player.playername, player.password);
    fclose(fp);
    strcpy(player.playername, "�ο�");//û�е�½�����ο����
    while (1)
        if (getch() == 0x1b)
            break;
}

//��¼
void Login()
{
    char name[MAX_CHAR], password[MAX_CHAR];
    system("cls");
    while (1)
    {
        puts("------------------------------------------------------------------------------------------------------------------------");
        puts("|                                   tips:�������Ҫ�˳�ѡ��ESC,���������������¼.                                  |");
        puts("------------------------------------------------------------------------------------------------------------------------");
        if (getch() == 0x1b)
            return;
        else
        {
            while(1)
            {
                system("cls");
                printf("                                    1.�����û���:");
                scanf("%s", name);
                if (Out_of_range(name))
                    break;
                else
                {
                    puts("-------------------------------------------WARNING!����������,����������---------------------------------------------");
                    system("pause");
                }
            }
            strcpy(player.playername, name);
            while(1)
            {
                system("cls");
                printf("                                    1.�����û���:%s\n", player.playername);
                printf("                                    2.��������:");
                scanf("%s", password);
                if (Out_of_range(password))
                    break;
                else
                {
                    puts("-------------------------------------------WARNING!����������,����������---------------------------------------------");
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
                    puts("------------------------------------------------------��¼�ɹ�---------------------------------------------------------");
                    puts("|                                                 ����ɫ       ����1                                                  |");
                    puts("|                                                                                                                     |");
                    puts("|                                                 ����ɫ       ����������                                             |");
                    puts("-----------------------------------------------------------------------------------------------------------------------");
                    if (getch() == '1')
                        system("color 03");
                    return;
                }
            }
            fclose(fp);
        }
        puts("-------------------------------------------WARNING!����û����������Ǵ����--------------------------------------------");
        puts("-----------------------------------------------------�������룡--------------------------------------------------------");
        strcpy(player.playername, "�ο�");
    }
}

//����Ա��¼
void Administrator()
{
    char name[MAX_CHAR], password[MAX_CHAR];
    if (strcmp(player.playername, "����Ա"))
    while(1)
    {
        system("cls");
        puts("*****************************************************����Ա��¼********************************************************\n");
        printf("                                    1.�������Ա����:");
        scanf("%s", name);
        printf("                                    2.�������Ա����:");
        scanf("%s", password);
        if (!strcmp(name, adm.playername) && !strcmp(password, adm.password))
        {
            score = 0;
            puts("************************************���Ѿ��ɹ���¼����Ա,���Թ���Ա��ݸ����û���Ϣ.***********************************");
            puts("------------------------------------------------------��¼�ɹ�---------------------------------------------------------");
            puts("|                                                 ���ɫ       ����1                                                  |");
            puts("|                                                                                                                     |");
            puts("|                                                 ����ɫ       ����������                                             |");
            puts("-----------------------------------------------------------------------------------------------------------------------");
            if (getch() == '1')
                system("color 06");
            strcpy(player.playername, "����Ա");
            break;
        }
        else
        {
            puts("-------------------------------------------WARNING!����û����������Ǵ����--------------------------------------------");
            puts("|                                    ����ESC�˻ص�¼ҳ��,�������������ٴγ��Ե�¼.                                    |");
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
        printf("                             ���: %d,   �û���: %-10s,   �ɼ�: %-10s\n", p + 1, P[p].playername, P[p].password);
        ++p;
    }
    fclose(fp);
    system("pause");
    while(p)
    {
        int t = 0;
        puts("-----------------------------------------------------------------------------------------------------------------------");
        puts("|��ã�����Ա ��ѡ������ѡ��:                                                                                         |");
        puts("|                                                ����Ա�˵�                                                           |");
        puts("|                                                                                                                     |");
        puts("-----------------------------------------------------------------------------------------------------------------------");
        puts("|                        1.�޸��û���Ϣ;                                          ����1                               |");
        puts("|                        2.ɾ���û���Ϣ;                                          ����2                               |");
        puts("|                        3.�����û���Ϣ;                                          ����3                               |");
        puts("|                        4.�����û���Ϣ;                                          ����4                               |");
        puts("|                                                                                                                     |");
        puts("-----------------------------------------------------------------------------------------------------------------------");
        puts("|                                            �˳���Ϸ,����ESC.                                                        |");
        puts("-----------------------------------------------------------------------------------------------------------------------");
        switch (getch())
        {
            case '1':
                system("cls");
                puts("************************************************�޸��û���Ϣ***********************************************************");
                printf("                         1.�޸��û������:");
                scanf("%d", &t);
                printf("                         2.�޸ĺ��%d���û����û���:", t);
                scanf("%s", name);
                printf("                         3.�޸ĺ��%d���û�������:", t);
                scanf("%s", password);
                strcpy(P[t - 1].playername, name);
                strcpy(P[t - 1].password, password);
                t = 1;
                break;
            case '2':
                system("cls");
                puts("************************************************ɾ���û���Ϣ***********************************************************");
                printf("                         ɾ���û������:");
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
                puts("************************************************�����û���Ϣ***********************************************************");
                printf("                         �����û�������:");
                scanf("%d", &sum);
                for (i = p; i - p < sum; i++)
                {
                    printf("                         ���ӵĵ�%d���û����û���:", i - p + 1);
                    scanf("%s", name);
                    printf("                         ���ӵĵ�%d���û�������:", i - p + 1);
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
                    puts("|                  �Ƿ񽫸��ĵ����ݱ���,������ԭ�������ݸ�Ϊ���ĺ��,�粻����ԭ�������ݲ������ı�.                    |");
                    puts("|                              ������: 'Y'/'y'(������) ���� 'N'/'n'(�����).                                          |");
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
                            printf("                             ���: %d,   �û���: %-10s,   �ɼ�: %-10s\n", i + 1, P[i].playername, P[i].password);
                            fprintf(fq, "%s\t%s\n", P[i].playername, P[i].password);
                            ++i;
                        }
                        fclose(fp);
                        fclose(fq);        
                        puts("*************************************************�����Ѹ���!***********************************************************");
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
                            printf("                             ���: %d,   �û���: %-10s,   �ɼ�: %-10s\n", i + 1, P[i].playername, P[i].password);
                            fprintf(fp, "%s\t%s\n", P[i].playername, P[i].password);
                            ++i;
                        }
                        fclose(fp);
                        fclose(fq);
                        puts("***********************************************����δ��������!*********************************************************");
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
                printf("                             ���: %d,   �û���: %-10s,   �ɼ�: %-10s\n", i + 1, P[i].playername, P[i].password);
            }
            fclose(fp);
        }
    }
}

//�����ض�����Ϣ
void find(int p)
{
    char _name[10];
    while(1)
    {
        system("cls");
        int t = 0;
        puts("-----------------------------------------------------------------------------------------------------------------------");
        printf("                ������ҵ��˵��û���:");
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
                printf("                             �û���: %-10s,   �ɼ�: %d,   ����: %d\n", name, grade, i);
            else
                puts("|                                                  û���ҵ����û�!                                                    |");
            puts("-----------------------------------------------------------------------------------------------------------------------");
            puts("|                                       ����ESC���˳������˵�,����������������.                                       |");
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
                printf("          �û���:%-10s,   ����:%s\n", name, password);
            else
                puts("|                                                  û���ҵ����û�!                                                    |");
            puts("-----------------------------------------------------------------------------------------------------------------------");
            puts("|                                       ����ESC���˳������˵�,����������������.                                    |");
            puts("-----------------------------------------------------------------------------------------------------------------------");
            fclose(fp);
            if (getch() == 0x1b)
                return;
        }
        
    }
}

//�˳���¼
void _Login()
{
    system("color 07");
    on_line = 0;
    score = 0;
    strcpy(player.playername, "�ο�");
}

//�ж��Ƿ񳬳���Χ
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

//���ۺ���
void Evaluate()
{
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                              �Ըó�����������?                                                    |");
    puts("|                                             ��ѡ�������һ������.                                                   |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                            o(������)��(����)            ����1                                       |");
    puts("|                                                                                                                     |");
    puts("|                                            (��������) ��~~)(����)       ����2                                       |");
    puts("|                                                                                                                     |");
    puts("|                                            X�nX(����)                   ����3                                       |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    puts("|                                              ֱ���˳���Ϸ,����ESC.                                                  |");
    puts("-----------------------------------------------------------------------------------------------------------------------");
    FILE *fp = fopen("C:\\Users\\15792\\Desktop\\study\\vsc\\c\\project\\evaluate.txt", "a+");
    while(1)
    {
        switch (getch())
        {
            case '1':
                puts("\n                                         Hi~ o(*������*)��(��л!!!)");
                fprintf(fp, "1\n");
                fclose(fp);
                return;
            case '2':
                puts("\n                                              (�ѩn��)(�ð�~)");
                fprintf(fp, "2\n");
                fclose(fp);
                return;
            case '3':
                puts("\n                                           ��|��|_(�����Ŭ����!)");
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