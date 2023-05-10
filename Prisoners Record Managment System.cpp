#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct PrisonerBasics {
	string Citizenship;
	string name;
	int dateOfBirth;
	int id;
	string caseOfConvict;
	string typeOfAssault;
	bool haveFamily;
	int familySize;
	string dateOfArrest;
};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(short x, short y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//This function is for creating a cool efect with strings. it delays the desired string when it showes on the console window for example:
//If you pass S = "SUCCESSFULY REGISTERED!" to this function it will delay it when outputing just like this S U C C E S S F U L....like this
// it will create a time gap between every character in the string S.
void Delayer(string S) {
	for(int i = 0; i < S.size(); i++) {
		cout<<S[i];
		Sleep(65);
	}
	cout<<endl;
	SetConsoleTextAttribute(hConsole, 15);
}

// this function is for sorting a string number in array or vector. for example if your vector is like this Vector v = {"1","3","2","10","5"} it will
// sort it like this v = {"1","2","3","5","10"}
bool Comparator(string s1, string s2) {
	if(s1.size() == s2.size())
		return s1 < s2;
	else
		return s1.size() < s2.size();
}

//This are function prototypes
void accept(PrisonerBasics basics);
void showList(PrisonerBasics basics);
void search(PrisonerBasics basics);
void Update(PrisonerBasics basics);
void account_setting();
void Delete();
void Sort(string& UserName);
void Reset();
void admin();
int idGenerator();

int main() {
	//this found boolean variable will be true if the password and email that the user entered is found of the PASSWORD.dat binary file else it will be false
	bool found = false;
	//this blocked boolean variable will be true if the user attempts to login five times incorrectly
	bool blocked = false;
	//this two flags are usef if the password and the user name are found
	bool flag1 = false;
	bool flag2 = false;
	//this is attempt counter when the user enters a password if he enteres incorrect password it will decrease to 4 and again to 3.... and then when zero the blocked boolean variable will be true
	//and the acount will be closed forever only admin can access it
	int attemptCnter = 5;
	//this is just for accepting the password and the email from the user
	char password[26];
	string UserName;
	//this string variable will be passed to the Delay() function if the user inserts correct password and email
	string S = "Login Successful!";
	string email, line;
	int choice;



	do {
		ifstream pf("PASSWORD.dat");
		ifstream it("idTracker.txt");
		if(pf.fail() || it.fail()) {
			system("CLS");
			admin();
		} else {
			system("CLS");
			cout<<"Choose One To Procede"<<endl<<endl;
			cout<<"(1) For Admin Access"<<endl<<endl;
			cout<<"(2) For Employee Access"<<endl<<endl;
			cout<<"(3) Exit"<<endl<<endl;

			cout<<"Please Enter Your Choice: ";
			cin>>choice;
			if(choice == 1) {
				system("CLS");
				admin();
			} else if(choice == 2) {
				system("CLS");
				//if you see the below code in the rest of the program remember it is just used for changing the color of text that output to the console
				SetConsoleTextAttribute(hConsole, 15);
				ifstream blockedfile("Blocked.dat");
				//this code checkes if there is a file called blocked.dat in the computer and if it is found it will not procede to the rest program it will just show
				//acount is temporarily closed message!
				if(!blockedfile.fail()) {
					SetConsoleTextAttribute(hConsole, 12);
					cout <<"Account Temporarily Closed only Admin Can restore it :("<<endl;
					SetConsoleTextAttribute(hConsole, 15);
					return 0;
				}
				//this will be excuted when the user entered 5 incorrect passwords
				while(true) {
					if(attemptCnter == 0) {
						SetConsoleTextAttribute(hConsole, 12);
						cout <<"Account Temporarily Closed only Admin Can restore it :("<<endl;
						SetConsoleTextAttribute(hConsole, 15);
						remove("PASSWORD.dat");
						blocked = true;
						break;
					}
					//this is just simple output to the console window all are done with cout and the setconsoletext...code below is just like i told you is to change the color of
					//the text for in this case to chage the color of "Please Login To Continue" text to blue

					cout<<"      ************************************************************************************************"<<endl;
					cout<<"      #        Welcom To Our System Please Login In order To Procede to the Next Page                #"<<endl;
					cout<<"      #                                                                                              #"<<endl;
					cout<<"      #___________________________________";
					SetConsoleTextAttribute(hConsole, 3);
					cout<<"Please Login To Continue";
					SetConsoleTextAttribute(hConsole, 15);
					cout<<"___________________________________#"<<endl;
					cout<<endl;
					cout<< "          Please Enter the Email                                     Please Enter the Password\n"<<endl;
					cout<< "        ********************************                        ***********************************\n";
					cout<< "        #                              #                        #                                 #\n";
					cout<< "        ********************************                        ***********************************\n";
					gotoxy(11, 8);
					SetConsoleTextAttribute(hConsole, 11);
					cin >>email;
					gotoxy(67, 8);
					cin>>password;
					int j = 62;
					//the gotoxy functions are to change the location of the cursor in the console so that the user can input password and email in the desired location
					cout<<endl;
					cout<<endl;
					SetConsoleTextAttribute(hConsole, 15);
					//this will try to read PASSWORD.dat file that has been created by the program
					ifstream passfile("PASSWORD.dat");
					if(passfile.fail()) {
						SetConsoleTextAttribute(hConsole, 12);
						cout<<"file failed to open!"<<endl;
						SetConsoleTextAttribute(hConsole, 15);
						exit(1);
					}
					while(getline(passfile, line)) {
						if(line.find(password, 0) != string::npos) {
							flag1 = true;
						}
						if(line.find(email, 0) != string::npos) {
							flag2 = true;
						}
					}
					if(flag1 && flag2) {
						found = true;

					}
					passfile.close();
					//if the password and the email are correct by the above code then the program will procede to the below code which is if(found)
					if(found) {
						attemptCnter = 5;
						cout<<endl;
						cout<<"(+) Hello User Please Enter Your name for better interaction: ";
						cin.ignore();
						SetConsoleTextAttribute(hConsole, 11);
						getline(cin, UserName);
						SetConsoleTextAttribute(hConsole, 15);
						cout<<endl;

						SetConsoleTextAttribute(hConsole, 10);
						Delayer(S);

						system("pause");
						system("CLS");

						int choice;
						// this are variables that i created to by using the struct data type
						PrisonerBasics basics;

						//this program will excute as long as the user don't enter number 9
						//remember the do while loop is still inside the if(found) condition
						do {
							choice = 0;
							cout<<endl;
							cout<<"    ________________________________________________________________"<<endl;
							cout<<"    ******************PRISONER'S RECORED MANAGMENT *****************"<<endl;
							cout<<"    ________________________________________________________________"<<endl;
							cout<<"    ************************** OPTIONS *****************************"<<endl;
							cout<<"    #              1.Add New Prisoner Record.                      #"<<endl;
							cout<<"    #              2.Show Prisoner's Record.                       #"<<endl;
							cout<<"    #              3.Search a Prisoner's Record.                   #"<<endl;
							cout<<"    #              4.Update Prisoner's Record.                     #"<<endl;
							cout<<"    #              5.Delete a Prisoner's Record.                   #"<<endl;
							cout<<"    #              6.Sort The Prisoner's Record.                   #"<<endl;
							cout<<"    #              7.Reset the system.                             #"<<endl;
							cout<<"    #              8.Account Setting                               #"<<endl;
							cout<<"    #              9.Exit the Program.                             #"<<endl;
							cout<<"    ****************************************************************"<<endl<<endl;

							do {
								cout<<"    (-) Enter your Choice Please -> ";
								cin >> choice;
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							} while(cin.fail());

							if(choice == 1) {

								system ("CLS");
								accept(basics);
							} else if(choice == 2) {
								system("CLS");
								showList(basics);
							} else if(choice == 4) {
								system("CLS");
								Update(basics);
							} else if(choice == 3) {
								system("CLS");
								search(basics);
							} else if(choice == 5) {
								system("CLS");
								Delete();
							} else if(choice == 6) {
								system("CLS");
								Sort(UserName);
							} else if(choice == 7) {
								system("CLS");
								Reset();
							} else if(choice == 8) {
								system("CLS");
								account_setting();
							} else if(choice == 9) {
								system("CLS");
								cout<<"You Have Exited the Program!";
								return 0;
							} else {
								SetConsoleTextAttribute(hConsole, 12);
								cout<<"Error: Please Enter Your Choice Correctly! "<<endl;
								SetConsoleTextAttribute(hConsole, 15);
								system("pause");
								system("CLS");
							}

							cout<<endl;

						} while(true);

					}
					//this program will be excuted if the password that the user entered is incorrect
					//remember the Delayer function will only delay strings by creating time interval when outputing characters
					else {
						attemptCnter--;
						SetConsoleTextAttribute(hConsole, 12);
						string I = "Incorrect Password or Email Please Try Again!";
						Delayer(I);
						cout<<endl;
						SetConsoleTextAttribute(hConsole, 12);
						cout <<"Only "<< attemptCnter <<" Attempts left"<<endl<<endl;
						SetConsoleTextAttribute(hConsole, 15);
						system("pause");
						system("CLS");
					}

				}
				//this will excute if the user enterd 5 incorrect passwords
				// and if this file code is excuted the program will no longer work unless the admin restors it!!!
				if(blocked) {
					ofstream userBlocked("blocked.dat", ios::binary);
					userBlocked <<"Blocked";
				}

				return 0;
			} else if(choice == 3)
				break;
			else {
				cout<<"INVALID INPUT"<<endl<<endl;
			}
		}
		pf.close();
		it.close();
	} while(true);
}


void accept(PrisonerBasics basics) {
	string S = "SUCCESSFULLY REGISTERED!";
	// this boolean variable is used to check if the prisoner has a child or not in the below program
	//and i used it to manipulate the cursor position by GOTOXY function
	bool fChecker;
	int size;

	do {
		cout<<"Enter the number of Prisoners: ";
		cin>>size;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while(cin.fail());

	system("CLS");

	ofstream MyFile("prisonersRecord.txt", ios::app);
	if(MyFile.fail()) {
		SetConsoleTextAttribute(hConsole, 12);
		cout<<"file failed to open!"<<endl;
		SetConsoleTextAttribute(hConsole, 15);
		exit(1);
	}
	//this is just for accepting the prisoners data and the size is the number of prisoners that we want to register
	for(int i=0; i<size; i++) {

		fChecker = false;
		int x = 10;
		int y = 12;

		cout <<"Form Number "<<i+1<<endl;
		cout<<"---------------"<<endl;

		cout<<"(-) Enter the Prisoner's  Name: ";
		gotoxy(55,2);
		getline(cin,basics.name);
		cout<<endl;
		cout<<"(-) Enter the Prisoner's year of birth:";
		gotoxy(55,4);
		cin >>basics.dateOfBirth;
		cout<<endl;
		cout<<"(-) Enter the Citizenship of the prisoner's: ";
		gotoxy(55,6);
		cin.ignore();
		cin>>basics.Citizenship;
		cout<<endl;
		cout<<"(-) Does he have a family 1/0: ";
		gotoxy(55,8);
		cin>>basics.haveFamily;
		cout<<endl;
		if(basics.haveFamily) {
			cout<<"(-) How many children: ";
			gotoxy(55,10);
			cin>>basics.familySize;
			cout<<endl;
			fChecker = true;
		}

		if (fChecker) {
			x = 12;
			y = 14;
		}

		cout<<"(-) Case of Convict: ";
		gotoxy(55,x);
		cin.ignore();
		getline(cin,basics.caseOfConvict);
		cout<<endl;
		cout<<"(-) Enter Date of Arrest: DD/MM/YY: ";
		gotoxy(55,y);
		cin >>basics.dateOfArrest;
		cout<<endl;
		//when this idGenerator() function is called it will return number by increamenting 1 value to the previously recorded prisoner's id number
		basics.id = idGenerator();
		cout<<"(-) Prisoner Inmate:"<< basics.id<<endl<<endl;
		cout<<"(+) ";
		SetConsoleTextAttribute(hConsole, 10);
		Delayer(S);
		SetConsoleTextAttribute(hConsole, 15);

		cout<<"________________________________________"<<endl;
		//this will write the entered data to the prisonersRecord.txt file
		MyFile << basics.id<<"\n"<<basics.name<<"\n"<<basics.dateOfBirth<<"\n"<<basics.Citizenship<<"\n"<<basics.haveFamily<<"\n"<<basics.familySize<<"\n"<<basics.caseOfConvict<<"\n"<<
		       basics.dateOfArrest<<endl;

		system("pause");
		system("CLS");
	}

	MyFile.close();
}

int idGenerator() {
	string idsNo;
	string line;
	//string stream is used to change the string numbers to integer number for example "123" to 123
	stringstream ss;
	static int id;

	ofstream idfiletowrite("IdTracker.txt", ios::app);
	ifstream idFile("IdTracker.txt");
	if(idFile.fail() || idfiletowrite.fail()) {
		SetConsoleTextAttribute(hConsole, 12);
		cout<<"file failed to open!"<<endl;
		SetConsoleTextAttribute(hConsole, 15);
		exit(1);
	}
	//this will get the last Id on the IdTracker.txt file and then put it in the idsNO variable
	while(getline(idFile, line)) {
		idsNo = line;
	}

//this is for turning string number to integer number and then increament 1 to that id number then write it in the IdTracker.txt file
	ss << idsNo;
	ss >> id;
	id++;
	idfiletowrite <<"\n" << id;

	idfiletowrite.close();
	idFile.close();

	return id;
}

void showList(PrisonerBasics basics) {
	string myText;
	int counter = 0;

	ifstream MyReadFile("prisonersRecord.txt");

	cout<<"Prisoners Details"<<endl;
	cout<<"-----------------"<<endl;

//this program will read from the prisonersRecord.txt file and then print out only the name and the Id of the prisoner but not other informations
//it is done by ( when reading the file if it is the first and the seconde line (Id and name) it will print it out but if it is other line it will
//just ignore it and pass to the next line
	while (getline (MyReadFile, myText)) {
		if(counter==0) {
			cout<<"(-) Inmate: "<<myText<<" ------------------------";
		} else if(counter==1) {
			cout<<" Name: "<<myText<<endl;
		}
		if(counter==7) {
			counter=0;
			continue;
		}
		counter++;
	}

	MyReadFile.close();
	system("pause");
	system("CLS");
}

void search(PrisonerBasics basics) {
	string search;
	string line;
	string N = ". . . . . . . . .";
	bool flag = false;
	do {
		cout <<"Enter the Id to be searched: ";
		cin >> search;

		ifstream fileInput("prisonersRecord.txt");
		if(fileInput.fail()) {
			SetConsoleTextAttribute(hConsole, 50);
			cout<<"file failed to open!";
			SetConsoleTextAttribute(hConsole, 15);
			exit(1);
		}

		unsigned int curLine = 0;
		unsigned int counter = 0;

		while(getline(fileInput, line)) {
			curLine++;
			if (line.find(search, 0) != string::npos) {
				flag = true;

				cout<<"Searching ";
				Delayer(N);
				cout<<endl;
				SetConsoleTextAttribute(hConsole, 10);
				cout << "Prisoner Found!"<<endl;
				SetConsoleTextAttribute(hConsole, 15);

				while(counter != 8) {

					if(counter==0) {
						cout<<"(-) ID:              ---------------------------- "<<"INMATE: "<<line<<endl;
					} else if(counter==1) {
						cout<<"(-) Name:            ---------------------------- "<<line<<endl;
					} else if(counter == 2) {
						cout<<"(-) Birth Year:      ---------------------------- "<<line<<endl;
					} else if(counter == 3) {
						cout<<"(-) Citizenship:     ---------------------------- "<<line<<endl;
					} else if(counter == 4) {
						cout<<"(-) Family:          ---------------------------- "<<line<<endl;
					} else if(counter == 5) {
						cout<<"(-) Child No:        ---------------------------- "<<line<<endl;
					} else if(counter == 6) {
						cout<<"(-) Case of Convict: ---------------------------- "<<line<<endl;
					} else if(counter == 7) {
						cout<<"(-) Arrest Date:     ---------------------------- "<<line<<endl;
					}
					counter++;
					getline(fileInput, line);
				}
			}
		}
		//this will be true if the flag is false which means not found
		if(!flag) {
			cout<<"Searching ";
			Delayer(N);
			system("CLS");
			cout<<endl;
			SetConsoleTextAttribute(hConsole, 12);
			cout <<"Not Found!"<<endl;
			SetConsoleTextAttribute(hConsole, 15);
		}
		fileInput.close();
		system("pause");
		system("CLS");
	} while(!flag);

}

// the general idea how Update() function works
// the function will create a temporary text file called temp.txt and the until the id
// is found it will write all the information from the prisonersRecord.txt file to the temp.txt file
// and when the id number that the user is searching found it will jump 8 lines with while loop and
// askes the user to enter 8 informations. when the user inputs 8 things it then will write it to the
// temp.txt file and again it will continue to copy the remaining data from the prisonersRecord.txt to the temp.txt file
// when it is done it will remove the prisonersRecord.txt and then rename temp.txt file to prisoners.txt file
// SIMPLE right :)

void Update(PrisonerBasics basics) {
	string line;
	string tobeupdated;
	int counter = 0;
	int x = 8;
	int y = 10;
	bool fChecker = false;
	bool flag = false;
	string id;
	string S = "Successfully Updated!";

	do {
		ifstream myfile("prisonersRecord.txt");
		ofstream temp("temp.txt", ios::app);
		if(myfile.fail() || temp.fail()) {
			cout<<"file failed to open"<<endl;
			exit(1);
		}
		cout<<"Please Enter the ID to be Updated -> ";
		cin >> tobeupdated;
		system("CLS");

		while(getline(myfile, line)) {
			if(line.find(tobeupdated) != string::npos) {
				while(counter != 8) {
					getline(myfile, line);
					counter++;
					flag = true;
				}
				cout<<"(-) Enter the Prisoner's  Name: ";
				gotoxy(55,0);
				cin.ignore();
				getline(cin,basics.name);
				cout<<endl;
				cout<<"(-) Enter the Prisoner's year of birth:";
				gotoxy(55,2);
				cin >>basics.dateOfBirth;
				cout<<endl;
				cout<<"(-) Enter the Citizenship of the prisoner's: ";
				gotoxy(55,4);
				cin>>basics.Citizenship;
				cout<<endl;
				cout<<"(-) Does he have a family 1/0: ";
				gotoxy(55,6);
				cin>>basics.haveFamily;
				cout<<endl;
				if(basics.haveFamily) {
					cout<<"(-) How many children: ";
					gotoxy(55,8);
					cin>>basics.familySize;
					cout<<endl;
					fChecker = true;
				}

				if (fChecker) {
					x = 10;
					y = 12;
				}
				cout<<"(-) Case of Convict: ";
				gotoxy(55,x);
				cin.ignore();
				getline(cin,basics.caseOfConvict);
				cout<<endl;
				cout<<"(-) Enter Date of Arrest: DD/MM/YY: ";
				gotoxy(55,y);
				cin >>basics.dateOfArrest;
				cout<<endl;

				id = tobeupdated;
				cout<<"(-) Prisoner Inmate:"<<id;
				cout<<endl<<endl;

				cout<<"(+) ";

				SetConsoleTextAttribute(hConsole, 10);
				Delayer(S);
				SetConsoleTextAttribute(hConsole, 15);

				cout<<endl;

				temp<<id<<"\n"<<basics.name<<"\n"<<basics.dateOfBirth<<"\n"<<basics.Citizenship<<"\n"<<basics.haveFamily<<"\n"<<basics.familySize<<"\n"<<basics.caseOfConvict<<"\n"<<
				    basics.dateOfArrest<<endl;
			}
			else
			   	temp<<line<<"\n";
		}

		if(!flag) {
			SetConsoleTextAttribute(hConsole, 12);
			cout <<"Id Is Not Found In The Record!"<<endl;
			SetConsoleTextAttribute(hConsole, 15);
		}
		myfile.close();
		temp.close();
		system("pause");
		system("CLS");
	} while(!flag);
	remove("prisonersRecord.txt");
	rename("temp.txt","prisonersRecord.txt");
	system("pause");
	system("CLS");
}

//this delete function is the same as update but a little simpler
// first the function will create a temp.txt file and then copy every data from the prisonersRecord.txt
// untill it finds the tobedeleted id number. when it finds it it will jump 8 lines and again start writing it to the temp.txt file
// Done
void Delete() {
	int	counter = 0;
	int confirmation;
	string line;
	string tobedeleted;
	bool sure = false;
	bool flag = false;
	do {

		ofstream temp("temp.txt", ios::app);
		ifstream myfile("prisonersRecord.txt", ios::app);
		if(temp.fail() || myfile.fail()) {
			cout<<"file failed to open"<<endl;
			exit(1);
		}
		cout<<"Please Enter the Id to be Deleted -> ";
		cin>>tobedeleted;
		cout <<endl;

		while(getline(myfile, line)) {
			if(line.find(tobedeleted, 0) != string :: npos) {
				flag = true;
				do {
					cout <<"Press 1 for confirmation please -> ";
					cin >> confirmation;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while(cin.fail());

				cout<<endl;
				if(confirmation == 1) {
					while(counter != 8) {
						getline(myfile, line);
						counter++;
					}
				} else {
					sure = true;
					SetConsoleTextAttribute(hConsole,12);
					cout <<"Account is not Deleted!"<<endl<<endl;
					SetConsoleTextAttribute(hConsole,15);
				}

			}
			if(line.size() != 0)
				temp<<line<<"\n";
		}

		if(!flag) {
			SetConsoleTextAttribute(hConsole,12);
			cout <<"Account not found!"<<endl<<endl;
			SetConsoleTextAttribute(hConsole,15);
		}
		myfile.close();
		temp.close();
		system("pause");
		system("CLS");
	} while(!flag);
	remove("prisonersRecord.txt");
	rename("temp.txt","prisonersRecord.txt");

	if(!sure) {
		SetConsoleTextAttribute(hConsole, 10);
		cout << "Successfully Deleted"<<endl<<endl;
		SetConsoleTextAttribute(hConsole, 15);
	}

	system("pause");
	system("CLS");
}

//This account setting is simple try to understand it by just watching the cout things :)
// and if it is hard to understand i will tell you in person
void account_setting() {
	string line;
	string password;
	string newpass;

	while(true) {
		cout<<"************* Account Setting *************"<<endl;
		cout<<"-------------------------------------------"<<endl;

		cout<<"(1) Change The Password "<<endl;
		cout<<endl;
		cout<<"(2) About"<<endl;
		cout<<endl;
		cout<<"(3) BACK "<<endl;
		int choice;
		string about = "This Program Is Made to You by our team";
		cout<<endl;

		do {
			cout<<"Enter Your Choice Please -> ";
			cin >> choice;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while(cin.fail());

		bool flag = false;

		if(choice == 1) {
			ifstream pwordfile("PASSWORD.dat");
			if(pwordfile.fail()) {
				cout<<"file failed to open"<<endl;
				exit(1);
			}
			cout<<endl;
			cout<<"(-) Please Enter The Previous Password: ";
			cin>>password;
			cout<<endl;
			while(getline(pwordfile, line)) {
				if(line.find(password, 0) != string:: npos) {
					ofstream newpassword("PASSWORD.dat");

					SetConsoleTextAttribute(hConsole, 10);
					cout<<"CORRECT!"<<endl;
					cout<<endl;
					SetConsoleTextAttribute(hConsole, 15);

					cout<<"Please Enter the new password: ";

					cin>>newpass;
					flag = true;
					newpassword << newpass;
					cout<<endl;

					SetConsoleTextAttribute(hConsole, 10);
					cout<<"SUCCESFULLY CHANGED!"<<endl;
					SetConsoleTextAttribute(hConsole, 15);
				}
			}
			pwordfile.close();
			if(!flag) {
				SetConsoleTextAttribute(hConsole, 12);
				cout<<"Incorrect Password!"<<endl;
				SetConsoleTextAttribute(hConsole, 15);
			}

		} else if(choice == 2) {
			system("CLS");

			SetConsoleTextAttribute(hConsole, 3);
			Delayer(about);
			SetConsoleTextAttribute(hConsole, 3);

			cout<<endl;
			cout<<"Group Members-----------------------------------------------ID NUMBER-"<<endl;
			cout<<"(1) Baslael Workineh----------------------------------------UGR/0774/14"<<endl;
			SetConsoleTextAttribute(hConsole, 15);
		} else if(choice == 3) {
			system("CLS");
			break;
		} else {
			cout <<"Incorect Choice Please try again!"<<endl;
		}

		system("pause");
		system("CLS");
	}
}

// this Sort function is a little harder to make you understand by the comments only so here me out
// when we meet :)

void Sort(string& UserName) {
	vector <string> all;
	vector <string> names;
	vector <string> Id;
	string line;
	string temp;
	int answer;
	string S = "THE LIST IS SUCCESSFULLY SORTED!";

	do {
		cout<<"_________________________________________________________________________________________"<<endl;
		cout<<"Hello "<<UserName<<" Choose (1) for Sorting by Name || Choose (2) for Sorting by Id Order"<<endl;
		cout<<"-----------------------------------------------------------------------------------------"<<endl;
		cout<<"(1) Sort By Name Order!"<<endl;
		cout<<"(2) Sort By ID Order!"<<endl;
		cout<<"(3) Exit"<<endl<<endl;
		do {
			cout<<"Answer: ";
			cin>>answer;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while(cin.fail());

		if(answer == 1) {

			ifstream myfile("prisonersRecord.txt");
			if(myfile.fail()) {
				cout<<"file failed to open!"<<endl;
				exit(1);
			}
			while(getline(myfile, line)) {
				all.push_back(line);
			}

			for(int i =0; i < all.size(); i+=8) {
				names.push_back(all[i]);
				names.push_back(all[i+1]);
			}

			for(int i = 1; i < names.size(); i+=2) {
				for(int j = i; j < names.size(); j+=2) {
					if(names[i][0] > names[j][0]) {
						temp = names[i];
						names[i] = names[j];
						names[j] = temp;

						temp = names[i-1];
						names[i-1] = names[j-1];
						names[j-1] = temp;
					}

				}
			}

			int counter = 0;
			int i = 1;

			myfile.clear();
			myfile.seekg(0,myfile.beg);

			ofstream tempfile("temp.txt", ios::app);

			while(i < names.size()) {

				getline(myfile, line);

				if(line.find(names[i], 0) != string :: npos) {

					tempfile<<names[i-1]<<endl;
					while(counter != 7) {
						tempfile<<line<<endl;
						counter++;
						getline(myfile, line);
						cout<<".";
					}
					i+=2;

					counter = 0;
					myfile.clear();
					myfile.seekg(0,myfile.beg);
				}
			}

			cout<<endl;

			myfile.close();
			tempfile.close();

			remove("prisonersRecord.txt");
			rename("temp.txt","prisonersRecord.txt");

			SetConsoleTextAttribute(hConsole, 10);
			Delayer(S);
			SetConsoleTextAttribute(hConsole, 15);

			system("pause");
			system("CLS");
		}

		else if(answer == 2) {
			ifstream myfile("prisonersRecord.txt");
			if(myfile.fail()) {
				cout<<"file failed to open!"<<endl;
				exit(1);
			}
			while(getline(myfile, line)) {
				all.push_back(line);
			}

			for(int i =0; i < all.size(); i+=8) {
				Id.push_back(all[i]);
			}

			string tempV;
			stringstream ss;
			int num1;
			int num2;

			sort(Id.begin(),Id.end(),Comparator);

			myfile.clear();
			myfile.seekg(0,myfile.beg);

			ofstream tempfile("temp.txt", ios::app);

			int i = 0;
			int counter = 0;

			while(i < Id.size()) {
				getline(myfile, line);

				if(line.find(Id[i], 0) != string :: npos) {
					while(counter != 8) {
						tempfile<<line<<endl;
						counter++;
						getline(myfile, line);
						cout<<".";
					}
					i++;
					counter = 0;
					myfile.clear();
					myfile.seekg(0,myfile.beg);
				}
			}

			cout<<endl;

			myfile.close();
			tempfile.close();

			remove("prisonersRecord.txt");
			rename("temp.txt","prisonersRecord.txt");

			SetConsoleTextAttribute(hConsole, 10);
			Delayer(S);
			SetConsoleTextAttribute(hConsole, 15);

			system("pause");
			system("CLS");

		} else {
			cout<<endl<<endl;
			string N = "It seems You Don't want to Sort the list!";

			SetConsoleTextAttribute(hConsole, 12);
			Delayer(N);
			SetConsoleTextAttribute(hConsole, 15);

			cout<<endl;
			system("pause");
			system("CLS");
			return;
		}
	} while(answer != 3);
}

// when a user wants to reset all the program the code will come here just like the others
// and this function is just going to delete everything
// by everything I don't mean the code :)
// it is going to delete the "PASSWORD.dat" file the "prisonersRecord.txt" file and the "IdTracker.txt" file
// and after this function is called and run the program again it will show you "file failed to open" so only admin can restor it
void Reset() {
	string answer;
	cout<<"Do you Want to Reset the system: Yes/No: ";
	cin>>answer;

	if(answer == "Yes" || answer == "yes") {
		remove("prisonersRecord.txt");
		remove("PASSWORD.dat");
		remove("IdTracker.txt");
		SetConsoleTextAttribute(hConsole, 10);
		cout<<endl;
		cout<<"The System Successfully Reseted Now Only the Admin Can Restore it!"<<endl;
		cout<<endl;
		SetConsoleTextAttribute(hConsole, 15);
		system("pause");
		exit(1);

	} else if(answer == "No" || answer == "no") {
		SetConsoleTextAttribute(hConsole, 10);
		cout<<"System Not Erased!"<<endl;
		SetConsoleTextAttribute(hConsole, 15);
	} else {
		SetConsoleTextAttribute(hConsole, 12);
		cout<<"Invalid Input!"<<endl;
		SetConsoleTextAttribute(hConsole, 15);
	}

	system("pause");
	system("CLS");
}

void admin() {
	int choice;
	int Id;
	bool flag1 = false;
	bool flag2 = false;
	bool emailFlag = false;
	string password;
	string Email;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ifstream idfile("IdTracker.txt");
	ifstream passfile("PASSWORD.dat");

	do {
		cout<<"_______________________________This is Admins Page______________________________"<<endl;
		cout<<endl;
		cout<<"(1) Create Username and password for the system"<<endl<<endl;
		cout<<"(2) Instantiate The first ID number"<<endl<<endl;
		cout<<"(3) Exit the program"<<endl<<endl;

		cout<<"Please Enter Your Choice here -> ";
		cin >> choice;
		cout<<endl;

		if(choice == 1) {

			ofstream passfile("PASSWORD.dat", ios::binary);

			do {
				cout<<"(-) Please Enter the Email -> ";
				cin>>Email;
				for(int i = 0; i < Email.size(); i++) {
					if(Email[i] == '@') {
						emailFlag = true;
					}
				}
				if(!emailFlag) {
					cout<<endl;
					cout<<"Please Enter the Email in this format:";
					SetConsoleTextAttribute(hConsole, 3);
					cout<<" example@gmail.com "<<endl<<endl;
					SetConsoleTextAttribute(hConsole, 15);
				}

			} while(!emailFlag);
			emailFlag = false;
			cout<<endl;
			do {
				cout<<"(-) Please Enter the Password -> ";
				cin>>password;

				if(password.size() < 8) {
					cout<<endl;
					cout<<"Please Enter A ";
					SetConsoleTextAttribute(hConsole, 3);
					cout<<"Strong Password!"<<endl<<endl;
					SetConsoleTextAttribute(hConsole, 15);
				} else {
					emailFlag = true;
				}
			} while(!emailFlag);

			passfile<<password<<endl<<Email;
			passfile.close();
			cout<<endl;
			SetConsoleTextAttribute(hConsole, 10);
			cout<<"Password and Email Setup Completed!"<<endl<<endl;
			SetConsoleTextAttribute(hConsole, 15);
			flag1 = true;
			remove("Blocked.dat");
			system("pause");
			system("CLS");


		} else if(choice == 2) {
			//this must be modified

			if(idfile.fail()) {
				ofstream idfile("IdTracker.txt");

				cout<<"(-) Please Enter the ID number that the first Prisnor will get -> ";
				cin>>Id;
				idfile << Id;
				idfile.close();
				cout<<endl;
				SetConsoleTextAttribute(hConsole, 10);
				cout<<"Id Setup Completed!"<<endl<<endl;
				SetConsoleTextAttribute(hConsole, 15);
				system("pause");
				system("CLS");
				flag2 = true;
			} else {

				SetConsoleTextAttribute(hConsole, 3);
				cout<<"(-) You Already Have Instantiated the Id number! "<<endl<<endl;
				SetConsoleTextAttribute(hConsole, 15);
				flag2 = true;
				system("pause");
				system("CLS");
			}

		} else if((flag1 && flag2 && choice == 3) || (!idfile.fail() && !passfile.fail() && choice == 3)) {
			cout<<"You Have Exited the program"<<endl;
			return;
		} else {
			cout<<endl;
			SetConsoleTextAttribute(hConsole, 12);
			cout<<"Please Finish The Set Up first!"<<endl;
			SetConsoleTextAttribute(hConsole, 15);

			system("pause");
			system("CLS");
		}

	} while(true);

}
//Good Luck to Us