#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> v(10);
	int i;
	cout << "Size = " << v.size() << endl;
	cout <<"\n\n";
	for (i=0; i < 10; i++) v[i] = i;
	cout << "Current contents:\n";
	for (i=0; i < v.size(); i++) cout << v[i] << " ";
	cout << "\n\n";
	cout << "Expanding vector\n";
	cout << "\n\n";
	for (i=0; i < 5; ++i) v.push_back(i + 10);
	cout << "Size now = " << v.size() << endl;
	cout << "\n";
	cout << "Current contents:\n";
	for (i=0; i < v.size(); i++) cout << v[i] << " ";
	cout << "\n\n";
	for (i=0; i < v.size(); ++i) v[i] = -v[i];
	cout << "Modified contents:\n";
	for (i=0; i < v.size(); i++) cout << v[i] << " ";
	cout << "\n\n";
	return 0;
}


