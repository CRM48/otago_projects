#include "Rational.h"
#include <sstream>

namespace cosc326 {

	//default constructor
	Rational::Rational() : whole("0"), num("0"), den("0") {}

	//set rational based on string put
	Rational::Rational(const std::string& str) {
		std::string denString = (str.find('/') != std::string::npos ? str.substr(str.find('/') + 1) : "0");
		std::string wholeString;
		std::string numString;
		if(denString == "0"){
			wholeString = str;
			numString = "0";
		}
		else{
			wholeString = (str.find('.') != std::string::npos ? str.substr(0, str.find('.')) : "0");
			numString = (str.find('.') != std::string::npos ? str.substr(str.find('.') + 1, str.find('/') - str.find('.') - 1) : str.substr(0, str.find('/')));
		}
		Integer w(wholeString);
		Integer n (numString);
		Integer d(denString);
		whole = w;
		num = n;
		den = d;
		*this = format();
	}

	//copy constructor
	Rational::Rational(const Rational& r) : whole(r.whole), num(r.num), den(r.den) {
		*this = format();
	}

	//set rational = a
	Rational::Rational(const Integer& a) : whole(a), num("0"), den("0") {
		*this = format();
	}

	//set rational = a/b
	Rational::Rational(const Integer& a, const Integer& b) : whole("0"), num(a), den(b) {
		*this = format();
	}

	//set rational = a.b/c
	Rational::Rational(const Integer& a, const Integer& b, const Integer& c) : whole(a), num(b), den(c) {
		*this = format();
	}

	//destructor
	Rational::~Rational() {

	}

	//method to get the whole part of the rational
	Integer Rational::getWhole() const{
		return whole;
	}

	//method to get the numerator of the rational
	Integer Rational::getNum() const{
		return num;
	}

	//method to get the denominator of the rational
	Integer Rational::getDen() const{
		return den;
	}

	/*
	 * format
	 *
	 * This method formats the rational so that the only negative part
	 * is the whole number, therefore, the num/den is always positive.
	 * Because of this -17.5/6 actually represents -16.2 as what it is
	 * really saying is -17 + 5/6 which is -16.2
	 * This method also simplfies the denominator and numerator
	 * 
	*/
	Rational& Rational::format(){
		std::string wholeString = whole.getValue();
		std::string numString = num.getValue();
		std::string denString = den.getValue();
		if(numString == "0" || denString == "0"){
			whole = Integer(wholeString);
			num = Integer("0");
			den = Integer("0");
			return *this;
		}
		//if denominator is negative, set to positive and swap signs of numerator
		if(denString[0] == '-'){
			denString = denString.substr(1);
			numString = (numString[0] == '-' ? numString.substr(1) : '-' + numString);
		}
		Integer w(wholeString);
		Integer n(numString);
		Integer d(denString);
		Integer null;
		whole = w;
		num = n;
		den = d;
		*this = fromImproper();
		return *this;
	}

	//converts to improper fraction with whole = 0
	Rational& Rational::toImproper(){
		Integer w;
		Integer n(num + whole*den);
		Integer d(den);
		Integer one("1");
		if(den.getValue() == "0" || num.getValue() == "0"){
			n = whole;
			d = one;
		}
		whole = w;
		num = n;
		den = d;
		return *this;
	}

	//converts to proper fraction with num < den
	Rational& Rational::fromImproper(){
		Integer w(whole + num/den);
		Integer n(num%den);
		Integer d(den);
		whole = w;
		num = n;
		den = d;
		*this = simplify();
		return *this;
	}

	//simplifies the fraction part of the rational
	Rational& Rational::simplify(){
		Integer w(whole);
		Integer n(num/gcd(num,den));
		Integer d(den/gcd(num,den));
		whole = w;
		num = n;
		den = d;
		return *this;
	}

	//sets the rational equal to r
	Rational& Rational::operator=(const Rational& r) {
		whole = r.whole;
		num = r.num;
		den = r.den;
		return *this;
	}

