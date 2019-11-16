#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iomanip>

#define PA "Physical Attack!"
#define SA1 "Special Attack 1!"
#define SA2 "Special Attack 2!"

typedef char CHAR[50];

using namespace std;

/* DECLARATIONS*/

void MENU();
void New_Game(); void Game_Info();
int combat(int); void sub_combat(int,int);
void View_Matches();
void View_WIN();
void Del_REC(); void Del_W_REC(int);
void Modify_REC(); void Modify_W_REC(int,char[]);
void PlayerSearch();

/* CLASS DEFINITIONS */

class Player
{
	int health; //health of hero
	unsigned int CD_1; //spl. attack 1 cooldown
	unsigned int CD_2; //spl. attack 2 cooldown
	unsigned int Potion;
	unsigned int P_id;
	public:
		CHAR Name, Hero_Name;
		Player()
		{
			health=1500;
			CD_1=5;
			CD_2=3;
			Potion=2;
		}
		void getinfo();
		void putinfo();
		void put_lim_info();
		int modify_H(int);
		void modify_CD_1(int x=0)
		{
			if (x==2)
				CD_1=0;
			else
				CD_1++;

			if (CD_1>5)
				CD_1=5;
		}
		void modify_CD_2(int x=0)
		{
			if (x==3)
				CD_2=0;
			else
				CD_2++;

			if (CD_2>3)
				CD_2=3;
		}
		void modify_P()
		{
			--Potion;
		}
		int ret_H()
		{
			return health;
		}
		int ret_CD_1()
		{
			return CD_1;
		}
		int ret_CD_2()
		{
			return CD_2;
		}
		int ret_P()
		{
			return Potion;
		}
		int ret_P_id()
		{
			return P_id;
		}
		void set_P_id(int id)
		{
			P_id=id;
		}
		void refresh()
		{
			health=1500;
			CD_1=5;
			CD_2=3;
			Potion=2;
		}
};

void Player::getinfo()
{
	cout << endl;

	fflush(stdin);

	cout << "Enter your name: ";
	gets(Name);
	cout << "Enter your hero's name: ";
	gets(Hero_Name);
	cout << "Enter your Player ID: ";
	cin >> P_id;
}

void Player::putinfo()
{
	cout << endl << setw(15) << Name;
	cout << setw(15) << Hero_Name;
	cout << setw(15) << P_id;
	cout << setw(15) << Potion << endl;
}

void Player::put_lim_info()
{
	cout << endl << setw(20) << Name << setw(20) << Hero_Name << setw(20) << P_id << endl;
}

int Player::modify_H(int a) //a=attack type
{
	if(a==1)
	{
		health-=50;
		if (health<0)
			health=0;
	}
	else if(a==2)
	{
	 	srand (time(NULL));
	 	int effect_1 = rand()%301+100;
	 	health-=effect_1;
	 	if(health<0)
		{
			effect_1+=health;
			health=0;
		}
	 	return effect_1;
	}
	else if(a==3)
	{
		srand (time(NULL));
	 	int effect_2 = rand()%101+50;
	 	health-=effect_2;
	 	if(health<0)
		{
			effect_2+=health;
			health=0;
		}
	 	return effect_2;
	}
	else
	{
		int effect_rt=health;
		srand (time(NULL));
		int effect_3 = rand()%201+100;
		health+=effect_3;
		if(health>1500)
			health=1500;
			effect_3=health-effect_rt;
		return effect_3;
	}
}

class Game
{
	unsigned int Match_ID;

	public:

	Game()
	{
		Match_ID=0;
	}

	Player P[2]; //Containership

	void set_M_ID();

	unsigned int ret_M_ID()
	{
		return Match_ID;
	}

	void putdat();

}G;

void Game::set_M_ID()
{
	Game g;
	ifstream fin;
	srand(time(NULL));
	Match_ID=rand()%65535;
	fin.open("MatchData.dat",ios::in|ios::binary);
	while(fin.read((char*)&g,sizeof(g)))
	{
		while(Match_ID==g.ret_M_ID())
			Match_ID=rand()%65535;
	}
	fin.close();
}

