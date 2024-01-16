
using namespace std;



void coordconv_6()
{
	int namesSize = 0;
	int time_index = 8;		//	the time column number in the TXT source file.

	string concname;
	string line;

	TString collection, frame,group, point,time,file_name;
	TString flag;

	ifstream in_file;
	
	float x, y, z, offp, offr;

	vector<TString>	file_name_vec,frame_vec,collection_vec,group_vec,point_vec,tot_frame_vec;
	vector<float>	x_vec,y_vec,z_vec,offp_vec,offr_vec;
	vector<TString> date_time_vec;

	float PI=4*atan(1);


	cout<<"START Block (1) : reading data from the source TXT files ... "<<endl;

//	----------------------------------------------------------------------------
//	1) START : ..............	reading data from TXT files	...................
//	----------------------------------------------------------------------------


	int num_files=56+1;

	for(int f=2;f<num_files;f++)
	{
//	define the input files... 
//	the first one is ole and its frame is the old/main PSI frame, there is no need to use it, it is not a direct MUSE survey.

		if(f==1		){file_name="201200120_PIM1_Distanzberechnungen";	}
		if(f==2		){file_name="20180420_WEHA_MUSE_Kont_Target_calc";	}
		if(f==3		){file_name="20180523_WEHA_PIM1_Muse_Messungen_doku";	}
		if(f==4		){file_name="20181028_WEHA_PIM1_Muse_calc";	}
		if(f==5		){file_name="201901028_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1_calc2458544";	}
		if(f==6		){file_name="201901028_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1_GV_Panel9";	}
		if(f==7		){file_name="201901028_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1";	}
		if(f==8		){file_name="201901029_WEHA_PIM1_Muse_Grund_STT_Testareal";	}
		if(f==9		){file_name="20190510_WEHA_PIM1_Muse_Kont_Target_Insert_2";	}
		if(f==10	){file_name="20190517_WEHA_PIM1_Muse_Aufmass_GEM_calc4";	}
		if(f==11	){file_name="20190524_WEHA_PIM1_Muse_Grund_Target_calc";	}
		if(f==12	){file_name="20190719_WEHA_PIM1_Muse_Kontrollen_Areal_calc2";	}
		if(f==13	){file_name="20190719_WEHA_PIM1_Muse_Kontrollen_Areal_calc3";	}
		if(f==14	){file_name="20190719_WEHA_PIM1_Muse_Kontrollen_Areal_calc4";	}
		if(f==15	){file_name="20200108_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1_calc";	}
		if(f==16	){file_name="20200108_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1";	}
		if(f==17	){file_name="20200116_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_1_frameMUSE";	}
		if(f==18	){file_name="20200116_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_1";	}
		if(f==19	){file_name="20200116_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_frameMUSE";	}
		if(f==20	){file_name="20200116_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target";	}
		if(f==21	){file_name="20200218_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_calc20200813_frameMUSE";	}
		if(f==22	){file_name="20200218_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_calc20200813";	}
		if(f==23	){file_name="20200218_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_frameMUSE";	}
		if(f==24	){file_name="20200218_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target";	}
		if(f==25	){file_name="20200317_PIM1_Position_Panel1-13_Berechnungen";	}
		if(f==26	){file_name="20201209_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1_calc";}	
		if(f==27	){file_name="20201209_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1";	}
		if(f==28	){file_name="20210430_WEHA_PIM1_Muse_Target";	}
		if(f==29	){file_name="20210601_WEHA_PIM1_Muse_Target_calc_frameMUSE";	}
		if(f==30	){file_name="20210601_WEHA_PIM1_Muse_Target_calc";	}
		if(f==31	){file_name="20210601_WEHA_PIM1_Muse_Target_frameMUSE";	}
		if(f==32	){file_name="20210601_WEHA_PIM1_Muse_Target";	}
		if(f==33	){file_name="20210928_WEHA_PIM1_Muse_Target";	}
		if(f==34	){file_name="20220118_WEHA_PIM1_Muse_STT-and-BMbars_only";	}
		if(f==35	){file_name="20220118_WEHA_PIM1_Muse";	}
		if(f==36	){file_name="20220223_WEHA_PIM1_Muse_calc2";	}
		if(f==37	){file_name="20220223_WEHA_PIM1_Muse";	}
		if(f==38	){file_name="20220517_WEHA_PIM1_Muse_calc_relabeled_target-movement-only";	}
		if(f==39	){file_name="20220517_WEHA_PIM1_Muse_calc_relabeled_target-only";	}
		if(f==40	){file_name="20220517_WEHA_PIM1_Muse_calc";	}
		if(f==41	){file_name="20220810_WEHA_PIM1_Muse_Procedure";	}
		if(f==42	){file_name="20220830_WEHA_PIM1_Muse_Grundverm_transf";	}
		if(f==43	){file_name="20220831_WEHA_PIM1_Muse_Grundverm";}
		if(f==44	){file_name="20220906_WEHA_PIM1_Muse_Grundverm";	}
		if(f==45	){file_name="20220907_WEHA_PIM1_Muse_Grundverm";	}
		if(f==46	){file_name="20220913_WEHA_PIM1_Muse_Grundverm_red_ohne_Modell";	}
		if(f==47	){file_name="20220914_WEHA_PIM1_Muse_Grundverm_Sensor_VETO_annotated";	}
		if(f==48	){file_name="20220914_WEHA_PIM1_Muse_Grundverm_Sensor_VETO";	}
		if(f==49	){file_name="20230117_WEHA_PiM1_Muse_Gestell";	}
		if(f==50	){file_name="20230118_WEHA_PiM1_Muse_Gestell";	}
		if(f==51	){file_name="20230119_WEHA_PiM1_Muse_Gestell";	}
		if(f==52	){file_name="20230120_WEHA_PiM1_Muse_Gestell_PiM1";	}
		if(f==53	){file_name="20230612_WEHA_PiM1_Muse_Grund_TCPV";	}
		if(f==54	){file_name="20230613_WEHA_PiM1_Muse_Kont_Targetpositionen";	}
		if(f==55	){file_name="20230614_WEHA_PiM1_Muse_Kont_STT";	}
		if(f==56	){file_name="20230914_WEHA_PiM1_Muse_Kont_STT";	}




		if(f==1		){	frame="Messung::WORLD";}
		if(f==2		){	frame="Standpunkt 1::WORLD";}
		if(f==3		){	frame="Standpunkt 1::Strahl";}
		if(f==4		){	frame="20181128 Kontrollen im Areal::Drehzentrum-Strahl (MUSE)";}
		if(f==5		){	frame="20191028::MUSE 2";}
		if(f==6		){	frame="20191028::MUSE";}
		if(f==7		){	frame="20191028::MUSE";}
		if(f==8		){	frame="Station1::WORLD";}
		if(f==9		){	frame="Standpunkt 1::WORLD";}
		if(f==10	){	frame="GEM 20180312::GV GEM";}
		if(f==11	){	frame="Standpunkt 1::New Frame";}
		if(f==12	){	frame="Standpunkt 1::WORLD";}
		if(f==13	){	frame="Standpunkt 1::WORLD";}
		if(f==14	){	frame="Standpunkt 1::WORLD";}
		if(f==15	){	frame="Station1::PIM1";}
		if(f==16	){	frame="Station1::PIM1";}
		if(f==17	){	frame="Station1::PIM1";}
		if(f==18	){	frame="Targetkorrektur::New Frame";}
		if(f==19	){	frame="Station1::PIM1";}
		if(f==20	){	frame="Targetkorrektur 2::Kammer Lokal Mittig";}
		if(f==21	){	frame="Station1::PIM1";}
		if(f==22	){	frame="Grundvermessung Vakuumkammer::Kammer LOKAL";}
		if(f==23	){	frame="Station1::PIM1";}
		if(f==24	){	frame="20200218 Kontrolle Target Ausgebaut::Kammer Lokal Mittig";}
		if(f==25	){	frame="Panelposition im Areal PIM1::MUSE";}
		if(f==26	){	frame="surf::bottom-surface";}	
		if(f==27	){	frame="20201209 Aufmasse::PIM1";}
		if(f==28	){	frame="20210430::PIM1";}
		if(f==29	){	frame="20210601- Aufmasse MUSE::PIM1";}
		if(f==30	){	frame="20210601- Aufmasse COPY::bottom-surface";}
		if(f==31	){	frame="20210601- Aufmasse MUSE::PIM1";}
		if(f==32	){	frame="20210601- Aufmasse COPY::bottom-surface";}
		if(f==33	){	frame="20210928 Justierung Vakuumkammer und Target::PIM1";}
		if(f==34	){	frame="20220119 Kontrolle Rahmen::PIM1";}
		if(f==35	){	frame="20220119 Kontrolle Rahmen::PIM1";}
		if(f==36	){	frame="20220119 Kontrolle Rahmen::PIM1";}
		if(f==37	){	frame="20220119 Kontrolle Rahmen::PIM1";}
		if(f==38	){	frame="Soll+NK::PIM1";}
		if(f==39	){	frame="Soll+NK::PIM1";}
		if(f==40	){	frame="Soll+NK::PIM1";}
		if(f==41	){	frame="20220119 Kontrolle Rahmen::PIM1";	time_index=15;}		//	the time stored in different columns for the next files.
		if(f==42	){	frame="20220830::EC-local";	time_index=23;}
		if(f==43	){	frame="20220831::Koordinatensystem Instr20220831_1";	time_index=23;}
		if(f==44	){	frame="202209006_Wdh_mit_Gasdruck::Koordinatensystem Instr2";	time_index=23;}
		if(f==45	){	frame="202209006_Wdh_mit_Gasdruck::Koordinatensystem Instr2";	time_index=23;}
		if(f==46	){	frame="202209006_Wdh_mit_Gasdruck::Koordinatensystem Instr2";	time_index=23;}
		if(f==47	){	frame="Station1::WORLD";	time_index=23;}
		if(f==48	){	frame="Station1::WORLD";	time_index=23;}
		if(f==49	){	frame="20230117::MUSE";	time_index=23;}
		if(f==50	){	frame="20230118::MUSE";	time_index=23;}
		if(f==51	){	frame="2023019::MUSE";	time_index=23;}
		if(f==52	){	frame="20230120 calc::MUSE";	time_index=23;}
		if(f==53	){	frame="20200218_GVM_Targetkammer.Stp::WORLD";	time_index=23;}
		if(f==54	){	frame="20230613::MUSE";	time_index=23;}
		if(f==55	){	frame="Standpunkt 1::WORLD1";	time_index=23;}
		if(f==56	){	frame="20230914::WORLD*";	time_index=23;}	





		if(frame.Contains(" "))	{	frame.ReplaceAll(" ","_");	}

		in_file.open(file_name+".txt");

		int lineno = 0;
		while(getline(in_file,line))
		{
		lineno++;
			int line_flag=1;	//	this flag means it is OK to read from the line inside the file

		//	if(line.empty() || TString (line)=='\t' || TString (line)=='\n' || TString (line)=="" || TString (line)==" " || TString (line)=="	" )	
			if(line.empty() )	{	line_flag=0;	}	

			if(line_flag==1)

			{
				stringstream ss(line);
				string item;
				vector<string> items;
				char delim = ',';
				while (getline (ss,item, delim)) {	items.push_back (item);		}

				flag = (TString) items[0];
					int non_comment_flag=1;
					if(flag.Contains("//"))	{non_comment_flag=0;}	//	also, it is a comment line, nothing to be read

				time=TString(items[time_index]);
					int time_flag=1;
					if( time.Contains("00:00:00")){ time_flag=0; }	//	theoritical measurments values
					if(time.Contains(" "))	{	time.ReplaceAll(" ","");	}


				if(non_comment_flag==1 && time_flag==1 && line_flag==1)	//	NOW, we can read data from the line & real measurements
				{	

					collection = (TString)items[0];
					if(collection.Contains(" "))		{	collection.ReplaceAll(" ","");			}
					
					group = (TString)items[1];
					if(group.Contains(" "))				{	group.ReplaceAll(" ","");				}
				

					point = (TString)items[2];

					if(point.Contains(" "))				{	point.ReplaceAll(" ","");				}

					x = atof(items[3].c_str());
					y = atof(items[4].c_str());
					z = atof(items[5].c_str());
					offp = atof(items[6].c_str());
					offr = atof(items[7].c_str());


//	if there is a real measurement, then there is a real time (flag=1), if the time = 00:00:00 (flag=0) then it is a theoritical data, and we don't need it.

//	define the next combination to use it later.

						TString tot_frame_name = file_name+"..."+frame+"..."+collection+"..."+group;




							tot_frame_vec.push_back(file_name+"..."+frame+"..."+collection+"..."+group);
							file_name_vec.push_back(file_name);
							frame_vec.push_back(frame);
							collection_vec.push_back(collection);
							group_vec.push_back(group);
							point_vec.push_back(point);
							x_vec.push_back(x);
							y_vec.push_back(y);
							z_vec.push_back(z);
							offp_vec.push_back(offp);
							offr_vec.push_back(offr);
							date_time_vec.push_back(time);



				}			//	if(comment_flag==1) the line contains useful data
			}				//	if(line_flag==1) ...	the line contains data, any data
		}					//	while the in_file is open
	in_file.close();		//	closing the input TXT file in progress
	}						//	for(f)	opening and reading from the TXT files.

//	----------------------------------------------------------------------------
//	1) END : ................	reading data from TXT files	...................
//	----------------------------------------------------------------------------

//	storing all the points from the vector to a TXT file.

	ofstream out_file_6_0;

	out_file_6_0.open("out_file_6_0.txt");


	for(int i=0;i<x_vec.size();i++)
	{
		out_file_6_0<<file_name_vec[i]<<","<<frame_vec[i]<<","<<collection_vec[i]<<","<<group_vec[i]<<","<<point_vec[i]<<","<<x_vec[i]<<","<<y_vec[i]<<","<<z_vec[i]<<" ,  "<<offp_vec[i]<<","<<offr_vec[i]<<","<<date_time_vec[i]<<endl;
	}


	out_file_6_0.close();


//	defining the output root file.


//	----------------------------------------------------------------------------
//	2) START :	seperating the known points by using the common xyz           ..
//	----------------------------------------------------------------------------

	cout<<"START Block (2) : seperating the known points by using the common xyz. "<<endl;

	TFile *	out_root_file	=	new TFile("points_6.root","RECREATE");

	TString		out_file_name,out_frame,out_collection,out_group,out_point,out_date_time;
	float 		out_x,out_y,out_z,out_offp,out_offr;


	basic_string<char> a ;

	float tmp_x,tmp_y,tmp_z;
	TString tmp_point,tmp_group,tmp_collection;

	vector<int> same_group,same_xyz,same_point;





//	...................................
	ofstream out_trees_file;
	out_trees_file.open("trees_file_6.txt");
//	...................................

	TString tmp_file_name_0,tmp_frame_0,tmp_collection_0,tmp_group_0,tmp_point_0,tmp_date_time_0;
	float	tmp_x_0,tmp_y_0,tmp_z_0,tmp_offp_0,tmp_offr_0;

	int num_trees=0;



	while(point_vec.size()>0)
	{
		num_trees++;
		cout<<num_trees<<" ) ";

		same_group.clear();
		same_xyz.clear();
		same_point.clear();

//	for(int i=0;i<x_vec.size();i++){same_group.push_back(0);	same_xyz.push_back(0);}


		tmp_file_name_0	=	file_name_vec[0];
		tmp_frame_0		=	frame_vec[0];
		tmp_collection_0=	collection_vec[0];
		tmp_group_0		=	group_vec[0];
		tmp_point_0		=	point_vec[0];
		tmp_x_0			=	x_vec[0];
		tmp_y_0			=	y_vec[0];
		tmp_z_0			=	z_vec[0];
		tmp_offp_0		=	offp_vec[0];
		tmp_offr_0		=	offr_vec[0];
		tmp_date_time_0	=	date_time_vec[0];

//	...................................................

	for(int i=0;i<x_vec.size();i++)
	{
		if(point_vec[i]==tmp_point_0){	same_point.push_back(1);	}
	}			//	for(i)

//	...................................................


//	...................................................

	for(int i=0;i<x_vec.size();i++)
	{
		if(x_vec[i]==tmp_x_0 && y_vec[i]==tmp_y_0 && z_vec[i]==tmp_z_0 ){	same_xyz.push_back(1);	}
	}			//	for(i)

//	...................................................


//	...................................................

	for(int i=0;i<x_vec.size();i++)
	{
		if(group_vec[i]==tmp_group_0 ){	same_group.push_back(1);	}
	}			//	for(i)

//	...................................................









	TString treeeeee=tmp_group_0;

						TString tot_frame_name=tmp_file_name_0+"..."+tmp_frame_0+"..."+tmp_collection_0+"..."+tmp_group_0;
						bool local_measurements = tot_frame_name.Contains("Grund") || tot_frame_name.Contains("Rotationsachse") ||
						tot_frame_name.Contains("Calorimeter") ||	tot_frame_name.Contains
						("surf") ||	tot_frame_name.Contains("Flaeche") ||	tot_frame_name.Contains
						("Ecken") ||	tot_frame_name.Contains("Ebene") ||	tot_frame_name.Contains("scan");

						int local_flag=0;

						if(local_measurements){local_flag=1;}	//	finding the LOCAL measurements


	if(local_flag==0)	{	out_trees_file<<treeeeee<<endl;	a= string (tmp_group_0);}
	if(local_flag==1)	{	out_trees_file<<"loc_"+treeeeee<<endl;	a= string ("loc_"+tmp_group_0);}


	TTree *out_tree	=	new TTree(Form("%s_%d",a.c_str(),num_trees),"");

	out_tree	->	Branch("file_name",&out_file_name);
	out_tree	->	Branch("frame",&out_frame);
	out_tree	->	Branch("collection",&out_collection);
	out_tree	->	Branch("group",&out_group);
	out_tree	->	Branch("point",&out_point);
	out_tree	->	Branch("x",&out_x);
	out_tree	->	Branch("y",&out_y);
	out_tree	->	Branch("z",&out_z);
	out_tree	->	Branch("offp",&out_offp);
	out_tree	->	Branch("offr",&out_offr);
	out_tree	->	Branch("date_time",&out_date_time);

	
	for(int i=0;i<x_vec.size();i++)
	{
		if(same_group[i]==1 && same_xyz[i]==1 && same_point[i]==1 )
		{

		out_file_name	=	file_name_vec[i];
		out_frame		=	frame_vec[i];
		out_collection	=	collection_vec[i];
		out_group		=	group_vec[i];
		out_point		=	point_vec[i];
		out_x			=	x_vec[i];
		out_y			=	y_vec[i];
		out_z			=	z_vec[i];
		out_offp		=	offp_vec[i];
		out_offr		=	offr_vec[i];
		out_date_time	=	date_time_vec[i];


		out_tree	->  Fill();

		}
	}








	int size_before=point_vec.size();


	for(int i=point_vec.size()-1;i>-1;i--)
	{
		if(same_group[i]==1)
		{
			file_name_vec.erase(std::next(file_name_vec.begin(),i));
			frame_vec.erase(std::next(frame_vec.begin(),i));
			collection_vec.erase(std::next(collection_vec.begin(),i));
			group_vec.erase(std::next(group_vec.begin(),i));
			point_vec.erase(std::next(point_vec.begin(),i));
			x_vec.erase(std::next(x_vec.begin(),i));
			y_vec.erase(std::next(y_vec.begin(),i));
			z_vec.erase(std::next(z_vec.begin(),i));
			offp_vec.erase(std::next(offp_vec.begin(),i));
			offr_vec.erase(std::next(offr_vec.begin(),i));
			date_time_vec.erase(std::next(date_time_vec.begin(),i));
		}
	}
	
	int size_after=point_vec.size();

	cout<<endl;
	cout<<"size before : "<<size_before<<" ... size after : "<<size_after<<" ... size classified : "<<size_before-size_after<<endl;
	cout<<endl;







	}	//	while







	out_trees_file.close();



	out_root_file	->	Write();
//	out_root_file	->	Print();
	out_root_file	->	Close();






//	storing all the points from the vector to a TXT file.

	ofstream out_file_6_2;

	out_file_6_2.open("out_file_6_2.txt");


	for(int i=0;i<x_vec.size();i++)
	{
		out_file_6_2<<file_name_vec[i]<<","<<frame_vec[i]<<","<<collection_vec[i]<<","<<group_vec[i]<<","<<point_vec[i]<<","<<x_vec[i]<<","<<y_vec[i]<<","<<z_vec[i]<<" ,  "<<offp_vec[i]<<","<<offr_vec[i]<<","<<date_time_vec[i]<<endl;
	}


	out_file_6_2.close();

}	//	main










































