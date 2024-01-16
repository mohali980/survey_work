ClassImp(TTimeStamp);
using namespace std;

void coordconv_8()
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
//	----------------------------------------------------------------------------
//	1) START : ..............	reading data from TXT files	...................
//	----------------------------------------------------------------------------

//	Block (1)
//	1) The input TXT files were prepared without the header, and without any empty lines because many issues appeared during reading them without this process.
//	2) The names of these TXT files are listed in the code. 
//	3) Since the frame is stored in the header, the frames are written in the code.
//	*  For any additional TXT files, the same should be done.
//	4) All the points are stored in 1D vectors.{file_names, frames, collection, group, point, x, y, z, offp, offr, date_time}, and use these vectors in the next blocks.

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
						("Ecken") ||	tot_frame_name.Contains("Ebene") ||	tot_frame_name.Contains("scan") ||	tot_frame_name.Contains("Lokal")
						 ||	tot_frame_name.Contains("Geometrie");

						

						int local_flag=0;

//	the local measurements (local_flag=1) will be stored separately, the "muse" measurements (local_flag=0).

						if(local_measurements){local_flag=1;}	//	finding the LOCAL measurements


					//	local_flag=0;	//	this is just to store everything regardless the local measurements.


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
//	----------------------------------------------------------------------------
//	1) END : ................	reading data from TXT files	...................
//	----------------------------------------------------------------------------



//	.....................................................
//	storing all the points from the vector to a TXT file. All the points ~255031 points from about 56 TXT files.

	ofstream out_file_8_0;
	out_file_8_0.open("out_file_8_0.txt");
	for(int i=0;i<x_vec.size();i++)
	{
		out_file_8_0<<file_name_vec[i]<<","<<frame_vec[i]<<","<<collection_vec[i]<<","<<group_vec[i]<<","<<point_vec[i]<<","<<x_vec[i]<<","<<y_vec[i]<<","<<z_vec[i]<<" ,  "<<offp_vec[i]<<","<<offr_vec[i]<<","<<date_time_vec[i]<<endl;
	}
	out_file_8_0.close();
//	.....................................................



//	.....................................................
//	storing all the points from the vector to a TXT file. All the points ~255031 points from about 56 TXT files.

	ofstream out_loc_file_8_0;
	out_loc_file_8_0.open("out_loc_file_8_0.txt");
	for(int i=0;i<loc_x_vec.size();i++)
	{
		out_loc_file_8_0<<loc_file_name_vec[i]<<","<<loc_frame_vec[i]<<","<<loc_collection_vec[i]<<","<<loc_group_vec[i]<<","<<loc_point_vec[i]<<","<<loc_x_vec[i]<<","<<loc_y_vec[i]<<","<<loc_z_vec[i]<<" ,  "<<loc_offp_vec[i]<<","<<loc_offr_vec[i]<<","<<loc_date_time_vec[i]<<endl;
	}
	out_loc_file_8_0.close();
//	.....................................................










//	----------------------------------------------------------------------------
//	2) START :	seperating frames to vectors	................................
//	----------------------------------------------------------------------------
	cout<<"START Block (2) : seperating frames to vectors "<<endl;

	vector<float>	working_2_x_vec,working_2_y_vec,working_2_z_vec,working_2_offp_vec,working_2_offr_vec;
	vector<TString>	working_2_file_name_vec,working_2_frame_vec,working_2_collection_vec,working_2_group_vec,working_2_point_vec,working_2_date_time_vec;

	working_2_file_name_vec=file_name_vec;
	working_2_frame_vec=frame_vec;
	working_2_collection_vec=collection_vec;
	working_2_group_vec=group_vec;
	working_2_point_vec=point_vec;
	working_2_x_vec=x_vec;
	working_2_y_vec=y_vec;
	working_2_z_vec=z_vec;
	working_2_offp_vec=offp_vec;
	working_2_offr_vec=offr_vec;
	working_2_date_time_vec=date_time_vec;

	vector<vector<float>>	C_x_vec,C_y_vec,C_z_vec,C_offp_vec,C_offr_vec;
	vector<vector<TString>>	C_file_name_vec,C_frame_vec,C_collection_vec,C_group_vec,C_point_vec,C_date_time_vec;

	vector<float>	tmp_x_vec,tmp_y_vec,tmp_z_vec,tmp_offp_vec,tmp_offr_vec;
	vector<TString>	tmp_file_name_vec,tmp_frame_vec,tmp_collection_vec,tmp_group_vec,tmp_point_vec,tmp_date_time_vec;
	vector<int>	same_xyz,flags;

	float eps=1.0;

	for(int i=0;i<x_vec.size();i++)
	{
//	.......................................................
		for(int j=0;j<working_2_x_vec.size();j++)
		{
		if(fabs(working_2_x_vec[j]-x_vec[i])<eps && fabs(working_2_y_vec[j]-y_vec[i])<eps && fabs(working_2_z_vec[j]-z_vec[i])<eps && working_2_point_vec[j]==point_vec[i])
			{
				same_xyz.push_back(j);
			}
		}
//	.......................................................
	if(same_xyz.size()>2)	{	cout<<"the size before : "<<working_2_x_vec.size()<<"	";	}
//	.......................................................
	if(same_xyz.size()>2)
	{	
		for(int m=0;m<same_xyz.size();m++)
		{	
			for(int j=0;j<working_2_x_vec.size();j++)
			{
				if((working_2_frame_vec[j]==working_2_frame_vec[same_xyz[m]]) && (working_2_group_vec[j]==working_2_group_vec[same_xyz[m]]) && (working_2_collection_vec[j]==working_2_collection_vec[same_xyz[m]]) && (working_2_file_name_vec[j]==working_2_file_name_vec[same_xyz[m]]))
				{
					tmp_file_name_vec.push_back(working_2_file_name_vec[j]);
					tmp_frame_vec.push_back(working_2_frame_vec[j]);
					tmp_collection_vec.push_back(working_2_collection_vec[j]);
					tmp_group_vec.push_back(working_2_group_vec[j]);
					tmp_point_vec.push_back(working_2_point_vec[j]);
					tmp_x_vec.push_back(working_2_x_vec[j]);
					tmp_y_vec.push_back(working_2_y_vec[j]);
					tmp_z_vec.push_back(working_2_z_vec[j]);
					tmp_offp_vec.push_back(working_2_offp_vec[j]);
					tmp_offr_vec.push_back(working_2_offr_vec[j]);
					tmp_date_time_vec.push_back(working_2_date_time_vec[j]);

					flags.push_back(1);
				//	replace( flags.begin(), flags.end(), flags[j], 1 );
				}
				else{flags.push_back(0);}		//	else{flags.push_back(0);}
			}	//	for(j)
//	.......................................................
		for(int l=working_2_x_vec.size()-1;l>-1;l--)
		{
			if(flags[l]==1)
			{
				working_2_file_name_vec.erase(std::next(working_2_file_name_vec.begin(),l));
				working_2_frame_vec.erase(std::next(working_2_frame_vec.begin(),l));
				working_2_collection_vec.erase(std::next(working_2_collection_vec.begin(),l));
				working_2_group_vec.erase(std::next(working_2_group_vec.begin(),l));
				working_2_point_vec.erase(std::next(working_2_point_vec.begin(),l));
				working_2_x_vec.erase(std::next(working_2_x_vec.begin(),l));
				working_2_y_vec.erase(std::next(working_2_y_vec.begin(),l));
				working_2_z_vec.erase(std::next(working_2_z_vec.begin(),l));
				working_2_offp_vec.erase(std::next(working_2_offp_vec.begin(),l));
				working_2_offr_vec.erase(std::next(working_2_offr_vec.begin(),l));
				working_2_date_time_vec.erase(std::next(working_2_date_time_vec.begin(),l));
			}
		}	//	for(l)
//	.......................................................

		flags.clear();
		}		//	for(m)
//	...............................................

	C_file_name_vec.push_back(tmp_file_name_vec);
	C_frame_vec.push_back(tmp_frame_vec);
	C_collection_vec.push_back(tmp_collection_vec);
	C_group_vec.push_back(tmp_group_vec);
	C_point_vec.push_back(tmp_point_vec);
	C_x_vec.push_back(tmp_x_vec);
	C_y_vec.push_back(tmp_y_vec);
	C_z_vec.push_back(tmp_z_vec);
	C_offp_vec.push_back(tmp_offp_vec);
	C_offr_vec.push_back(tmp_offr_vec);
	C_date_time_vec.push_back(tmp_date_time_vec);
//	...............................................

	cout<<" ) the size after : "<<working_2_x_vec.size()<<"	| the 1-D vector size : "<<tmp_x_vec.size()<<" | the C 2-D vec size : "<<C_x_vec.size()<<endl;

	tmp_file_name_vec.clear();
	tmp_frame_vec.clear();
	tmp_collection_vec.clear();
	tmp_group_vec.clear();
	tmp_point_vec.clear();
	tmp_x_vec.clear();
	tmp_y_vec.clear();
	tmp_z_vec.clear();
	tmp_offp_vec.clear();
	tmp_offr_vec.clear();
	tmp_date_time_vec.clear();
	same_xyz.clear();
	}			//	if(same_xyz.size()>1)
	same_xyz.clear();

	}	//	for(i)