void Game::putdat()
{
	cout << endl << setw(40) << "MATCH ID: " << Match_ID << endl;
	cout << endl << setw(15) << "NAME" << setw(15) << "HERO NAME";
	cout << setw(15) << "PLAYER ID" << setw(15) << "POTIONS LEFT";
	for(int i=0;i<2;i++)
	{
		P[i].putinfo();
		cout << endl;
	}
}

/* FUNCTION DEFINITIONS */

void MENU()
{
	int n;
	do
	{
        system("CLS");
		cout << "\t \t ========== MENU ==========" << endl;
		cout << "\t \t 1. Play a new Game \n";
		cout << "\t \t 2. View list of matches recorded \n";
		cout << "\t \t 3. View list of winners \n";
		cout << "\t \t 4. Delete Game Records (by searching Match ID) \n";
		cout << "\t \t 5. Update Game Records (Player Name) \n";
		cout << "\t \t 6. Do a player search \n";
		cout << "\t \t 7. Exit\n\n";
		cout << "Enter your choice: "; cin >> n;

		switch (n)
		{
			case 1: New_Game(); break;
			case 2: View_Matches(); break;
			case 3: View_WIN(); break;
			case 4: Del_REC(); break;
			case 5: Modify_REC(); break;
			case 6: PlayerSearch();break;
			case 7: break;
			default: cout << "Invaid input!"; getch();
		}
	}while(n!=7);
}

