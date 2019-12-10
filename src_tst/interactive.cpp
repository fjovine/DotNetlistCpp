#include <iostream>
#include <map>
#include <vector>

using namespace std;
map<int, vector<int>> blob;

int main()
{
	for (int i=1; i<10; i++)
	{		
		blob[i] = vector<int>();
		for (int j=0; j<i; j++) {
			blob[i].push_back(j);
		}
	}
	
	for (auto m : blob) {
		cout << m.first;
		auto v = m.second;
		for (auto i : v) {
			cout << " " << i;
		}
		cout << endl;
	}
}