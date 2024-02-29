
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

void root_2_OBJ_test()

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
	in_trees_file.open("10_trees.txt");

	vector<TString> trees_names;

	while(getline(in_trees_file,line))
	{
		stringstream ss(line);
		string item;
		while (getline (ss,item)) {	trees_names.push_back (item);		}
	}

	cout<<"Number of the different coordinates : "<<trees_names.size()<<endl;

	TString working_file_name,working_frame,working_collection,working_group,working_point;
	int working_month,working_day,working_yr,working_hr,working_min,working_sec;
	float working_x,working_y,working_z,working_offp,working_offr;

//	................................................................

TFile file("10_points.root");


		TString dir="10_OBJ_filesssssss";
		gSystem->Exec("rm -rf "+dir);

	gSystem->Exec("rm -rf "+dir);
	gSystem->Exec("mkdir "+dir);

	TString meaning;


	int tt=0;
	basic_string<char> a = "dddddddddd";

	vrt.clear();



		

		TString ofstName =  (TString) a.c_str() + ".obj";

		ofstream ofst;
		ofst.open(dir+"/"+ofstName);


		int tree_size=0;
vector<float>ccc;
vector<vector<float>> AAA;
vector<TString> names;

names.pushback("GEMH0");
names.pushback("GEMV0");
names.pushback("Point0 ");
names.pushback("Point1 ");
names.pushback("Point2 ");
names.pushback("Point3 ");
names.pushback("Point4 ");
names.pushback("Point5 ");
names.pushback("Point6 ");
names.pushback("Point7 ");
names.pushback("GEMH1");
names.pushback("GEMV1");
names.pushback("Point8 ");
names.pushback("Point9 ");
names.pushback("Point10");
names.pushback("Point11");
names.pushback("Point12");
names.pushback("Point13");
names.pushback("Point14");
names.pushback("GEMH2");
names.pushback("GEMV2");
names.pushback("Point15");
names.pushback("Point16");
names.pushback("Point17");
names.pushback("Point18");
names.pushback("Point19");
names.pushback("GEMH3");
names.pushback("GEMV3");
names.pushback("Point20");
names.pushback("Point21");
names.pushback("Point22");
names.pushback("Point23");
names.pushback("Point24");
names.pushback("Point25");
names.pushback("Ref0 ");
names.pushback("Ref1 ");
names.pushback("Ref2 ");
names.pushback("Ref3 ");
names.pushback("Ref4 ");
names.pushback("Ref5 ");
names.pushback("Ref6 ");
names.pushback("transGEM0");
names.pushback("transGEM1");
names.pushback("transGEM2");
names.pushback("transGEM3");
names.pushback("rotGEM0 ");
names.pushback("rotGEM1  ");
names.pushback("rotGEM2  ");
names.pushback("rotGEM3  ");
names.pushback("transMUSEFrame");
names.pushback("rotMUSEFrame"); 






ccc.push_back(	-0.351 );ccc.push_back(68.931 );ccc.push_back(23.525	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-70.271);ccc.push_back(124.273);ccc.push_back(34.712 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	58.739 );ccc.push_back(186.564);ccc.push_back(33.824 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	59.194 );ccc.push_back(186.589);ccc.push_back(33.835  	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-58.280);ccc.push_back(187.022);ccc.push_back(33.922 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-55.753);ccc.push_back(186.909);ccc.push_back(34.013 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-63.084);ccc.push_back(64.064 );ccc.push_back(34.982  	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-62.966);ccc.push_back(63.811 );ccc.push_back(35.088  	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-63.203);ccc.push_back(179.810);ccc.push_back(33.989 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	62.532 );ccc.push_back(76.084 );ccc.push_back(35.029  	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-0.158 );ccc.push_back(195.053);ccc.push_back(94.724  	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-70.666);ccc.push_back(125.813);ccc.push_back(95.465 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-62.864);ccc.push_back(184.114);ccc.push_back(95.017 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-64.306);ccc.push_back(68.706 );ccc.push_back(95.053  	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	57.508 );ccc.push_back(187.140);ccc.push_back(95.419  	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	58.972 );ccc.push_back(187.118);ccc.push_back(95.540  	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	61.471 );ccc.push_back(75.891 );ccc.push_back(95.879  	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	61.959 );ccc.push_back(81.371 );ccc.push_back(96.112  	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-62.776);ccc.push_back(186.022);ccc.push_back(95.203 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-0.735 );ccc.push_back(194.205);ccc.push_back(158.431 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-70.572);ccc.push_back(124.524);ccc.push_back(161.563	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-63.125);ccc.push_back(182.762);ccc.push_back(159.378	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-59.809);ccc.push_back(186.936);ccc.push_back(158.843	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-63.872);ccc.push_back(66.628 );ccc.push_back(162.023 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	55.892 );ccc.push_back(187.034);ccc.push_back(156.831 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	62.694 );ccc.push_back(183.496);ccc.push_back(156.647 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-0.995 );ccc.push_back(194.487);ccc.push_back(220.796 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-70.906);ccc.push_back(124.498);ccc.push_back(220.649	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-59.947);ccc.push_back(187.495);ccc.push_back(219.924	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-64.666);ccc.push_back(66.595 );ccc.push_back(220.493 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	57.596 );ccc.push_back(187.578);ccc.push_back(220.344 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	55.426 );ccc.push_back(187.455);ccc.push_back(220.196 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	62.473 );ccc.push_back(79.701 );ccc.push_back(221.083 	); AAA.push_back(ccc);	ccc.clear();
ccc.push_back(	-61.314);ccc.push_back(187.328);ccc.push_back(220.253	); AAA.push_back(ccc);	ccc.clear();