void New_Game()
{
	cout << "\n\t \t ====================================================="<< endl;
	cout << "\t \t   PvP COMBAT GAME (TEXT VERSION) BY MRIGANK BADOLA"    << endl;
	cout << "\t \t =====================================================" << endl;
	Game_Info();



	char ch,key='N';
	int status;

	int id,flag,size;
	int ID[2];
	Game g;

	ofstream file_2;
	fstream file_1;
	file_1.open("MatchData.dat",ios::in|ios::out|ios::ate|ios::binary);
	file_2.open("Win_Data.dat",ios::out|ios::binary|ios::app);

	file_1.seekg(0,ios::end);
	size=file_1.tellg();

	G.set_M_ID();

	for(int i=0; i<2; i++)
	{

		do
		{
			cout << "Enter details, player " << i+1 << " :" << endl;
			if(size!=0)
			{
				cout << "Have you ever played this game before(y=YES)?: ";
				cin >> key;
				if (key=='Y'||key=='y')
				{
					cout << "Enter your player ID: ";
					cin >> id;

					file_1.clear();
					file_1.seekg(0,ios::beg);

					while(file_1.read((char*)&g,sizeof(Game)))
					{
						if(id==g.P[0].ret_P_id())
						{
							cout << "Welcome, " << g.P[0].Name << "! Good to see you back!" << endl;
							strcpy(G.P[i].Name,g.P[0].Name);
							G.P[i].set_P_id(id);

							cout << "Enter hero's name: ";

							fflush(stdin);

							gets(G.P[i].Hero_Name);
							status=1;
							break;
						}

						else if(id==g.P[1].ret_P_id())
						{
							cout << "Welcome, " << g.P[1].Name << "! Good to see you back!" << endl;
							strcpy(G.P[i].Name,g.P[1].Name);
							G.P[i].set_P_id(id);

							cout << "Enter hero's name: ";

							fflush(stdin);

							gets(G.P[i].Hero_Name);
							status=1;
							break;
						}

						else
						{
							status=0;
						}

					}
					if(!status)
					{
						cout << "No such player exists! Resuming enter full details ..." << endl;
					}
				}

				if (!(key=='Y'||key=='y') || !(status))
				{
					do
					{
						flag = 0;

						G.P[i].getinfo();

						file_1.clear();
						file_1.seekg(0,ios::beg);

						while(file_1.read((char*)&g,sizeof(Game)))
						{
							if(G.P[i].ret_P_id()==g.P[0].ret_P_id()||G.P[i].ret_P_id()==g.P[1].ret_P_id())
							{
								cout << "This player already exists! Enter correct details ..." << endl;
								flag=1;
								break;
							}
						}

						if(i==1 && G.P[1].ret_P_id()==G.P[0].ret_P_id() && !(flag))
						{
							cout << "This player already exists! Enter your details again ..." << endl;
							flag=1;
						}

					} while(flag);
				}
			}
			else
			{
				do
				{
					G.P[i].getinfo();

					if(i==1 && G.P[1].ret_P_id()==G.P[0].ret_P_id())
					{
						cout << "Player ID already exists! Enter your details again ..." << endl;
					}
					else if (G.P[i].ret_P_id()<=0)
					{
						cout << "Invalid input!" << endl;
					}
				}while(G.P[1].ret_P_id()==G.P[0].ret_P_id()||G.P[i].ret_P_id()<=0);
			}

			cout << endl << "Are you sure you want to save this data?" << endl;
			cout<<"Press any key other than y to re-enter details . . ."<<endl;
			cin >> ch;
			cout << endl;

			fflush(stdin);

		}while(!(ch=='y'||ch=='Y'));

		cout << "Saving your data . . ."<<endl;
		cout << "Done! Press any key to proceed ...";

		getch();
	}

	for(int i=0; i<2; i++)
	{
		ID[i]=G.P[i].ret_P_id();
		G.P[i].refresh();
	}

	cout << "We shall toss a coin. "<< G.P[0].Name << "(" << ID[0] << "), choose Heads(1) or Tails(2)."<<endl;
	int choice;
	cin>>choice;

	if(choice<1||choice>2)
	{
		cout << "Randomly selecting side ..." << endl;
		srand (time(NULL));
		choice=rand()%2+1;
	}

	srand (time(NULL));
	int side = rand()% 2 + 1;

	if (side==1)
		cout << "It's heads!" << endl;
	else
		cout << "It's tails!" << endl;

	if (side==choice)
	 {
	 	cout<<"Congrats, "<< G.P[0].Name << "(" << ID[0] << ")! You have won the toss and you will start the game.";
	 	choice=1;
	 }
	else
	{
		cout<<"Congrats, "<< G.P[1].Name << "(" << ID[1] << ")! You have won the toss and you will start the game.";
		choice=2;
	}

	getch();

	cout << "\t \t ================================================" << endl;
	cout << "\t \t \t \t The Battle Starts!"                         << endl;
	cout << "\t \t ================================================" << endl;

	int win=combat(choice);

	cout << endl << endl << G.P[win].Name << "(" << ID[win] << ") won the game!! CONGRATS!!"<< endl << endl;

	cout << endl << "Storing the details of winner ..." << endl;

    file_1.clear();
    file_1.seekp(0,ios::end);

    file_1.write((char*)&G,sizeof(Game));
    file_2.write((char*)&G.P[win],sizeof(Player));

	cout << "Done!";

	cout << endl << endl << "\t \t **************THANK YOU FOR PLAYING****************\n";

    file_1.close(); file_2.close();

    getch();
}

void Game_Info()
{
	cout << endl << "DESCRIPTION:-" << endl;
	cout << "1.This game can be played by two players only." << endl;
	cout << "2.Both the players are given a hero. They have to give a name to their hero." << endl;
	cout << "3.A hero has a health of 1500 points and has 3 abilities: " << endl << endl;
	cout << "(a)Normal Attack: Deals a damage of 50." << endl;
	cout << "(b)Special Attack 1: Deals random damage ranging from 100 to 400 hitpoints \nand has a 5-turn cooldown.\n";
	cout << "(c)Special Attack 2: Deals random damage ranging from 50 to 150 hitpoints \nand has a 3-turn cooldown.\n";
	cout << "Also, users are given two 'health potions' which restores health of hero \nranging from 100 to 300 points.\n\n";
	cout << "Press any key to proceed . . .";
	getch();
}