//	...............................................
//	also storing the single (non repeated) points in the last 1D vector inside the C-2D grand vector.

			for(int j=0;j<working_2_x_vec.size();j++)
			{
				if(1==1)
				{
					tmp_file_name_vec.push_back(working_2_file_name_vec[j]);
					tmp_frame_vec.push_back(working_2_frame_vec[j]);
					tmp_collection_vec.push_back(working_2_collection_vec[j]);
					tmp_group_vec.push_back(working_2_group_vec[j]);
					tmp_point_vec.push_back(working_2_point_vec[j]);
					tmp_x_vec.push_back(working_2_x_vec[j]);
					tmp_y_vec.push_back(working_2_y_vec[j]);
					tmp_z_vec.push_back(working_2_z_vec[j]);
					tmp_offp_vec.push_back(working_2_offp_vec[j]);
					tmp_offr_vec.push_back(working_2_offr_vec[j]);
					tmp_date_time_vec.push_back(working_2_date_time_vec[j]);

					flags.push_back(1);
				//	replace( flags.begin(), flags.end(), flags[j], 1 );
				}
				else{flags.push_back(0);}
				//	else{flags.push_back(0);}
			}	//	for(j)

//	...............................................
	for(int l=working_2_x_vec.size()-1;l>-1;l--)
	{
		if(flags[l]==1)
		{
			working_2_file_name_vec.erase(std::next(working_2_file_name_vec.begin(),l));
			working_2_frame_vec.erase(std::next(working_2_frame_vec.begin(),l));
			working_2_collection_vec.erase(std::next(working_2_collection_vec.begin(),l));
			working_2_group_vec.erase(std::next(working_2_group_vec.begin(),l));
			working_2_point_vec.erase(std::next(working_2_point_vec.begin(),l));
			working_2_x_vec.erase(std::next(working_2_x_vec.begin(),l));
			working_2_y_vec.erase(std::next(working_2_y_vec.begin(),l));
			working_2_z_vec.erase(std::next(working_2_z_vec.begin(),l));
			working_2_offp_vec.erase(std::next(working_2_offp_vec.begin(),l));
			working_2_offr_vec.erase(std::next(working_2_offr_vec.begin(),l));
			working_2_date_time_vec.erase(std::next(working_2_date_time_vec.begin(),l));
		}
	}	//	for(l)
//	...............................................
	flags.clear();
//	...............................................

	C_file_name_vec.push_back(tmp_file_name_vec);
	C_frame_vec.push_back(tmp_frame_vec);
	C_collection_vec.push_back(tmp_collection_vec);
	C_group_vec.push_back(tmp_group_vec);
	C_point_vec.push_back(tmp_point_vec);
	C_x_vec.push_back(tmp_x_vec);
	C_y_vec.push_back(tmp_y_vec);
	C_z_vec.push_back(tmp_z_vec);
	C_offp_vec.push_back(tmp_offp_vec);
	C_offr_vec.push_back(tmp_offr_vec);
	C_date_time_vec.push_back(tmp_date_time_vec);
//	...............................................

//	----------------------------------------------------------------------------
//	2) END :	seperating frames to vectors	................................
//	----------------------------------------------------------------------------

	vector<vector<float>>	D_x_vec,D_y_vec,D_z_vec,D_offp_vec,D_offr_vec;
	vector<vector<TString>>	D_file_name_vec,D_frame_vec,D_collection_vec,D_group_vec,D_point_vec,D_date_time_vec;

	D_file_name_vec=C_file_name_vec;
	D_frame_vec=C_frame_vec;
	D_collection_vec=C_collection_vec;
	D_group_vec=C_group_vec;
	D_point_vec=C_point_vec;
	D_x_vec=C_x_vec;
	D_y_vec=C_y_vec;
	D_z_vec=C_z_vec;
	D_offp_vec=C_offp_vec;
	D_offr_vec=C_offr_vec;
	D_date_time_vec=C_date_time_vec;

cout<<"D_vec size : "<<D_x_vec.size()<<endl;










//	----------------------------------------------------------------------------
//	3) START :	Unifying frames to the Hall fram	............................
//	----------------------------------------------------------------------------
	cout<<"START Block (3) : Unifying frames to the Hall fram. "<<endl;



//	The transformation goes through the following steps:
//	1) In the 1st Block: collecting all the points from different files and frames. Then, store them in one big vector for each parameter { file_name, frame, collection, group, point_name, x, y, z, offp, offr, date_time.

//	2) Separating all the points according to the same {frame, collection, group} and storing them in 2-D vectors.

//	3) Aligning the points to one of the hall's frames.
//		* Choosing the points' measurements in (chrome-extension://efaidnbmnnnibpcajpcglclefindmkaj/https://muse.physics.lsa.umich.edu/doku/lib/exe/fetch.php?media=converted:20181024_weha_pim1_muse_rep.pdf; page 6) to be the hall frame of reference, and store these points in a separate 1D vector.
//		* Looking for at least 3 common points in each vector within the 2D vectors with the same point_name, whatever their positions.
//		* Testing the distances between the 3 points, it should be the same in the two frames, the first is the supposed frame, and the second is from the vectors which will go through the transformation process.
//		* transformation steps:
//			1) Determining the 3 points from the primary and the secondary {A1, A2, A3} and {B1, B2, B3} frames and choosing one of them to be the origin (but not at (0,0,0)).
//			2) Draging the second frame to match the points (A1, B1) by the dr=B1-A1. Now, one point is matched.
//			3) Draging all the points in both frames to the primary origin by adding (-A1) for each point vector, in this case, the next rotations will be around the origin.
//			4) Rotating the secondary points' vectors around the common normal on the second points' vectors in both frames by the angle between them. Now, two points are matched.
//			5) Rotating the secondary points about the second points vector, by the angle between the surfaces (A2:A1:A3) and (B2:B1:B3) by finding their normals. Now, the three common points are matched, and by this step, all the points in the secondary frame are matched with the primary frame's points, but they are all framed to (0,0,0) point.
//			6) Adding the A1 vector to all the points to return the points to their original position, which is the undoing step (3).
//		*	storing the transformation parameters {dr (vector) , step_back (vector), rot_axis_1 (vector), theta_1 (float), rot_axis_2 (vector), theta_2 (float)}.


	vector<float>	final_x_vec,final_y_vec,final_z_vec,final_offp_vec,final_offr_vec;
	vector<TString>	final_file_name_vec,final_frame_vec,final_collection_vec,final_group_vec,final_point_vec,final_date_time_vec;

	TVector3	A1,A2,A3,B1,B2,B3;
	TVector3	norm_1,norm_2,norm_3,dr,rot_axis_1,rot_axis_2,step_back;
	TVector3	rot_ref_1,rot_ref_2;
	float 		dx,dy,dz,theta_1,theta_2;


	vector<float> A3_xs,A3_ys,A3_zs,B3_xs,B3_ys,B3_zs,C3_xs,C3_ys,C3_zs;

