
using namespace std;
ClassImp(TTimeStamp);


void TXT_2_TREE()

{

//	...........................................................................
//	1) START:	reading from the TXT files.
//	...........................................................................
/*
	NOTEs:

-	ONE_FILE_1D_vec	:	is the temprory class vector that used to store each file data.
-	ALL_DATA_2D_vec :	is the final 2D vector, which stors all the files data.
-	The calculated data in some files, they have date and time = "00:00:00" are not stored in the final 2D-vector since they are nor real survey data.
-	The input TXT files were prepared without the header, and without any empty lines because many issues appeared during reading them without this process.
-	The names of these TXT files are listed in the code. 
-	Since the frame is stored in the header, the frames are written in the code.
-	For any additional TXT files (new surveys), the same should be done.
-	All the points are stored in 1D vectors of class {file_name,frame,collection,group,point,sec,min,hr,day,month,yr,x,y,z,offp,offr}.
-	In each next blocks, working_# vectors will be define as a copies from the original 2D vector, to keep the original victors unchanged over all the code.
*/


	int namesSize = 0;
	int time_index = 8;		//	the time column number in the TXT source file.

	string concname;
	string line;

	TString collection, frame,group, point,time,file_name;
	int 	month,day,yr,hr,min,sec;
	TString flag;

	ifstream in_file;
	ofstream out_file,pre_out_file,out_loc_file;
	
	float x, y, z, offp, offr;

	vector<TString>	file_name_vec,frame_vec,collection_vec,group_vec,point_vec,tot_frame_vec;
	vector<TString>	loc_file_name_vec,loc_frame_vec,loc_collection_vec,loc_group_vec,loc_point_vec,loc_tot_frame_vec;

	vector<float>	x_vec,y_vec,z_vec,offp_vec,offr_vec;
	vector<float>	loc_x_vec,loc_y_vec,loc_z_vec,loc_offp_vec,loc_offr_vec;
	vector<int>		month_vec,day_vec,yr_vec,hr_vec,min_vec,sec_vec;

	vector<TString> loc_date_time_vec,date_time_vec;

	float PI=4*atan(1);

	class PointDef
	{
  	public:
    TString File_name,Frame,Collection,Group,Point;
    int sec,min,hr,day,month,yr;
    float x,y,z,offp,offr;
	};

	vector<PointDef> ONE_FILE_1D_vec;
	vector<vector<PointDef>> ALL_DATA_2D_vec;


	cout<<"START Block (1) : reading data from the source TXT files and store them as a class vectors ... "<<endl;

	int num_files=56+1;

	int sum=0;

	for(int f=2;f<num_files;f++)
	{
//	define the input files... 
//	the first one is ole and its frame is the old/main PSI frame, there is no need to use it, it is not a direct MUSE survey.

		if(f==1		){file_name="01_source_TXT/201200120_PIM1_Distanzberechnungen";	}
		if(f==2		){file_name="01_source_TXT/20180420_WEHA_MUSE_Kont_Target_calc";	}
		if(f==3		){file_name="01_source_TXT/20180523_WEHA_PIM1_Muse_Messungen_doku";	}
		if(f==4		){file_name="01_source_TXT/20181028_WEHA_PIM1_Muse_calc";	}
		if(f==5		){file_name="01_source_TXT/201901028_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1_calc2458544";	}
		if(f==6		){file_name="01_source_TXT/201901028_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1_GV_Panel9";	}
		if(f==7		){file_name="01_source_TXT/201901028_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1";	}
		if(f==8		){file_name="01_source_TXT/201901029_WEHA_PIM1_Muse_Grund_STT_Testareal";	}
		if(f==9		){file_name="01_source_TXT/20190510_WEHA_PIM1_Muse_Kont_Target_Insert_2";	}
		if(f==10	){file_name="01_source_TXT/20190517_WEHA_PIM1_Muse_Aufmass_GEM_calc4";	}
		if(f==11	){file_name="01_source_TXT/20190524_WEHA_PIM1_Muse_Grund_Target_calc";	}
		if(f==12	){file_name="01_source_TXT/20190719_WEHA_PIM1_Muse_Kontrollen_Areal_calc2";	}
		if(f==13	){file_name="01_source_TXT/20190719_WEHA_PIM1_Muse_Kontrollen_Areal_calc3";	}
		if(f==14	){file_name="01_source_TXT/20190719_WEHA_PIM1_Muse_Kontrollen_Areal_calc4";	}
		if(f==15	){file_name="01_source_TXT/20200108_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1_calc";	}
		if(f==16	){file_name="01_source_TXT/20200108_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1";	}
		if(f==17	){file_name="01_source_TXT/20200116_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_1_frameMUSE";	}
		if(f==18	){file_name="01_source_TXT/20200116_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_1";	}
		if(f==19	){file_name="01_source_TXT/20200116_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_frameMUSE";	}
		if(f==20	){file_name="01_source_TXT/20200116_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target";	}
		if(f==21	){file_name="01_source_TXT/20200218_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_calc20200813_frameMUSE";	}
		if(f==22	){file_name="01_source_TXT/20200218_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_calc20200813";	}
		if(f==23	){file_name="01_source_TXT/20200218_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_frameMUSE";	}
		if(f==24	){file_name="01_source_TXT/20200218_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target";	}
		if(f==25	){file_name="01_source_TXT/20200317_PIM1_Position_Panel1-13_Berechnungen";	}
		if(f==26	){file_name="01_source_TXT/20201209_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1_calc";}	
		if(f==27	){file_name="01_source_TXT/20201209_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1";	}
		if(f==28	){file_name="01_source_TXT/20210430_WEHA_PIM1_Muse_Target";	}
		if(f==29	){file_name="01_source_TXT/20210601_WEHA_PIM1_Muse_Target_calc_frameMUSE";	}
		if(f==30	){file_name="01_source_TXT/20210601_WEHA_PIM1_Muse_Target_calc";	}
		if(f==31	){file_name="01_source_TXT/20210601_WEHA_PIM1_Muse_Target_frameMUSE";	}
		if(f==32	){file_name="01_source_TXT/20210601_WEHA_PIM1_Muse_Target";	}
		if(f==33	){file_name="01_source_TXT/20210928_WEHA_PIM1_Muse_Target";	}
		if(f==34	){file_name="01_source_TXT/20220118_WEHA_PIM1_Muse_STT-and-BMbars_only";	}
		if(f==35	){file_name="01_source_TXT/20220118_WEHA_PIM1_Muse";	}
		if(f==36	){file_name="01_source_TXT/20220223_WEHA_PIM1_Muse_calc2";	}
		if(f==37	){file_name="01_source_TXT/20220223_WEHA_PIM1_Muse";	}
		if(f==38	){file_name="01_source_TXT/20220517_WEHA_PIM1_Muse_calc_relabeled_target-movement-only";	}
		if(f==39	){file_name="01_source_TXT/20220517_WEHA_PIM1_Muse_calc_relabeled_target-only";	}
		if(f==40	){file_name="01_source_TXT/20220517_WEHA_PIM1_Muse_calc";	}
		if(f==41	){file_name="01_source_TXT/20220810_WEHA_PIM1_Muse_Procedure";	}
		if(f==42	){file_name="01_source_TXT/20220830_WEHA_PIM1_Muse_Grundverm_transf";	}
		if(f==43	){file_name="01_source_TXT/20220831_WEHA_PIM1_Muse_Grundverm";}
		if(f==44	){file_name="01_source_TXT/20220906_WEHA_PIM1_Muse_Grundverm";	}
		if(f==45	){file_name="01_source_TXT/20220907_WEHA_PIM1_Muse_Grundverm";	}
		if(f==46	){file_name="01_source_TXT/20220913_WEHA_PIM1_Muse_Grundverm_red_ohne_Modell";	}
		if(f==47	){file_name="01_source_TXT/20220914_WEHA_PIM1_Muse_Grundverm_Sensor_VETO_annotated";	}
		if(f==48	){file_name="01_source_TXT/20220914_WEHA_PIM1_Muse_Grundverm_Sensor_VETO";	}
		if(f==49	){file_name="01_source_TXT/20230117_WEHA_PiM1_Muse_Gestell";	}
		if(f==50	){file_name="01_source_TXT/20230118_WEHA_PiM1_Muse_Gestell";	}
		if(f==51	){file_name="01_source_TXT/20230119_WEHA_PiM1_Muse_Gestell";	}
		if(f==52	){file_name="01_source_TXT/20230120_WEHA_PiM1_Muse_Gestell_PiM1";	}
		if(f==53	){file_name="01_source_TXT/20230612_WEHA_PiM1_Muse_Grund_TCPV";	}
		if(f==54	){file_name="01_source_TXT/20230613_WEHA_PiM1_Muse_Kont_Targetpositionen";	}
		if(f==55	){file_name="01_source_TXT/20230614_WEHA_PiM1_Muse_Kont_STT";	}
		if(f==56	){file_name="01_source_TXT/20230914_WEHA_PiM1_Muse_Kont_STT";	}
//	.....................................................
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
				while (getline (ss,item, delim)) {	items.push_back(item);		}

				flag = (TString) items[0];
					int non_comment_flag=1;
					if(flag.Contains("//"))	{non_comment_flag=0;}	//	also, it is a comment line, nothing to be read

				time=TString(items[time_index]);
					int time_flag=1;
					if( time.Contains("00:00:00")){ time_flag=0; }	//	theoritical measurments values
					if(time.Contains(" "))	{	time.ReplaceAll(" ","");	}
					if(time.Contains(":"))	{	time.ReplaceAll(":","");	}
					if(time.Contains("/"))	{	time.ReplaceAll("/","");	}




				if(non_comment_flag==1 && time_flag==1 && line_flag==1)	//	NOW, we can read data from the line & real measurements
				{	

				month=stoi(time(0,2));
				day=stoi(time(2,2));
				yr=stoi(time(4,2));
				hr=stoi(time(6,2));
				min=stoi(time(8,2));
				sec=stoi(time(10,2));

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
						("Ecken") ||	tot_frame_name.Contains("Ebene") ||	tot_frame_name.Contains("scan") ||	tot_frame_name.Contains("Lokal")
						 ||	tot_frame_name.Contains("Geometrie") ||	tot_frame_name.Contains("Aufmasse") ||	tot_frame_name.Contains("calc");

						int local_flag=0;

//	the local measurements (local_flag=1) will be stored separately, the "muse" measurements (local_flag=0).

						if(local_measurements){local_flag=1;}	//	finding the LOCAL measurements

					local_flag=0;

						if(local_flag==0)	//	NON-Local measuremants
						{
//	storing the same non-local total_frame data in the same 1D vector, which will be imbedded latter within a 2D vector.

						ONE_FILE_1D_vec.push_back({file_name,frame,collection,group,point,sec,min,hr,day,month,yr,x,y,z,offp,offr});
						}	//	if(local_flag==0)		NON-Local measuremants


				}			//	if(comment_flag==1) the line contains useful data
			}				//	if(line_flag==1) ...	the line contains data, any data
		}					//	while the in_file is open
	in_file.close();		//	closing the input TXT file in progress


	ALL_DATA_2D_vec.push_back(ONE_FILE_1D_vec);

