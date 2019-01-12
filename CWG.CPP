//PROGRAM ON COMMON WEALTH GAMES MANAGEMENT
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<iomanip.h>
#include<dos.h>
class cwg
{
	int tid,noticket;
	char name[20],game[20],phone[11];
	public:
	cwg()
	{
		tid=noticket=0;
		strcpy(name,NULL);
		strcpy(phone,NULL);
		strcpy(game,NULL);
	}
	void ticketid();
	void inputinfo(int);
	void display();
	int retnoticket()
	{
		return noticket;
	}
	int rettid()
	{
		return tid;
	}
	void modi();
}c;


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
|This function is called by append() to generate a|
|new ticket id evry time user book tickets.       |
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void cwg::ticketid()
{
	int a;
	fstream f("ticket.dat",ios::in||ios::out);
	if(!f)
		a=0;
	while(!f.eof())
	{
		f.read((char*)&c,sizeof(c));
		a=tid;
	}
	a++;
	inputinfo(a);
	f.close();
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
|This function will help in entering the details|
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void cwg::inputinfo(int ab)
{
	clrscr();
	tid=ab;
	cout<<"\tGAMES ARE:\n";
	cout<<"\t\t|*Shooting      |\n" ;
	cout<<"\t\t|*Wrestling     |\n";
	cout<<"\t\t|*Archery       |\n";
	cout<<"\t\t|*Boxing        |\n";
	cout<<"\t\t|*Atheletics    |\n";
	cout<<"\t\t|*Weightlifting |\n";
	cout<<"\t\t|*Badminton     |\n";
	cout<<"\t\t|*Table tennis  |\n";
	cout<<"\t\t|*Tennis        |\n";
	cout<<"\t\t|*Gymnastics    |\n";
	cout<<"\t\t|*Hockey        |\n";
	cout<<"\t\t|*Aquatics      |\n";
	cout<<"\t\t|*Netball       |\n";
	cout<<"\t\t|*Rugby         |\n";
	cout<<"\t\t|*Squash        |\n";
	cout<<"\nEnter the name of the game from the above list: ";
	gets(game);
    A:	cout<<"\nEnter your name: ";
	gets(name);
	for(int i=0;name[i]!='\0';i++)
	{
	  if(!isalpha(name[i]))
	  {
		cout<<"\nWrong name entered. Re-enter...\n";
		goto A;
	  }
	}
	cout<<"\nEnter the no. of tickets: ";
	cin>>noticket;
    B:	cout<<"\nEnter your phone no.: ";
	gets(phone);
	if(strlen(phone)!=10)
	{
		cout<<"\nWrong phone number entered. Re-enter...\n";
		goto B;
	}
	delay(1000);
	cout<<"\n\n\t""!__CONGRATS YOUR TICKETS ARE BOOKED__!""";
	cout<<"\n\t\tPlease pay Rs."<<(noticket*500);
	cout<<"\n\t\tYOUR TICKET ID IS "<<tid;
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
|The function will help in displaying the details|
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void cwg::display()
{
	cout<<"\nThe game is: "<<game;
	cout<<"\nThe ticket ID is: "<<tid;
	cout<<"\nThe name is: "<<name;
	cout<<"\nThe no. of tickets are: "<<noticket;
	cout<<"\nThe phone no. is: "<<phone;
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
|This function will first display the details and|
|then it will modify the details                 |
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void cwg::modi()
{
	cout<<"\nTicket ID:"<<tid<<endl;
	cout<<"Game:"<<game<<endl;
	cout<<"Name:"<<name<<endl;
	cout<<"Number of tickets:"<<noticket<<endl;
	cout<<"Phone number:"<<phone<<endl;
	cout<<"Enter new details....\n\n"<<endl;
	char nm[20],gm[20],ph[11];
	int no;
	cout<<"Enter the new game (Press '.' to retain old one): ";
	gets(gm);
	cout<<"Enter the new name (Press '.' to retain old one): ";
	gets(nm);
	cout<<"Enter the no. of tickets (Press '1' to retain old one): ";
	cin>>no;
	cout<<"Enter new phone no.(Press '1' to retain old one): ";
	cin>>ph;
	if(strcmp(gm,".")!=0)
		strcpy(game,gm);
	if(strcmp(nm,".")!=0)
		strcpy(name,nm);
	if(strcmp(ph,"1")!=0)
		strcpy(phone,ph);
	if(no!=1)
		noticket=no;
	cout<<"\n\n\n\t\t\t!...RECORD MODIFIED...!";
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
|This function will delete the enteries of tickets|
|from the file.         			  |
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void deleteticket(int no)
{
	fstream fp("ticket.dat",ios::in|ios::out|ios::binary);
	fstream fo("temp2.dat",ios::out|ios::binary);
	fp.seekg(0,ios::beg);
	while(!fp.eof())
	{
	   fp.read((char*)&c,sizeof(c));
		if(c.rettid()==no)
		{
			c.display();
			delay(600);
			cout<<"\n\n\t\t....<<RECORD DELETED>>.... ";
		}
		else
			fo.write((char*)&c,sizeof(c));
	}
	fo.close();
	fp.close();
	remove("ticket.dat");
	rename("temp2.dat","ticket.dat");
	getch();
}


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
|This function will append the records in the file.|
=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void append()
{
	clrscr();
	fstream fp;
	fp.open("ticket.dat",ios::out|ios::binary);
	int m;
	char ans='y';
	while(ans=='y')
	{
		c.ticketid();
		fp.write((char*)&c,sizeof(c));
		cout<<"\n\nDo you want to book more tickets(y/n): ";
		cin>>ans;
	}
	fp.close();
}


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
|This function is modifying the records from the file|
by invoking the function named "modi".               |
-==-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void modify()
{
	clrscr();
	fstream fio("ticket.dat",ios::in|ios::out|ios::binary);
	int id;
	int pos;
	char found='n';
	cout<<"\nEnter the Ticket ID: ";
	cin>>id;
	while(!fio.eof())
	{
		fio.read((char*)&c,sizeof(c));
		pos=fio.tellg();
		if(c.rettid()==id)
		{
			c.modi();
			fio.seekg(pos);
			fio.write((char*)&c,sizeof(c));
			found='y';
			break;
		}
	}
	if(found=='n')
	   cout<<"\n\n\nTicket ID not found......!!";
	getch();
}


/*=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
|This function is searching the records with the help|
|of a variable named "tid".                          |
=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void search()
{
	clrscr();
	fstream se("ticket.dat",ios::in|ios::out|ios::binary);
	int t;
	char found='n';
	cout<<"\nEnter the Ticket ID to be searched: ";
	cin>>t;
	while(!se.eof())
	{
		se.read((char*)&c,sizeof(c));
		if(c.rettid()==t)
		{
			c.display();
			found='y';
			break;
		}
	}
	if(found=='n')
	cout<<"\n\n\n\t...Ticket ID not found....";
	se.close();
	getch();
}


/*=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
|This function count the total number of tickets been|
|already booked.                                     |
=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void countticket()
{
	clrscr();
	ifstream fi2("ticket.dat",ios::in|ios::binary);
	int count=0;
	while(!fi2.eof())
	{
		fi2.read((char*)&c,sizeof(c));
		count+=c.retnoticket();
	}
	cout<<"\nNumber of tickets booked: "<<count;
	fi2.close();
	getch();
}


/*=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
|This function shows the list of games.            |
=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void listgames()
{
	int a;
	clrscr();
	cout<<"\tGAMES ARE:\n";
	cout<<"\t\t|*Shooting      |\n" ;
	cout<<"\t\t|*Wrestling     |\n";
	cout<<"\t\t|*Archery       |\n";
	cout<<"\t\t|*Boxing        |\n";
	cout<<"\t\t|*Atheletics    |\n";
	cout<<"\t\t|*Weightlifting |\n";
	cout<<"\t\t|*Badminton     |\n";
	cout<<"\t\t|*Table tennis  |\n";
	cout<<"\t\t|*Tennis        |\n";
	cout<<"\t\t|*Gymnastics    |\n";
	cout<<"\t\t|*Hockey        |\n";
	cout<<"\t\t|*Aquatics      |\n";
	cout<<"\t\t|*Netball       |\n";
	cout<<"\t\t|*Rugby         |\n";
	cout<<"\t\t|*Squash        |\n";
	cout<<"\n\n....Press 1 to return....\n";
	cin>>a;
	getch();
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
|This is loading function and it will be invoked while	|
|going from one menu to main menu.                    	|
|This function uses keyword "delay" to delay the loading|
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void loading()
{
	cout<<"\n\n\n\tLOADING, PLEASE WAIT.....";
	cout<<"\t\t!!!!";
	delay(800);
	cout<<"!!!!!";
	delay(500);
	cout<<"!!!!!!";
	delay(900);
	cout<<"!!!";
	cout<<"\n\n\t\t.....PRESS ENTER TO CONTINUE.....";
	getch();
}


/*=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
|This is administrator function and it will be invoked|
|when option 1 will be chosen from main menu.         |
|In this function the user is given function to       |
|display list of games,view ticket entry,view total   |
|tickets booked etc.                                  |
-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void administrator()
{
	clrscr();
	int ch;
	void mainmenu();
	void listgames();
	cout<<"\n\t\t\t::::WELCOME TO ADMINISTRATOR MENU::::\n\n" ;
	cout<<"1. TO VIEW LIST OF GAMES\n";
	cout<<"2. TO VIEW TICKET ENTRY\n";
	cout<<"3. TO VIEW TOTAL NUMBER OF TICKETS BOOKED\n";
	cout<<"4. TO RETURN BACK\n";
	cout<<"5. TO EXIT";
	cout<<"\n\nEnter your choice: ";
	cin>>ch;
	switch(ch)
	{
		case 1:
			listgames();
			administrator();
			break;
		case 2:
			search();
			administrator();
			break;
		case 3:
			countticket();
			administrator();
			break;
		case 4:
			loading();
			mainmenu();
			break;
		case 5:
			exit(0);
		default:
			cout<<"\n\n\t\t(VALID CHOICE ARE 1...5 ONLY) \n" ;
			break;
	}
	getch();
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
|this is costomer function and it will be invoked when|
|option 2 will be chosen from main menu.              |
|in this function the user is given function to create|
|display, modify, delete, exit etc.                   |
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void customer()
{
	clrscr();
	void mainmenu();
	void loading();
	void listgames();
	int ch1,a;
	cout<<"\n\t\t\t::::: WELCOME TO THE COSTOMER MENU :::::\n\n";
	cout<<"1. IF YOU WANT TO SEE THE LIST OF GAMES\n";
	cout<<"2. IF YOU WANT TO BUY TICKETS\n";
	cout<<"3. IF YOU WISH TO CANCEL ANY TICKET\n";
	cout<<"4. IT YOU WISH TO MODIFY ANY OF YOUR TICKET DETAILS\n";
	cout<<"5. TO VIEW YOUR TICKET DETAILS\n";
	cout<<"6. TO RETURN TO MAIN MENU\n";
	cout<<"7. TO EXIT\n\n";
	cout<<"ENTER YOUR CHOICE: ";
	cin>>ch1;
	switch(ch1)
	{
		case 1:
			listgames();
			customer();
			break;
		case 2:
			append();
			customer();
			break;
		case 3:
			clrscr();
			cout<<"\n\nEnter ticket ID whose record is to be deleted: ";
			cin>>a;
			deleteticket(a);
			customer();
			break;
		case 4:
			modify();
			customer();
			break;
		case 5:
			search();
			customer();
			break;
		case 6:
			loading();
			mainmenu();
			break;
		case 7:
			exit(0);
		default:
			cout<<"\n\n\t\t(VALID CHOICES ARE 1...7 ONLY)\n";
			break;
	}
getch();
}


/*=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
|This function uses keyword "setw" to run the mascot|
|of CWG i.e Clyde.                                  |
-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void clyde()
{
	void clyde2();
	int i=80;
	for(int j=35; j>1; j--)
	{
		clrscr();
		cout<<"\n"<<setw(i)<<"           \\    | /   /   /                 ";
		cout<<"\n"<<setw(i)<<"          \\    \\   /   /                   ";
		cout<<"\n"<<setw(i)<<"        \\    \\   |  |  | /                 ";
		cout<<"\n"<<setw(i)<<"           \\   _  ~~~_--_                   ";
		cout<<"\n"<<setw(i)<<"        .,(  ~~~~  ~~~~  },          /\\     ";
		cout<<"\n"<<setw(i)<<"       .,/    $      $    ),       /^  ^\\   ";
		cout<<"\n"<<setw(i)<<"       ,(        ::        ),     |     |   ";
		cout<<"\n"<<setw(i)<<"       ,(    _   ::    _   ),     |     |   ";
		cout<<"\n"<<setw(i)<<"        ,(  \\  \\_._._.//   /      |     |   ";
		cout<<"\n"<<setw(i)<<"         .\\   \\......./   }        /     |   ";
		cout<<"\n"<<setw(i)<<"             |           |       /       /   ";
		cout<<"\n"<<setw(i)<<"        /----  --------  ------^       /    ";
		cout<<"\n"<<setw(i)<<"     / ^  __ /   _____  \\ _          /      ";
		cout<<"\n"<<setw(i)<<"   /    /   !  / .==*   \\ !  ------/        ";
		cout<<"\n"<<setw(i)<<"  |    |    ! | ||  ,,,  |!                 ";
		cout<<"\n"<<setw(i)<<"  |     \\__ !  \\ \\\\_; : / !                 ";
		cout<<"\n"<<setw(i)<<"    \\      /!   \\______/  !                 ";
		cout<<"\n"<<setw(i)<<"      \\   | |\\.........../                  ";
		cout<<"\n"<<setw(i)<<"        ^^\\/  /   /\\   \\                   ";
		cout<<"\n"<<setw(i)<<"             /   /  \\   \\                  ";
		cout<<"\n"<<setw(i)<<"            /   /    \\   \\                 ";
		cout<<"\n"<<setw(i)<<"         __/   /      \\   \\__              ";
		cout<<"\n"<<setw(i)<<"         (______|       |_____)             ";
		delay(100);
		i--;
	}
	delay(200);
	clyde2();
	getch();
}


void clyde2()
{
clrscr();
cout<<"\n           \\    | /   /   /                        ";
cout<<"\n          \\    \\   /   /                           ";
cout<<"\n        \\    \\   |  |  | /                         ";
cout<<"\n           \\   _  ~~~_--_                          ";
cout<<"\n        .,(  ~~~~  ~~~~  },           /\\             ";
cout<<"\n       .,/    $      $    ),        /^  ^\\           ";
cout<<"\n       ,(        ::        ),      |     |           ";
cout<<"\n       ,(    _   ::    _   ),      |     |           ";
cout<<"\n        ,(  \\  \\______//   /       |     |           ";
cout<<"\n         .\\   \\______/    }        /     |           ";
cout<<"\n             |           |       /       /                WELCOME TO THE      ";
cout<<"\n        /----  --------  ------^       /               COMMONWEALTH GAMES  ";
cout<<"\n     / ^  __ /   _____   \\ _         /                          XX      ";
cout<<"\n   /    /   !  / .==*   \\ !  ------/                          GLASGOW         ";
cout<<"\n  |    |    ! | ||  ,,,  |!                        ";
cout<<"\n  |     \\__ !  \\ \\\\_; : / !                        ";
cout<<"\n    \\      /!   \\______/  !                        ";
cout<<"\n      \\   | |\\.........../                         ";
cout<<"\n        ^^\\/  /   /\\   \\                           ";
cout<<"\n             /   /  \\   \\                          ";
cout<<"\n            /   /    \\   \\                         ";
cout<<"\n         __/   /      \\   \\__                      ";
cout<<"\n        (______|       |_____)                     ";
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
|This function gives user 3 option i.e      |
|administrator menu, customer menu and exit.|
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void mainmenu()
{
	clrscr();
	int ch2;
	cout<<"\n\n       MAIN MENU:\n\n";
	cout<<"1. Administrator Menu.\n";
	cout<<"2. Customer Menu.\n";
	cout<<"3. Exit.\n\n";
	cout<<"ENTER YOUR CHOICE: ";
	cin>>ch2;
	switch(ch2)
	{
		case 1:
			administrator();
			break;
		case 2:
			customer();
			break;
		case 3:
			exit(0);
		default:
			cout<<"WRONG CHOICE ENTERED...";
			break;
	}
}


/*-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
|This is main function and it invokes various function|
|i.e mainmenu() and clyde().                          |
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

void main()
{
	clrscr();
	void clyde();
	void mainmenu();
	clyde();
	mainmenu();
	getch();
}
