//students information management system
#include<iostream>
#include<conio.h>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<windows.h>
using namespace std;

// this is global variable
COORD coord= {0,0};                                  //center of axis is set to the top left cornor of the screen
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
class student
{
public:
    void help(); //function to show help to the user.
    void new_student();//function to add new record (student) to the file.
    void display_student();//function to display the information of a student.
    void display_all();//function to display information of all students.
    void modify_student();//function to modify the information of student.
    void delete_student();//functio to delete record (student) from the file.
    void getdata();//function to enter student information.
    void putdata(int y);//function to put student information.
    int getadm_no()//function to get admission no. of the student.
    {
        return adm_no;
    }
private:
    int adm_no;//admission no. of the student
    string name;//name of the student
    int dob, mob, yob, doj, moj, yoj;//date of birth and date of joining
    int Class;//class of student
    char section;//section of calss
    int roll_no;//roll no. of the student
} stu,stu2; //objects of class student

int i = 0;
void student::getdata()
{
    system("cls");
    cout<<"********************* ";
    cout<<"ADD NEW STUDENT ";
    cout<<"*********************"<<endl;
    cout<<"\nEnter the details of the student :";
    cout<<"\n\nAdmission no. : ";
    cin>>adm_no;
    cout<<endl<<"Name :";
    cin.ignore();
    getline(cin,name);
    int len=name.length();
    for(i=0; i<len; i++)
    {
        if(islower(name[i]))
            name[i]=toupper(name[i]);
    }
    cout<<endl<<"---Date of joining---"<<endl;
    cout<<"Date : ";
    cin>>doj;
    cout<<"Month: ";
    cin>>moj;
    cout<<"Year : ";
    cin>>yoj;
    cout<<endl<<"---Date of birth---";
    cout<<endl<<"Date : ";
    cin>>dob;
    cout<<"Month : ";
    cin>>mob;
    cout<<"Year : ";
    cin>>yob;
    cout<<endl<<"class : ";
    cin>>Class;
    cout<<"Section : ";
    cin>>section;
    if(islower(section))
        section=toupper(section);
    cout<<endl<<"Roll No. : ";
    cin>>roll_no;
}



void student::putdata(int y)
{
    cout<<"\n|         |                          |            |           |      |        |";
    gotoxy(4,y);
    cout<<adm_no;
    gotoxy(12,y);
    cout<<name;
    gotoxy(40,y);
    cout<<doj<<"-"<<moj<<"-"<<yoj;
    gotoxy(53,y);
    cout<<dob<<"-"<<mob<<"-"<<yob;
    gotoxy(64,y);
    cout<<Class;
    cout<<" "<<section;
    gotoxy(71,y);
    cout<<roll_no;
    cout<<"\n|_________|__________________________|____________|___________|______|________|";
}


void student::new_student()
{
    char ch_ns='y';
    while(ch_ns=='y'||ch_ns=='Y')
    {
        system("cls");
        fstream fio;
        fio.open("stud.dat", ios::in);
        if(!fio)//to add first record
        {
            cout<<"********************* ";
            cout<<"ADD NEW STUDENT ";
            cout<<"*********************"<<endl;
            fio.open("stud.dat", ios::out|ios::binary);
            stu.getdata();
            fio.write((char*)&stu, sizeof(stu));
            cout<<"\nRecord added.\n";
        }
        else //to add record when some records already exist
        {
            cout<<"********************* ";
            cout<<"ADD NEW STUDENT ";
            cout<<"*********************"<<endl;
            ofstream fout("tempp.dat", ios::out|ios::binary);
            char last='y';
            stu.getdata();
            fio.seekg(0,ios::beg);
            while(!fio.eof()) //to traverse each record and find specific position of record
            {
                fio.read((char*)&stu2, sizeof(stu2));
                if(fio.eof())
                    break;
                if(stu.getadm_no() == stu2.getadm_no())
                {
                    cout<<"\nAdmission no. already exists. Record cannot be added!!!";
                    getch();
                    last='u';
                    break;
                }
                else if(stu.getadm_no() < stu2.getadm_no())
                {
                    fout.write((char*)&stu, sizeof(stu));
                    last='n';
                    break;
                }
                else
                    fout.write((char*)&stu2, sizeof(stu2));
            }

            if (last=='y')
                fout.write((char*)&stu, sizeof(stu));
            else if (last=='u')
                break;

            else if (!fio.eof())
            {
                fout.write((char*)&stu2, sizeof(stu2));

                while(!fio.eof())
                {
                    fio.read((char*)&stu2, sizeof(stu2));
                    if(fio.eof())
                        break;
                    fout.write((char*)&stu2, sizeof(stu2));
                }
            }

            fio.close();
            fout.close();
            remove("stud.dat");
            rename("tempp.dat", "stud.dat");
            if(last!='u')
                cout<<"\nRecord added.";
        }
        cout<<"\nWant to enter more records?(y/n) :";
        cin>>ch_ns;
        if(!(ch_ns=='y'||ch_ns=='Y'||ch_ns=='n'||ch_ns=='N'))
        {
            cout<<"\nIllegal command. Aborting!!!";
            getch();
            exit(0);
        }
    }
}




