#include "Integer.h"

namespace cosc326 {
	

	//default constructor, sets value equal to 0
	Integer::Integer() : value("0") {}

	//copy constructor, sets this equal to i but also removes + and leading 0's
	Integer::Integer(const Integer& i) : value(i.value) {
		//removes leading plus if added (as number's don't need positive declaration)
		if(value[0] == '+'){
			value = value.substr(1);
		}

		//removes any excess zeros added to the number
		value  = removeZeros(value);
	}

	//setting constructer, sets value equal to s, removes + and leading 0's if added
	Integer::Integer(const std::string& s) : value(s){
		if(value[0] == '+'){
			value = value.substr(1);
		}
		value  = removeZeros(value);
	}

	//destructor
	Integer::~Integer() {
		//empty as no specific cleanup tasks
	}

	//method to get the value of a Integer instance
	std::string Integer::getValue() const{
		return value;
	}

	//adds 1 to the string which represents an Integer value
	std::string iterate(const std::string i){
		std::string num = i;
		if(num[num.length()-1] == '9'){
			if(num.length() == 1){
				num = "00";
			}
			else{
				num[num.length()-1] = '0';
			}
			int loop = num.length()-2;
			for (int j = loop; j >= 0; j--) {
				if (num[j] == '9') {
					num[j] = '0';
				} else {
					num[j] = (int(num[j] - '0') + 1) + '0';
					break;
				}
				if(j == 0){
					num = '1' + num;
				}
        	}
		}
		else{
			num[num.length()-1] = (int(num[num.length()-1] - '0') + 1) + '0';
		}
		return num;
	}

	//method which removes any leading 0's from a string
	std::string removeZeros(const std::string num){
		int length = num.length();
		std::string local_num = num;
		for (int i = 0; i < length; i++){
			if(num[i] == '-' && i == 0){
				continue;
			}
			else if ((num[i] - '0' == 0 || num[i] == ' ') && local_num.length() != 1){
				local_num.erase(0, 1);
			}
			else {
				break;
			}
		}
		return local_num;
	}

	//sets Integer = i
	Integer& Integer::operator=(const Integer& i) {
		value = i.value;
		return *this;
	}

	//returns negative version of Integer instance
	Integer Integer::operator-() const {
		std::string negatedValue = value;

		if (negatedValue != "0") {
			if (negatedValue[0] == '-') {
				negatedValue = negatedValue.substr(1);  // Remove the leading minus sign
			}
			else {
				negatedValue = "-" + negatedValue;  // Add a leading minus sign
			}
		}
		


		return Integer(negatedValue);
	}

	//returns positive version of Integer instance
	Integer Integer::operator+() const {
		return Integer(*this);
	}

	// Compound Methods

	//adds i to Integer
	Integer& Integer::operator+=(const Integer& i) {
		*this = *this + i;
		return *this;
	}

	//subtracts i from Integer
	Integer& Integer::operator-=(const Integer& i) {
		*this = *this - i;
		return *this;
	}

	//Multiplies Integer by i
	Integer& Integer::operator*=(const Integer& i) {
		*this = *this * i;
		return *this;
	}

	//divides Integer by i
	Integer& Integer::operator/=(const Integer& i) {
		*this = *this / i;
		return *this;
	}

	//sets Integer = remainder of it divided by i (modulo)
	Integer& Integer::operator%=(const Integer& i) {
		*this = *this % i;
		return *this;
	}

	//Binary Methods

