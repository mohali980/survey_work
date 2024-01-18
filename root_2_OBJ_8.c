
#include <iostream>
#include <iomanip>


int vcounter = 0; //this keeps track of the number of vertex points in the obj file

static TString ptColor = "red"; //collor of point
static float unitsConv = 0.10; //if a units conversion is needed, we can do it here (i.e. m to mm)
static float ptHW = 2.0*unitsConv; //this will make each plane have +/- ptHW in mm

void ptconv(vector<float> pts, TString name, ofstream *st)
{
	//each cross will have 12 points, so out vertex tracker will need to be incremented by 12 each time
	//give some information here:
	*st << "# " << name << "  (" << pts[0] << ", " << pts[1] << ", " << pts[2] << ")" << endl;
	//first we loop through the points
	*st << "g " << name << endl;
	*st << "v " << pts[0] << " " << pts[1] + ptHW << " " << pts[2] + ptHW << endl;
	*st << "v " << pts[0] << " " << pts[1] + ptHW << " " << pts[2] - ptHW << endl;
	*st << "v " << pts[0] << " " << pts[1] - ptHW << " " << pts[2] - ptHW << endl;
	*st << "v " << pts[0] << " " << pts[1] - ptHW << " " << pts[2] + ptHW << endl;
	*st << "f -4 -3 -2 -1" << endl;
	
	*st << "v " << pts[0] + ptHW << " " << pts[1] << " " << pts[2] + ptHW << endl;
	*st << "v " << pts[0] + ptHW << " " << pts[1] << " " << pts[2] - ptHW << endl;
	*st << "v " << pts[0] - ptHW << " " << pts[1] << " " << pts[2] - ptHW << endl;
	*st << "v " << pts[0] - ptHW << " " << pts[1] << " " << pts[2] + ptHW << endl;
	*st << "f -4 -3 -2 -1" << endl;
	
	*st << "v " << pts[0] + ptHW << " " << pts[1] + ptHW << " " << pts[2] << endl;
	*st << "v " << pts[0] + ptHW << " " << pts[1] - ptHW << " " << pts[2] << endl;
	*st << "v " << pts[0] - ptHW << " " << pts[1] - ptHW << " " << pts[2] << endl;
	*st << "v " << pts[0] - ptHW << " " << pts[1] + ptHW << " " << pts[2] << endl;
	*st << "f -4 -3 -2 -1" << endl;
	*st << endl;
}

void root_2_OBJ_8()

