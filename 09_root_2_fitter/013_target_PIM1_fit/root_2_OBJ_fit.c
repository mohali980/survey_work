
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



//	reading the measurements input file, which is the survied data file:

	ifstream in_file;
	vector<TString> Point_vec,Frame_vec;
	vector<float>	x_vec,y_vec,z_vec;
	string line,unit;

	TString tmp_frame,tmp_point;
	float tmp_x,tmp_y,tmp_z;

//	define the input files... 
//	the first one is ole and its frame is the old/main PSI frame, there is no need to use it, it is not a direct MUSE survey.

	vector<TString> files_vec{"measurements","aaa.measurements_in_global"};//,"fitted"};

	for(int j=0;j<files_vec.size();j++)
	{

	if(j==0)	{	in_file.open(files_vec[0]+".txt");	}
	if(j==1)	{	in_file.open(files_vec[1]);	}

	stringstream ss;


	if(in_file.is_open()) 
	{

		while(getline(in_file,line)) 
		{
			
			int flag=1;
			ss.clear();
			ss.str(line);

			if(TString(line).Contains("#") || line.empty())		{flag=0;}

			if(flag==1)
			
			{
				if(j==0)	{		ss>>tmp_frame>>tmp_point>>tmp_x>>tmp_y>>tmp_z>>unit;}
				if(j==1)	{		ss>>tmp_point>>tmp_x>>tmp_y>>tmp_z>>unit;}

			Frame_vec.push_back(tmp_frame);
			Point_vec.push_back(tmp_point);
			x_vec.push_back(tmp_x);
			y_vec.push_back(tmp_y);
			z_vec.push_back(tmp_z);
			}
		}
	}
	else
	{
		cout << "File doesn't exist! " << "\n";
		return;
	}


cout<<files_vec[j]<<endl;
for(int t=0;t<x_vec.size();t++)
{
	cout<< Point_vec[t]<<"	"<<x_vec[t]<<"	"<<y_vec[t]<<endl;
}
cout<<endl;


	TString working_frame,working_point;
	float working_x,working_y,working_z;

		

		TString ofstName =  files_vec[j]+".obj";

		ofstream ofst;
		ofst.open(ofstName);

//	...............................................................................

	for (int k=0;k<x_vec.size();k++) 
	{
					
		working_frame=Frame_vec[k];
		working_point=Point_vec[k];
		working_x=x_vec[k];
		working_y=y_vec[k];
		working_z=z_vec[k];
	
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

					collname = working_frame;
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
	}	//	for(k)
//	...............................................................................
		ofst.close();
		in_file.close();

			Frame_vec.clear();
			Point_vec.clear();
			x_vec.clear();
			y_vec.clear();
			z_vec.clear();


}	//	for(j)


}	//	main



	
