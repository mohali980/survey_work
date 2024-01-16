ClassImp(TTimeStamp);
using namespace std;

void coordconv_7()
{
	int namesSize = 0;
	int time_index = 8;		//	the time column number in the TXT source file.

	string concname;
	string line;

	TString collection, frame,group, point,time,file_name;
	TString flag;

	ifstream in_file;
	ofstream out_file,pre_out_file,out_loc_file;
	
	float x, y, z, offp, offr;

	vector<TString>	file_name_vec,frame_vec,collection_vec,group_vec,point_vec,tot_frame_vec;
	vector<TString>	loc_file_name_vec,loc_frame_vec,loc_collection_vec,loc_group_vec,loc_point_vec,loc_tot_frame_vec;

	vector<float>	x_vec,y_vec,z_vec,offp_vec,offr_vec;
	vector<float>	loc_x_vec,loc_y_vec,loc_z_vec,loc_offp_vec,loc_offr_vec;

	vector<TString> loc_date_time_vec,date_time_vec;

	float PI=4*atan(1);


	cout<<"START Block (1) : reading data from the source TXT files ... "<<endl;
//	1) START : ..............	reading data from TXT files	...................


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
				//	if(point.Contains("product-name:"))	{	point.ReplaceAll("product-name:","");	}
					if(point.Contains(" "))				{	point.ReplaceAll(" ","");				}

					x = atof(items[3].c_str());
					y = atof(items[4].c_str());
					z = atof(items[5].c_str());
					offp = atof(items[6].c_str());
					offr = atof(items[7].c_str());


//	if there is a real measurement, then there is a real time (flag=1), if the time = 00:00:00 (flag=0) then it is a theoritical data, and we don't need it.

//	define the next combination to use it later.

						TString tot_frame_name = file_name+"..."+frame+"..."+collection+"..."+group;

//	if the defined combination contains one of the shown expressions, then it is a local measurement.

						bool local_measurements = tot_frame_name.Contains("Grund") || tot_frame_name.Contains("Rotationsachse") ||
						tot_frame_name.Contains("Calorimeter") ||	tot_frame_name.Contains
						("surf") ||	tot_frame_name.Contains("Flaeche") ||	tot_frame_name.Contains
						("Ecken") ||	tot_frame_name.Contains("Ebene") ||	tot_frame_name.Contains("scan");

						int local_flag=0;

//	the local measurements (local_flag=1) will be stored separately, the "muse" measurements (local_flag=0).

						if(local_measurements){local_flag=1;}	//	finding the LOCAL measurements


						local_flag=0;


						if(local_flag==0)	//	NON-Local measuremants
						{



//	storing the same non-local total_frame data in the same 1D vector, which will be imbedded latter within a 2D vector.

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

						}	//	if(local_flag==0)		NON-Local measuremants

						if(local_flag==1)	//	Local measurements
						{


//	storing the same local total_frame data in the same 1D vector, which will be imbedded latter within a 2D vector.

							loc_tot_frame_vec.push_back(file_name+"..."+frame+"..."+collection+"..."+group);
							loc_file_name_vec.push_back(file_name);
							loc_frame_vec.push_back(frame);
							loc_collection_vec.push_back(collection);
							loc_group_vec.push_back(group);
							loc_point_vec.push_back(point);
							loc_x_vec.push_back(x);
							loc_y_vec.push_back(y);
							loc_z_vec.push_back(z);
							loc_offp_vec.push_back(offp);
							loc_offr_vec.push_back(offr);
							loc_date_time_vec.push_back(time);
					
					}		//	if(local_flag==1)		Local measurements
				}			//	if(comment_flag==1) the line contains useful data
			}				//	if(line_flag==1) ...	the line contains data, any data
		}					//	while the in_file is open
	in_file.close();		//	closing the input TXT file in progress
	}						//	for(f)	opening and reading from the TXT files.
//	1) END : ................	reading data from TXT files	...................
	


//	storing all the points from the vector to a TXT file.
	ofstream out_file_7_0;
	out_file_7_0.open("out_file_7_0.txt");
	for(int i=0;i<x_vec.size();i++)
	{
		out_file_7_0<<file_name_vec[i]<<","<<frame_vec[i]<<","<<collection_vec[i]<<","<<group_vec[i]<<","<<point_vec[i]<<","<<x_vec[i]<<","<<y_vec[i]<<","<<z_vec[i]<<" ,  "<<offp_vec[i]<<","<<offr_vec[i]<<","<<date_time_vec[i]<<endl;
	}
	out_file_7_0.close();

//	.....................................................









	cout<<"START Block (2) : seperating each divice's coordinates, in a separate file for each year."<<endl;