void student::display_student()
{
    char ch_ds='y';
    system("cls");
    int adno;
    char found='n';
    ifstream fin("stud.dat",ios::in|ios::binary);
    if(!fin)//if file stud.dat does not exist
    {
        fin.close();
        for(int i=0; i<28; i++)
            cout<<"*";
        gotoxy(30,1);
        cout<<"DISPLAY INFORMATION ";
        for(i=0; i<30; i++)
            cout<<"*";
        cout<<"\nNo information.";
    }
    else
    {
        while(ch_ds=='y'||ch_ds=='Y')
        {
            ifstream fin("stud.dat",ios::in|ios::binary);
            system("cls");
            found='n';
            for(int i=0; i<28; i++)
                cout<<"*";
            gotoxy(30,1);
            cout<<"DISPLAY INFORMATION ";
            for(i=0; i<30; i++)
                cout<<"*";
            fin.seekg(0,ios::end);
            if(fin.tellg()>0)
            {
                cout<<"\nEnter admission no. of the student to be displayed.\nAdmission no.:";
                cin>>adno;
            }
            else
            {
                cout<<"\nNo information.";
                fin.close();
                return;
            }
            fin.seekg(0,ios::beg);
            while(!fin.eof())
            {
                fin.read((char*)&stu,sizeof(stu));
                if(fin.eof())
                    break;
                if(stu.getadm_no()==adno)
                {
                    system("cls");
                    for(int i=0; i<28; i++)
                        cout<<"*";
                    gotoxy(30,1);
                    cout<<"DISPLAY INFORMATION ";
                    for(i=0; i<30; i++)
                        cout<<"*";
                    cout<<"\n===============================================================================";
                    cout<<"\n|ADM. NO. |           NAME           |D.O.JOINING |D.O.BIRTH  |CLASS |ROLL NO |";
                    cout<<"\n|_________|__________________________|____________|___________|______|________|";
                    stu.putdata(5);
                    getch();
                    found='y';
                    break;
                }
            }
            if(found=='n')
            {
                cout<<"\nAdmission no. not found in file.";
                getch();
            }
            cout<<"\nWant to display more records?(y/n) :";
            cin>>ch_ds;
            if(!(ch_ds=='y'||ch_ds=='Y'||ch_ds=='n'||ch_ds=='N'))
            {
                cout<<"\nIllegal command. Aborting!!!";
                getch();
                exit(0);
            }
        }
    }
    fin.close();
}

void student::display_all()
{
    system("cls");
    int y=5,run=0;
    ifstream fin("stud.dat",ios::in|ios::binary);
    if(!fin) //if file stud.dat does not exist
    {
        for(int i=0; i<28; i++)
            cout<<"*";
        gotoxy(30,1);
        cout<<"DISPLAY INFORMATION ";
        for(i=0; i<30; i++)
            cout<<"*";
        cout<<"\nNo information.";
    }
    else
    {
        for(int i=0; i<28; i++)
            cout<<"*";
        gotoxy(30,1);
        cout<<"DISPLAY INFORMATION ";
        for(i=0; i<30; i++)
            cout<<"*";
        fin.seekg(0,ios::end);
        if(fin.tellg()>0)
        {
//File not empty.Normal execution.
        }
        else
        {
            cout<<"\nNo information.";
            fin.close();
            return;
        }
        fin.seekg(0,ios::beg);

        while(!fin.eof())
        {
            fin.read((char*)&stu,sizeof(stu));
            if(fin.eof())
                break;
            if(run==0)
            {
                cout<<"\n===============================================================================";
                cout<<"\n|ADM. NO. |           NAME           |D.O.JOINING |D.O.BIRTH  |CLASS |ROLL NO |";
                cout<<"\n|_________|__________________________|____________|___________|______|________|";
                run++;
            }
            stu.putdata(y);
            y=y+2;
        }
        getch();
    }
    fin.close();
}



