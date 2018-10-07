#include <bits/stdc++.h>
#include<conio.h>
#include<ctime>


using namespace std;
void setdate(int* dd, int* mm, int* yy)
{
    time_t now=time(0);
    tm* ltm=localtime(&now);
    int year, date , month;
    year=1900+ltm->tm_year;
    date=ltm->tm_mday;
    month=1+ltm->tm_mon;
    *dd=date; *mm=month; *yy=year;

}
const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};

int countleapyears(int d, int m, int y)
{
    int years = y;


    if (m <= 2)
        years--;

    return years / 4 - years / 100 + years / 400;
}

int difference(int d2,int m2,int y2,int d1,int m1, int y1)
{
    long int diff,n1,n2;
    n1=365*y1+d1;
    for (int i=0; i<m1 - 1; i++)
        n1 += monthDays[i];
        n1+= countleapyears(d1,m1,y1);

        n2=365*y2+d2;
    for (int i=0; i<m2 - 1; i++)
        n2 += monthDays[i];
        n2+= countleapyears(d2,m2,y2);
diff = n2 - n1;

    return diff;
}

class issued
{   public:
    char roll[11];
    long int book_code;
    int dd;
    int mm;
    int yy;
   void  details();
   /* setdate(int dd, int mm, int yy)
{
    time_t now=time(0);
    tm* ltm=localtime(&now);
    int year, date , month;
    year=1900+ltm->tm_year-90;
    date=ltm->tm_mday;
    month=1+ltm->tm_mon;
    dd=date; mm=month; yy=year;

}*/


};

void callwhileissue(long int bk2, char rollcode[])
{
    issued iss;
    iss.book_code = bk2;
    strcpy(iss.roll,rollcode);
    setdate(&iss.dd,&iss.mm,&iss.yy);
    cout<<endl<<"issue date is : ";
    cout<<iss.dd<<" "<<iss.mm<<" "<<iss.yy<<endl;
    fstream file;
    file.open("issued.dat",ios::app|ios::binary);
    file.write((char*)&iss, sizeof(iss));
    file.close();
}

void  issued :: details()
{
     cout<<"\n book code : ";
    cout<<book_code;
    fflush(stdout);
    cout<<"\n student : ";
    puts(roll);
    //issued on and details

}
void changeissuestatus(long int bk2)
    {
		issued iss;
		fstream file;
		fstream temp;
		file.open("issued.dat",ios::app|ios::binary);
		temp.open("issued1.dat",ios::app|ios::binary);
		while(file.read((char*)&iss,sizeof(iss)))
		{
			if(iss.book_code == bk2)
			{}
		else
		{
			temp.write((char*)&iss, sizeof(iss));
		}
		}
		file.close();
		temp.close();
		remove("issued.dat");
		rename("issued1.dat", "issued.dat");
    }

void show_issued_books(char rollcode[])
{
    issued iss;
    fstream file;
    file.open("issued.dat", ios::in|ios::binary);
    if(!file)
    {
        cout<<"\n cannot open file ! ";
        getch();
       // return -1;
    }
    while(file.read((char*)&iss,sizeof(iss)))
    {
        if(strcmpi(iss.roll,rollcode) == 0)
           iss.details();
    }
    file.close();

}

int get_year(char rollno[])
{
  /*  string year = rollno;
   // char year[5];
   // strncpy(year, rollno, 4);
   // year[4] = '\0';

    int yy =0;
    stringstream geek(year);
    geek>>yy;
    return yy;*/
    int y = 0;
    for(int i=0; i<4; i++)
    {
        y = y*10 + (rollno[i] - '0');
    }

    return y;
}