//	4) START:	.............	seperating each divice's coordinates 	.......................
//	defining the output tree,
//	in the next lines, defining the branches whit their parameters, we can add any more branches 
//	but the parameters should be define as done in the others, COPY and PASTE is very useful.

	TString		out_file_name,out_frame,out_collection,out_group,out_point,out_date_time;
	float 		out_x,out_y,out_z,out_offp,out_offr;

	basic_string<char> a ;


	TFile *	out_root_file	=	new TFile("points_7.root","RECREATE");

	vector<TString>	trees;
	vector<int>		flags;

//	............................................
	trees.clear();

//	trees.push_back("PiM1");
	trees.push_back("G1");
	trees.push_back("G2");
	trees.push_back("G3");
	trees.push_back("G4");
	trees.push_back("G5");
	trees.push_back("G6");
	trees.push_back("G7");
/*	trees.push_back("H_SlidingTable");
	trees.push_back("M_STT");
	trees.push_back("TA_SlidingTable");
	trees.push_back("HP");
	trees.push_back("PA6");
	trees.push_back("PA7");
	trees.push_back("Kreis");
	trees.push_back("G1");
	trees.push_back("G2");
	trees.push_back("G3");
	trees.push_back("G4");
	trees.push_back("G5");
	trees.push_back("G6");
	trees.push_back("G7");
	trees.push_back("TG");
	trees.push_back("2E2");
	trees.push_back("2E1");
	trees.push_back("TC1");
	trees.push_back("TC2");
	trees.push_back("TC3");
	trees.push_back("BFM_PiM1");
	trees.push_back("Draht_PiM1");
	trees.push_back("Flaeche_PiM1");
	trees.push_back("Panel9O");
	trees.push_back("Panel10O");
	trees.push_back("Panel11O");
	trees.push_back("Panel12O");
	trees.push_back("Leiter3-1");
	trees.push_back("Fenster");
	trees.push_back("loc_BFM");
	trees.push_back("loc_Flaeche");
	trees.push_back("TCPVL_1");
	trees.push_back("TCPVL_2");
	trees.push_back("TCPVL_3");
	trees.push_back("TCPVL_4");
	trees.push_back("TCPVR_1");
	trees.push_back("TCPVR_2");
	trees.push_back("TCPVR_3");
	trees.push_back("TCPVR_4");*/

//	trees.push_back("BM_BigBars");
//	trees.push_back("BM_Hodo");
//	trees.push_back("STT_LV60");
//	trees.push_back("STT_LH60");
//	trees.push_back("STT_LV90");
//	trees.push_back("STT_LH90");
//	trees.push_back("SPS_LF");
//	trees.push_back("SPS_LR");
//	trees.push_back("STT_RV60");
//	trees.push_back("STT_RH60");
//	trees.push_back("STT_RV90");
//	trees.push_back("STT_RH90");
//	trees.push_back("SPS_RF");
//	trees.push_back("SPS_RR");	

	int sum_classified=0;
	int size_after;

//	............................................
	for(int i=0;i<x_vec.size();i++){flags.push_back(0);}
//	............................................

	int size_before=x_vec.size();
	
	cout<<"size before : "<<size_before<<endl;

	string H;