	//returns the negative version of the rational
	//remember, we represent -16.5 as -17 1/2
	Rational Rational::operator-() const {
		std::string wValue = whole.getValue();
		wValue = (wValue[0] == '-' ? wValue.substr(1) : '-' + wValue);
		Integer n(num);
		Integer d(den);
		Integer w(wValue);
		Integer one("1");
		if(d.getValue() != n.getValue()){
			w -= one;
			n = d-n;
		}
		return Rational(w, n, d);
	}

	//returns the positive version of the rational
	Rational Rational::operator+() const {
		return Rational(*this);
	}

	//adds r to the rational
	Rational& Rational::operator+=(const Rational& r) {
		*this = *this + r;
		return *this;
	}

	//subtractss r from the rational
	Rational& Rational::operator-=(const Rational& r) {
		*this = *this - r;
		return *this;
	}

	//multiply's the rational by r
	Rational& Rational::operator*=(const Rational& r) {
		*this = *this * r;
		return *this;
	}

	//divides's the rational by r
	Rational& Rational::operator/=(const Rational& r) {
		*this = *this / r;
		return *this;
	}

	//adds lhs to rhs and returns result
	Rational operator+(const Rational& lhs, const Rational& rhs) {
		
		bool isNegative;
		Rational left;
		Rational right;
		if(lhs.getWhole().getValue()[0] == '-'){
			left = -lhs;
			if(rhs.getWhole().getValue()[0] == '-'){
				right = -rhs;
				isNegative = true;
			}
			else{
				right = rhs;
				return(right-left);
			}
		}
		else{
			left = lhs;
			if(rhs.getWhole().getValue()[0] == '-'){
				right = -rhs;
				return(left-right);
			}
			else{
				right = rhs;
				isNegative = false;
			}
		}
		
		/*
		 * adds rationals by turning to improper fractions and adding fractions
		 * together by multiplying both sides by the opposites denominators and
		 * adding
		 */
		left = left.toImproper();
		right = right.toImproper();
		Integer n = left.getNum() * right.getDen() + left.getDen() * right.getNum();
		Integer d = left.getDen() * right.getDen();

		//converts back to proper fraction and sets to negative if required
		Rational result(n, d);
		result = result.fromImproper();
		result = (isNegative ? -result : result);
		return result;
	}

	//subtracts rhs from lhs and returns result
	Rational operator-(const Rational& lhs, const Rational& rhs) {
		bool isNegative = false;
		Rational left(lhs);
		Rational right(rhs);
		
		if(lhs.getWhole().getValue()[0] == '-'){
			
			if(rhs.getWhole().getValue()[0] == '-'){
				
				left = -lhs;
				right = -rhs;
				std::swap(left, right);
			}
			else{
				right = -rhs;
				return(left+right);
			}
		}
		else{
			if(rhs.getWhole().getValue()[0] == '-'){
				right = -rhs;
				return(left+right);
			}
		}

		if(right > left){
			std::swap(left, right);
			isNegative = true;
		}

		/*
		 * subtracts rationals by turning to improper fractions and subtracts fractions
		 * together by multiplying both sides by the opposites denominators and
		 * subtracting
		 */
		left = left.toImproper();
		right = right.toImproper();
		Integer n = left.getNum() * right.getDen() - left.getDen() * right.getNum();
		Integer d = left.getDen() * right.getDen();
		
		//converts back to proper fraction and sets to negative if required
		Rational result(n, d);
		result = result.fromImproper();
		result = (isNegative ? -result : result);
		return result;
	}

	//multiplies lhs with rhs and returns result
	Rational operator*(const Rational& lhs, const Rational& rhs) {
		//declarations and initialisations of local variables
		bool isNegative = (lhs.getWhole().getValue()[0] == '-') ^ (rhs.getWhole().getValue()[0] == '-');
		Rational left = (lhs.getWhole().getValue()[0] == '-' ? -lhs : lhs);
		Rational right = (rhs.getWhole().getValue()[0] == '-' ? -rhs : rhs);

		//calculate multiplied fraction in improper form
		//simply multiply num1*num2 and den1*den2
		left = left.toImproper();
		right = right.toImproper();
		Integer n = left.getNum() * right.getNum();
		Integer d = left.getDen() * right.getDen();

		//convert back to normal form and turn negative if required
		Rational result(n, d);
		result = result.fromImproper();
		result = (isNegative ? -result : result);
		return result;
	}

