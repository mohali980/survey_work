

#include<assert.h>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include <vector>
#include "Riostream.h"
#include "TString.h"
#include "TRegexp.h"
#include "string.h"

#include "TTimeStamp.h"

#include "TError.h"

#include <unistd.h>
#include <sys/time.h>

#include "TVirtualMutex.h"
#include <ctime> 

#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TMath.h"

#include "TApplication.h"
#include "TROOT.h"

#include "TH1F.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TSystem.h"

ClassImp(TTimeStamp);
 
 


using namespace std;



void coordconv_3()
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
	

/*


	cout<<"START Block (2) : filling 2X2 vectos for the NON-LOCAL frames, collections, groups & the points & (x,y,z) coordinates and the {offp,offr} values and so on..."<<endl;
//	2) START : ..............	seperating NON_LOCAL frames, collection, groups and so on.
//	Start : filling 2X2 vectos for the frames, collections, groups & the points & (x,y,z) coordinates and the {offp,offr} values.
//			for NON-Local measurements.

	vector<int> B;		//	use it just in the process.
	vector<TString> 	temp_tot_frame_vec,temp_frame_vec,temp_point_vec,temp_collection_vec,temp_group_vec,temp_file_name_vec;
	vector<float>	temp_x_vec,temp_y_vec,temp_z_vec,temp_offp_vec,temp_offr_vec;
	vector<TString>		A_tot_frame,A_point,A_frame,A_collection,A_group,A_file_name;
	vector<float> 	A_x,A_y,A_z,A_offp,A_offr;
	vector<TString>	A_date_time;
	vector<TString>	temp_date_time_vec;

	vector<vector<TString>> C_tot_frame,C_point,C_frame,C_collection,C_group,C_file_name;	//	the 2X2 vector which contains the frames and the other information
	vector<vector<float>> C_x,C_y,C_z,C_offp,C_offr;												//	the 2X2 vectors which contain the coordinates...
	vector<vector<TString>>	C_date_time;	

	A_tot_frame	=	tot_frame_vec;
	A_file_name	=	file_name_vec;
	A_collection=	collection_vec;
	A_group 	=	group_vec;
	A_frame 	=	frame_vec;
	A_point 	=	point_vec;
	A_x			=	x_vec;
	A_y			=	y_vec;
	A_z			=	z_vec;
	A_offp		=	offp_vec;
	A_offr		=	offr_vec;
	A_date_time	=	date_time_vec;


//	...........................................................................

while (A_tot_frame.size()!=0)
{
	temp_tot_frame_vec.clear();
	temp_file_name_vec.clear();
	temp_collection_vec.clear();
	temp_group_vec.clear();
	temp_frame_vec.clear();
	temp_point_vec.clear();
	temp_x_vec.clear();
	temp_y_vec.clear();
	temp_z_vec.clear();
	temp_offp_vec.clear();
	temp_offr_vec.clear();
	temp_date_time_vec.clear();

	temp_tot_frame_vec.push_back(A_tot_frame[0]);
	temp_file_name_vec.push_back(A_file_name[0]);
	temp_collection_vec.push_back(A_collection[0]);
	temp_group_vec.push_back(A_group[0]);
	temp_frame_vec.push_back(A_frame[0]);
	temp_point_vec.push_back(A_point[0]);
	temp_x_vec.push_back(A_x[0]);
	temp_y_vec.push_back(A_y[0]);
	temp_z_vec.push_back(A_z[0]);
	temp_offp_vec.push_back(A_offp[0]);
	temp_offr_vec.push_back(A_offr[0]);
	temp_date_time_vec.push_back(A_date_time[0]);

	B.clear();
	B.push_back(0);

	for(int y=1;y<A_tot_frame.size();y++)	
		{	if (A_tot_frame[y]==temp_tot_frame_vec[0]) 
			{	
				temp_tot_frame_vec.push_back(A_tot_frame[0]);
				temp_file_name_vec.push_back(A_file_name[0]);
				temp_frame_vec.push_back(A_frame[0]);
				temp_collection_vec.push_back(A_collection[0]);
				temp_group_vec.push_back(A_group[0]);
				temp_point_vec.push_back(A_point[y]);
				temp_x_vec.push_back(A_x[y]);
				temp_y_vec.push_back(A_y[y]);
				temp_z_vec.push_back(A_z[y]);
				temp_offp_vec.push_back(A_offp[y]);
				temp_offr_vec.push_back(A_offr[y]);
				temp_date_time_vec.push_back(A_date_time[y]);


				B.push_back(y);
			}
		}

	for(int y=B.size()-1;y>-1;y--)	
		{
			A_tot_frame.erase(std::next(A_tot_frame.begin(),B[y]));
			A_file_name.erase(std::next(A_file_name.begin(),B[y]));
			A_frame.erase(std::next(A_frame.begin(),B[y]));
			A_collection.erase(std::next(A_collection.begin(),B[y]));
			A_group.erase(std::next(A_group.begin(),B[y]));
			A_point.erase(std::next(A_point.begin(),B[y]));	
			A_x.erase(std::next(A_x.begin(),B[y]));	
			A_y.erase(std::next(A_y.begin(),B[y]));	
			A_z.erase(std::next(A_z.begin(),B[y]));	
			A_offp.erase(std::next(A_offp.begin(),B[y]));	
			A_offr.erase(std::next(A_offr.begin(),B[y]));	
			A_date_time.erase(std::next(A_date_time.begin(),B[y]));
		}

//	storing the data in 2X2 vectors (TSiring)

	C_tot_frame.push_back(temp_tot_frame_vec);
	C_file_name.push_back(temp_file_name_vec);
	C_frame.push_back(temp_frame_vec);
	C_collection.push_back(temp_collection_vec);
	C_group.push_back(temp_group_vec);
	C_point.push_back(temp_point_vec);
	C_x.push_back(temp_x_vec);
	C_y.push_back(temp_y_vec);
	C_z.push_back(temp_z_vec);
	C_offp.push_back(temp_offp_vec);
	C_offr.push_back(temp_offr_vec);
	C_date_time.push_back(temp_date_time_vec);

}	//	while(int j<size)

//	cout<<"End : filling the 2X2 vectos for the tot_frame & the points & (x,y,z) coordinates and the {offp,offr} values."<<endl;

//	End : filling 2X2 vectos for the tot_frame & the points & (x,y,z) coordinates and the {offp,offr} values.
//	2) END : 	.............	seperating total NON_LOCAL frames	.......................



	
	
	cout<<"START Block (3) : filling 2X2 vectos for the LOCAL frames, collections, groups & the points & (x,y,z) coordinates and the {offp,offr} values and so on..."<<endl;
//	3) START : ..............	seperating LOCAL frames, collection, groups and so on.
//	Start : filling 2X2 vectos for the frames, collections, groups & the points & (x,y,z) coordinates and the {offp,offr} values.
//			for NON-Local measurements.

	vector<int> loc_B;		//	use it just in the process.
	vector<TString> 	loc_temp_tot_frame_vec,loc_temp_frame_vec,loc_temp_point_vec,loc_temp_collection_vec,loc_temp_group_vec,loc_temp_file_name_vec;
	vector<float>	loc_temp_x_vec,loc_temp_y_vec,loc_temp_z_vec,loc_temp_offp_vec,loc_temp_offr_vec;
	vector<TString>		loc_A_tot_frame,loc_A_point,loc_A_frame,loc_A_collection,loc_A_group,loc_A_file_name;
	vector<float> 	loc_A_x,loc_A_y,loc_A_z,loc_A_offp,loc_A_offr;
	vector<TString>	loc_A_date_time;
	vector<TString>	loc_temp_date_time_vec;

	vector<vector<TString>> loc_C_tot_frame,loc_C_point,loc_C_frame,loc_C_collection,loc_C_group,loc_C_file_name;	//	the 2X2 vector which contains the frames and the other information
	vector<vector<float>> loc_C_x,loc_C_y,loc_C_z,loc_C_offp,loc_C_offr;												//	the 2X2 vectors which contain the coordinates...
	vector<vector<TString>>	loc_C_date_time;	

	loc_A_tot_frame	=	loc_tot_frame_vec;
	loc_A_file_name	=	loc_file_name_vec;
	loc_A_collection=	loc_collection_vec;
	loc_A_group 	=	loc_group_vec;
	loc_A_frame 	=	loc_frame_vec;
	loc_A_point 	=	loc_point_vec;
	loc_A_x			=	loc_x_vec;
	loc_A_y			=	loc_y_vec;
	loc_A_z			=	loc_z_vec;
	loc_A_offp		=	loc_offp_vec;
	loc_A_offr		=	loc_offr_vec;
	loc_A_date_time	=	loc_date_time_vec;


//	...........................................................................

while (loc_A_tot_frame.size()!=0)
{
	loc_temp_tot_frame_vec.clear();
	loc_temp_file_name_vec.clear();
	loc_temp_collection_vec.clear();
	loc_temp_group_vec.clear();
	loc_temp_frame_vec.clear();
	loc_temp_point_vec.clear();
	loc_temp_x_vec.clear();
	loc_temp_y_vec.clear();
	loc_temp_z_vec.clear();
	loc_temp_offp_vec.clear();
	loc_temp_offr_vec.clear();
	loc_temp_date_time_vec.clear();

	loc_temp_tot_frame_vec.push_back(loc_A_tot_frame[0]);
	loc_temp_file_name_vec.push_back(loc_A_file_name[0]);
	loc_temp_collection_vec.push_back(loc_A_collection[0]);
	loc_temp_group_vec.push_back(loc_A_group[0]);
	loc_temp_frame_vec.push_back(loc_A_frame[0]);
	loc_temp_point_vec.push_back(loc_A_point[0]);
	loc_temp_x_vec.push_back(loc_A_x[0]);
	loc_temp_y_vec.push_back(loc_A_y[0]);
	loc_temp_z_vec.push_back(loc_A_z[0]);
	loc_temp_offp_vec.push_back(loc_A_offp[0]);
	loc_temp_offr_vec.push_back(loc_A_offr[0]);
	loc_temp_date_time_vec.push_back(loc_A_date_time[0]);

	loc_B.clear();
	loc_B.push_back(0);

	for(int y=1;y<loc_A_tot_frame.size();y++)	
		{	if (loc_A_tot_frame[y]==loc_temp_tot_frame_vec[0]) 
			{	
				loc_temp_tot_frame_vec.push_back(loc_A_tot_frame[0]);
				loc_temp_file_name_vec.push_back(loc_A_file_name[0]);
				loc_temp_frame_vec.push_back(loc_A_frame[0]);
				loc_temp_collection_vec.push_back(loc_A_collection[0]);
				loc_temp_group_vec.push_back(loc_A_group[0]);
				loc_temp_point_vec.push_back(loc_A_point[y]);
				loc_temp_x_vec.push_back(loc_A_x[y]);
				loc_temp_y_vec.push_back(loc_A_y[y]);
				loc_temp_z_vec.push_back(loc_A_z[y]);
				loc_temp_offp_vec.push_back(loc_A_offp[y]);
				loc_temp_offr_vec.push_back(loc_A_offr[y]);
				loc_temp_date_time_vec.push_back(loc_A_date_time[y]);


				loc_B.push_back(y);
			}
		}
	for(int y=loc_B.size()-1;y>-1;y--)	
		{
			loc_A_tot_frame.erase(std::next(loc_A_tot_frame.begin(),loc_B[y]));
			loc_A_file_name.erase(std::next(loc_A_file_name.begin(),loc_B[y]));
			loc_A_frame.erase(std::next(loc_A_frame.begin(),loc_B[y]));
			loc_A_collection.erase(std::next(loc_A_collection.begin(),loc_B[y]));
			loc_A_group.erase(std::next(loc_A_group.begin(),loc_B[y]));
			loc_A_point.erase(std::next(loc_A_point.begin(),loc_B[y]));	
			loc_A_x.erase(std::next(loc_A_x.begin(),loc_B[y]));	
			loc_A_y.erase(std::next(loc_A_y.begin(),loc_B[y]));	
			loc_A_z.erase(std::next(loc_A_z.begin(),loc_B[y]));	
			loc_A_offp.erase(std::next(loc_A_offp.begin(),loc_B[y]));	
			loc_A_offr.erase(std::next(loc_A_offr.begin(),loc_B[y]));	
			loc_A_date_time.erase(std::next(loc_A_date_time.begin(),loc_B[y]));
		}

//	storing the data in 2X2 vectors (TSiring)

	loc_C_tot_frame.push_back(loc_temp_tot_frame_vec);
	loc_C_file_name.push_back(loc_temp_file_name_vec);
	loc_C_frame.push_back(loc_temp_frame_vec);
	loc_C_collection.push_back(loc_temp_collection_vec);
	loc_C_group.push_back(loc_temp_group_vec);
	loc_C_point.push_back(loc_temp_point_vec);
	loc_C_x.push_back(loc_temp_x_vec);
	loc_C_y.push_back(loc_temp_y_vec);
	loc_C_z.push_back(loc_temp_z_vec);
	loc_C_offp.push_back(loc_temp_offp_vec);
	loc_C_offr.push_back(loc_temp_offr_vec);
	loc_C_date_time.push_back(loc_temp_date_time_vec);



}	//	while(int j<size)

//	cout<<"End : filling the 2X2 vectos for the tot_frame & the points & (x,y,z) coordinates and the {offp,offr} values."<<endl;

//	End : filling 2X2 vectos for the tot_frame & the points & (x,y,z) coordinates and the {offp,offr} values.
//	3) END : 	.............	seperating total LOCAL frames	.......................





*/



	cout<<"START Block (4) : seperating each divice's coordinates, in a separate file for each year."<<endl;