{
	
//1	................................................................

	float PI=4*atan(1);
	TString collection = "";
	TString rotTrans="";
	vector<float> vrt={};


	ifstream in_trees_file;
	string line;


//	define the input files... 
//	the first one is ole and its frame is the old/main PSI frame, there is no need to use it, it is not a direct MUSE survey.

	int nu_of_trees=0;
	in_trees_file.open("trees_file_9.txt");

	vector<TString> trees_names;

	while(getline(in_trees_file,line))
	{
		stringstream ss(line);
		string item;
		while (getline (ss,item)) {	trees_names.push_back (item);		}
	}

	cout<<"Number of the different coordinates : "<<trees_names.size()<<endl;

	TString working_file_name,working_frame,working_collection,working_group,working_point,working_date_time;
	float working_x,working_y,working_z,working_offp,working_offr;

//	................................................................

TFile file("points_9.root");


		TString dir="OBJ_files";
		gSystem->Exec("rm -rf "+dir);

	gSystem->Exec("rm -rf "+dir);
	gSystem->Exec("mkdir "+dir);

	TString meaning;
	

	for(int k=0;k<trees_names.size();k++)	//	(AAA)
	{
	int tt=0;
	basic_string<char> a = string (trees_names[k]);

	vrt.clear();

//	................................................................
//	inserting the transformation here (xyzXYZARBT), for each tree:

		if(k+1==1)		{	rotTrans="xzy"	;	vrt={-251.5,215.5,152.5};			tt=1;	meaning="";	}
		if(k+1==2)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),132.5,0};			tt=1;	meaning="target Local Center";	}
		if(k+1==3)		{	rotTrans="yz"	;	vrt={23,115.5};						tt=1;	meaning="target Local Center";	}
		if(k+1==4)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),132.5,0};			tt=1;	meaning="target Local Center";	}
		if(k+1==5)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),132.5,-0.65};		tt=1;	meaning="target Local Center";	}
		if(k+1==6)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),132.5,-0.65};		tt=1;	meaning="target Local Center";	}
		if(k+1==7)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),132.5,-0.65};		tt=1;	meaning="target Local Center";	}
		if(k+1==8)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),142.5,-0.65};		tt=1;	meaning="";	}
		if(k+1==9)		{	rotTrans="yz"	;	vrt={33,115.5};						tt=1;	meaning="";	}
		if(k+1==10)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),142.5,-0.65};		tt=1;	meaning="";	}
		if(k+1==11)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),142.5,0};			tt=1;	meaning="";	}
		if(k+1==12)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),142.5,-0.8};		tt=1;	meaning="";	}
		if(k+1==13)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),142.5,-0.8};		tt=1;	meaning="";	}
		if(k+1==14)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),141.5,-0.65};		tt=1;	meaning="target pre-measurement";	}
		if(k+1==15)		{	rotTrans="yzx"	;	vrt={33,115.5,-0.65};				tt=1;	meaning="target pre-measurement";	}
		if(k+1==16)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),141.5,-0.65};		tt=1;	meaning="target pre-measurement";	}
		if(k+1==17)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="";	}
		if(k+1==18)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="";	}
		if(k+1==19)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="";	}
		if(k+1==20)		{	rotTrans="Xxzy"	;	vrt={0*(PI/180),-252.5,198,152.5};	tt=1;	meaning="";	}
		if(k+1==21)		{	rotTrans="zy"	;	vrt={142.5,40};						tt=1;	meaning="";	}
		if(k+1==22)		{	rotTrans="zy"	;	vrt={142.5,39};						tt=1;	meaning="";	}
		if(k+1==23)		{	rotTrans="zy"	;	vrt={142.5,30};						tt=1;	meaning="";	}
		if(k+1==24)		{	rotTrans="Xz"	;	vrt={-90*(PI/180),9};				tt=1;	meaning="Rotary table yellow";	}
		if(k+1==25)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==26)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==27)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==28)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==29)		{	rotTrans="Xzxy"	;	vrt={90*(PI/180),142.5,-0.8,-0.75};	tt=1;	meaning="";	}
		if(k+1==30)		{	rotTrans="Xzxy"	;	vrt={90*(PI/180),185.5,-0.8,-0.75};	tt=1;	meaning="";	}
		if(k+1==31)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed >>>";	}
		if(k+1==32)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="Vacuum chamber Target PIM1, NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==33)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==34)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==35)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==36)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==37)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==38)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="G bottom surface measurement, NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==39)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="G bottom surface measurement, NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==40)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="G bottom surface measurement, NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==41)		{	rotTrans="Xzyx"	;	vrt={90*(PI/180),140,-0.5,-0.8};	tt=1;	meaning="Target Chamber";	}
		if(k+1==42)		{	rotTrans="Xzyx"	;	vrt={90*(PI/180),152.5,-0.5,-0.8};	tt=1;	meaning="Target Chamber";	}
		if(k+1==43)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="IN THE HALL FRAME, NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==44)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="IN THE HALL FRAME, NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==45)		{	rotTrans="Xz"	;	vrt={90*(PI/180),112};				tt=1;	meaning="IN THE HALL FRAME, NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==46)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==47)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==48)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==49)		{	rotTrans="Xz"	;	vrt={90*(PI/180),155.75};			tt=1;	meaning="";	}
		if(k+1==50)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==51)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),185.5,-0.5};		tt=1;	meaning="";	}
		if(k+1==52)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),185.5,-0.5};		tt=1;	meaning="";	}
		if(k+1==53)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==54)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),142,-0.8};			tt=1;	meaning="";	}
		if(k+1==55)		{	rotTrans="Xzxy"	;	vrt={90*(PI/180),143.5,-0.8,-0.7};	tt=1;	meaning="Flange E cylinder";	}
		if(k+1==56)		{	rotTrans="Xz"	;	vrt={90*(PI/180),112.5};			tt=1;	meaning="Yellow table";	}
		if(k+1==57)		{	rotTrans="Xzx"	;	vrt={90*(PI/180),141,-0.5};			tt=1;	meaning="";	}
		if(k+1==58)		{	rotTrans="Xz"	;	vrt={90*(PI/180),47.5};				tt=1;	meaning="Yellow table";	}
		if(k+1==59)		{	rotTrans="Xzy"	;	vrt={90*(PI/180),111.5,-0.5};		tt=1;	meaning="Yellow table";	}
		if(k+1==60)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, not clear shape";	}
		if(k+1==61)		{	rotTrans="Xxzy"	;	vrt={90*(PI/180),2.5,209.5,-5};		tt=1;	meaning="cylinder";	}
		if(k+1==62)		{	rotTrans="Xxzy"	;	vrt={90*(PI/180),-0.65,130.5,0};	tt=1;	meaning="Chamber cylinder";	}
		if(k+1==63)		{	rotTrans="Xxzy"	;	vrt={90*(PI/180),-0.65,120.5,0};	tt=1;	meaning="Chamber cylinder";	}
		if(k+1==64)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="small cylinder (can be in more than one place";	}
		if(k+1==65)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="small cylinder (can be in more than one place";	}
		if(k+1==66)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="small cylinder (can be in more than one place";	}
		if(k+1==67)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="mid size circle (can be in more than one place";	}
		if(k+1==68)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="mid size circle (can be in more than one place";	}
		if(k+1==69)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="mid size circle (can be in more than one place";	}
		if(k+1==70)		{	rotTrans="Xxzy"	;	vrt={90*(PI/180),-0.65,142.5,-0.65};tt=1;	meaning="Cylinder target installation without vacuum";	}
		if(k+1==71)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="small cylinder/circle (can be in more than one place";	}
		if(k+1==72)		{	rotTrans=""		;	vrt={};								tt=1;	meaning="small cylinder/circle (can be in more than one place";	}
		if(k+1==73)		{	rotTrans="Zyzx"	;	vrt={180*(PI/180),-31,115.5,-0.67};	tt=1;	meaning="Target mark (bellow square)";	}
		if(k+1==74)		{	rotTrans=""		;	vrt={	};							tt=1;	meaning="Target mark (bellow square) (rotated)	... NOT TRANSFORMED YET.";	}
		if(k+1==75)		{	rotTrans=""		;	vrt={	};							tt=1;	meaning="Target mark (bellow square) (rotated)	... NOT TRANSFORMED YET.";	}
		if(k+1==76)		{	rotTrans=""		;	vrt={	};							tt=1;	meaning="Target mark (bellow square) (rotated)	... NOT TRANSFORMED YET.";	}
		if(k+1==77)		{	rotTrans=""		;	vrt={	};							tt=1;	meaning="Target bottom surface, NOT TRANSFORMED YET.";	}
		if(k+1==78)		{	rotTrans="yzx"	;	vrt={33,115.6,-1.3};				tt=1;	meaning="Target mark (bellow square)";	}
		if(k+1==79)		{	rotTrans="YXzxy";	vrt={180*(PI/180),90*(PI/180),174.5,-4.5,4};			tt=1;	meaning="";	}
		if(k+1==80)		{	rotTrans="YXzxy";	vrt={90*(PI/180),90*(PI/180),131,4,3.5};			tt=1;	meaning="";	}
		if(k+1==81)		{	rotTrans="YXzxy";	vrt={180*(PI/180),90*(PI/180),174.5,-4.5,4};			tt=1;	meaning="";	}
		if(k+1==82)		{	rotTrans="YXzxy";	vrt={90*(PI/180),90*(PI/180),131,4,3.5};			tt=1;	meaning="";	}
		if(k+1==83)		{	rotTrans="Xz"	;	vrt={90*(PI/180),141};			tt=1;	meaning="";	}
		if(k+1==84)		{	rotTrans="Zyxz"	;	vrt={13*(PI/180),-272.5,119.5,146.5};	tt=1;	meaning="Target Flange (Chamber back)";	}
		if(k+1==85)		{	rotTrans=""		;	vrt={	};							tt=1;	meaning="Part of a big circle, NOT TRANSFORMED YET.";	}
		if(k+1==86)		{	rotTrans=""		;	vrt={	};							tt=1;	meaning="Part of a big circle, NOT TRANSFORMED YET.";	}
		if(k+1==87)		{	rotTrans="zxy"	;	vrt={221,-0.75,-0.75	};			tt=1;	meaning="flange";	}
		if(k+1==88)		{	rotTrans=""		;	vrt={	};							tt=1;	meaning="Part of a big circle, NOT TRANSFORMED YET.";	}
		if(k+1==89)		{	rotTrans="Xzxy"	;	vrt={90*(PI/180),142.5,-1,-0.5};	tt=1;	meaning="Target Flange (Chamber back)";	}
		if(k+1==90)		{	rotTrans="zxy"	;	vrt={221,-0.75,0	};				tt=1;	meaning="flange";	}
		if(k+1==91)		{	rotTrans="zxy"	;	vrt={235,-1,1	};					tt=1;	meaning="flange";	}
		if(k+1==92)		{	rotTrans="zxy"	;	vrt={234,-.60,0	};					tt=1;	meaning="flange";	}
		if(k+1==93)		{	rotTrans="zxy"	;	vrt={234,-0.6,-8.5	};				tt=1;	meaning="flange";	}
		if(k+1==94)		{	rotTrans="Xzxy"	;	vrt={90*(PI/180),142.5,-0.6,-0.5	};tt=1;	meaning="flange";	}
		if(k+1==95)		{	rotTrans="Xzxy"	;	vrt={90*(PI/180),187,-0.7,-0.5	};	tt=1;	meaning="flange";	}
		if(k+1==96)		{	rotTrans="Xzxy"	;	vrt={90*(PI/180),131,3,3.3	};		tt=1;	meaning="flange";	}
		if(k+1==97)		{	rotTrans="Xzxy"	;	vrt={90*(PI/180),173.5,3,4.2	};	tt=1;	meaning="flange";	}
		if(k+1==98)		{	rotTrans="Xzxy"	;	vrt={90*(PI/180),173.5,3,4.2	};	tt=1;	meaning="flange";	}
		if(k+1==116)	{	rotTrans="ZXzxy";	vrt={35*(PI/180),-90*(PI/180),277.5,-103,78.5};tt=1;	meaning="target/Ladder bottom surface";	}
		if(k+1==123)	{	rotTrans="Xzxy"	;	vrt={90*(PI/180),142,0,-0.6};		tt=1;	meaning="target/Ladder bottom surface";	}
		if(k+1==124)	{	rotTrans="Xzxy"	;	vrt={90*(PI/180),185,-0.5,0.5};		tt=1;	meaning="target/Ladder bottom surface";	}
		if(k+1==125)	{	rotTrans="ZXzxy";	vrt={35*(PI/180),90*(PI/180),-9.5,-103.5,-80.2};tt=1;	meaning="target/Ladder bottom surface";	}
		if(k+1==126)	{	rotTrans="ZXzxy";	vrt={35*(PI/180),90*(PI/180),-9.5,-104,-79.7};tt=1;	meaning="target/Ladder bottom surface";	}

		if(k+1==131)	{	rotTrans="Xzxy";	vrt={90*(PI/180),142.5,-0.6,-0.5};	tt=1;	meaning="target/Ladder bottom surface";	}
		
		if(k+1==132)	{	rotTrans="Xzx"	;	vrt={90*(PI/180),185,-0.65};				tt=1;	meaning="target/Ladder bottom surface";	}

		if(k+1==133)	{	rotTrans="Xzyx"	;	vrt={90*(PI/180),131,3.5,2.7};		tt=1;	meaning="target/Ladder bottom surface";	}
		
		if(k+1==134)	{	rotTrans="Xzyx"	;	vrt={90*(PI/180),174,4,3};			tt=1;	meaning="target/Ladder bottom surface";	}

		if(k+1==151)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET,Looks like the BH, THE CAD FILE needed.";	}

		if(k+1==163)	{	rotTrans="Xzxy"	;	vrt={90*(PI/180),142.7,-0.6,0	};	tt=1;	meaning="flange";	}
		if(k+1==166)	{	rotTrans="zxy"	;	vrt={154,169,47	};					tt=1;	meaning="flange";	}
	
		if(k+1==200)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==254)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, 0.25X0.5 m^2 plate, THE CAD FILE needed.";	}
		if(k+1==259)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, 1X1 m^2 platte , THE CAD FILE needed.";	}
		if(k+1==261)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==262)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, THE CAD FILE needed.";	}
		if(k+1==263)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (77 cm X 92 cm) panel (STT or SPS)... THE CAD FILE needed.";	}
		if(k+1==264)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (77 cm X 92 cm) panel (STT or SPS)... THE CAD FILE needed.";	}
		if(k+1==265)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (77 cm X 92 cm) panel (STT or SPS)... THE CAD FILE needed.";	}
		if(k+1==266)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (77 cm X 92 cm) panel (STT or SPS)... THE CAD FILE needed.";	}
		if(k+1==267)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (83 cm X 92 cm) panel (STT or SPS)... THE CAD FILE needed.";	}
		if(k+1==268)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (83 cm X 92 cm) panel (STT or SPS)... THE CAD FILE needed.";	}
		if(k+1==269)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (83 cm X 92 cm) panel (STT or SPS)... THE CAD FILE needed.";	}
		if(k+1==270)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (83 cm X 92 cm) panel (STT or SPS)... THE CAD FILE needed.";	}
		if(k+1==271)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (~60 cm) like a stand, THE CAD FILE needed >>>";	}
		if(k+1==272)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (102 cm X 120 cm) 4 corners-panel (STT or SPS)... THE CAD FILE needed.";	}
		if(k+1==273)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (10 cm X 80 cm) (Panel Small Left Dots)... THE CAD FILE needed";	}
		if(k+1==274)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (76 cm X 72 cm) (Panel small right)... THE CAD FILE needed";	}
		if(k+1==275)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET ~(8X9 cm) two parallel ~9 cm spacing, THE CAD FILE needed";	}
		if(k+1==276)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET ~(8X9 cm) two parallel ~9 cm spacing, THE CAD FILE needed";	}
		if(k+1==277)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET ~(20 cm) un-recognized shape, THE CAD FILE needed";	}
		if(k+1==278)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET ~(104 cm two sides fora ~ 200 cm door) (maybe SPS), THE CAD FILE needed";	}
		if(k+1==279)	{	rotTrans="XZzx"	;	vrt={90*(PI/180),-90*(PI/180),141,711};		tt=1;	meaning="points on the yellow sliding table";	}
		if(k+1==280)	{	rotTrans="Xyxz"	;	vrt={90*(PI/180),234,0.3,0.1};		tt=1;	meaning=" ~(41 cm X 61 cm) 4 corners BM panel";	}
		if(k+1==281)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, unrecognized shape in a plane, maybe THE CAD FILE needed";	}
		if(k+1==282)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET, unrecognized shape in a plane, maybe THE CAD FILE needed";	}
		if(k+1==283)	{	rotTrans="Xzx"	;	vrt={90*(PI/180),142.24,-0.636};	tt=1;	meaning="flange, chamber window";	}
		if(k+1==284)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET ~(98 cm row of points, they exist in the 285 tree), don't know for what, THE CAD FILE needed";	}
		if(k+1==285)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET ~(two parallel 98 cm row of points), look like a panel sides, THE CAD FILE needed";	}
		if(k+1==286)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET ~(two parallel 98 cm row of points, the same as 285), look like a panel sides, THE CAD FILE needed";	}
		if(k+1==287)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET ~(two parallel 98 cm row of points, the same as 285), look like a panel sides, THE CAD FILE needed";	}
		if(k+1==288)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (two rows of points 56 cm length, 92 cm apart) (like sides of a Panel)... THE CAD FILE needed";	}
		if(k+1==289)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (two rows of points 56 cm length, 92 cm apart) (like sides of a Panel, same as 288)... THE CAD FILE needed";	}
		if(k+1==290)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (two rows of points 56 cm length, 92 cm apart) (like sides of a Panel, same as 289)... THE CAD FILE needed";	}
		if(k+1==291)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (two rows of points 56 cm length, 92 cm apart) (like sides of a Panel, same as 290)... THE CAD FILE needed";	}
		if(k+1==292)	{	rotTrans="Xzxy"	;	vrt={90*(PI/180),155,-0.7,-0.6};	tt=1;	meaning=" around Chamber top flange";	}
		if(k+1==293)	{	rotTrans="Xzxy"	;	vrt={90*(PI/180),197.7,-0.7,0};		tt=1;	meaning=" around Chamber top flange";	}
		if(k+1==294)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (group of 8X8 cm non-recognized shape)... THE CAD FILE needed";	}
		if(k+1==295)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (group of 8X8 cm non-recognized shape) as 294... THE CAD FILE needed";	}
		if(k+1==296)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (group of 6 points non-recognized shape) ... THE CAD FILE needed";	}
		if(k+1==297)	{	rotTrans=""		;	vrt={};								tt=1;	meaning="NOT TRANSFORMED YET (group of 6 points non-recognized shape) as 296 ... THE CAD FILE needed";	}





	//	else			{				tt=0;		meaning="";}
