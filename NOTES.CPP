// Program:Examples for Student Notes
// By: Bryan J. Baker


#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
//#include <apmatrix.h>
//#include <apvector.h>
#include <apstring.h>
#include <bool.h>
#include <math.h>

//Const Section

//Var Section
	int I,J, Choice;
	apstring Name, Trash;
	char Ans;


void main()
{
/* This program gives examples for a wide range of commands that a student
	 should know how to do. These are classic examples but should not be taken
	 as the only why to use them.
*/
	do{
			clrscr(); // clears the screen

			do{clrscr();
				 cout<<"Please enter your name:";
				 getline(cin,Name);  // Collect an APString with spaces
				 if (Name.length()==0) // If command to check Name length
					{
						cout<<endl<<"You must enter a name.";
						cout<<" Please press return to continue.";
						getch();
					}

				}while(Name.length()==0); // Check to see if the user entered
																	// a name. If the name length is 0
																	// (then user just pressed return)
																	// it runs again.
			cout<<endl<<endl;	// Move the curser down two lines.
			cout<<"Thank you "<<Name<<" now please press return to continue.";
			getch(); // Wait for the user to press the return key
			clrscr();
			// Using two for loops display the Multiplication tables for 0 - 12
			cout<<setw(30)<<"Multiplication Table"; // use setw to position Title
			for( I=0; I<13; I++) // Values for top of table
			{ gotoxy(I*3+4,2); // use gotoxy to place I value across top
				cout<<I;
				gotoxy(1,I*2+4); // use gotoxy to place I value down left side
				cout<<I;
				for(J=0; J<13; J++) // Values for left side of table
				{	gotoxy(I*3+4,J*2+4); // use gotoxy to position value
						cout<<I*J; // value to be seen
				}
			}
			cout<<endl<<endl;
			cout<<"Please press return to continue.";
			getch();
			do{
					clrscr();
					cout<<Name<<" Please pick from the follow items:"<<endl<<endl;
					cout<<"1. See your name backwards."<<endl;
					cout<<"2. See it run down the left side of the screen."<<endl;
					cout<<"3. See it diagonal."<<endl;
					cout<<"Choice:";
					cin>>Choice;
				}while(Choice<1 || Choice>3); // User proof
				cout<<endl<<endl;
			 switch(Choice) // Switch case because we have a menu and 4 choices
			 {
				case 1 : // Case to put the user's name backward on the screen
								 // The idea is to use the apstring like an apvector
								 for(I=Name.length()-1; I>=0; I--) // Count backward
									 cout<<Name[I]; // use apsrting like a 1D array.
								 cout<<endl<<endl;
								 break;

				case 2 : // Case to put the user's name down the side of the screen
								 // With only one char on a line.

								 for(I=0; I< Name.length(); I++) // Count forward Name length
									{ gotoxy(1,8+I); // Possition the Ith Letter of the name
										cout<<Name[I]; // cout the Ith element of the name
									}
								 break;

				case 3 : // Display the name diagonaly down the screen

								for(I=0; I< Name.length(); I++)
									{ gotoxy(10+I,8+I);
										cout<<Name[I];
									}
								 break;

				case 4: // Here is where you could write the code
								// to display the name backward and diagonaly.

								break;
			 }
			 cout<<endl<<endl;	// Move the curser down two lines.
			cout<<"Would you like to see the program again (Y/N)?";
			cin>>Ans;// collects the users answer
			getline(cin,Trash); // Clears the buffer after the cin above
													// The program only needs this if we use
													// a getline somewhere above abfore we use
													// cin again.

		}while(Ans=='Y'||Ans=='y'); // Checks for Y/y only any other answer
																//and the loop stops


}