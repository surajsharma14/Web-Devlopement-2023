#include"MTH.h"
#include<string.h>
#include<math.h>
#include"conio2.h"
#include<stdio.h>
#include<error.h>
#include<dir.h>
void print_char(char ch,int reps,int row,int text_color)
{
    textcolor(text_color);
    gotoxy(1,row);
    for(int i=1;i<=reps;i++)
    {
        printf("%c",ch);
    }

}
void print_title(char *title,int column,int row,int text_color)
{
    textcolor(text_color);
    gotoxy(column,row);
    printf("%s",title);
}
void print_title_in_middle(char *title,int row,int text_color)
{
    textcolor(text_color);
    int column=(80-strlen(title))/2;
    gotoxy(column,row);
    printf("%s",title);
}
void print_basic_screen()
{
    clrscr();
    print_title_in_middle("Movie Ticket Booking App",2,MAGENTA);
    print_char('-',80,1,LIGHTCYAN);
    print_char('-',80,3,LIGHTCYAN);
    print_title("Enter \"0\" to cancel input",55,4,LIGHTGREEN);
    print_char('-',80,6,YELLOW);
    print_char('-',80,22,YELLOW);
}
void add_questions()
{
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Questions.bin","rb");
    if(fp==NULL)
    {
        fp=fopen("E:\\Movie Ticket Booking\\Questions.bin","wb");
        if(fp==NULL)
        {
            print_char(' ',79,25,BLACK);
            print_title("Error in creating the file Questions.bin\n",1,25,RED);
            perror("Reason:");
            getch();
            exit(1);
        }
        char questions[][100] = {"Which adventurous sport does your father enjoy?", "Who is your favorite sports columnist?", "Which company would you like to work for in the future?", "What is the registration number of your first vehicle?", "What is the name of your best friend?", "Who is your favorite author?", "What is your favorite food?", "What is your favorite hobby?", "What is your favorite sport?", "Where did you meet your spouse?"};
        question ques[10];
        for(int i=0;i<=9;i++)
        {
            sprintf(ques[i].question_id,"Ques-%d",i+1);
            strcpy(ques[i].question,questions[i]);
        }
        fwrite(ques,sizeof(ques),1,fp);
        //printf("\nQuestions.bin file created and saved!");
    }

    fclose(fp);
}
void set_master_admin_rec()
{
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Users.bin","rb");
    if(fp==NULL)
    {
        fp=fopen("E:\\Movie Ticket Booking\\Users.bin","wb");
        if(fp==NULL)
        {
            print_char(' ',79,25,BLACK);
            print_title("Error in creating the file Users.bin\n",1,25,RED);
            perror("Reason:");
            getch();
            exit(1);
        }
        user usr={"master_admin","Ayushee gupta","shruti07","master_admin","","","8462094444"};
        fwrite(&usr,sizeof(usr),1,fp);
        //printf("\nUsers.bin created and saved");
    }

    fclose(fp);
}
void get_string(char *str,int size)
{
    fflush(stdin);
    textcolor(RED);
    fgets(str,size,stdin);
    char *p;
    p=strchr(str,'\n');
    if(p!=NULL)
        *p='\0';
}
int is_valid_integer(char *str)
{
    while(*str)
    {
       if(isdigit(*str)==0)
           return 0;
       str++;
    }
    return 1;
}
char * get_mobile_number(int row,int column)
{
    static char mobile_number[20];
    int valid=0;
    do
    {

        print_title("Enter your mobile number: +91-",column,row,BROWN);
        get_string(mobile_number,20);
        if(strcmp(mobile_number,"0")==0)
        {
            return NULL;
        }
        if(is_valid_integer(mobile_number)==0 || strlen(mobile_number)!=10)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Error! Mobile Number Is Incorrect. Please Try Again",25,RED);
            getch();
            print_char(' ',80,25,BLACK);
            print_char(' ',80,row,BLACK);
        }
        else
            valid=1;
    }while(valid==0);

    return mobile_number;
}
int check_mobile_number_in_records(char *mob_no)
{
    FILE *fp=fopen("E:\\Movie Ticket Booking\\users.bin","rb");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Users.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return -1;
    }
    user u;
    while(fread(&u,sizeof(u),1,fp)==1)
    {
        if(strcmp(u.mobile_number,mob_no)==0)
        {
            fclose(fp);
            return 1;
        }

    }
    fclose(fp);
    return 0;
}
void get_password(char *pwd, int size)
{
    int i=0;
    char ch;
    fflush(stdin);
    textcolor(LIGHTRED);
    while(1)
    {
        ch=getch();
        if(ch==13)
            break;
        if(ch=='\b')
        {
            if(i==0)
                continue;
            i--;
            printf("\b \b");
            continue;
        }
        if(i==size-1)
            continue;
        printf("%c",ch);
        delay(100);
        printf("\b*");
        pwd[i]=ch;
        i++;
    }
    printf("\n");
    pwd[i]='\0';

}
user * get_credentials(char *usertype)
{
    print_basic_screen();
    if(strcmp(usertype,"master_admin")==0)
        print_title_in_middle("Enter Master Admin UserId And Pwd",10,LIGHTCYAN);
    static user u;
    strcpy(u.usertype,usertype);
    int valid=0;
    do
    {
        print_title("Enter user id:",30,12,BROWN);
        get_string(u.userid,100);
        if(strcmp(u.userid,"0")==0)
            return NULL;
        if(strlen(u.userid)==0)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Error! Userid Cannot Be Blank. Please Try Again",25,RED);
            getch();
        }
        else
        {
            valid=1;
        }

    }while(valid==0);
    valid=0;
    do
    {
        print_title("Enter password:",30,14,BROWN);
        get_password(u.password,100);
        if(strcmp(u.password,"0")==0)
            return NULL;
        if(strlen(u.password)==0)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Error! Password Cannot Be Blank. Please Try Again",25,RED);
            getch();
        }
        else
        {
            valid=1;
        }

    }while(valid==0);
    return &u;
}
int check_user_details(user *u)
{
    FILE *fp=fopen("E:\\Movie Ticket Booking\\users.bin","rb");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Users.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return -1;
    }
    user usr;
    int found=0;
    char temp[200];
    while(fread(&usr,sizeof(usr),1,fp)==1)
    {
        if(strcmp(u->usertype,"master_admin")==0)
        {
            //display the details of master admin
            print_title_in_middle("Contact with admin if you have any trouble during logging",20,YELLOW);
            strcpy(temp,"Admin Name:");
            strcat(temp,usr.username);
            print_title_in_middle(temp,23,YELLOW);
            strcpy(temp,"Admin Contact Details:");
            strcat(temp,usr.mobile_number);
            print_title_in_middle(temp,24,YELLOW);
        }
        if(strcmp(usr.userid,u->userid)==0 && strcmp(usr.password,u->password)==0 && strcmp(usr.usertype,u->usertype)==0)
        {
            found=1;
            *u=usr;
            break;
        }
    }
    fclose(fp);
    return found;

}
user * login(char *usertype)
{
    user *usr;
    char temp[100];
    for(int i=1;i<=3;i++)
    {
        usr=get_credentials(usertype);
        if(usr==NULL)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Login Cancelled",25,BLUE);
            getch();
            break;
        }
        else
        {
            if(check_user_details(usr)==1)
            {
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Login Accepted",25,GREEN);
                getch();
                return usr;
            }
            else
            {
                if(i!=3)
                {
                    sprintf(temp,"%d attempts left",3-i);
                    print_title(temp,67,8,DARKGRAY);
                    print_char(' ',80,25,BLACK);
                    print_title_in_middle("Invalid Userid/Password",25,RED);
                    getch();

                }
                else
                {
                  print_char(' ',80,25,BLACK);
                  print_title_in_middle("Login Denied",25,RED);
                  getch();
                }



            }
        }
    }
    return NULL;
}
void input_password(user *u,int column,int row)
{
    char pwd1[100],pwd2[100];
    int valid=0;
    do
    {
        do
        {
            print_title("Enter password:",column,row,BROWN);
            get_string(pwd1,100);
            if(strcmp(pwd1,"0")==0){
                strcpy(u->password,"0");
                return;
            }
            if(strlen(pwd1)>=1){
                valid=1;
            }
            else{
                  print_char(' ',80,25,BLACK);
                  print_title_in_middle("Password cannot be blank",25,RED);
                  getch();
                  print_char(' ',80,row,BLACK);
                }

        }while(valid==0);
        valid=0;
        do
        {
            print_title("Re-Type password:",column,row+2,BROWN);
            get_password(pwd2,100);
            if(strcmp(pwd2,"0")==0){
                strcpy(u->password,"0");
                return;
            }
            if(strlen(pwd2)>=1){
                valid=1;
            }
            else{
                  print_char(' ',80,25,BLACK);
                  print_title_in_middle("Password cannot be blank",25,RED);
                  getch();
                  print_char(' ',80,row+2,BLACK);
                }
        }while(valid==0);
        valid=0;
        if(strcmp(pwd1,pwd2)!=0){
                  print_char(' ',80,25,BLACK);
                  print_title_in_middle("Passwords do not match. Try Again",25,RED);
                  getch();
                  print_char(' ',80,row,BLACK);
                  print_char(' ',80,row+2,BLACK);
        }
        else{
            valid=1;
        }
    }while(valid==0);
    strcpy(u->password,pwd1);
    return;
}
char * get_question_id()
{
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Questions.bin","rb");
    if(fp==NULL)
    {
            print_char(' ',79,25,BLACK);
            print_title("Error in opening the file Questions.bin\n",1,25,RED);
            perror("Reason:");
            getch();
            return NULL;
    }
    print_basic_screen();
    print_title("Question ID",5,8,YELLOW);
    print_title("Question",40,8,YELLOW);
    int row_no=10;
    int column_que_id=6;
    question que;
    while(fread(&que,sizeof(que),1,fp)==1){
        print_title(que.question_id,column_que_id,row_no,YELLOW);
        print_title(que.question,column_que_id+18,row_no,YELLOW);
        row_no++;
    }
    int valid=0;
    int id;
    static char question_id[100];
    do{
        print_title("Enter Question ID: Ques-",25,23,BROWN);
        get_integer(&id);
        if(id==0){
            fclose(fp);
            return NULL;
        }
        if(id==-1){
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Invalid Number",25,RED);
            getch();
            print_char(' ',80,23,BLACK);
        }
        else{
            sprintf(question_id,"Ques-%d",id);
            rewind(fp);
            while(fread(&que,sizeof(que),1,fp)==1){
                    if(strcmp(question_id,que.question_id)==0){
                        valid=1;
                        break;
                    }
            }
            if(valid==0){
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Question Id Is Incorect. Try Again",25,RED);
                getch();
                print_char(' ',80,23,BLACK);
            }
        }

    }while(valid==0);
    fclose(fp);
    return question_id;

}
void get_integer(int *p)
{
    char temp[100];
    get_string(temp,100);
    if(strcmp(temp,"0")==0){
        *p=0;
        return;
    }
    if(strlen(temp)==0 || is_valid_integer(temp)==0){
            *p=-1;
             return;
    }
    *p=atoi(temp);
}
user* get_user_details(char *usertype)
{
    print_basic_screen();
    char msg[100]={"Registration Of "};
    strcat(msg,usertype);
    print_title_in_middle(msg,5,LIGHTGRAY);
    int row=8,column=25;
    print_title_in_middle("Enter Details Carefully",row,DARKGRAY);
    print_title("Enter Username:",column,row+2,BROWN);
    static user u;
    get_string(u.username,100);
    if(strcmp(u.username,"0")==0){
        return NULL;
    }
    input_password(&u,column,row+4);
    if(strcmp(u.password,"0")==0){
        return NULL;
    }
    int valid=0;
    char *p;
    do{
        p=get_mobile_number(row+8,column);
        if(p==NULL){
            return NULL;
        }
        if(check_mobile_number_in_records(p)==1){
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Mobile Number Already Registered. Try Again",25,RED);
                getch();
                print_char(' ',80,row+8,BLACK);
        }else{
            valid=1;
        }

    }while(valid==0);
    strcpy(u.mobile_number,p);
    p=get_question_id();
    if(p==NULL){
        return NULL;
    }
    strcpy(u.question_id,p);
    valid=0;
    do{
        print_title("Enter Hint Answer:",25,24,BROWN);
        get_string(u.hint_answer,100);
        if(strcmp(u.hint_answer,"0")==0)
        {
            printf("Hint answer is null");
            getch();
            return NULL;
        }

        if(strlen(u.hint_answer)>=1)
            valid=1;
        else
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Answer Cannot Be Blank. Try Again",25,RED);
            getch();
            print_char(' ',80,24,BLACK);
        }

    }while(valid==0);
    return &u;

}
void create_user(char *usertype)
{
    FILE *fp=fopen("E:\\Movie Ticket Booking\\users.bin","ab+");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Users.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        exit(1);
    }
    user usr;
    user *up;
    char *p;
    char temp[100];
    if(strcmp(usertype,"admin")==0){
        fseek(fp,-(long long signed int)sizeof(usr),SEEK_END);
        fread(&usr,sizeof(usr),1,fp);
        if(strcmp(usr.usertype,"master_admin")!=0)
            return;
        up=login("master_admin");
        if(up!=NULL){
            up=get_user_details("admin");
            if(up==NULL){
                printf("up is null");
                getch();
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Cancelling The Admin Profile SetUp",25,RED);
                fclose(fp);
                getch();
                exit(0);
            }
            strcpy(up->userid,"admin");
            strcpy(up->usertype,"admin");
            //set fp to end
            fseek(fp,0,SEEK_END);
            fwrite(up,sizeof(user),1,fp);
            print_basic_screen();
            print_title_in_middle("Admin Registered Successfully!",10,YELLOW);
            strcpy(temp,"User Name: ");
            strcat(temp,up->username);
            print_title_in_middle(temp,13,YELLOW);
            strcpy(temp,"User ID: ");
            strcat(temp,up->userid);
            print_title_in_middle(temp,15,YELLOW);
            strcpy(temp,"Mobile Number: ");
            strcat(temp,up->mobile_number);
            print_title_in_middle(temp,17,YELLOW);
            getch();
        }
        else{
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Cancelling The Admin Profile SetUp",25,RED);
                fclose(fp);
                getch();
                exit(0);
        }
    }
    else if(strcmp(usertype,"user")==0){
        fseek(fp,-(long long signed int)sizeof(usr),SEEK_END);
        fread(&usr,sizeof(usr),1,fp);
        if(strcmp(usr.usertype,"admin")==0){
            sprintf(temp,"USER-%d",1);
        }else{
            p=strchr(usr.userid,'-');
            int last_id=atoi(p+1);
            ++last_id;
            sprintf(temp,"USER-%d",last_id);
        }
        up=get_user_details("user");
        if(up==NULL){
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Cancelling The User Profile SetUp",25,RED);
                fclose(fp);
                getch();
                exit(0);
            }
       strcpy(up->userid,temp);
       strcpy(up->usertype,"user");
       fseek(fp,0,SEEK_END);
       fwrite(up,sizeof(user),1,fp);
       print_basic_screen();
       print_title_in_middle("User Registered Successfully!",10,YELLOW);
       strcpy(temp,"User Name: ");
       strcat(temp,up->username);
       print_title_in_middle(temp,13,YELLOW);
       strcpy(temp,"User ID: ");
       strcat(temp,up->userid);
       print_title_in_middle(temp,15,YELLOW);
       strcpy(temp,"Mobile Number: ");
       strcat(temp,up->mobile_number);
       print_title_in_middle(temp,17,YELLOW);
       getch();
    }
    fclose(fp);
}
int enter_login_choice(){
    print_basic_screen();
    print_title_in_middle("Select An Option",9,YELLOW);
    int column=32,row=10;
    print_title("1. Admin",column,++row,YELLOW);
    print_title("2. User(Login)",column,++row,YELLOW);
    print_title("3. User(Sign-Up)",column,++row,YELLOW);
    int choice,valid=0;
    do
    {
        print_title_in_middle("Enter Your Choice:",row+1,YELLOW);
        get_integer(&choice);
        if(choice==-1){
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Only Digits Allowed! Try Again",25,RED);
            getch();
            print_char(' ',80,row+1,BLACK);
        }
        else
            valid=1;

    }while(valid==0);
    return choice;
}
int enter_choice(user *ur)
{
    print_basic_screen();
    char temp[100];
    sprintf(temp,"%s: %s",ur->usertype,ur->username);
    print_title(temp,1,5,YELLOW);
    print_title_in_middle("Select An Option:",8,YELLOW);
    int row,column;
    if(strcmp(ur->usertype,"admin")==0){
        row=9,column=28;
        print_title("1. Add Theater",column,++row,YELLOW);
        print_title("2. Show Theater",column,++row,YELLOW);
        print_title("3. Delete Theater",column,++row,YELLOW);
        print_title("4. Add Movie",column,++row,YELLOW);
        print_title("5. Show Movie",column,++row,YELLOW);
        print_title("6. Delete Movie",column,++row,YELLOW);
        print_title("7. Change Contact Details",column,++row,YELLOW);
        print_title("8. Change Security Question",column,++row,YELLOW);
        print_title("9. Change Password",column,++row,YELLOW);
        print_title("10. View My Profile",column,++row,YELLOW);

    }else{
        row=10,column=28;
        print_title("1. Show Movie",column,++row,YELLOW);
        print_title("2. Book Ticket",column,++row,YELLOW);
        print_title("3. View Bookings",column,++row,YELLOW);
        print_title("4. Cancel Bookings",column,++row,YELLOW);
        print_title("5. Change Contact Details",column,++row,YELLOW);
        print_title("6. Change Security Question",column,++row,YELLOW);
        print_title("7. Change Password",column,++row,YELLOW);
        print_title("8. View My Profile",column,++row,YELLOW);
        print_title("9. Delete My Account",column,++row,YELLOW);


    }
    int choice,valid=0;
    do{
        print_title_in_middle("Enter Your Choice: ",row+2,YELLOW);
        get_integer(&choice);
        if(choice==-1)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Only Digits Allowed! Try Again",25,RED);
            getch();
            print_char(' ',80,row+2,BLACK);
        }
        else{
            valid=1;
        }
    }while(valid==0);
    return choice;
}
void add_theater()
{
    print_basic_screen();
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Theaters.bin","ab+");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Theaters.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return;
    }
    theater th;
    char *p;
    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
        strcpy(th.theater_id,"THEATER-1");
    }
    else
    {
       fseek(fp,-(long long signed int)sizeof(th),SEEK_END);
       fread(&th,sizeof(th),1,fp);
       p=strchr(th.theater_id,'-');
       int last_id=atoi(p+1);
       ++last_id;
       sprintf(th.theater_id,"THEATER-%d",last_id);
    }
    th.is_booked=0;
    int valid=0;
    do
    {
        print_title("Enter Theater Name:",25,12,YELLOW);
        get_string(th.theater_name,100);
        if(strcmp(th.theater_name,"0")==0)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Cancelling Add Theater",25,RED);
            fclose(fp);
            getch();
            return;
        }
        if(strlen(th.theater_name)==0)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Theater Name Cannot Be Empty! Try Again",25,RED);
            getch();
            print_char(' ',80,12,BLACK);
        }
        else
            valid=1;

    }while(valid==0);
    fseek(fp,0,SEEK_END);
    fwrite(&th,sizeof(th),1,fp);
    fclose(fp);
    char temp[100];
    strcpy(temp,"Theater Addedd Successfully! Theater Id Is ");
    strcat(temp,th.theater_id);
    print_title_in_middle(temp,15,YELLOW);
    getch();
}
void show_theater()
{
    print_basic_screen();
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Theaters.bin","rb");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Theaters.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return;
    }
    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
        print_char(' ',80,25,BLACK);
        print_title_in_middle("No Theaters Present In The File",25,RED);
        fclose(fp);
        getch();
        return;
    }
    rewind(fp);
    int row=8;
    print_title("Theater ID",5,row,YELLOW);
    print_title("Theater Name",20,row,YELLOW);
    print_title("Theater Booking Status",40,row,YELLOW);
    theater th;
    char temp[100];
    row+=2;
    while(fread(&th,sizeof(th),1,fp)==1)
    {
        print_title(th.theater_id,5,row,YELLOW);
        print_title(th.theater_name,20,row,YELLOW);
        if(th.is_booked==0)
        {
            strcpy(temp,"Available For Booking");
        }
        else
        {
            strcpy(temp,"Already Booked");
        }
        print_title(temp,40,row,YELLOW);
        row++;
    }
    fclose(fp);
    getch();
}
char * get_theater_id(int status)
{
    print_basic_screen();
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Theaters.bin","rb");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Theaters.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return NULL;
    }
    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
        print_char(' ',80,25,BLACK);
        print_title_in_middle("No Theaters Present In The File",25,RED);
        fclose(fp);
        getch();
        return NULL;
    }
    rewind(fp);
    static char th_id[100];
    int row=8;
    print_title("Theater ID",5,row,YELLOW);
    print_title("Theater Name",20,row,YELLOW);
    print_title("Theater Booking Status",40,row,YELLOW);
    theater th;
    row+=2;
    while(fread(&th,sizeof(th),1,fp)==1)
    {
        if(th.is_booked==0)
        {
           print_title(th.theater_id,5,row,YELLOW);
           print_title(th.theater_name,20,row,YELLOW);
           print_title("Available For Booking",45,row,YELLOW);
        }
        else
        {
            if(status==1)
                continue;
           print_title(th.theater_id,5,row,YELLOW);
           print_title(th.theater_name,20,row,YELLOW);
           print_title("Already Booked",45,row,YELLOW);
        }
        row++;

    }
    int valid=0;
    int id;
    do
    {
        print_title("Enter Theater ID: THEATER-",25,23,YELLOW);
        get_integer(&id);
        if(id==0)
        {
            fclose(fp);
            return NULL;
        }
        if(id==-1)
        {
            print_char(' ',80,25,BLACK);
            print_title_in_middle("Only Digits Allowed. Try Again",25,RED);
            getch();
            print_char(' ',80,23,BLACK);
        }
        else
        {
            sprintf(th_id,"THEATER-%d",id);
            rewind(fp);
             while(fread(&th,sizeof(th),1,fp)==1)
             {
                 if(status==0)
                 {
                     if(strcmp(th.theater_id,th_id)==0)
                     {
                         valid=1;
                         break;
                     }
                 }
                 else
                 {
                     if(strcmp(th.theater_id,th_id)==0 && th.is_booked==0)
                     {
                         valid=1;
                         break;
                     }
                 }
             }
             if(valid==0)
             {
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Invalid ID. Try Again",25,RED);
                getch();
                print_char(' ',80,23,BLACK);
             }

        }

    }while(valid==0);
    fclose(fp);
    return th_id;
}