ccc.push_back( -67.799);ccc.push_back( -118.135);ccc.push_back( -549.577);	AAA.push_back(ccc);	ccc.clear();
ccc.push_back( 66.797 );ccc.push_back(-118.245 );ccc.push_back(-549.763 );	AAA.push_back(ccc);	ccc.clear();
ccc.push_back( -0.991 );ccc.push_back(-118.195 );ccc.push_back(-505.228 );	AAA.push_back(ccc);	ccc.clear();
ccc.push_back( 64.298 );ccc.push_back(-118.107 );ccc.push_back(-448.707 );	AAA.push_back(ccc);	ccc.clear();
ccc.push_back( -65.149);ccc.push_back( -118.083);ccc.push_back( -439.135);	AAA.push_back(ccc);	ccc.clear();
ccc.push_back( 64.811 );ccc.push_back(-117.942 );ccc.push_back(-320.139 );	AAA.push_back(ccc);	ccc.clear();
ccc.push_back( -63.46 );ccc.push_back(-117.626 );ccc.push_back(-320.971 );	AAA.push_back(ccc);	ccc.clear();


ccc.push_back(	-1.52758);ccc.push_back(   8.41524);ccc.push_back( -285.52589); AAA.push_back(ccc); ccc.clear();
ccc.push_back(	-0.96654);ccc.push_back(   0.91200);ccc.push_back(  -1.09473 ); AAA.push_back(ccc); ccc.clear();
ccc.push_back(	-0.75371);ccc.push_back(   0.24629);ccc.push_back(   0.93714 ); AAA.push_back(ccc); ccc.clear();
ccc.push_back(	-1.15381);ccc.push_back(   0.30619);ccc.push_back(   0.05019 ); AAA.push_back(ccc); ccc.clear();
ccc.push_back(-96.37327 );ccc.push_back(-45.82106 );ccc.push_back(-320.47091 ); AAA.push_back(ccc); ccc.clear();
ccc.push_back(-0.20295  );ccc.push_back(-0.28750  );ccc.push_back(-0.51758 	) ; AAA.push_back(ccc); ccc.clear();
ccc.push_back(-1.28918  );ccc.push_back( 1.13342  );ccc.push_back(-0.04944	) ; AAA.push_back(ccc); ccc.clear();
ccc.push_back(-0.23977  );ccc.push_back(-0.19108  );ccc.push_back( 0.03099 	) ; AAA.push_back(ccc); ccc.clear();
ccc.push_back(1.84152  	);ccc.push_back(-0.16440  );ccc.push_back(-2.73585 	) ; AAA.push_back(ccc); ccc.clear();
ccc.push_back(	-0.10191);ccc.push_back(   0.21716);ccc.push_back(  -0.13129 ); AAA.push_back(ccc); ccc.clear();

//	...............................................................................

	

			for(int I=0;I<AAA.size();I++)
			{
		
						working_file_name=*names[I];
						working_frame=*names[I];
						working_collection=*names[I];
						working_group=*names[I];
						working_point=*names[I];
						working_month=1;
						working_day=1;
						working_yr=1;
						working_hr=1;
						working_min=1;
						working_sec=1;
							
						working_x=AAA[I][0];
						working_y=AAA[I][1];
						working_z=AAA[I][2];
						working_offp=.2;
						working_offr=.2;

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


			}	//	for(I)

//	...............................................................................


	cout<<setw(5)<<tree_size;
	if(tt==1){cout<<setw(40)<<" pts, Doing Transformations... notes/means : "<<setw(35)<<meaning<<endl;}
	else{cout<<endl;}

	ofst.close();

	meaning="";

}	//	main



	