//	cout<<"ONE_FILE_1D_vec.size = "<<ONE_FILE_1D_vec.size()<<"	|	"<<"ALL_DATA_2D_vec.size = "<<ALL_DATA_2D_vec.size();

	sum=sum+ONE_FILE_1D_vec.size();
	ONE_FILE_1D_vec.clear();

//	cout<<"	|	the ONE_FILE_1D_vec.size NOW = "<<ONE_FILE_1D_vec.size()<<"	|	the 1D_vec in the 2D_vec size : "<<ALL_DATA_2D_vec[ALL_DATA_2D_vec.size()-1].size()<<"	|	and thew total number of points : "<<sum<<endl;


	}	//	for(f)

//	...........................................................................
//	1) END:	reading from the TXT files.
//	...........................................................................




//	...........................................................................
//	2) START: classifying data in trees.
//	...........................................................................

	cout<<"START Block (1) : reading data from the 2D-vector and classifying them in the out_tree in a root file. ... "<<endl;

	TFile *out_root_file	=	new TFile("measurements.root","RECREATE");
	TTree *out_tree 		=	new TTree("measurements","");

	vector<vector<PointDef>>	working_2_ALL_DATA;
	working_2_ALL_DATA=ALL_DATA_2D_vec;

	PointDef out_Points;

	for(int i=0;i<working_2_ALL_DATA.size();i++)
	{
		for(int j=0;j<working_2_ALL_DATA[i].size();j++)
		{
			if(i==0)
			{

				TTree *out_tree =	new TTree("Standpunkt1","");
				out_tree		->	Branch("Standpunkt1",&out_Points);				
				out_Points	=	working_2_ALL_DATA[i][j];	
				
				if(working_2_ALL_DATA[i][j].Collection=="Standpunkt1")	{	out_tree->Fill();	}





			}	//	if(i==0)
		}		//	for(j)
	}			//	for(i)



//	...........................................................................
//	2) END: reading from the TXT files.
//	...........................................................................



out_root_file->Write();
out_root_file->Close();




}	//	main



