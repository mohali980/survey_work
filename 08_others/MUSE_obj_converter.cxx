int vcounter = 0; //this keeps track of the number of vertex points in the obj file

static TString ptColor = "red"; //collor of point
static float unitsConv = 1.0; //if a units conversion is needed, we can do it here (i.e. m to mm)
static float ptHW = 0.5*unitsConv; //this will make each plane have +/- ptHW in mm

void ptconv(vector<float> pts, int line, TString name, ofstream *st){
	//each cross will have 12 points, so out vertex tracker will need to be incremented by 12 each time
	//give some information here:
	*st << "# " << name << "  " << line << "  (" << pts[0] << ", " << pts[1] << ", " << pts[2] << ")" << endl;
	//first we loop through the points
	*st << "g " << name << endl;
	*st << "v " << pts[0] << " " << pts[1] + ptHW << " " << pts[2] + ptHW << endl;
	*st << "v " << pts[0] << " " << pts[1] + ptHW << " " << pts[2] - ptHW << endl;
	*st << "v " << pts[0] << " " << pts[1] - ptHW << " " << pts[2] - ptHW << endl;
	*st << "v " << pts[0] << " " << pts[1] - ptHW << " " << pts[2] + ptHW << endl;
	*st << "f -4 -3 -2 -1" << endl;
	
	*st << "v " << pts[0] + ptHW << " " << pts[1] << " " << pts[2] + ptHW << endl;
	*st << "v " << pts[0] + ptHW << " " << pts[1] << " " << pts[2] - ptHW << endl;
	*st << "v " << pts[0] - ptHW << " " << pts[1] << " " << pts[2] - ptHW << endl;
	*st << "v " << pts[0] - ptHW << " " << pts[1] << " " << pts[2] + ptHW << endl;
	*st << "f -4 -3 -2 -1" << endl;
	
	*st << "v " << pts[0] + ptHW << " " << pts[1] + ptHW << " " << pts[2] << endl;
	*st << "v " << pts[0] + ptHW << " " << pts[1] - ptHW << " " << pts[2] << endl;
	*st << "v " << pts[0] - ptHW << " " << pts[1] - ptHW << " " << pts[2] << endl;
	*st << "v " << pts[0] - ptHW << " " << pts[1] + ptHW << " " << pts[2] << endl;
	*st << "f -4 -3 -2 -1" << endl;
	*st << endl;
}

