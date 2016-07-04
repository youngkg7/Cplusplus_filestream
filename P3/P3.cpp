		  //Filename:P3.cpp
          //Programmer: Young Kwon			                                             CSCI 123 Fall '14
          //Due Date: 10/30/2014                                                         Instructor:  Timothy Mai
          //Program Description: Project 3, File reading and writing

#include <iostream>
#include <string>
#include <cstring> 
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;

void Getlist(ifstream& inCompanies, string company[50], string symbol[50], double price[50]);
void Getbalance(ifstream& inAccount, string account[20], double cash[20]);
void buy(ifstream& inCompanies, ifstream& inAccount, ofstream& outTrans, string company[], string symbol[], double price[], string account[], double cash[]);
void sell(ifstream& inCompanies, ifstream& inAccount, ofstream& outTrans, string company[], string symbol[], double price[], string account[], double cash[]);
string getCurrenttime();

int index; //global variable

void main()
{
	 string company[50], symbol[50], account[20];
	 double price[50], cash[20];
	 char menu1, redo;
	 ifstream inCompanies, inAccount; 
	 ofstream outTrans;

	 		 cout.setf(ios::fixed);
			 cout.setf(ios::showpoint);
			 cout.precision(2);

		 inCompanies.open ("Companies.txt");

		 // START OF inCompanies
		 if (inCompanies.fail()) 

		 {

			 cout << "Input file opening failed.\n";

			 exit(1);

		 }

		 for (int i=0; i<8; i++)
			 inCompanies >> company[i] >> symbol[i] >> price[i];
		 // END OF inCompanies

		 // START Of inAccount
		 inAccount.open("Account.txt");
		 
		 if (inAccount.fail()) 
		 {
			 cout << "Input file opening failed.\n";
			 exit(1);
		 }

		 for (int i=0; i < 5; i++)
			 inAccount >> account[i] >> cash[i];
		 // END OF inAccount

		 outTrans.open("Transactions.txt", ios::app);

			 if (outTrans.fail()) 
		 {
			 cout << "Output file opening failed.\n";   
			 exit(1);
		 }

	 do
	 {
		 cout << "Do you want to list, buy, sell stocks or check the cash available of an account?(l/b/s/c)" << endl;
		 cin >> menu1;

		 switch (menu1)
		 {
			 case 'l': Getlist(inCompanies, company, symbol, price);
				 break;
			 case 'c': Getbalance(inAccount, account, cash);
				 break;
			 case 'b': buy(inCompanies, inAccount, outTrans, company, symbol, price, account, cash);
				 break;
			 case 's': sell(inCompanies, inAccount, outTrans, company, symbol, price, account, cash);
				 break;
			 default: cout << "Invalid menu entry." << endl;
				 break;
		 }

		 cout << "Do you want to quit?(y/n)" << endl;
		 cin >> redo;

		 while (redo != 'y' && redo != 'n')
		 {
			 cout << "Invalid entry, please try again." << endl;
			 cout << "Do you want to quit?(y/n)" << endl;
			 cin >> redo;
		 }

		 if(redo == 'y')
			 cout << "Bye" << endl;

	 } while (redo == 'n');

	 inCompanies.close();
	 outTrans.close();
}

void Getlist(ifstream& inCompanies, string company[50], string symbol[50], double price[50])
{
	 for (int i=0; i < 7; i++)
	 {
		 inCompanies >> company[i] >> symbol[i] >> price[i];

		 if(i != 5)
			 cout << company[i] << "\t\t" << symbol[i] << "\t\t" << price[i] << endl;
		 else
			 cout << company[i] << "\t" << symbol[i] << "\t\t" << price[i] << endl;
	 }
}

 void Getbalance(ifstream& inAccount, string account[20], double cash[20])
{
	 char re_do;
	 bool acheck = false;
	 string accountid;

	 for (int i=0; i < 5; i++) 
		inAccount >> account[i] >> cash[i];

	 do
	 {
		 do
		 {
			 acheck = false;
			 cout << "Please enter the account ID that you would like to check." << endl;
			 cin >> accountid;
			 cout << endl;

			 for (int i = 0; i < 5; i++)
			 {
				 if (accountid == account[i])
				 {
					 cout << "$" << cash[i] << " is available";
					 cout << endl;
					 acheck = true;
				 }
			 }

			 if (acheck == false)
				 cout << "Invalid entry. Please try again." << endl;

		 } while (acheck == false);

		 cout << endl;
		 cout << "Would you like to check another account?(y/n)" << endl;
		 cin >> re_do;

		 while (re_do != 'y' && re_do != 'n')
		 {
			 cout << "Invalid entry, please try again." << endl;
			 cout << "Would you like to check another account?" << endl;
			 cin >> re_do;
		 }

	 } while (re_do == 'y');

}

	 string getCurrentTime ()
{
       time_t rawtime;
       struct tm * timeinfo; 
       time (&rawtime);
       timeinfo = localtime (&rawtime);
       char timeStr[100];
       char tempStr[100];  
       strcpy(tempStr, asctime(timeinfo));
       int len = strlen(tempStr);
       strncpy_s(timeStr, tempStr,  len - 1);
       return string (timeStr);
}