//	deterrmining some of the hall frames...

	for (int i=0;i<x_vec.size();i++)
	{
		bool hall_file_frame_flag	=(file_name_vec[i]=="20181028_WEHA_PIM1_Muse_calc" && frame_vec[i]=="20181128_Kontrollen_im_Areal::Drehzentrum-Strahl_(MUSE)");
		bool hall_coll_group_1_flag	=(collection_vec[i]=="20181024Netzerweiterung" && group_vec[i]=="Netz");
		bool hall_coll_group_2_flag	=(collection_vec[i]=="20181024Netzerweiterung" && group_vec[i]=="Netz-1");
		bool hall_coll_group_3_flag	=(collection_vec[i]=="20181024Netzerweiterung" && group_vec[i]=="Netz-2");
		bool hall_coll_group_4_flag	=(collection_vec[i]=="20181024Detektoren" && group_vec[i]=="REF");
		bool hall_frame_flag=hall_file_frame_flag && (hall_coll_group_1_flag||hall_coll_group_2_flag||hall_coll_group_3_flag||hall_coll_group_4_flag);

	if(hall_frame_flag)	
	{	
		final_file_name_vec.push_back(file_name_vec[i]);
		final_frame_vec.push_back(frame_vec[i]);
		final_collection_vec.push_back(collection_vec[i]);
		final_group_vec.push_back(group_vec[i]);
		final_point_vec.push_back(point_vec[i]);
		final_x_vec.push_back(x_vec[i]);
		final_y_vec.push_back(y_vec[i]);
		final_z_vec.push_back(z_vec[i]);
		final_offp_vec.push_back(offp_vec[i]);
		final_offr_vec.push_back(offr_vec[i]);
		final_date_time_vec.push_back(date_time_vec[i]);

	}	//	if(hall_frame_flag)
	}	//	for(i)