void MUSE_obj_converter()
{
	




TString file_name;






int num_files=56+1;

	for(int f=2;f<num_files;f++)
	{

//	define the input files... 
//	the first one is ole and its frame is the old/main PSI frame, there is no need to use it, it is not a direct MUSE survey.

		if(f==1		){file_name="201200120_PIM1_Distanzberechnungen";	frame="Messung::WORLD";}
		if(f==2		){file_name="20180420_WEHA_MUSE_Kont_Target_calc";	frame="Standpunkt 1::WORLD";}
		if(f==3		){file_name="20180523_WEHA_PIM1_Muse_Messungen_doku";	frame="Standpunkt 1::Strahl";}
		if(f==4		){file_name="20181028_WEHA_PIM1_Muse_calc";	frame="20181128 Kontrollen im Areal::Drehzentrum-Strahl (MUSE)";}
		if(f==5		){file_name="201901028_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1_calc2458544";	frame="20191028::MUSE 2";}
		if(f==6		){file_name="201901028_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1_GV_Panel9";	frame="20191028::MUSE";}
		if(f==7		){file_name="201901028_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1";	frame="20191028::MUSE";}
		if(f==8		){file_name="201901029_WEHA_PIM1_Muse_Grund_STT_Testareal";	frame="Station1::WORLD";}
		if(f==9		){file_name="20190510_WEHA_PIM1_Muse_Kont_Target_Insert_2";	frame="Standpunkt 1::WORLD";}
		if(f==10	){file_name="20190517_WEHA_PIM1_Muse_Aufmass_GEM_calc4";	frame="GEM 20180312::GV GEM";}
		if(f==11	){file_name="20190524_WEHA_PIM1_Muse_Grund_Target_calc";	frame="Standpunkt 1::New Frame";}
		if(f==12	){file_name="20190719_WEHA_PIM1_Muse_Kontrollen_Areal_calc2";	frame="Standpunkt 1::WORLD";}
		if(f==13	){file_name="20190719_WEHA_PIM1_Muse_Kontrollen_Areal_calc3";	frame="Standpunkt 1::WORLD";}
		if(f==14	){file_name="20190719_WEHA_PIM1_Muse_Kontrollen_Areal_calc4";	frame="Standpunkt 1::WORLD";}
		if(f==15	){file_name="20200108_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1_calc";	frame="Station1::PIM1";}
		if(f==16	){file_name="20200108_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1";	frame="Station1::PIM1";}
		if(f==17	){file_name="20200116_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_1_frameMUSE";	frame="Station1::PIM1";}
		if(f==18	){file_name="20200116_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_1";	frame="Targetkorrektur::New Frame";}
		if(f==19	){file_name="20200116_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_frameMUSE";	frame="Station1::PIM1";}
		if(f==20	){file_name="20200116_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target";	frame="Targetkorrektur 2::Kammer Lokal Mittig";}
		if(f==21	){file_name="20200218_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_calc20200813_frameMUSE";	frame="Station1::PIM1";}
		if(f==22	){file_name="20200218_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_calc20200813";	frame="Grundvermessung Vakuumkammer::Kammer LOKAL";}
		if(f==23	){file_name="20200218_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target_frameMUSE";	frame="Station1::PIM1";}
		if(f==24	){file_name="20200218_WEHA_PIM1_Muse_Kontrollen_AussenAreal_Target";	frame="20200218 Kontrolle Target Ausgebaut::Kammer Lokal Mittig";}
		if(f==25	){file_name="20200317_PIM1_Position_Panel1-13_Berechnungen";	frame="Panelposition im Areal PIM1::MUSE";}
		if(f==26	){file_name="20201209_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1_calc";frame="surf::bottom-surface";}	
		if(f==27	){file_name="20201209_WEHA_PIM1_Muse_Kontrollen_Areal_PIM1";	frame="20201209 Aufmasse::PIM1";}
		if(f==28	){file_name="20210430_WEHA_PIM1_Muse_Target";	frame="20210430::PIM1";}
		if(f==29	){file_name="20210601_WEHA_PIM1_Muse_Target_calc_frameMUSE";	frame="20210601- Aufmasse MUSE::PIM1";}
		if(f==30	){file_name="20210601_WEHA_PIM1_Muse_Target_calc";	frame="20210601- Aufmasse COPY::bottom-surface";}
		if(f==31	){file_name="20210601_WEHA_PIM1_Muse_Target_frameMUSE";	frame="20210601- Aufmasse MUSE::PIM1";}
		if(f==32	){file_name="20210601_WEHA_PIM1_Muse_Target";	frame="20210601- Aufmasse COPY::bottom-surface";}
		if(f==33	){file_name="20210928_WEHA_PIM1_Muse_Target";	frame="20210928 Justierung Vakuumkammer und Target::PIM1";}
		if(f==34	){file_name="20220118_WEHA_PIM1_Muse_STT-and-BMbars_only";	frame="20220119 Kontrolle Rahmen::PIM1";}
		if(f==35	){file_name="20220118_WEHA_PIM1_Muse";	frame="20220119 Kontrolle Rahmen::PIM1";}
		if(f==36	){file_name="20220223_WEHA_PIM1_Muse_calc2";	frame="20220119 Kontrolle Rahmen::PIM1";}
		if(f==37	){file_name="20220223_WEHA_PIM1_Muse";	frame="20220119 Kontrolle Rahmen::PIM1";}
		if(f==38	){file_name="20220517_WEHA_PIM1_Muse_calc_relabeled_target-movement-only";	frame="Soll+NK::PIM1";}
		if(f==39	){file_name="20220517_WEHA_PIM1_Muse_calc_relabeled_target-only";	frame="Soll+NK::PIM1";}
		if(f==40	){file_name="20220517_WEHA_PIM1_Muse_calc";	frame="Soll+NK::PIM1";}
		if(f==41	){file_name="20220810_WEHA_PIM1_Muse_Procedure";	time_index=15;	frame="20220119 Kontrolle Rahmen::PIM1";}		//	the time stored in different columns for the next files.
		if(f==42	){file_name="20220830_WEHA_PIM1_Muse_Grundverm_transf";	time_index=23;	frame="20220830::EC-local";}
		if(f==43	){file_name="20220831_WEHA_PIM1_Muse_Grundverm";	time_index=23;	frame="20220831::Koordinatensystem Instr20220831_1";}
		if(f==44	){file_name="20220906_WEHA_PIM1_Muse_Grundverm";	time_index=23;	frame="202209006_Wdh_mit_Gasdruck::Koordinatensystem Instr2";}
		if(f==45	){file_name="20220907_WEHA_PIM1_Muse_Grundverm";	time_index=23;	frame="202209006_Wdh_mit_Gasdruck::Koordinatensystem Instr2";}
		if(f==46	){file_name="20220913_WEHA_PIM1_Muse_Grundverm_red_ohne_Modell";	time_index=23;	frame="202209006_Wdh_mit_Gasdruck::Koordinatensystem Instr2";}
		if(f==47	){file_name="20220914_WEHA_PIM1_Muse_Grundverm_Sensor_VETO_annotated";	time_index=23;	frame="Station1::WORLD";}
		if(f==48	){file_name="20220914_WEHA_PIM1_Muse_Grundverm_Sensor_VETO";	time_index=23;	frame="Station1::WORLD";}
		if(f==49	){file_name="20230117_WEHA_PiM1_Muse_Gestell";	time_index=23;	frame="20230117::MUSE";}
		if(f==50	){file_name="20230118_WEHA_PiM1_Muse_Gestell";	time_index=23;	frame="20230118::MUSE";}
		if(f==51	){file_name="20230119_WEHA_PiM1_Muse_Gestell";	time_index=23;	frame="2023019::MUSE";}
		if(f==52	){file_name="20230120_WEHA_PiM1_Muse_Gestell_PiM1";	time_index=23;	frame="20230120 calc::MUSE";}
		if(f==53	){file_name="20230612_WEHA_PiM1_Muse_Grund_TCPV";	time_index=23;	frame="20200218_GVM_Targetkammer.Stp::WORLD";}
		if(f==54	){file_name="20230613_WEHA_PiM1_Muse_Kont_Targetpositionen";	time_index=23;	frame="20230613::MUSE";}
		if(f==55	){file_name="20230614_WEHA_PiM1_Muse_Kont_STT";	time_index=23;	frame="Standpunkt 1::WORLD1";}
		if(f==56	){file_name="20230914_WEHA_PiM1_Muse_Kont_STT";	time_index=23;	frame="20230914::WORLD*";}


TString infile=file_name;




//	TString infile="out_file.txt";
	
	string concname;
	stringstream ssfn((string)infile);
	getline(ssfn, concname, '.');
	
	TString cname = (TString)concname;
	//cout << cname << endl;
	TString coll2 = collection;
	coll2.ReplaceAll(" ","_");
	
	TString ofstName =  cname+ "_" + coll2 + ".obj";
	ofstream ofst;
	ofst.open(ofstName);
	
	ifstream ifst;
	ifst.open(infile);
	set<string> names;
	int namesSize = 0;
	string line;
	
	int lineno = 1;
	bool rt = false;
	
	if((int)vrt.size()){
		if((int)vrt.size() == rotTrans.Length()){
			cout << "doing a rotations/translation" << endl;
			rt = true;
		}else{
			cout << "string " << rotTrans << " needs to have the same number of characters as the size of the supplied vector: " << vrt.size() << endl;
		}
	}
			
	
	while(getline(ifst,line)){
		stringstream ss(line);
		string item;
		vector<string> items;
		char delim = ',';

	    while (getline (ss, item, delim)) {
	        items.push_back (item);
	    }
		TString name, collname;
	
		float pt1, pt2, pt3;
		if(lineno > 5){
			collname = (TString)items[0];
			name = (TString)items[2];
			namesSize = (int)names.size();
			names.insert((string)name);
			//cout << items[3] << endl;
			pt1 = unitsConv*stof(items[3]);
			pt2 = unitsConv*stof(items[4]);
			pt3 = unitsConv*stof(items[5]);
			
			if(rt){
				TVector3 v(pt1, pt2, pt3);
				TVector3 varb;
				for(int i = 0; i < (int)vrt.size(); i++){
					if(rotTrans[i] == 'x'){
						v[0] += vrt[i];
					}
					if(rotTrans[i] == 'y'){
						v[1] += vrt[i];
					}
					if(rotTrans[i] == 'z'){
						v[2] += vrt[i];
					}
					if(rotTrans[i] == 'X'){
						v.RotateX(vrt[i]);
					}
					if(rotTrans[i] == 'Y'){
						v.RotateY(vrt[i]);
					}
					if(rotTrans[i] == 'Z'){
						v.RotateZ(vrt[i]);
					}
					if(rotTrans[i] == 'A'){
						varb.SetX(vrt[i]);
					}
					if(rotTrans[i] == 'R'){
						varb.SetY(vrt[i]);
					}
					if(rotTrans[i] == 'B'){
						varb.SetZ(vrt[i]);
						varb = varb.Unit();
					}
					if(rotTrans[i] == 'T'){
						v.Rotate(vrt[i],varb);
					}
					
				}
				pt1 = v[0];
				pt2 = v[1];
				pt3 = v[2];
			}
			
			vector<float> pts = {pt1, pt2, pt3};
			//cout << collname << "  " << collection << endl;
			//if((int)names.size() > namesSize && (int)items.size() > 11 && collection.EqualTo(collname)){
			if((int)items.size() > 11 && (collection.EqualTo(collname) || collection.EqualTo(""))){
				ptconv(pts, lineno, name, &ofst);
			}
				
		}
		line.clear();
		lineno++;
		}
		
	}
	ifst.close();
	ofst.close();
	
	
	
}