void student::modify_student()
{
    char ch_ms='y';

    system("cls");
    int y=8;
    int adno;
    char found='f';
    fstream fio("stud.dat",ios::in);
    if(!fio)//if stud.dat does not exist
    {
        fio.close();
        for(int i=0; i<30; i++)
            cout<<"*";
        gotoxy(32,1);
        cout<<"MODIFY STUDENT ";
        for(i=0; i<33; i++)
            cout<<"*";
        cout<<"\nNo information.";
    }
    else
    {
        while(ch_ms=='y'||ch_ms=='Y')
        {
            system("cls");
            for(int i=0; i<30; i++)
                cout<<"*";
            gotoxy(32,1);
            cout<<"MODIFY STUDENT ";
            for(i=0; i<33; i++)
                cout<<"*";
            fstream fio("stud.dat",ios::out|ios::in|ios::binary);
            fio.seekg(0,ios::end);
            if(fio.tellg()>0)
            {
                cout<<"\nEnter the admission no. of the student whose record is to be modified.\nAdmission no.:";
                cin>>adno;
            }
            else
            {
                cout<<"\nNo information.";
                fio.close();
                return;
            }
            fio.seekg(0,ios::beg);

            while(!fio.eof())
            {
                int pos=fio.tellg();//to find position where the record is to be written
                fio.read((char*)&stu,sizeof(stu));
                if(fio.eof())
                    break;
                if(stu.getadm_no()==adno)
                {
                    cout<<"\n===============================================================================";
                    cout<<"\n|ADM. NO. |           NAME           |D.O.JOINING |D.O.BIRTH  |CLASS |ROLL NO |";
                    cout<<"\n|_________|__________________________|____________|___________|______|________|";
                    stu.putdata(y);
                    found='t';
                    string nm;
                    char sec;
                    int dj,mj,yj,db,mb,yb,clas,rno;

                    cout<<"\nEnter the new details of the student :";
                    cout<<"\n\nName (Enter '.' to retain old one):      \n\nDate of joining (Enter '-1' to retain old one): Date:    "
                        "Month :    Year :    \n\nDate of birth (Enter '-1' to retain old one):   Date:    "
                        "Month :    Year :    \n\nClass(Enter '-1' to retain old one):   Section(Enter '.' to retain old one):  \n\nRoll no. (Enter '-1' to retain old one): ";

                    gotoxy(36, 12);
                    getline(cin,nm);
                    int len=nm.length();
                    for(i=0; i<len; i++)
                    {
                        if(islower(nm[i]))
                            nm[i]=toupper(nm[i]);
                    }
                    if(nm != ".")
                        name = nm;
                    gotoxy(54,14);
                    cin>>dj;
                    if(dj!=-1)
                        doj=dj;
                    gotoxy(65,14);
                    cin>>mj;
                    if(mj!=-1)
                        moj=mj;
                    gotoxy(75,14);
                    cin>>yj;
                    if(yj!=-1)
                        yoj=yj;
                    gotoxy(54,16);
                    cin>>db;
                    if(db!=-1)
                        dob=db;
                    gotoxy(65,16);
                    cin>>mb;
                    if(mb!=-1)
                        mob=mb;
                    gotoxy(75,16);
                    cin>>yb;
                    if(yb!=-1)
                        yob=yb;
                    gotoxy(37,18);
                    cin>>clas;
                    if(clas!=-1)
                        Class=clas;
                    gotoxy(77,18);
                    cin>>sec;
                    if(islower(sec))
                        sec=toupper(sec);
                    if(sec!='.')
                        section=sec;
                    gotoxy(41,20);
                    cin>>rno;
                    if(rno!=-1)
                        roll_no=rno;
                    fio.seekg(pos);
                    fio.write((char*)&stu,sizeof(stu));
                    break;
                }
            }
            if(found=='f')
                cout<<"\nRecord not found!!";
            else
                cout<<"\nRecord modified.";
            cout<<"\nWant to modify more records?(y/n) :";
            cin>>ch_ms;
            if(!(ch_ms=='y'||ch_ms=='Y'||ch_ms=='n'||ch_ms=='N'))
            {
                cout<<"\nIllegal command. Aborting!!!";
                getch();
                exit(0);
            }
        }
    }
    fio.close();
}




