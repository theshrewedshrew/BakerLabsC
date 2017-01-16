

typedef struct Item_Rec
{	apstring	Name;
	double	Size;
	apstring	Power_Info;
	apstring	Item_Notes;
	apstring	Abrev;
};

typedef struct Box
{ apstring 	Item_Name;
	apstring  Abrev;
	bool	Active;
	int	Type;
	double	Power;
	double	Damage;
	double	Points;
};
struct Ship_Rec
{	apstring	Name;
	apstring	Type;
	apvector<Box> Space;
	int	Chassis_Weight;
	int	Max_Power;
	int Sinsors;
	int Size;
	double	Speed_Factor;
	double	Shield_Pts;
	double	Aromor_Pts;
};
apvector<Item_Rec> Items;

void init_items(apvector<Item_Rec> & );
int keypress();
void menu_movement(int X, int Y, int Min,int Max, int & Value);
apstring Name_Ship();

void init_items(apvector<Item_Rec> & Items)
{ Items.resize(13);

	Items[0].Name="Battery";
	Items[0].Size=1.0;
	Items[0].Power_Info="+2 units";
	Items[0].Item_Notes="Storage device: 2 power units copassity.";
	Items[0].Abrev="B";

	Items[1].Name="Heavy Battery";
	Items[1].Size=2;
	Items[1].Power_Info="+5 units";
	Items[1].Item_Notes="Storage device: 5 power units copassity.";
	Items[1].Abrev="HB";

	Items[2].Name="Shield Box";
	Items[2].Size=1;
	Items[2].Power_Info="-2 units";
	Items[2].Item_Notes="Box which when powered +1000 chassis pts.";
	Items[2].Abrev="SB";

	Items[3].Name="Heavy Shield Box";
	Items[3].Size=2;
	Items[3].Power_Info="-3 units";
	Items[3].Item_Notes="Box which when powered +2500 chassis pts.";
	Items[3].Abrev="HSB";

	Items[4].Name="Armor";
	Items[4].Size=1;
	Items[4].Power_Info="0 units";
	Items[4].Item_Notes="Box which +500 chassis pts.";
	Items[4].Abrev="A";

	Items[5].Name="Heavy Armor";
	Items[5].Size=2;
	Items[5].Power_Info="0 units";
	Items[5].Item_Notes="Box which +1250 chassis pts.";
	Items[5].Abrev="HA";

	Items[6].Name="Regular Sensor Package";
	Items[6].Size=1;
	Items[6].Power_Info="-1 unit ";
	Items[6].Item_Notes="When powered allows ship to ship tracking.";
	Items[6].Abrev="RSP";

	Items[7].Name="Advanced Sensor Package";
	Items[7].Size=1;
	Items[7].Power_Info="-2 units";
	Items[7].Item_Notes="Upgrade: allows +50% to tracking.";
	Items[7].Abrev="ASP";

	Items[8].Name="Repair Module";
	Items[8].Size=1;
	Items[8].Power_Info="-1 unit ";
	Items[8].Item_Notes="Repairs 1 Ship's box or 100 pts of Armor.";
	Items[8].Abrev="RM";

	Items[9].Name="Nano Repair Module";
	Items[9].Size=0.5;
	Items[9].Power_Info="-3 units";
	Items[9].Item_Notes="Repairs 2 Ship's boxs or 300 pts of Armor.";
	Items[9].Abrev="NRM";

	Items[10].Name="Engine Box";
	Items[10].Size=1;
	Items[10].Power_Info="+5 units";
	Items[10].Item_Notes="Generates 5 power points a turn.";
	Items[10].Abrev="EB";

	Items[11].Name="Heavy Engine Box";
	Items[11].Size=1.5;
	Items[11].Power_Info="+8 units";
	Items[11].Item_Notes="Generates 8 power points a turn.";
	Items[11].Abrev="HEB";

	Items[12].Name="Extra Heavy Engine Box";
	Items[12].Size=3;
	Items[12].Power_Info="+20 units";
	Items[12].Item_Notes="Generates 20 power points a turn.";
	Items[12].Abrev="EHEB";

};

int keypress()
{
 int Key;
 while(!kbhit());
 Key=getch();
 if(Key==0)
	Key=getch();
 return Key;
}

void menu_movement(int X, int Y, int Min,int Max, int & Value)
{
	int Key;
 do{
		 Key=keypress();
		 switch(Key)
		 {
			case 72: gotoxy(2,Y);
							 cout<<" ";
							 gotoxy(X,Y);
							 cout<<" ";
							 Y--;
							 if(Y<Min)
								Y=Max;
							 gotoxy(2,Y);
							 cout<<"<";
							 gotoxy(X,Y);
							 cout<<">";
							 gotoxy(2,Y);
							 break; // Go Up

			case 80: gotoxy(2,Y);
							 cout<<" ";
							 gotoxy(X,Y);
							 cout<<" ";
							 Y++;
							 if(Y>Max)
								Y=Min;
							 gotoxy(2,Y);
							 cout<<"<";
							 gotoxy(X,Y);
							 cout<<">";
							 gotoxy(2,Y);
							 break; // Go Down
			case 13: Value =Y-2;
		 }
		}while(Key!=13);
}

apstring Name_Ship()
{ apstring Temp;
	do	{
				gotoxy (10,10);
				cout<<"Please enter the Name of your Ship:";
				gotoxy (46,10);
				getline(cin,Temp);
			}	while (Temp =="");
	return Temp;
}
