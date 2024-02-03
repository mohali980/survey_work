int checkVec(TString s, vector<TString> v){
	int i = 0;
	if((int)v.size()){
		for(int k = 0; k < (int)v.size(); k++){
			if(s.EqualTo(v[k])){
				break;
			}else i++;
		}
		if(i == (int)v.size()){
			return -1;
		}
		return i;
	}
	return -1;
}

void rootConverter(TString filename){
	int namesSize = 0;
	string line;
	
	ifstream ifst;
	ifst.open(filename);
        
	int lineno = 1;
	//bool rt = false;
	
	string concname;
	stringstream ssfn((string)filename);
	getline(ssfn, concname, '.');
	TFile *f = new TFile((TString)concname + ".root", "RECREATE");
	TTree *T = new TTree("T","");
	float x, y, z, offp, offr;
	TString collection, group, name;
	int collnum;
	int groupnum;
	int namenum;
	set<TString> collection_set;
	set<TString>::iterator cit;
	set<TString> group_set;
	set<TString>::iterator git;
	set<TString> name_set;
	set<TString>::iterator nit;
	vector<TString> collections;
	vector<TString> groups;
	vector<TString> names;
	
	T->Branch("collection", &collection);
	T->Branch("group", &group);
	T->Branch("name", &name);
	T->Branch("x", &x, "x/F");
	T->Branch("y", &y, "y/F");
	T->Branch("z", &z, "z/F");
	T->Branch("offp", &offp, "offp/F");
	T->Branch("offr", &offr, "offr/F");
	
	T->Branch("collnum", &collnum, "collnum/I");
	T->Branch("groupnum", &groupnum, "groupnum/I");
	T->Branch("namenum", &namenum, "namenum/I");
	
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
        
		
		if(lineno > 5){
			collection = (TString)items[0];
			if(collection.Contains(" ")){
				collection.ReplaceAll(" ","");
			}
			int ccv = checkVec(collection, collections);
			
			if(ccv == -1){
				collections.push_back(collection);
				collnum = (int)collections.size() - 1;
			}else{
				collnum = ccv;
			}
			//cout << collection << "  " << collnum << endl;
			
			
			group = (TString)items[1];
			if(group.Contains(" ")){
				group.ReplaceAll(" ","");
			}
			int gcv = checkVec(group, groups);
			if(gcv == -1){
				groups.push_back(group);
				groupnum = (int)groups.size() -1;
			}else{
				groupnum = gcv;
			}
			
			
			name = (TString)items[2];
			if(name.Contains("product-name:")){
				name.ReplaceAll("product-name:","");
			}
			if(name.Contains(" ")){
				name.ReplaceAll(" ","");
			}
			int ncv = checkVec(name, names);
			
			if(ncv == -1){
				names.push_back(name);
				namenum = (int)names.size() -1;
			}else{
				namenum = ncv;
			}
			
			x = stof(items[3]);
			y = stof(items[4]);
			z = stof(items[5]);
			offp = stof(items[6]);
			offr = stof(items[7]);
			T->Fill();
		}
		lineno++;
	}
	T->Write();
	
	TTree *H = new TTree("H","");
	H->Branch("collections", &collections);
	H->Branch("groups", &groups);
	H->Branch("names", &names);
	
	/*
	for(cit=collection_set.begin(); cit!=collection_set.end(); ++cit){
		collections.push_back(*cit);
	}
	
	for(git=group_set.begin(); git!=group_set.end(); ++git){
		groups.push_back(*git);
	}
	
	for(nit=name_set.begin(); nit!=name_set.end(); ++nit){
		names.push_back(*nit);
	}
	*/
	H->Fill();
	H->Write();
	
	f->Close();
			
}