char * get_branch(char rollno[])
{
    char arr[3];
    arr[0] = rollno[5];
    arr[1] = rollno[6];
    arr[2] = '\0';

    if(strcmpi(arr,"CO")==0)
        return "COMPUTER SCIENCE";
    else if(strcmpi(arr,"IT")==0)
        return "INFORMATION TECHNOLOGY";
    else if(strcmpi(arr,"BT")==0)
        return "BIO-TECHNOLOGY";
    else if(strcmpi(arr,"EC")==0)
        return "ELECTRONICS AND COMMUNICATION";
    else if(strcmpi(arr,"IC")==0)
        return "INSTRUMENTATION AND CONTROL";
    else if(strcmpi(arr,"ME")==0)
        return "MECHANICAL";

    return "BRANCH NOT DEFINED";
}

class student
{
public:

    char sname[20], sroll[11], sbranch[50], sadd[75], sphone[12];
    int no_of_books;
    int year_of_add;

    void display();
    void input();
    void showlist();

};

void student :: input()
{
    cout<<"\n enter roll no : ";
    fflush(stdin);
    gets(sroll);
    cout<<"\n enter name : ";
    fflush(stdin);
    gets(sname);
    cout<<"\n enter phone no : ";
    fflush(stdin);
    gets(sphone);
    no_of_books = 0;
    fflush(stdin);
    year_of_add = get_year(sroll);
   // sbranch = get_branch(sroll);
   fflush(stdin);
   strcpy(sbranch,get_branch(sroll));
}

void student :: display()
{
     cout<<"\n details are ";
    fflush(stdout);
     cout<<"\n name : ";
     puts(sname);
    fflush(stdout);
     cout<<" roll no : ";
     puts(sroll);
    fflush(stdout);
     cout<<" branch : ";
     puts(sbranch);
     fflush(stdout);
      cout<<" year of admission : ";
      cout<<year_of_add;
    fflush(stdout);
     cout<<"\n phone no. : ";
     puts(sphone);
    fflush(stdout);
    if(no_of_books == 0)
        cout<<"\n student has not issued any book !\n ";
    else
        cout<<no_of_books<<" books issued\n ";

}

void changestudentissuestatus(char roll[], int x)
{
   // puts(roll);
    student st;
    fstream file;
    file.open("student.dat",ios::in|ios::out|ios::binary);
    if(!file)
    {
        cout<<"\n cannot open file ";
        getch();
    }
    file.seekg(0);
    int recno = 0;
    while(file.read((char*)&st,sizeof(st)))
    {

        if(strcmpi(st.sroll,roll)==0)
        {
            st.no_of_books+=x;

            file.seekp(recno*sizeof(st)) ;
            file.write((char*)&st,sizeof(st)) ;
        }

        recno++;
    }
    file.close();

}



class book
{
public:

    char title[20], author[25], publisher[25];
    int edition;
    long int isbn_no;
    long int book_id;
    bool status;


    void get_data();
    void display();
    void showlist();
    void modify();


};
void changebookstatus(long int bk2)
    {
        book bk;
        fstream fb;
        fb.open("book.dat", ios::in|ios::out|ios::binary);
        if(!fb)
        {
            cout<<"\n cannot open file ";
            getch();
        }
        fb.seekg(0);
        int recno = 0;
        while(fb.read((char*)&bk,sizeof(bk)))
        {
            if(bk.book_id == bk2)
            {
                if(bk.status == false)
                    bk.status = true;
                else if(bk.status==true)
                    bk.status = false;
                fb.seekp(recno*sizeof(bk));
                fb.write((char*)&bk,sizeof(bk)) ;
            }
            recno++;
        }
        fb.close();
    }

void book :: get_data()
{
    cout<<"\n enter the details of the book : ";
    fflush(stdin);
    cout<<"\n title : ";
    gets(title);
    fflush(stdin);
    cout<<"\n author : ";
    gets(author);
    fflush(stdin);
    cout<<"\n publisher : ";
    gets(publisher);
    fflush(stdin);
    cout<<"\n edition : ";
    cin>>edition;
    fflush(stdin);
    cout<<"\n isbn no. : ";
    cin>>isbn_no;
    fflush(stdin);
    cout<<"\n book id no : ";
    cin>>book_id;
    fflush(stdin);
    status = 0;
}