	//divides lhs by rhs and returns result
	Rational operator/(const Rational& lhs, const Rational& rhs) {
		//declarations and initialisations of local variables
		bool isNegative = (lhs.getWhole().getValue()[0] == '-') ^ (rhs.getWhole().getValue()[0] == '-');
		Rational left = (lhs.getWhole().getValue()[0] == '-' ? -lhs : lhs);
		Rational right = (rhs.getWhole().getValue()[0] == '-' ? -rhs : rhs);

		//calculate divided fraction in improper form
		//simply multiply num1*den2 and num2*den1
		left = left.toImproper();
		right = right.toImproper();
		Integer n = left.getNum() * right.getDen();
		Integer d = left.getDen() * right.getNum();

		//convert back to normal form and turn negative if required
		Rational result(n, d);
		result = result.fromImproper();
		result = (isNegative ? -result : result);
		return result;
	}

	//prints rational i to output in specified way
	std::ostream& operator<<(std::ostream& os, const Rational& i) {
		if(i.getNum().getValue() == "0" || i.getDen().getValue() == "0"){
			os << i.getWhole();
		}
		else if(i.getWhole().getValue() == "0"){
			os << i.getNum() << "/" << i.getDen();
		}
		else{
			os << i.getWhole() << " " << i.getNum() << "/" << i.getDen();
		}
		return os;
	}

	//sets rational i equal to user input
	std::istream& operator>>(std::istream& is, Rational& i) {
		std::string input;
		is >> input;
		i = Rational(input);
		return is;
	}

	//returns true if lhs < rhs
	bool operator<(const Rational& lhs, const Rational& rhs) {
		bool inverse = false;
		if(lhs.getWhole().getValue()[0] == '-'){
			if(rhs.getWhole().getValue()[0] == '-'){
				inverse = true;
			}
			else{
				return true;
			}
		}
		else{
			if(rhs.getWhole().getValue()[0] == '-'){
				return false;
			}
		}
		Rational left(lhs);
		Rational right(rhs);
		left = left.fromImproper();
		right = right.fromImproper();
		if(left.getWhole() < right.getWhole()){
			return (true ^ inverse);
		}
		else if(left.getWhole() > right.getWhole()){
			return (false ^ inverse);
		}
		else{
			Integer numLeft = left.getNum() * right.getDen();
			Integer numRight = right.getNum() * left.getDen();
			if(numLeft < numRight){
				return (true ^ inverse);
			}
			else if(numLeft == numRight){
				return false;
			}
		}
		return (false ^ inverse);
	}

	//returns true if lhs > rhs
	bool operator>(const Rational& lhs, const Rational& rhs) {
		return !((lhs < rhs) || (lhs == rhs));
	}

	//returns true if lhs <= rhs
	bool operator<=(const Rational& lhs, const Rational& rhs) {
		return ((lhs < rhs) || (lhs == rhs));
	}

	//returns true if lhs >= rhs
	bool operator>=(const Rational& lhs, const Rational& rhs) {
		return ((lhs > rhs) || (lhs == rhs));
	}

	//returns true if lhs == rhs
	bool operator==(const Rational& lhs, const Rational& rhs) {
		Rational left(lhs);
		Rational right(rhs);
		left = left.toImproper().simplify();
		right = right.toImproper().simplify();
		if(left.getNum().getValue().compare(right.getNum().getValue()) == 0 &&
		left.getDen().getValue().compare(right.getDen().getValue()) == 0){
			return true;
		}
		return false;
	}

	//returns true if lhs != rhs
	bool operator!=(const Rational& lhs, const Rational& rhs) {
		return (!(lhs == rhs));
	}

}
