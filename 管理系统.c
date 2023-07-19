#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include <time.h>
int sys_min,sys_hour;
char student_num_list[20][10];              //ѧ��������ѧ����½ʹ�ã�
int student_nums=0;                         //ѧ������
struct student
{
    int vaca_hour;
    int vaca_min;                           //�ƻ���Уʱ��
    int delay_hour;                 
    int delay_min;                          //���ڷ�Уʱ��
    char del_vaca;                          //�������  N���δ���٣�δ��У��  Y��������٣���У��
    char delay_vaca;                        //�������  Y����   N δ����
    int vaca_numbers;                       //��ٴ���
};
struct teacher_admin
{
    char admin[10];
    char passworld[20];                     //��ʦ�˻�����
};
typedef struct Data 
{
    char num[10];                           //ѧ��
    char name[30];                          //����
    char phone[13];                         //�ֻ���
    char vaca;                              //������          Nδ��٣���У��  Y����٣�δ��У��
    char daka;                              //�����          Nδ��  Y�Ѵ� 
    struct student delay_vaca;              //�������
    struct Data *next;          
}*Link,data;
int student_login(char input_num[]);        //ѧ����½ϵͳ
void sys_time();                            //��ȡϵͳʱ��
Link head();                                //����ͷ�ڵ�   
int creat1(Link head);                      //�����ڵ�              ���ļ���ȡ������¼�룩
void teacher_menu();                        //��ʦ�˵�     
void student_menu();                        //ѧ���˵�     
void main_menu();                           //���˵�    
Link search(Link head,char input_num[]);    //����ѧ��             �������ݲ�ѯ��
void del(Link head);                        //ɾ��ѧ��             ��ɾ����
void insert(Link head);                     //����ѧ��             �����룩
void output(Link head);                     //�����Ϣ             ����ӡ����
int change(Link head,int x_1,int x_2,int x_3,char input_num[]); //���޸ģ�
//������Ϣ     (��ʦ�˸���������Ϣ��ѧ���˸���  �򿨡����  ��Ϣ)             
void sort(Link head);                        //ѧ������             ������
void sort_vaca_numbers(Link head);           //����ٴ�������        ������
void undaka(Link head);                      //δ��ѧ��            ���򵥲�ѯ��ͳ�ƣ�
void undaka_vaca(Link head);                 //�鿴δ�������ѧ��   ����ϲ�ѯ��ͳ�ƣ�
void save(Link head);                        //������Ϣ              �����棩
void vaca_menu();                            //��ٲ˵�
int teacher_login();                        //��ʦ��¼ϵͳ
void hide_passworld(char pass[]);            //��������                     
int main()
{
    char  mode;                               //ʹ�ö�ѡ��
    char input_num[10];                     //��ʦ����Ĺ���
    Link head_=head();
    creat1(head_);   
    while(1)
    {
        main_menu();
        printf("\t\t\t\t\t\t\t\t\t");
      	mode=getchar();
        getchar();
        if(mode=='1')                         //������ʦ��
        {
            int back_flag=teacher_login();
            if(back_flag==1)
                continue;
            int teacher_mode;
            teacher_menu();                 //��ʦ����ѡ��
            while(1)
            {               
                scanf("%d",&teacher_mode);
                if(teacher_mode>=0&&teacher_mode<=9)
                {
                    
                    switch(teacher_mode)
                    {
                        case 0:
                        {
                            printf("��лʹ��,ϵͳ���˳�!");
                            exit(0);
                        }
                        case 1:
                        {
                            teacher_menu();
                            undaka(head_);              //δ��ѧ�����꣩
                            continue;
                        }   
                        case 2:                         //δ�������ѧ�����꣩
                        {
                            undaka_vaca(head_);
                            continue;
                        }
                        case 3:
                        {
                            teacher_menu();
                            insert(head_);              //����ѧ�����꣩
                            save(head_);
                            continue;
                        }
                        case 4:
                        {
                            teacher_menu();
                            del(head_);                 //ɾ��ѧ�����꣩
                            save(head_);
                            continue;
                        }
                        case 5:                         //��ѯ
                        {
                            teacher_menu();
                            Link q;
                            while(1)
                            {
                                printf("������ѧ��ѧ��:");
                                scanf("%s",input_num);                            
                                q=search(head_,input_num);
                                if(q==NULL)
                                {
                                    printf("δ�ҵ�������Ϣ,����������!\n");
                                    continue;
                                }
                                break;
                            }
                            printf("%s����Ϣ����:\n",q->name);
                            printf("����\tѧ��\t�ֻ�\t�Ƿ��\t�Ƿ���У\n");
                            printf("%s\t%s\t%s\t",q->name,q->num,q->phone);
                            if(q->daka=='Y')
                                printf("��\t\t");
                            if(q->daka=='N')
                                printf("��\t\t");
                            if(q->vaca=='Y')
                                printf("��\t");
                            if(q->vaca=='N')
                                printf("��\t");
                            printf("\n");
                            continue;
                        }                        
                        case 6:                     //������Ϣ
                        {
                            teacher_menu();                           
                            int flag=1;
                            while(flag==1)
                            {
                                printf("\n��������޸���Ϣѧ��ѧ��:");
                                scanf("%s",input_num);
                                flag=change(head_,0,0,0,input_num);      
                            }
                            save(head_);                         
                            continue;
                        }
                        case 7:
                        {   
                            teacher_menu();
                            sort(head_);            //��ѧ�������꣩
                            continue;
                        }
                        case 8:
                        {
                            teacher_menu();
                            sort_vaca_numbers(head_);   //����ٴ�������
                            continue;
                        }
                        case 9:
                        {
                            teacher_menu();
                            output(head_);              //��ӡ��Ϣ���꣩
                            continue;
                        }
                    }
                }
                else
                {
                    printf("��������,����������:\n");
                    fflush(stdin);
                    continue;
                }
            }
        }
        else if(mode=='2')                    //����ѧ����
        {
            char input_num[10]={"0"};
            int back_flag=student_login(input_num);
            if(back_flag==1)
                continue;
            int student_mode;       
            student_menu();                 //ѧ������ѡ��
            while(1)
            {
				
                scanf("%d",&student_mode);
                if(student_mode>=0&&student_mode<=3)
                {
                    switch(student_mode)
                    {
                        case 0:
                        {
                            printf("��лʹ��,ϵͳ���˳�!");
                            exit(0);
                        }
                        case 1:                 //������
                        {
                            change(head_,0,0,1,input_num);
                            save(head_); 
                            Sleep(1000);
                            fflush(stdin);
                            student_menu();       
                            continue;
                        }   
                        case 2:                 //���
                        {
                            char student_mode_new[3];
                            vaca_menu();
                            while(1)
                            {
                                scanf("%s",student_mode_new);
                                if((strcmp(student_mode_new,"1")==0)||(strcmp(student_mode_new,"2")==0)||(strcmp(student_mode_new,"B")==0))
                                {
                                    if(strcmp(student_mode_new,"1")==0)    //��Уʱ��
                                    {
                                        change(head_,1,1,0,input_num);
                                        save(head_);
                                        Sleep(1000);
                                        student_menu();
                                        break;
                                    }
                                    if(strcmp(student_mode_new,"2")==0)     //����
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
                                    printf("\n��������,���������룺");                                   
                                    continue;
                                }
                            }
                            continue;
                        }
                        case 3:             //����
                        {
                            Link p=search(head_,input_num);
                            if(p->vaca=='N')
                            {
                                printf("��δ��ٲ���ִ�д˲���!\n");  
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
                    printf("��������,���������룺\n");
                    char c=getchar();
                    continue;
                }
            }
        }
        else if(mode=='0')
        {
            printf("ϵͳ���˳�,��лʹ��!");
            exit(0);
        }
        else
        {
            printf("�����������������룡\n");
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
    printf("\t\t\t\t\t\t\t|           1 <-��ʦ��->          |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                 |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                 |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|           2 <-ѧ����->          |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                 |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t----------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t��������������������������ѡ������ˡ�������������������\t\t\t\t\t\t\t\t\t\t\n");
}
void teacher_menu()
{
    system("cls");
    printf("\t\t\t\t\t\t\t----------------------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                            |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             1  �鿴δ��ѧ��              |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             2  �鿴δ�������ѧ��        |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             3  ���ѧ��                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             4  ɾ��ѧ��                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             5  ��ѯѧ����Ϣ                |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             6  �޸�ѧ����Ϣ                |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             7  ��ѧ������                  |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             8  ����ٴ�������              |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             9  �������ѧ����Ϣ            |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             0  �˳�ϵͳ                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t----------------------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t����������������������������������<��ѡ��(0~9)>��������������������������������\t\t\t\t\t\t\t\t\t\t\n");
}
void student_menu()
{
    system("cls");
    printf("\t\t\t\t\t\t\t----------------------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                            |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             1  ������                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             2  ������                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             3  ����                        |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             0  �˳�ϵͳ                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t----------------------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t��������������������������������<��ѡ��(0~3)>��������������������������������\t\t\t\t\t\t\t\t\t\t\n");
}   
void vaca_menu()
{
    system("cls");
    printf("\t\t\t\t\t\t\t---------------------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|                                            |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             1  ��Уʱ��                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             2  ����                        |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t|             0  �˳�ϵͳ                    |\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t--------------------------------------------\t\t\t\t\t\t\t\t\t\t\n");
    printf("\t\t\t\t\t\t\t��������������������������������<��ѡ��(0~2)>��������������������������������\t\t\t\t\t\t\t\t\t\t\n");
}   
void hide_passworld(char pass[])
{
    int i = 0; //��¼���볤��
    char c; //����ʵ��������ʽ����
    while (1)
     {
        c = getch(); //�� getch() �������룬�ַ�������ʾ����Ļ��
        if (c == '\r') { //�����س������������������
            break; //while ѭ���ĳ���
        }
        else if (c == '\b') { //�����˸���Ҫɾ��ǰһ���Ǻ�
            printf("\b \b");  //�˸񣬴�һ���ո����˸�ʵ�������ÿո񸲸ǵ��Ǻ�
            --i;
        }
        else {
            pass[i++] = c;//���ַ���������
            printf("*");     
        }
    }
}   
int student_login(char input_num[])
{
	int i;
    int login_flag=0,back_flag=0;
    printf("���践���밴B\n");
    while(1)
    {
        printf("������ѧ��:");
        scanf("%s",input_num);
        if(strcmp(input_num,"B")==0)
        {
			getchar();
            return 1;                   //����1 ��ʾ  ����ѡ��
    	}
        for(i=0;i<student_nums;i++)
        {
            if(strcmp(student_num_list[i],input_num)==0)
                login_flag=1;           
        }
        if(login_flag==0)
        {
            printf("δ�ҵ�������Ϣ,��ȷ�����Ǹð�ѧ����\n");
            continue;
        }
        printf("��½�ɹ�!\n");
        break;
    }
    return 0;                           //����0 ��ʾ  ��¼�ɹ�
}  
int teacher_login()
{
    FILE *fp_=fopen("teacher_admin.txt","rt");
    char input_teacher_admin[10];
    char c;
    char input_teacher_pass[20]={"0"};//������˺�����
    struct teacher_admin adminer;
    char adminer_[10];
    char passworld_[20];        //�˺������м����
    char new_pass[20];          //������
    int i=0,j=3;
    while(fscanf(fp_,"%s\t%s",adminer_,passworld_)!=EOF)
    {
        strcpy(adminer.admin,adminer_);
        strcpy(adminer.passworld,passworld_);
    }
    fclose(fp_);
    printf("���践���밴B\n");
    while(j)
    {
        printf("����:\n");
        scanf("%s",input_teacher_admin);
        if(strcmp(input_teacher_admin,"B")==0)
        {
        	getchar();
            return 1;
        }
        printf("����:\n");
        hide_passworld(input_teacher_pass);
        if((strcmp(adminer.admin,input_teacher_admin)==0)&&(strcmp(adminer.passworld,input_teacher_pass)==0))
            break;
        else
        {
            printf("\n�˺Ż��������,����������!\n");
            j--;
            continue;
        }
    }
    if(j==0)
    {
        printf("���������Ѵ�����,ϵͳ�˳�!");
        exit(0);
    }
    printf("\n\n��½�ɹ�!\n");
    printf("������������밴1,������������밴0 :  ");
    int change_pass_flag;
    
    while(1)
    {
        scanf("%d",&change_pass_flag);
        if(change_pass_flag==1)
        {
            
            while(1)
            {
                printf("������������:\n");
                hide_passworld(new_pass);
                if(strcmp(new_pass,adminer.passworld)==0)
                {
                    printf("�����벻�����������ͬ!\n");
                    continue;
                }
                fp_=fopen("teacher_admin.txt","wt");
                strcpy(adminer.passworld,new_pass);
                fprintf(fp_,"%s\t%s",adminer.admin,new_pass);
                fclose(fp_);
                printf("\n�����޸ĳɹ�!\n");
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
            printf("��������,����������!\n");
            continue;
        }
        break;
    }
}
void sys_time()
{
    time_t t;
    struct tm * lt;
    time (&t);//��ȡUnixʱ�����
    lt = localtime (&t);//תΪʱ��ṹ��
    sys_hour=lt->tm_hour;
    sys_min=lt->tm_min;
}
Link head()                                    //����ͷ�ڵ�
{   
    Link head=(data *)malloc(sizeof(data));
    head->next=NULL;
    return head;
}
int creat1(Link head)                          //����ڵ�
{
    Link r=head;   
    int i=0; 
    FILE *fp=fopen("ѧ������.txt","rt");
    char name_[30];
    char num_[10];
    char phone_[13];
    char vaca_;     //�Ƿ����
    char daka_;     //�Ƿ��
    char del_vaca_;//�Ƿ�����
    int hour_,min_;//�ƻ���Уʱ��
    char delay_vaca_;    //�Ƿ�����
    int delay_hour,delay_min; //����ʱ��
    int vaca_numbers_;
    char first_line[50];
    fgets(first_line,148,fp);                //�ƶ��ļ�ָ�뵽�ڶ�������
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
void del(Link head)                             //ɾ��ѧ����Ϣ
{
    char num[10];
    printf("��������Ҫɾ����ѧ��ѧ�ţ�");
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
            printf("ѧ����Ϣ������,���������룡\n");
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
    printf("����ɾ��,���Ժ�");
    for(i=0;i<3;i++)
    {
        printf(".");
        Sleep(1000);
    }
    printf("\nɾ���ɹ�!\n");   
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
void insert(Link head)                                  //β��
{
    Link end=head->next;
    char num[10];
    while(1)
    {	
    	printf("ѧ�ţ�");
    	scanf("%s",num);
    	if(search(head,num)!=NULL)
    	{
    		printf("�����Ѿ�����,����������ѧ��!\n");
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
    printf("������");
    scanf("%s",new->name);
    printf("�ֻ���");
    scanf("%s",new->phone);
    new->daka='Y';                                      //��
    new->vaca='N';                                      //������
    new->delay_vaca.del_vaca='Y';                       //�������
    new->delay_vaca.delay_vaca='N';                     //�������
    new->delay_vaca.vaca_hour=0;
    new->delay_vaca.vaca_min=0;
    new->delay_vaca.delay_hour=0;
    new->delay_vaca.delay_min=0;
    new->delay_vaca.vaca_numbers=0;
    new->next=NULL;   
    printf("��ӳɹ�!\n");
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
                printf("δ�ҵ���Ϣ!\n");
                printf("���������룺");
                return 1;
            }
        else
            {
                char x;  
                char new_name[10],new_num[10],new_phone[13]; 
                if(x_1==0&&x_2==0&&x_3==0)              //��ʦ����������Ϣ
                {
                    printf("��Ҫ����ʲô��Ϣ��\n");
                    printf("A.���� B.ѧ�� C.�ֻ�  D.����\n");
                    fflush(stdin);
                    while(1)
                    {
                        scanf("%c",&x);
                        if(x=='A')
                        {
                            printf("����������:");
                            scanf("%s",new_name);
                            strcpy(q->name,new_name);
                            printf("���ĳɹ���\n");
                            break;
                        }
                        if(x=='B')
                        {   
                            printf("������ѧ��:");
                            scanf("%s",new_num);
                            strcpy(q->num,new_num);
                            printf("���ĳɹ���\n");
                            break;
                        }
                        if(x=='C')
                        {
                            printf("�������ֻ���:");
                            scanf("%s",new_phone);
                            strcpy(q->phone,new_phone);
                            printf("���ĳɹ���\n");
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
                            printf("���ٳɹ���\n");
                            break;
                        }
                        else
                        {
                            printf("��������,���������룡\n");
                            continue;
                        }
                    }
                }
                if(x_1==0&&x_2==0&&x_3==1)              //ѧ����
                {
                    if(q->daka=='Y')
                    {
                        printf("���Ѵ�,����һ������!\n");
                        return  9;
                    }
                    q->daka='Y';
                    printf("�򿨳ɹ�!\n");
                }    
                if(x_1==1&&x_2==0&&x_3==0)              //ѧ������
                {
                    sys_time();
                    if(q->delay_vaca.delay_vaca=='N')
                    {
                        if((sys_hour>q->delay_vaca.vaca_hour)||(sys_hour==q->delay_vaca.vaca_hour&&sys_min>q->delay_vaca.vaca_min))
                        {
                            printf("���ѳ�����Уʱ��,����ʧ��!");
                            exit(0);
                        }
                    }
                    else if(q->delay_vaca.delay_vaca=='Y')
                    {
                        if((sys_hour>q->delay_vaca.delay_hour)||(sys_hour==q->delay_vaca.delay_hour&&sys_min>q->delay_vaca.delay_min))
                        {
                            printf("���ѳ������ڷ�Уʱ��,����ʧ��!");
                            exit(0);
                        }
                        q->delay_vaca.delay_vaca='N';   //�Ƿ�������Ĭ��
                        q->delay_vaca.delay_hour=0;
                        q->delay_vaca.delay_min=0;      //���ڷ�Уʱ����Ĭ��
                    }
                    q->vaca='N';                        //��������Ĭ��
                    q->delay_vaca.del_vaca='Y';         //������� ��  ��
                    q->delay_vaca.vaca_hour=0;
                    q->delay_vaca.vaca_min=0;           //�ƻ���Уʱ����Ĭ��
                    
                    printf("���ٳɹ�!\n");
                }
                if(x_1==0&&x_2==1&&x_3==1)              //����
                {
                    int delay_hour_now,delay_min_now;
                    if(q->vaca=='N')
                    {
                        printf("��δ���,��������!");
                        exit(0);
                    }
                    while(1)
                    {
                        printf("�������ӳٷ�Уʱ��(����13:45):");
                        sys_time();
                        scanf("%d:%d",&delay_hour_now,&delay_min_now);
                        if((delay_hour_now<0||delay_hour_now>24)||(delay_min_now<0||delay_min_now>60))
                        {
                            printf("��������,����������!\n");
                            continue;
                        }
                        if((delay_hour_now<sys_hour)||(delay_hour_now==sys_hour&&delay_min_now<sys_min))
                        {
                            printf("�ӳٷ�Уʱ��Ӧ���ڵ�ǰʱ��!\n");
                            continue;
                        }
                        if(delay_hour_now>=23&&delay_hour_now<=24)
                        {
                            printf("�ӳٷ�Уʱ��Ӧ����23:00!\n");
                            continue;
                        }
                        q->delay_vaca.delay_hour=delay_hour_now;
                        q->delay_vaca.delay_min=delay_min_now;
                        q->delay_vaca.delay_vaca='Y';
                        break;
                    }
                    printf("���ڳɹ�!\n");
                }
                if(x_1==1&&x_2==1&&x_3==0)              //��Уʱ��(���)
                {   
                    int vaca_hour_now,vaca_min_now;
                    if(q->vaca=='Y')
                    {
                        printf("�������,���ܼ������!");
                        return 0;
                    }
                    while(1)
                    {
                        printf("�����뷵Уʱ��(����13:45):");
                        sys_time();
                        scanf("%d:%d",&vaca_hour_now,&vaca_min_now);
                        
                        if((vaca_hour_now<0||vaca_hour_now>24)||(vaca_min_now<0||vaca_min_now>60))
                        {
                            printf("��������,����������!\n");
                            continue;
                        }
                        if((vaca_hour_now<sys_hour)||(vaca_hour_now==sys_hour&&vaca_min_now<=sys_min))
                        {
                            printf("��Уʱ��Ӧ���ڵ�ǰʱ��!\n");
                            continue;
                        }
                        if(vaca_hour_now>=23&&vaca_hour_now<=24)
                        {
                            printf("��Уʱ��Ӧ����23:00!\n");
                            continue;
                        }
                        q->delay_vaca.vaca_hour=vaca_hour_now;
                        q->delay_vaca.vaca_min=vaca_min_now;
                        q->delay_vaca.del_vaca='N';
                        break;
                    }
                    q->vaca='Y';
                    q->delay_vaca.vaca_numbers++;
                    printf("��ٳɹ�!\n");
                }
            }
        return 2;
}
void output(Link head)
{
    Link ipos=head->next;
    printf("����\tѧ��\t�ֻ�\t�Ƿ��\t�Ƿ����\t�ۼ���ٴ���\n");
    while(ipos!=NULL)
    {
        printf("%s\t%s\t%s\t",ipos->name,ipos->num,ipos->phone);
        fflush(stdin);
        if(ipos->daka=='N')
            printf("  ��\t");
        if(ipos->daka=='Y')
            printf("  ��\t");
        if(ipos->vaca=='N')
            printf("  \t  ��\t\t");
        if(ipos->vaca=='Y')
            printf("  \t  ��\t\t");
        printf("%d",ipos->delay_vaca.vaca_numbers);
        printf("\n");
        ipos=ipos->next;
    }
}
void sort(Link head)
{
    Link pre,q,q_next,end;                      //preǰһ��  cur��ǰ��   next��һ��  
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
    Link pre,q,q_next,end;                      //preǰһ��  cur��ǰ��   next��һ��  
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
        printf("û�� δ�� �� ����� ��ѧ��!");
    }
    else if(i!=0)
    {
        printf("%dλѧ��δ���������",i);
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
        printf("����ѧ���Ѵ�!");
    }
    else
        printf("%d λѧ��δ��!",i);
    printf("\n");
}
void save(Link head)
{
        FILE *fp;
        Link p;
        fp=fopen("ѧ������.txt","wt");
        char ch1[]={"����"},ch2[]={"ѧ��"},ch3[]={"�ֻ�"},ch4[]={"�Ƿ��"},ch5[]={"�Ƿ����"},ch7='Y',ch8='N',ch0[]={"��Уʱ��"},ch9[]={"�Ƿ�����"},ch10[]={"�Ƿ�����"},ch11[]={"����ʱ��"};    
        fprintf(fp,"%s\t%s\t\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",ch1,ch2,ch3,ch4,ch5,ch0,ch9,ch10,ch11,"��ٴ���");
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