/*


	vector<int> filled_points;

	TString		out_file_name,out_frame,out_collection,out_group,out_point,out_date_time;
	float 		out_x,out_y,out_z,out_offp,out_offr;

	TString tmp_file_name_0,tmp_frame_0,tmp_collection_0,tmp_group_0,tmp_point_0,tmp_date_time_0;
	float	tmp_x_0,tmp_y_0,tmp_z_0,tmp_offp_0,tmp_offr_0;

	int num_trees=0;

	out_trees_file.open("trees_file_5.txt");


	for(int k=0;k<known_groups_vec.size();k++)
	{

	num_trees++;
	filled_points.clear();
	filled_points.push_back(1);


		tmp_file_name_0	=	file_name_vec[0];
		tmp_frame_0		=	frame_vec[0];
		tmp_collection_0=	collection_vec[0];
		tmp_group_0		=	group_vec[0];
		tmp_point_0		=	point_vec[0];
		tmp_x_0			=	x_vec[0];
		tmp_y_0			=	y_vec[0];
		tmp_z_0			=	z_vec[0];
		tmp_offp_0		=	offp_vec[0];
		tmp_offr_0		=	offr_vec[0];
		tmp_date_time_0	=	date_time_vec[0];

		to_string (num_trees);


	basic_string<char> a ;
	TString treeeeee=known_groups_vec[k]+"_"+(TString)to_string (num_trees);


						TString tot_frame_name=tmp_file_name_0+"..."+tmp_frame_0+"..."+tmp_collection_0+"..."+tmp_group_0;
						bool local_measurements = tot_frame_name.Contains("Grund") || tot_frame_name.Contains("Rotationsachse") ||
						tot_frame_name.Contains("Calorimeter") ||	tot_frame_name.Contains
						("surf") ||	tot_frame_name.Contains("Flaeche") ||	tot_frame_name.Contains
						("Ecken") ||	tot_frame_name.Contains("Ebene") ||	tot_frame_name.Contains("scan");

						int local_flag=0;

						if(local_measurements){local_flag=1;}	//	finding the LOCAL measurements


	if(local_flag==0)	{	out_trees_file<<treeeeee<<endl;	a= string (tmp_group_0);}
	if(local_flag==1)	{	out_trees_file<<"loc_"+treeeeee<<endl;	a= string ("loc_"+tmp_group_0);}


	TTree *out_tree	=	new TTree(Form("%s_%d",a.c_str(),num_trees),"");

	out_tree	->	Branch("file_name",&out_file_name);
	out_tree	->	Branch("frame",&out_frame);
	out_tree	->	Branch("collection",&out_collection);
	out_tree	->	Branch("group",&out_group);
	out_tree	->	Branch("point",&out_point);
	out_tree	->	Branch("x",&out_x);
	out_tree	->	Branch("y",&out_y);
	out_tree	->	Branch("z",&out_z);
	out_tree	->	Branch("offp",&out_offp);
	out_tree	->	Branch("offr",&out_offr);
	out_tree	->	Branch("date_time",&out_date_time);
	

		out_file_name	=	file_name_vec[0];
		out_frame		=	frame_vec[0];
		out_collection	=	collection_vec[0];
		out_group		=	group_vec[0];
		out_point		=	point_vec[0];
		out_x			=	x_vec[0];
		out_y			=	y_vec[0];
		out_z			=	z_vec[0];
		out_offp		=	offp_vec[0];
		out_offr		=	offr_vec[0];
		out_date_time	=	date_time_vec[0];


		out_tree	->  Fill();


	float eps=0.1;

		for(int i=1;i<point_vec.size();i++)
		{

			if(	group_vec[i]==tmp_group_0 && frame_vec[i]==tmp_frame_0	)//&&	fabs(x_vec[i]-tmp_x_0)<eps && fabs(y_vec[i]-tmp_y_0)<eps && fabs(z_vec[i]-tmp_z_0)<eps)
			{
				filled_points.push_back(1);

				out_file_name	=	file_name_vec[i];
				out_frame		=	frame_vec[i];
				out_collection	=	collection_vec[i];
				out_group		=	group_vec[i];
				out_point		=	point_vec[i];
				out_x			=	x_vec[i];
				out_y			=	y_vec[i];
				out_z			=	z_vec[i];
				out_offp		=	offp_vec[i];
				out_offr		=	offr_vec[i];
				out_date_time	=	date_time_vec[i];

			out_tree	->  Fill();

			}	//	if(x_vec[i]==tmp_x_0 && y_vec[i]==tmp_y_0 && z_vec[i]==tmp_z_0)

			else{	filled_points.push_back(0); }


	
		}	//	for(i)




//	dropping the elements which filled in the tree from the original vectors.

	int size_before=point_vec.size();


	for(int i=point_vec.size()-1;i>-1;i--)
	{
		if(filled_points[i]==1)
		{
			file_name_vec.erase(std::next(file_name_vec.begin(),i));
			frame_vec.erase(std::next(frame_vec.begin(),i));
			collection_vec.erase(std::next(collection_vec.begin(),i));
			group_vec.erase(std::next(group_vec.begin(),i));
			point_vec.erase(std::next(point_vec.begin(),i));
			x_vec.erase(std::next(x_vec.begin(),i));
			y_vec.erase(std::next(y_vec.begin(),i));
			z_vec.erase(std::next(z_vec.begin(),i));
			offp_vec.erase(std::next(offp_vec.begin(),i));
			offr_vec.erase(std::next(offr_vec.begin(),i));
			date_time_vec.erase(std::next(date_time_vec.begin(),i));
		}
	}
	
	int size_after=point_vec.size();

	cout<<endl;
	cout<<"size before : "<<size_before<<" ... size after : "<<size_after<<" ... size classified : "<<size_before-size_after<<endl;
	cout<<endl;


	}	//	for(k) over the known groups vector.













	out_file.open("out_file_5_1.txt");


	for(int i=0;i<x_vec.size();i++)
	{
		out_file<<file_name_vec[i]<<","<<frame_vec[i]<<","<<collection_vec[i]<<","<<group_vec[i]<<","<<point_vec[i]<<","<<x_vec[i]<<","<<y_vec[i]<<","<<z_vec[i]<<" ,  "<<offp_vec[i]<<","<<offr_vec[i]<<","<<date_time_vec[i]<<endl;
	}


	out_file.close();

	out_trees_file.close();




*/