//	==================================================================================

	for(int i=0;i<trees.size();i++)
	{


	a= string (trees[i]);

	TTree *out_tree	=	new TTree(Form("%s",a.c_str()),"");

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

	int counter=0;

	for(int j=point_vec.size()-1;j>-1;j--)

//	for(int j=0;j<x_vec.size();j++)
	{
	int yes=0;
	int n=-1;
//	...........................................................................
//	if(i==n)	{	if( point_vec[j].Contains("PIM1"))	{yes=1;}}	n++;



	bool tmp_G=(frame_vec[j]=="20210430::PIM1" ||	frame_vec[j]=="20210601-_Aufmasse_MUSE::PIM1" || frame_vec[j]=="20210928_Justierung_Vakuumkammer_und_Target::PIM1");
	if(i==n+1)	{	if( group_vec[j]=="G1" && tmp_G)	{yes=1;}}	n++;
	if(i==n+1)	{	if( group_vec[j]=="G2" && tmp_G)	{yes=1;}}	n++;
	if(i==n+1)	{	if( group_vec[j]=="G3" && tmp_G)	{yes=1;}}	n++;
	if(i==n+1)	{	if( group_vec[j]=="G4" && tmp_G)	{yes=1;}}	n++;
	if(i==n+1)	{	if( group_vec[j]=="G5" && tmp_G)	{yes=1;}}	n++;
	if(i==n+1)	{	if( group_vec[j]=="G6" && tmp_G)	{yes=1;}}	n++;
	if(i==n+1)	{	if( group_vec[j]=="G7" && tmp_G)	{yes=1;}}	n++;

/*	if(i==n+1)	{	H=(string) point_vec[j];
					if(H.compare("H")==0)		{yes=1;}
					if(H.compare("H0")==0)		{yes=1;}
					if(H.compare("H1")==0)		{yes=1;}
					if(H.compare("H2")==0)		{yes=1;}
					if(H.compare("H3")==0)		{yes=1;}
					if(H.compare("H4")==0)		{yes=1;}
					if(H.compare("H5")==0)		{yes=1;}
					if(H.compare("H6")==0)		{yes=1;}
					if(H.compare("H7")==0)		{yes=1;}
					if(H.compare("H8")==0)		{yes=1;}
					if(H.compare("H9")==0)		{yes=1;}
					if(H.compare("H10")==0)		{yes=1;}
					if(H.compare("H11")==0)		{yes=1;}
					if(H.compare("H12")==0)		{yes=1;}
					if(H.compare("H13")==0)		{yes=1;}
					if(H.compare("H14")==0)		{yes=1;}
					if(H.compare("H15")==0)		{yes=1;}
					if(H.compare("H16")==0)		{yes=1;}
					if(H.compare("H17")==0)		{yes=1;}
					if(H.compare("H18")==0)		{yes=1;}
					if(H.compare("H19")==0)		{yes=1;}
					if(H.compare("H20")==0)		{yes=1;}
					if(H.compare("H21")==0)		{yes=1;}
					if(H.compare("H22")==0)		{yes=1;}
					if(H.compare("H23")==0)		{yes=1;}
					if(H.compare("H24")==0)		{yes=1;}}	n++;
	if(i==n+1)	{	if( point_vec[j].Contains("M"))		{yes=1;}}	n++;
	if(i==n+1)	{	if( point_vec[j].Contains("TA"))	{yes=1;}}	n++;
	if(i==n+1)	{	if( point_vec[j].Contains("HP"))	{yes=1;}}	n++;
	if(i==n+1)	{	if( point_vec[j].Contains("PA6"))	{yes=1;}}	n++;
	if(i==n+1)	{	if( point_vec[j].Contains("PA7"))	{yes=1;}}	n++;
	if(i==n+1)	{	if( group_vec[j]=="Kreis")			{yes=1;}}	n++;
	if(i==n+1)	{	if (frame_vec[j]=="20210601-_Aufmasse_COPY::bottom-surface" && group_vec[j]=="G1")		{yes=1;}}	n++;
	if(i==n+1)	{	if (frame_vec[j]=="20210601-_Aufmasse_COPY::bottom-surface" && group_vec[j]=="G2")		{yes=1;}}	n++;
	if(i==n+1)	{	if (frame_vec[j]=="20210601-_Aufmasse_COPY::bottom-surface" && group_vec[j]=="G3")		{yes=1;}}	n++;
	if(i==n+1)	{	if (frame_vec[j]=="20210601-_Aufmasse_COPY::bottom-surface" && group_vec[j]=="G4")		{yes=1;}}	n++;
	if(i==n+1)	{	if (frame_vec[j]=="20210601-_Aufmasse_COPY::bottom-surface" && group_vec[j]=="G5")		{yes=1;}}	n++;
	if(i==n+1)	{	if (frame_vec[j]=="20210601-_Aufmasse_COPY::bottom-surface" && group_vec[j]=="G6")		{yes=1;}}	n++;
	if(i==n+1)	{	if (frame_vec[j]=="20210601-_Aufmasse_COPY::bottom-surface" && group_vec[j]=="G7")		{yes=1;}}	n++;
	if(i==n+1)	{	if( point_vec[j].Contains("TG-"))	{yes=1;}}	n++;
	if(i==n+1)	{	if( group_vec[j].Contains("Position2E2"))	{yes=1;}}	n++;
	if(i==n+1)	{	if( group_vec[j].Contains("Position2E1"))	{yes=1;}}	n++;
	if(i==n+1)	{	H =(string) group_vec[j];	if( H.compare("TC1")==0)		{yes=1;}}	n++;
	if(i==n+1)	{	H =(string) group_vec[j];	if( H.compare("TC2")==0)		{yes=1;}}	n++;
	if(i==n+1)	{	H =(string) group_vec[j];	if( H.compare("TC3")==0)		{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="20220119_Kontrolle_Rahmen::PIM1" && group_vec[j]=="BFM")			{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="20220119_Kontrolle_Rahmen::PIM1" && group_vec[j]=="Draht")		{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="20220119_Kontrolle_Rahmen::PIM1" && group_vec[j]=="Flaeche")		{yes=1;}}	n++;
	if(i==n+1)	{	if(group_vec[j].Contains("Panel9O"))		{yes=1;}}	n++;
	if(i==n+1)	{	if(group_vec[j].Contains("Panel10O"))		{yes=1;}}	n++;
	if(i==n+1)	{	if(group_vec[j].Contains("Panel11O"))		{yes=1;}}	n++;
	if(i==n+1)	{	if(group_vec[j].Contains("Panel12O"))		{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="20210430::PIM1" && group_vec[j].Contains("Leiter3-"))										{yes=1;}
					if(frame_vec[j]=="20210601-_Aufmasse_MUSE::PIM1" && group_vec[j].Contains("Leiter3-"))						{yes=1;}
					if(frame_vec[j]=="20210928_Justierung_Vakuumkammer_und_Target::PIM1" && group_vec[j].Contains("Leiter3-"))	{yes=1;}}	n++;
	if(i==n+1)	{	if(group_vec[j]==("Fenster"))																	{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="202209006_Wdh_mit_Gasdruck::Koordinatensystem_Instr2" && group_vec[j]=="BFM")	{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="202209006_Wdh_mit_Gasdruck::Koordinatensystem_Instr2" && group_vec[j]=="Flaeche")	{yes=1;}}	n++;
	if(i==n+1)	{	if((frame_vec[j]=="20200218_GVM_Targetkammer.Stp::WORLD" && group_vec[j]=="TCPVL")
					||	(frame_vec[j]=="20200218_GVM_Targetkammer.Stp::WORLD" && group_vec[j]=="TCPVL_1"))	{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="20200218_GVM_Targetkammer.Stp::WORLD" && group_vec[j]=="TCPVL_2")	{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="20200218_GVM_Targetkammer.Stp::WORLD" && group_vec[j]=="TCPVL_3")	{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="20200218_GVM_Targetkammer.Stp::WORLD" && group_vec[j]=="TCPVL_4")	{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="20200218_GVM_Targetkammer.Stp::WORLD" && group_vec[j]=="TCPVR_1")	{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="20200218_GVM_Targetkammer.Stp::WORLD" && group_vec[j]=="TCPVR_2")	{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="20200218_GVM_Targetkammer.Stp::WORLD" && group_vec[j]=="TCPVR_3")	{yes=1;}}	n++;
	if(i==n+1)	{	if(frame_vec[j]=="20200218_GVM_Targetkammer.Stp::WORLD" && group_vec[j]=="TCPVR_4")	{yes=1;}}	//n++;

*/
//	...........................................................................

	if(yes==1)
	{
		out_file_name	=	file_name_vec[j];
		out_frame		=	frame_vec[j];
		out_collection	=	collection_vec[j];
		out_group		=	group_vec[j];
		out_point		=	point_vec[j];
		out_x			=	x_vec[j];
		out_y			=	y_vec[j];
		out_z			=	z_vec[j];
		out_offp		=	offp_vec[j];
		out_offr		=	offr_vec[j];
		out_date_time	=	date_time_vec[j];

		out_tree->Fill();

	   replace( flags.begin(), flags.end(), flags[j], 1 );
	   counter++;

	   	{
			file_name_vec.erase(std::next(file_name_vec.begin(),j));
			frame_vec.erase(std::next(frame_vec.begin(),j));
			collection_vec.erase(std::next(collection_vec.begin(),j));
			group_vec.erase(std::next(group_vec.begin(),j));
			point_vec.erase(std::next(point_vec.begin(),j));
			x_vec.erase(std::next(x_vec.begin(),j));
			y_vec.erase(std::next(y_vec.begin(),j));
			z_vec.erase(std::next(z_vec.begin(),j));
			offp_vec.erase(std::next(offp_vec.begin(),j));
			offr_vec.erase(std::next(offr_vec.begin(),j));
			date_time_vec.erase(std::next(date_time_vec.begin(),j));
		}

	}




	}	//	for(j)	over all the points
	sum_classified=sum_classified+counter;
	size_after=size_before-counter;

	cout<<"	( "<<i<<" )	"<<a<<"		size_after : "<< size_after<<" 		and the classified points now : "<<counter<<"	the total classified : "<<sum_classified<<endl;


	}	//	for(i) over the known devices coordinates

//	==================================================================================




//	dropping the elements which filled in the tree from the original vectors.


/*
	for(int i=point_vec.size()-1;i>-1;i--)
	{
		if(flags[i]==1)
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
	*/
	cout<<endl;

//	storing all the rest points from the vector to a TXT file.
	ofstream out_file_7_1;
	out_file_7_1.open("out_file_7_1.txt");
	for(int i=0;i<x_vec.size();i++)
	{
		out_file_7_1<<file_name_vec[i]<<","<<frame_vec[i]<<","<<collection_vec[i]<<","<<group_vec[i]<<","<<point_vec[i]<<","<<x_vec[i]<<","<<y_vec[i]<<","<<z_vec[i]<<" ,  "<<offp_vec[i]<<","<<offr_vec[i]<<","<<date_time_vec[i]<<endl;
	}
	out_file_7_1.close();

//	.....................................................





	out_root_file->Write();
	out_root_file->Close();

	}	//	main


