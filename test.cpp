#include <iostream>
#include <list>
using namespace std;

class base {
public:
	int array[100];
	base() {}
};

class derived : public base {
public:
	int b[100];
	derived() {}
};

int main() {
	cout << "new" << endl;
	list<base*> li;
	base* pt = new derived();
	li.push_back(pt);
	cout << "free" << endl;
	list<base*>::iterator it = li.begin();
	free(*it);
	free(*it);
	cout << "freed" << endl;
	return 0;
}