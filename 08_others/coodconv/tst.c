


void tst()
{
	



vector<int> AAA;
for (int i=0;i<11;i++){AAA.push_back(i);  }
cout<<endl;
cout<<endl;
cout<<endl;
for (int i=0;i<11;i++){ cout<<AAA[i]<<"	";}
cout<<endl;


						AAA.erase(std::next(AAA.begin(),3));  //     vect.insert(vect.begin() + 3, 4);

						AAA.insert(AAA.begin()+3,555);	
for (int i=0;i<11;i++){ cout<<AAA[i]<<"	";}
cout<<endl;

}