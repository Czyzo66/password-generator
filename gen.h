#pragma once

#include <QtWidgets/QMainWindow>
#include <QString>
#include <string>
#include <set>

class Gen : public QMainWindow
{
	Q_OBJECT
private:
	QString m_password; //generated password
	int m_length; //passwords length
	std::string m_sym = ("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{}"); //symbols
	std::string m_num = ("0123456789"); //numbers
	std::string m_low = ("abcdefghijklmnopqrstuvwxyz"); //lowercase letters
	std::string m_upp = ("ABCDEFGHIJKLMNOPQRSTUVWXYZ"); //uppercase letters
	std::string m_sim = ("oO0iIl1"); //similar characters
	std::string m_amb = ("()[]{}<>/\\'\"`,.;:"); //ambigous characters
	std::set<char> m_chars; //set from which password characters are randomly picked up during generating password

	//password properties setting:
	bool m_symbols; //if true: include symbols
	bool m_numbers; //if true: include numbers
	bool m_lowercase; //if true: include lowercase letters
	bool m_uppercase; //if true: include uppercase letters
	bool m_no_similar; //if true: exclude similar characters
	bool m_no_ambigous; //if true exclude ambigous characters

	void insertChars(bool chars_type, std::string chars_to_insert); //insert set of chars stored in chars_to_insert to m_chars if chars_type is true
	void eraseChars(bool chars_type, std::string chars_to_erase); //erase set of chars stored in chars_to_insert from m_chars if chars_type is true
	void modifyChars(); //modify m_chars according to password properties settings
	void generatePassword(); //generate password
public:
	Gen(int length, bool symbols, bool numbers, bool lowercase, bool uppercase, bool similar, bool ambigous); //constructor
signals:
	void signalPassword(QString password); //emit password (called by slotGeneratePassword() )
public slots:
	void slotSetLength(int length) { m_length = length + 1; }
	void slotSetSymbols(int symbols) { m_symbols = symbols; }
	void slotSetNumbers(int numbers) { m_numbers = numbers; }
	void slotSetLowercase(int lowercase) { m_lowercase = lowercase; }
	void slotSetUppercase(int uppercase) { m_uppercase = uppercase; }
	void slotSetSimilar(int similar) { m_no_similar = similar; }
	void slotSetAmbigous(int ambigous) { m_no_ambigous = ambigous; }
	void slotGeneratePassword();
};
