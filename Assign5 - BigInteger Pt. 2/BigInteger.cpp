#include <iostream>
#include <algorithm>
#include <cmath>

#include "BigInteger.hpp"

BigInteger::BigInteger() {
	m_digitCount = 0;
	m_sizeReserved = 4;
	m_number = new uint8_t[m_sizeReserved];
	for (unsigned int i = 0; i < m_sizeReserved; i++) {
		m_number[i] = 0;
	}
	
}

BigInteger::BigInteger(std::string number) {
	
	stringToInt(number);
}

BigInteger::BigInteger(int number) {

	std::string num = std::to_string(number);
	stringToInt(num);
}

void BigInteger::stringToInt(std::string value) {
	m_digitCount = 0;
	m_sizeReserved = 4;
	m_number = new uint8_t[m_sizeReserved];
	for (unsigned int i = 0; i < m_sizeReserved; i++) {
		m_number[i] = 0;
	}
	int num;
	for (unsigned int i = 0; i < value.size(); i++) {
		unsigned int reverse = ((value.size() - 1) - i);
		num = (value[reverse] - '0');
		setDigit(i, num);
	}
}

BigInteger::BigInteger(const BigInteger& obj) {
	m_digitCount = obj.m_digitCount;
	m_sizeReserved = obj.m_sizeReserved;
	m_number = new uint8_t[obj.m_sizeReserved];
	for (unsigned int i = 0; i < obj.m_sizeReserved; i++) {
		m_number[i] = 0;
	}
	for (unsigned int i = 0; i < obj.m_digitCount; i++) {
		m_number[i] = obj.m_number[i];
	}
}

BigInteger::~BigInteger() {
	delete[] m_number;
}

BigInteger& BigInteger::operator=(const BigInteger& rhs) {
	m_digitCount = rhs.m_digitCount;
	m_sizeReserved = rhs.m_sizeReserved;
	m_number = new uint8_t[rhs.m_sizeReserved];
	for (unsigned int i = 0; i < m_sizeReserved; i++) {
		m_number[i] = 0;
	}
	for (unsigned int i = 0; i < m_digitCount; i++) {
		m_number[i] = rhs.m_number[i];
	}
	return *this;
}

BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs) {
	BigInteger result;
	unsigned int length = (lhs.m_digitCount > rhs.m_digitCount) ? lhs.m_digitCount : rhs.m_digitCount;

	int carry = 0;
	for (unsigned int digit = 0; digit < length; digit++)
	{
		int v1 = lhs.getDigit(digit);
		int v2 = rhs.getDigit(digit);
		int sum = v1 + v2 + carry;
		int single = sum % 10;
		carry = ((sum - single) > 0) ? (sum - single) / 10 : 0;

		result.setDigit(digit, single);
	}
	if (carry > 0)
	{
		result.setDigit(length, carry);
	}

	return result;
}
BigInteger operator+(const BigInteger& lhs, unsigned int num) {
	BigInteger rhs(num);
	BigInteger result = lhs + rhs;
	return result;
}

BigInteger & BigInteger::operator+=(const BigInteger & rhs) {
	BigInteger result = *this;
	*this = result + rhs;
	return *this;
}

BigInteger BigInteger::operator++(int) {
	BigInteger result = *this;
	*this += 1;
	return result;
}

BigInteger operator*(const BigInteger lhs, const BigInteger rhs) {
	BigInteger result;
	const BigInteger& b = (lhs.m_digitCount < rhs.m_digitCount) ? lhs : rhs;
	const BigInteger& t = (lhs.m_digitCount < rhs.m_digitCount) ? rhs : lhs;

	for (unsigned int bDigit = 0; bDigit < b.m_digitCount; bDigit++)
	{
		BigInteger temp(0);
		int v1 = b.getDigit(bDigit);
		int carry = 0;
		for (unsigned int tDigit = 0; tDigit < t.m_digitCount; tDigit++)
		{
			int v2 = t.getDigit(tDigit);
			int sum = v1 * v2 + carry;
			int single = sum % 10;
			carry = ((sum - single) > 0) ? (sum - single) / 10 : 0;

			temp.setDigit(bDigit + tDigit, single);
		}
		if (carry > 0)
		{
			temp.setDigit(bDigit + t.m_digitCount, carry);
		}
		BigInteger temp2 = result + temp;
		result = temp2;
	}
	return result;
}

BigInteger& BigInteger::operator*=(const BigInteger& rhs) {
	BigInteger result = *this;
	*this = result * rhs;
	return *this;
}

bool BigInteger::operator<=(const BigInteger & rhs)
{
	if (this->m_digitCount < rhs.m_digitCount) return true;
	if (this->m_digitCount > rhs.m_digitCount) return false;
	//
	// Have to go digit by digit
	for (int digit = m_digitCount - 1; digit >= 0; digit--)
	{
		if (this->m_number[digit] < rhs.m_number[digit]) return true;
		if (this->m_number[digit] > rhs.m_number[digit]) return false;
	}
	return true;
}

bool BigInteger::operator==(const BigInteger & rhs)
{
	if (this->m_digitCount != rhs.m_digitCount) {
		return false;
	}
	else {
		for (unsigned int i = 0; i < this->m_digitCount; i++) {
			if (this->m_number[i] != rhs.m_number[i]) {
				return false;
			}
		}
		return true;
	}
}

BigInteger::operator double() {
	double temp = 0;
	for (unsigned int digit = 0; digit < this->m_digitCount; digit++) {
		temp += static_cast<double>((this->m_number[digit]) * pow(10, digit));
	}
	return temp;
}

std::ostream& operator<<(std::ostream & output, const BigInteger & obj)
{
	for (unsigned int digit = obj.m_digitCount; digit > 0; digit--) {
		output << static_cast<int>(obj.m_number[digit - 1]);
	}
	return output;
}

void BigInteger::setDigit(unsigned int position, std::uint8_t digit) {

	if (position >= m_sizeReserved) {
		while (m_sizeReserved <= position) {
			m_sizeReserved *= 2;

		}
		std::uint8_t* temp = new uint8_t[m_sizeReserved];
		for (int i = 0; i < m_sizeReserved; i++) {
		temp[i] = 0;
	}

		for (int i = 0; i < m_digitCount; i++) {
			temp[i] = m_number[i];
		}

		delete[] m_number;
		m_number = temp;
	}
	m_number[position] = digit;
	m_digitCount = position + 1;
}

// ------------------------------------------------------------------
//
// Returns the digit as the specified positon.  If the position is greater
// that the number representation, a 0 is returned.
//
// ------------------------------------------------------------------
std::uint8_t BigInteger::getDigit(unsigned int position) const
{
	if (position < m_digitCount)
	{
		return m_number[position];
	}

	return 0;
}


