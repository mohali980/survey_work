int findIndex(TString s, vector<TString> v){
	//returns index of string.
	//if string doesn not exists in the vector, then returns -1;
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

void printVec(vector<TString> v){
	for(int k = 0; k < (int)v.size(); k++){
		cout << "   " << k << "  " << v[k] << endl;
	}
}

void readRoot(TString filename){
	TFile *f = new TFile(filename,"READ");
	//Read the header with the collection, group, and names vectors
	TTreeReader tr((TTree*)f->Get("H"));
	TTreeReaderValue<vector<TString>> collections(tr,"collections");
	TTreeReaderValue<vector<TString>> groups(tr,"groups");
	TTreeReaderValue<vector<TString>> names(tr,"names");
	tr.Next();
	
	//printVec(*names);
	
	TTreeReader tr2((TTree*)f->Get("T"));
	
	TTreeReaderValue<TString> collection(tr2,"collection");
	TTreeReaderValue<TString> group(tr2,"group");
	TTreeReaderValue<TString> name(tr2,"name");
	TTreeReaderValue<float> x(tr2,"x");
	TTreeReaderValue<float> y(tr2,"y");
	TTreeReaderValue<float> z(tr2,"z");
	TTreeReaderValue<float> offp(tr2,"offp");
	TTreeReaderValue<float> offr(tr2,"offr");
	TTreeReaderValue<int> collnum(tr2,"collnum");
	TTreeReaderValue<int> groupnum(tr2,"groupnum");
	TTreeReaderValue<int> namenum(tr2,"namenum");
	
	while(tr2.Next()){
		//do stuff here:
		if(name->EqualTo("PIM1_5")){
			cout << *collection << "  " << *group << "  " << *x << "  " << *y << "  " << *z << endl;
		}
	}
	
}