int combat(int x) //x=Player number
{
	int m=G.ret_M_ID();
	cout << setw(40) << "MATCH ID: " << m << endl;

	int id[2];

	for(int i=0; i<2; i++)
	{
		id[i]=G.P[i].ret_P_id();
	}

	int t; //attack option

	do
	{
		cout << endl << endl << G.P[x-1].Name << "(" << id[x-1] << "), what would you like to do?"<<endl;
		cout << "1. Physical Attack \t 2. Special Attack 1\n3. Special Attack 2 \t 4. Use Potion"<<endl<<endl;
		cout << "(   )\b\b\b";

		cin >> t;

		if(G.P[x-1].ret_CD_1()!=5&&t==2)
		{
			cout << SA1 << " not available. Dealing normal damage ..." << endl << endl;
			t=1;
		}

		if(G.P[x-1].ret_CD_2()!=3&&t==3)
		{
			cout << SA2 << " not available. Dealing normal damage ..." << endl << endl;
			t=1;
		}

		if(G.P[x-1].ret_P()==0&&t==4)
		{
			cout << "No potions left! Dealing normal damage ..." << endl << endl;
			t=1;
		}

		else if(t==2)
			G.P[x-1].modify_CD_1(t);

		else if(t==3)
			G.P[x-1].modify_CD_2(t);

		else if(t==4)
			G.P[x-1].modify_P();

		else if(t>4||t<0)
		{
			cout << "Wrong input, dealing normal damage ..." << endl << endl;
			t=1;
		}

		sub_combat(t,x); //sending attack type, player number to function

		if (x==2)
		{
			x=1;
		}

		else
		{
			x=2;
		}

		if((G.P[x-1].ret_CD_1()!=5))
		{
			G.P[x-1].modify_CD_1(); //incrementing cooldown when turn changes
		}

		if((G.P[x-1].ret_CD_2()!=3))
		{
			G.P[x-1].modify_CD_2(); //incrementing cooldown when turn changes
		}

	}while(!((G.P[0].ret_H()==0)||(G.P[1].ret_H()==0)));

	if(G.P[0].ret_H()==0)
		return 1; // indicates player 1 hero has fainted

	else
		return 0; // indicates player 2 hero has fainted
}

void sub_combat(int a, int p) //a=attack type, p=player number
{
	int cdmg;
	int id[2];

	for(int i=0; i<2; i++)
	{
		id[i]=G.P[i].ret_P_id();
	}

	if(a==1) //Comparing for attack type
	{
		cout << endl << G.P[p-1].Hero_Name << "(" << id[p-1] << ") used " << PA;
		getch();
		cdmg = G.P[(p%2)].modify_H(a); //p%2 because the attacker affects other player

		if(!(G.P[(p%2)].ret_H()==0))
			cout << endl << endl << "Health of " << G.P[(p%2)].Hero_Name << "(" << id[(p%2)] << ") = " << G.P[(p%2)].ret_H() << endl;

		else
			cout << endl << "Health of " << G.P[(p%2)].Hero_Name << "(" << id[(p%2)] << ") = 0" << endl;
		cout << "Health of " << G.P[p-1].Hero_Name << "(" << id[(p-1)] << ") = " << G.P[(p-1)].ret_H();
		getch();
	}

	else if (a==2)
	{
		cout << endl << G.P[p-1].Hero_Name << "(" << id[(p-1)] << ") used " << SA1;

		getch();

		cdmg = G.P[(p%2)].modify_H(a);
		cout<< endl << SA1 <<" damage: " << cdmg << " hitpoints" << endl;
		getch();

		if(!(G.P[(p%2)].ret_H()==0))
			cout << endl << "Health of " << G.P[(p%2)].Hero_Name << "(" << id[(p%2)] << ") = " << G.P[(p%2)].ret_H()<<endl;

		else
			cout << endl << "Health of " << G.P[(p%2)].Hero_Name << "(" << id[(p%2)] << ") = 0" << endl;
		cout << "Health of "<< G.P[p-1].Hero_Name << "(" << id[(p-1)] << ") = " << G.P[(p-1)].ret_H();

		getch();
	}
	else if(a==3)
	{
		cout << endl << G.P[p-1].Hero_Name << "(" << id[(p-1)] << ") used " << SA2;

		getch();

		cdmg = G.P[(p%2)].modify_H(a);
		cout<< endl << SA2 << " damage: " << cdmg << " hitpoints" << endl;

		getch();

		if(!(G.P[(p%2)].ret_H()==0))
			cout << endl << "Health of " << G.P[(p%2)].Hero_Name << "(" << id[(p%2)] << ") = " << G.P[(p%2)].ret_H() <<endl;

		else
			cout << endl << "Health of " << G.P[(p%2)].Hero_Name << "(" << id[(p%2)] << ") = 0" << endl;
		cout << "Health of " << G.P[p-1].Hero_Name << "(" << id[(p-1)] << ") = " << G.P[(p-1)].ret_H();

		getch();
	}
	else
	{
		cout << endl << G.P[p-1].Name << "(" << id[(p-1)] << ") used Potion!" << endl;
		getch();
		cdmg=G.P[p-1].modify_H(a);
		cout << G.P[p-1].Hero_Name << "(" << id[(p-1)] << ") revived by " << cdmg << " points" << endl;
		getch();
		cout << endl << "Health of "<< G.P[p-1].Hero_Name << "(" << id[(p-1)] << ") = " << G.P[p-1].ret_H() << endl;
	}
}