	//adds lhs to rhs
	Integer operator+(const Integer& lhs, const Integer& rhs) {
		//declare and initialise local variables
		bool isNegative;
		std::string lhsValue = lhs.getValue();
		std::string rhsValue = rhs.getValue();

		

		//figure out how to calculate sum based on signs
		if (lhsValue[0] == '-') {
			lhsValue = lhsValue.substr(1);
			//negative, negative, sum with sign negative
			if(rhsValue[0] == '-'){
				rhsValue = rhsValue.substr(1);
				isNegative = true;
			}
			//negative, positive, subtract lhsValue from rhsValue
			else{
				Integer a(rhsValue);
				Integer b(lhsValue);
				return(a - b);
			}
		}
		else {
			//positive, negative, subtract rhsValue from lhsValue
			if (rhsValue[0] == '-') {
				rhsValue = rhsValue.substr(1);
				Integer a(lhsValue);
				Integer b(rhsValue);
				return(a - b);
			}
			//positive, positive, simply do the sum, without adding a negative sign
			else {
				isNegative = false;
			}
		}


		//declare and initialise variables for loop
		int maxLength = std::max(lhsValue.length(), rhsValue.length()) + 1;
		std::string result(maxLength+1, '0');
		int first;
		int second;
		int carry = 0;

		//loop to calculate sum
		for (int i = 0; i < maxLength; i++) {

			//adds values starting from 1's column
			first = (i < lhsValue.length()) ? (lhsValue[lhsValue.length() - 1 - i] - '0') : 0;
			second = (i < rhsValue.length()) ? (rhsValue[rhsValue.length() - 1 - i] - '0') : 0;
			first = first + second + carry;

			//sets carry if sum > 10
			if (first >= 10) {
				carry = 1;
				first = first % 10;
			}
			else {
				carry = 0;
			}
			result[result.length() - 1 - i] = first + '0';
		}
		
		//format result and return declared Integer sum with value = result
		result = removeZeros(result);
		result = (isNegative ? "-" + result : result);
		Integer sum(result);
		return sum;
	}

	//subtracts rhs from lhs
	Integer operator-(const Integer& lhs, const Integer& rhs) {
		//declare and initialise local variables
		bool isNegative = false;
		std::string lhsValue = lhs.getValue();
		std::string rhsValue = rhs.getValue();

		//figure out how to calculate difference based on sign
		if (lhsValue[0] == '-') {
			//negative, negative, means you can just subtract the first from the second
			if (rhsValue[0] == '-') {
				lhsValue = lhsValue.substr(1);
				rhsValue = rhsValue.substr(1);
				std::swap(lhsValue, rhsValue);
			}
			//negative, positive, just sum with both being negative values
			else {
				rhsValue = '-' + rhsValue;
				Integer a(lhsValue);
				Integer b(rhsValue);
				return(a+b);
			}
		}
		else {
			//positive, negative, just sum with both being positive values
			if (rhsValue[0] == '-') {
				rhsValue = rhsValue.substr(1);
				Integer a(lhsValue);
				Integer b(rhsValue);
				return(a+b);
			}
			//positive, positive, do nothing
		}

		//if lhs > rhs then you can simply swap the values and set the final result to negative
		//therefore, this if and else if checks if the lhsValue < rhsValue
		Integer r(rhsValue);
		Integer l(lhsValue);
		if (r > l) {
			std::swap(lhsValue, rhsValue);
			isNegative = true;
		}

		//declare and initialise variables for loop
		std::string result(lhsValue.length(), '0');
		int first;
		int second;
		int carry = 0;

		
			
		//loop to subtract rhs from lhs
		for (int i = 0; i < lhsValue.length(); i++) {

			//calculates difference starting at 1's column
			first = (i < lhsValue.length()) ? (lhsValue[lhsValue.length() - 1 - i] - '0') : 0;
			second = (i < rhsValue.length()) ? (rhsValue[rhsValue.length() - 1 - i] - '0') : 0;
			first = first - second - carry;

			//sets carry if difference < 0
			if (first < 0) {
				carry = 1;
				first = first + 10;
			}
			else {
				carry = 0;
			}
			result[result.length() - 1 - i] = first + '0';
		}
		
		//format result and return declared Integer sub with value = result
		result = removeZeros(result);
		result = (isNegative ? "-" + result : result);
		Integer sub(result);
		return sub;
	}