//	...............................................
	for(int N=0;N<5;N++)
	{
//	...............................................
	for(int i=0;i<D_x_vec.size();i++)
	{
	TString		same_point_1="000";
	TString		same_point_2="000";
	TString		same_point_3="000";

		for(int j=0;j<D_x_vec[i].size()-1;j++)	//	-1 because we don't need the last vector in the C-2D vectors, it is not a unified frame vector.
		{
			if(A3_xs.size()<4)					//	we need just 3-common points to start the transformation.

			for(int m=0;m<final_x_vec.size();m++)
			{
				if(final_point_vec[m]==D_point_vec[i][j]	)
				{	
					if(D_point_vec[i][j]!=same_point_1	&& D_point_vec[i][j]!=same_point_2	&& D_point_vec[i][j]!=same_point_3)					
					{
						A3_xs.push_back(final_x_vec[m]);	A3_ys.push_back(final_y_vec[m]);	A3_zs.push_back(final_z_vec[m]);
						B3_xs.push_back(D_x_vec[i][j]);		B3_ys.push_back(D_y_vec[i][j]);		B3_zs.push_back(D_z_vec[i][j]);

						if(A3_xs.size()==1){same_point_1=D_point_vec[i][j]; cout<<D_point_vec[i][j]<<"	"<<final_point_vec[m]<<endl;}
						if(A3_xs.size()==2){same_point_2=D_point_vec[i][j]; cout<<D_point_vec[i][j]<<"	"<<final_point_vec[m]<<endl;}
						if(A3_xs.size()==3){same_point_3=D_point_vec[i][j]; cout<<D_point_vec[i][j]<<"	"<<final_point_vec[m]<<endl;}
					}
				}
			}	//	for(m
		}		//	for(j)	the 1-D internal vectors, inside C-vectors, each contains the same-frame points.

	if(A3_xs.size()>2)		//	if the common points are 3 then we can start the transformation.
	{
			A1.SetXYZ(A3_xs[0],A3_ys[0],A3_zs[0]);
			A2.SetXYZ(A3_xs[1],A3_ys[1],A3_zs[1]);
			A3.SetXYZ(A3_xs[2],A3_ys[2],A3_zs[2]);
			B1.SetXYZ(B3_xs[0],B3_ys[0],B3_zs[0]);
			B2.SetXYZ(B3_xs[1],B3_ys[1],B3_zs[1]);
			B3.SetXYZ(B3_xs[2],B3_ys[2],B3_zs[2]);

	A3_xs.clear();	A3_ys.clear();	A3_zs.clear();
	B3_xs.clear();	B3_ys.clear();	B3_zs.clear();
	
cout<<"the 3 common points : "<<same_point_1<<" , "<<same_point_2<<" , "<<same_point_3<<endl;
cout<<"============================================================"<<endl;
cout<<i<<" )"<<endl;
//	.......................................................
	
	cout<<"coordenates before transformations :"<<endl;
	cout<<A1.X()<<"	|	"<<A1.Y()<<"	|	"<<A1.Z()<<endl;
	cout<<B1.X()<<"	|	"<<B1.Y()<<"	|	"<<B1.Z()<<endl;
	cout<<".............."<<endl;
	cout<<A2.X()<<"	|	"<<A2.Y()<<"	|	"<<A2.Z()<<endl;
	cout<<B2.X()<<"	|	"<<B2.Y()<<"	|	"<<B2.Z()<<endl;
	cout<<".............."<<endl;
	cout<<A3.X()<<"	|	"<<A3.Y()<<"	|	"<<A3.Z()<<endl;
	cout<<B3.X()<<"	|	"<<B3.Y()<<"	|	"<<B3.Z()<<endl;
	cout<<endl;
	cout<<"A12 length : "<<(A2-A1).Mag()<<"	|	A13 length : "<<(A3-A1).Mag()<<"	|	A23 length : "<<(A3-A2).Mag()<<endl;
	cout<<"B12 length : "<<(B2-B1).Mag()<<"	|	B13 length : "<<(B3-B1).Mag()<<"	|	B23 length : "<<(B3-B2).Mag()<<endl;
	cout<<"------------------------------------------"<<endl;

	float A12_dist,A13_dist,A23_dist,B12_dist,B13_dist,B23_dist;

	A12_dist=(A2-A1).Mag();	A13_dist=(A3-A1).Mag();	A23_dist=(A2-A3).Mag();
	B12_dist=(B2-B1).Mag();	B13_dist=(B3-B1).Mag();	B23_dist=(B2-B3).Mag();

	bool off_dist= (fabs(A12_dist-B12_dist) + fabs(A13_dist-B13_dist) + fabs(A23_dist-B23_dist))<10;


	if(off_dist)
	{

//	1) finding the 1st transformation : the draging dx,dy,dz.

		dx	=	B1.X()-A1.X();
		dy	=	B1.Y()-A1.Y();
		dz	=	B1.Z()-A1.Z();

		dr.SetXYZ(dx,dy,dz);

		B1=B1-dr;	B2=B2-dr;	B3=B3-dr;
//	.......................................................
	cout<<"coordenates after 1st transformation :"<<endl;

	cout<<A1.X()<<"	|	"<<A1.Y()<<"	|	"<<A1.Z()<<endl;
	cout<<B1.X()<<"	|	"<<B1.Y()<<"	|	"<<B1.Z()<<endl;
	cout<<".............."<<endl;
	cout<<A2.X()<<"	|	"<<A2.Y()<<"	|	"<<A2.Z()<<endl;
	cout<<B2.X()<<"	|	"<<B2.Y()<<"	|	"<<B2.Z()<<endl;
	cout<<".............."<<endl;
	cout<<A3.X()<<"	|	"<<A3.Y()<<"	|	"<<A3.Z()<<endl;
	cout<<B3.X()<<"	|	"<<B3.Y()<<"	|	"<<B3.Z()<<endl;
	cout<<endl;
	cout<<"A12 length : "<<(A2-A1).Mag()<<"	|	A13 length : "<<(A3-A1).Mag()<<"	|	A23 length : "<<(A3-A2).Mag()<<endl;
	cout<<"B12 length : "<<(B2-B1).Mag()<<"	|	B13 length : "<<(B3-B1).Mag()<<"	|	B23 length : "<<(B3-B2).Mag()<<endl;
	cout<<"------------------------------------------"<<endl;

//	2) sending A1,B1 to the origin, the rotatin is around a vector passing through the origin.

	step_back=A1;

	A1=A1-step_back;	A2=A2-step_back;	A3=A3-step_back;
	B1=B1-step_back;	B2=B2-step_back;	B3=B3-step_back;

//	.......................................................
	cout<<"coordenates after 2nd transformation :"<<endl;

	cout<<A1.X()<<"	|	"<<A1.Y()<<"	|	"<<A1.Z()<<endl;
	cout<<B1.X()<<"	|	"<<B1.Y()<<"	|	"<<B1.Z()<<endl;
	cout<<".............."<<endl;
	cout<<A2.X()<<"	|	"<<A2.Y()<<"	|	"<<A2.Z()<<endl;
	cout<<B2.X()<<"	|	"<<B2.Y()<<"	|	"<<B2.Z()<<endl;
	cout<<".............."<<endl;
	cout<<A3.X()<<"	|	"<<A3.Y()<<"	|	"<<A3.Z()<<endl;
	cout<<B3.X()<<"	|	"<<B3.Y()<<"	|	"<<B3.Z()<<endl;
	cout<<endl;
	cout<<"A12 length : "<<(A2-A1).Mag()<<"	|	A13 length : "<<(A3-A1).Mag()<<"	|	A23 length : "<<(A3-A2).Mag()<<endl;
	cout<<"B12 length : "<<(B2-B1).Mag()<<"	|	B13 length : "<<(B3-B1).Mag()<<"	|	B23 length : "<<(B3-B2).Mag()<<endl;
	cout<<"------------------------------------------"<<endl;

//	3) finding the 2nd transformation : rotating by theta_1.

	norm_1	=	(B2).Cross(A2);
	theta_1	=	(B2).Angle(A2);

	rot_axis_1=norm_1;
	cout<<"theta_1 : "<<(180/PI)*theta_1;
	B1.Rotate(theta_1,rot_axis_1);	B2.Rotate(theta_1,rot_axis_1);	B3.Rotate(theta_1,rot_axis_1);
//	.......................................................
	cout<<"coordenates after 3rd transformation :"<<endl;

	cout<<A1.X()<<"	|	"<<A1.Y()<<"	|	"<<A1.Z()<<endl;
	cout<<B1.X()<<"	|	"<<B1.Y()<<"	|	"<<B1.Z()<<endl;
	cout<<".............."<<endl;
	cout<<A2.X()<<"	|	"<<A2.Y()<<"	|	"<<A2.Z()<<endl;
	cout<<B2.X()<<"	|	"<<B2.Y()<<"	|	"<<B2.Z()<<endl;
	cout<<".............."<<endl;
	cout<<A3.X()<<"	|	"<<A3.Y()<<"	|	"<<A3.Z()<<endl;
	cout<<B3.X()<<"	|	"<<B3.Y()<<"	|	"<<B3.Z()<<endl;
	cout<<endl;
	cout<<"A12 length : "<<(A2-A1).Mag()<<"	|	A13 length : "<<(A3-A1).Mag()<<"	|	A23 length : "<<(A3-A2).Mag()<<endl;
	cout<<"B12 length : "<<(B2-B1).Mag()<<"	|	B13 length : "<<(B3-B1).Mag()<<"	|	B23 length : "<<(B3-B2).Mag()<<endl;
	cout<<"------------------------------------------"<<endl;
//	.......................................................
//	4) finding the 4rth transformation : rotating by theta_1.

	norm_2	=	(B2).Cross(B3);
	norm_3	=	(A2).Cross(A3);
	theta_2	=	norm_2.Angle(norm_3);

	rot_axis_2=B2;
	cout<<"theta_2 : "<<(180/PI)*theta_2;

	B1.Rotate(-theta_2,rot_axis_2);	B2.Rotate(-theta_2,rot_axis_2);	B3.Rotate(-theta_2,rot_axis_2);

//	.......................................................
	cout<<"coordenates after 4th transformation :"<<endl;

	cout<<A1.X()<<"	|	"<<A1.Y()<<"	|	"<<A1.Z()<<endl;
	cout<<B1.X()<<"	|	"<<B1.Y()<<"	|	"<<B1.Z()<<endl;
	cout<<".............."<<endl;
	cout<<A2.X()<<"	|	"<<A2.Y()<<"	|	"<<A2.Z()<<endl;
	cout<<B2.X()<<"	|	"<<B2.Y()<<"	|	"<<B2.Z()<<endl;
	cout<<".............."<<endl;
	cout<<A3.X()<<"	|	"<<A3.Y()<<"	|	"<<A3.Z()<<endl;
	cout<<B3.X()<<"	|	"<<B3.Y()<<"	|	"<<B3.Z()<<endl;
	cout<<endl;
	cout<<"A12 length : "<<(A2-A1).Mag()<<"	|	A13 length : "<<(A3-A1).Mag()<<"	|	A23 length : "<<(A3-A2).Mag()<<endl;
	cout<<"B12 length : "<<(B2-B1).Mag()<<"	|	B13 length : "<<(B3-B1).Mag()<<"	|	B23 length : "<<(B3-B2).Mag()<<endl;
	cout<<"------------------------------------------"<<endl;

//	.......................................................
//	5) returning to the first frame (A1-frame).
	A1=A1+step_back;	A2=A2+step_back;	A3=A3+step_back;
	B1=B1+step_back;	B2=B2+step_back;	B3=B3+step_back;
//	.......................................................
	cout<<"coordenates after 5th transformation :"<<endl;

	cout<<A1.X()<<"	|	"<<A1.Y()<<"	|	"<<A1.Z()<<endl;
	cout<<B1.X()<<"	|	"<<B1.Y()<<"	|	"<<B1.Z()<<endl;
	cout<<".............."<<endl;
	cout<<A2.X()<<"	|	"<<A2.Y()<<"	|	"<<A2.Z()<<endl;
	cout<<B2.X()<<"	|	"<<B2.Y()<<"	|	"<<B2.Z()<<endl;
	cout<<".............."<<endl;
	cout<<A3.X()<<"	|	"<<A3.Y()<<"	|	"<<A3.Z()<<endl;
	cout<<B3.X()<<"	|	"<<B3.Y()<<"	|	"<<B3.Z()<<endl;
	cout<<endl;
	cout<<"A12 length : "<<(A2-A1).Mag()<<"	|	A13 length : "<<(A3-A1).Mag()<<"	|	A23 length : "<<(A3-A2).Mag()<<endl;
	cout<<"B12 length : "<<(B2-B1).Mag()<<"	|	B13 length : "<<(B3-B1).Mag()<<"	|	B23 length : "<<(B3-B2).Mag()<<endl;
	cout<<"------------------------------------------"<<endl;

//	.......................................................
//	start transforming all the points inside the vector
	cout<<"Transforming the frame # ("<<i<<") to the hall frame : "<<endl;

	TVector3 tmp_vec_point;

	for(int j=0;j<D_x_vec[i].size()-1;j++)	//	-1 because we don't need the last vector in the C-2D vectors, it is not a unified frame vector.
	{
		tmp_vec_point.SetXYZ(D_x_vec[i][j],D_y_vec[i][j],D_z_vec[i][j]);

		tmp_vec_point=tmp_vec_point-dr;

		tmp_vec_point=tmp_vec_point-step_back;

		tmp_vec_point.Rotate(theta_1,rot_axis_1);

		tmp_vec_point.Rotate(-theta_2,rot_axis_2);

	//	TEMPRORY PROCESS to aligne with the frame, it should be removed later:
	//	tmp_vec_point.RotateX(-PI/2);
	//	tmp_vec_point=0.01*tmp_vec_point;	

		tmp_vec_point=tmp_vec_point+step_back;

		final_file_name_vec.push_back(D_file_name_vec[i][j]+"trans");
		final_frame_vec.push_back(D_frame_vec[i][j]+"trans");
		final_collection_vec.push_back(D_collection_vec[i][j]+"trans");
		final_group_vec.push_back(D_group_vec[i][j]+"trans");
		final_point_vec.push_back(D_point_vec[i][j]);
		final_x_vec.push_back(tmp_vec_point.X());
		final_y_vec.push_back(tmp_vec_point.Y());
		final_z_vec.push_back(tmp_vec_point.Z());
		final_offp_vec.push_back(D_offp_vec[i][j]);
		final_offr_vec.push_back(D_offr_vec[i][j]);
		final_date_time_vec.push_back(D_date_time_vec[i][j]);

//	.......................................................
				D_file_name_vec[i].erase(std::next(D_file_name_vec[i].begin(),j));
				D_frame_vec[i].erase(std::next(D_frame_vec[i].begin(),j));
				D_collection_vec[i].erase(std::next(D_collection_vec[i].begin(),j));
				D_group_vec[i].erase(std::next(D_group_vec[i].begin(),j));
				D_point_vec[i].erase(std::next(D_point_vec[i].begin(),j));
				D_x_vec[i].erase(std::next(D_x_vec[i].begin(),j));
				D_y_vec[i].erase(std::next(D_y_vec[i].begin(),j));
				D_z_vec[i].erase(std::next(D_z_vec[i].begin(),j));
				D_offp_vec[i].erase(std::next(D_offp_vec[i].begin(),j));
				D_offr_vec[i].erase(std::next(D_offr_vec[i].begin(),j));
				D_date_time_vec[i].erase(std::next(D_date_time_vec[i].begin(),j));
//	.......................................................


	}	//	for(j)



	}	//	if(off_dist)
	else
	{
		cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
		cout<<"++  THE DISTANCE BETWEEN THE 3 POINTS IN THE PRIMARY FRAME IS NOT THE SAME AS THEM IN THE SECONDARY ONE!!!  ++"<<endl;
		cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	}

	}	//	if(A3_xs.size()>2)

	else
		{
			cout<<"*********************************************************************************"<<endl;
			cout<<"the sub-vectors ("<<i<<"), which contains ("<<D_x_vec[i].size()<<") elements doesn't aligned from the ("<<N+1<<") (st/nd/rd/th) time."<<endl;
			cout<<"*********************************************************************************"<<endl;
		}

	}			//	for(i)	the 2-D C-vectors
//	...............................................

	cout<<endl;
	cout<<endl;
	cout<<final_x_vec.size();
	cout<<endl;
	cout<<endl;


//	...............................................
}	//	for(N)
//	...............................................






