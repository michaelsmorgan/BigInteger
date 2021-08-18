#ifndef _BIGINTEGER_HPP_
#define _BIGINTEGER_HPP_

#include <cstdint>
#include <iostream>
#include <string>

class TestCases;

class BigInteger
{
public:

	friend class TestCases; // TODO Have students do this first thing

	BigInteger();
	BigInteger(std::string number);
	BigInteger(int number);
	BigInteger(const BigInteger& obj);
	~BigInteger();
	BigInteger& operator=(const BigInteger& rhs);
	friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs);
	friend BigInteger operator+(const BigInteger& lhs, unsigned int num);
	BigInteger& operator+=(const BigInteger& rhs);
	BigInteger operator++(int);
	friend BigInteger operator*(const BigInteger lhs, const BigInteger rhs);
	BigInteger& operator*=(const BigInteger& rhs);
	bool operator<=(const BigInteger& rhs);
	bool operator==(const BigInteger& rhs);
	operator double();
	friend std::ostream& operator<<(std::ostream& output, const BigInteger& obj);
	
	void stringToInt(std::string value);

	friend TestCases; // TODO Have students do this first thing

private:
	std::uint8_t* m_number;		// Internal representation of the number.
	unsigned int m_sizeReserved;	// Total size of the allocated space used to internally store the number
	unsigned int m_digitCount;	// How many digits are in the number.

	std::uint8_t getDigit(unsigned int position) const;
	void setDigit(unsigned int position, std::uint8_t digit);
};

#endif
