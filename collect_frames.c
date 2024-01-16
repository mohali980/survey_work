


void collect_frames()
{
	
	ifstream in_trees_file;
	string line;


	int nu_of_trees=0;
	in_trees_file.open("trees_file_4.txt");

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






	vector<TString> file_name_vec,frame_vec,collection_vec,group_vec,point_vec,date_time_vec;
	vector<float>	x_vec,y_vec,z_vec,offp_vec,offr_vec;



	


TFile file("points_4.root");


		TString dir="OBJ_files";
		gSystem->Exec("rm -rf "+dir);



	for(int i=0;i<trees_names.size();i++)
	{
		basic_string<char> a = string (trees_names[i]);


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

		cout<<i+1<<" ) "<<a.c_str()<<" : ";




		int tree_size=0;
	while (reader.Next()) 
	{
		tree_size++;

		vector<vector<TString>>	
		vector<vector<float>>	














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










	}	//	while (reader.Next())

	cout<<tree_size<<endl;


	}		//	for(int i=0;i<trees_names.size();i++)




























}