void student::delete_student()
{
    char ch_ds='y';
    int y=8;

    system("cls");
    ifstream fin("stud.dat",ios::in);
    if(!fin)//if file stud.dat does not exist
    {
        fin.close();
        for(int i=0; i<30; i++)
            cout<<"*";
        gotoxy(32,1);
        cout<<"DELETE STUDENT ";
        for(i=0; i<33; i++)
            cout<<"*";
        cout<<"\nNo information.";
    }
    else
    {
        while(ch_ds=='y'||ch_ds=='Y')
        {
            system("cls");
            for(int i=0; i<30; i++)
                cout<<"*";
            gotoxy(32,1);
            cout<<"DELETE STUDENT ";
            for(i=0; i<33; i++)
                cout<<"*";
            ifstream fin("stud.dat",ios::in);
            ofstream fout("tempp.dat",ios::out);
            int adno;
            char found='f';
            char confirm='n';
            fin.seekg(0,ios::end);
            if(fin.tellg()>0)
            {
                cout<<"\nEnter the admission no. of the student whose record is to be deleted.\nAdmission no.:";
                cin>>adno;
            }
            else
            {
                cout<<"\nNo information.";
                fin.close();
                fout.close();
                remove("stud.dat");
                rename("tempp.dat","stud.dat");
                return;
            }
            fin.seekg(0,ios::beg);
            while(!fin.eof())
            {
                fin.read((char*)&stu,sizeof(stu));
                if(fin.eof())
                    break;
                if(stu.getadm_no()==adno)
                {
                    cout<<"\n===============================================================================";
                    cout<<"\n|ADM. NO. |           NAME           |D.O.JOINING |D.O.BIRTH  |CLASS |ROLL NO |";
                    cout<<"\n|_________|__________________________|____________|___________|______|________|";
                    stu.putdata(y);
                    found='t';
                    cout<<"\nAre you sure, you want to delete this record ?(y/n)...";
                    cin>>confirm;
                    if(confirm=='n')
                    {
                        fout.write((char*)&stu,sizeof(stu));
                        cout<<"\nRecord not deleted.";
                    }
                    else
                        cout<<"\nRecord deleted.";
                }
                else
                    fout.write((char*)&stu,sizeof(stu));
            }

            if(found=='f')
                cout<<"\nRecord not found.";
            fin.close();
            fout.close();
            remove("stud.dat");
            rename("tempp.dat","stud.dat");
            cout<<"\nWant to delete more records?(y/n) :";
            cin>>ch_ds;
            if(!(ch_ds=='y'||ch_ds=='Y'||ch_ds=='n'||ch_ds=='N'))
            {
                cout<<"\nIllegal command. Aborting!!!";
                getch();
                exit(0);
            }
        }
    }
}

void student::help()
{
    system("cls");
    for(int i=0; i<37; i++)
        cout<<"*";
    gotoxy(39,1);
    cout<<"HELP ";
    for(i=0; i<36; i++)
        cout<<"*";
    cout<<"\n1.ADD NEW STUDENT "
        "-\n  To store information of the new student in the record.\n"
        "\n2.MODIFY STUDENT "
        "-\n  To modify (change) the information of the stored student.\n"
        "\n3.DISPLAY STUDENT "
        "-\n  To display the information of a particular student.\n"
        "\n4.DISPLAY ALL STUDENTS "
        "-\n  To display the information of all students.\n"
        "\n5.DELETE STUDENT "
        "-\n  To delete the complete information of the student permanently.\n"
        "\n6.EXIT "
        "-\n  To exit the program.\n";
    cout<<"\nPress any key to go back....";
}