//	----------------------------------------------------------------------------
//	2) END :	seperating the known points by using the common group's name. ..
//	----------------------------------------------------------------------------















/*


	

	TFile *	out_root_file	=	new TFile("points_4.root","RECREATE");


	vector<int> filled_points;

	TString		out_file_name,out_frame,out_collection,out_group,out_point,out_date_time;
	float 		out_x,out_y,out_z,out_offp,out_offr;

	TString tmp_file_name_0,tmp_frame_0,tmp_collection_0,tmp_group_0,tmp_point_0,tmp_date_time_0;
	float	tmp_x_0,tmp_y_0,tmp_z_0,tmp_offp_0,tmp_offr_0;

	int num_trees=0;



	out_trees_file.open("trees_file_4.txt");


	while(point_vec.size()>0)
	{
		for(int k=0;k<known_groups_vec.size();k++)
		{


	num_trees++;
	filled_points.clear();
	filled_points.push_back(1);


		tmp_file_name_0	=	file_name_vec[0];
		tmp_frame_0		=	frame_vec[0];
		tmp_collection_0=	collection_vec[0];
		tmp_group_0		=	group_vec[0];
		tmp_point_0		=	point_vec[0];
		tmp_x_0			=	x_vec[0];
		tmp_y_0			=	y_vec[0];
		tmp_z_0			=	z_vec[0];
		tmp_offp_0		=	offp_vec[0];
		tmp_offr_0		=	offr_vec[0];
		tmp_date_time_0	=	date_time_vec[0];

		to_string (num_trees);


	basic_string<char> a ;
	TString treeeeee=known_groups_vec[k]+"_"+(TString)to_string (num_trees);


						TString tot_frame_name=tmp_file_name_0+"..."+tmp_frame_0+"..."+tmp_collection_0+"..."+tmp_group_0;
						bool local_measurements = tot_frame_name.Contains("Grund") || tot_frame_name.Contains("Rotationsachse") ||
						tot_frame_name.Contains("Calorimeter") ||	tot_frame_name.Contains
						("surf") ||	tot_frame_name.Contains("Flaeche") ||	tot_frame_name.Contains
						("Ecken") ||	tot_frame_name.Contains("Ebene") ||	tot_frame_name.Contains("scan");

						int local_flag=0;

						if(local_measurements){local_flag=1;}	//	finding the LOCAL measurements


	if(local_flag==0)	{	out_trees_file<<treeeeee<<endl;	a= string (tmp_group_0);}
	if(local_flag==1)	{	out_trees_file<<"loc_"+treeeeee<<endl;	a= string ("loc_"+tmp_group_0);}


	TTree *out_tree	=	new TTree(Form("%s_%d",a.c_str(),num_trees),"");

	out_tree	->	Branch("file_name",&out_file_name);
	out_tree	->	Branch("frame",&out_frame);
	out_tree	->	Branch("collection",&out_collection);
	out_tree	->	Branch("group",&out_group);
	out_tree	->	Branch("point",&out_point);
	out_tree	->	Branch("x",&out_x);
	out_tree	->	Branch("y",&out_y);
	out_tree	->	Branch("z",&out_z);
	out_tree	->	Branch("offp",&out_offp);
	out_tree	->	Branch("offr",&out_offr);
	out_tree	->	Branch("date_time",&out_date_time);
	

		out_file_name	=	file_name_vec[0];
		out_frame		=	frame_vec[0];
		out_collection	=	collection_vec[0];
		out_group		=	group_vec[0];
		out_point		=	point_vec[0];
		out_x			=	x_vec[0];
		out_y			=	y_vec[0];
		out_z			=	z_vec[0];
		out_offp		=	offp_vec[0];
		out_offr		=	offr_vec[0];
		out_date_time	=	date_time_vec[0];


		out_tree	->  Fill();


	float eps=0.1;

		for(int i=1;i<point_vec.size();i++)
		{



			if(	group_vec[i]==tmp_group_0 && frame_vec[i]==tmp_frame_0	)//&&	fabs(x_vec[i]-tmp_x_0)<eps && fabs(y_vec[i]-tmp_y_0)<eps && fabs(z_vec[i]-tmp_z_0)<eps)
			{
				filled_points.push_back(1);

				out_file_name	=	file_name_vec[i];
				out_frame		=	frame_vec[i];
				out_collection	=	collection_vec[i];
				out_group		=	group_vec[i];
				out_point		=	point_vec[i];
				out_x			=	x_vec[i];
				out_y			=	y_vec[i];
				out_z			=	z_vec[i];
				out_offp		=	offp_vec[i];
				out_offr		=	offr_vec[i];
				out_date_time	=	date_time_vec[i];

			out_tree	->  Fill();

			}	//	if(x_vec[i]==tmp_x_0 && y_vec[i]==tmp_y_0 && z_vec[i]==tmp_z_0)

			else{	filled_points.push_back(0); }


	
		}	//	for(i)




//	dropping the elements which filled in the tree from the original vectors.

	int size_before=point_vec.size();


	for(int i=point_vec.size()-1;i>-1;i--)
	{
		if(filled_points[i]==1)
		{
			file_name_vec.erase(std::next(file_name_vec.begin(),i));
			frame_vec.erase(std::next(frame_vec.begin(),i));
			collection_vec.erase(std::next(collection_vec.begin(),i));
			group_vec.erase(std::next(group_vec.begin(),i));
			point_vec.erase(std::next(point_vec.begin(),i));
			x_vec.erase(std::next(x_vec.begin(),i));
			y_vec.erase(std::next(y_vec.begin(),i));
			z_vec.erase(std::next(z_vec.begin(),i));
			offp_vec.erase(std::next(offp_vec.begin(),i));
			offr_vec.erase(std::next(offr_vec.begin(),i));
			date_time_vec.erase(std::next(date_time_vec.begin(),i));
		}
	}
	
	int size_after=point_vec.size();

	cout<<endl;
	cout<<"size before : "<<size_before<<" ... size after : "<<size_after<<" ... size classified : "<<size_before-size_after<<endl;
	cout<<endl;


	}	//	for(k) over the known groups vector.




	}	//	while(point_vec.size()>-1)




	out_file.open("out_file_4.txt");


	for(int i=0;i<x_vec.size();i++)
	{
		out_file<<file_name_vec[i]<<","<<frame_vec[i]<<","<<collection_vec[i]<<","<<group_vec[i]<<","<<point_vec[i]<<","<<x_vec[i]<<","<<y_vec[i]<<","<<z_vec[i]<<" ,  "<<offp_vec[i]<<","<<offr_vec[i]<<","<<date_time_vec[i]<<endl;
	}


	out_file.close();

	out_trees_file.close();






	out_root_file	->	Write();
//	out_root_file	->	Print();
	out_root_file	->	Close();



}	//	main


*/