//	.....................................................
//	storing all the points from the vector to a TXT file.
	ofstream out_file_8_3;
	out_file_8_3.open("out_file_8_3.txt");
	for(int i=0;i<final_x_vec.size();i++)
	{
		out_file_8_3<<final_file_name_vec[i]<<","<<final_frame_vec[i]<<","<<final_collection_vec[i]<<","<<final_group_vec[i]<<","<<final_point_vec[i]<<","<<final_x_vec[i]<<","<<final_y_vec[i]<<","<<final_z_vec[i]<<" ,  "<<final_offp_vec[i]<<","<<final_offr_vec[i]<<","<<final_date_time_vec[i]<<endl;
	}
	out_file_8_3.close();
//	.....................................................



//	----------------------------------------------------------------------------
//	3) END :	Unifying frames to the Hall fram	............................
//	----------------------------------------------------------------------------







	cout<<"================================================="<<final_x_vec.size()<<endl;

	vector<TString>	working_4_file_name_vec,working_4_frame_vec,working_4_collection_vec,working_4_group_vec,working_4_point_vec,working_4_date_time_vec;
	vector<float>	working_4_x_vec,working_4_y_vec,working_4_z_vec,working_4_offp_vec,working_4_offr_vec;

		working_4_file_name_vec=final_file_name_vec;
		working_4_frame_vec=final_frame_vec;
		working_4_collection_vec=final_collection_vec;
		working_4_group_vec=final_group_vec;
		working_4_point_vec=final_point_vec;
		working_4_x_vec=final_x_vec;
		working_4_y_vec=final_y_vec;
		working_4_z_vec=final_z_vec;
		working_4_offp_vec=final_offp_vec;
		working_4_offr_vec=final_offr_vec;
		working_4_date_time_vec=final_date_time_vec;

//	----------------------------------------------------------------------------
//	4) START :	Storing data in root file according to point group names.     ..
//	----------------------------------------------------------------------------

	TString		out_file_name,out_frame,out_collection,out_group,out_point,out_date_time;
	float 		out_x,out_y,out_z,out_offp,out_offr;


	vector<TString> AAA;


//	.............................................................................
	TFile *	out_root_file	=	new TFile("points_8.root","RECREATE");
//	.............................................................................
			TTree *out_non_classified_tree	=	new TTree("non_classified","");
			TTree *out_PA5_tree		=	new TTree("PA5","");
			TTree *out_PA6_tree		=	new TTree("PA6","");
			TTree *out_PA7_tree		=	new TTree("PA7","");
			TTree *out_PA8_tree		=	new TTree("PA8","");
			TTree *out_TA_tree		=	new TTree("TA","");
			TTree *out_TC_tree		=	new TTree("TC","");
			TTree *out_R_tree		=	new TTree("R","");
			TTree *out_O_tree		=	new TTree("O","");
			TTree *out_U_tree		=	new TTree("U","");
			TTree *out_PIM1_tree	=	new TTree("PIM1","");
			TTree *out_H_tree		=	new TTree("H","");
			TTree *out_G_tree		=	new TTree("G","");
			TTree *out_UK_tree		=	new TTree("UK","");
			TTree *out_TG_tree		=	new TTree("TG","");
			TTree *out_Panel_1_tree	=	new TTree("Panel_1","");
			TTree *out_Panel_5_tree	=	new TTree("Panel_5","");
			TTree *out_Panel_6_tree	=	new TTree("Panel_6","");
			TTree *out_M_tree		=	new TTree("M","");
			TTree *out_PA6_M_tree	=	new TTree("PA6_M","");
			TTree *out_Kante_tree	=	new TTree("Kante","");
			TTree *out_Target_tree	=	new TTree("Target","");
			TTree *out_EC_tree		=	new TTree("EC","");
			TTree *out_Rot_tree		=	new TTree("Rot","");
			TTree *out_HP_tree		=	new TTree("HP","");
			TTree *out_Turning_center_check_trans_tree		=	new TTree("Turning_center_check_trans(Drehzentrumchecktrans)","");

	basic_string<char> a ;

			vector<TString> trees;
			trees.push_back("PA5");	trees.push_back("PA6");	trees.push_back("PA7");	trees.push_back("TA");
			trees.push_back("TC");	trees.push_back("R");	trees.push_back("O");	trees.push_back("U");
			trees.push_back("PIM1");trees.push_back("H");	trees.push_back("G");	trees.push_back("UK");
			trees.push_back("TG");	trees.push_back("Panel_1");	trees.push_back("Panel_5");	trees.push_back("Panel_6");
			trees.push_back("M");	trees.push_back("PA6_M");	trees.push_back("Kante");	trees.push_back("Target");
			trees.push_back("EC");	trees.push_back("Rot");	trees.push_back("HP");	trees.push_back("Turning_center_check_trans(Drehzentrumchecktrans)");

	
//	.....................................................
//	storing all the trees' names from the vector to a TXT file.
	ofstream out_trees_names_8;
	out_trees_names_8.open("trees_file_8.txt");
	for(int k=0;k<trees.size();k++)
	{
		out_trees_names_8<<trees[k]<<endl;
	}
	out_trees_names_8.close();