void book:: display()
{
    cout<<"\n\n details are "<<endl;
    fflush(stdout);
    cout<<" book id "<<book_id<<endl;
    fflush(stdout);
    cout<<" isbn no "<<isbn_no<<endl;
    fflush(stdout);
    cout<<" title "<<title<<endl;
    fflush(stdout);
    cout<<" author "<<author<<endl;
    fflush(stdout);
    cout<<" publisher "<<publisher<<endl;
    fflush(stdout);
    cout<<" edition "<<edition<<endl;
    fflush(stdout);
    if(status == 0)
        cout<<"  this book is not issued to anyone ";
    else
        cout<<"  this book is already issued ";

}
int search_stud(char roll[])
{
    int found = 0;
    student stud;
    fstream fs;
    fs.open("student.dat", ios::in|ios::binary);
    if(!fs)
    {
        cout<<"\n cannot open file ! ";
        getch();
        return -1;
    }
    while(fs.read((char*)&stud, sizeof(stud)))
    {
        if(strcmpi(stud.sroll,roll)==0 && stud.no_of_books == 3)
        {
            found = 1;
            break;
        }
        else if(strcmpi(stud.sroll,roll)==0 && stud.no_of_books<3)
        {
            found = 2;
            break;
        }

    }
    fs.close();
    return found;
}

int search_book(long int bkcode)
{
    int found = 0;
    book bk;
    fstream fb;
    fb.open("book.dat", ios::in|ios::binary);
    if(!fb)
    {
        cout<<"\n cannot open file ! ";
        getch();
        return -1;
    }

    while(fb.read((char*)&bk,sizeof(bk)))
    {
        if(bkcode==bk.book_id && bk.status==0)
        {
            found = 2;
            break;
        }
        else if(bkcode == bk.book_id && bk.status==1)
        {
            found = 1;
            break;
        }
    }
    fb.close();
    return found;
}

int search_book(char name[])
{
    int found = 0;
    book bk;
    fstream fb;
    fb.open("book.dat", ios::in|ios::binary);
    if(!fb)
    {
        cout<<"\n cannot open file ";
        getch();
        return -1;
    }
    while(fb.read((char*)&bk, sizeof(bk)))
    {
        if(bk.status==false &&(strcmpi(bk.title,name)==0 || strcmpi(bk.author,name)==0))
        {
            found = 2;
            break;
        }
        else if(bk.status==true &&(strcmpi(bk.title,name)==0 || strcmpi(bk.author,name)==0))
        {
            found = 1;
            break;
        }

    }
    fb.close();
    return found;
}

int search_bcode(long int bookcode)
{
    int found = 0;
    book bk;
    fstream fb;
    fb.open("book.dat", ios::in|ios::binary);
    if(!fb)
    {
        cout<<"\n cannot open file ! ";
        getch();
        return -1;
    }
     while(fb.read((char*)&bk, sizeof(bk)))
     {
         if(bk.book_id == bookcode && bk.status == 1)
         {
             found = 2;
             break;
         }
         else if(bk.book_id == bookcode && bk.status==0)
         {
             found = 1;
             break;
         }
     }
     fb.close();
     return found;
}

void issue()
{
fflush(stdin);
    cout<<"\n enter roll no of the student : ";
    char rollcode[12];
    gets(rollcode);
 //  cin.getline(rollcode,11);
    fflush(stdin);
    int found = search_stud(rollcode);
    if(found==0)
    {
        cout<<"\n student is not yet registered ! ";
        return;
    }
    else if(found==1)
    {
        cout<<"\n you have already issued 3 books ! ";
        return;
    }
    else if(found==2)
    {
       cout<<"\n enter the code of the book you want to issue : ";
        long int code;
        cin>>code;
        fflush(stdin);
        int check=0;
        check = search_book(code);
        if(check == 0)
           cout<<"\n book does not exist ";
        else if(check == 1)
            cout<<"\n book is already issued ! ";
        else if(check == 2)
        {
            cout<<"\n you can issue "<<endl;
         //   long int bookc = get_bookid(book_name);
            changebookstatus(code);
            int x = 1;
            changestudentissuestatus(rollcode,x);

            callwhileissue(code, rollcode);


        }

        cout<<"\n  book issued ! ";

    }
	//issued ii;



}