//	4) START:	.............	seperating each divice's coordinates 	.......................
//	defining the output tree,
//	in the next lines, defining the branches whit their parameters, we can add any more branches 
//	but the parameters should be define as done in the others, COPY and PASTE is very useful.

	vector<int> detectors_flag_vec;	//	define the locations in the points vector to drop the recognized ones. and keep the un-knowns in the output.txt file

	TFile *	out_root_file	=	new TFile("points_3.root","RECREATE");

	TTree *out_PiM1_tree			=	new TTree("PiM1","");
	TTree *out_G_PlatForm_tree		=	new TTree("G_PlatForm","");
	TTree *out_H_SlidingTable_tree	=	new TTree("H_SlidingTable","");
	TTree *out_TA_SlidingTable_tree	=	new TTree("TA_SlidingTable","");
	TTree *out_BM_BigBars_tree		=	new TTree("BM_BigBars","");
	TTree *out_BM_Hodo_tree			=	new TTree("BM_Hodo","");
	TTree *out_STT_LV60_tree		=	new TTree("STT_LV60","");
	TTree *out_STT_LH60_tree		=	new TTree("STT_LH60","");
	TTree *out_STT_LV90_tree		=	new TTree("STT_LV90","");
	TTree *out_STT_LH90_tree		=	new TTree("STT_LH90","");
	TTree *out_SPS_LF_tree			=	new TTree("SPS_LF","");
	TTree *out_SPS_LR_tree			=	new TTree("SPS_LR","");
	TTree *out_STT_RV60_tree		=	new TTree("STT_RV60","");
	TTree *out_STT_RH60_tree		=	new TTree("STT_RH60","");
	TTree *out_STT_RV90_tree		=	new TTree("STT_RV90","");
	TTree *out_STT_RH90_tree		=	new TTree("STT_RH90","");
	TTree *out_SPS_RF_tree			=	new TTree("SPS_RF","");
	TTree *out_SPS_RR_tree			=	new TTree("SPS_RR","");
	TTree *out_M_STT_tree			=	new TTree("M_STT","");
	TTree *out_HP_tree				=	new TTree("HP","");
	TTree *out_PA6_tree				=	new TTree("PA6","");
	TTree *out_PA7_tree				=	new TTree("PA7","");
	TTree *out_Kreis_tree			=	new TTree("Kreis","");
	TTree *out_G_group_tree			=	new TTree("G_group","");
	TTree *out_TG_tree				=	new TTree("TG","");
	TTree *out_2E2_tree				=	new TTree("2E2","");
	TTree *out_2E1_tree				=	new TTree("2E1","");
	TTree *out_TC1_tree				=	new TTree("TC1","");
	TTree *out_TC2_tree				=	new TTree("TC2","");
	TTree *out_TC3_tree				=	new TTree("TC3","");
	TTree *out_BFM_PiM1_tree		=	new TTree("BFM_PiM1","");
	TTree *out_Draht_PiM1_tree		=	new TTree("Draht_PiM1","");
	TTree *out_Flaeche_PiM1_tree	=	new TTree("Flaeche_PiM1","");
	TTree *out_Panel9O_tree			=	new TTree("Panel9O","");
	TTree *out_Panel10O_tree		=	new TTree("Panel10O","");
	TTree *out_Panel11O_tree		=	new TTree("Panel11O","");
	TTree *out_Panel12O_tree		=	new TTree("Panel12O","");
	TTree *out_Leiter3_1_tree		=	new TTree("Leiter3-1","");
	TTree *out_Fenster_tree			=	new TTree("Fenster","");
	TTree *out_loc_BFM_tree			=	new TTree("loc_BFM","");

	
	TString		out_file_name_loc_BFM,out_frame_loc_BFM,out_collection_loc_BFM,out_group_loc_BFM,out_point_loc_BFM,out_date_time_loc_BFM;
	float 	out_x_loc_BFM,out_y_loc_BFM,out_z_loc_BFM,out_offp_loc_BFM,out_offr_loc_BFM;

	out_loc_BFM_tree				->	Branch("file_name",&out_file_name_loc_BFM);
	out_loc_BFM_tree				->	Branch("frame",&out_frame_loc_BFM);
	out_loc_BFM_tree				->	Branch("collection",&out_collection_loc_BFM);
	out_loc_BFM_tree				->	Branch("group",&out_group_loc_BFM);
	out_loc_BFM_tree				->	Branch("point",&out_point_loc_BFM);
	out_loc_BFM_tree				->	Branch("x",&out_x_loc_BFM);
	out_loc_BFM_tree				->	Branch("y",&out_y_loc_BFM);
	out_loc_BFM_tree				->	Branch("z",&out_z_loc_BFM);
	out_loc_BFM_tree				->	Branch("offp",&out_offp_loc_BFM);
	out_loc_BFM_tree				->	Branch("offr",&out_offr_loc_BFM);
	out_loc_BFM_tree				->	Branch("date_time",&out_date_time_loc_BFM);
	
	TString		out_file_name_Fenster,out_frame_Fenster,out_collection_Fenster,out_group_Fenster,out_point_Fenster,out_date_time_Fenster;
	float 	out_x_Fenster,out_y_Fenster,out_z_Fenster,out_offp_Fenster,out_offr_Fenster;

	out_Fenster_tree				->	Branch("file_name",&out_file_name_Fenster);
	out_Fenster_tree				->	Branch("frame",&out_frame_Fenster);
	out_Fenster_tree				->	Branch("collection",&out_collection_Fenster);
	out_Fenster_tree				->	Branch("group",&out_group_Fenster);
	out_Fenster_tree				->	Branch("point",&out_point_Fenster);
	out_Fenster_tree				->	Branch("x",&out_x_Fenster);
	out_Fenster_tree				->	Branch("y",&out_y_Fenster);
	out_Fenster_tree				->	Branch("z",&out_z_Fenster);
	out_Fenster_tree				->	Branch("offp",&out_offp_Fenster);
	out_Fenster_tree				->	Branch("offr",&out_offr_Fenster);
	out_Fenster_tree				->	Branch("date_time",&out_date_time_Fenster);
	
	TString		out_file_name_Leiter3_1,out_frame_Leiter3_1,out_collection_Leiter3_1,out_group_Leiter3_1,out_point_Leiter3_1,out_date_time_Leiter3_1;
	float 	out_x_Leiter3_1,out_y_Leiter3_1,out_z_Leiter3_1,out_offp_Leiter3_1,out_offr_Leiter3_1;

	out_Leiter3_1_tree				->	Branch("file_name",&out_file_name_Leiter3_1);
	out_Leiter3_1_tree				->	Branch("frame",&out_frame_Leiter3_1);
	out_Leiter3_1_tree				->	Branch("collection",&out_collection_Leiter3_1);
	out_Leiter3_1_tree				->	Branch("group",&out_group_Leiter3_1);
	out_Leiter3_1_tree				->	Branch("point",&out_point_Leiter3_1);
	out_Leiter3_1_tree				->	Branch("x",&out_x_Leiter3_1);
	out_Leiter3_1_tree				->	Branch("y",&out_y_Leiter3_1);
	out_Leiter3_1_tree				->	Branch("z",&out_z_Leiter3_1);
	out_Leiter3_1_tree				->	Branch("offp",&out_offp_Leiter3_1);
	out_Leiter3_1_tree				->	Branch("offr",&out_offr_Leiter3_1);
	out_Leiter3_1_tree				->	Branch("date_time",&out_date_time_Leiter3_1);
	
	TString		out_file_name_Panel9O,out_frame_Panel9O,out_collection_Panel9O,out_group_Panel9O,out_point_Panel9O,out_date_time_Panel9O;
	float 	out_x_Panel9O,out_y_Panel9O,out_z_Panel9O,out_offp_Panel9O,out_offr_Panel9O;

	out_Panel9O_tree				->	Branch("file_name",&out_file_name_Panel9O);
	out_Panel9O_tree				->	Branch("frame",&out_frame_Panel9O);
	out_Panel9O_tree				->	Branch("collection",&out_collection_Panel9O);
	out_Panel9O_tree				->	Branch("group",&out_group_Panel9O);
	out_Panel9O_tree				->	Branch("point",&out_point_Panel9O);
	out_Panel9O_tree				->	Branch("x",&out_x_Panel9O);
	out_Panel9O_tree				->	Branch("y",&out_y_Panel9O);
	out_Panel9O_tree				->	Branch("z",&out_z_Panel9O);
	out_Panel9O_tree				->	Branch("offp",&out_offp_Panel9O);
	out_Panel9O_tree				->	Branch("offr",&out_offr_Panel9O);
	out_Panel9O_tree				->	Branch("date_time",&out_date_time_Panel9O);
	
	TString		out_file_name_Panel10O,out_frame_Panel10O,out_collection_Panel10O,out_group_Panel10O,out_point_Panel10O,out_date_time_Panel10O;
	float 	out_x_Panel10O,out_y_Panel10O,out_z_Panel10O,out_offp_Panel10O,out_offr_Panel10O;

	out_Panel10O_tree				->	Branch("file_name",&out_file_name_Panel10O);
	out_Panel10O_tree				->	Branch("frame",&out_frame_Panel10O);
	out_Panel10O_tree				->	Branch("collection",&out_collection_Panel10O);
	out_Panel10O_tree				->	Branch("group",&out_group_Panel10O);
	out_Panel10O_tree				->	Branch("point",&out_point_Panel10O);
	out_Panel10O_tree				->	Branch("x",&out_x_Panel10O);
	out_Panel10O_tree				->	Branch("y",&out_y_Panel10O);
	out_Panel10O_tree				->	Branch("z",&out_z_Panel10O);
	out_Panel10O_tree				->	Branch("offp",&out_offp_Panel10O);
	out_Panel10O_tree				->	Branch("offr",&out_offr_Panel10O);
	out_Panel10O_tree				->	Branch("date_time",&out_date_time_Panel10O);
		
	TString		out_file_name_Panel11O,out_frame_Panel11O,out_collection_Panel11O,out_group_Panel11O,out_point_Panel11O,out_date_time_Panel11O;
	float 	out_x_Panel11O,out_y_Panel11O,out_z_Panel11O,out_offp_Panel11O,out_offr_Panel11O;

	out_Panel11O_tree				->	Branch("file_name",&out_file_name_Panel11O);
	out_Panel11O_tree				->	Branch("frame",&out_frame_Panel11O);
	out_Panel11O_tree				->	Branch("collection",&out_collection_Panel11O);
	out_Panel11O_tree				->	Branch("group",&out_group_Panel11O);
	out_Panel11O_tree				->	Branch("point",&out_point_Panel11O);
	out_Panel11O_tree				->	Branch("x",&out_x_Panel11O);
	out_Panel11O_tree				->	Branch("y",&out_y_Panel11O);
	out_Panel11O_tree				->	Branch("z",&out_z_Panel11O);
	out_Panel11O_tree				->	Branch("offp",&out_offp_Panel11O);
	out_Panel11O_tree				->	Branch("offr",&out_offr_Panel11O);
	out_Panel11O_tree				->	Branch("date_time",&out_date_time_Panel11O);
		
	TString		out_file_name_Panel12O,out_frame_Panel12O,out_collection_Panel12O,out_group_Panel12O,out_point_Panel12O,out_date_time_Panel12O;
	float 	out_x_Panel12O,out_y_Panel12O,out_z_Panel12O,out_offp_Panel12O,out_offr_Panel12O;

	out_Panel12O_tree				->	Branch("file_name",&out_file_name_Panel12O);
	out_Panel12O_tree				->	Branch("frame",&out_frame_Panel12O);
	out_Panel12O_tree				->	Branch("collection",&out_collection_Panel12O);
	out_Panel12O_tree				->	Branch("group",&out_group_Panel12O);
	out_Panel12O_tree				->	Branch("point",&out_point_Panel12O);
	out_Panel12O_tree				->	Branch("x",&out_x_Panel12O);
	out_Panel12O_tree				->	Branch("y",&out_y_Panel12O);
	out_Panel12O_tree				->	Branch("z",&out_z_Panel12O);
	out_Panel12O_tree				->	Branch("offp",&out_offp_Panel12O);
	out_Panel12O_tree				->	Branch("offr",&out_offr_Panel12O);
	out_Panel12O_tree				->	Branch("date_time",&out_date_time_Panel12O);
		
	TString		out_file_name_Draht_PiM1,out_frame_Draht_PiM1,out_collection_Draht_PiM1,out_group_Draht_PiM1,out_point_Draht_PiM1,out_date_time_Draht_PiM1;
	float 	out_x_Draht_PiM1,out_y_Draht_PiM1,out_z_Draht_PiM1,out_offp_Draht_PiM1,out_offr_Draht_PiM1;

	out_Draht_PiM1_tree				->	Branch("file_name",&out_file_name_Draht_PiM1);
	out_Draht_PiM1_tree				->	Branch("frame",&out_frame_Draht_PiM1);
	out_Draht_PiM1_tree				->	Branch("collection",&out_collection_Draht_PiM1);
	out_Draht_PiM1_tree				->	Branch("group",&out_group_Draht_PiM1);
	out_Draht_PiM1_tree				->	Branch("point",&out_point_Draht_PiM1);
	out_Draht_PiM1_tree				->	Branch("x",&out_x_Draht_PiM1);
	out_Draht_PiM1_tree				->	Branch("y",&out_y_Draht_PiM1);
	out_Draht_PiM1_tree				->	Branch("z",&out_z_Draht_PiM1);
	out_Draht_PiM1_tree				->	Branch("offp",&out_offp_Draht_PiM1);
	out_Draht_PiM1_tree				->	Branch("offr",&out_offr_Draht_PiM1);
	out_Draht_PiM1_tree				->	Branch("date_time",&out_date_time_Draht_PiM1);
	
	TString		out_file_name_Flaeche_PiM1,out_frame_Flaeche_PiM1,out_collection_Flaeche_PiM1,out_group_Flaeche_PiM1,out_point_Flaeche_PiM1,out_date_time_Flaeche_PiM1;
	float 	out_x_Flaeche_PiM1,out_y_Flaeche_PiM1,out_z_Flaeche_PiM1,out_offp_Flaeche_PiM1,out_offr_Flaeche_PiM1;

	out_Flaeche_PiM1_tree				->	Branch("file_name",&out_file_name_Flaeche_PiM1);
	out_Flaeche_PiM1_tree				->	Branch("frame",&out_frame_Flaeche_PiM1);
	out_Flaeche_PiM1_tree				->	Branch("collection",&out_collection_Flaeche_PiM1);
	out_Flaeche_PiM1_tree				->	Branch("group",&out_group_Flaeche_PiM1);
	out_Flaeche_PiM1_tree				->	Branch("point",&out_point_Flaeche_PiM1);
	out_Flaeche_PiM1_tree				->	Branch("x",&out_x_Flaeche_PiM1);
	out_Flaeche_PiM1_tree				->	Branch("y",&out_y_Flaeche_PiM1);
	out_Flaeche_PiM1_tree				->	Branch("z",&out_z_Flaeche_PiM1);
	out_Flaeche_PiM1_tree				->	Branch("offp",&out_offp_Flaeche_PiM1);
	out_Flaeche_PiM1_tree				->	Branch("offr",&out_offr_Flaeche_PiM1);
	out_Flaeche_PiM1_tree				->	Branch("date_time",&out_date_time_Flaeche_PiM1);
		
	TString		out_file_name_BFM_PiM1,out_frame_BFM_PiM1,out_collection_BFM_PiM1,out_group_BFM_PiM1,out_point_BFM_PiM1,out_date_time_BFM_PiM1;
	float 	out_x_BFM_PiM1,out_y_BFM_PiM1,out_z_BFM_PiM1,out_offp_BFM_PiM1,out_offr_BFM_PiM1;

	out_BFM_PiM1_tree				->	Branch("file_name",&out_file_name_BFM_PiM1);
	out_BFM_PiM1_tree				->	Branch("frame",&out_frame_BFM_PiM1);
	out_BFM_PiM1_tree				->	Branch("collection",&out_collection_BFM_PiM1);
	out_BFM_PiM1_tree				->	Branch("group",&out_group_BFM_PiM1);
	out_BFM_PiM1_tree				->	Branch("point",&out_point_BFM_PiM1);
	out_BFM_PiM1_tree				->	Branch("x",&out_x_BFM_PiM1);
	out_BFM_PiM1_tree				->	Branch("y",&out_y_BFM_PiM1);
	out_BFM_PiM1_tree				->	Branch("z",&out_z_BFM_PiM1);
	out_BFM_PiM1_tree				->	Branch("offp",&out_offp_BFM_PiM1);
	out_BFM_PiM1_tree				->	Branch("offr",&out_offr_BFM_PiM1);
	out_BFM_PiM1_tree				->	Branch("date_time",&out_date_time_BFM_PiM1);
	
	TString		out_file_name_TC1,out_frame_TC1,out_collection_TC1,out_group_TC1,out_point_TC1,out_date_time_TC1;
	float 	out_x_TC1,out_y_TC1,out_z_TC1,out_offp_TC1,out_offr_TC1;

	out_TC1_tree				->	Branch("file_name",&out_file_name_TC1);
	out_TC1_tree				->	Branch("frame",&out_frame_TC1);
	out_TC1_tree				->	Branch("collection",&out_collection_TC1);
	out_TC1_tree				->	Branch("group",&out_group_TC1);
	out_TC1_tree				->	Branch("point",&out_point_TC1);
	out_TC1_tree				->	Branch("x",&out_x_TC1);
	out_TC1_tree				->	Branch("y",&out_y_TC1);
	out_TC1_tree				->	Branch("z",&out_z_TC1);
	out_TC1_tree				->	Branch("offp",&out_offp_TC1);
	out_TC1_tree				->	Branch("offr",&out_offr_TC1);
	out_TC1_tree				->	Branch("date_time",&out_date_time_TC1);
	
	TString		out_file_name_TC2,out_frame_TC2,out_collection_TC2,out_group_TC2,out_point_TC2,out_date_time_TC2;
	float 	out_x_TC2,out_y_TC2,out_z_TC2,out_offp_TC2,out_offr_TC2;

	out_TC2_tree				->	Branch("file_name",&out_file_name_TC2);
	out_TC2_tree				->	Branch("frame",&out_frame_TC2);
	out_TC2_tree				->	Branch("collection",&out_collection_TC2);
	out_TC2_tree				->	Branch("group",&out_group_TC2);
	out_TC2_tree				->	Branch("point",&out_point_TC2);
	out_TC2_tree				->	Branch("x",&out_x_TC2);
	out_TC2_tree				->	Branch("y",&out_y_TC2);
	out_TC2_tree				->	Branch("z",&out_z_TC2);
	out_TC2_tree				->	Branch("offp",&out_offp_TC2);
	out_TC2_tree				->	Branch("offr",&out_offr_TC2);
	out_TC2_tree				->	Branch("date_time",&out_date_time_TC2);
	
	TString		out_file_name_TC3,out_frame_TC3,out_collection_TC3,out_group_TC3,out_point_TC3,out_date_time_TC3;
	float 	out_x_TC3,out_y_TC3,out_z_TC3,out_offp_TC3,out_offr_TC3;

	out_TC3_tree				->	Branch("file_name",&out_file_name_TC3);
	out_TC3_tree				->	Branch("frame",&out_frame_TC3);
	out_TC3_tree				->	Branch("collection",&out_collection_TC3);
	out_TC3_tree				->	Branch("group",&out_group_TC3);
	out_TC3_tree				->	Branch("point",&out_point_TC3);
	out_TC3_tree				->	Branch("x",&out_x_TC3);
	out_TC3_tree				->	Branch("y",&out_y_TC3);
	out_TC3_tree				->	Branch("z",&out_z_TC3);
	out_TC3_tree				->	Branch("offp",&out_offp_TC3);
	out_TC3_tree				->	Branch("offr",&out_offr_TC3);
	out_TC3_tree				->	Branch("date_time",&out_date_time_TC3);
	
	TString		out_file_name_2E1,out_frame_2E1,out_collection_2E1,out_group_2E1,out_point_2E1,out_date_time_2E1;
	float 	out_x_2E1,out_y_2E1,out_z_2E1,out_offp_2E1,out_offr_2E1;

	out_2E1_tree				->	Branch("file_name",&out_file_name_2E1);
	out_2E1_tree				->	Branch("frame",&out_frame_2E1);
	out_2E1_tree				->	Branch("collection",&out_collection_2E1);
	out_2E1_tree				->	Branch("group",&out_group_2E1);
	out_2E1_tree				->	Branch("point",&out_point_2E1);
	out_2E1_tree				->	Branch("x",&out_x_2E1);
	out_2E1_tree				->	Branch("y",&out_y_2E1);
	out_2E1_tree				->	Branch("z",&out_z_2E1);
	out_2E1_tree				->	Branch("offp",&out_offp_2E1);
	out_2E1_tree				->	Branch("offr",&out_offr_2E1);
	out_2E1_tree				->	Branch("date_time",&out_date_time_2E1);
		
	TString		out_file_name_2E2,out_frame_2E2,out_collection_2E2,out_group_2E2,out_point_2E2,out_date_time_2E2;
	float 	out_x_2E2,out_y_2E2,out_z_2E2,out_offp_2E2,out_offr_2E2;

	out_2E2_tree				->	Branch("file_name",&out_file_name_2E2);
	out_2E2_tree				->	Branch("frame",&out_frame_2E2);
	out_2E2_tree				->	Branch("collection",&out_collection_2E2);
	out_2E2_tree				->	Branch("group",&out_group_2E2);
	out_2E2_tree				->	Branch("point",&out_point_2E2);
	out_2E2_tree				->	Branch("x",&out_x_2E2);
	out_2E2_tree				->	Branch("y",&out_y_2E2);
	out_2E2_tree				->	Branch("z",&out_z_2E2);
	out_2E2_tree				->	Branch("offp",&out_offp_2E2);
	out_2E2_tree				->	Branch("offr",&out_offr_2E2);
	out_2E2_tree				->	Branch("date_time",&out_date_time_2E2);
		
	TString		out_file_name_G_group,out_frame_G_group,out_collection_G_group,out_group_G_group,out_point_G_group,out_date_time_G_group;
	float 	out_x_G_group,out_y_G_group,out_z_G_group,out_offp_G_group,out_offr_G_group;

	out_G_group_tree				->	Branch("file_name",&out_file_name_G_group);
	out_G_group_tree				->	Branch("frame",&out_frame_G_group);
	out_G_group_tree				->	Branch("collection",&out_collection_G_group);
	out_G_group_tree				->	Branch("group",&out_group_G_group);
	out_G_group_tree				->	Branch("point",&out_point_G_group);
	out_G_group_tree				->	Branch("x",&out_x_G_group);
	out_G_group_tree				->	Branch("y",&out_y_G_group);
	out_G_group_tree				->	Branch("z",&out_z_G_group);
	out_G_group_tree				->	Branch("offp",&out_offp_G_group);
	out_G_group_tree				->	Branch("offr",&out_offr_G_group);
	out_G_group_tree				->	Branch("date_time",&out_date_time_G_group);
		
	TString		out_file_name_TG,out_frame_TG,out_collection_TG,out_group_TG,out_point_TG,out_date_time_TG;
	float 	out_x_TG,out_y_TG,out_z_TG,out_offp_TG,out_offr_TG;

	out_TG_tree				->	Branch("file_name",&out_file_name_TG);
	out_TG_tree				->	Branch("frame",&out_frame_TG);
	out_TG_tree				->	Branch("collection",&out_collection_TG);
	out_TG_tree				->	Branch("group",&out_group_TG);
	out_TG_tree				->	Branch("point",&out_point_TG);
	out_TG_tree				->	Branch("x",&out_x_TG);
	out_TG_tree				->	Branch("y",&out_y_TG);
	out_TG_tree				->	Branch("z",&out_z_TG);
	out_TG_tree				->	Branch("offp",&out_offp_TG);
	out_TG_tree				->	Branch("offr",&out_offr_TG);
	out_TG_tree				->	Branch("date_time",&out_date_time_TG);
		
	TString		out_file_name_PiM1,out_frame_PiM1,out_collection_PiM1,out_group_PiM1,out_point_PiM1,out_date_time_PiM1;
	float 	out_x_PiM1,out_y_PiM1,out_z_PiM1,out_offp_PiM1,out_offr_PiM1;

	out_PiM1_tree				->	Branch("file_name",&out_file_name_PiM1);
	out_PiM1_tree				->	Branch("frame",&out_frame_PiM1);
	out_PiM1_tree				->	Branch("collection",&out_collection_PiM1);
	out_PiM1_tree				->	Branch("group",&out_group_PiM1);
	out_PiM1_tree				->	Branch("point",&out_point_PiM1);
	out_PiM1_tree				->	Branch("x",&out_x_PiM1);
	out_PiM1_tree				->	Branch("y",&out_y_PiM1);
	out_PiM1_tree				->	Branch("z",&out_z_PiM1);
	out_PiM1_tree				->	Branch("offp",&out_offp_PiM1);
	out_PiM1_tree				->	Branch("offr",&out_offr_PiM1);
	out_PiM1_tree				->	Branch("date_time",&out_date_time_PiM1);
	
	TString		out_file_name_G_PlatForm,out_frame_G_PlatForm,out_collection_G_PlatForm,out_group_G_PlatForm,out_point_G_PlatForm,out_date_time_G_PlatForm;
	float 	out_x_G_PlatForm,out_y_G_PlatForm,out_z_G_PlatForm,out_offp_G_PlatForm,out_offr_G_PlatForm;
	
	out_G_PlatForm_tree			->	Branch("file_name",&out_file_name_G_PlatForm);
	out_G_PlatForm_tree			->	Branch("frame",&out_frame_G_PlatForm);
	out_G_PlatForm_tree			->	Branch("collection",&out_collection_G_PlatForm);
	out_G_PlatForm_tree			->	Branch("group",&out_group_G_PlatForm);
	out_G_PlatForm_tree			->	Branch("point",&out_point_G_PlatForm);
	out_G_PlatForm_tree			->	Branch("x",&out_x_G_PlatForm);
	out_G_PlatForm_tree			->	Branch("y",&out_y_G_PlatForm);
	out_G_PlatForm_tree			->	Branch("z",&out_z_G_PlatForm);
	out_G_PlatForm_tree			->	Branch("offp",&out_offp_G_PlatForm);
	out_G_PlatForm_tree			->	Branch("offr",&out_offr_G_PlatForm);
	out_G_PlatForm_tree			->	Branch("date_time",&out_date_time_G_PlatForm);

	TString		out_file_name_H_SlidingTable,out_frame_H_SlidingTable,out_collection_H_SlidingTable,out_group_H_SlidingTable,out_point_H_SlidingTable,out_date_time_H_SlidingTable;
	float 	out_x_H_SlidingTable,out_y_H_SlidingTable,out_z_H_SlidingTable,out_offp_H_SlidingTable,out_offr_H_SlidingTable;

	out_H_SlidingTable_tree		->	Branch("file_name",&out_file_name_H_SlidingTable);
	out_H_SlidingTable_tree		->	Branch("frame",&out_frame_H_SlidingTable);
	out_H_SlidingTable_tree		->	Branch("collection",&out_collection_H_SlidingTable);
	out_H_SlidingTable_tree		->	Branch("group",&out_group_H_SlidingTable);
	out_H_SlidingTable_tree		->	Branch("point",&out_point_H_SlidingTable);
	out_H_SlidingTable_tree		->	Branch("x",&out_x_H_SlidingTable);
	out_H_SlidingTable_tree		->	Branch("y",&out_y_H_SlidingTable);
	out_H_SlidingTable_tree		->	Branch("z",&out_z_H_SlidingTable);
	out_H_SlidingTable_tree		->	Branch("offp",&out_offp_H_SlidingTable);
	out_H_SlidingTable_tree		->	Branch("offr",&out_offr_H_SlidingTable);
	out_H_SlidingTable_tree		->	Branch("date_time",&out_date_time_H_SlidingTable);

	TString		out_file_name_TA_SlidingTable,out_frame_TA_SlidingTable,out_collection_TA_SlidingTable,out_group_TA_SlidingTable,out_point_TA_SlidingTable,out_date_time_TA_SlidingTable;
	float	out_x_TA_SlidingTable,out_y_TA_SlidingTable,out_z_TA_SlidingTable,out_offp_TA_SlidingTable,out_offr_TA_SlidingTable;
	
	out_TA_SlidingTable_tree	->	Branch("file_name",&out_file_name_TA_SlidingTable);
	out_TA_SlidingTable_tree	->	Branch("frame",&out_frame_TA_SlidingTable);
	out_TA_SlidingTable_tree	->	Branch("collection",&out_collection_TA_SlidingTable);
	out_TA_SlidingTable_tree	->	Branch("group",&out_group_TA_SlidingTable);
	out_TA_SlidingTable_tree	->	Branch("point",&out_point_TA_SlidingTable);
	out_TA_SlidingTable_tree	->	Branch("x",&out_x_TA_SlidingTable);
	out_TA_SlidingTable_tree	->	Branch("y",&out_y_TA_SlidingTable);
	out_TA_SlidingTable_tree	->	Branch("z",&out_z_TA_SlidingTable);
	out_TA_SlidingTable_tree	->	Branch("offp",&out_offp_TA_SlidingTable);
	out_TA_SlidingTable_tree	->	Branch("offr",&out_offr_TA_SlidingTable);
	out_TA_SlidingTable_tree	->	Branch("date_time",&out_date_time_TA_SlidingTable);

	TString		out_file_name_BM_BigBars,out_frame_BM_BigBars,out_collection_BM_BigBars,out_group_BM_BigBars,out_point_BM_BigBars,out_date_time_BM_BigBars;
	float 	out_x_BM_BigBars,out_y_BM_BigBars,out_z_BM_BigBars,out_offp_BM_BigBars,out_offr_BM_BigBars;

	out_BM_BigBars_tree			->	Branch("file_name",&out_file_name_BM_BigBars);
	out_BM_BigBars_tree			->	Branch("frame",&out_frame_BM_BigBars);
	out_BM_BigBars_tree			->	Branch("collection",&out_collection_BM_BigBars);
	out_BM_BigBars_tree			->	Branch("group",&out_group_BM_BigBars);
	out_BM_BigBars_tree			->	Branch("point",&out_point_BM_BigBars);
	out_BM_BigBars_tree			->	Branch("x",&out_x_BM_BigBars);
	out_BM_BigBars_tree			->	Branch("y",&out_y_BM_BigBars);
	out_BM_BigBars_tree			->	Branch("z",&out_z_BM_BigBars);
	out_BM_BigBars_tree			->	Branch("offp",&out_offp_BM_BigBars);
	out_BM_BigBars_tree			->	Branch("offr",&out_offr_BM_BigBars);
	out_BM_BigBars_tree			->	Branch("date_time",&out_date_time_BM_BigBars);

	TString		out_file_name_BM_Hodo,out_frame_BM_Hodo,out_collection_BM_Hodo,out_group_BM_Hodo,out_point_BM_Hodo,out_date_time_BM_Hodo;
	float 	out_x_BM_Hodo,out_y_BM_Hodo,out_z_BM_Hodo,out_offp_BM_Hodo,out_offr_BM_Hodo;

	out_BM_Hodo_tree			->	Branch("file_name",&out_file_name_BM_Hodo);
	out_BM_Hodo_tree			->	Branch("frame",&out_frame_BM_Hodo);
	out_BM_Hodo_tree			->	Branch("collection",&out_collection_BM_Hodo);
	out_BM_Hodo_tree			->	Branch("group",&out_group_BM_Hodo);
	out_BM_Hodo_tree			->	Branch("point",&out_point_BM_Hodo);
	out_BM_Hodo_tree			->	Branch("x",&out_x_BM_Hodo);
	out_BM_Hodo_tree			->	Branch("y",&out_y_BM_Hodo);
	out_BM_Hodo_tree			->	Branch("z",&out_z_BM_Hodo);
	out_BM_Hodo_tree			->	Branch("offp",&out_offp_BM_Hodo);
	out_BM_Hodo_tree			->	Branch("offr",&out_offr_BM_Hodo);
	out_BM_Hodo_tree			->	Branch("date_time",&out_date_time_BM_Hodo);

	TString		out_file_name_STT_LV60,out_frame_STT_LV60,out_collection_STT_LV60,out_group_STT_LV60,out_point_STT_LV60,out_date_time_STT_LV60;
	float 	out_x_STT_LV60,out_y_STT_LV60,out_z_STT_LV60,out_offp_STT_LV60,out_offr_STT_LV60;

	out_STT_LV60_tree			->	Branch("file_name",&out_file_name_STT_LV60);
	out_STT_LV60_tree			->	Branch("frame",&out_frame_STT_LV60);
	out_STT_LV60_tree			->	Branch("collection",&out_collection_STT_LV60);
	out_STT_LV60_tree			->	Branch("group",&out_group_STT_LV60);
	out_STT_LV60_tree			->	Branch("point",&out_point_STT_LV60);
	out_STT_LV60_tree			->	Branch("x",&out_x_STT_LV60);
	out_STT_LV60_tree			->	Branch("y",&out_y_STT_LV60);
	out_STT_LV60_tree			->	Branch("z",&out_z_STT_LV60);
	out_STT_LV60_tree			->	Branch("offp",&out_offp_STT_LV60);
	out_STT_LV60_tree			->	Branch("offr",&out_offr_STT_LV60);
	out_STT_LV60_tree			->	Branch("date_time",&out_date_time_STT_LV60);

	TString		out_file_name_STT_LH60,out_frame_STT_LH60,out_collection_STT_LH60,out_group_STT_LH60,out_point_STT_LH60,out_date_time_STT_LH60;
	float 	out_x_STT_LH60,out_y_STT_LH60,out_z_STT_LH60,out_offp_STT_LH60,out_offr_STT_LH60;

	out_STT_LH60_tree			->	Branch("file_name",&out_file_name_STT_LH60);
	out_STT_LH60_tree			->	Branch("frame",&out_frame_STT_LH60);
	out_STT_LH60_tree			->	Branch("collection",&out_collection_STT_LH60);
	out_STT_LH60_tree			->	Branch("group",&out_group_STT_LH60);
	out_STT_LH60_tree			->	Branch("point",&out_point_STT_LH60);
	out_STT_LH60_tree			->	Branch("x",&out_x_STT_LH60);
	out_STT_LH60_tree			->	Branch("y",&out_y_STT_LH60);
	out_STT_LH60_tree			->	Branch("z",&out_z_STT_LH60);
	out_STT_LH60_tree			->	Branch("offp",&out_offp_STT_LH60);
	out_STT_LH60_tree			->	Branch("offr",&out_offr_STT_LH60);
	out_STT_LH60_tree			->	Branch("date_time",&out_date_time_STT_LH60);

	TString		out_file_name_STT_LV90,out_frame_STT_LV90,out_collection_STT_LV90,out_group_STT_LV90,out_point_STT_LV90,out_date_time_STT_LV90;
	float 	out_x_STT_LV90,out_y_STT_LV90,out_z_STT_LV90,out_offp_STT_LV90,out_offr_STT_LV90;

	out_STT_LV90_tree			->	Branch("file_name",&out_file_name_STT_LV90);
	out_STT_LV90_tree			->	Branch("frame",&out_frame_STT_LV90);
	out_STT_LV90_tree			->	Branch("collection",&out_collection_STT_LV90);
	out_STT_LV90_tree			->	Branch("group",&out_group_STT_LV90);
	out_STT_LV90_tree			->	Branch("point",&out_point_STT_LV90);
	out_STT_LV90_tree			->	Branch("x",&out_x_STT_LV90);
	out_STT_LV90_tree			->	Branch("y",&out_y_STT_LV90);
	out_STT_LV90_tree			->	Branch("z",&out_z_STT_LV90);
	out_STT_LV90_tree			->	Branch("offp",&out_offp_STT_LV90);
	out_STT_LV90_tree			->	Branch("offr",&out_offr_STT_LV90);
	out_STT_LV90_tree			->	Branch("date_time",&out_date_time_STT_LV90);

	TString		out_file_name_STT_LH90,out_frame_STT_LH90,out_collection_STT_LH90,out_group_STT_LH90,out_point_STT_LH90,out_date_time_STT_LH90;
	float 	out_x_STT_LH90,out_y_STT_LH90,out_z_STT_LH90,out_offp_STT_LH90,out_offr_STT_LH90;

	out_STT_LH90_tree			->	Branch("file_name",&out_file_name_STT_LH90);
	out_STT_LH90_tree			->	Branch("frame",&out_frame_STT_LH90);
	out_STT_LH90_tree			->	Branch("collection",&out_collection_STT_LH90);
	out_STT_LH90_tree			->	Branch("group",&out_group_STT_LH90);
	out_STT_LH90_tree			->	Branch("point",&out_point_STT_LH90);
	out_STT_LH90_tree			->	Branch("x",&out_x_STT_LH90);
	out_STT_LH90_tree			->	Branch("y",&out_y_STT_LH90);
	out_STT_LH90_tree			->	Branch("z",&out_z_STT_LH90);
	out_STT_LH90_tree			->	Branch("offp",&out_offp_STT_LH90);
	out_STT_LH90_tree			->	Branch("offr",&out_offr_STT_LH90);
	out_STT_LH90_tree			->	Branch("date_time",&out_date_time_STT_LH90);

	TString		out_file_name_SPS_LF,out_frame_SPS_LF,out_collection_SPS_LF,out_group_SPS_LF,out_point_SPS_LF,out_date_time_SPS_LF;
	float 	out_x_SPS_LF,out_y_SPS_LF,out_z_SPS_LF,out_offp_SPS_LF,out_offr_SPS_LF;

	out_SPS_LF_tree				->	Branch("file_name",&out_file_name_SPS_LF);
	out_SPS_LF_tree				->	Branch("frame",&out_frame_SPS_LF);
	out_SPS_LF_tree				->	Branch("collection",&out_collection_SPS_LF);
	out_SPS_LF_tree				->	Branch("group",&out_group_SPS_LF);
	out_SPS_LF_tree				->	Branch("point",&out_point_SPS_LF);
	out_SPS_LF_tree				->	Branch("x",&out_x_SPS_LF);
	out_SPS_LF_tree				->	Branch("y",&out_y_SPS_LF);
	out_SPS_LF_tree				->	Branch("z",&out_z_SPS_LF);
	out_SPS_LF_tree				->	Branch("offp",&out_offp_SPS_LF);
	out_SPS_LF_tree				->	Branch("offr",&out_offr_SPS_LF);
	out_SPS_LF_tree				->	Branch("date_time",&out_date_time_SPS_LF);

	TString		out_file_name_SPS_LR,out_frame_SPS_LR,out_collection_SPS_LR,out_group_SPS_LR,out_point_SPS_LR,out_date_time_SPS_LR;
	float 	out_x_SPS_LR,out_y_SPS_LR,out_z_SPS_LR,out_offp_SPS_LR,out_offr_SPS_LR;

	out_SPS_LR_tree				->	Branch("file_name",&out_file_name_SPS_LR);
	out_SPS_LR_tree				->	Branch("frame",&out_frame_SPS_LR);
	out_SPS_LR_tree				->	Branch("collection",&out_collection_SPS_LR);
	out_SPS_LR_tree				->	Branch("group",&out_group_SPS_LR);
	out_SPS_LR_tree				->	Branch("point",&out_point_SPS_LR);
	out_SPS_LR_tree				->	Branch("x",&out_x_SPS_LR);
	out_SPS_LR_tree				->	Branch("y",&out_y_SPS_LR);
	out_SPS_LR_tree				->	Branch("z",&out_z_SPS_LR);
	out_SPS_LR_tree				->	Branch("offp",&out_offp_SPS_LR);
	out_SPS_LR_tree				->	Branch("offr",&out_offr_SPS_LR);
	out_SPS_LR_tree				->	Branch("date_time",&out_date_time_SPS_LR);

	TString		out_file_name_STT_RV60,out_frame_STT_RV60,out_collection_STT_RV60,out_group_STT_RV60,out_point_STT_RV60,out_date_time_STT_RV60;
	float 	out_x_STT_RV60,out_y_STT_RV60,out_z_STT_RV60,out_offp_STT_RV60,out_offr_STT_RV60;

	out_STT_RV60_tree			->	Branch("file_name",&out_file_name_STT_RV60);
	out_STT_RV60_tree			->	Branch("frame",&out_frame_STT_RV60);
	out_STT_RV60_tree			->	Branch("collection",&out_collection_STT_RV60);
	out_STT_RV60_tree			->	Branch("group",&out_group_STT_RV60);
	out_STT_RV60_tree			->	Branch("point",&out_point_STT_RV60);
	out_STT_RV60_tree			->	Branch("x",&out_x_STT_RV60);
	out_STT_RV60_tree			->	Branch("y",&out_y_STT_RV60);
	out_STT_RV60_tree			->	Branch("z",&out_z_STT_RV60);
	out_STT_RV60_tree			->	Branch("offp",&out_offp_STT_RV60);
	out_STT_RV60_tree			->	Branch("offr",&out_offr_STT_RV60);
	out_STT_RV60_tree			->	Branch("date_time",&out_date_time_STT_RV60);
	
	TString		out_file_name_STT_RH60,out_frame_STT_RH60,out_collection_STT_RH60,out_group_STT_RH60,out_point_STT_RH60,out_date_time_STT_RH60;
	float 	out_x_STT_RH60,out_y_STT_RH60,out_z_STT_RH60,out_offp_STT_RH60,out_offr_STT_RH60;
	
	out_STT_RH60_tree			->	Branch("file_name",&out_file_name_STT_RH60);
	out_STT_RH60_tree			->	Branch("frame",&out_frame_STT_RH60);
	out_STT_RH60_tree			->	Branch("collection",&out_collection_STT_RH60);
	out_STT_RH60_tree			->	Branch("group",&out_group_STT_RH60);
	out_STT_RH60_tree			->	Branch("point",&out_point_STT_RH60);
	out_STT_RH60_tree			->	Branch("x",&out_x_STT_RH60);
	out_STT_RH60_tree			->	Branch("y",&out_y_STT_RH60);
	out_STT_RH60_tree			->	Branch("z",&out_z_STT_RH60);
	out_STT_RH60_tree			->	Branch("offp",&out_offp_STT_RH60);
	out_STT_RH60_tree			->	Branch("offr",&out_offr_STT_RH60);
	out_STT_RH60_tree			->	Branch("date_time",&out_date_time_STT_RH60);

	TString		out_file_name_STT_RV90,out_frame_STT_RV90,out_collection_STT_RV90,out_group_STT_RV90,out_point_STT_RV90,out_date_time_STT_RV90;
	float 	out_x_STT_RV90,out_y_STT_RV90,out_z_STT_RV90,out_offp_STT_RV90,out_offr_STT_RV90;

	out_STT_RV90_tree			->	Branch("file_name",&out_file_name_STT_RV90);
	out_STT_RV90_tree			->	Branch("frame",&out_frame_STT_RV90);
	out_STT_RV90_tree			->	Branch("collection",&out_collection_STT_RV90);
	out_STT_RV90_tree			->	Branch("group",&out_group_STT_RV90);
	out_STT_RV90_tree			->	Branch("point",&out_point_STT_RV90);
	out_STT_RV90_tree			->	Branch("x",&out_x_STT_RV90);
	out_STT_RV90_tree			->	Branch("y",&out_y_STT_RV90);
	out_STT_RV90_tree			->	Branch("z",&out_z_STT_RV90);
	out_STT_RV90_tree			->	Branch("offp",&out_offp_STT_RV90);
	out_STT_RV90_tree			->	Branch("offr",&out_offr_STT_RV90);
	out_STT_RV90_tree			->	Branch("date_time",&out_date_time_STT_RV90);

	TString		out_file_name_STT_RH90,out_frame_STT_RH90,out_collection_STT_RH90,out_group_STT_RH90,out_point_STT_RH90,out_date_time_STT_RH90;
	float 	out_x_STT_RH90,out_y_STT_RH90,out_z_STT_RH90,out_offp_STT_RH90,out_offr_STT_RH90;

	out_STT_RH90_tree			->	Branch("file_name",&out_file_name_STT_RH90);
	out_STT_RH90_tree			->	Branch("frame",&out_frame_STT_RH90);
	out_STT_RH90_tree			->	Branch("collection",&out_collection_STT_RH90);
	out_STT_RH90_tree			->	Branch("group",&out_group_STT_RH90);
	out_STT_RH90_tree			->	Branch("point",&out_point_STT_RH90);
	out_STT_RH90_tree			->	Branch("x",&out_x_STT_RH90);
	out_STT_RH90_tree			->	Branch("y",&out_y_STT_RH90);
	out_STT_RH90_tree			->	Branch("z",&out_z_STT_RH90);
	out_STT_RH90_tree			->	Branch("offp",&out_offp_STT_RH90);
	out_STT_RH90_tree			->	Branch("offr",&out_offr_STT_RH90);
	out_STT_RH90_tree			->	Branch("date_time",&out_date_time_STT_RH90);

	TString		out_file_name_SPS_RF,out_frame_SPS_RF,out_collection_SPS_RF,out_group_SPS_RF,out_point_SPS_RF,out_date_time_SPS_RF;
	float 	out_x_SPS_RF,out_y_SPS_RF,out_z_SPS_RF,out_offp_SPS_RF,out_offr_SPS_RF;

	out_SPS_RF_tree				->	Branch("file_name",&out_file_name_SPS_RF);
	out_SPS_RF_tree				->	Branch("frame",&out_frame_SPS_RF);
	out_SPS_RF_tree				->	Branch("collection",&out_collection_SPS_RF);
	out_SPS_RF_tree				->	Branch("group",&out_group_SPS_RF);
	out_SPS_RF_tree				->	Branch("point",&out_point_SPS_RF);
	out_SPS_RF_tree				->	Branch("x",&out_x_SPS_RF);
	out_SPS_RF_tree				->	Branch("y",&out_y_SPS_RF);
	out_SPS_RF_tree				->	Branch("z",&out_z_SPS_RF);
	out_SPS_RF_tree				->	Branch("offp",&out_offp_SPS_RF);
	out_SPS_RF_tree				->	Branch("offr",&out_offr_SPS_RF);
	out_SPS_RF_tree				->	Branch("date_time",&out_date_time_SPS_RF);

	TString		out_file_name_SPS_RR,out_frame_SPS_RR,out_collection_SPS_RR,out_group_SPS_RR,out_point_SPS_RR,out_date_time_SPS_RR;
	float 	out_x_SPS_RR,out_y_SPS_RR,out_z_SPS_RR,out_offp_SPS_RR,out_offr_SPS_RR;

	out_SPS_RR_tree				->	Branch("file_name",&out_file_name_SPS_RR);
	out_SPS_RR_tree				->	Branch("frame",&out_frame_SPS_RR);
	out_SPS_RR_tree				->	Branch("collection",&out_collection_SPS_RR);
	out_SPS_RR_tree				->	Branch("group",&out_group_SPS_RR);
	out_SPS_RR_tree				->	Branch("point",&out_point_SPS_RR);
	out_SPS_RR_tree				->	Branch("x",&out_x_SPS_RR);
	out_SPS_RR_tree				->	Branch("y",&out_y_SPS_RR);
	out_SPS_RR_tree				->	Branch("z",&out_z_SPS_RR);
	out_SPS_RR_tree				->	Branch("offp",&out_offp_SPS_RR);
	out_SPS_RR_tree				->	Branch("offr",&out_offr_SPS_RR);
	out_SPS_RR_tree				->	Branch("date_time",&out_date_time_SPS_RR);

	TString		out_file_name_M_STT,out_frame_M_STT,out_collection_M_STT,out_group_M_STT,out_point_M_STT,out_date_time_M_STT;
	float 	out_x_M_STT,out_y_M_STT,out_z_M_STT,out_offp_M_STT,out_offr_M_STT;

	out_M_STT_tree				->	Branch("file_name",&out_file_name_M_STT);
	out_M_STT_tree				->	Branch("frame",&out_frame_M_STT);
	out_M_STT_tree				->	Branch("collection",&out_collection_M_STT);
	out_M_STT_tree				->	Branch("group",&out_group_M_STT);
	out_M_STT_tree				->	Branch("point",&out_point_M_STT);
	out_M_STT_tree				->	Branch("x",&out_x_M_STT);
	out_M_STT_tree				->	Branch("y",&out_y_M_STT);
	out_M_STT_tree				->	Branch("z",&out_z_M_STT);
	out_M_STT_tree				->	Branch("offp",&out_offp_M_STT);
	out_M_STT_tree				->	Branch("offr",&out_offr_M_STT);
	out_M_STT_tree				->	Branch("date_time",&out_date_time_M_STT);

	TString		out_file_name_HP,out_frame_HP,out_collection_HP,out_group_HP,out_point_HP,out_date_time_HP;
	float 	out_x_HP,out_y_HP,out_z_HP,out_offp_HP,out_offr_HP;

	out_HP_tree				->	Branch("file_name",&out_file_name_HP);
	out_HP_tree				->	Branch("frame",&out_frame_HP);
	out_HP_tree				->	Branch("collection",&out_collection_HP);
	out_HP_tree				->	Branch("group",&out_group_HP);
	out_HP_tree				->	Branch("point",&out_point_HP);
	out_HP_tree				->	Branch("x",&out_x_HP);
	out_HP_tree				->	Branch("y",&out_y_HP);
	out_HP_tree				->	Branch("z",&out_z_HP);
	out_HP_tree				->	Branch("offp",&out_offp_HP);
	out_HP_tree				->	Branch("offr",&out_offr_HP);
	out_HP_tree				->	Branch("date_time",&out_date_time_HP);


	TString		out_file_name_PA6,out_frame_PA6,out_collection_PA6,out_group_PA6,out_point_PA6,out_date_time_PA6;
	float 	out_x_PA6,out_y_PA6,out_z_PA6,out_offp_PA6,out_offr_PA6;

	out_PA6_tree				->	Branch("file_name",&out_file_name_PA6);
	out_PA6_tree				->	Branch("frame",&out_frame_PA6);
	out_PA6_tree				->	Branch("collection",&out_collection_PA6);
	out_PA6_tree				->	Branch("group",&out_group_PA6);
	out_PA6_tree				->	Branch("point",&out_point_PA6);
	out_PA6_tree				->	Branch("x",&out_x_PA6);
	out_PA6_tree				->	Branch("y",&out_y_PA6);
	out_PA6_tree				->	Branch("z",&out_z_PA6);
	out_PA6_tree				->	Branch("offp",&out_offp_PA6);
	out_PA6_tree				->	Branch("offr",&out_offr_PA6);
	out_PA6_tree				->	Branch("date_time",&out_date_time_PA6);


	TString		out_file_name_PA7,out_frame_PA7,out_collection_PA7,out_group_PA7,out_point_PA7,out_date_time_PA7;
	float 	out_x_PA7,out_y_PA7,out_z_PA7,out_offp_PA7,out_offr_PA7;

	out_PA7_tree				->	Branch("file_name",&out_file_name_PA7);
	out_PA7_tree				->	Branch("frame",&out_frame_PA7);
	out_PA7_tree				->	Branch("collection",&out_collection_PA7);
	out_PA7_tree				->	Branch("group",&out_group_PA7);
	out_PA7_tree				->	Branch("point",&out_point_PA7);
	out_PA7_tree				->	Branch("x",&out_x_PA7);
	out_PA7_tree				->	Branch("y",&out_y_PA7);
	out_PA7_tree				->	Branch("z",&out_z_PA7);
	out_PA7_tree				->	Branch("offp",&out_offp_PA7);
	out_PA7_tree				->	Branch("offr",&out_offr_PA7);
	out_PA7_tree				->	Branch("date_time",&out_date_time_PA7);

	TString		out_file_name_Kreis,out_frame_Kreis,out_collection_Kreis,out_group_Kreis,out_point_Kreis,out_date_time_Kreis;
	float 	out_x_Kreis,out_y_Kreis,out_z_Kreis,out_offp_Kreis,out_offr_Kreis;

	out_Kreis_tree				->	Branch("file_name",&out_file_name_Kreis);
	out_Kreis_tree				->	Branch("frame",&out_frame_Kreis);
	out_Kreis_tree				->	Branch("collection",&out_collection_Kreis);
	out_Kreis_tree				->	Branch("group",&out_group_Kreis);
	out_Kreis_tree				->	Branch("point",&out_point_Kreis);
	out_Kreis_tree				->	Branch("x",&out_x_Kreis);
	out_Kreis_tree				->	Branch("y",&out_y_Kreis);
	out_Kreis_tree				->	Branch("z",&out_z_Kreis);
	out_Kreis_tree				->	Branch("offp",&out_offp_Kreis);
	out_Kreis_tree				->	Branch("offr",&out_offr_Kreis);
	out_Kreis_tree				->	Branch("date_time",&out_date_time_Kreis);



	for(int i=0;i<point_vec.size();i++)
	{

//	defining a flag of the point name is recognized in the points vector (=1), if not (=0).

	int	PiM1_flag				=	0;
	int	G_PlatForm_flag			=	0;
	int	H_SlidingTable_flag		=	0;
	int	TA_SlidingTable_flag	=	0;
	int	BM_BigBars_flag			=	0;
	int	BM_Hodo_flag			=	0;
	int	STT_LV60_flag			=	0;
	int	STT_LH60_flag			=	0;
	int	STT_LV90_flag			=	0;
	int	STT_LH90_flag			=	0;
	int	SPS_LF_flag				=	0;
	int	SPS_LR_flag				=	0;
	int	STT_RV60_flag			=	0;
	int	STT_RH60_flag			=	0;
	int	STT_RV90_flag			=	0;
	int	STT_RH90_flag			=	0;
	int	SPS_RF_flag				=	0;
	int	SPS_RR_flag				=	0;
	int M_STT_flag				=	0;
	int HP_flag					=	0;
	int PA6_flag				=	0;
	int PA7_flag				=	0;
	int Kreis_flag				=	0;
	int G_group_flag			=	0;
	int TG_flag					=	0;
	int flag_2E2				=	0;
	int flag_2E1				=	0;
	int TC1_flag				=	0;
	int TC2_flag				=	0;
	int TC3_flag				=	0;
	int BFM_PiM1_flag			=	0;
	int Flaeche_PiM1_flag		=	0;
	int Draht_PiM1_flag			=	0;
	int Panel9O_flag			=	0;
	int Panel10O_flag			=	0;
	int Panel11O_flag			=	0;
	int Panel12O_flag			=	0;
	int Leiter3_1_flag			=	0;
	int Fenster_flag			=	0;
	int loc_BFM_flag			=	0;

		bool tmp_1;
		bool tmp_2;


		if(frame_vec[i]=="202209006_Wdh_mit_Gasdruck::Koordinatensystem_Instr2" && group_vec[i]=="BFM")	{loc_BFM_flag=1;}

		if(group_vec[i]==("Fenster"))		{Fenster_flag=1;}

		if(frame_vec[i]=="20210430::PIM1" && group_vec[i].Contains("Leiter3-"))										{Leiter3_1_flag=1;}
		if(frame_vec[i]=="20210601-_Aufmasse_MUSE::PIM1" && group_vec[i].Contains("Leiter3-"))						{Leiter3_1_flag=1;}
		if(frame_vec[i]=="20210928_Justierung_Vakuumkammer_und_Target::PIM1" && group_vec[i].Contains("Leiter3-"))	{Leiter3_1_flag=1;}

		if(frame_vec[i]=="20220119_Kontrolle_Rahmen::PIM1" && group_vec[i]=="BFM")			{BFM_PiM1_flag=1;}
		if(frame_vec[i]=="20220119_Kontrolle_Rahmen::PIM1" && group_vec[i]=="Flaeche")		{Flaeche_PiM1_flag=1;}
		if(frame_vec[i]=="20220119_Kontrolle_Rahmen::PIM1" && group_vec[i]=="Draht")		{Draht_PiM1_flag=1;}

		if(group_vec[i].Contains("Panel9O"))		{Panel9O_flag=1;}
		if(group_vec[i].Contains("Panel10O"))		{Panel10O_flag=1;}
		if(group_vec[i].Contains("Panel11O"))		{Panel11O_flag=1;}
		if(group_vec[i].Contains("Panel12O"))		{Panel12O_flag=1;}

		if( point_vec[i].Contains("PIM1"))	{PiM1_flag=1;}
		
		string H=(string) point_vec[i];
		if(H.compare("H")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H0")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H1")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H2")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H3")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H4")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H5")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H6")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H7")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H8")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H9")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H10")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H11")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H12")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H13")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H14")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H15")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H16")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H17")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H18")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H19")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H20")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H21")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H22")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H23")==0)		{H_SlidingTable_flag=1;}
		if(H.compare("H24")==0)		{H_SlidingTable_flag=1;}

		if( point_vec[i].Contains("TA"))	{TA_SlidingTable_flag=1;}
		if( point_vec[i].Contains("M"))		{M_STT_flag=1;}
		if( point_vec[i].Contains("HP"))	{HP_flag=1;}
		if( point_vec[i].Contains("PA6"))	{PA6_flag=1;}
		if( point_vec[i].Contains("PA7"))	{PA7_flag=1;}

		H =(string) group_vec[i];
		if( H.compare("Kreis")==0)		{Kreis_flag=1;}

		H =(string) group_vec[i];
		if( H.compare("G1")==0)		{G_group_flag=1;}
		if( H.compare("G2")==0)		{G_group_flag=1;}
		if( H.compare("G3")==0)		{G_group_flag=1;}
		if( H.compare("G4")==0)		{G_group_flag=1;}
		if( H.compare("G5")==0)		{G_group_flag=1;}
		if( H.compare("G6")==0)		{G_group_flag=1;}
		if( H.compare("G7")==0)		{G_group_flag=1;}

		H =(string) point_vec[i];
		if( H.compare("G1")==0)		{G_PlatForm_flag=1;}
		if( H.compare("G2")==0)		{G_PlatForm_flag=1;}
		if( H.compare("G3")==0)		{G_PlatForm_flag=1;}
		if( H.compare("G4")==0)		{G_PlatForm_flag=1;}
		if( H.compare("G5")==0)		{G_PlatForm_flag=1;}
		
		H =(string) group_vec[i];
		if( H.compare("TC1")==0)		{TC1_flag=1;}
		if( H.compare("TC2")==0)		{TC2_flag=1;}
		if( H.compare("TC3")==0)		{TC3_flag=1;}

		if( point_vec[i].Contains("TG-"))	{TG_flag=1;}

		if( group_vec[i].Contains("Position2E1"))	{flag_2E1=1;}


		if( group_vec[i].Contains("Position2E2"))	{flag_2E2=1;}




		int	tot_flag=0;
			tot_flag=tot_flag+G_group_flag+Kreis_flag+PA6_flag+PA7_flag+HP_flag+PiM1_flag+G_PlatForm_flag+H_SlidingTable_flag;
			tot_flag=tot_flag+TA_SlidingTable_flag+BM_BigBars_flag+BM_Hodo_flag+STT_LV60_flag+STT_LH60_flag;
			tot_flag=tot_flag+STT_LV90_flag+STT_LH90_flag+SPS_LF_flag+SPS_LR_flag+STT_RV60_flag+STT_RH60_flag+STT_RV90_flag+STT_RH90_flag;
			tot_flag=tot_flag+SPS_RF_flag+SPS_RR_flag+M_STT_flag+flag_2E2+flag_2E1+TC1_flag+TC2_flag+TC3_flag+BFM_PiM1_flag+Draht_PiM1_flag;	
			tot_flag=tot_flag+G_PlatForm_flag+Flaeche_PiM1_flag+TG_flag+Leiter3_1_flag+Fenster_flag+loc_BFM_flag;
			tot_flag=tot_flag+Panel9O_flag+Panel10O_flag+Panel11O_flag+Panel12O_flag;

		if (tot_flag>0)		{	detectors_flag_vec.push_back(1);	}
		if (tot_flag==0)	{	detectors_flag_vec.push_back(0);	}




