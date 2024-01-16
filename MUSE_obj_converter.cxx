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

void MUSE_obj_converter(TString infile, TString collection = "", TString rotTrans = "", vector<float> vrt = {}){


//	...............................................................

	ifstream in_trees_file;
	string line;


//	define the input files... 
//	the first one is ole and its frame is the old/main PSI frame, there is no need to use it, it is not a direct MUSE survey.

	int nu_of_trees=0;
	in_trees_file.open("trees_file_9.txt");

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

//	...............................................................
	
TFile file("points_9.root");


		TString dir="OBJ_files";
		gSystem->Exec("rm -rf "+dir);

	gSystem->Exec("rm -rf "+dir);
	gSystem->Exec("mkdir "+dir);



	for(int i=0;i<trees_names.size();i++)
	









	
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
	
	if((int)vrt.size())
	{
		if((int)vrt.size() == rotTrans.Length()){
			cout << "doing a rotations/translation" << endl;
			rt = true;
		}else{
			cout << "string " << rotTrans << " needs to have the same number of characters as the size of the supplied vector: " << vrt.size() << endl;
		}
	}
			
	
	while(getline(ifst,line))
	{
		stringstream ss(line);
		string item;
		vector<string> items;
		char delim = ',';



	    while (getline (ss, item, delim)) {     items.push_back (item);     }




		TString name, collname;
	
		float pt1, pt2, pt3;
		if(lineno > 5)
		{
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
				
		}		//	if(lineno > 5)

		line.clear();
		lineno++;
		
		
	}			//	while(getline(ifst,line))
	
	ifst.close();
	ofst.close();
	
	
	
}		//	main