void View_Matches()
{
	Game g;
	int size;

	ifstream fin;
	fin.open("MatchData.dat",ios::binary);
	fin.seekg(0,ios::end);
	size=fin.tellg();

	if(size!=-1)
	{
		fin.seekg(0,ios::beg);

		while(fin.read((char*)&g,sizeof(Game)))
		{
			cout << endl;
			g.putdat();
		}

	}

	else
	{
		cout << "No records exist!";
	}

	fin.close();

	getch();
}
void View_WIN()
{
	int size;
	Player p;

	ifstream fin;
	fin.open("Win_Data.dat",ios::binary);
	fin.seekg(0,ios::end);
	size=fin.tellg();

	if(size!=-1)
	{
		fin.seekg(0,ios::beg);

		cout << endl << setw(20) << "NAME" << setw(20) << "HERO NAME" << setw(20) << "PLAYER ID" << endl;

		while(fin.read((char*)&p,sizeof(Player)))
		{
			p.put_lim_info();
		}
		cout << endl;
	}

	else
	{
		cout << "No records exist!";
	}

	fin.close();

	getch();
}

void Del_REC()
{
	int n;
	int status=0;

	cout << "Enter MatchID to delete Match Records: ";
	cin >> n;

	Del_W_REC(n);

	Game g;
	ofstream fo;
	ifstream fin;

	fo.open("tempdat.dat",ios::out|ios::binary);
	fin.open("MatchData.dat",ios::in|ios::binary);

	fin.clear();
	fin.seekg(0,ios::beg);
	while(fin.read((char*)&g,sizeof(Game)))
	{
		if(g.ret_M_ID()==n)
		{
			status=1;
			cout << "\nRecord deleted: \n";
			g.putdat();
		}
		else
		{
			fo.write((char*)&g,sizeof(Game));
		}
	}

	if(!status)
	{
		cout << "Record doesn't exists!";
	}

	fin.close();
	fo.close();

	remove("MatchData.dat");
	rename("tempdat.dat","MatchData.dat");

	getch();
}

void Del_W_REC(int n)
{
	Player p;
	Game g;
	int count=0;

	ifstream fin,if1;
	ofstream fo;

	fo.open("temp_dat.dat",ios::out|ios::binary);
	fin.open("Win_Data.dat",ios::in|ios::binary);
	if1.open("MatchData.dat",ios::in|ios::binary);

	if1.clear();
	if1.seekg(0,ios::beg);
	while(if1.read((char*)&g,sizeof(Game)))
	{
		if(g.ret_M_ID()==n)
			break;
		else
			count++;
	}

	fin.clear();
	fin.seekg(0,ios::beg);
	while(fin.read((char*)&p,sizeof(Player)))
	{
		if(fin.tellg()!=count*sizeof(Player))
		{
			fo.write((char*)&p,sizeof(Player));
		}
	}

	if1.close();
	fin.close();
	fo.close();

	remove("Win_Data.dat");
	rename("temp_dat.dat","Win_Data.dat");
}