//	if(detectors_flag_vec[i]==1)cout<<i+1<<" ) "<<point_vec[i]<<"	|	";

//	filling each tree branches.



			if(loc_BFM_flag==1)				
				{
					out_file_name_loc_BFM	=	file_name_vec[i];
					out_frame_loc_BFM		=	frame_vec[i];
					out_collection_loc_BFM	=	collection_vec[i];
					out_group_loc_BFM		=	group_vec[i];
					out_point_loc_BFM		=	point_vec[i];
					out_x_loc_BFM			=	x_vec[i];
					out_y_loc_BFM			=	y_vec[i];
					out_z_loc_BFM			=	x_vec[i];
					out_offp_loc_BFM		=	offp_vec[i];
					out_offr_loc_BFM		=	offr_vec[i];
					out_date_time_loc_BFM	=	date_time_vec[i];

					out_loc_BFM_tree	-> 	Fill();
				}

			if(Fenster_flag==1)				
				{
					out_file_name_Fenster	=	file_name_vec[i];
					out_frame_Fenster		=	frame_vec[i];
					out_collection_Fenster	=	collection_vec[i];
					out_group_Fenster		=	group_vec[i];
					out_point_Fenster		=	point_vec[i];
					out_x_Fenster			=	x_vec[i];
					out_y_Fenster			=	y_vec[i];
					out_z_Fenster			=	x_vec[i];
					out_offp_Fenster		=	offp_vec[i];
					out_offr_Fenster		=	offr_vec[i];
					out_date_time_Fenster	=	date_time_vec[i];

					out_Fenster_tree	-> 	Fill();
				}

			if(Leiter3_1_flag==1)				
				{
					out_file_name_Leiter3_1	=	file_name_vec[i];
					out_frame_Leiter3_1		=	frame_vec[i];
					out_collection_Leiter3_1=	collection_vec[i];
					out_group_Leiter3_1		=	group_vec[i];
					out_point_Leiter3_1		=	point_vec[i];
					out_x_Leiter3_1			=	x_vec[i];
					out_y_Leiter3_1			=	y_vec[i];
					out_z_Leiter3_1			=	x_vec[i];
					out_offp_Leiter3_1		=	offp_vec[i];
					out_offr_Leiter3_1		=	offr_vec[i];
					out_date_time_Leiter3_1	=	date_time_vec[i];

					out_Leiter3_1_tree	-> 	Fill();
				}

			if(Panel9O_flag==1)				
				{
					out_file_name_Panel9O	=	file_name_vec[i];
					out_frame_Panel9O		=	frame_vec[i];
					out_collection_Panel9O	=	collection_vec[i];
					out_group_Panel9O		=	group_vec[i];
					out_point_Panel9O		=	point_vec[i];
					out_x_Panel9O			=	x_vec[i];
					out_y_Panel9O			=	y_vec[i];
					out_z_Panel9O			=	x_vec[i];
					out_offp_Panel9O		=	offp_vec[i];
					out_offr_Panel9O		=	offr_vec[i];
					out_date_time_Panel9O	=	date_time_vec[i];

					out_Panel9O_tree	-> 	Fill();
				}

			if(Panel10O_flag==1)				
				{
					out_file_name_Panel10O	=	file_name_vec[i];
					out_frame_Panel10O		=	frame_vec[i];
					out_collection_Panel10O	=	collection_vec[i];
					out_group_Panel10O		=	group_vec[i];
					out_point_Panel10O		=	point_vec[i];
					out_x_Panel10O			=	x_vec[i];
					out_y_Panel10O			=	y_vec[i];
					out_z_Panel10O			=	x_vec[i];
					out_offp_Panel10O		=	offp_vec[i];
					out_offr_Panel10O		=	offr_vec[i];
					out_date_time_Panel10O	=	date_time_vec[i];

					out_Panel10O_tree	-> 	Fill();
				}

			if(Panel11O_flag==1)				
				{
					out_file_name_Panel11O	=	file_name_vec[i];
					out_frame_Panel11O		=	frame_vec[i];
					out_collection_Panel11O	=	collection_vec[i];
					out_group_Panel11O		=	group_vec[i];
					out_point_Panel11O		=	point_vec[i];
					out_x_Panel11O			=	x_vec[i];
					out_y_Panel11O			=	y_vec[i];
					out_z_Panel11O			=	x_vec[i];
					out_offp_Panel11O		=	offp_vec[i];
					out_offr_Panel11O		=	offr_vec[i];
					out_date_time_Panel11O	=	date_time_vec[i];

					out_Panel11O_tree	-> 	Fill();
				}

			if(Panel12O_flag==1)				
				{
					out_file_name_Panel12O	=	file_name_vec[i];
					out_frame_Panel12O		=	frame_vec[i];
					out_collection_Panel12O	=	collection_vec[i];
					out_group_Panel12O		=	group_vec[i];
					out_point_Panel12O		=	point_vec[i];
					out_x_Panel12O			=	x_vec[i];
					out_y_Panel12O			=	y_vec[i];
					out_z_Panel12O			=	x_vec[i];
					out_offp_Panel12O		=	offp_vec[i];
					out_offr_Panel12O		=	offr_vec[i];
					out_date_time_Panel12O	=	date_time_vec[i];

					out_Panel12O_tree	-> 	Fill();
				}

			if(Draht_PiM1_flag==1)				
				{
					out_file_name_Draht_PiM1	=	file_name_vec[i];
					out_frame_Draht_PiM1		=	frame_vec[i];
					out_collection_Draht_PiM1	=	collection_vec[i];
					out_group_Draht_PiM1		=	group_vec[i];
					out_point_Draht_PiM1		=	point_vec[i];
					out_x_Draht_PiM1			=	x_vec[i];
					out_y_Draht_PiM1			=	y_vec[i];
					out_z_Draht_PiM1			=	x_vec[i];
					out_offp_Draht_PiM1			=	offp_vec[i];
					out_offr_Draht_PiM1			=	offr_vec[i];
					out_date_time_Draht_PiM1	=	date_time_vec[i];

					out_Draht_PiM1_tree	-> 	Fill();
				}

			if(BFM_PiM1_flag==1)				
				{
					out_file_name_BFM_PiM1	=	file_name_vec[i];
					out_frame_BFM_PiM1		=	frame_vec[i];
					out_collection_BFM_PiM1	=	collection_vec[i];
					out_group_BFM_PiM1		=	group_vec[i];
					out_point_BFM_PiM1		=	point_vec[i];
					out_x_BFM_PiM1			=	x_vec[i];
					out_y_BFM_PiM1			=	y_vec[i];
					out_z_BFM_PiM1			=	x_vec[i];
					out_offp_BFM_PiM1		=	offp_vec[i];
					out_offr_BFM_PiM1		=	offr_vec[i];
					out_date_time_BFM_PiM1	=	date_time_vec[i];

					out_BFM_PiM1_tree	-> 	Fill();
				}
			
			if(Flaeche_PiM1_flag==1)				
				{
					out_file_name_Flaeche_PiM1	=	file_name_vec[i];
					out_frame_Flaeche_PiM1		=	frame_vec[i];
					out_collection_Flaeche_PiM1	=	collection_vec[i];
					out_group_Flaeche_PiM1		=	group_vec[i];
					out_point_Flaeche_PiM1		=	point_vec[i];
					out_x_Flaeche_PiM1			=	x_vec[i];
					out_y_Flaeche_PiM1			=	y_vec[i];
					out_z_Flaeche_PiM1			=	x_vec[i];
					out_offp_Flaeche_PiM1		=	offp_vec[i];
					out_offr_Flaeche_PiM1		=	offr_vec[i];
					out_date_time_Flaeche_PiM1	=	date_time_vec[i];

					out_Flaeche_PiM1_tree	-> 	Fill();
				}

			if(TC1_flag==1)				
				{
					out_file_name_TC1	=	file_name_vec[i];
					out_frame_TC1		=	frame_vec[i];
					out_collection_TC1	=	collection_vec[i];
					out_group_TC1		=	group_vec[i];
					out_point_TC1		=	point_vec[i];
					out_x_TC1			=	x_vec[i];
					out_y_TC1			=	y_vec[i];
					out_z_TC1			=	x_vec[i];
					out_offp_TC1		=	offp_vec[i];
					out_offr_TC1		=	offr_vec[i];
					out_date_time_TC1	=	date_time_vec[i];

					out_TC1_tree	-> 	Fill();
				}

			if(TC2_flag==1)				
				{
					out_file_name_TC2	=	file_name_vec[i];
					out_frame_TC2		=	frame_vec[i];
					out_collection_TC2	=	collection_vec[i];
					out_group_TC2		=	group_vec[i];
					out_point_TC2		=	point_vec[i];
					out_x_TC2			=	x_vec[i];
					out_y_TC2			=	y_vec[i];
					out_z_TC2			=	x_vec[i];
					out_offp_TC2		=	offp_vec[i];
					out_offr_TC2		=	offr_vec[i];
					out_date_time_TC2	=	date_time_vec[i];

					out_TC2_tree	-> 	Fill();
				}

			if(TC3_flag==1)				
				{
					out_file_name_TC3	=	file_name_vec[i];
					out_frame_TC3		=	frame_vec[i];
					out_collection_TC3	=	collection_vec[i];
					out_group_TC3		=	group_vec[i];
					out_point_TC3		=	point_vec[i];
					out_x_TC3			=	x_vec[i];
					out_y_TC3			=	y_vec[i];
					out_z_TC3			=	x_vec[i];
					out_offp_TC3		=	offp_vec[i];
					out_offr_TC3		=	offr_vec[i];
					out_date_time_TC3	=	date_time_vec[i];

					out_TC3_tree	-> 	Fill();
				}

			if(flag_2E1==1)				
				{
					out_file_name_2E1	=	file_name_vec[i];
					out_frame_2E1		=	frame_vec[i];
					out_collection_2E1	=	collection_vec[i];
					out_group_2E1		=	group_vec[i];
					out_point_2E1		=	point_vec[i];
					out_x_2E1			=	x_vec[i];
					out_y_2E1			=	y_vec[i];
					out_z_2E1			=	x_vec[i];
					out_offp_2E1		=	offp_vec[i];
					out_offr_2E1		=	offr_vec[i];
					out_date_time_2E1	=	date_time_vec[i];

					out_2E1_tree	-> 	Fill();
				}

			if(flag_2E2==1)				
				{
					out_file_name_2E2	=	file_name_vec[i];
					out_frame_2E2		=	frame_vec[i];
					out_collection_2E2	=	collection_vec[i];
					out_group_2E2		=	group_vec[i];
					out_point_2E2		=	point_vec[i];
					out_x_2E2			=	x_vec[i];
					out_y_2E2			=	y_vec[i];
					out_z_2E2			=	x_vec[i];
					out_offp_2E2		=	offp_vec[i];
					out_offr_2E2		=	offr_vec[i];
					out_date_time_2E2	=	date_time_vec[i];

					out_2E2_tree	-> 	Fill();
				}

			if(G_group_flag==1)				
				{
					out_file_name_G_group	=	file_name_vec[i];
					out_frame_G_group		=	frame_vec[i];
					out_collection_G_group	=	collection_vec[i];
					out_group_G_group		=	group_vec[i];
					out_point_G_group		=	point_vec[i];
					out_x_G_group			=	x_vec[i];
					out_y_G_group			=	y_vec[i];
					out_z_G_group			=	x_vec[i];
					out_offp_G_group		=	offp_vec[i];
					out_offr_G_group		=	offr_vec[i];
					out_date_time_G_group	=	date_time_vec[i];

					out_G_group_tree	-> 	Fill();
				}

			if(TG_flag==1)				
				{
					out_file_name_TG	=	file_name_vec[i];
					out_frame_TG		=	frame_vec[i];
					out_collection_TG	=	collection_vec[i];
					out_group_TG		=	group_vec[i];
					out_point_TG		=	point_vec[i];
					out_x_TG			=	x_vec[i];
					out_y_TG			=	y_vec[i];
					out_z_TG			=	x_vec[i];
					out_offp_TG			=	offp_vec[i];
					out_offr_TG			=	offr_vec[i];
					out_date_time_TG	=	date_time_vec[i];

					out_TG_tree	-> 	Fill();
				}

			if(HP_flag==1)				
				{
					out_file_name_HP	=	file_name_vec[i];
					out_frame_HP		=	frame_vec[i];
					out_collection_HP	=	collection_vec[i];
					out_group_HP		=	group_vec[i];
					out_point_HP		=	point_vec[i];
					out_x_HP			=	x_vec[i];
					out_y_HP			=	y_vec[i];
					out_z_HP			=	x_vec[i];
					out_offp_HP			=	offp_vec[i];
					out_offr_HP			=	offr_vec[i];
					out_date_time_HP	=	date_time_vec[i];

					out_HP_tree	-> 	Fill();
				}

			if(PiM1_flag==1)				
				{
					out_file_name_PiM1	=	file_name_vec[i];
					out_frame_PiM1		=	frame_vec[i];
					out_collection_PiM1	=	collection_vec[i];
					out_group_PiM1		=	group_vec[i];
					out_point_PiM1		=	point_vec[i];
					out_x_PiM1			=	x_vec[i];
					out_y_PiM1			=	y_vec[i];
					out_z_PiM1			=	x_vec[i];
					out_offp_PiM1		=	offp_vec[i];
					out_offr_PiM1		=	offr_vec[i];
					out_date_time_PiM1	=	date_time_vec[i];

					out_PiM1_tree	-> 	Fill();
				}

			if(H_SlidingTable_flag==1)				
				{
					out_file_name_H_SlidingTable	=	file_name_vec[i];
					out_frame_H_SlidingTable		=	frame_vec[i];
					out_collection_H_SlidingTable	=	collection_vec[i];
					out_group_H_SlidingTable		=	group_vec[i];
					out_point_H_SlidingTable		=	point_vec[i];
					out_x_H_SlidingTable			=	x_vec[i];
					out_y_H_SlidingTable			=	y_vec[i];
					out_z_H_SlidingTable			=	x_vec[i];
					out_offp_H_SlidingTable			=	offp_vec[i];
					out_offr_H_SlidingTable			=	offr_vec[i];
					out_date_time_H_SlidingTable	=	date_time_vec[i];

					out_H_SlidingTable_tree	-> 	Fill();
				}

			if(TA_SlidingTable_flag==1)				
				{
					out_file_name_TA_SlidingTable	=	file_name_vec[i];
					out_frame_TA_SlidingTable		=	frame_vec[i];
					out_collection_TA_SlidingTable	=	collection_vec[i];
					out_group_TA_SlidingTable		=	group_vec[i];
					out_point_TA_SlidingTable		=	point_vec[i];
					out_x_TA_SlidingTable			=	x_vec[i];
					out_y_TA_SlidingTable			=	y_vec[i];
					out_z_TA_SlidingTable			=	x_vec[i];
					out_offp_TA_SlidingTable		=	offp_vec[i];
					out_offr_TA_SlidingTable		=	offr_vec[i];
					out_date_time_TA_SlidingTable	=	date_time_vec[i];

					out_TA_SlidingTable_tree-> 	Fill();
				}
	
			if(G_PlatForm_flag==1)				
				{
					out_file_name_G_PlatForm	=	file_name_vec[i];
					out_frame_G_PlatForm		=	frame_vec[i];
					out_collection_G_PlatForm	=	collection_vec[i];
					out_group_G_PlatForm		=	group_vec[i];
					out_point_G_PlatForm		=	point_vec[i];
					out_x_G_PlatForm			=	x_vec[i];
					out_y_G_PlatForm			=	y_vec[i];
					out_z_G_PlatForm			=	x_vec[i];
					out_offp_G_PlatForm			=	offp_vec[i];
					out_offr_G_PlatForm			=	offr_vec[i];
					out_date_time_G_PlatForm	=	date_time_vec[i];

					out_G_PlatForm_tree		-> Fill();
				}

			if(BM_BigBars_flag==1)				
				{
					out_file_name_BM_BigBars	=	file_name_vec[i];
					out_frame_BM_BigBars		=	frame_vec[i];
					out_collection_BM_BigBars	=	collection_vec[i];
					out_group_BM_BigBars		=	group_vec[i];
					out_point_BM_BigBars		=	point_vec[i];
					out_x_BM_BigBars			=	x_vec[i];
					out_y_BM_BigBars			=	y_vec[i];
					out_z_BM_BigBars			=	x_vec[i];
					out_offp_BM_BigBars			=	offp_vec[i];
					out_offr_BM_BigBars			=	offr_vec[i];
					out_date_time_BM_BigBars	=	date_time_vec[i];

					out_BM_BigBars_tree		-> 	Fill();
				}
	
			if(BM_Hodo_flag==1)				
				{
					out_file_name_BM_Hodo	=	file_name_vec[i];
					out_frame_BM_Hodo		=	frame_vec[i];
					out_collection_BM_Hodo	=	collection_vec[i];
					out_group_BM_Hodo		=	group_vec[i];
					out_point_BM_Hodo		=	point_vec[i];
					out_x_BM_Hodo			=	x_vec[i];
					out_y_BM_Hodo			=	y_vec[i];
					out_z_BM_Hodo			=	x_vec[i];
					out_offp_BM_Hodo		=	offp_vec[i];
					out_offr_BM_Hodo		=	offr_vec[i];
					out_date_time_BM_Hodo	=	date_time_vec[i];

					out_BM_Hodo_tree		-> 	Fill();
				}

			if(STT_LV60_flag==1)				
				{
					out_file_name_STT_LV60	=	file_name_vec[i];
					out_frame_STT_LV60		=	frame_vec[i];
					out_collection_STT_LV60	=	collection_vec[i];
					out_group_STT_LV60		=	group_vec[i];
					out_point_STT_LV60		=	point_vec[i];
					out_x_STT_LV60			=	x_vec[i];
					out_y_STT_LV60			=	y_vec[i];
					out_z_STT_LV60			=	x_vec[i];
					out_offp_STT_LV60		=	offp_vec[i];
					out_offr_STT_LV60		=	offr_vec[i];
					out_date_time_STT_LV60	=	date_time_vec[i];

					out_STT_LV60_tree		-> 	Fill();
				}
	
			if(STT_LH60_flag==1)				
				{
					out_file_name_STT_LH60	=	file_name_vec[i];
					out_frame_STT_LH60		=	frame_vec[i];
					out_collection_STT_LH60	=	collection_vec[i];
					out_group_STT_LH60		=	group_vec[i];
					out_point_STT_LH60		=	point_vec[i];
					out_x_STT_LH60			=	x_vec[i];
					out_y_STT_LH60			=	y_vec[i];
					out_z_STT_LH60			=	x_vec[i];
					out_offp_STT_LH60		=	offp_vec[i];
					out_offr_STT_LH60		=	offr_vec[i];
					out_date_time_STT_LH60	=	date_time_vec[i];

					out_STT_LH60_tree		-> 	Fill();
				}

			if(STT_LV90_flag==1)				
				{
					out_file_name_STT_LV90	=	file_name_vec[i];
					out_frame_STT_LV90		=	frame_vec[i];
					out_collection_STT_LV90	=	collection_vec[i];
					out_group_STT_LV90		=	group_vec[i];
					out_point_STT_LV90		=	point_vec[i];
					out_x_STT_LV90			=	x_vec[i];
					out_y_STT_LV90			=	y_vec[i];
					out_z_STT_LV90			=	x_vec[i];
					out_offp_STT_LV90		=	offp_vec[i];
					out_offr_STT_LV90		=	offr_vec[i];
					out_date_time_STT_LV90	=	date_time_vec[i];

					out_STT_LV90_tree		-> 	Fill();
				}

			if(STT_LH90_flag==1)				
				{
					out_file_name_STT_LH90	=	file_name_vec[i];
					out_frame_STT_LH90		=	frame_vec[i];
					out_collection_STT_LH90	=	collection_vec[i];
					out_group_STT_LH90		=	group_vec[i];
					out_point_STT_LH90		=	point_vec[i];
					out_x_STT_LH90			=	x_vec[i];
					out_y_STT_LH90			=	y_vec[i];
					out_z_STT_LH90			=	x_vec[i];
					out_offp_STT_LH90		=	offp_vec[i];
					out_offr_STT_LH90		=	offr_vec[i];
					out_date_time_STT_LH90	=	date_time_vec[i];

					out_STT_LH90_tree		-> 	Fill();
				}

			if(SPS_LF_flag==1)				
				{
					out_file_name_SPS_LF	=	file_name_vec[i];
					out_frame_SPS_LF		=	frame_vec[i];
					out_collection_SPS_LF	=	collection_vec[i];
					out_group_SPS_LF		=	group_vec[i];
					out_point_SPS_LF		=	point_vec[i];
					out_x_SPS_LF			=	x_vec[i];
					out_y_SPS_LF			=	y_vec[i];
					out_z_SPS_LF			=	x_vec[i];
					out_offp_SPS_LF			=	offp_vec[i];
					out_offr_SPS_LF			=	offr_vec[i];
					out_date_time_SPS_LF	=	date_time_vec[i];

					out_SPS_LF_tree			-> 	Fill();
				}

			if(SPS_LR_flag==1)				
				{
					out_file_name_SPS_LR	=	file_name_vec[i];
					out_frame_SPS_LR		=	frame_vec[i];
					out_collection_SPS_LR	=	collection_vec[i];
					out_group_SPS_LR		=	group_vec[i];
					out_point_SPS_LR		=	point_vec[i];
					out_x_SPS_LR			=	x_vec[i];
					out_y_SPS_LR			=	y_vec[i];
					out_z_SPS_LR			=	x_vec[i];
					out_offp_SPS_LR			=	offp_vec[i];
					out_offr_SPS_LR			=	offr_vec[i];
					out_date_time_SPS_LR	=	date_time_vec[i];

					out_SPS_LR_tree			-> 	Fill();
				}
	
			if(STT_RV60_flag==1)				
				{
					out_file_name_STT_RV60	=	file_name_vec[i];
					out_frame_STT_RV60		=	frame_vec[i];
					out_collection_STT_RV60	=	collection_vec[i];
					out_group_STT_RV60		=	group_vec[i];
					out_point_STT_RV60		=	point_vec[i];
					out_x_STT_RV60			=	x_vec[i];
					out_y_STT_RV60			=	y_vec[i];
					out_z_STT_RV60			=	x_vec[i];
					out_offp_STT_RV60		=	offp_vec[i];
					out_offr_STT_RV60		=	offr_vec[i];
					out_date_time_STT_RV60	=	date_time_vec[i];

					out_STT_RV60_tree		-> 	Fill();
				}

			if(STT_RH60_flag==1)				
				{
					out_file_name_STT_RH60	=	file_name_vec[i];
					out_frame_STT_RH60		=	frame_vec[i];
					out_collection_STT_RH60	=	collection_vec[i];
					out_group_STT_RH60		=	group_vec[i];
					out_point_STT_RH60		=	point_vec[i];
					out_x_STT_RH60			=	x_vec[i];
					out_y_STT_RH60			=	y_vec[i];
					out_z_STT_RH60			=	x_vec[i];
					out_offp_STT_RH60		=	offp_vec[i];
					out_offr_STT_RH60		=	offr_vec[i];
					out_date_time_STT_RH60	=	date_time_vec[i];

					out_STT_RH90_tree		-> 	Fill();
				}

			if(STT_RV90_flag==1)				
				{
					out_file_name_STT_RV90	=	file_name_vec[i];
					out_frame_STT_RV90		=	frame_vec[i];
					out_collection_STT_RV90	=	collection_vec[i];
					out_group_STT_RV90		=	group_vec[i];
					out_point_STT_RV90		=	point_vec[i];
					out_x_STT_RV90			=	x_vec[i];
					out_y_STT_RV90			=	y_vec[i];
					out_z_STT_RV90			=	x_vec[i];
					out_offp_STT_RV90		=	offp_vec[i];
					out_offr_STT_RV90		=	offr_vec[i];
					out_date_time_STT_RV90	=	date_time_vec[i];

					out_STT_RV90_tree		-> 	Fill();
				}

			if(STT_RH90_flag==1)				
				{
					out_file_name_STT_RH90	=	file_name_vec[i];
					out_frame_STT_RH90		=	frame_vec[i];
					out_collection_STT_RH90	=	collection_vec[i];
					out_group_STT_RH90		=	group_vec[i];
					out_point_STT_RH90		=	point_vec[i];
					out_x_STT_RH90			=	x_vec[i];
					out_y_STT_RH90			=	y_vec[i];
					out_z_STT_RH90			=	x_vec[i];
					out_offp_STT_RH90		=	offp_vec[i];
					out_offr_STT_RH90		=	offr_vec[i];
					out_date_time_STT_RH90	=	date_time_vec[i];

					out_STT_RH90_tree		-> 	Fill();
				}

			if(SPS_RF_flag==1)				
				{
					out_file_name_SPS_RF	=	file_name_vec[i];
					out_frame_SPS_RF		=	frame_vec[i];
					out_collection_SPS_RF	=	collection_vec[i];
					out_group_SPS_RF		=	group_vec[i];
					out_point_SPS_RF		=	point_vec[i];
					out_x_SPS_RF			=	x_vec[i];
					out_y_SPS_RF			=	y_vec[i];
					out_z_SPS_RF			=	x_vec[i];
					out_offp_SPS_RF			=	offp_vec[i];
					out_offr_SPS_RF			=	offr_vec[i];
					out_date_time_SPS_RF	=	date_time_vec[i];

					out_SPS_RF_tree			-> 	Fill();
				}

			if(SPS_RR_flag==1)				
				{
					out_file_name_SPS_RR	=	file_name_vec[i];
					out_frame_SPS_RR		=	frame_vec[i];
					out_collection_SPS_RR	=	collection_vec[i];
					out_group_SPS_RR		=	group_vec[i];
					out_point_SPS_RR		=	point_vec[i];
					out_x_SPS_RR			=	x_vec[i];
					out_y_SPS_RR			=	y_vec[i];
					out_z_SPS_RR			=	x_vec[i];
					out_offp_SPS_RR			=	offp_vec[i];
					out_offr_SPS_RR			=	offr_vec[i];
					out_date_time_SPS_RR	=	date_time_vec[i];

					out_SPS_RR_tree			-> 	Fill();
				}

			if(M_STT_flag==1)				
				{
					out_file_name_M_STT	=	file_name_vec[i];
					out_frame_M_STT		=	frame_vec[i];
					out_collection_M_STT=	collection_vec[i];
					out_group_M_STT		=	group_vec[i];
					out_point_M_STT		=	point_vec[i];
					out_x_M_STT			=	x_vec[i];
					out_y_M_STT			=	y_vec[i];
					out_z_M_STT			=	x_vec[i];
					out_offp_M_STT		=	offp_vec[i];
					out_offr_M_STT		=	offr_vec[i];
					out_date_time_M_STT	=	date_time_vec[i];

					out_M_STT_tree			-> 	Fill();

				}

			if(PA6_flag==1)				
				{
					out_file_name_PA6	=	file_name_vec[i];
					out_frame_PA6		=	frame_vec[i];
					out_collection_PA6	=	collection_vec[i];
					out_group_PA6		=	group_vec[i];
					out_point_PA6		=	point_vec[i];
					out_x_PA6			=	x_vec[i];
					out_y_PA6			=	y_vec[i];
					out_z_PA6			=	x_vec[i];
					out_offp_PA6		=	offp_vec[i];
					out_offr_PA6		=	offr_vec[i];
					out_date_time_PA6	=	date_time_vec[i];

					out_PA6_tree			-> 	Fill();

				}

			if(PA7_flag==1)				
				{
					out_file_name_PA7	=	file_name_vec[i];
					out_frame_PA7		=	frame_vec[i];
					out_collection_PA7	=	collection_vec[i];
					out_group_PA7		=	group_vec[i];
					out_point_PA7		=	point_vec[i];
					out_x_PA7			=	x_vec[i];
					out_y_PA7			=	y_vec[i];
					out_z_PA7			=	x_vec[i];
					out_offp_PA7		=	offp_vec[i];
					out_offr_PA7		=	offr_vec[i];
					out_date_time_PA7	=	date_time_vec[i];

					out_PA7_tree			-> 	Fill();

				}

			if(Kreis_flag==1)				
				{
					out_file_name_Kreis	=	file_name_vec[i];
					out_frame_Kreis		=	frame_vec[i];
					out_collection_Kreis=	collection_vec[i];
					out_group_Kreis		=	group_vec[i];
					out_point_Kreis		=	point_vec[i];
					out_x_Kreis			=	x_vec[i];
					out_y_Kreis			=	y_vec[i];
					out_z_Kreis			=	x_vec[i];
					out_offp_Kreis		=	offp_vec[i];
					out_offr_Kreis		=	offr_vec[i];
					out_date_time_Kreis	=	date_time_vec[i];

					out_Kreis_tree		-> 	Fill();

				}

	

	}



