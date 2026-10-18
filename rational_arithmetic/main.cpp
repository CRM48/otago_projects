/*
	Test main for Rational and Integer
*/

#include <iostream>
using namespace std;

#include "Integer.h"
#include "Rational.h"

using namespace cosc326;

int main() {
	std::cout << "Kia ora World" << std::endl;

	Integer a("-5");
	Integer b("-1456");
	Integer e("16");
	Integer c("2");
	Integer d("10");
	
	Rational test(a, b, c);
	Rational test1(e, c, d);
	std::cout<<test<<std::endl;
	std::cout<<test1<<std::endl;
	test*=test1;
	std::cout<<(test)<<std::endl;

	return 0;
}