void show_details(long int bkcode)
{
     book bk;
 fstream f;
 f.open("book.dat",ios::in|ios::binary);
 f.read((char*)&bk,sizeof(bk));
 while(!f.eof())
 {
  if(bk.book_id==bkcode)
  {
    bk.display();
    break;
  }
  f.read((char*)&bk,sizeof(bk));
 }
}
int getissuedate(long int bk2, int kyakaru)
{
    issued ii;
    fstream fb;
    fb.open("issued.dat", ios::in|ios::binary);
    if(!fb)
    {
        cout<<"\n cannot open file ! ";
        getch();
        return -1;
    }
     while(fb.read((char*)&ii, sizeof(ii)))
     {
         if(ii.book_code == bk2)
         {
             if(kyakaru==1)
             return ii.dd;
            else if(kyakaru==2)
                return ii.mm;
             else
                return ii.yy;

         }

     }
     fb.close();


}

long int getcode(char name[])
{
    fstream file;
    book bk;
    file.open("book.dat",ios::in|ios::binary);
    if(!file)
    {
        cout<<"\n cannot open file";
        getch();
        return -1;
    }
    while(file.read((char*)&bk, sizeof(bk)))
    {
        if(strcmpi(bk.title,name)==0 || strcmpi(bk.author,name)==0)
        {
            return bk.book_id;
        }
    }
    return 0;
}


