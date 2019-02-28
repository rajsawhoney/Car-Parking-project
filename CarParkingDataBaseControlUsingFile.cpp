//Progam 8. A parking garage charges a $2.00 minimum fee to park for up to three hours. The garage charges an additional $0.50 per hour for each hour or part thereof in excess of three hours. People who park their cars for longer than 24 hours will pay $8.00 per day. Write a program that calculates and prints the parking charges. The inputs to your program are the date and time when a car enters the parking garage, and the date and time when the same car leaves the parking garage. Keep track of number of cars in the garage overloading ++ and -- operators.

#include "CarParkingControl.h"  //user defined header which includes all the required methods and functionality

int main()
{   
	char option, option1;
	bool isLoginned = false;
	bool firstlog = true;
    loginPanel:
	while (1)
	{
		LoginPanel();
		if (firstlog)
		{
			cout << "NOTE: Your default username='admin' & password='password'. Please change it for more security reason..." << endl;
			cout << "________________________________________________________________________" << endl;
		}
		cin >> option1;
		switch (option1)
		{
		case '1':
		{
			enterAgain:
			string userNm,password;
			cout<<"\nPlease enter the usename==\t";
			cin>>userNm;
			cout << "\nPlease enter your login password==\t";
			getch();
			char ch1;
			ch1 = _getch();
			//while (ch1!=13) //Works on Windows where 13 is ASCII value  of Enter key
			while(ch1!='\n')
	 		{
			password+=ch1;
			cout << '*';
			ch1 = _getch();
			}
			if (checkLogin(userNm,password))
			{
				cout << "\n\tSuccessfully loginned.....\n\n" << endl;
				isLoginned = true;
				goto DataBase;
			}
			else
			{
				cout << "\n\tUsename or password not matched!!!!Please try again..." << endl;
				isLoginned = false;
				goto enterAgain;
			}
			break;
		}
		case '2':
		{
			enterAgain2:
			string tempPass="", newPass="";
			cout << "\nSir Please enter your current password==\t";
			getch();  //pause the program for a while
			char ch2;
			ch2 = _getch();
			//while (ch2!=13) //Works on Windows where 13 is ASCII value of Enter key
			while(ch2!='\n')
	 	  {
			tempPass+=ch2;
			cout << '*';
			ch2 = _getch();
			}
			if (DataBasePass==tempPass)
			{				
				cout << "\nEnter your new and a bit stronger password==\t" << endl;
				getch();
				char ch3;
				ch3 = _getch();
				//while (ch3!=13)  //Works on Windows where 13 is ASCII value for Enter key
				while(ch3!='\n')
	 		  {
				newPass+=ch3;
				cout << '*';
				ch3 = _getch();
				}
				changePass(newPass);
				char choice;
				string temUser;
				cout << "\n\t\tPassword successfully changed..." << endl;
				firstlog = false;
				cout<<"Do you wish to change the username as well????[Y/N]";
				cin>>choice;
				if(choice=='Y' || choice=='y')
				{
				    cout<<"Enter your new username...:\t";
				    cin>>temUser;
				    changeUsername(temUser);
				    cout<<"Username successfully changed..!!\n";
				}
			}
			else
				{
					cout << "\n\t\tWrong password!!!  Please Try again..." << endl;
					goto enterAgain2;
				}
			break;
		}
		case '3':
			char confirm1[2];
			cout << "Do you  really wanna exit (Y/N)?? ";
			cin >> confirm1;
			if (strcmp(confirm1, "Y") == 0 || strcmp(confirm1, "y") == 0)
			{
				cout << "Thanks for visiting us...\n";
				goto last;
			}
			else
				break;
		default:
			cout << "Invalid option selected...\n";
			break;
		}
	}
DataBase:
	while (isLoginned)
	{
		menu();
		cin >> option;
		switch (option)
		{
		case '1':
		{
			string Id;
			bool ifexist;
			cout<<"Enter the carId:\t";
			cin>>Id;
			fstream file;
			file.open(filename,ios::in|ios::out|ios::binary|ios::app);
			file.seekg(0,ios::beg);
			while (file.read((char *)&c, sizeof(c)))
			{
			if (c.getCarId()== Id)
			   {
			       ifexist=true;			         			    
			       break;
				}
				else
					ifexist=false;
			}
			if(ifexist)
			{
				cout<<"Car with the ID "<<Id<<" already exist in our DataBase!!!"<<endl;
				break;
			}
				else
				{
				c.putcarId(Id);
			    c.entryStatus = true;
	    		++c;
				c.get_entry();
				file.clear();
				file.seekp(0,ios::end);
				file.write((char *)&c, sizeof(c));
				cout << "Data is stored..." << endl;
				file.close();
				}
			break;
		}
		case '2':
		{
			string id;
			int recordFound=0;
			cout << "Enter the CarId: ";
			cin >> id;
			fstream file;
			file.open(filename, ios::in|ios::binary);
			file.clear();
			file.seekg(0,ios::beg);
			while (file.read((char *)&c, sizeof(c)))
			{
				if (c.getCarId()== id)
				{
					recordFound=1;
			    	break;			    	
			    }
			}
			file.close();
			if(recordFound==1)
			{
			    ofstream fout;
				fout.open("temp1.dat", ios::out | ios::binary);
				fout.seekp(0,ios::beg);
				ifstream infile(filename, ios::binary | ios::in);
				while (infile.read((char *)&c, sizeof(c)))
				{					
					if (c.getCarId()==id)
					{	
				    	c.get_exit();
		    			c.exitStatus = true;
					}
						fout.write((char *)&c, sizeof(c));
				 }
				
				infile.close();
				fout.close();
				remove(filename);
				rename("temp1.dat",filename);
				}
				else
				   cout << "Sorry sir!!! There is no car with this ID in our Parking Lot!!!" << endl;
			break;
		}
		case '3':
 		{
			delete_record();
			break;
	 	}
		case '4':
		 {
				cout << "\n\t=== View the Records in the Parking Database ===\n";
				ifstream infile(filename, ios::binary | ios::in);
				int d = 1;
				while (infile.read((char *)&c, sizeof(c)))
				{
					infile.clear();
					//system("pause");
					cout << "\n\tThe Car position in the Parking Lot : " << d << endl;
					d++;
					c.showTotalCarParked();
			}
				cout << "\n\tTotal no of cars in the lot: " <<d-1<< endl;
				if(d==1)
				    cout<<"\n\tNo any records found in our DataBase "<<endl;
				infile.close();
 			break;
		}

		case '5':
		{
			char confirm[1];
			cout << "Do you  really wanna sign out (Y/N)?? ";
			cin >> confirm;
			if (strcmp(confirm, "Y") == 0 || strcmp(confirm, "y") == 0)
			{
				cout << "Thanks for visiting us...\n";
				goto loginPanel;
			}
			else
				break;
		}
		default:
			cout << "Invalid option selected...\n";
			break;
		}
	}
	last:
	return 0;
}
