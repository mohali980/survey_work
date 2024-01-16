#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> vec = {3, 1, 2, 1, 2, 1, 5, 6, 12, 5};  
    cout<<"The vector before calling replace(): ";
    for(int x: vec)
        cout << x << " ";
    
    cout << endl;
    replace(vec.begin(), vec.end(), vec[2], 100);


    cout<<"The vector after calling replace(): ";
    for(int x: vec)
        cout << x << " ";
}