int delete_booking_by_movie_id(char* movie_id)
{
    print_basic_screen();
    FILE *fp1=fopen("E:\\Movie Ticket Booking\\Bookings.bin","rb");
    if(fp1==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Bookings.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return 0;
    }
    FILE *fp2=fopen("E:\\Movie Ticket Booking\\TempBookings.bin","wb");
    if(fp2==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file TempBookings.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        fclose(fp1);
        return 0;
    }
    ticket tk;
    while(fread(&tk,sizeof(tk),1,fp1)==1)
    {
        if(strcmp(tk.movie_id,movie_id)!=0)
        {
            fwrite(&tk,sizeof(tk),1,fp2);
        }

    }
    fclose(fp1);
    fclose(fp2);
    int x,y;
    x=remove("E:\\Movie Ticket Booking\\Bookings.bin");
    if(x==0)
    {
        y=rename("E:\\Movie Ticket Booking\\TempBookings.bin","E:\\Movie Ticket Booking\\Bookings.bin");
        if(y==0)
            return 1;
    }
    return 0;
}
int delete_movie_by_theater_id(char *th_id)
{
    FILE *fp1=fopen("E:\\Movie Ticket Booking\\Movies.bin","rb");
    if(fp1==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Movies.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return 0;
    }
    FILE *fp2=fopen("E:\\Movie Ticket Booking\\TempMovies.bin","wb");
    if(fp2==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file TempMovies.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        fclose(fp1);
        return 0;
    }
    movie mov;
    while(fread(&mov,sizeof(mov),1,fp1)==1)
    {
        if(strcmp(mov.theater_id,th_id)!=0)
        {
            fwrite(&mov,sizeof(mov),1,fp2);
        }
        else
        {
            int resp=delete_booking_by_movie_id(mov.movie_id);
            if(resp==0)
            {
                fclose(fp1);
                fclose(fp2);
                remove("E:\\Movie Ticket Booking\\TempMovies.bin");
                return 0;
            }
        }

    }
    fclose(fp1);
    fclose(fp2);
    int x,y;
    x=remove("E:\\Movie Ticket Booking\\Movies.bin");
    if(x==0)
    {
        y=rename("E:\\Movie Ticket Booking\\TempMovies.bin","E:\\Movie Ticket Booking\\Movies.bin");
        if(y==0)
            return 1;
    }
    return 0;
}
int delete_theater()
{
   char *theater_id=get_theater_id(0);
   if(theater_id==NULL)
   {
        print_char(' ',80,25,BLACK);
        print_title_in_middle("Cancelling Delete Theater",25,RED);
        getch();
        return 0;
   }
   FILE *fp1=fopen("E:\\Movie Ticket Booking\\Theaters.bin","rb");
   if(fp1==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Theaters.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return 0;
    }
   FILE *fp2=fopen("E:\\Movie Ticket Booking\\TempTheaters.bin","wb");
    if(fp2==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file TempTheaters.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        fclose(fp1);
        return 0;
    }
    theater th;
    while(fread(&th,sizeof(th),1,fp1)==1)
    {
         if(strcmp(th.theater_id,theater_id)!=0)
         {
             fwrite(&th,sizeof(th),1,fp2);
         }
         else
         {
             if(th.is_booked==1)
             {
                 int resp=delete_movie_by_theater_id(th.theater_id);
                 if(resp==0)
                 {
                    fclose(fp1);
                    fclose(fp2);
                    remove("E:\\Movie Ticket Booking\\TempTheaters.bin");
                    return 0;
                 }
             }
         }
    }
    fclose(fp1);
    fclose(fp2);
    int x,y;
    x=remove("E:\\Movie Ticket Booking\\Theaters.bin");
    if(x==0)
    {
        y=rename("E:\\Movie Ticket Booking\\TempTheaters.bin","E:\\Movie Ticket Booking\\Theaters.bin");
        if(y==0)
            return 1;

    }
    return 0;

}
int is_leap_year(int year)
{
    if((year%4==0&&year%100!=0)||year%400==0)
        return 1;
    return 0;
}
int compare_date(struct tm first,struct tm sec)
{
    if(first.tm_year==sec.tm_year)
    {
        if(first.tm_mon==sec.tm_mon)
        {
            if(first.tm_mday==sec.tm_mday)
                return 0;
            else if(first.tm_mday>sec.tm_mday)
                return 1;
            else
                return -1;

        }
        else if(first.tm_mon>sec.tm_mon)
            return 1;
        else
            return -1;
    }
    else if(first.tm_year>sec.tm_year)
        return 1;
    else
        return  -1;
}
int is_valid_date(struct tm date)
{
    int leap_result=is_leap_year(date.tm_year);
    if((date.tm_mday>=1 && date.tm_mday<=31)&&(date.tm_mon==1 ||date.tm_mon==3||date.tm_mon==5||date.tm_mon==7||date.tm_mon==8||date.tm_mon==10||date.tm_mon==12))
        return 1;
    else if((date.tm_mday>=1 && date.tm_mday<=30)&&(date.tm_mon==4 ||date.tm_mon==6||date.tm_mon==9||date.tm_mon==11))
        return 1;
    else if(date.tm_mon==2&& date.tm_mday>=1 && date.tm_mday<=28 && leap_result==0)
        return 1;
    else if(date.tm_mon==2 && date.tm_mday>=1 && date.tm_mday<=29 && leap_result==1)
        return 1;
    else
        return 0;


}
void change_theater_booking_status(char * th_id)
{
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Theaters.bin","rb+");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Theaters.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return;
    }
    theater th;
    while(fread(&th,sizeof(th),1,fp)==1)
    {
        if(strcmp(th.theater_id,th_id)==0)
        {
            th.is_booked=!th.is_booked;
            fseek(fp,-4,SEEK_CUR);
            fwrite(&th.is_booked,sizeof(int),1,fp);
            break;
        }
    }
    fclose(fp);
}
void add_movie()
{
    char *theater_id=get_theater_id(0);
    if(theater_id==0)
    {
        print_char(' ',80,25,BLACK);
        print_title_in_middle("Cancelling add movie",25,RED);
        getch();
        return 0;
    }
    print_basic_screen();
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Movies.bin","ab+");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Movies.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return 0;
    }
    movie mov;
    char *p;
    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
        strcpy(mov.movie_id,"MOVIE-1");
    }
    else
    {
       fseek(fp,-(long long signed int)sizeof(mov),SEEK_END);
       fread(&mov,sizeof(mov),1,fp);
       p=strchr(mov.movie_id,'-');
       int last_id=atoi(p+1);
       ++last_id;
       sprintf(mov.movie_id,"MOVIE-%d",last_id);
    }
    strcpy(mov.theater_id,theater_id);

    int valid=0,column=25;
    do
    {
        print_title("Enter movie name:",column,8,YELLOW);
        get_string(mov.movie_name,100);
        if(strcmp(mov.movie_name,"0")==0)
        {
           print_char(' ',80,25,BLACK);
           print_title_in_middle("Cancelling Add Movie",25,RED);
           getch();
           return;
        }
        if(strlen(mov.movie_name)==0)
        {
           print_char(' ',80,25,BLACK);
           print_title_in_middle("Movie Name Cannot Be Blank",25,RED);
           getch();
           print_char(' ',80,8,BLACK);
        }
        else
            valid=1;

    }while(valid==0);
    valid=0;
    do
    {
        print_title("Enter First Block Price:",column,10,YELLOW);
        get_integer(&mov.first_block_price);
        if(mov.first_block_price==0)
        {
           print_char(' ',80,25,BLACK);
           print_title_in_middle("Cancelling Add Movie",25,RED);
           getch();
           return;
        }
        if(mov.first_block_price==-1)
        {
           print_char(' ',80,25,BLACK);
           print_title_in_middle("Only Digits Allowed!",25,RED);
           getch();
           print_char(' ',80,10,BLACK);
        }
        else
            valid=1;

    }while(valid==0);
    valid=0;
    do
    {
        print_title("Enter Second Block Price:",column,12,YELLOW);
        get_integer(&mov.second_block_price);
        if(mov.second_block_price==0)
        {
           print_char(' ',80,25,BLACK);
           print_title_in_middle("Cancelling Add Movie",25,RED);
           getch();
           return;
        }
        if(mov.second_block_price==-1)
        {
           print_char(' ',80,25,BLACK);
           print_title_in_middle("Only Digits Allowed!",25,RED);
           getch();
           print_char(' ',80,12,BLACK);
        }
        else
            valid=1;

    }while(valid==0);
    valid=0;
    do
    {
        print_title("Enter Third Block Price:",column,14,YELLOW);
        get_integer(&mov.third_block_price);
        if(mov.third_block_price==0)
        {
           print_char(' ',80,25,BLACK);
           print_title_in_middle("Cancelling Add Movie",25,RED);
           getch();
           return;
        }
        if(mov.third_block_price==-1)
        {
           print_char(' ',80,25,BLACK);
           print_title_in_middle("Only Digits Allowed!",25,RED);
           getch();
           print_char(' ',80,14,BLACK);
        }
        else
            valid=1;

    }while(valid==0);

   time_t now;
   time(&now);
   struct tm * ptr=localtime(&now);
   struct tm today=*ptr;
   today.tm_mon++;
   today.tm_year+=1900;
   valid=0;
   do
   {
       print_title("Enter Final Date:",column,16,YELLOW);
       scanf("%d/%d/%d",&mov.show_date.tm_mday,&mov.show_date.tm_mon,&mov.show_date.tm_year);
       if(mov.show_date.tm_mday==0)
       {
           print_char(' ',80,25,BLACK);
           print_title_in_middle("Cancelling Add Movie",25,RED);
           getch();
           return;
       }
       if(compare_date(mov.show_date,today)<0)
       {
           print_char(' ',80,25,BLACK);
           print_title_in_middle("Final Date Cannot Be Lesser Than Current Date",25,RED);
           getch();
          print_char(' ',80,16,BLACK);
       }
       else
        valid=1;

   }while(valid==0);
   change_theater_booking_status(mov.theater_id);
   for(int i=0;i<100;i++)
   {
       mov.seats[i].seat_is_booked=0;
       mov.seats[i].seat_number=i+1;
   }
   struct tm start=today;
   struct tm end=mov.show_date;
   fseek(fp,0,SEEK_END);
   while(compare_date(start,end)<=0)
   {
       mov.show_date=start;
       fwrite(&mov,sizeof(mov),1,fp);
       start.tm_mday++;
       if(is_valid_date(start)==0)
       {
           start.tm_mon++;
           start.tm_mday=1;
           if(is_valid_date(start)==0)
           {
               start.tm_year++;
               start.tm_mon=1;
           }
       }

   }
   fclose(fp);
   char temp[100];
   print_basic_screen();
   print_title_in_middle("movie added successfully",8,YELLOW);
   strcpy(temp,"movie ID: ");
   strcat(temp,mov.movie_id);
   print_title(temp,25,10,YELLOW);
   strcpy(temp,"movie name: ");
   strcat(temp,mov.movie_name);
   print_title(temp,25,9,YELLOW);
   strcpy(temp,"theater ID: ");
   strcat(temp,mov.theater_id);
   print_title(temp,25,10,YELLOW);
   sprintf(temp,"First block prize: %d",mov.first_block_price);
   print_title(temp,25,10,YELLOW);
   sprintf(temp,"Second block prize: %d",mov.second_block_price);
   print_title(temp,25,11,YELLOW);
   sprintf(temp,"Third block prize: %d",mov.third_block_price);
   print_title(temp,25,12,YELLOW);
   sprintf(temp,"Final date: (%02d/%02d/%04d)",mov.show_date.tm_mday,mov.show_date.tm_mon,mov.show_date.tm_year);
   print_title(temp,25,13,YELLOW);
   getch();
}
char * get_theater_name(char*th_id)
{
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Theaters.bin","rb");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Theaters.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return NULL;
    }
    theater th;
    static char th_name[100];
    while(fread(&th,sizeof(th),1,fp)==1)
    {
        if(strcmp(th_id,th.theater_id)==0)
        {
            strcpy(th_name,th.theater_name);
            break;
        }
    }
    fclose(fp);
    return th_name;

}
void show_movie()
{
    int row=8;
    print_basic_screen();
     FILE *fp=fopen("E:\\Movie Ticket Booking\\Movies.bin","rb");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Movies.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return;
    }
    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
        print_char(' ',79,25,BLACK);
        print_title("no movie is present\n",1,25,RED);
        perror("Reason:");
        getch();
        return;
    }
    print_title("Theater name",1,row,BLUE);
    print_title("Movie name",23,row,BLUE);
    print_title("First block",40,row,BLUE);
    print_title("Second block",55,row,BLUE);
    print_title("Third block",68,row,BLUE);
    rewind(fp);
    movie mov;
    row+=2;
    char prev_mov_id[100]={""};
    char temp_str[100];
    while(fread(&mov,sizeof(mov),1,fp)==1)
    {

         if(strcmp(mov.movie_id,prev_mov_id)!=0)
        {
            strcpy(temp_str,get_theater_name(mov.theater_id));
            print_title(temp_str,2,row,YELLOW);

            strcpy(temp_str,mov.movie_name);
            print_title(temp_str,24,row,YELLOW);

            sprintf(temp_str,"%d",mov.first_block_price);
            print_title(temp_str,43,row,YELLOW);

            sprintf(temp_str,"%d",mov.second_block_price);
            print_title(temp_str,58,row,YELLOW);

            sprintf(temp_str,"%d",mov.third_block_price);
            print_title(temp_str,73,row,YELLOW);

            strcpy(prev_mov_id,mov.movie_id);
            row++;
        }
    }
   fclose(fp);
   getch();
}
void change_contact_details(user *u)
{
    print_basic_screen();
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Users.bin","rb+");
    if(fp==NULL)
        {
            print_char(' ',79,25,BLACK);
            print_title("Error in opening the file Users.bin\n",1,25,RED);
            perror("Reason:");
            getch();
           return;
        }
    char choice;
    print_title_in_middle("Are you sure to change the contact details(Y/y/N/n):",10,YELLOW);
    fflush(stdin);
    scanf("%c",&choice);
    if(choice=='n'|| choice=='N')
    {
        print_char(' ',79,25,BLACK);
        print_title_in_middle("Cancelling Change Contact Details",25,RED);
        getch();
    }
    else if(choice=='Y'||choice=='y')
    {
        char *mobile_no;
        int result;
        do
        {
            mobile_no=get_mobile_number(15,25);
            result=check_mobile_number_in_records(mobile_no);
            if(result==1)
            {
                print_char(' ',79,25,BLACK);
                print_title_in_middle("Mobile Number Already Taken!. Try Again!",25,RED);
                getch();
                print_char(' ',79,15,BLACK);
            }
            else
                break;

        }while(1);
        rewind(fp);
        user us;
        while(fread(&us,sizeof(us),1,fp)==1)
        {
            if(strcmp(us.userid,u->userid)==0)
            {
                strcpy(u->mobile_number,mobile_no);
                fseek(fp,-(long long signed int)sizeof(user),SEEK_CUR);
                fwrite(u,sizeof(user),1,fp);
                break;
            }
        }
        print_char(' ',79,25,BLACK);
        print_title_in_middle("Mobile Number Changed Successfully!",25,LIGHTGREEN);
        getch();
    }
    else
    {
        print_char(' ',79,25,BLACK);
        print_title_in_middle("Invalid Choice",25,RED);
        getch();
    }
    fclose(fp);
}
void show_my_profile(user *u)
{
    print_basic_screen();
    int column=32;
    char temp[100];
    sprintf(temp,"%s profile",u->usertype);
    print_title_in_middle(temp,8,YELLOW);
    sprintf(temp,"User Name:%s",u->username);
    print_title(temp,column,10,YELLOW);

    sprintf(temp,"User ID:%s",u->userid);
    print_title(temp,column,12,YELLOW);

    sprintf(temp,"Mobile Number:%s",u->mobile_number);
    print_title(temp,column,14,YELLOW);

    sprintf(temp,"Security Question ID:%s",u->question_id);
    print_title(temp,column,16,YELLOW);

    sprintf(temp,"Hint Answer:%s",u->hint_answer);
    print_title(temp,column,18,YELLOW);

    sprintf(temp,"Password:%s",u->password);
    print_title(temp,column,20,YELLOW);

    getch();
}
void change_password(user *u)
{
    print_basic_screen();
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Users.bin","rb+");
    if(fp==NULL)
        {
            print_char(' ',79,25,BLACK);
            print_title("Error in opening the file Users.bin\n",1,25,RED);
            perror("Reason:");
            getch();
            return;
        }
    char choice;
    print_title_in_middle("Are you sure to change the password(Y/y/N/n):",10,YELLOW);
    fflush(stdin);
    scanf("%c",&choice);
    if(choice=='n'|| choice=='N')
    {
        print_char(' ',79,25,BLACK);
        print_title_in_middle("Cancelling Change Password",25,RED);
        getch();
    }
    else if(choice=='Y'||choice=='y')
    {
       user us;
       input_password(&us,30,12);
       if(strcmp(us.password,"0")==0)
       {
           fclose(fp);
           print_char(' ',79,25,BLACK);
           print_title_in_middle("Cancelling Change Password",25,RED);
           getch();
           return;
       }
       strcpy(u->password,us.password);
       rewind(fp);
       while(fread(&us,sizeof(us),1,fp)==1)
        {
            if(strcmp(us.userid,u->userid)==0)
            {
                fseek(fp,-(long long signed int)sizeof(user),SEEK_CUR);
                fwrite(u,sizeof(user),1,fp);
                break;
            }
        }
        print_char(' ',79,25,BLACK);
        print_title_in_middle("Password Changed Successfully!",25,LIGHTGREEN);
        getch();
    }
        else
        {
        print_char(' ',79,25,BLACK);
        print_title_in_middle("Invalid Choice",25,RED);
        getch();
        }
    fclose(fp);
}
movie *get_movie_id_and_show_date()
{
    print_basic_screen();
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Movies.bin","rb");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Movies.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return NULL;
    }
    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
        print_char(' ',79,25,BLACK);
        print_title_in_middle("Movie Details Not Present",25,RED);
        fclose(fp);
        getch();
        return NULL;
    }
    rewind(fp);
    int row=8;
    print_title("Movie ID",1,row,YELLOW);
    print_title("Movie Name",10,row,YELLOW);
    print_title("First Block Price",25,row,YELLOW);
    print_title("Second Block Price",44,row,YELLOW);
    print_title("Third Block Price",64,row,YELLOW);

    rewind(fp);
    static movie mov;


    row+=2;
    char prev_mov_id[100]={""};
    char temp_str[100];

    while(fread(&mov,sizeof(mov),1,fp)==1)
    {

         if(strcmp(mov.movie_id,prev_mov_id)!=0)
        {
            print_title(mov.movie_id,1,row,YELLOW);
            print_title(mov.movie_name,10,row,YELLOW);

            sprintf(temp_str,"%d",mov.first_block_price);
            print_title(temp_str,25,row,YELLOW);

            sprintf(temp_str,"%d",mov.second_block_price);
            print_title(temp_str,44,row,YELLOW);

            sprintf(temp_str,"%d",mov.third_block_price);
            print_title(temp_str,64,row,YELLOW);

            strcpy(prev_mov_id,mov.movie_id);
            row++;
        }
    }
    int id,valid=0;
    char mov_id[100];
    struct tm date;
    time_t now;
    time(&now);
    struct tm current=*(localtime(&now));
    current.tm_mon++;
    current.tm_year+=1900;

    do
    {
        print_title("Enter Movie ID: MOVIE-",25,23,BROWN);
        get_integer(&id);
        if(id==0)
        {
            fclose(fp);
            return NULL;
        }
        if(id==-1)
        {
           print_char(' ',80,25,BLACK);
           print_title_in_middle("Movie ID Must Be Numeric",25,RED);
           getch();
           print_char(' ',80,23,BLACK);
        }
        else
        {
            sprintf(mov_id,"MOVIE-%d",id);
            rewind(fp);
            while(fread(&mov,sizeof(mov),1,fp)==1)
            {
                if(strcmp(mov.movie_id,mov_id)==0)
                {
                    valid=1;
                    break;
                }
            }
            if(valid==0)
            {
                print_char(' ',80,25,BLACK);
                print_title_in_middle("Invalid Movie ID",25,RED);
                getch();
                print_char(' ',80,23,BLACK);
            }
        }
        if(valid==1)
        {
            row=8;
            print_basic_screen();
            print_title("Movie ID",5,row,YELLOW);
            print_title("Movie Name",20,row,YELLOW);
            print_title("Show Date",40,row,YELLOW);
            row+=2;
            rewind(fp);
            while(fread(&mov,sizeof(mov),1,fp)==1)
            {
                if(strcmp(mov.movie_id,mov_id)==0)
                {
                    print_title(mov.movie_id,5,row,YELLOW);
                    print_title(mov.movie_name,20,row,YELLOW);

                    sprintf(temp_str,"%02d/%02d/%04d",mov.show_date.tm_mday,mov.show_date.tm_mon,mov.show_date.tm_year);
                    print_title(temp_str,40,row,YELLOW);
                    row++;
                }
            }
            valid=0;
            do
            {
                print_title("Enter Show date: ", 25, 23, BROWN);
                scanf("%d/%d/%d", &date.tm_mday, &date.tm_mon, &date.tm_year);
                if(date.tm_mday == 0)
                {
                    fclose(fp);
                    return NULL;
                }
                if(compare_date(date, current) < 0)
                {

                    print_char(' ', 79, 25, BLACK);
                    print_title_in_middle("Show Date Cannot Be Less Than Today's Date", 25, RED);
                    getch();
                    print_char(' ', 79, 23, BLACK);
                }
                else
                {
                    rewind(fp);

                    while(fread(&mov, sizeof(mov), 1, fp) == 1)
                    {
                        //printf("\n%d/%d/%d",mov.show_date.tm_mday,mov.show_date.tm_mon,mov.show_date.tm_year);
                        //printf("\t%d/%d/%d",date.tm_mday,date.tm_mon,date.tm_year);
                        if((strcmp(mov.movie_id, mov_id) == 0) && (compare_date(mov.show_date, date) == 0))
                        {
                            valid = 1;
                            break;
                        }
                    }
                    if(valid == 0)
                    {
                        print_char(' ', 79, 25, BLACK);
                        print_title_in_middle("Wrong Show Date! Try Again!", 25, RED);
                        getch();
                        print_char(' ', 79, 23, BLACK);
                    }
                }
            }while(valid == 0);
        }
    }while(valid == 0);
    fclose(fp);
    return &mov;
}
int * get_seat_numbers(movie * m)
{
    print_basic_screen();

    FILE * fp = fopen("E:\\Movie Ticket Booking\\SeatNumbers.bin", "wb+");
    if(fp == NULL)
    {
        print_char(' ', 79, 25, BLACK);
        print_title("Error in opening file SeatNumbers.bin booking(user * u)", 1, 25, RED);
        perror("Error");
        getch();
        return NULL;
    }

    int seat_number, valid;
    char choice;
    int column, row;
    char temp_str[100];

    sprintf(temp_str, "1-30:First Block:%dRs/-, 31-70:Second Block:%dRs/-, 71-100:Third Block:%dRs/-", m->first_block_price, m->second_block_price, m->third_block_price);
    print_title(temp_str, 1, 7, YELLOW);

    textbackground(CYAN);
    print_char(' ', 80, 9, CYAN);
    print_title_in_middle("SCREEN", 9, LIGHTRED);
    textbackground(BLACK);

    int temp_color;

    do
    {
        column = 3, row = 11;
        for(int i = 1, pos = 0; i <= 10; i++)
        {
            gotoxy(column, row);
            for(int j = 1; j <= 10; j++, pos++)
            {
                if(m->seats[pos].seat_is_booked == 0)
                {
                    sprintf(temp_str, "%d", m->seats[pos].seat_number);
                    if(m->seats[pos].seat_number >= 1 && m->seats[pos].seat_number <= 30)
                        temp_color = LIGHTMAGENTA;
                    else if(m->seats[pos].seat_number >= 31 && m->seats[pos].seat_number <= 70)
                        temp_color = DARKGRAY;
                    else
                        temp_color = LIGHTCYAN;
                    print_title(temp_str, column, row, temp_color);
                    column += 8;
                }
                else
                {
                    print_title("X", column, row, RED);
                    column += 8;
                }
            }
            row++;
            column = 3;
        }
        do
        {
            print_char(' ',79,23,BLACK);
            print_title("Enter Seat Number:",25,23,YELLOW);
            get_integer(&seat_number);
            if(seat_number==0)
            {
                print_char(' ', 79, 25, BLACK);
                print_title("Cancelling Booking!", 1, 25, RED);
                fclose(fp);
                getch();
                if(remove("E:\\Movie Ticket Booking\\SeatNumbers.bin"))
                {
                    print_char(' ', 79, 25, BLACK);
                    print_title("Error In Removing SeatNumbers.bin!", 1, 25, RED);
                    perror("Error");
                    getch();

                }
                return NULL;
            }
            if(seat_number==-1)
            {
                print_char(' ', 79, 25, BLACK);
                print_title_in_middle("Invlaid Seat Number", 25, RED);
                getch();
                print_char(' ',79,23,BLACK);
            }
            else
            {
                for(int i=0;i<=99;i++)
                {
                    if(seat_number==m->seats[i].seat_number && m->seats[i].seat_is_booked==0)
                    {
                        valid=1;
                        break;
                    }
                }
                if(valid==0)
                {
                    print_char(' ', 79, 25, BLACK);
                    print_title_in_middle("Invalid Seat Number", 25, RED);
                    getch();
                    print_char(' ',79,23,BLACK);
                }
            }

        }while(valid==0);
        m->seats[seat_number-1].seat_is_booked=1;
        fseek(fp,0,SEEK_END);
        fwrite(&seat_number,sizeof(int),1,fp);
        print_char(' ',79,24,BLACK);
        valid=0;
        do
        {
            print_title("Do You Want To Book More Seats ?(Y/y/N/n)",20,24,YELLOW);
            fflush(stdin);
            scanf("%c",&choice);
            if(choice=='Y'||choice=='y'||choice=='N'||choice=='n')
                valid=1;
            else
            {
                print_char(' ', 79, 25, BLACK);
                print_title_in_middle("Invalid Choice!", 25, RED);
                getch();
                print_char(' ',79,24,BLACK);
            }
        }while(valid==0);
        for(int i=0,row=11;i<=9;i++,row++)
            print_char('\t',10,row,BLACK);
    }while(choice=='Y'||choice=='y');
    fseek(fp,0,SEEK_END);
    int size=ftell(fp)/sizeof(int)+1;
    int *p=(int *)malloc(size*sizeof(int));
    if(p==NULL)
    {
        print_char(' ', 79, 25, BLACK);
        print_title_in_middle("Cannot Create Dynamic Array!!", 25, RED);
        getch();
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    fread(p,(size-1)*sizeof(int),1,fp);
    p[size-1]=-1;
    fclose(fp);
    if(remove("E:\\Movie Ticket Booking\\SeatNumbers.bin"))
      {
         print_char(' ', 79, 25, BLACK);
         print_title("Error In Removing SeatNumbers.bin!", 1, 25, RED);
         perror("Error");
         getch();

      }
    return p;
}
void change_seat_booking_status(int seat_number,char *mov_id,struct tm date)
{
    FILE * fp = fopen("E:\\Movie Ticket Booking\\Movies.bin", "rb+");
    if(fp == NULL)
    {
        print_char(' ', 79, 25, BLACK);
        print_title("Error in opening file Movies.bin booking(user * u)", 1, 25, RED);
        perror("Error");
        getch();
        return;
    }
    movie mov;
    while(fread(&mov, sizeof(mov), 1, fp) == 1)
    {
      if((strcmp(mov.movie_id, mov_id) == 0) && (compare_date(mov.show_date, date) == 0))
        {
            fseek(fp,-(long long signed int )sizeof(mov),SEEK_CUR);
            mov.seats[seat_number-1].seat_is_booked=!mov.seats[seat_number-1].seat_is_booked;
            fwrite(&mov,sizeof(mov),1,fp);
            break;
        }
    }
    fclose(fp);
}
void booking(user * u)
{
    movie *m=get_movie_id_and_show_date();
    if(m==NULL)
    {
        print_char(' ', 79, 25, BLACK);
        print_title("Cancelling Booking!", 1, 25, RED);
        getch();
        return;
    }
    int *seat_numbers=get_seat_numbers(m);
    if(seat_numbers==NULL)
    {
        return;
    }
    int fb_count=0,sb_count=0,tb_count=0;
    for(int i=0;seat_numbers[i]!=-1;i++)
    {
        if(seat_numbers[i]>=1 && seat_numbers[i]<=30)
            fb_count++;
        else if(seat_numbers[i]>=31 && seat_numbers[i]<=70)
            sb_count++;
        else if(seat_numbers[i]>=71 && seat_numbers[i]<=100)
            tb_count++;
    }
     print_basic_screen();
    int fb_amount=fb_count*m->first_block_price;
    int sb_amount=sb_count*m->second_block_price;
    int tb_amount=tb_count*m->third_block_price;
    int row=8,column=25;
    print_title_in_middle("Total Amount To Be Paid",8,YELLOW);
    char temp_str[100];

    sprintf(temp_str,"First Block:%d * %d : %d",fb_count,m->first_block_price,fb_amount);
    print_title(temp_str,column,row+=2,YELLOW);

    sprintf(temp_str,"Second Block:%d * %d : %d",sb_count,m->second_block_price,sb_amount);
    print_title(temp_str,column,row+=2,YELLOW);

    sprintf(temp_str,"Third Block:%d * %d : %d",tb_count,m->third_block_price,tb_amount);
    print_title(temp_str,column,row+=2,YELLOW);

    sprintf(temp_str,"Total Amount:%d + %d + %d : %d",fb_amount,sb_amount,tb_amount,fb_amount+sb_amount+tb_amount);
    print_title(temp_str,column,row+=2,YELLOW);
    int valid=0;
    char choice;
    do
    {
        print_title("Are You Sure To Book The Tickets(Y/y/N/n)?",15,row+2,YELLOW);
        fflush(stdin);
        scanf("%c",&choice);
        if(choice=='Y'||choice=='y'||choice=='N'||choice=='n')
                valid=1;
            else
            {
                print_char(' ', 79, 25, BLACK);
                print_title_in_middle("Invalid Choice!", 25, RED);
                getch();
                print_char(' ',79,row+2,BLACK);
            }
    }while(valid==0);
    if(choice=='N'||choice=='n')
    {
        print_char(' ', 79, 25, BLACK);
        print_title("Cancelling Booking!", 1, 25, RED);
        getch();
        free(seat_numbers);
        return;
    }
    FILE * fp = fopen("E:\\Movie Ticket Booking\\Bookings.bin", "ab+");
    if(fp == NULL)
    {
        print_char(' ', 79, 25, BLACK);
        print_title("Error in opening file Bookings.bin booking(user * u)", 1, 25, RED);
        perror("Error");
        getch();
        return NULL;
    }
    fseek(fp,0,SEEK_END);
    ticket tk;
    char *p;
    if(ftell(fp)==0)
    {
        strcpy(tk.ticket_id,"TICKET-1");
    }
    else
    {
       fseek(fp,-(long long signed int)sizeof(tk),SEEK_END);
       fread(&tk,sizeof(tk),1,fp);
       p=strchr(tk.ticket_id,'-');
       int last_id=atoi(p+1);
       ++last_id;
       sprintf(tk.ticket_id,"TICKET-%d",last_id);
    }
    strcpy(tk.theater_id,m->theater_id);
    strcpy(tk.movie_id,m->movie_id);
    tk.show_date=m->show_date;
    strcpy(tk.user_id,u->userid);
    fseek(fp,0,SEEK_END);
    int rec_count=0;
    for(int i=0;seat_numbers[i]!=-1;i++)
    {
        tk.seat_number=seat_numbers[i];
        change_seat_booking_status(tk.seat_number,tk.movie_id,tk.show_date);
        fwrite(&tk,sizeof(tk),1,fp);
        p=strchr(tk.ticket_id,'-');
        int last_id=atoi(p+1);
        ++last_id;
        sprintf(tk.ticket_id,"TICKET-%d",last_id);
        ++rec_count;
    }
    print_basic_screen();
    fseek(fp,-(rec_count*sizeof(tk)),SEEK_END);
    row=8;
    print_title("Ticket ID",1,row,YELLOW);
    print_title("Theater ID",12,row,YELLOW);
    print_title("Movie ID",24,row,YELLOW);
    print_title("Seat No",34,row,YELLOW);
    print_title("Show Date",45,row,YELLOW);
    row+=2;
    while(fread(&tk,sizeof(tk),1,fp)==1)
    {
        print_title(tk.ticket_id,1,row,YELLOW);
        print_title(tk.theater_id,12,row,YELLOW);
        print_title(tk.movie_id,24,row,YELLOW);

        sprintf(temp_str,"%d",tk.seat_number);
        print_title(temp_str,36,row,YELLOW);

        sprintf(temp_str,"%02d/%02d/%04d",tk.show_date.tm_mday,tk.show_date.tm_mon,tk.show_date.tm_year);
        print_title(temp_str,45,row,YELLOW);
        row++;
    }
    print_title_in_middle("Tickets Booked Successfully!",25,LIGHTGREEN);
    fclose(fp);
    free(seat_numbers);
    getch();
    return;

}
void show_booking_of_user(user *usr)
{
    print_basic_screen();
    ticket tk;
    char temp_str[100];
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Bookings.bin","rb");
    if(fp==NULL)
    {
        print_char(' ',79,25,BLACK);
        print_title("Error in opening the file Bookings.bin\n",1,25,RED);
        perror("Reason:");
        getch();
        return;
    }
    int row=8;
    print_title("Ticket ID",1,row,BLUE);
    print_title("Theater ID",18,row,BLUE);
    print_title("Movie ID",37,row,BLUE);
    print_title("Seat No",52,row,BLUE);
    print_title("Show Date",66,row,BLUE);
    row+=2;
    while(fread(&tk,sizeof(tk),1,fp)==1)
    {
        if(strcmp(tk.user_id,usr->userid)==0)
        {
        print_title(tk.ticket_id,1,row,YELLOW);
        print_title(tk.theater_id,18,row,YELLOW);
        print_title(tk.movie_id,37,row,YELLOW);

        sprintf(temp_str,"%d",tk.seat_number);
        print_title(temp_str,52,row,YELLOW);

        sprintf(temp_str,"%02d/%02d/%04d",tk.show_date.tm_mday,tk.show_date.tm_mon,tk.show_date.tm_year);
        print_title(temp_str,66,row,YELLOW);
        row++;
        }
    }
    fclose(fp);
    getch();

}
void change_security_question(user *u)
{
    print_basic_screen();
    FILE *fp=fopen("E:\\Movie Ticket Booking\\Users.bin","rb+");
    if(fp==NULL)
        {
            print_char(' ',79,25,BLACK);
            print_title("Error in opening the file Users.bin\n",1,25,RED);
            perror("Reason:");
            getch();
            return;
        }
    char choice;
    char *p;
    print_title_in_middle("Are you sure to change the security question(Y/y/N/n):",10,YELLOW);
    fflush(stdin);
    scanf("%c",&choice);
    if(choice=='n'|| choice=='N')
    {
        print_char(' ',79,25,BLACK);
        print_title_in_middle("Cancelling Change Password",25,RED);
        getch();
    }
    else if(choice=='Y'||choice=='y')
    {
       user us;
       p=get_question_id();
       if(p==NULL)
       {
           fclose(fp);
           print_char(' ',79,25,BLACK);
           print_title_in_middle("Cancelling change security question",25,RED);
           getch();
           return;
       }
       print_title("Enter Hint Answer:",25,24,BROWN);
        get_string(us.hint_answer,100);
        {
            if(us.hint_answer==0)
            {
                fclose(fp);
                print_char(' ',79,25,BLACK);
                print_title_in_middle("Cancelling change security question",25,RED);
                getch();
                return;
            }
        }

       strcpy(u->question_id,p);
       strcpy(u->hint_answer,us.hint_answer);
       rewind(fp);
       while(fread(&us,sizeof(us),1,fp)==1)
        {
            if((strcmp(us.question_id,u->userid)==0)&&(strcmp(us.hint_answer,u->hint_answer)==0))
            {
                fseek(fp,-(long long signed int)sizeof(user),SEEK_CUR);
                fwrite(u,sizeof(user),1,fp);
                break;
            }
        }
        print_char(' ',79,25,BLACK);
        print_title_in_middle("security question changed Successfully!",25,LIGHTGREEN);
        getch();
    }
        else
        {
        print_char(' ',79,25,BLACK);
        print_title_in_middle("Invalid Choice",25,RED);
        getch();
        }
    fclose(fp);
}
void delete_booking_of_user(char *p)
{

}


