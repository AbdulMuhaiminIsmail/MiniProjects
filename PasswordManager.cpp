#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
using namespace std;

int response;
void sugg_pass()
{
    char arr[]="1234567890!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; //total 70 characters(indices 0-69)
    int n, length = sizeof(arr)-1; //(\0 is the 71st so we minus one)
    long long seed=std::chrono::system_clock::now().time_since_epoch().count(); //seed for true randomness it is the nanoseconds since epoch
    srand(seed);
    cout<<"Enter the desired length for password: ";
    cin>>n;
    cout<<"Generated password: ";
    for (int i = 0; i < n; i++)
    {
        cout<<arr[rand() % length]; //69%70=69 :: 70%70=0 in this way it does not let index exceed 69
    }
}
int del_pass()
{
    vector<string> lines;
    fstream file;
    file.open("passMngr.txt");
    if (file.is_open())
    {
        string platform, line, username;
        bool platformIsFound=false;
        cout<<"Enter platform: ";
        cin>>platform;
        cout<<"Enter username: ";
        cin>>username;
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
        for (int i = 0; i < lines.size(); i++)
        {
            if ((lines[i]==platform)&&(lines[i+1]=="Username/E-mail: "+username))
            {
                platformIsFound=true;
                vector<string>::iterator start = lines.begin() + i;
                vector<string>::iterator end = lines.begin() + (i+4);
                if (end>lines.end())
                {
                    end=lines.end();
                }
                
                lines.erase(start,end);
            }
            else
            {
                continue;
            }
        }
        if (platformIsFound=false)
        {
            cout<<"Platform not found.";
            return 1;
        }
        
    }
    else
    {
        cout<<"Error opening file!"<<endl;
        return 1;
    }
    file.open("passMngr.txt", std::ios::out);
    if(file.is_open())
    {
        for (int i = 0; i < lines.size(); i++)
        {
            file << lines[i] << endl;
        }
        file.close();
        cout<<"System Updated!";
    }
    else
    {
        cout<<"Error updating system!";
    }
    return 0;
}
int update_pass()
{
    vector<string> lines;
    fstream file;
    file.open("passMngr.txt");
    if (file.is_open())
    {
        string platform, username, line, newPass;
        bool platformIsFound=false;
        cout<<"Enter platform: ";
        cin>>platform;
        cout<<"Enter username: ";
        cin>>username;
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
        for (int i = 0; i < lines.size(); i++)
        {
            if ((lines[i]==platform)&&(lines[i+1]=="Username/E-mail: "+username))
            {
                platformIsFound=true;
                cout<<"Enter new password: ";
                cin>>newPass;
                lines[i+2]="Password: "+newPass;
                break;
            }
            else
            {
                continue;
            }
        }
        if (platformIsFound==false)
        {
            cout<<"Platform not found.";
            return 1;
        }
        
    }
    else
    {
        cout<<"Error opening file!"<<endl;
        return 1;
    }
    file.open("passMngr.txt", std::ios::out);
    if(file.is_open())
    {
        for (int i = 0; i < lines.size(); i++)
        {
            file << lines[i] << endl;
        }
        file.close();
        cout<<"System Updated!";
    }
    else
    {
        cout<<"Error updating system!";
    }
    return 0;
}
void add_pass()
{
    string inputText, platform, pass, name;
    cout<<"Enter the name of app/website: ";
    cin>>platform;
    cout<<"Enter the username/email: ";
    cin>>name;
    cout<<"Enter the password: ";
    cin>>pass;
    inputText=platform+"\n"+"Username/E-mail: "+name+"\n"+"Password: "+pass+"\n----------------------------\n";
    fstream outputFile;
    outputFile.open("passMngr.txt", std::ios::app);
    if (outputFile.is_open())
    {
        outputFile << inputText;
        cout<<"\nSystem updated!";
        outputFile.close();
    }
    else
    {
        cerr<<"Error opening file."<<endl;
    }   

}
void list_pass()
{
    string line;
    fstream outputFile;
    outputFile.open("passMngr.txt");
    if (outputFile.is_open())
    {
        cout<<endl;
        while (getline(outputFile, line))
        {
            cout<<line<<endl;
        }
         
    }
    else
    {
        cout<<"Error opening file!";
        exit(0);
    }    
}
int retrieve_pass()
{
    fstream outputFile;
    outputFile.open("passMngr.txt");
    if (outputFile.is_open())
    {
       string line, email, pass, platform;
       bool platformIsFound=false;
       cout<<"Enter the platform for which you want to retrieve login details: ";
       cin>>platform;
       while (getline(outputFile, line))
       {
        if (line==platform)
        {
            if (getline(outputFile, email) && getline(outputFile, pass))
            {
                platformIsFound=true;
                cout<<"["<<platform<<"]"<<endl;
                cout<<email<<endl;
                cout<<pass<<endl;
                cout<<"----------------------------"<<endl;
                continue;
                
            }
            
        }
       }
       if (platformIsFound==false)
       {
            cout<<"Platform not found.";
            return 1;
       }
       outputFile.close();
       
        
    }
    return 0;
    
}
int menu()
{
    cout<<"\n1. Add Password\n";
    cout<<"2. Retrieve Password\n";
    cout<<"3. Update Password\n";
    cout<<"4. Delete Password\n";
    cout<<"5. List All Password(s)\n";
    cout<<"6. Suggest Strong Password\n";
    cout<<"7. Exit";
    cout<<"\nChoose one option from (1-7): ";
    cin>>response;
    return response;
}
int main() 
{
    string master_pass, input_pass, platform;
    master_pass="your_password";
    cout<<"Please enter Master Password for authorization: ";
    cin>>input_pass;
    if (input_pass==master_pass)
    {
        cout<<"Access Granted! ";
        bool isRun=true;
        cout<<"\nWelcome to your Password Manager!";
        while(isRun==true)
        {
            response=menu();
            if (response==1)
            {
                add_pass();
            }
            else if (response==2)
            {
                retrieve_pass();
            }
            else if (response==3)
            {
                update_pass();
            }
            else if (response==4)
            {
                del_pass();
            }
            
            else if(response==5)
            {
                list_pass();
            }
            else if(response==6)
            {
                sugg_pass();
            }
            else if(response==7)
            {
                cout<<"System closed!";
                isRun=false;
                return 0;
            }
            else
            {
                cout<<"Incorrect option!";
            }
        }
    }
    else
    {
        cout<<"Incorrect master password.";
    }

    return 0;
    
}