	//multiplies lhs by rhs
	Integer operator*(const Integer& lhs, const Integer& rhs) {
		//declaration and initialisation for local variables
		std::string lhsValue = lhs.getValue();
		std::string rhsValue = rhs.getValue();

		//Checks if the result will be negative
		bool isNegative = (lhsValue[0] == '-') ^ (rhsValue[0] == '-');

		//checks for and removes signs
		lhsValue = (lhsValue[0] == '-') ? lhsValue.substr(1) : lhsValue;
		rhsValue = (rhsValue[0] == '-') ? rhsValue.substr(1) : rhsValue;

		//reduces possibility of error
		lhsValue = removeZeros(lhsValue);
		rhsValue = removeZeros(rhsValue);

		//declaration and initialisation for variables in loop
		std::string result(lhsValue.length()+rhsValue.length(), '0');
		int product; //can never be above 81
		int sum; //can never be above 90

		//nested loop to multiply the two numbers
		for(int i = lhsValue.length() - 1; i >= 0; i--){
			for(int j = rhsValue.length() - 1; j >= 0; j--){
				product = (lhsValue[i] - '0') * (rhsValue[j] - '0');
				sum = product + (result[i+j+1] - '0');
				result[i+j] = ((result[i+j] - '0') + sum/10) + '0';
				result[i+j+1] = sum%10 + '0';
			}
		}
		
		//format result and return declared Integer multSum with value = result
		result = removeZeros(result);
		result = (isNegative ? "-" + result : result);
		Integer multSum(result);
		return multSum;
		
	}

	//divides lhs by rhs
	Integer operator/(const Integer& lhs, const Integer& rhs) {
		std::string lhsValue = lhs.getValue();
		std::string rhsValue = rhs.getValue();
		Integer null;
		
		// Checks if the result will be negative
		bool isNegative = (lhsValue[0] == '-') ^ (rhsValue[0] == '-');

		// Checks for and removes signs
		lhsValue = (lhsValue[0] == '-') ? lhsValue.substr(1) : lhsValue;
		rhsValue = (rhsValue[0] == '-') ? rhsValue.substr(1) : rhsValue;

		// Reduces possibility of error
		lhsValue = removeZeros(lhsValue);
		rhsValue = removeZeros(rhsValue);

		Integer numerator(lhsValue);
		Integer denominator(rhsValue);

		// Checks inputs for base cases
		// If denominator is 0, print error
		if (rhsValue[0] == '0') {
			//std::cout << "Error: Cannot divide by 0" << std::endl;
			return null;
		} else if (numerator < denominator) {
			return null;
		}

		std::string divAmmount = "1";
		for(int i = 1; i < lhsValue.length(); i++){
			divAmmount += "0";
		}

		Integer result;
		Integer dividendValue;
		Integer ten("10");
		int lhsIndex = 0;

		while (lhsIndex < lhsValue.length()) {
			Integer mult(divAmmount);
			std::string val(1, lhsValue[lhsIndex]);
			Integer num(val);
			dividendValue *= ten;
			dividendValue += num;
			lhsIndex++;

			if (dividendValue >= denominator) {
				std::string quotientDigit = "0";
				while (dividendValue >= denominator) {
					quotientDigit = iterate(quotientDigit);
					dividendValue -= denominator;
				}
				Integer add(quotientDigit);
				add *= mult;
				result += add;
			} else {
				result += null;
			}
			divAmmount.erase(divAmmount.length() - 1);
		}
		

		std::string resultVal = result.getValue();
		resultVal = (isNegative ? '-' + resultVal : resultVal);
		Integer quotient(resultVal);
		return quotient;
	}

