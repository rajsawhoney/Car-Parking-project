#include "CarParkingControl.h"
#define parkingSize 10
int main()
{
      ParkingLotControl p[parkingSize];
      int carNo;
      int displayCount=0;
      int recentlydeleted;
      char option, option1;
	  bool isLoginned = false;
	  bool recentDeletion=false;
	  bool firstlog = true;          
      loginPanel2:
      while(1)
      {
        displayCount++;
        if(displayCount>8)
        {
            clrscr();
            displayCount=0;
       }
       LoginPanel();
	   if (firstlog)
	   {
			cout << "NOTE: Your default username: admin\npassword: 'password' \nPlease change it for more security reason..." << endl;
			cout << "________________________________________________________________________" << endl;
		}
		cin >> option1;
		switch (option1)
		{
		case '1':
		{
			enterAgain3:
			string userNm;
			string password;
			cout<<"\nPlease enter the usename==\t";
			cin>>userNm;
			cout << "\nPlease enter your login password==\t";
			getch();
			char ch1;
			ch1 = _getch();
			//while (ch1!=13) //Works on Windows
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
				goto DataBase2;
			}
			else
			{
				cout << "\n\tUsename or password not matched!!!!Please try again..." << endl;
				isLoginned = false;
				goto enterAgain3;
			}
			break;
		}
		case '2':
		{
			enterAgain4:
			string tempPass="", newPass="";
			cout << "\nSir Please enter your current password==\t";
			getch();  //pause the program for a while
			char ch2;
			ch2 = _getch();
			//while (ch2!=13) //Works on Windows
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
				//while (ch3!=13)  //Works on Windows
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
					goto enterAgain4;
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
DataBase2:
	while (isLoginned)
	{
	    displayCount++;
        if(displayCount>9)
        {
            clrscr();
            displayCount=0;
        }
	    carNo=ParkingLotControl::getTotalCar();
	    //cout<<"Total car in lot="<<carNo<<endl;
		menu();
		cin >> option;
		switch (option)
		{
		case '1':
		{
		    if(carNo==parkingSize)
		    {
		        cout<<"Sorry!! The parking lot is completely FULL...Plz Try after sometime\n";
		        break;
		    }
			string Id;
			bool ifexist=false;
			cout<<"Enter the carId:\t";
    		cin>>Id;
    		if(carNo>0)
    		{			
			for(int j=0;j<carNo;j++)
			{
			    if (p[j].getCarId()== Id)
			     {
		   	     ifexist=true;
			    	break;
			     }			    
			}
    		}
    		else
    		    goto enterData;
			
			if(ifexist)
			{
				cout<<"Car with the ID "<<Id<<" already exist in our DataBase!!!"<<endl;
				break;
			}
				else
				{
				enterData:
				if(recentDeletion)
				{
				    p[recentlydeleted].putcarId(Id);
			        p[recentlydeleted].entryStatus = true;
	    		    ++p[recentlydeleted]; //increases the car num by 1
			    	p[recentlydeleted].get_entry();	
				    carNo++;  //Increasing  the index for more car entry
				    recentDeletion=false;
				}
			else
			{
				p[carNo].putcarId(Id);
			    p[carNo].entryStatus = true;
	    		++p[carNo]; //increases the car num by 1
				p[carNo].get_entry();	
				carNo++;  //Increasing  the index for more car entry
				}
				}
			break;
		}
		case '2': //Car Id is matched and is ready to get departured
		{
			string id;
			int recordNo;
			int recordFound=0;
			cout << "Enter the CarId: ";
			cin >> id;
			for(int i=0;i<carNo;i++)
			{
			    if (p[i].getCarId()== id)
			    {
				    recordFound=1;
				    recordNo=i;
			        break;			        
			   }
			}
			if(recordFound==1)
			{		   				
				    p[recordNo].get_exit();
					p[recordNo].exitStatus = true;
			}
		   else
			  cout << "Sorry sir!!! There is no car with this ID in our Parking Lot!!!" << endl;
			 break;
		}
		case '3':  //Delete the particular car from the dataBase and display the charges for the departured one
 		{
			string id;
			int recordNo;
			int recordFound=0;
			cout << "Enter the CarId: ";
			cin >> id;
			for(int i=0;i<carNo;i++)
			{
			    if (p[i].getCarId()== id)
			    {
				    recordFound=1;
				    recordNo=i;
			        break;			        
			    }
			}			
			if(recordFound==1 && p[recordNo].exitStatus==true)
			{
			    p[recordNo].showCharge();
			    --p[recordNo];	//decreases the car num by 1
			    for(int i=0;i<carNo;i++)
			    {
			        if(i==recordNo)
			        {
			            p[recordNo].removeCar();
			            recentlydeleted=recordNo;
			            recentDeletion=true;
			        }
			       /*
			         if(i==recordNo)
			        {
			            for(int j=i;j<carNo-1;j++)			            
			                p[j]=p[j+1];  //stores all other car except that one 
			            break;    
			        }
			        */
			    }
			}
			else if(recordFound==1 && p[recordNo].exitStatus==false)
			    cout<<"This car with id "<<id<<" is still to take exit..."<<endl;
			    
			    else if(recordFound==0)
			        cout<<"Car with Id "<<id<<" is not found in our DataBase!!"<<endl;
			break;
	 	}
		case '4':
		 {
				cout << "\n\t=== View the Records in the Parking Database ===";
				cout << "\n";
				int i=0;  //since used outside the for loop
				for(i=0;i<parkingSize;i++)
				{
				    if(p[i].isLotEmpty)
				        cout<<"\n\t  The Lot no. "<<i+1<<" is empty!!!"<<endl;
				   else if(!p[i].isLotEmpty)
				   {
				   cout << "\n\tThe Car position in the Parking Lot : " << i+1 << endl;
   				p[i].showTotalCarParked();				   
				   }
		    	}
		    					
				if(i==0)
				    cout<<"\n\tNo any records found in our DataBase "<<endl;
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
				goto loginPanel2;
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