#include <iostream.h>
#include <fstream.h>
#include <conio.h>
#include <iomanip.h>
#include <apstring.h>
#include <apvector.h>
#include <apmatrix.h>
#include <stdlib.h>
int Lines;
int I;
apstring Trash;

apvector <apstring> Array(0);
ifstream in_file;
void main()
{ // This Part take numbers from a file.


	clrscr();
	in_file.open("a:\\prob#21.txt");
	in_file>>Lines;
	Array.resize(Lines);
	for(I=0;I<Lines;I++)
		in_file>>Array[I];
	for(I=0;I<Lines;I++)
		cout<<Array[I]<<endl;

	in_file.close();

	// This Part takes a number and then whole lines of text
	// One Line at a time

	clrscr();
	in_file.open("a:\\test.txt");
	in_file>>Lines;
	getline(in_file,Trash);
	Array.resize(Lines);
	for(I=0;I<Lines;I++)
	getline(in_file,Array[I]);

	//	in_file>>Array[I];
	for(I=0;I<Lines;I++)
		cout<<Array[I]<<endl;

	in_file.close();


	getch();

};