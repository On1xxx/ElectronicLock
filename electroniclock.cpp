#include "electroniclock.hpp"

#include <stdexcept>

ElectronicLock::ElectronicLock(int _programmingCode)
	:programmingCode(_programmingCode), feel(true){}

ElectronicLock::ElectronicLock(ElectronicLock && _el)
	: codes(std::move(_el.codes)), feel(std::move(_el.feel)), programmingCode(std::move(_el.programmingCode))
{}

ElectronicLock::ElectronicLock(ElectronicLock & _el)
	: codes(_el.codes), feel(_el.feel), programmingCode(_el.programmingCode)
{}


bool ElectronicLock::toggleProgrammingMode ( int _programmingCode )
{
	if (_programmingCode==programmingCode) 
	{
		feel=(!feel);
		return true;
	}
	else return false;
}

void ElectronicLock::registerCode(int _code)
{
	if (isInProgrammingMode()) 
		codes.insert(_code);
	else throw  std::logic_error ("Not in programming mode");

}

void ElectronicLock::unregisterCode(int _code)
{
	if (isInProgrammingMode()) 
	codes.erase(_code);
	else throw  std::logic_error ("Not in programming mode");
}

void ElectronicLock::changeProgrammingCode( int _code)
{
	if (isInProgrammingMode()) 
	programmingCode=_code;
	else throw  std::logic_error ("Not in programming mode");
}

bool ElectronicLock::tryUnlocking(int _code)
{
	if (!isInProgrammingMode()) 
	{
		return codes.find(_code) != codes.end();
	}
	else throw  std::logic_error ("Not in operational mode");
}

 bool ElectronicLock::tryUnlocking(const char* _code)
{
	if (!isInProgrammingMode()) 
	{
		int temp;
		int nMatched = sscanf(_code, "%d", &temp);
		if (nMatched != 1)
			throw std::logic_error("Bad format");
		if (codes.find(temp)!=codes.end()) return true;
		else return false;
	}
	else throw std::logic_error ("Not in operational mode");
}

 bool ElectronicLock::operator == (const ElectronicLock & el) const
 {
	 if (programmingCode != el.getPcode())
		 return false;

	 return std::equal(codes.begin(), codes.end(), el.codes.begin(), el.codes.end());
	
 }

 bool ElectronicLock::operator != (const ElectronicLock & el) const
 {
	 return !(*this == el);
 }

 ElectronicLock & ElectronicLock::operator = (ElectronicLock && _el)
 {
	
	 if (&_el == this)
		 return *this;

	 std::swap(programmingCode, _el.programmingCode);
	 std::swap(feel, _el.feel);
	 std::swap(codes, _el.codes);


	 return *this;
 }

 ElectronicLock & ElectronicLock::operator = (const ElectronicLock & _el)
 {
	 if (&_el == this)
		 return *this;

	 programmingCode= _el.programmingCode;
	 feel= _el.feel;
	 codes= _el.codes;

	 return *this;
 }