//	dropping the elements which filled in the tree from the original vectors.

	int size_before=point_vec.size();


	for(int i=point_vec.size()-1;i>-1;i--)
	{
		if(detectors_flag_vec[i]==1)
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

	cout<<"size before : "<<size_before<<" ... size after : "<<size_after<<" ... size classified : "<<size_before-size_after<<endl;




//	4) END:		.............	seperating each divice's coordinates 	.......................











/*



	cout<<"START Block (4) : finding the MUSE frame."<<endl;
//	4) START:	.............	finding the MUSE frame 	.......................


	vector<TString>	final_tot_frame,final_file_name,final_point,final_time,final_frame,final_collection,final_group;
	vector<float>	final_x,final_y,final_z,final_offp,final_offr;
	vector<vector<int>>	flag_2D;
	vector<int>	flag_1D;

	TString main_frame="20220810_WEHA_PIM1_Muse_Procedure...20220119KontrolleRahmen::PIM1...20220810...AufmassRefTargetkammer";
	
	for (int i=0;i<C_tot_frame.size();i++)
	{
		for(int j=0;j<C_tot_frame[i].size();j++)
		{
			if(C_tot_frame[i][j]==main_frame)
			{
	//			cout<<i<<":"<<j<<" )"<<C_tot_frame[i][j]<<"	"<<C_point[i][j]<<"	"<<C_x[i][j]<<"	"<<C_y[i][j]<<"	"<<C_z[i][j]<<C_time[i][j]<<endl;

				final_tot_frame.push_back(C_tot_frame[i][j]);
				final_file_name.push_back(C_file_name[i][j]);
				final_point.push_back(C_point[i][j]);
				final_collection.push_back(C_collection[i][j]);
				final_group.push_back(C_group[i][j]);
				final_time.push_back(C_time[i][j]);
				final_x.push_back(C_x[i][j]);
				final_y.push_back(C_y[i][j]);
				final_z.push_back(C_z[i][j]);
				final_offp.push_back(C_offp[i][j]);
				final_offr.push_back(C_offr[i][j]);

				flag_1D.push_back(1);
			}
			if(C_tot_frame[i][j]!=main_frame){flag_1D.push_back(0);}
		}
		flag_2D.push_back(flag_1D);
		flag_1D.clear();
	}


//	4) END :	.............	finding the MUSE frame 	.......................

*/

/*


//	printing results, just to check.

	for(int i=0;i<flag_2D.size();i++)
	{cout<<i<<" ) "<<flag_2D[i].size()<<" : ";
		for(int j=0;j<flag_2D[i].size();j++)
		{
		cout<<flag_2D[i][j]<<"	";

		}
		cout<<endl;
	}

*/

	/*

	cout<<"START Block (5) : matching differnet farmes with the MAIN frame."<<endl;
//	5) START :	.............	matching differnet farmes with the MAIN frame .

	float eps=1;

	for(int R=0;R<4;R++)
	{
		for (int i=0;i<flag_2D.size();i++)
		{
			int num_points=0;
			int same_flag=0;

			for(int j=0;j<flag_2D[i].size();j++)
			{
				for (int k=0;k<final_point.size();k++)
				{
					if(flag_2D[i][j]==0	&&	C_point[i][j]==final_point[k])
					{
						num_points++;
						if (fabs(C_x[i][j]-final_x[k])<eps	&&	fabs(C_y[i][j]-final_y[k])<eps	&&	fabs(C_z[i][j]-final_z[k])<eps)
						{	same_flag++;	}
						
						else 
						{	same_flag=0;	}
					}
				}
			}
			
			if(num_points>2 && same_flag>2)
			{
				for(int s=0;s<flag_2D[i].size();s++)
				{
					flag_2D[i].erase(next(flag_2D[i].begin(),s));
					flag_2D[i].insert(flag_2D[i].begin()+s,1);

					final_tot_frame.push_back(C_tot_frame[i][s]);
					final_file_name.push_back(C_file_name[i][s]);
					final_point.push_back(C_point[i][s]);
					final_collection.push_back(C_collection[i][s]);
					final_group.push_back(C_group[i][s]);
					final_time.push_back(C_time[i][s]);
					final_x.push_back(C_x[i][s]);
					final_y.push_back(C_y[i][s]);
					final_z.push_back(C_z[i][s]);
					final_offp.push_back(C_offp[i][s]);
					final_offr.push_back(C_offr[i][s]);
				}
			}
			
			if(num_points>2 && same_flag<3)
			{
				for(int s=0;s<flag_2D[i].size();s++)
				{
					flag_2D[i].erase(next(flag_2D[i].begin(),s));
					flag_2D[i].insert(flag_2D[i].begin()+s,3);


				}
			}
		}
}	//	for(R)


//	5) END :	.............	matching differnet farmes with the MAIN frame .

*/
/*
//	printing results, just to check.
	cout<<"****************************************************************"<<endl;

		cout<<endl;
		cout<<endl;
		cout<<endl;

	for(int i=0;i<flag_2D.size();i++)
	{cout<<i<<" ) "<<flag_2D[i].size()<<" : ";
		for(int j=0;j<flag_2D[i].size();j++)	
			{	cout<<flag_2D[i][j]<<"	"; if (flag_2D[i][j]==1) cout<<" ( "<<C_point[i][j]<<"	"<<C_x[i][j]<<" )";	}
		cout<<endl;
	}
*/


/*
	cout<<"START Block (6) : transforming the coordinates."<<endl;
//	6) START :	.............	transforming the coordinates	...............

	float Ax,Ay,Az,Bx,By,Bz,Cx,Cy,Cz;
	float AAx,AAy,AAz,BBx,BBy,BBz,CCx,CCy,CCz;			//	the matching points between the 1st and the 2nd frames. (AA~A`,BB~B',CC~C')
	int k1,k2,k3;

	TString	S1="AAA";
	TString	S2="AAA";
	TString	S3="AAA";

				TVector3 vect_1st,vect_2nd,Norm_AB_vec,Norm_ABC_vec,Norm_AABBCC_vec,Norm_Norm_vec,CCC_Norm;
				TVector3 A_vec,B_vec,C_vec,AA_vec,BB_vec,CC_vec;
				TVector3 AB_vec,AC_vec,ABp_vec,ACp_vec;

				TVector3 rot_axis_1st,rot_axis_2nd,ref_vec;



				float the_1,the_3;

	vector<float> displacement, angle_1,angle_2;




	for(int i=0;i<flag_2D.size();i++)
	{
		int counter=0;
				float tmp_x,tmp_y,tmp_z,rot_angle_1st,rot_angle_2nd;

		for(int j=0;j<flag_2D[i].size();j++)
		{
			if(flag_2D[i][j]==3)
			{
				

				for(int k=0;k<final_point.size();k++)
				{
					if(C_point[i][j]==final_point[k] && counter<3 && final_point[k]!=S1 && final_point[k]!=S2 && final_point[k]!=S3 && counter<3)
						{
							counter++;
							if(counter==1){ Ax=final_x[k];
											Ay=final_y[k];
											Az=final_z[k];
											AAx=C_x[i][j];
											AAy=C_y[i][j];
											AAz=C_z[i][j];	S1=final_point[k];	k1=k;}

							if(counter==2){ Bx=final_x[k];
											By=final_y[k];
											Bz=final_z[k];
											BBx=C_x[i][j];
											BBy=C_y[i][j];
											BBz=C_z[i][j];	S2=final_point[k];	k2=k;}

							if(counter==3){	Cx=final_x[k];
											Cy=final_y[k];
											Cz=final_z[k];
											CCx=C_x[i][j];
											CCy=C_y[i][j];
											CCz=C_z[i][j];	S3=final_point[k];	k3=k;}


						}
				}	//	for(k)	over the final stored vector of points and their information.





		
			}				//	if(flag_2D[i][j]==3) if the common point are 3 or more, but not alligned with the main frame points.
		}					//	for(j)

				if(counter==3)
					{
	

					//	cout<<"--------------------------------------"<<endl;

					//	cout<<"before"<<endl;
					//	cout<<final_point[k1]<<" ] "<<Ax<<"	"<<AAx<<"		"<<Ay<<"	"<<AAy<<"		"<<Az<<"	"<<AAz<<endl;
					//	cout<<final_point[k2]<<" ] "<<Bx<<"	"<<BBx<<"		"<<By<<"	"<<BBy<<"		"<<Bz<<"	"<<BBz<<endl;
					//	cout<<final_point[k3]<<" ] "<<Cx<<"	"<<CCx<<"		"<<Cy<<"	"<<CCy<<"		"<<Cz<<"	"<<CCz<<endl;

						tmp_x=(AAx-Ax);	tmp_y=(AAy-Ay);	tmp_z=(AAz-Az);
						AAx=AAx-tmp_x;	AAy=AAy-tmp_y;	AAz=AAz-tmp_z;
						BBx=BBx-tmp_x;	BBy=BBy-tmp_y;	BBz=BBz-tmp_z;
						CCx=CCx-tmp_x;	CCy=CCy-tmp_y;	CCz=CCz-tmp_z;

					//	cout<<"after"<<endl;
					//	cout<<final_point[k1]<<" ] "<<Ax<<"	"<<AAx<<"		"<<Ay<<"	"<<AAy<<"		"<<Az<<"	"<<AAz<<endl;
					//	cout<<final_point[k2]<<" ] "<<Bx<<"	"<<BBx<<"		"<<By<<"	"<<BBy<<"		"<<Bz<<"	"<<BBz<<endl;
					//	cout<<final_point[k3]<<" ] "<<Cx<<"	"<<CCx<<"		"<<Cy<<"	"<<CCy<<"		"<<Cz<<"	"<<CCz<<endl;
					//	cout<<"--------------"<<endl;

					A_vec.SetXYZ(Ax,Ay,Az);
					B_vec.SetXYZ(Bx,By,Bz);
					C_vec.SetXYZ(Cx,Cy,Cz);
					AA_vec.SetXYZ(AAx,AAy,AAz);
					BB_vec.SetXYZ(BBx,BBy,BBz);
					CC_vec.SetXYZ(CCx,CCy,CCz);

					ref_vec=A_vec;
					AB_vec=B_vec-A_vec;
					AC_vec=C_vec-A_vec;
					ABp_vec=BB_vec-AA_vec;
					ACp_vec=CC_vec-AA_vec;

					rot_axis_1st	=	AB_vec.Cross(ABp_vec);
					rot_angle_1st	=	AB_vec.Angle(ABp_vec);

				//	cout<<"A->B vector :"<<endl;
			//		cout<<(180/PI)*AB_vec.Theta()<<"	before	"<<(180/PI)*ABp_vec.Theta()<<endl;
					ABp_vec.Rotate(-rot_angle_1st,rot_axis_1st);
			//		cout<<(180/PI)*AB_vec.Theta()<<"	after	"<<(180/PI)*ABp_vec.Theta()<<endl;

					ACp_vec.Rotate(-rot_angle_1st,rot_axis_1st);


					TVector3 BAC_Norm_vec,BACp_Norm_vec;

					BAC_Norm_vec 	=	AB_vec.Cross(AC_vec);
					BACp_Norm_vec	=	AB_vec.Cross(ACp_vec);

					rot_axis_2nd=AB_vec;
					rot_angle_2nd=BAC_Norm_vec.Angle(BACp_Norm_vec);

			//		cout<<"A->C vector :"<<endl;
			//		cout<<(180/PI)*AC_vec.Theta()<<"	before	"<<(180/PI)*ACp_vec.Theta()<<endl;
					ACp_vec.Rotate(-rot_angle_2nd,rot_axis_2nd);
			//		cout<<(180/PI)*AC_vec.Theta()<<"	after	"<<(180/PI)*ACp_vec.Theta()<<endl;	
					}


		for(int j=0;j<flag_2D[i].size();j++)
		{

			if(flag_2D[i][j]==3)
			{
			TVector3 tmp_vec,rel_vec;
			tmp_vec.SetXYZ(C_x[i][j]-tmp_x,C_y[i][j]-tmp_y,C_z[i][j]-tmp_z);
			rel_vec=tmp_vec-ref_vec;

			rel_vec.Rotate(-rot_angle_1st,rot_axis_1st);
			rel_vec.Rotate(-rot_angle_2nd,rot_axis_2nd);

					flag_2D[i].erase(next(flag_2D[i].begin(),j));
					flag_2D[i].insert(flag_2D[i].begin()+j,1);

					final_tot_frame.push_back(C_tot_frame[i][j]);
					final_file_name.push_back(C_file_name[i][j]);
					final_point.push_back(C_point[i][j]);
					final_collection.push_back(C_collection[i][j]);
					final_group.push_back(C_group[i][j]);
					final_time.push_back(C_time[i][j]);
					final_x.push_back((rel_vec+ref_vec).X());
					final_y.push_back((rel_vec+ref_vec).Y());
					final_z.push_back((rel_vec+ref_vec).Z());
					final_offp.push_back(C_offp[i][j]);
					final_offr.push_back(C_offr[i][j]);
			}


		}

	}						//	for(i)



//	6) END :	.............	transforming the coordinates	...............






*/



/*

//	printing results, just to check.
	//cout<<"****************************************************************"<<final_point.size()<<endl;

		cout<<endl;
		cout<<endl;
		cout<<endl;

	for(int i=0;i<flag_2D.size();i++)
	{//	cout<<i<<" ) "<<"the Frame combination is : "<<C_tot_frame[i][0]<<endl;
		//cout<<"	Number of points : "<<flag_2D[i].size()<<" ( "<<C_time[i][0]<<" ) : ";
		for(int j=0;j<flag_2D[i].size();j++)	
			{	
				cout<<flag_2D[i][j]<<"	"; if (flag_2D[i][j]==0) cout<<" ( "<<C_point[i][j]<<"	"<<C_x[i][j]<<" )";	}
		cout<<endl;cout<<endl;
	}


*/

/*

//	X) START :	.............	Storing the final vectors in TXT file 	.......

	out_file.open("out_file.txt");

	for(int i=0;i<final_point.size();i++)
		{
			out_file<<final_file_name[i]<<"	"<<final_frame[i]<<"	"<<final_collection[i]<<"	"<<final_group[i]<<"	"<<final_point[i]<<"	"<<final_x[i]<<"	"<<final_y[i]<<"	"<<final_z[i]<<"	"<<final_offp[i]<<"	"<<final_offr[i]<<"	"<<final_time[i]<<endl;
		}


//	X) END :	.............	Storing the final vectors in TXT file 	.......


*/



	out_file.open("out_file.txt");
	out_loc_file.open("out_loc_file.txt");


	for(int i=0;i<x_vec.size();i++)
	{
		out_file<<file_name_vec[i]<<","<<frame_vec[i]<<","<<collection_vec[i]<<","<<group_vec[i]<<","<<point_vec[i]<<","<<x_vec[i]<<","<<y_vec[i]<<","<<z_vec[i]<<" ,  "<<offp_vec[i]<<","<<offr_vec[i]<<","<<date_time_vec[i]<<endl;
	}

	for(int i=0;i<loc_x_vec.size();i++)
	{
		out_loc_file<<loc_file_name_vec[i]<<","<<loc_frame_vec[i]<<","<<loc_collection_vec[i]<<","<<loc_group_vec[i]<<","<<loc_point_vec[i]<<","<<loc_x_vec[i]<<","<<loc_y_vec[i]<<","<<loc_z_vec[i]<<" ,  "<<loc_offp_vec[i]<<","<<loc_offr_vec[i]<<","<<loc_date_time_vec[i]<<endl;
	}


	out_file.close();
	out_loc_file.close();

	out_root_file	->	Write();
	out_root_file	->	Close();


}	//	main