int main()
{
    int ch;
    char  pass[20],p1,p2,p3,p4,p5,p6,p7,p8;
    int p=0;
    system("cls");
    cout<<"\n%%    %% %%%%%%% %%      %%%%%%% %%%%%%% %%%  %%% %%%%%%%  %%%%%% %%%%%%%     ";
    cout<<"\n%%    %% %%      %%      %%      %%   %% %% %% %% %%         %%   %%   %% ";
    cout<<"\n%%    %% %%%%%   %%      %%      %%   %% %%    %% %%%%%      %%   %%   %%  ";
    cout<<"\n%% %% %% %%      %%      %%      %%   %% %%    %% %%         %%   %%   %%   ";
    cout<<"\n%%%  %%% %%%%%%% %%%%%%% %%%%%%% %%%%%%% %%    %% %%%%%%%    %%   %%%%%%%  \n\n";
    cout<<"\n%%%%%% %%%%%% %%  %% %%%%%  %%%%% %%   %% %%%%%%   %%%%%% %%   %% %%%%% %%%%%%";
    cout<<"\n%%       %%   %%  %% %%  %% %%    %%%  %%   %%       %%   %%%  %% %%    %%  %%";
    cout<<"\n%%%%%%   %%   %%  %% %%  %% %%%%  %% % %%   %%       %%   %% % %% %%%%  %%  %%";
    cout<<"\n    %%   %%   %%  %% %%  %% %%    %%  %%%   %%       %%   %%  %%% %%    %%  %%";
    cout<<"\n%%%%%%   %%   %%%%%% %%%%%  %%%%% %%   %%   %%     %%%%%% %%   %% %%    %%%%%%\n\n";
    cout<<"\n %%%  %%% %%%%%%  %%   %% %%%%%% %%%%%%% %%%%% %%%  %%% %%%%% %%   %% %%%%%%   ";
    cout<<"\n %% %% %% %%  %%  %%%  %% %%  %% %%      %%    %% %% %% %%    %%%  %%   %%     ";
    cout<<"\n %%    %% %%%%%%  %% % %% %%%%%% %%      %%%%  %%    %% %%%%  %% % %%   %%     ";
    cout<<"\n %%    %% %%  %%  %%  %%% %%  %% %% %%%% %%    %%    %% %%    %%  %%%   %%     ";
    cout<<"\n %%    %% %%  %%  %%   %% %%  %% %%%% %% %%%%% %%    %% %%%%% %%   %%   %%     ";


    cout<<"\n\nDeveloped by :\n1.RAJENDRA KUMAR DANGWAL\n2.AMARJEET YADAV\n3.SUBRAT BHUYAN\t\t\t\t";
    cout<<"Enter the user number (1/2/3): ";
    getch();

    while(p<2)
    {
        system("cls");
        gotoxy(31,12);
        cout<<" Enter Password \n";
        gotoxy(33,14);
        printf("            ");
        gotoxy(35,14);
        p1=getch();
        cout<<"P";
        p2=getch();
        cout<<"A";
        p3=getch();
        cout<<"S";
        p4=getch();
        cout<<"S";
        p5=getch();
        cout<<"W";
        p6=getch();
        cout<<"O";
        p7=getch();
        cout<<"R";
        p8=getch();
        cout<<"D";
        getch();
        p++;
        if ((p1=='r')&&(p2=='a')&&(p3=='j')&&(p4=='e')&&(p5=='n')&&(p6=='d')&&(p7=='r')&&(p8=='a')||(p1=='a')&&(p2=='m')&&(p3=='a')&&(p4=='r')&&(p5=='j')&&(p6=='e')&&(p7=='e')&&(p8=='t')||(p1==' ')&&(p2=='s')&&(p3=='u')&&(p4=='b')&&(p5=='r')&&(p6=='a')&&(p7=='t')&&(p8==' '))
        {
            p=p+3;

            do
            {
                system("cls");
                for(int i=0; i<23; i++)
                    cout<<"*";
                printf("STUDENT INFORMATION MANAGEMENT");
                cout<<" ";
                for(i=0; i<26; i++)
                    cout<<"*";
                for(i=2; i<26; i++)
                {
                    gotoxy(1,i);
                    cout<<"*";
                    gotoxy(80,i);
                    cout<<"*";
                }
                gotoxy(29,3);
                printf("MAIN MENU");
                gotoxy(26,5);
                printf("1.ADD NEW STUDENT");
                gotoxy(26,7);
                printf("2.MODIFY STUDENT");
                gotoxy(26,9);
                printf("3.DISPLAY STUDENT");
                gotoxy(26,11);
                printf("4.DISPLAY ALL STUDENTS");
                gotoxy(26,13);
                printf("5.DELETE STUDENT");

                gotoxy(26,15);
                printf("6.EXIT");

                cout<<"\n\n\n";
                gotoxy(26,19);
                printf("Enter your choice(1-6) :");
                gotoxy(2,24);
                printf("Press 0 for help.");
                cout<<"\n*******************************************************************************";
                gotoxy(51,19);
                cin>>ch;

                switch(ch)
                {
                case 0:
                    stu.help();
                    break;
                case 1:
                    stu.new_student();
                    break;
                case 2:
                    stu.modify_student();
                    break;
                case 3:
                    stu.display_student();
                    break;
                case 4:
                    stu.display_all();
                    break;
                case 5:
                    stu.delete_student();
                    break;
                case 6:
                    exit(0);
                    break;
                default :
                    gotoxy(26,21);
                    cout<<"Wrong choice!!";
                }

                getchar();
            }
            while(ch!=6);
        }
        else
        {
            gotoxy(31,18);
            cout<<"Wrong Password!!";
            getch();
        }
    }
    return 0;
}
