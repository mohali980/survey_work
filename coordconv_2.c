#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "TMathBase.h"
 
#include "TError.h"
#include <algorithm>
#include <limits>
#include <cmath>
 

//	...........................................................................

void coordconv_2()
	{

	float out_x, out_y, out_z, out_offp, out_offr;

	TString out_frame,out_collection, out_group, out_point,out_total_frame,out_txt_file;
	TString temp_tot_frame,temp_x,temp_y,temp_z,temp_offp,temp_offr;

	string in_file_name,in_frame,in_collection,in_group,in_point;
	string in_x,in_y,in_z,in_offp,in_offr;

	vector	<TString>	file_name_vec,frame_vec,collection_vec,group_vec,point_vec,tot_frame_vec;
//	vector	<float>		x_vec,y_vec,z_vec,offp_vec,offr_vec;
	vector	<TString>		x_vec,y_vec,z_vec,offp_vec,offr_vec;



//	START : .................	reading data from TXT files	...................



	ifstream in_file;
	in_file.open("2022_all_data.txt");


	TFile *out_file = new TFile("2022_frames_2.root", "RECREATE");

	float PI=4*atan(1);

	int lineno = 0;


	while(getline(in_file,in_file_name))
	{

		in_file>>in_file_name>>in_frame>>in_collection>>in_group>>in_point>>in_x>>in_y>>in_z>>in_offp>>in_offr;


		TString temp_file_name,temp_frame,temp_collection,temp_group,temp_point;


		temp_file_name	=	(TString)	in_file_name;
		temp_frame		=	(TString)	in_frame;
		temp_collection	=	(TString)	in_collection;
		temp_group		=	(TString)	in_group;
		temp_point		=	(TString)	in_point;
		temp_x			=	(TString)	in_x;
		temp_y			=	(TString)	in_y;
		temp_z			=	(TString)	in_z;
		temp_offp		=	(TString)	in_offp;
		temp_offr		=	(TString)	in_offr;

		temp_tot_frame=temp_file_name+"..."+temp_frame+"..."+temp_collection+"..."+temp_group;

	
/*
		out_x = atof(in_x.c_str());
		out_y = atof(in_y.c_str());
		out_z = atof(in_z.c_str());
		out_offp = atof(in_offp.c_str());
		out_offr = atof(in_offr.c_str());

*/


	file_name_vec.push_back(temp_file_name);
	frame_vec.push_back(temp_frame);
	collection_vec.push_back(temp_collection);
	group_vec.push_back(temp_group);
	point_vec.push_back(temp_point);
	tot_frame_vec.push_back(temp_tot_frame);


	x_vec.push_back(temp_x);
	y_vec.push_back(temp_y);
	z_vec.push_back(temp_z);
	offp_vec.push_back(temp_offp);
	offr_vec.push_back(temp_offr);

/*
	x_vec.push_back(out_x);
	y_vec.push_back(out_y);
	z_vec.push_back(out_z);
	offp_vec.push_back(out_offp);
	offr_vec.push_back(out_offr);
*/


	lineno++;
	}	//	while




//	END : .................	reading data from TXT files	...................










vector<int> B;
vector<TString> temp_tot_frame_vec,temp_point_vec,temp_x_vec,temp_y_vec,temp_z_vec,temp_offp_vec,temp_offr_vec;
vector<TString>	A,A_tot_frame,A_point;
vector<TString> A_x,A_y,A_z,A_offp,A_offr;

vector<vector<TString>> C_tot_frame,C_point;				//	the 2X2 vector which contains the total frames
vector<vector<TString>> C_x,C_y,C_z,C_offp,C_offr;	//	the 2X2 vectors which contain the coordinates...


A_tot_frame	=	tot_frame_vec;
A_point 	=	point_vec;
A_x			=	x_vec;
A_y			=	y_vec;
A_z			=	z_vec;
A_offp		=	offp_vec;
A_offr		=	offr_vec;



int j=1;



cout<<"Start : filling the 2X2 vectos for the tot_frame & the points & (x,y,z) coordinates and the {offp,offr} values."<<endl;

//	...........................................................................
//	Start : filling 2X2 vectos for the tot_frame & the points & (x,y,z) coordinates and the {offp,offr} values.

while (A_tot_frame.size()!=0)
{
	temp_tot_frame_vec.clear();
	temp_point_vec.clear();
	temp_x_vec.clear();
	temp_y_vec.clear();
	temp_z_vec.clear();
	temp_offp_vec.clear();
	temp_offr_vec.clear();

	temp_tot_frame_vec.push_back(A_tot_frame[0]);
	temp_point_vec.push_back(A_point[0]);
	temp_x_vec.push_back(A_x[0]);
	temp_y_vec.push_back(A_y[0]);
	temp_z_vec.push_back(A_z[0]);
	temp_offp_vec.push_back(A_offp[0]);
	temp_offr_vec.push_back(A_offr[0]);

	B.clear();
	B.push_back(0);

	for(int y=1;y<A_tot_frame.size();y++)	
		{	if (A_tot_frame[y]==temp_tot_frame_vec[0]) 
			{	
				temp_tot_frame_vec.push_back(A_tot_frame[0]);
				temp_point_vec.push_back(A_point[y]);
				temp_x_vec.push_back(A_x[y]);
				temp_y_vec.push_back(A_y[y]);
				temp_z_vec.push_back(A_z[y]);
				temp_offp_vec.push_back(A_offp[y]);
				temp_offr_vec.push_back(A_offr[y]);

				B.push_back(y);	}


			}

	for(int y=B.size()-1;y>-1;y--)	
		{
			A_tot_frame.erase(std::next(A_tot_frame.begin(),B[y]));	
			A_point.erase(std::next(A_point.begin(),B[y]));	
			A_x.erase(std::next(A_x.begin(),B[y]));	
			A_y.erase(std::next(A_y.begin(),B[y]));	
			A_z.erase(std::next(A_z.begin(),B[y]));	
			A_offp.erase(std::next(A_offp.begin(),B[y]));	
			A_offr.erase(std::next(A_offr.begin(),B[y]));	
		}

//	storing the data in 2X2 vectors (TSiring)

	C_tot_frame.push_back(temp_tot_frame_vec);
	C_point.push_back(temp_point_vec);
	C_x.push_back(temp_x_vec);
	C_y.push_back(temp_y_vec);
	C_z.push_back(temp_z_vec);
	C_offp.push_back(temp_offp_vec);
	C_offr.push_back(temp_offr_vec);


/*
//	JUST FOR TESTING:
	cout<<"--------------------------------------"<<endl;
	cout<<j<<"		C size : "<<C_tot_frame[j-1].size()<<"	...	"<<C_tot_frame[j-1][0]<<endl;
	for(int i=0;i<C_tot_frame[j-1].size();i++){cout<<C_point[j-1][i]<<"	";}
	cout<<endl<<"--------------------------------------"<<endl;
*/
	j++;
}	//	while(int j<size)

	cout<<"End : filling the 2X2 vectos for the tot_frame & the points & (x,y,z) coordinates and the {offp,offr} values."<<endl;

//	End : filling 2X2 vectos for the tot_frame & the points & (x,y,z) coordinates and the {offp,offr} values.
//	...........................................................................


	for(int i=0;i<C_tot_frame.size();i++)
	{



	}


	TString main_frame="20220810_WEHA_PIM1_Muse_Procedure...20220119_Kontrolle_Rahmen::PIM1...20220810...Aufmass_Ref_Targetkammer";
	
	vector<TString>	final_points;
	vector<float>	final_x,final_y,final_z,final_offp,final_offr;




//	start:	.................	finding the MUSE frame 	.......................

	int muse_frame_number;


	for (int i=0;i<C_tot_frame.size();i++)	
	{	for(int j=0;j<C_tot_frame[i].size();j++)
		{
			if(C_tot_frame[i][0]==main_frame){muse_frame_number=i;}
		}	//	for(j)
	}		//	for(i)

//	end :	.................	finding the MUSE frame 	.......................

	final_points	=	C_point[muse_frame_number];

	for(int i=0;i<C_point[muse_frame_number].size();i++)
	{
	final_x.push_back(atof(string (C_x[muse_frame_number][i]).c_str()));
	final_y.push_back(atof(string (C_y[muse_frame_number][i]).c_str()));
	final_z.push_back(atof(string (C_z[muse_frame_number][i]).c_str()));
	final_offp.push_back(atof(string (C_offp[muse_frame_number][i]).c_str()));
	final_offr.push_back(atof(string (C_offr[muse_frame_number][i]).c_str()));

	}


//	start:	.................	matching points with the MUSE-frame points	...


	for (int i=0;i<C_tot_frame.size();i++)						//	over all the frames
	{
		cout<<i<<"  :  ";
	
int counter=0;
	for(int j=0;j<C_tot_frame[i].size();j++)					//	over points in each frame
	{
	
	for (int k=0;k<C_point[muse_frame_number].size();k++)		//	over the MUSE frame points
	{
		
		float Ax,Ay,Az,Bx,By,Bz,Cx,Cy,Cz;
		float AAx,AAy,AAz,BBx,BBy,BBz,CCx,CCy,CCz;		//	the matching points between the 1st and the 2nd frames. (AA~A`,BB~B',CC~C')

		if(i != muse_frame_number && C_point[i][j]== C_point[muse_frame_number][k] && counter<4)
		{
			counter++;
			if(counter==1)	{	Ax=atof(string (C_x[muse_frame_number][k]).c_str());
								Ay=atof(string (C_y[muse_frame_number][k]).c_str());
								Az=atof(string (C_z[muse_frame_number][k]).c_str());
								AAx=atof(string (C_x[i][j]).c_str());
								AAy=atof(string (C_y[i][j]).c_str());	cout<<C_point[muse_frame_number][k]<<"	"<<C_point[i][j]<<endl;
								AAz=atof(string (C_z[i][j]).c_str());	}
			if(counter==2)	{	Bx=atof(string (C_x[muse_frame_number][k]).c_str());
								By=atof(string (C_y[muse_frame_number][k]).c_str());
								Bz=atof(string (C_z[muse_frame_number][k]).c_str());
								BBx=atof(string (C_x[i][j]).c_str());
								BBy=atof(string (C_y[i][j]).c_str());	cout<<C_point[muse_frame_number][k]<<"	"<<C_point[i][j]<<endl;
								BBz=atof(string (C_z[i][j]).c_str());	}
			if(counter==3)	{	Cx=atof(string (C_x[muse_frame_number][k]).c_str());
								Cy=atof(string (C_y[muse_frame_number][k]).c_str());
								Cz=atof(string (C_z[muse_frame_number][k]).c_str());
								CCx=atof(string (C_x[i][j]).c_str());
								CCy=atof(string (C_y[i][j]).c_str());	cout<<C_point[muse_frame_number][k]<<"	"<<C_point[i][j]<<endl;
								CCz=atof(string (C_z[i][j]).c_str());	}


		}


			if(counter==3)
			{
cout<<endl;
			//	AAx=AAx-(AAx-Ax);	AAy=AAy-(AAy-Ay);	AAz=AAz-(AAz-Az);
			//	BBx=BBx-(AAx-Ax);	BBy=BBy-(AAy-Ay);	BBz=BBz-(AAz-Az);
			//	CCx=CCx-(AAx-Ax);	CCy=CCy-(AAy-Ay);	CCz=CCz-(AAz-Az);

			//	cout<<Ax<<"	"<<AAx<<"		"<<Ay<<"	"<<AAy<<"		"<<Az<<"	"<<AAz<<endl;
			//	cout<<Bx<<"	"<<BBx<<"		"<<By<<"	"<<BBy<<"		"<<Bz<<"	"<<BBz<<endl;
			//	cout<<Cx<<"	"<<CCx<<"		"<<Cy<<"	"<<CCy<<"		"<<Cz<<"	"<<CCz<<endl;

				TVector3 AB,AC,BC,AABB,AACC,BBCC;
				AB.SetXYZ(Bx-Ax,By-Ay,Bz-Az);
				AC.SetXYZ(Cx-Ax,Cy-Ay,Cz-Az);
				BC.SetXYZ(Cx-Bx,Cy-By,Cz-Bz);
				
				AABB.SetXYZ(BBx-AAx,BBy-AAy,BBz-AAz);
				AACC.SetXYZ(CCx-AAx,CCy-AAy,CCz-AAz);
				BBCC.SetXYZ(CCx-BBx,CCy-BBy,CCz-BBz);

				cout<<"---------------"<<AB.Mag()<<"	"<<AABB.Mag()<<"		"<<AC.Mag()<<"	"<<AACC.Mag()<<"		"<<BC.Mag()<<"	"<<BBCC.Mag()<<endl;





			TVector3 Norm;
			
			Norm.SetXYZ(AB.Y()*AABB.Z()-AB.Z()*AABB.Y(),AB.X()*AABB.Z()-AB.Z()*AABB.X(),AB.X()*AABB.Y()-AB.Y()*AABB.X());

			float the_1	=	asin(Norm.Mag()/(AB.Mag()*AABB.Mag()));
		
		//	cout<<(180/PI)*AB.Theta()<<"	before	"<<(180/PI)*AABB.Theta()<<endl;

			AABB.Rotate(-the_1,Norm);



		//	cout<<(180/PI)*AB.Theta()<<"	after	"<<(180/PI)*AABB.Theta()<<endl;


			}


	}		//	for(k)
	}		//	for(j)
		cout<<endl;

	}		//	for(i)

//	end:	.................	matching points with the MUSE-frame points	...


}	//	main


//	the location of the ASCII files from Tino (meeting)
//	https://drive.google.com/drive/folders/1qVItAlvcx8cz3r4qsBRBcPhgYiCl-wBs


