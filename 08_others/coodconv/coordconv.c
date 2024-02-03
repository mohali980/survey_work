#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


//	...........................................................................

void coordconv()
	{

	float out_x, out_y, out_z, out_offp, out_offr;
	TString out_frame,out_collection, out_group, out_point,out_total_frame,out_txt_file;
		TString temp;


	string in_file_name,in_frame,in_collection,in_group,in_point;
	string in_x,in_y,in_z,in_offp,in_offr;
	vector	<TString> frames;

	ifstream in_file;
	in_file.open("2022_all_data.txt");

//	.........................	define the output root file 	...............

	TFile *out_file = new TFile("2022_all_data.root", "RECREATE");
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

		out_tree->Fill();


/*
		temp=temp_file_name+"..."+temp_frame+"..."+temp_collection+"..."+temp_group+"..."+temp_point;

		int flag=1;

		if(lineno==0){frames.push_back(temp);}

		if (lineno!=0)
		{
		for(int i=0;i<lineno;i++)	{	if(temp!=frames[i])	{	flag=flag*1;	}}
		for(int i=0;i<lineno;i++)	{	if(temp==frames[i])	{	flag=flag*0;	}}
			cout<<flag<<endl;
		}
	
*/


	lineno++;
	}	//	while

//	...........................................................................

	out_tree->Write();
//	out_tree->Print();
	out_file->Close();
			
}	//	main