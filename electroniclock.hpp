#ifndef _ELECTRONICLOCK_HPP_
#define _ELECTRONICLOCK_HPP_
#include <set>

/*****************************************************************************/

class ElectronicLock
{
private:

	int programmingCode;
	bool feel;
	std::set<int> codes;

	int getPcode() const { return programmingCode; }

	

public:

	explicit ElectronicLock(int programmingCode);

	ElectronicLock(ElectronicLock & _el);
	ElectronicLock(ElectronicLock && _el);

	ElectronicLock & operator = (ElectronicLock && _el);
	ElectronicLock & operator = (const ElectronicLock & _el);

	bool isInProgrammingMode() const { return feel; }


	bool toggleProgrammingMode ( int _programmingCode );

	void registerCode(int _code);

	void unregisterCode(int _code);

	void changeProgrammingCode( int _code);
	
	bool tryUnlocking(int _code);

	bool tryUnlocking(const char* _code);

	bool operator == (const ElectronicLock & el) const;
	bool operator != (const ElectronicLock & el) const;
	

};


/*****************************************************************************/

#endif //  _ELECTRONICLOCK_HPP_