#include <iostream>
#include <sstream>
#include <string>
#include "Integer.h"
#include "Rational.h"

using namespace cosc326;

int passed = 0;
int failed = 0;

template <typename T>
void check(const std::string& name, const T& actual, const std::string& expected) {
    std::ostringstream out;
    out << actual;
    if (out.str() == expected) {
        std::cout << "PASS: " << name << '\n';
        ++passed;
    } else {
        std::cout << "FAIL: " << name << " (expected " << expected
                  << ", got " << out.str() << ")\n";
        ++failed;
    }
}

void checkBool(const std::string& name, bool condition) {
    if (condition) {
        std::cout << "PASS: " << name << '\n';
        ++passed;
    } else {
        std::cout << "FAIL: " << name << '\n';
        ++failed;
    }
}

int main() {
    std::cout << "Integer tests\n";
    check("addition", Integer("12") + Integer("8"), "20");
    check("subtraction", Integer("12") - Integer("20"), "-8");
    check("multiplication", Integer("-7") * Integer("6"), "-42");
    check("division", Integer("17") / Integer("5"), "3");
    check("modulo", Integer("17") % Integer("5"), "2");
    check("zero", Integer("0") + Integer("5"), "5");
    check("large number", Integer("99999999999999999999") + Integer("1"), "100000000000000000000");
    checkBool("integer equality", Integer("42") == Integer("42"));
    checkBool("integer less than", Integer("-2") < Integer("3"));
    checkBool("integer greater than", Integer("10") > Integer("3"));

    std::cout << "\nRational tests\n";
    const Rational half(Integer("1"), Integer("2"));
    const Rational third(Integer("1"), Integer("3"));
    const Rational quarter(Integer("1"), Integer("4"));
    check("fraction simplification", Rational(Integer("2"), Integer("4")), "1/2");
    check("addition", half + third, "5/6");
    check("subtraction", half - quarter, "1/4");
    check("multiplication", half * third, "1/6");
    check("division", half / quarter, "2");
    check("mixed number", Rational(Integer("2"), Integer("1"), Integer("2")), "2 1/2");
    checkBool("rational equality", half == Rational(Integer("2"), Integer("4")));
    checkBool("rational comparison", third < half);

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}
