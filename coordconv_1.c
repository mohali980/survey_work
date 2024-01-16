#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>


//	...........................................................................

void coordconv_1()
	{

	float out_x, out_y, out_z, out_offp, out_offr;
	TString out_frame,out_collection, out_group, out_point,out_total_frame,out_txt_file;
	TString temp,temp_x,temp_y,temp_z,temp_offp,temp_offr;


	string in_file_name,in_frame,in_collection,in_group,in_point;
	string in_x,in_y,in_z,in_offp,in_offr;

	vector	<TString> frames,POINT;
	vector	<float>	X,Y,Z,OFFP,OFFR;

	ifstream in_file;
	in_file.open("2022_all_data.txt");



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

		temp=temp_file_name+"..."+temp_frame+"..."+temp_collection+"..."+temp_group;



		out_txt_file	=	temp_file_name;
		out_frame		=	temp_frame;
		out_collection 	=	temp_collection;
		out_group 		=	temp_group;
		out_point 		=	temp_point;

		out_total_frame	=	temp;

		out_x = atof(in_x.c_str());
		out_y = atof(in_y.c_str());
		out_z = atof(in_z.c_str());
		out_offp = atof(in_offp.c_str());
		out_offr = atof(in_offr.c_str());



		frames.push_back(temp);
		POINT.push_back(temp_point);
		X.push_back(out_x);
		Y.push_back(out_y);
		Z.push_back(out_z);
		OFFP.push_back(out_offp);
		OFFR.push_back(out_offr);




	lineno++;
	}	//	while



	for(int i=0;i<X.size();i++)
	{	
		for(int j=i+1;j<X.size();j++)
		{
		//	if(fabs(X[j]-X[i])<1 && fabs(Y[j]-Y[i])<1 && fabs(Z[j]-Z[i])<1 ){cout<<i<<"-"<<j<<" ) "<<POINT[i]<<"	"<<X[j]<<"	"<<Y[j]<<"	"<<Z[j]<<"	"<<frames[j]<<endl;}
			if((frames[j]==frames[i] && POINT[i]==POINT[j])  ){cout<<i<<"-"<<j<<" ) "<<POINT[i]<<"	"<<X[j]<<"	"<<Y[j]<<"	"<<Z[j]<<endl;}
		}
cout<<"-------------------------------------------------------"<<endl;
	}






}	//	main

/*

//	.........................	define the output root file 	...............

	TFile *out_file = new TFile("2022_frames.root", "RECREATE");
	TTree *out_tree = new TTree("T","");
	
	out_tree->Branch("total_frame",&out_total_frame);
	out_tree->Branch("txt_file",&out_txt_file);
	out_tree->Branch("frame", &out_frame);
	out_tree->Branch("collection", &out_collection);
	out_tree->Branch("group", &out_group);
	out_tree->Branch("point", &out_point);
	out_tree->Branch("x", &out_x,"out_x/F");
	out_tree->Branch("y", &out_y,"out_y/F");
	out_tree->Branch("z", &out_z,"out_z/F");
	out_tree->Branch("offp", &out_offp,"out_offp/F");
	out_tree->Branch("offr", &out_offr,"out_offr/F");
	

//	.........................	reading from the data txt file 	...............
	
//	...........................................................................

	out_tree->Write();
//	out_tree->Print();
	out_file->Close();
			
}	//	main



*/