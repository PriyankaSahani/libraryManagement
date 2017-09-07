#include <bits/stdc++.h>
#include<conio.h>
#include<ctime>

using namespace std;

class issued
{   public:
    char roll[11];
    long int book_code;
    int dd;
    int mm;
    int yy;
    void details();

};

void issued :: details()
{
    cout<<"\n book code : ";
    cout<<book_code;
    fflush(stdout);
    //issued on and details
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
    //year_of_add = get_year(sroll);
    //sbranch = get_branch(sroll);
}

void student :: display()
{
     cout<<"\n details are "<<endl;
    fflush(stdout);
     cout<<"\n name : "<<endl;
     puts(sname);
    fflush(stdout);
     cout<<"\n roll no : "<<endl;
     puts(sroll);
    fflush(stdout);
     cout<<"\n branch : "<<endl;
     puts(sbranch);
     fflush(stdout);
      cout<<"\n year of admission : "<<endl;
      cout<<year_of_add;
    fflush(stdout);
     cout<<"\n phone no. : "<<endl;
     puts(sphone);
    fflush(stdout);
    if(no_of_books == 0)
        cout<<"\n student has not issued any book ! ";

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
    status = false;
}

void book:: display()
{
    cout<<"\n details are "<<endl;
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
    if(status == false)
        cout<<"  this book is not issued to anyone ";
    else
        cout<<"  this book is already issued ";

}

void changestudentissuestatus(char roll[], int x)
{
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
            cout<<"incremented" <<endl;
            file.seekp(recno*sizeof(st)) ;
            file.write((char*)&st,sizeof(st)) ;
        }
        cout<<"whole ki andar";
        recno++;
    }
    file.close();

}
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
                else
                    bk.status = false;
                fb.seekp(recno*sizeof(bk));
                fb.write((char*)&bk,sizeof(bk)) ;
            }
            recno++;
        }
        fb.close();
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
    char rollcode[11];
    gets(rollcode);
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
            changestudentissuestatus(rollcode,3);



        }

        cout<<"\n  book issued ! ";

    }

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


int main()
{   system("cls");
    int ans;
    do{
    cout<<"\n enter one option from the menu "<<endl;
    cout<<"\n 1. Add a book ";
    cout<<"\n 2. Remove a book ";
    cout<<"\n 3. Search book ";
    cout<<"\n 4. Search student ";
    cout<<"\n 5. Issue ";
    cout<<"\n 6. Return ";
    cout<<"\n 7. Registered students ";
    cout<<"\n 8. Modify book details ";
    cout<<"\n 9. Modify student details ";
    cout<<"\n 10. register new student ";
    cout<<"\n 11. list of books ";
    cout<<"\n 12. delete student ";
    cout<<"\n 13. list of defaulters ";
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
        }
        break;
    case 3:
        system("cls");
        {
            cout<<"\n enter the book id of the book  : ";
            long int code;
            cin>>code;
            int found=0;
            found = search_book(code);
            if(found == 0)
                cout<<"\n book does not exist  ";
            else if(found==1 || found==2)
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
            }
        }
        break;
    case 4:
        system("cls");
        {    fflush(stdin);
             cout<<"\n enter the roll no of the student : ";
             char rollcode[11];
             gets(rollcode);
             int found =0;
             found= search_stud(rollcode);
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
                         if(st.no_of_books>0)
                         {
                             show_issued_books(rollcode);
                         }
                     }
                 }
                 fs.close();
             }
        }
        break;
    case 5:
        system("cls");
        issue();
        break;
    case 6:
        system("cls");
    //    return();
        break;
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
        }
    case 14:
        exit(1);

    }

    }while(1);
}


