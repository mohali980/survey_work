void rootConverter()
	{

	string line;
	
	TString filename = "ALL_data.txt";
	ifstream ifst;
	ifst.open(filename);
        
	int lineno = 1;


	string concname;
	stringstream ssfn((string)filename);
	getline(ssfn, concname, '.');



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
		vector<TString> items;
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

			TString temp_x = items[4];
			TString temp_y = items[5];
			TString temp_z = items[6];
			TString temp_offp = items[7];
			TString temp_offr = items[8];

	
			out_x = float(temp_x);
			out_y = float(temp_y);
			out_z = float(temp_z);
			out_offp = float(temp_offp);
			out_offr = float(temp_offr);

			/*
			out_x = atof(temp_x.c_str());
			out_y = atof(temp_y.c_str());
			out_z = atof(temp_z.c_str());
			out_offp = atof(temp_offp.c_str());
			out_offr = atof(temp_offr.c_str());
*/

		out_tree->Fill();
		
		lineno++;
	}


	out_tree->Write();
	out_tree->Print();
	out_file->Close();
			
}