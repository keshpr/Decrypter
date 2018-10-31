#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif
#include <iostream>
#include "MyHash.h"
#include "provided.h"
#include <cassert>
using namespace std;

//#define CHECKHASH
//#define CHECKTOKEN
//#define CHECKWORDLIST
//#define CHECKTRANS
#define CHECKDECRYPT

const string string1 = "Trcy oyc koon oz rweelycbb vmobcb, wyogrcn oecyb; hjg ozgcy tc moox bo moya wg grc vmobck koon grwg tc ko yog bcc grc oyc trlvr rwb hccy oecyck zon jb. - Rcmcy Xcmmcn";
const string string2 = "Jxwpjq qwrla glcu pcx qcn xkvv dw uclw ekarbbckpjwe dq jzw jzkpta jzrj qcn ekep'j ec jzrp dq jzw cpwa qcn eke ec. -Urls Jxrkp";
const string string3 = "Xjzwq gjz cuvq xz huri arwqvudiy fuk ufjrqoq svquxiy. -Lzjk Nqkkqcy";
const string string4 = "Axevfvu lvnelvp bxqp mvpprjv rgl bvoop Grnxvgkvuj dqupb jvbp buvrbvl be lqggvu.";

int main()
{
#ifdef CHECKHASH
	
	MyHash<int, string> m;
	m.associate(222, "Ethel");
	m.associate(333, "Lucy");
	m.associate(111, "Fred");
	assert(m.getNumItems() == 3);
	cout << m.getLoadFactor() << endl;
	assert(abs(m.getLoadFactor() - 0.03) < 0.00001);
	MyHash<char, int> myTable(2);
	//cout << "Reached 1\n";
	for (int i = 0; i < 20; i++)
	{
		myTable.associate('0' + i,i);
	}
	myTable.associate('0', 0);
	//cout << *myTable.find('a') << endl;
	//myTable.associate('a' + 10, 10);

	//myTable.dump();
	/*for (int i = 0; i < 20; i++)
	{
		cout << *myTable.find('0' + i) << endl;
	}*/
#endif
#ifdef CHECKTOKEN
	Tokenizer t("0123456789 ,;:.!()[]{}-\"#$%^&");
	vector<string>	v = t.tokenize("W,svbbvnaq8vy0dvbq[yhtvavnja6vy w 444 fvb");
	//	v	now	contains	"This",	"is",	"a",	"test",	"It's",	"the",	and	"best"
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
	string s = "!!!!!";
	v = t.tokenize(s);
	cout << v.size() << endl;
	//	v	is	now	empty
#endif // CHECKTOKEN
#ifdef CHECKWORDLIST

	WordList wordList;
	cout << "Opened:" << wordList.loadWordList("wordlistchecker.txt") << endl;
	assert(!wordList.contains("abet"));
	assert(!wordList.contains("xxxxxxxxx"));
	assert(!wordList.contains("abetment") );
	assert(!wordList.contains("fighting") );
	assert(wordList.contains("first") );
	assert(!wordList.contains("firsts") );
	assert(wordList.contains("second") );
	assert(!wordList.contains("seconds") );
	cout << "Passed" << endl;

	wordList.loadWordList("wordlist.txt");
	vector<string> cands;
	cands = wordList.findCandidates("abced", "z????");
	vector<string>::iterator it = cands.begin();
	while (it != cands.end())
	{
		cout << (*it) << endl;
		it++;
	}
	
#endif // CHECKWORDLIST
#ifdef CHECKTRANS
	Translator translator;
	translator.pushMapping("ABC", "XYZ");
	assert(translator.getTranslation("abcdef") == "xyz???");
	assert(translator.getTranslation("aBCdef::") == "xYZ???::");
	assert(translator.getTranslation("aBCdef::??") == "xYZ???::??");
	assert(translator.getTranslation("aBCdef::xyz") == "xYZ???::???");
	assert(!translator.pushMapping("adef", "pqrs"));
	assert(translator.pushMapping("adef", "xpqr"));
	assert(translator.getTranslation("abcdef") == "xyzpqr");
	assert(translator.getTranslation("abCDef") == "xyZPqr");
	assert(translator.getTranslation("abcdef!!:ghij") == "xyzpqr!!:????");
	assert(translator.popMapping());
	assert(translator.getTranslation("abcdef!!:ghij") == "xyz???!!:????");
	assert(!translator.pushMapping("ghij", "lmnx"));
	assert(translator.pushMapping("ghij", "lmno"));
	assert(translator.getTranslation("abcdef!!:ghij") == "xyz???!!:lmno");
	assert(translator.popMapping());
	assert(translator.getTranslation("abcdef!!:ghij") == "xyz???!!:????");
	assert(translator.popMapping());
	assert(translator.getTranslation("abcdef!!:ghij") == "??????!!:????");
	std:: cout << "Passed" << endl;
#endif // CHECKTRANS
#ifdef CHECKDECRYPT
	Decrypter decrypter;
	decrypter.load("wordlist.txt");
	vector<string> possibles = decrypter.crack(string1);
	for (int i = 0; i < possibles.size(); i++)
	{
		cout << possibles[i] << endl;
	}

#endif // CHECKDECRYPT



}