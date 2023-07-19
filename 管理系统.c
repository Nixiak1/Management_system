#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include <time.h>
int sys_min,sys_hour;
char student_num_list[20][10];              //学生名单（学生登陆使用）
int student_nums=0;                         //学生人数
struct student
{
    int vaca_hour;
    int vaca_min;                           //计划返校时间
    int delay_hour;                 
    int delay_min;                          //延期返校时间
    char del_vaca;                          //销假情况  N外出未销假（未在校）  Y外出已销假（在校）
    char delay_vaca;                        //延期情况  Y延期   N 未延期
    int vaca_numbers;                       //请假次数
};
struct teacher_admin
{
    char admin[10];
    char passworld[20];                     //教师账户密码
};
typedef struct Data 
{
    char num[10];                           //学号
    char name[30];                          //姓名
    char phone[13];                         //手机号
    char vaca;                              //请假情况          N未请假（在校）  Y已请假（未在校）
    char daka;                              //打卡情况          N未打卡  Y已打卡 
    struct student delay_vaca;              //延期情况
    struct Data *next;          
}*Link,data;
int student_login(char input_num[]);        //学生登陆系统
void sys_time();                            //获取系统时间
Link head();                                //创建头节点   
int creat1(Link head);                      //创建节点              （文件读取，数据录入）
void teacher_menu();                        //教师菜单     
void student_menu();                        //学生菜单     
void main_menu();                           //主菜单    
Link search(Link head,char input_num[]);    //查找学生             （简单数据查询）
void del(Link head);                        //删除学生             （删除）
void insert(Link head);                     //增添学生             （插入）
void output(Link head);                     //输出信息             （打印报表，
int change(Link head,int x_1,int x_2,int x_3,char input_num[]); //（修改）
//更改信息     (老师端更改所有信息，学生端更改  打卡、请假  信息)             
void sort(Link head);                        //学号排序             （升序）
void sort_vaca_numbers(Link head);           //按请假次数排序        （降序）
void undaka(Link head);                      //未打卡学生            （简单查询，统计）
void undaka_vaca(Link head);                 //查看未打卡且请假学生   （组合查询，统计）
void save(Link head);                        //保存信息              （保存）
void vaca_menu();                            //请假菜单
int teacher_login();                        //老师登录系统
void hide_passworld(char pass[]);            //密码输入                     
int main()
{
    char  mode;                               //使用端选择
    char input_num[10];                     //老师输入的工号
    Link head_=head();
    creat1(head_);   
    while(1)
    {
        main_menu();
        printf("\t\t\t\t\t\t\t\t\t");
      	mode=getchar();
        getchar();
        if(mode=='1')                         //进入老师端
        {
            int back_flag=teacher_login();
            if(back_flag==1)
                continue;
            int teacher_mode;
            teacher_menu();                 //老师功能选项
            while(1)
            {               
                scanf("%d",&teacher_mode);
                if(teacher_mode>=0&&teacher_mode<=9)
                {
                    
                    switch(teacher_mode)
                    {
                        case 0:
                        {
                            printf("感谢使用,系统已退出!");
                            exit(0);
                        }
                        case 1:
                        {
                            teacher_menu();
                            undaka(head_);              //未打卡学生（完）
                            continue;
                        }   
                        case 2:                         //未打卡且请假学生（完）
                        {
                            undaka_vaca(head_);
                            continue;
                        }
                        case 3:
                        {
                            teacher_menu();
                            insert(head_);              //增添学生（完）
                            save(head_);
                            continue;
                        }
                        case 4:
                        {
                            teacher_menu();
                            del(head_);                 //删除学生（完）
                            save(head_);
                            continue;
                        }
                        case 5:                         //查询
                        {
                            teacher_menu();
                            Link q;
                            while(1)
                            {
                                printf("请输入学生学号:");
                                scanf("%s",input_num);                            
                                q=search(head_,input_num);
                                if(q==NULL)
                                {
                                    printf("未找到该生信息,请重新输入!\n");
                                    continue;
                                }
                                break;
                            }
                            printf("%s的信息如下:\n",q->name);
                            printf("姓名\t学号\t手机\t是否打卡\t是否在校\n");
                            printf("%s\t%s\t%s\t",q->name,q->num,q->phone);
                            if(q->daka=='Y')
                                printf("是\t\t");
                            if(q->daka=='N')
                                printf("否\t\t");
                            if(q->vaca=='Y')
                                printf("否\t");
                            if(q->vaca=='N')
                                printf("是\t");
                            printf("\n");
                            continue;
                        }                        
                        case 6:                     //更改信息
                        {
                            teacher_menu();                           
                            int flag=1;
                            while(flag==1)
                            {
                                printf("\n请输入待修改信息学生学号:");
                                scanf("%s",input_num);
                                flag=change(head_,0,0,0,input_num);      
                            }
                            save(head_);                         
                            continue;
                        }
                        case 7:
                        {   
                            teacher_menu();
                            sort(head_);            //按学号排序（完）
                            continue;
                        }
                        case 8:
                        {
                            teacher_menu();
                            sort_vaca_numbers(head_);   //按请假次数排序
                            continue;
                        }
                        case 9:
                        {
                            teacher_menu();
                            output(head_);              //打印信息（完）
                            continue;
                        }
                    }
                }
                else
                {
                    printf("输入有误,请重新输入:\n");
                    fflush(stdin);
                    continue;
                }
            }
        }
        else if(mode=='2')                    //进入学生端
        {
            char input_num[10]={"0"};
            int back_flag=student_login(input_num);
            if(back_flag==1)
                continue;
            int student_mode;       
            student_menu();                 //学生功能选项
            while(1)
            {
				
                scanf("%d",&student_mode);
                if(student_mode>=0&&student_mode<=3)
                {
                    switch(student_mode)
                    {
                        case 0:
                        {
                            printf("感谢使用,系统已退出!");
                            exit(0);
                        }
                        case 1:                 //健康打卡
                        {
                            change(head_,0,0,1,input_num);
                            save(head_); 
                            Sleep(1000);
                            fflush(stdin);
                            student_menu();       
                            continue;
                        }   
                        case 2:                 //请假
                        {
                            char student_mode_new[3];
                            vaca_menu();
                            while(1)
                            {
                                scanf("%s",student_mode_new);
                                if((strcmp(student_mode_new,"1")==0)||(strcmp(student_mode_new,"2")==0)||(strcmp(student_mode_new,"B")==0))
                                {
                                    if(strcmp(student_mode_new,"1")==0)    //返校时间
                                    {
                                        change(head_,1,1,0,input_num);
                                        save(head_);
                                        Sleep(1000);
                                        student_menu();
                                        break;
                                    }
                                    if(strcmp(student_mode_new,"2")==0)     //延期
                                    {
                                        change(head_,0,1,1,input_num);
                                        save(head_);
                                        Sleep(1000);
                                        student_menu();
                                        break;
                                    }
                                    if(strcmp(student_mode_new,"B")==0)
                                    {
                                        student_menu();
                                        break;
                                    }
                                }
                                else
                                {
                                    printf("\n输入有误,请重新输入：");                                   
                                    continue;
                                }
                            }
                            continue;
                        }
                        case 3:             //销假
                        {
                            Link p=search(head_,input_num);
                            if(p->vaca=='N')
                            {
                                printf("你未请假不能执行此操作!\n");  
                                continue;
                            }
                            change(head_,1,0,0,input_num);
                            Sleep(1000);
                            save(head_);
                            continue;
                        }
                    }
                }
                else
                {
                    printf("输入有误,请重新输入：\n");
                    char c=getchar();
                    continue;
                }
            }
        }
        else if(mode=='0')
        {
            printf("系统已退出,感谢使用!");
            exit(0);
        }
        else
        {
            printf("输入有误，请重新输入！\n");
            fflush(stdin);
            system("pause");
            continue;
        }
    }

}
void main_menu()
{
    system("cls");
    printf("\t\t\t\t\t\t\t----------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                 |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|           1 <-教师端->          |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                 |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                 |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|           2 <-学生端->          |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                 |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t----------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t————————————请选择操作端——————————\t\t\t\t\t\t\t\t\t\t\n");
}
void teacher_menu()
{
    system("cls");
    printf("\t\t\t\t\t\t\t----------------------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                            |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             1  查看未打卡学生              |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             2  查看未打卡且请假学生        |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             3  添加学生                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             4  删除学生                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             5  查询学生信息                |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             6  修改学生信息                |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             7  按学号排序                  |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             8  按请假次数排序              |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             9  输出所有学生信息            |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             0  退出系统                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t----------------------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t—————————————————<请选择(0~9)>————————————————\t\t\t\t\t\t\t\t\t\t\n");
}
void student_menu()
{
    system("cls");
    printf("\t\t\t\t\t\t\t----------------------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                            |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             1  健康打卡                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             2  外出请假                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             3  销假                        |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             0  退出系统                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t----------------------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t————————————————<请选择(0~3)>————————————————\t\t\t\t\t\t\t\t\t\t\n");
}   
void vaca_menu()
{
    system("cls");
    printf("\t\t\t\t\t\t\t---------------------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                            |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             1  返校时间                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             2  延期                        |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             0  退出系统                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t--------------------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t————————————————<请选择(0~2)>————————————————\t\t\t\t\t\t\t\t\t\t\n");
}   
void hide_passworld(char pass[])
{
    int i = 0; //记录密码长度
    char c; //用于实现密码隐式输入
    while (1)
     {
        c = getch(); //用 getch() 函数输入，字符不会显示在屏幕上
        if (c == '\r') { //遇到回车，表明密码输入结束
            break; //while 循环的出口
        }
        else if (c == '\b') { //遇到退格，需要删除前一个星号
            printf("\b \b");  //退格，打一个空格，再退格，实质上是用空格覆盖掉星号
            --i;
        }
        else {
            pass[i++] = c;//将字符放入数组
            printf("*");     
        }
    }
}   
int student_login(char input_num[])
{
	int i;
    int login_flag=0,back_flag=0;
    printf("如需返回请按B\n");
    while(1)
    {
        printf("请输入学号:");
        scanf("%s",input_num);
        if(strcmp(input_num,"B")==0)
        {
			getchar();
            return 1;                   //返回1 表示  重新选择
    	}
        for(i=0;i<student_nums;i++)
        {
            if(strcmp(student_num_list[i],input_num)==0)
                login_flag=1;           
        }
        if(login_flag==0)
        {
            printf("未找到您的信息,请确保你是该班学生！\n");
            continue;
        }
        printf("登陆成功!\n");
        break;
    }
    return 0;                           //返回0 表示  登录成功
}  
int teacher_login()
{
    FILE *fp_=fopen("teacher_admin.txt","rt");
    char input_teacher_admin[10];
    char c;
    char input_teacher_pass[20]={"0"};//输入的账号密码
    struct teacher_admin adminer;
    char adminer_[10];
    char passworld_[20];        //账号密码中间变量
    char new_pass[20];          //新密码
    int i=0,j=3;
    while(fscanf(fp_,"%s\t%s",adminer_,passworld_)!=EOF)
    {
        strcpy(adminer.admin,adminer_);
        strcpy(adminer.passworld,passworld_);
    }
    fclose(fp_);
    printf("如需返回请按B\n");
    while(j)
    {
        printf("工号:\n");
        scanf("%s",input_teacher_admin);
        if(strcmp(input_teacher_admin,"B")==0)
        {
        	getchar();
            return 1;
        }
        printf("密码:\n");
        hide_passworld(input_teacher_pass);
        if((strcmp(adminer.admin,input_teacher_admin)==0)&&(strcmp(adminer.passworld,input_teacher_pass)==0))
            break;
        else
        {
            printf("\n账号或密码错误,请重新输入!\n");
            j--;
            continue;
        }
    }
    if(j==0)
    {
        printf("密码输入已达上限,系统退出!");
        exit(0);
    }
    printf("\n\n登陆成功!\n");
    printf("如需更改密码请按1,不需更改密码请按0 :  ");
    int change_pass_flag;
    
    while(1)
    {
        scanf("%d",&change_pass_flag);
        if(change_pass_flag==1)
        {
            
            while(1)
            {
                printf("请输入新密码:\n");
                hide_passworld(new_pass);
                if(strcmp(new_pass,adminer.passworld)==0)
                {
                    printf("新密码不能与旧密码相同!\n");
                    continue;
                }
                fp_=fopen("teacher_admin.txt","wt");
                strcpy(adminer.passworld,new_pass);
                fprintf(fp_,"%s\t%s",adminer.admin,new_pass);
                fclose(fp_);
                printf("\n密码修改成功!\n");
                system("pause");
                break;
            }
        }
        else if(change_pass_flag==0)
        {
            break;
        }
        else
        {
            printf("输入有误,请重新输入!\n");
            continue;
        }
        break;
    }
}
void sys_time()
{
    time_t t;
    struct tm * lt;
    time (&t);//获取Unix时间戳。
    lt = localtime (&t);//转为时间结构。
    sys_hour=lt->tm_hour;
    sys_min=lt->tm_min;
}
Link head()                                    //创造头节点
{   
    Link head=(data *)malloc(sizeof(data));
    head->next=NULL;
    return head;
}
int creat1(Link head)                          //创造节点
{
    Link r=head;   
    int i=0; 
    FILE *fp=fopen("学生名单.txt","rt");
    char name_[30];
    char num_[10];
    char phone_[13];
    char vaca_;     //是否请假
    char daka_;     //是否打卡
    char del_vaca_;//是否销假
    int hour_,min_;//计划返校时间
    char delay_vaca_;    //是否延期
    int delay_hour,delay_min; //延期时间
    int vaca_numbers_;
    char first_line[50];
    fgets(first_line,148,fp);                //移动文件指针到第二行行首
    while(fscanf(fp,"%s\t%s\t%s\t%c\t\t%c\t\t%d:%d\t\t%c\t%c\t%d:%d\t\t%d",name_,num_,phone_,&daka_,&vaca_,&hour_,&min_,&del_vaca_,&delay_vaca_,&delay_hour,&delay_min,&vaca_numbers_)!=EOF)
    {
        Link node=(data *)malloc(sizeof(data));
        r->next=node;
        strcpy(node->name,name_);
        strcpy(node->num,num_);
        strcpy(student_num_list[student_nums],num_);
        strcpy(node->phone,phone_);
        node->daka=daka_;
        node->vaca=vaca_;
        node->delay_vaca.del_vaca=del_vaca_;
        node->delay_vaca.vaca_hour=hour_;
        node->delay_vaca.vaca_min=min_;
        node->delay_vaca.delay_hour=delay_hour;
        node->delay_vaca.delay_min=delay_min;
        node->delay_vaca.delay_vaca=delay_vaca_;
        node->delay_vaca.vaca_numbers=vaca_numbers_;
        r=node;
        i++;
        student_nums++;
    }
    r->next=NULL;
    fclose(fp);
    return i;
}
void del(Link head)                             //删除学生信息
{
    char num[10];
    printf("请输入需要删除的学生学号：");
    while(1)
    {
        Link p=head->next;
        Link pre=head->next;
        scanf("%s",num);
        while(p)
        {
            if(strcmp(p->num,num)!=0)
            {
                pre=p;
                p=p->next;
            }
            else 
                break;
        }
        if(p==head->next)
            {
                head->next=p->next;
                free(p);
            }
        else if(p==NULL)
        {
            printf("学生信息不存在,请重新输入！\n");
            continue;
        }
        else if(p->next==NULL)
        {
            pre->next=NULL;
            free(p);
        }
        else
        {
            pre->next=p->next;
            free(p);
        }
        break;
    } 
    int i;
    printf("正在删除,请稍后");
    for(i=0;i<3;i++)
    {
        printf(".");
        Sleep(1000);
    }
    printf("\n删除成功!\n");   
}
Link search(Link head,char input_num[])
{
    Link q=head->next;
    while(q)
    {
        if(strcmp(q->num,input_num)!=0)
        {
            q=q->next;
        }
        else
            break;
    }       
    return q;
}
void insert(Link head)                                  //尾插
{
    Link end=head->next;
    char num[10];
    while(1)
    {	
    	printf("学号：");
    	scanf("%s",num);
    	if(search(head,num)!=NULL)
    	{
    		printf("该生已经存在,请重新输入学号!\n");
    		continue;
		}
		else
		{
			break;
		}
	}
	while(end->next)
        end=end->next;
    Link new=(data *)malloc(sizeof(data));
    end->next=new;
	strcpy(new->num,num);
    printf("姓名：");
    scanf("%s",new->name);
    printf("手机：");
    scanf("%s",new->phone);
    new->daka='Y';                                      //打卡
    new->vaca='N';                                      //请假情况
    new->delay_vaca.del_vaca='Y';                       //销假情况
    new->delay_vaca.delay_vaca='N';                     //延期情况
    new->delay_vaca.vaca_hour=0;
    new->delay_vaca.vaca_min=0;
    new->delay_vaca.delay_hour=0;
    new->delay_vaca.delay_min=0;
    new->delay_vaca.vaca_numbers=0;
    new->next=NULL;   
    printf("添加成功!\n");
}
int change(Link head,int x_1,int x_2,int x_3,char input_num[])
{
        Link q=head->next;
        while(q)
        {
            if(strcmp(q->num,input_num)!=0)
            {
                q=q->next;
            }
            else
                break;
        }
        if(q==NULL)
            {
                printf("未找到信息!\n");
                printf("请重新输入：");
                return 1;
            }
        else
            {
                char x;  
                char new_name[10],new_num[10],new_phone[13]; 
                if(x_1==0&&x_2==0&&x_3==0)              //教师更改所有信息
                {
                    printf("需要更改什么信息？\n");
                    printf("A.姓名 B.学号 C.手机  D.销假\n");
                    fflush(stdin);
                    while(1)
                    {
                        scanf("%c",&x);
                        if(x=='A')
                        {
                            printf("请输入姓名:");
                            scanf("%s",new_name);
                            strcpy(q->name,new_name);
                            printf("更改成功！\n");
                            break;
                        }
                        if(x=='B')
                        {   
                            printf("请输入学号:");
                            scanf("%s",new_num);
                            strcpy(q->num,new_num);
                            printf("更改成功！\n");
                            break;
                        }
                        if(x=='C')
                        {
                            printf("请输入手机号:");
                            scanf("%s",new_phone);
                            strcpy(q->phone,new_phone);
                            printf("更改成功！\n");
                            break;
                        }
                        if(x=='D')
                        {
                            q->vaca='N';
                            q->delay_vaca.del_vaca='Y';
                            q->delay_vaca.vaca_hour=0;
                            q->delay_vaca.vaca_min=0;
                            q->delay_vaca.delay_vaca='N';
                            q->delay_vaca.delay_hour=0;
                            q->delay_vaca.delay_min=0;
                            printf("销假成功！\n");
                            break;
                        }
                        else
                        {
                            printf("输入有误,请重新输入！\n");
                            continue;
                        }
                    }
                }
                if(x_1==0&&x_2==0&&x_3==1)              //学生打卡
                {
                    if(q->daka=='Y')
                    {
                        printf("你已打卡,请下一步操作!\n");
                        return  9;
                    }
                    q->daka='Y';
                    printf("打卡成功!\n");
                }    
                if(x_1==1&&x_2==0&&x_3==0)              //学生销假
                {
                    sys_time();
                    if(q->delay_vaca.delay_vaca=='N')
                    {
                        if((sys_hour>q->delay_vaca.vaca_hour)||(sys_hour==q->delay_vaca.vaca_hour&&sys_min>q->delay_vaca.vaca_min))
                        {
                            printf("你已超出返校时间,销假失败!");
                            exit(0);
                        }
                    }
                    else if(q->delay_vaca.delay_vaca=='Y')
                    {
                        if((sys_hour>q->delay_vaca.delay_hour)||(sys_hour==q->delay_vaca.delay_hour&&sys_min>q->delay_vaca.delay_min))
                        {
                            printf("你已超出延期返校时间,销假失败!");
                            exit(0);
                        }
                        q->delay_vaca.delay_vaca='N';   //是否延期置默认
                        q->delay_vaca.delay_hour=0;
                        q->delay_vaca.delay_min=0;      //延期返校时间置默认
                    }
                    q->vaca='N';                        //请假情况置默认
                    q->delay_vaca.del_vaca='Y';         //销假情况 置  是
                    q->delay_vaca.vaca_hour=0;
                    q->delay_vaca.vaca_min=0;           //计划返校时间置默认
                    
                    printf("销假成功!\n");
                }
                if(x_1==0&&x_2==1&&x_3==1)              //延期
                {
                    int delay_hour_now,delay_min_now;
                    if(q->vaca=='N')
                    {
                        printf("你未请假,不能延期!");
                        exit(0);
                    }
                    while(1)
                    {
                        printf("请输入延迟返校时间(例如13:45):");
                        sys_time();
                        scanf("%d:%d",&delay_hour_now,&delay_min_now);
                        if((delay_hour_now<0||delay_hour_now>24)||(delay_min_now<0||delay_min_now>60))
                        {
                            printf("输入有误,请重新输入!\n");
                            continue;
                        }
                        if((delay_hour_now<sys_hour)||(delay_hour_now==sys_hour&&delay_min_now<sys_min))
                        {
                            printf("延迟返校时间应晚于当前时间!\n");
                            continue;
                        }
                        if(delay_hour_now>=23&&delay_hour_now<=24)
                        {
                            printf("延迟返校时间应早于23:00!\n");
                            continue;
                        }
                        q->delay_vaca.delay_hour=delay_hour_now;
                        q->delay_vaca.delay_min=delay_min_now;
                        q->delay_vaca.delay_vaca='Y';
                        break;
                    }
                    printf("延期成功!\n");
                }
                if(x_1==1&&x_2==1&&x_3==0)              //返校时间(请假)
                {   
                    int vaca_hour_now,vaca_min_now;
                    if(q->vaca=='Y')
                    {
                        printf("你已请假,不能继续请假!");
                        return 0;
                    }
                    while(1)
                    {
                        printf("请输入返校时间(例如13:45):");
                        sys_time();
                        scanf("%d:%d",&vaca_hour_now,&vaca_min_now);
                        
                        if((vaca_hour_now<0||vaca_hour_now>24)||(vaca_min_now<0||vaca_min_now>60))
                        {
                            printf("输入有误,请重新输入!\n");
                            continue;
                        }
                        if((vaca_hour_now<sys_hour)||(vaca_hour_now==sys_hour&&vaca_min_now<=sys_min))
                        {
                            printf("返校时间应晚于当前时间!\n");
                            continue;
                        }
                        if(vaca_hour_now>=23&&vaca_hour_now<=24)
                        {
                            printf("返校时间应早于23:00!\n");
                            continue;
                        }
                        q->delay_vaca.vaca_hour=vaca_hour_now;
                        q->delay_vaca.vaca_min=vaca_min_now;
                        q->delay_vaca.del_vaca='N';
                        break;
                    }
                    q->vaca='Y';
                    q->delay_vaca.vaca_numbers++;
                    printf("请假成功!\n");
                }
            }
        return 2;
}
void output(Link head)
{
    Link ipos=head->next;
    printf("姓名\t学号\t手机\t是否打卡\t是否请假\t累计请假次数\n");
    while(ipos!=NULL)
    {
        printf("%s\t%s\t%s\t",ipos->name,ipos->num,ipos->phone);
        fflush(stdin);
        if(ipos->daka=='N')
            printf("  否\t");
        if(ipos->daka=='Y')
            printf("  是\t");
        if(ipos->vaca=='N')
            printf("  \t  否\t\t");
        if(ipos->vaca=='Y')
            printf("  \t  是\t\t");
        printf("%d",ipos->delay_vaca.vaca_numbers);
        printf("\n");
        ipos=ipos->next;
    }
}
void sort(Link head)
{
    Link pre,q,q_next,end;                      //pre前一项  cur当前项   next下一项  
	end=NULL;
    Link temp;
    int i=student_nums,j,k=0;
    for(j=0;j<i-1;j++)
    {
        for(pre=head,q=pre->next,q_next=q->next;  q->next!=NULL;  pre=pre->next,q=q->next,q_next=q_next->next)
		{
			if(strcmp(q->num,q_next->num)>0)
			{
				pre->next=q_next;
				q->next=q_next->next;
				q_next->next=q;
                temp=q;
                q=q_next; 
                q_next=temp;
			}
		}
   //     end=cur;
    }
    output(head);
}
void sort_vaca_numbers(Link head)
{
    Link pre,q,q_next,end;                      //pre前一项  cur当前项   next下一项  
	end=NULL;
    Link temp;
    int i=student_nums,j,k=0;
    for(j=0;j<i-1;j++)
    {
        for(pre=head,q=pre->next,q_next=q->next;  q->next!=NULL;  pre=pre->next,q=q->next,q_next=q_next->next)
		{
			if(q->delay_vaca.vaca_numbers<q_next->delay_vaca.vaca_numbers)
			{
				pre->next=q_next;
				q->next=q_next->next;
				q_next->next=q;
                temp=q;
                q=q_next; 
                q_next=temp;
			}
		}
   //     end=cur;
    }
    output(head);
}