//	.....................................................




	bool tmp_tag;




		//..................................................................

			out_Turning_center_check_trans_tree	->	Branch("file_name",&out_file_name);
			out_Turning_center_check_trans_tree	->	Branch("frame",&out_frame);
			out_Turning_center_check_trans_tree	->	Branch("collection",&out_collection);
			out_Turning_center_check_trans_tree	->	Branch("group",&out_group);
			out_Turning_center_check_trans_tree	->	Branch("point",&out_point);
			out_Turning_center_check_trans_tree	->	Branch("x",&out_x);
			out_Turning_center_check_trans_tree	->	Branch("y",&out_y);
			out_Turning_center_check_trans_tree	->	Branch("z",&out_z);
			out_Turning_center_check_trans_tree	->	Branch("offp",&out_offp);
			out_Turning_center_check_trans_tree	->	Branch("offr",&out_offr);
			out_Turning_center_check_trans_tree	->	Branch("date_time",&out_date_time);

			out_PA5_tree	->	Branch("file_name",&out_file_name);
			out_PA5_tree	->	Branch("frame",&out_frame);
			out_PA5_tree	->	Branch("collection",&out_collection);
			out_PA5_tree	->	Branch("group",&out_group);
			out_PA5_tree	->	Branch("point",&out_point);
			out_PA5_tree	->	Branch("x",&out_x);
			out_PA5_tree	->	Branch("y",&out_y);
			out_PA5_tree	->	Branch("z",&out_z);
			out_PA5_tree	->	Branch("offp",&out_offp);
			out_PA5_tree	->	Branch("offr",&out_offr);
			out_PA5_tree	->	Branch("date_time",&out_date_time);
			
			out_PA6_tree	->	Branch("file_name",&out_file_name);
			out_PA6_tree	->	Branch("frame",&out_frame);
			out_PA6_tree	->	Branch("collection",&out_collection);
			out_PA6_tree	->	Branch("group",&out_group);
			out_PA6_tree	->	Branch("point",&out_point);
			out_PA6_tree	->	Branch("x",&out_x);
			out_PA6_tree	->	Branch("y",&out_y);
			out_PA6_tree	->	Branch("z",&out_z);
			out_PA6_tree	->	Branch("offp",&out_offp);
			out_PA6_tree	->	Branch("offr",&out_offr);
			out_PA6_tree	->	Branch("date_time",&out_date_time);		
		
			out_PA7_tree	->	Branch("file_name",&out_file_name);
			out_PA7_tree	->	Branch("frame",&out_frame);
			out_PA7_tree	->	Branch("collection",&out_collection);
			out_PA7_tree	->	Branch("group",&out_group);
			out_PA7_tree	->	Branch("point",&out_point);
			out_PA7_tree	->	Branch("x",&out_x);
			out_PA7_tree	->	Branch("y",&out_y);
			out_PA7_tree	->	Branch("z",&out_z);
			out_PA7_tree	->	Branch("offp",&out_offp);
			out_PA7_tree	->	Branch("offr",&out_offr);
			out_PA7_tree	->	Branch("date_time",&out_date_time);		

			out_PA8_tree	->	Branch("file_name",&out_file_name);
			out_PA8_tree	->	Branch("frame",&out_frame);
			out_PA8_tree	->	Branch("collection",&out_collection);
			out_PA8_tree	->	Branch("group",&out_group);
			out_PA8_tree	->	Branch("point",&out_point);
			out_PA8_tree	->	Branch("x",&out_x);
			out_PA8_tree	->	Branch("y",&out_y);
			out_PA8_tree	->	Branch("z",&out_z);
			out_PA8_tree	->	Branch("offp",&out_offp);
			out_PA8_tree	->	Branch("offr",&out_offr);
			out_PA8_tree	->	Branch("date_time",&out_date_time);		

			out_Rot_tree	->	Branch("file_name",&out_file_name);
			out_Rot_tree	->	Branch("frame",&out_frame);
			out_Rot_tree	->	Branch("collection",&out_collection);
			out_Rot_tree	->	Branch("group",&out_group);
			out_Rot_tree	->	Branch("point",&out_point);
			out_Rot_tree	->	Branch("x",&out_x);
			out_Rot_tree	->	Branch("y",&out_y);
			out_Rot_tree	->	Branch("z",&out_z);
			out_Rot_tree	->	Branch("offp",&out_offp);
			out_Rot_tree	->	Branch("offr",&out_offr);
			out_Rot_tree	->	Branch("date_time",&out_date_time);		
			
			out_TA_tree	->	Branch("file_name",&out_file_name);
			out_TA_tree	->	Branch("frame",&out_frame);
			out_TA_tree	->	Branch("collection",&out_collection);
			out_TA_tree	->	Branch("group",&out_group);
			out_TA_tree	->	Branch("point",&out_point);
			out_TA_tree	->	Branch("x",&out_x);
			out_TA_tree	->	Branch("y",&out_y);
			out_TA_tree	->	Branch("z",&out_z);
			out_TA_tree	->	Branch("offp",&out_offp);
			out_TA_tree	->	Branch("offr",&out_offr);
			out_TA_tree	->	Branch("date_time",&out_date_time);		
			
			out_EC_tree	->	Branch("file_name",&out_file_name);
			out_EC_tree	->	Branch("frame",&out_frame);
			out_EC_tree	->	Branch("collection",&out_collection);
			out_EC_tree	->	Branch("group",&out_group);
			out_EC_tree	->	Branch("point",&out_point);
			out_EC_tree	->	Branch("x",&out_x);
			out_EC_tree	->	Branch("y",&out_y);
			out_EC_tree	->	Branch("z",&out_z);
			out_EC_tree	->	Branch("offp",&out_offp);
			out_EC_tree	->	Branch("offr",&out_offr);
			out_EC_tree	->	Branch("date_time",&out_date_time);		
		
			out_TC_tree	->	Branch("file_name",&out_file_name);
			out_TC_tree	->	Branch("frame",&out_frame);
			out_TC_tree	->	Branch("collection",&out_collection);
			out_TC_tree	->	Branch("group",&out_group);
			out_TC_tree	->	Branch("point",&out_point);
			out_TC_tree	->	Branch("x",&out_x);
			out_TC_tree	->	Branch("y",&out_y);
			out_TC_tree	->	Branch("z",&out_z);
			out_TC_tree	->	Branch("offp",&out_offp);
			out_TC_tree	->	Branch("offr",&out_offr);
			out_TC_tree	->	Branch("date_time",&out_date_time);		
			
			out_R_tree	->	Branch("file_name",&out_file_name);
			out_R_tree	->	Branch("frame",&out_frame);
			out_R_tree	->	Branch("collection",&out_collection);
			out_R_tree	->	Branch("group",&out_group);
			out_R_tree	->	Branch("point",&out_point);
			out_R_tree	->	Branch("x",&out_x);
			out_R_tree	->	Branch("y",&out_y);
			out_R_tree	->	Branch("z",&out_z);
			out_R_tree	->	Branch("offp",&out_offp);
			out_R_tree	->	Branch("offr",&out_offr);
			out_R_tree	->	Branch("date_time",&out_date_time);		
			
			out_O_tree	->	Branch("file_name",&out_file_name);
			out_O_tree	->	Branch("frame",&out_frame);
			out_O_tree	->	Branch("collection",&out_collection);
			out_O_tree	->	Branch("group",&out_group);
			out_O_tree	->	Branch("point",&out_point);
			out_O_tree	->	Branch("x",&out_x);
			out_O_tree	->	Branch("y",&out_y);
			out_O_tree	->	Branch("z",&out_z);
			out_O_tree	->	Branch("offp",&out_offp);
			out_O_tree	->	Branch("offr",&out_offr);
			out_O_tree	->	Branch("date_time",&out_date_time);		
			
			out_U_tree	->	Branch("file_name",&out_file_name);
			out_U_tree	->	Branch("frame",&out_frame);
			out_U_tree	->	Branch("collection",&out_collection);
			out_U_tree	->	Branch("group",&out_group);
			out_U_tree	->	Branch("point",&out_point);
			out_U_tree	->	Branch("x",&out_x);
			out_U_tree	->	Branch("y",&out_y);
			out_U_tree	->	Branch("z",&out_z);
			out_U_tree	->	Branch("offp",&out_offp);
			out_U_tree	->	Branch("offr",&out_offr);
			out_U_tree	->	Branch("date_time",&out_date_time);		

			out_PIM1_tree	->	Branch("file_name",&out_file_name);
			out_PIM1_tree	->	Branch("frame",&out_frame);
			out_PIM1_tree	->	Branch("collection",&out_collection);
			out_PIM1_tree	->	Branch("group",&out_group);
			out_PIM1_tree	->	Branch("point",&out_point);
			out_PIM1_tree	->	Branch("x",&out_x);
			out_PIM1_tree	->	Branch("y",&out_y);
			out_PIM1_tree	->	Branch("z",&out_z);
			out_PIM1_tree	->	Branch("offp",&out_offp);
			out_PIM1_tree	->	Branch("offr",&out_offr);
			out_PIM1_tree	->	Branch("date_time",&out_date_time);		
			
			out_H_tree	->	Branch("file_name",&out_file_name);
			out_H_tree	->	Branch("frame",&out_frame);
			out_H_tree	->	Branch("collection",&out_collection);
			out_H_tree	->	Branch("group",&out_group);
			out_H_tree	->	Branch("point",&out_point);
			out_H_tree	->	Branch("x",&out_x);
			out_H_tree	->	Branch("y",&out_y);
			out_H_tree	->	Branch("z",&out_z);
			out_H_tree	->	Branch("offp",&out_offp);
			out_H_tree	->	Branch("offr",&out_offr);
			out_H_tree	->	Branch("date_time",&out_date_time);		
			
			out_G_tree	->	Branch("file_name",&out_file_name);
			out_G_tree	->	Branch("frame",&out_frame);
			out_G_tree	->	Branch("collection",&out_collection);
			out_G_tree	->	Branch("group",&out_group);
			out_G_tree	->	Branch("point",&out_point);
			out_G_tree	->	Branch("x",&out_x);
			out_G_tree	->	Branch("y",&out_y);
			out_G_tree	->	Branch("z",&out_z);
			out_G_tree	->	Branch("offp",&out_offp);
			out_G_tree	->	Branch("offr",&out_offr);
			out_G_tree	->	Branch("date_time",&out_date_time);		
		
			out_UK_tree	->	Branch("file_name",&out_file_name);
			out_UK_tree	->	Branch("frame",&out_frame);
			out_UK_tree	->	Branch("collection",&out_collection);
			out_UK_tree	->	Branch("group",&out_group);
			out_UK_tree	->	Branch("point",&out_point);
			out_UK_tree	->	Branch("x",&out_x);
			out_UK_tree	->	Branch("y",&out_y);
			out_UK_tree	->	Branch("z",&out_z);
			out_UK_tree	->	Branch("offp",&out_offp);
			out_UK_tree	->	Branch("offr",&out_offr);
			out_UK_tree	->	Branch("date_time",&out_date_time);		
			
			out_TG_tree	->	Branch("file_name",&out_file_name);
			out_TG_tree	->	Branch("frame",&out_frame);
			out_TG_tree	->	Branch("collection",&out_collection);
			out_TG_tree	->	Branch("group",&out_group);
			out_TG_tree	->	Branch("point",&out_point);
			out_TG_tree	->	Branch("x",&out_x);
			out_TG_tree	->	Branch("y",&out_y);
			out_TG_tree	->	Branch("z",&out_z);
			out_TG_tree	->	Branch("offp",&out_offp);
			out_TG_tree	->	Branch("offr",&out_offr);
			out_TG_tree	->	Branch("date_time",&out_date_time);		
			
			out_Panel_1_tree	->	Branch("file_name",&out_file_name);
			out_Panel_1_tree	->	Branch("frame",&out_frame);
			out_Panel_1_tree	->	Branch("collection",&out_collection);
			out_Panel_1_tree	->	Branch("group",&out_group);
			out_Panel_1_tree	->	Branch("point",&out_point);
			out_Panel_1_tree	->	Branch("x",&out_x);
			out_Panel_1_tree	->	Branch("y",&out_y);
			out_Panel_1_tree	->	Branch("z",&out_z);
			out_Panel_1_tree	->	Branch("offp",&out_offp);
			out_Panel_1_tree	->	Branch("offr",&out_offr);
			out_Panel_1_tree	->	Branch("date_time",&out_date_time);		
			
			out_Panel_6_tree	->	Branch("file_name",&out_file_name);
			out_Panel_6_tree	->	Branch("frame",&out_frame);
			out_Panel_6_tree	->	Branch("collection",&out_collection);
			out_Panel_6_tree	->	Branch("group",&out_group);
			out_Panel_6_tree	->	Branch("point",&out_point);
			out_Panel_6_tree	->	Branch("x",&out_x);
			out_Panel_6_tree	->	Branch("y",&out_y);
			out_Panel_6_tree	->	Branch("z",&out_z);
			out_Panel_6_tree	->	Branch("offp",&out_offp);
			out_Panel_6_tree	->	Branch("offr",&out_offr);
			out_Panel_6_tree	->	Branch("date_time",&out_date_time);		
			
			out_Panel_5_tree	->	Branch("file_name",&out_file_name);
			out_Panel_5_tree	->	Branch("frame",&out_frame);
			out_Panel_5_tree	->	Branch("collection",&out_collection);
			out_Panel_5_tree	->	Branch("group",&out_group);
			out_Panel_5_tree	->	Branch("point",&out_point);
			out_Panel_5_tree	->	Branch("x",&out_x);
			out_Panel_5_tree	->	Branch("y",&out_y);
			out_Panel_5_tree	->	Branch("z",&out_z);
			out_Panel_5_tree	->	Branch("offp",&out_offp);
			out_Panel_5_tree	->	Branch("offr",&out_offr);
			out_Panel_5_tree	->	Branch("date_time",&out_date_time);		
			
			out_Target_tree	->	Branch("file_name",&out_file_name);
			out_Target_tree	->	Branch("frame",&out_frame);
			out_Target_tree	->	Branch("collection",&out_collection);
			out_Target_tree	->	Branch("group",&out_group);
			out_Target_tree	->	Branch("point",&out_point);
			out_Target_tree	->	Branch("x",&out_x);
			out_Target_tree	->	Branch("y",&out_y);
			out_Target_tree	->	Branch("z",&out_z);
			out_Target_tree	->	Branch("offp",&out_offp);
			out_Target_tree	->	Branch("offr",&out_offr);
			out_Target_tree	->	Branch("date_time",&out_date_time);		
	
			out_M_tree	->	Branch("file_name",&out_file_name);
			out_M_tree	->	Branch("frame",&out_frame);
			out_M_tree	->	Branch("collection",&out_collection);
			out_M_tree	->	Branch("group",&out_group);
			out_M_tree	->	Branch("point",&out_point);
			out_M_tree	->	Branch("x",&out_x);
			out_M_tree	->	Branch("y",&out_y);
			out_M_tree	->	Branch("z",&out_z);
			out_M_tree	->	Branch("offp",&out_offp);
			out_M_tree	->	Branch("offr",&out_offr);
			out_M_tree	->	Branch("date_time",&out_date_time);		
		
			out_PA6_M_tree	->	Branch("file_name",&out_file_name);
			out_PA6_M_tree	->	Branch("frame",&out_frame);
			out_PA6_M_tree	->	Branch("collection",&out_collection);
			out_PA6_M_tree	->	Branch("group",&out_group);
			out_PA6_M_tree	->	Branch("point",&out_point);
			out_PA6_M_tree	->	Branch("x",&out_x);
			out_PA6_M_tree	->	Branch("y",&out_y);
			out_PA6_M_tree	->	Branch("z",&out_z);
			out_PA6_M_tree	->	Branch("offp",&out_offp);
			out_PA6_M_tree	->	Branch("offr",&out_offr);
			out_PA6_M_tree	->	Branch("date_time",&out_date_time);		
			
			out_Kante_tree	->	Branch("file_name",&out_file_name);
			out_Kante_tree	->	Branch("frame",&out_frame);
			out_Kante_tree	->	Branch("collection",&out_collection);
			out_Kante_tree	->	Branch("group",&out_group);
			out_Kante_tree	->	Branch("point",&out_point);
			out_Kante_tree	->	Branch("x",&out_x);
			out_Kante_tree	->	Branch("y",&out_y);
			out_Kante_tree	->	Branch("z",&out_z);
			out_Kante_tree	->	Branch("offp",&out_offp);
			out_Kante_tree	->	Branch("offr",&out_offr);
			out_Kante_tree	->	Branch("date_time",&out_date_time);		
			
			out_HP_tree	->	Branch("file_name",&out_file_name);
			out_HP_tree	->	Branch("frame",&out_frame);
			out_HP_tree	->	Branch("collection",&out_collection);
			out_HP_tree	->	Branch("group",&out_group);
			out_HP_tree	->	Branch("point",&out_point);
			out_HP_tree	->	Branch("x",&out_x);
			out_HP_tree	->	Branch("y",&out_y);
			out_HP_tree	->	Branch("z",&out_z);
			out_HP_tree	->	Branch("offp",&out_offp);
			out_HP_tree	->	Branch("offr",&out_offr);
			out_HP_tree	->	Branch("date_time",&out_date_time);		


	vector<int> flagat;
