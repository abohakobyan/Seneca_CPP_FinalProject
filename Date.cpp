#include <iomanip>
#include <iostream>
#include <ctime>
#include <string>
using namespace std;
#include "Date.h"
#include "POS.h"
namespace sict {
	int _readErrorCode;
	int _year;
	int _day;
	int _mon;
	int _hour;
	int _min;
	bool _dateOnly;
	void Date::set() {
		time_t t = time(NULL);
		tm lt = *localtime(&t);
		_day = lt.tm_mday;
		_mon = lt.tm_mon + 1;
		_year = lt.tm_year + 1900;
		if (_dateOnly == false) {
			_hour = lt.tm_hour;
			_min = lt.tm_min;
		}
		else {
			
			_hour = _min = 0;
		}
	}

	int Date::errCode() const
	{
		return _readErrorCode;
	}

	bool Date::bad()const {
		return _readErrorCode != 0;
	}
	bool Date::dateOnly()const {
		return _dateOnly;

	}
	void Date::dateOnly(bool value) {
		_dateOnly = value;
		if (value == true) {
			_hour = 0;
			_min = 0;
		}

	}
	Date::Date() {
		_dateOnly = false;
		set();

	}
	Date::Date(int year, int mon, int day) {
		_dateOnly = true;
		_year = year;
		_mon = mon;
		_day = day;
		_hour = 0;
		_min = 0;
		_readErrorCode = NO_ERROR;
	}

	Date::Date(int year, int mon, int day, int hour, int min) {
		_dateOnly = false;
		_year = year;
		_mon = mon;
		_day = day;
		_hour = hour;
		_min = min;
		_readErrorCode = NO_ERROR;
	}
	int Date::value()const {
		return _year * 535680 + _mon * 44640 + _day * 1440 + _hour * 60 + _min;
	}

	void Date::errCode(int errorCode) {
		_readErrorCode = errorCode;
		

	}
	void Date::set(int year, int mon, int day, int hour, int min) {
		year = _year;
		mon = _mon;
		day = _day;
		hour = _hour;
		min = _min;
		_readErrorCode = NO_ERROR;
	}

	int Date::mdays()const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = _mon >= 1 && _mon <= 12 ? _mon : 13;
		mon--;
		return days[mon] + int((mon == 1)*((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0));
	}


	/***************************************************************************************************************/

	bool Date::operator==(const Date& D)const {
		if (this->value() == D.value()) {
			return true;
		}
		else {
			return false;
		}
	}
	bool Date::operator!=(const Date& D)const {
		if (this->value() != D.value()) {
			return false;
		}
		else {
			return true;
		}
	}
	bool Date::operator<(const Date& D)const {
		if (this->value() < D.value()) {
			return false;
		}
		else {
			return true;
		}
	}

	bool Date::operator>(const Date& D)const {
		if (this->value() > D.value()) {
			return false;
		}
		else {
			return true;
		}
	}
	bool Date::operator<=(const Date& D)const {
		if (this->value() <= D.value()) {
			return true;
		}
		else {
			return false;
		}
	}
	bool Date::operator>=(const Date& D)const {
		if (this->value() >= D.value()) {
			return true;
		}
		else {
			return false;
		}
	}

	

	std::istream& Date::read(std::istream& is){
		
		
		if (_dateOnly == true) {
			is >> _year;
			if (is.fail()) {
				_readErrorCode = CIN_FAILED;
				return is;
			}
			cin.ignore();
			is >> _mon;
			if (is.fail()) {
				_readErrorCode = CIN_FAILED;
				return is;
			}
			cin.ignore();
			is >> _day;
			if (is.fail()) {
				_readErrorCode = CIN_FAILED;
				return is;
			}
		}
		else {
			is >> _year;
			if (is.fail()) {
				_readErrorCode = CIN_FAILED;
				return is;
			}
			cin.ignore();
			is >> _mon;
			if (is.fail()) {
				_readErrorCode = CIN_FAILED;
				return is;
			}
			cin.ignore();
			is >> _day;
			if (is.fail()) {
				_readErrorCode = CIN_FAILED;
				return is;
			}
			cin.ignore();
			is >> _hour;
			if (is.fail()) {
				_readErrorCode = CIN_FAILED;
				return is;
			}
			cin.ignore();
			is >> _min;
			if (is.fail()) {
				_readErrorCode = CIN_FAILED;
				return is;
			}
		}
		int days = mdays();
		if (_year < MIN_YEAR || _year > MAX_YEAR) {
			_readErrorCode = YEAR_ERROR;
			
			return is;
		}
			else if (_mon < 1 || _mon > 12) {
				_readErrorCode = MON_ERROR;
				return is;
			}
			else if (_day < 1 || _day > days) {
				_readErrorCode = DAY_ERROR;
				return is;
			}
			else if (_hour < 0 || _hour > 24) {
				_readErrorCode = HOUR_ERROR;
				return is;
			}
			else if (_min < 0 || _min > 59) {
				_readErrorCode = MIN_ERROR;
				return is;
			}
			_readErrorCode = NO_ERROR;
			
			return is;
	
	}

	
	std::ostream & Date::write(std::ostream & ostr )const{
		// TODO: insert return statement here
		if (_dateOnly == false) {
			ostr << _year << "/" << _mon << "/" << _day
				<< "," << _hour << ":" << _min;
			

		}
		else {
			return ostr << _year << "/" << _mon << "/" << _day;
		}
		return ostr;
	}
	std::ostream & operator<<(std::ostream& os, const Date & A)  {
		A.write(os);
		return os;
	}

	std::istream & operator>>(std::istream & os, Date & B) 
	{
		B.read(os);

		return os;
	}


}