#include "coctx.h"
#include <iostream>

using namespace std;

int main(){
	ucontext temp;
	int t = coctx_init(&temp);
	cout << sizeof(temp) << endl;
	return 0;

}