//.........................

	for(int i=0;i<working_4_x_vec.size();i++)
	{

//..................................................................
			out_file_name=working_4_file_name_vec[i];
			out_frame=working_4_file_name_vec[i];
			out_collection=working_4_collection_vec[i];
			out_group=working_4_group_vec[i];
			out_point=working_4_point_vec[i];
			out_x=working_4_x_vec[i];
			out_y=working_4_y_vec[i];
			out_z=working_4_z_vec[i];
			out_offp=working_4_offp_vec[i];
			out_offr=working_4_offr_vec[i];
			out_date_time=working_4_date_time_vec[i];
//..................................................................
	TString P=working_4_point_vec[i];	//	just to make the if-statements shorter.
	TString G=working_4_group_vec[i];
//..........................
	if(P=="P0")		{	out_Turning_center_check_trans_tree	->	Fill();		flagat.push_back(1);	continue;}
	if(G=="Drehzentrumchecktrans") {if(P.Contains("P"))	{	out_Turning_center_check_trans_tree	->	Fill();		flagat.push_back(1);	continue;}}
//..........................
	if(P=="M5-PA6_15"||P=="PA6_15_M5"||P=="PA6_17_M1")		{	out_PA6_M_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P=="PA5_1"||P=="PA5_2"||P=="PA5_3"||P=="PA5_4"||P=="PA5_5"||P=="PA5_6"||P=="PA5_7"||P=="PA5_8"||P=="PA5_9"||P=="PA5_10"||P=="PA5_11"||P=="PA5_12"||P=="PA5_13"||P=="PA5_14"||P=="PA5_15")
	{	out_PA5_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P.Contains("PA6_"))//||P=="PA6_2"||P=="PA6_3"||P=="PA6_4"||P=="PA6_5"||P=="PA6_6"||P=="PA6_7"||P=="PA6_8"||P=="PA6_9"||P=="PA6_10"||P=="PA6_11"||P=="PA6_12"||P=="PA6_13"||P=="PA6_14"||P=="PA6_15"||P=="PA6_16"||P=="PA6_17"||P=="PA6_18"||P=="PA6_19"||P=="PA6_20")
	{	out_PA6_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P=="PA7_1"||P=="PA7_2"||P=="PA7_3"||P=="PA7_4"||P=="PA7_5"||P=="PA7_6"||P=="PA7_7"||P=="PA7_8"||P=="PA7_08"||P=="PA7_9"||P=="PA7_10"||P=="PA7_11"||P=="PA7_12"||P=="PA7_13"||P=="PA7_14"||P=="PA7_15"||P=="PA7_E2"||P=="PA7_E4"||P=="PA7_E3"||P=="PA7_E5")
	{	out_PA7_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P.Contains("PA8"))		{	out_PA8_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P.Contains("Rot"))		{	out_Rot_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P=="TA1"||P=="TA2"||P=="TA2(bumped)"||P=="TA3"||P=="TA4"||P=="TA5"||P=="TA6"||P=="TA7"||P=="TA8"||P=="TA9")
	{	out_TA_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P.Contains("HP1")||P.Contains("HP2")||P.Contains("HP3")||P.Contains("HP4")||P.Contains("HP5")||P.Contains("HP6")||P.Contains("HP7"))
	{	out_HP_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P=="EC-1"||P=="EC-2"||P=="EC-3"||P=="EC-4"||P=="EC-5"||P=="EC-6"||P=="EC-7"||P=="EC-7-1")
	{	out_EC_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P.Contains("TC"))		{	out_TC_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................		
	if(P=="R1"||P=="R2"||P=="R3"||P=="R4"||P=="R5"||P=="R6"||P=="R7"||P=="R8"||P=="R9"||P=="R10"||P=="R11")
	{	out_R_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P=="O1"||P=="O2"||P=="O3"||P=="O4"||P=="O5"||P=="O6"||P=="O7"||P=="O8")
	{	out_O_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................	
	if(P=="U1"||P=="U2"||P=="U3"||P=="U4"||P=="U5")
	{	out_U_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P.Contains("PIM1"))		{	out_PIM1_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P=="H1"||P=="H2"||P=="H3"||P=="H4"||P=="H5"||P=="H6"||P=="H7"||P=="H8"||P=="H9"||P=="H10"||P=="H11"||P=="H12"||P=="H13"||P=="H14"||P=="H15"||P=="H16"||P=="H17"||P=="H18"||P=="H19"||P=="H20"||P=="H21"||P=="H22"||P=="H23"||P=="H112")	
	{	out_H_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................	
	if(P=="G1"||P=="G2"||P=="G3"||P=="G4"||P=="G5"||P=="G6"||P=="G7"||P=="G8"||P=="G9"||P=="G10"||P=="G11"||P=="G12"||P=="G13"||P=="G1_2"||P=="G1_3_panel_Pos1"||P=="G1nachPanelupst")
	{	out_G_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P.Contains("UK"))			{	out_UK_tree			->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P.Contains("TG"))			{	out_TG_tree			->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P.Contains("Panel_1"))		{	out_Panel_1_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P.Contains("Panel_5"))		{	out_Panel_5_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P.Contains("Panel_6"))		{	out_Panel_6_tree	->	Fill();		flagat.push_back(1);	continue;}
//.........................
	if(P.Contains("Target"))		{	out_Target_tree		->	Fill();		flagat.push_back(1);	continue;}
//.........................	
	if(P=="M1"||P=="M2"||P=="M3"||P=="M4"||P=="M1*"||P=="M10"||P=="M11"||P=="M12"||P=="M20"||P=="M21")
	{	out_M_tree	->	Fill();			flagat.push_back(1);	continue;}
//.........................	
	if(P=="Kante1"||P=="Kante2"||P=="Kante3"||P=="Kante4"||P=="Kante5"||P=="Kante6"||P=="Kante7"||P=="Kante8"||P=="Kante9"||P=="Kante10")
	{	out_Kante_tree	->	Fill();			flagat.push_back(1);	continue;}
//.........................
	
	else{flagat.push_back(0);	continue;}

	}	//	for(i)

	cout<<"++++++++++	before	+++++++++++++++++++++"<<working_4_x_vec.size()<<endl;


//	...............................................
	
	for(int l=working_4_x_vec.size()-1;l>-1;l--)
	{
		if(flagat[l]==1)
		{
			working_4_file_name_vec.erase(std::next(working_4_file_name_vec.begin(),l));
			working_4_frame_vec.erase(std::next(working_4_frame_vec.begin(),l));
			working_4_collection_vec.erase(std::next(working_4_collection_vec.begin(),l));
			working_4_group_vec.erase(std::next(working_4_group_vec.begin(),l));
			working_4_point_vec.erase(std::next(working_4_point_vec.begin(),l));
			working_4_x_vec.erase(std::next(working_4_x_vec.begin(),l));
			working_4_y_vec.erase(std::next(working_4_y_vec.begin(),l));
			working_4_z_vec.erase(std::next(working_4_z_vec.begin(),l));
			working_4_offp_vec.erase(std::next(working_4_offp_vec.begin(),l));
			working_4_offr_vec.erase(std::next(working_4_offr_vec.begin(),l));
			working_4_date_time_vec.erase(std::next(working_4_date_time_vec.begin(),l));
		}
	}	//	for(l)
//	...............................................
	cout<<"+++++++++++++	after  +++++++++++++++++++++++++"<<working_4_x_vec.size()<<endl;





//	.....................................................
//	storing all the points from the vector to a TXT file.
	ofstream out_file_8_4;
	out_file_8_4.open("out_file_8_4.txt");
	for(int i=0;i<working_4_x_vec.size();i++)
	{
		out_file_8_4<<working_4_file_name_vec[i]<<","<<working_4_frame_vec[i]<<","<<working_4_collection_vec[i]<<","<<working_4_group_vec[i]<<","<<working_4_point_vec[i]<<","<<working_4_x_vec[i]<<","<<working_4_y_vec[i]<<","<<working_4_z_vec[i]<<" ,  "<<working_4_offp_vec[i]<<","<<working_4_offr_vec[i]<<","<<working_4_date_time_vec[i]<<endl;
	}
	out_file_8_4.close();
//	.....................................................




out_root_file->Write();
out_root_file->Close();



}	//	main




