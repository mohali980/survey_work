void rootConverter()
	{
	int namesSize = 0;
	string line;
	
	TString filename = "ALL_data.txt";
	ifstream ifst;
	ifst.open(filename);
        
	int lineno = 1;
	//bool rt = false;
	
	string concname;
	stringstream ssfn((string)filename);
	getline(ssfn, concname, '.');
	TFile *f = new TFile((TString)concname + ".root", "RECREATE");
	TTree *T = new TTree("T","");

	set<TString> collection_set;
	set<TString>::iterator cit;
	set<TString> group_set;
	set<TString>::iterator git;
	set<TString> name_set;
	set<TString>::iterator nit;

	float out_x, out_y, out_z, out_offp, out_offr;
	TString out_frame,out_collection, out_group, out_point;


	TFile *out_file = new TFile("2022_all_data.root", "RECREATE");
	TTree *out_tree = new TTree("T","");
	
	out_tree->Branch("frame", &out_frame);
	out_tree->Branch("collection", &out_collection);
	out_tree->Branch("group", &out_group);
	out_tree->Branch("point", &out_point);
	out_tree->Branch("x", &out_x,"out_x/F");
	out_tree->Branch("y", &out_y,"out_y/F");
	out_tree->Branch("z", &out_z,"out_z/F");
	out_tree->Branch("offp", &out_offp,"out_offp/F");
	out_tree->Branch("offr", &out_offr,"out_offr/F");
	

	
	

	//I'm going to read through the file twice, so I can set a unique vector of collections, groups, and names.
	//I will save this vector with collection, group, and name indexs, so cuts on those can be more easily applied numerically
	
	
	
	while(getline(ifst,line)){
		stringstream ss(line);
		string item;
		vector<string> items;
		char delim = ',';

		while (getline (ss, item, delim)) {
			items.push_back (item);
		}
        
			out_frame = (TString)items[0];
			if(out_frame.Contains(" ")){	out_frame.ReplaceAll(" ","");	}
			
			out_collection = (TString)items[1];
			if(out_collection.Contains(" ")){	out_collection.ReplaceAll(" ","");	}
			
			out_group = (TString)items[2];
			if(out_group.Contains(" "))		{	out_group.ReplaceAll(" ","");		}
			
			out_point = (TString)items[3];
			if(out_point.Contains("product-name:"))	{	out_point.ReplaceAll("product-name:","");}
			if(out_point.Contains(" "))		{	out_point.ReplaceAll(" ","");		}

			out_x = stof(items[4]);
			out_y = stof(items[5]);
			out_z = stof(items[6]);
			out_offp = stof(items[7]);
			out_offr = stof(items[8]);


		out_tree->Fill();
		
		lineno++;
	}


	out_tree->Write();
	out_tree->Print();
	out_file->Close();
			
}