void undaka_vaca(Link head)
{
    Link ipos=head->next;
    int i=0;
    while(ipos)
    {
        if(ipos->daka=='N'&&ipos->vaca=='Y')
        {
            printf("%s\t",ipos->name);
            i++;
        }
        ipos=ipos->next;
    }
    if(i==0)
    {
        printf("没有 未打卡 且 已请假 的学生!");
    }
    else if(i!=0)
    {
        printf("%d位学生未打卡且已请假",i);
    }
    printf("\n");
}
void undaka(Link head)
{
    int i=0;
     Link ipos=head->next;
     while(ipos)
    {
        if(ipos->daka=='N')
        {
            printf("%s\t",ipos->name);
            i++;
        }
        ipos=ipos->next;
    }
    if(i==0)
    {
        printf("所有学生已打卡!");
    }
    else
        printf("%d 位学生未打卡!",i);
    printf("\n");
}
void save(Link head)
{
        FILE *fp;
        Link p;
        fp=fopen("学生名单.txt","wt");
        char ch1[]={"姓名"},ch2[]={"学号"},ch3[]={"手机"},ch4[]={"是否打卡"},ch5[]={"是否请假"},ch7='Y',ch8='N',ch0[]={"返校时间"},ch9[]={"是否销假"},ch10[]={"是否延期"},ch11[]={"延期时间"};    
        fprintf(fp,"%s\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",ch1,ch2,ch3,ch4,ch5,ch0,ch9,ch10,ch11,"请假次数");
        for(p=head->next;p!=NULL;p=p->next)
        {
            fprintf(fp,"%s\t%s\t%s\t",p->name,p->num,p->phone);
            if(p->daka=='N')
                fprintf(fp,"%c\t\t",'N');
            if(p->daka=='Y')
                fprintf(fp,"%c\t\t",'Y');
            if(p->vaca=='N')
                fprintf(fp,"%c\t\t",'N');
            if(p->vaca=='Y')
                fprintf(fp,"%c\t\t",'Y');
            fprintf(fp,"%d:%02d\t\t",p->delay_vaca.vaca_hour,p->delay_vaca.vaca_min);
            fprintf(fp,"%c\t\t",p->delay_vaca.del_vaca);
            fprintf(fp,"%c\t\t",p->delay_vaca.delay_vaca);
            fprintf(fp,"%d:%02d\t\t",p->delay_vaca.delay_hour,p->delay_vaca.delay_min);
            fprintf(fp,"%d",p->delay_vaca.vaca_numbers);
            fputc('\n',fp);
        }
        fflush(stdin); 
        fclose(fp);
}