void Modify_REC()
{
	CHAR temp;
	Game g;
	int status=0;

	cout << "Enter Player ID of player whose data you wish to modify: ";
	unsigned int m,i=0;
	cin >> m;

	cout << endl << "\nEnter new details:" << endl;

	fflush(stdin);

	cout << "New name: "; gets(temp);


	fstream f;
	f.open("MatchData.dat",ios::in|ios::out|ios::binary|ios::ate);
	f.seekg(0,ios::beg);
	while(f.read((char*)&g,sizeof(Game)))
	{
		if(m==g.P[0].ret_P_id())
		{
			status=1;
			if(i=0)
			{
				cout << "Record to be modified: \n";
				cout << endl << setw(20) << "NAME" << setw(20) << "PLAYER ID";
				cout << endl << setw(20) << g.P[0].Name << setw(20) << g.P[0].ret_P_id();
			}
			strcpy(g.P[0].Name,temp);
			Modify_W_REC(m,temp);

			f.seekp(-sizeof(Game),ios::cur);
			f.write((char*)&g,sizeof(Game));
			i++;

		}
		else if(m==g.P[1].ret_P_id())
		{
			status=1;
			if(i=0)
			{
				cout << "Record to be modified: \n";
				cout << endl << setw(20) << "NAME" << setw(20) << "PLAYER ID";
				cout << endl << setw(20) << g.P[0].Name << setw(20) << g.P[0].ret_P_id();
			}

			strcpy(g.P[1].Name,temp);
			Modify_W_REC(m,temp);

			f.seekp(-sizeof(Game),ios::cur);
			f.write((char*)&g,sizeof(Game));
			i++;
		}
	}

	if(!status)
	{
		cout << "No such record exists!" << endl;
	}

	else
	{
		cout << endl << "Done!" << endl;
	}

	f.close();

	getch();
}

void Modify_W_REC(int m, char temp[])
{
	Player p;

	fstream f;
	f.open("Win_Data.dat",ios::in|ios::out|ios::binary|ios::ate);
	f.seekg(0,ios::beg);

	while(f.read((char*)&p,sizeof(Player)))
	{
		if(p.ret_P_id()==m)
		{
			strcpy(p.Name,temp);
			f.seekp(-sizeof(Player),ios::cur);
			f.write((char*)&p,sizeof(Player));
		}
	}
	f.close();
}

void PlayerSearch()
{
	Game g;
	int id, pos=0, counter=0;
	int zero_one,status=0;

	cout << "Enter player ID: ";
	cin >> id;
	cout << endl << "Searching for player ..." << endl;

	ifstream file;
	file.open("MatchData.dat",ios::in|ios::binary);

	while(file.read((char*)&g,sizeof(Game)))
	{
		if(id==g.P[0].ret_P_id())
		{
			pos=file.tellg();
			status=1;
			zero_one=0;
			break;
		}
		else if(id==g.P[1].ret_P_id())
		{
			pos=file.tellg();
			status=1;
			zero_one=1;
			break;
		}
	}

	file.clear();
	file.seekg(0,ios::beg);

	if(!status)
	{
		cout << "Player not found!";
	}
	else
	{
		while(file.read((char*)&g,sizeof(Game)))
		{
			if(id==g.P[0].ret_P_id()||id==g.P[1].ret_P_id())
				counter++;
		}
		file.clear();
		file.seekg(pos-sizeof(g),ios::beg);
		file.read((char*)&g,sizeof(g));

		cout << "Player found!"<<endl;
		cout << setw(20) << "NAME" << setw(40) << "NO OF TIMES PLAYED" <<endl;
		cout << setw(20) << g.P[zero_one].Name << setw(40) << counter << endl;
	}

	file.close();

	getch();
}

int main()
{
	MENU();
}

