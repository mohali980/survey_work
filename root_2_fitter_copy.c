
#include <iostream>
#include <iomanip>


void root_2_fitter_copy()
{



	TString working_file_name,working_frame,working_collection,working_group,working_point;
	int working_month,working_day,working_yr,working_hr,working_min,working_sec;
	float working_x,working_y,working_z,working_offp,working_offr;


//	................................................................
//	creat a folder contains all the measurements from the root trees:
//	it will be: ~/muse/g4PSI/root_2_fitter
//	and inside it a saperate folder for each detector according to the name of its tree.
	TString dir_name="10_root_2_fitter";
//	gSystem->Exec("cd ..");
	gSystem->Exec("rm -rf "+dir_name);
	gSystem->Exec("mkdir "+dir_name);


//	................................................................
//	trees' names are stored in the file "10_trees.txt"

	ifstream in_trees_file;
	string line;

	int nu_of_trees=0;
	in_trees_file.open("11_trees.txt");
	TFile file("measurements.root");

	vector<TString> trees_names;

	while(getline(in_trees_file,line))
	{
		stringstream ss(line);
		string item;
		while (getline (ss,item)) {	trees_names.push_back (item);		}
	}

	cout<<"Number of the different coordinates : "<<trees_names.size()<<endl;


	for(int k=0;k<trees_names.size();k++)	//	(AAA)
	{
	basic_string<char> a = string (trees_names[k]);

//	...............................................................................
//	getting data from the root file:

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
//	...............................................................................

		TString dir;

		dir=trees_names[k]+"_fit";
		gSystem->Exec("mkdir "+dir_name+"/"+dir);
		gSystem->Exec("cp root_2_OBJ_fit.c "+dir_name+"/"+dir+"/");		

		ofstream out_f;
		out_f.open(dir_name+"/"+dir+"/"+"measurements.txt");

//	...............................................................................

//	Fill the "measurements.txt" file:
	int tt=0;
		while (reader.Next()) 
		{
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

		//	...........................
		// the measurements.txt header:
			if(tt==0)
			{
			out_f<<"#############################################"<<endl;
			out_f<<"# "<<working_month<<"/20"<<working_yr<<" "<<working_group<<" survey points"<<endl;
			out_f<<"#############################################"<<endl;
			out_f<<endl;
			}

			out_f<<working_group<<" "<<working_point<<" "<<working_x<<" "<<working_y<<" "<<working_z<<" "<<"mm"<<endl;


			tt++;

		}	//	while (reader.Next())






		out_f.close();
/*
			gSystem->ChangeDirectory(dir_name+"/"+dir);
			gSystem->Exec("root root_2_OBJ_fit.c");
			gSystem->ChangeDirectory("../..");
*/

			


	}	//	for(k)

}	//	main




