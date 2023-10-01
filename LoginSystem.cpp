#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
using namespace std;

class Person
{
private:
    string name;
    string userName;
    string password;

public:
    bool login();
    bool checkUserNameCopy();
    void registration();
    void forgetPassword();
};
bool Person::login()
{
    int count = 0;
    int isUserNameMatch=0;
    string UName, pass;
    cout << "Enter the user name : " << endl;
    cin >> UName;
    cout << "Enter the Password : " << endl;
    cin >> pass;
    fstream check;
    check.open("DataBase.txt", ios::in | ios::binary);
    check.read((char *)this, sizeof(*this));
    while (!check.eof())
    {
        
        if (this->userName == UName)
        {
            if(this->password==pass)
            {
                cout << "\nLogin Sucessfully "<<endl<<endl<<endl;
                count++;
                return true;
            }
            else
            {
                isUserNameMatch++;
            }
        }
        check.read((char *)this, sizeof(*this));
    }

    if(isUserNameMatch==1)
        cout<<"\n'UserName is Right but Password is wrong'";
    if (count == 0)
        cout << "\n'Informations Don't match'"<<endl<<endl<<endl;
    return false;
    check.close();
}
bool Person::checkUserNameCopy()
{
    fstream insert;
    insert.open("DataBase.txt",ios::in|ios::binary);
    cout << "WELCOME" << endl;
    string UName;
    cout << "Enter the User Id : ";
    cin >>UName;
    insert.read((char*)this,sizeof(*this));
    while(!insert.eof())
    {
        if(this->userName==UName)
        {
            cout<<"This name is already taken"<<endl;
            return false;
        }
        insert.read((char*)this,sizeof(*this));
    }
    insert.close();
    cout<<"This user name is Unique"<<endl;
    return true;

}
void Person::registration()
{
    fstream insert;
    insert.open("DataBase.txt",ios::app|ios::binary);
    cout<<"Please Enter the user name Again : "<<endl;
    cin>>this->userName;
    cout<<"Please Enter the Password : ";
    cin>>this->password;
    insert.write((char*)this,sizeof(*this));
    insert.close();
}
void Person::forgetPassword()
{
    int count=0;
    string UName;
    cout<<"Enter the User Name : ";
    cin>>UName;
    fstream find;
    find.open("DataBase.txt",ios::in|ios::binary);
    find.read((char*)this,sizeof(*this));
    while(!find.eof())
    {
        if(this->userName==UName)
        {
            cout<<"Your Name is "<<name<<endl;
            cout<<"Your Password is : "<<password<<endl;
            count++;
            break;
        }
        find.read((char*)this,sizeof(*this));
        find.close();
    }
    if(count==0)
        cout<<"\nUser Name not found "<<endl;
}
void menu()
{
    bool flag = true;
    while (flag)
    {
        Person P;
        cout << "\nPress 1 for login : " << endl;
        cout << "Press 2 for registration : " << endl;
        cout << "Press 3 for recover password : " << endl;
        cout << "Press 4 for EXIT : " << endl;
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            P.login();
            break;
        case 2:
            if(P.checkUserNameCopy())
                P.registration();
            break;
        case 3:
            P.forgetPassword();
            break;
        case 4:
            flag = false;
            break;
        default:
            cout << "INVALID CHOICE";
            break;
        }
    }

}


int main()
{
    menu();
    return 0;
}