void buy(ifstream& inCompanies, ifstream& inAccount, ofstream& outTrans, string company[], string symbol[], double price[], string account[], double cash[])
{
	 cout.setf(ios::fixed);
	 cout.setf(ios::showpoint);
	 cout.precision(2);

	 double cashbal, total_cost, priceperstock;
	 int shares;
	 bool acheck;
	 string accountid, stock;
	 ofstream outAccount;

		 do
		 {
			 acheck = false;
			 cout << "Please enter your account ID" << endl;
			 cin >> accountid;
			 cout << endl;

			 for (int i = 0; i < 5; i++)
			 {
				 if (accountid == account[i])
				 {
					 accountid = account[i];
					 cashbal = cash[i];
					 index = i;
					 acheck = true;
				 }
			 }

			 if (acheck == false)
				 cout << "Invalid entry. Please try again." << endl;

		 } while (acheck == false);


		 do
		 {
			 do
			 {
				 acheck = false;
				 cout << "Please enter the company's stock symbol that you would like to purchase(CAPS)" << endl;
				 cin >> stock;
				 cout << endl;

				 cout << "Please enter the number of shares you would like to purchase." << endl;
				 cin >> shares;

				 while (shares < 1)
				 {
					 cout << "Invalid entry. Please try again." << endl;
					 cout << "Please enter the number of shares you would like to purchase." << endl;
					 cin >> shares;
				 }

				 for (int i = 0; i < 8; i++)  
				 {
					 if (stock == symbol[i])
					 {
						 total_cost = price[i] * shares;
						 priceperstock = price[i];
						 acheck = true;
					 }
				 }

				 if (acheck == false)
					 cout << "Invalid entry. Please enter the company symbol correctly." << endl;

			 } while (acheck == false);

			 if (cashbal < total_cost)
				 cout << "You do not have enough cash to purchase. Please try again." << endl;

		 } while (cashbal < total_cost);

		 outAccount.open("Account.txt");

		 if (outAccount.fail()) 
		 {
			 cout << "Output file opening failed.\n";   
			 exit(1);
		 }

			 outAccount.setf(ios::fixed);
			 outAccount.setf(ios::showpoint);
			 outAccount.precision(2);

	 if (cashbal > total_cost)
	 {
		 cash[index] = cashbal - total_cost;
		 cout << " Your new balance is: " << cash[index] << endl;

       for (int i = 0; i < 5; i++)
       {
		    string tab = "\t";

			 if (account[i].length() < 8 )
				 tab = "\t\t";
		
			 outAccount << account[i] << tab << cash[i] << endl;
       }
	 }

			 outTrans.setf(ios::fixed);
			 outTrans.setf(ios::showpoint);
			 outTrans.precision(2);

	 outTrans << getCurrentTime() << "\t" << accountid << "\t" << "buy" << "\t" << stock << "\t" << priceperstock << "\t" << shares << endl;

	 outAccount.close();
}




void sell(ifstream& inCompanies, ifstream& inAccount, ofstream& outTrans, string company[], string symbol[], double price[], string account[], double cash[])
{
	 string stock, accountid;
	 double cashbal, total_cost, priceperstock;
	 ofstream outAccount;
	 int shares;
	 bool acheck;

		 do
		 {
			 acheck = false;
			 cout << "Please enter your account ID" << endl;
			 cin >> accountid;
			 cout << endl;

			 for (int i = 0; i < 5; i++)
			 {
				 if (accountid == account[i])
				 {
					 accountid = account[i];
					 cashbal = cash[i];
					 index = i;
					 acheck = true;
				 }
			 }

			 if (acheck == false)
				 cout << "Invalid entry. Please try again." << endl;

		 } while (acheck == false);

	 for (int i=0; i<8; i++)
		 inCompanies >> company[i] >> symbol[i] >> price[i];

			 do
			 {
				 acheck = false;
				 cout << "Please enter the company's stock symbol that you would like to sell(CAPS)" << endl;
				 cin >> stock;

				 cout << endl;

				 cout << "Please enter the number of shares you would like to sell." << endl;
				 cin >> shares;

				 while (shares < 1)
				 {
					 cout << "Invalid entry. Please try again." << endl;
					 cout << "Please enter the number of shares you would like to sell." << endl;
					 cin >> shares;
				 }

				 for (int i = 0; i < 8; i++)  
				 {
					 if (stock == symbol[i])
					 {
						 total_cost = price[i] * shares;
						 priceperstock = price[i];
						 acheck = true;
					 }
				 }

				 if (acheck == false)
					 cout << "Invalid entry. Please enter the stock symbol correctly." << endl;

			 } while (acheck == false);

		 outAccount.open("Account.txt");

		 if (outAccount.fail()) 
		 {
			 cout << "Output file opening failed.\n";   
			 exit(1);
		 }

			 outAccount.setf(ios::fixed);
			 outAccount.setf(ios::showpoint);
			 outAccount.precision(2);

		 cash[index] = cashbal + total_cost;

		 cout << " Your new balance is: " << cash[index] << endl;

       for (int i = 0; i < 5; i++)
       {
		    string tab = "\t";

			 if (account[i].length() < 8 )
				 tab = "\t\t";

			 outAccount << account[i] << tab << cash[i] << endl;
       }

			 outTrans.setf(ios::fixed);
			 outTrans.setf(ios::showpoint);
			 outTrans.precision(2);

	 outTrans << getCurrentTime() << "\t" << accountid << "\t" << "sell" << "\t" << stock << "\t" << priceperstock << "\t" << shares << endl;

	 outAccount.close();
} 