int main()
{   system("cls");
    int ans;
    do{
            system("cls");
    cout<<"\n enter one option from the menu "<<endl;
    cout<<"\n 1. Add a book ";
    cout<<"\n 2. Remove a book ";
    cout<<"\n 3. Search book ";
    cout<<"\n 4. Search student ";
    cout<<"\n 5. Issue ";
    cout<<"\n 6. Return ";
    cout<<"\n 7. Registered students ";
 //   cout<<"\n 8. Modify book details ";
 //   cout<<"\n 9. Modify student details ";
    cout<<"\n 10. register new student ";
    cout<<"\n 11. list of books ";
    cout<<"\n 12. delete student ";
    cout<<"\n 13. list of defaulters ";
    cout<<"\n 15. show issued books ";
    cout<<"\n 14. exit ";
    cout<<"\n\n\t enter your choice : ";
    cin>>ans;
    switch(ans)
    {
    case 1 :
         system("cls");
       {
        fstream f;
        f.open("book.dat", ios::app|ios::binary) ;
        book b;
        b.get_data();
        f.write((char*)&b, sizeof(b)) ;
        f.close();
        cout<<"\n\t BOOK ADDED TO THE LIBRARY";
        cout<<"\n\n press any key ";
        getch();
       }
        break;

    case 2 :
        system("cls");
        {
        book b;
        long int bcode;
        cout<<"\n enter the book_id to be deleted : ";
        cin>>bcode;
        int found=search_bcode(bcode); //1.can be deleted...2.issued...0.does not exist
        if(found==0)
            cout<<"\n this book does not exist ! ";
        else if(found == 2)
            cout<<"\n book is issued ! ";
        else if(found == 1)
        {
            fstream f;
            f.open("book.dat", ios::in|ios::binary) ;
            fstream ftemp;
            ftemp.open("book1.dat", ios::out|ios::binary) ;
            f.seekg(0);
            while(f.read((char*)&b, sizeof(b)))
            {
                if(b.book_id == bcode)
                {
                    cout<<"\n details of the book are :\n";
                    b.display() ;
                }
                else
                    ftemp.write((char*)&b, sizeof(b)) ;
            }
            f.close();
            ftemp.close();
            int choice;
            cout<<"\n you really want to delete ?";
            cout<<"\n 0 -> no     1 -> yes \t";
            cin>>choice;
            if(choice==1)
            {
                remove("book.dat") ;
                rename("book1.dat", "book.dat") ;
                cout<<"\n book deleted ";
            }
        }
        cout<<"\n press any key ";
        getch();
        }
        break;
    case 3:
        system("cls");
        {   cout<<"\n enter the field by which you want to search : ";
            cout<<"\n 1-> book id no ";
            cout<<"\n 2-> title   ";
            cout<<"\n 3-> author ";
            int sel;
            cin>>sel;
            switch(sel)
            {
           case 1:
            system("cls");
{


            cout<<"\n enter the book id of the book  : ";
            long int code;
            cin>>code;
            int fnd= search_book(code);
            if(fnd == 0)
                cout<<"\n book does not exist  ";
            else if(fnd==1 || fnd==2)
            {
              /*  book bk;
                fstream file;
                file.open("book.dat",ios::in|ios::out);
                file.read((char*)&bk,sizeof(bk));
                while(!file.eof())
                {
                    if(bk.isbn_no == isbncode)
                    {
                        bk.display();
                        break;
                    }
                    file.read((char*)&bk, sizeof(bk));
                }
                file.close();
                cout<<"\n the book codes for the same isbn no are listed below : "<<endl;
            //    list_isbns(isbncode);*/

            show_details(code);
            }}
          //  cout<<"\n press any key";
            //getch();
            break;

           case 2:
            system("cls");
            {
                cout<<"\n enter keywords of the title : ";
                char booktitle[30];
                fflush(stdin);
                gets(booktitle);
                int found = 0;
                found = search_book(booktitle);
                if(found == 0)
                    cout<<"\n book does not exist ";
                else if(found == 1 || found ==2)
                {
                    long int code = getcode(booktitle);
                    show_details(code);

                }
            //    cout<<"\n press any key";
            //    getch();

            }
            break;
           case 3:
            system("cls");
            {
                 cout<<"\n enter keywords of the author : ";
                char bookauthor[30];
                fflush(stdin);
                gets(bookauthor);
                int found = 0;
                found = search_book(bookauthor);
                if(found == 0)
                    cout<<"\n book does not exist ";
                else if(found == 1 || found ==2)
                {
                    long int code = getcode(bookauthor);
                    show_details(code);

                }
             //   cout<<"\n press any key";
             //   getch();
            }
            }
            cout<<"\n press any key ";
            getch();
        }
        break;
    case 4:
        system("cls");
        {
             fflush(stdin);
             cout<<"\n enter the roll no of the student : ";
             char rollcode[11];
             gets(rollcode);
             int found = 0;
             found = search_stud(rollcode);
             if(found == 0)
                cout<<"\n student is not registered ! ";
             else if(found==1 || found==2)
             {
                 student st;
                 fstream fs;
                 fs.open("student.dat", ios::in|ios::binary);
                 if(!fs)
                 {
                     cout<<"\n cannot open file ! ";
                     getch();
                     return -1;
                 }
                 while(fs.read((char*)&st, sizeof(st)))
                {
                     if(strcmpi(st.sroll,rollcode) == 0)
                     {
                         st.display();
                         cout<<"\n no. of books issued = "<<st.no_of_books;
                         if(st.no_of_books>0)
                         {
                             show_issued_books(rollcode);
                         }
                     }
                 }
                 fs.close();
             }
             cout<<"\n\n press any key ";
             getch();
        }
        break;
    case 5:
        system("cls");
        issue();
        cout<<"\n press any key ";
        getch();
        break;
    case 6:
       {

        system("cls");
        cout<<"enter the book code of book to be returned: ";
        long int bk2;
        cin>>bk2;
        cout<<"enter the roll number of student: ";
        char rollno2[12];
        fflush(stdin);
        gets(rollno2);
        changebookstatus(bk2);

        changestudentissuestatus(rollno2,-1);

        int cdd,cmm,cyy;
        setdate(&cdd,&cmm,&cyy);
        int date=getissuedate(bk2,1);
        int month =getissuedate(bk2,2);
        int year=0;
         year=getissuedate(bk2,3);

		 cout<<"\n issue date was "<<date<<"-"<<month<<"-"<<year<<endl;

        cout<<"no. of days you have issued the book is : "<<difference(cdd,cmm,cyy,date,month,year);
		changeissuestatus(bk2);

    cout<<"\n\n press any key ";
    getch();
        break;
       }
case 10:
        system("cls");
        {
            fstream f;
            f.open("student.dat", ios::app|ios::binary);
            student st;
            st.input();
            f.write((char*)&st, sizeof(st));
            f.close();
            cout<<"\n student details registered successfully ! ";
            cout<<"\n\n press any key ";
            getch();
        }
        break;
case 7:
    system("cls");
       {
         cout<<"The registered students are:-\n";
         student stud;
         fstream fs;
         fs.open("student.dat", ios::in|ios::binary);
         if(!fs)
         {
           cout<<"cannot open file";
           cout<<"\npress any key to continue";
           getch();
         }
         fs.seekg(0);
         while(fs.read((char*)&stud,sizeof(stud)))
         {
           stud.display();
         }
         cout<<"\n\n press any key ";
         getch();
       }
       break;

case 11:
    system("cls");
       {
         cout<<"The list of books are:-\n";
         book bk;
         fstream fb;
         fb.open("book.dat", ios::in|ios::binary);
         if(!fb)
         {
           cout<<"cannot open file";
           cout<<"\npress any key to continue";
           getch();
         }
         fb.seekg(0);
         while(fb.read((char*)&bk,sizeof(bk)))
         {
           bk.display();
         }
         cout<<"\n\n press any key ";
         getch();
       }
       break;

case 12 :

        system("cls");
        {
        student st;
        char roll[11];
        fflush(stdin);
        cout<<"\n enter the roll no to be deleted : ";
        gets(roll);
        int found=search_stud(roll);
        if(found==0)
            cout<<"\n this record does not exist ! ";

        else if(found == 1 || found==2)
        {
            if(st.no_of_books>0)
            {
                cout<<"\n student has issued book(s) ";
                cout<<"\n record cannot be deleted";

            }
            else{
            fstream f;
            f.open("student.dat", ios::in|ios::binary) ;
            fstream ftemp;
            ftemp.open("student1.dat", ios::out|ios::binary) ;
            f.seekg(0);
            while(f.read((char*)&st, sizeof(st)))
            {
                if(strcmpi(st.sroll,roll)==0)
                {
                    cout<<"\n details of the student are :\n";
                    st.display() ;
                }
                else
                    ftemp.write((char*)&st, sizeof(st)) ;
            }
            f.close();
            ftemp.close();
            int choice;
            cout<<"\n\n you really want to delete ?";
            cout<<"\n 0 -> no     1 -> yes \t";
            cin>>choice;
            if(choice==1)
            {
                remove("student.dat") ;
                rename("student1.dat", "student.dat") ;
                cout<<"\n student record deleted ";
            }}
        }
        cout<<"\n press any key ";
        getch();
        }
        break;
case 15:
    system("cls");
    {
        fstream file;
        file.open("issued.dat", ios::in|ios::binary);
        if(!file)
        {
            cout<<"\n cannot open file";
            getch();
            break;
        }
        file.seekg(0);
        issued iss;
        while(file.read((char*)&iss, sizeof(iss)))
        {
            iss.details();
        }
    }
    case 14:
        exit(1);

    }

    }while(1);
}
