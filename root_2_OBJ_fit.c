
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

void root_2_OBJ_fit()

{
	
//	................................................................

	float PI=4*atan(1);
	TString collection = "";
	TString rotTrans="";
	vector<float> vrt={};

	int flag=1;

	ifstream in_pointdefs_file;
	string line;


//	define the input files... 
//	the first one is ole and its frame is the old/main PSI frame, there is no need to use it, it is not a direct MUSE survey.

	int nu_of_trees=0;
	in_pointdefs_file.open("10_trees.txt");

	vector<TString> items;

	while(getline(in_pointdefs_file,line))
	{
		stringstream ss(line);
		TString item;
		if(line.Contains("#")){flag=0;}
		while (getline (ss,item)) {	if(flag==1)	{	items.push_back (item);	}	}
	}







}	//	main

/*
	cout<<"Number of the different coordinates : "<<items.size()<<endl;

	TString working_file_name,working_frame,working_collection,working_group,working_point;
	int working_month,working_day,working_yr,working_hr,working_min,working_sec;
	float working_x,working_y,working_z,working_offp,working_offr;

//	................................................................

TFile file("10_points.root");


		TString dir="10_OBJ_files";
		gSystem->Exec("rm -rf "+dir);

	gSystem->Exec("rm -rf "+dir);
	gSystem->Exec("mkdir "+dir);

	TString meaning;
	

	for(int k=0;k<items.size();k++)	//	(AAA)
	{
	int tt=0;
	basic_string<char> a = string (items[k]);

	vrt.clear();


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

		TTreeReaderValue<int> in_month(reader, "month");
		TTreeReaderValue<int> in_day(reader, "day");
		TTreeReaderValue<int> in_yr(reader, "yr");
		TTreeReaderValue<int> in_hr(reader, "hr");
		TTreeReaderValue<int> in_min(reader, "min");
		TTreeReaderValue<int> in_sec(reader, "sec");

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
						working_month=*in_month;
						working_day=*in_day;
						working_yr=*in_yr;
						working_hr=*in_hr;
						working_min=*in_min;
						working_sec=*in_sec;
							
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


*/
	