	//returns remainder of lhs/rhs
	Integer operator%(const Integer& lhs, const Integer& rhs) {
		bool isNegative = (lhs.getValue()[0] == '-');
		std::string lhsValue = (lhs.getValue()[0] == '-' ? lhs.getValue().substr(1) : lhs.getValue());
		std::string rhsValue = (rhs.getValue()[0] == '-' ? rhs.getValue().substr(1) : rhs.getValue());
		Integer lhsRefined(lhsValue);
		Integer rhsRefined(rhsValue);
		Integer null;
		
		//reduces possibility of error
		lhsValue = removeZeros(lhsValue);
		rhsValue = removeZeros(rhsValue);

		//checks inputs for base cases
		//if denominator is 0, print error
		if(rhsValue[0] == '0'){
			//std::cout << "Error: Cannot divide by 0" << std::endl;
			return null;
		}

		Integer div(lhsRefined/rhsRefined);
		Integer mult(div*rhsRefined);
		std::string val = (isNegative ? '-' + (lhsRefined-mult).getValue() : (lhsRefined-mult).getValue());
		Integer result(val);
		return result;
	}

	//outputs value of i
	std::ostream& operator<<(std::ostream& os, const Integer& i) {
		os << i.getValue();
		return os;
	}

	//sets i = input
	std::istream& operator>>(std::istream& is, Integer& i) {
		std::string input;
		is >> input;
		i = Integer(input);
		return is;
	}

	//returns true if lhs < rhs
	bool operator<(const Integer& lhs, const Integer& rhs) {
		if(lhs == rhs){
			return false;
		}
		std::string lhsValue = lhs.getValue();
		std::string rhsValue = rhs.getValue();
		bool inverse = false;
		bool answer = false;

		//first you need to check signs
		if (lhsValue[0] == '-') {
			//if both negative, set inverse = true, return opposite at end
			if(rhsValue[0] == '-'){
				lhsValue = lhsValue.substr(1);
				rhsValue = rhsValue.substr(1);
				inverse = true;
			}
			//negative, positive, return true
			else{
				return true;
			}
		}
		else {
			//positive, negative, return false
			if (rhsValue[0] == '-') {
				return false;
			}
			//positive, positive, opperate as normal
		}

		//calculate if lhs < rhs
		if (lhsValue.length() < rhsValue.length()) {
			return true;
		}
		else if (lhsValue.length() == rhsValue.length()) {
			for (int i = 0; i < lhsValue.length(); i++) {
				if (lhsValue[i] < rhsValue[i]) {
					answer = true;
					break;
				}
				else if (lhsValue[i] > rhsValue[i]) {
					break;
				}
			}
		}
		//checks if both negative inputs
		
		return (answer ^ inverse);
	}

	//returns true if lhs > rhs
	bool operator>(const Integer& lhs, const Integer& rhs) {
		return (!((lhs < rhs) || (lhs == rhs)));
	}

	//returns true if lhs <= rhs
	bool operator<=(const Integer& lhs, const Integer& rhs) {
		return (!(lhs > rhs));
	}

	//returns true if lhs >= rhs
	bool operator>=(const Integer& lhs, const Integer& rhs) {
		return (!(lhs < rhs));
	}

	//returns true if lhs == rhs
	bool operator==(const Integer& lhs, const Integer& rhs) {
		
		return (lhs.getValue().compare(rhs.getValue()) == 0);
	}

	//returns true if lhs == rhs
	bool operator!=(const Integer& lhs, const Integer& rhs) {
		return (!(lhs == rhs));
	}


	Integer gcd(const Integer& a, const Integer& b) {
		//declares and sets values
		//gcd is never negative, so you should first set both to positive values
		std::string aValue = a.getValue();
		std::string bValue = b.getValue();
		aValue = (aValue[0] == '-' ? aValue.substr(1) : aValue);
		bValue = (bValue[0] == '-' ? bValue.substr(1) : bValue);
		
		//Define new Integers as a and b can't be modified
		Integer firstNum(aValue);
		Integer secondNum(bValue);

		//if a or b = 0, then gcd is value of non-vero int
		if (aValue == "0") return b;
		if (bValue == "0") return a;

		//else use euclids algorithm
		while (secondNum.getValue() != "0") {
			Integer remainder = firstNum % secondNum;
			firstNum = secondNum;
			secondNum = remainder;
		}

		return firstNum;
	}
}
