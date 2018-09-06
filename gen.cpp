#include "gen.h"
#include <random>
#include <string>
#include <set>


Gen::Gen(int length, bool symbols, bool numbers, bool lowercase, bool uppercase, bool similar, bool ambigous) :
	m_length{ length }, m_symbols{ symbols }, m_numbers{ numbers }, m_lowercase{ lowercase }, m_uppercase{ uppercase }, m_no_similar{ similar }, m_no_ambigous{ ambigous }
{}

//insert characters (chars_to_insert) to m_chars (m_chars are characters used during generating password)
void Gen::insertChars(bool chars_type, std::string chars_to_insert)
{
	if (chars_type)
	{
		for (char temp_char : chars_to_insert)
		{
			m_chars.insert(temp_char);
		}
	}
}

//erase characters (chars_to_erase) from m_chars (m_chars are characters used during generating password)
void Gen::eraseChars(bool chars_type, std::string chars_to_erase)
{
	if (chars_type)
	{
		for (char temp_char : chars_to_erase)
		{
			m_chars.erase(temp_char);
		}
	}
}

//modify m_chars according to password properties settings
void Gen::modifyChars()
{
	insertChars(m_lowercase, m_low);
	insertChars(m_uppercase, m_upp);
	insertChars(m_numbers, m_num);
	insertChars(m_symbols, m_sym);
	eraseChars(m_no_similar, m_sim);
	eraseChars(m_no_ambigous, m_amb);
}

void Gen::generatePassword()
{
	m_chars.clear(); //clear previously used characters
	modifyChars(); //set up m_chars
	if (m_chars.empty()) return; //if all possible characters are excluded (m_chars is empty) password is not generated
	std::random_device rd; //create random device
	std::mt19937 mersenne(rd()); //create mersenne twister using random device as a seed
	std::uniform_int_distribution<> rand(33, 125); //create random number generator that generates numbers between 33 and 125 (possible ASCII characters)
	m_password.clear(); //clear previously generated password
	for (int i = 0; i < m_length; ++i)
	{
		int temp = rand(mersenne); //generate random number here (ASCII code between 33 and 125)
		if (m_chars.find(temp) != m_chars.end()) //if character with generated code is in m_chars set, push it back to m_password
		{
			m_password.push_back(temp);
		}
		else --i; //in case there is no such character in m_chars, another iteration will be needed
	}
}

void Gen::slotGeneratePassword()
{
	generatePassword(); //generate password
	emit signalPassword(m_password); //emit generated password
}