//	................................................................

		TTreeReader reader(Form("%s",a.c_str()), &file);

		TTreeReaderValue<TString> in_file_name(reader, "file_name");
		TTreeReaderValue<TString> in_frame(reader, "frame");
		TTreeReaderValue<TString> in_collection(reader, "collection");
		TTreeReaderValue<TString> in_group(reader, "group");
		TTreeReaderValue<TString> in_point(reader, "point");

		TTreeReaderValue<float> in_x(reader, "x");
		TTreeReaderValue<float> in_y(reader, "y");
		TTreeReaderValue<float> in_z(reader, "z");
		TTreeReaderValue<float> in_offp(reader, "offp");
		TTreeReaderValue<float> in_offr(reader, "offr");

		TTreeReaderValue<TString> in_date_time(reader, "date_time");

		cout<< setw(4)<<k+1<<" ) "<< setw(45)<<a.c_str()<<" : ";


		

		TString ofstName =  (TString) a.c_str() + ".obj";

		ofstream ofst;
		ofst.open(dir+"/"+ofstName);


		int tree_size=0;

//	...............................................................................

					while (reader.Next()) 
					{
						tree_size++;

						working_file_name=*in_file_name;
						working_frame=*in_frame;
						working_collection=*in_collection;
						working_group=*in_group;
						working_point=*in_point;
						working_date_time=*in_date_time;
							
						working_x=*in_x;
						working_y=*in_y;
						working_z=*in_z;
						working_offp=*in_offp;
						working_offr=*in_offr;

						bool rt = false;
						
						if((int)vrt.size())
						{
							if((int)vrt.size() == rotTrans.Length())
							{
						//	cout << "doing a rotations/translation" << endl;
							rt = true;
							}
							else
							{
							cout << "string " << rotTrans << " needs to have the same number of characters as the size of the supplied vector: " << vrt.size() << endl;
							}
						}		

					TString name, collname;
					
					float pt1, pt2, pt3;
					name =	working_point;

					collname = working_collection;
					pt1 = unitsConv*working_x;
					pt2 = unitsConv*working_y;
					pt3 = unitsConv*working_z;
							
					if(rt)
					{
						TVector3 v(pt1, pt2, pt3);
						TVector3 varb;
						for(int i = 0; i < (int)vrt.size(); i++)
						{
							if(rotTrans[i] == 'x')	{	v[0] += vrt[i];		}
							if(rotTrans[i] == 'y')	{	v[1] += vrt[i];		}
							if(rotTrans[i] == 'z')	{	v[2] += vrt[i];		}
							if(rotTrans[i] == 'X')	{	v.RotateX(vrt[i]);	}
							if(rotTrans[i] == 'Y')	{	v.RotateY(vrt[i]);	}
							if(rotTrans[i] == 'Z')	{	v.RotateZ(vrt[i]);	}
							if(rotTrans[i] == 'A')	{	varb.SetX(vrt[i]);	}
							if(rotTrans[i] == 'R')	{	varb.SetY(vrt[i]);	}
							if(rotTrans[i] == 'B')	{	varb.SetZ(vrt[i]);	varb = varb.Unit();		}
							if(rotTrans[i] == 'T')	{	v.Rotate(vrt[i],varb);	}
						}
						pt1 = v[0];
						pt2 = v[1];
						pt3 = v[2];
					}
					vector<float> pts = {pt1, pt2, pt3};
					ptconv(pts, name, &ofst);
					}	//	while (reader.Next())

//	...............................................................................


	cout<<setw(5)<<tree_size;
	if(tt==1){cout<<setw(40)<<" pts, Doing Transformations... notes/means : "<<setw(35)<<meaning<<endl;}
	else{cout<<endl;}

	ofst.close();

	meaning="";
	}		//	for(int k=0;k<trees_names.size();k++)	(AAA)

}	//	main



	
