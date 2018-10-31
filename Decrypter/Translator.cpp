#include "provided.h"
#include <string>
using namespace std;


class TranslatorImpl
{
public:
	TranslatorImpl();
	~TranslatorImpl();
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
	struct MapPair
	{
		struct Pair
		{
			char letter;
			int otherIndex;

		};
		MapPair()
		{
			
			for (int i = 0; i < 26; i++)
			{
				fromPairs[i].letter = 'a' + i;
				fromPairs[i].otherIndex = -1;
				toPairs[i].letter = 'a' + i;
				toPairs[i].otherIndex = -1;
			}
		}
		MapPair(const MapPair* oldMap)
		{
			
			for (int i = 0; i < 26; i++)
			{
				fromPairs[i].letter = oldMap->fromPairs[i].letter;
				fromPairs[i].otherIndex = oldMap->fromPairs[i].otherIndex;
				toPairs[i].letter = oldMap->toPairs[i].letter;
				toPairs[i].otherIndex = oldMap->toPairs[i].otherIndex;
			}
		}
		
		Pair fromPairs[26];
		Pair toPairs[26];
	};
	MapPair* m_currMap;
	vector<MapPair*> m_oldMaps;

};


TranslatorImpl::TranslatorImpl()
{
	m_currMap = new MapPair();
}

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
	unsigned int cipherLen = ciphertext.size();
	unsigned int plainLen = plaintext.size();
	if (cipherLen != plainLen)
		return false;
	MapPair* newMap = new MapPair(m_currMap);

	for (int i = 0; i < cipherLen; i++)
	{
		if (!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
		{
			delete newMap;
			return false;
		}
		unsigned int cipherIndex = tolower(ciphertext[i]) - 'a';
		unsigned int plainIndex = tolower(plaintext[i]) - 'a';
		int toIndex = newMap->fromPairs[cipherIndex].otherIndex;
		int fromIndex = newMap->toPairs[plainIndex].otherIndex;
		if ((toIndex != -1 && newMap->toPairs[toIndex].letter != tolower(plaintext[i])) ||
			(fromIndex != -1 && newMap->fromPairs[fromIndex].letter != tolower(ciphertext[i])))
		{
			delete newMap;
			return false;
		}
		newMap->fromPairs[cipherIndex].otherIndex = plainIndex;
		newMap->toPairs[plainIndex].otherIndex =  cipherIndex;
	}
	m_oldMaps.push_back(m_currMap);
	m_currMap = newMap;
	return true;

}

bool TranslatorImpl::popMapping()
{
	if (m_oldMaps.empty())
		return false;
	MapPair* tempMap = m_currMap;
	vector<MapPair*>::iterator it = m_oldMaps.end();
	it--;
	m_currMap = (*it);
	m_oldMaps.erase(it);
	delete tempMap;
	return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
	string translation;
	int len = ciphertext.size();
	for (int i = 0; i < len; i++)
	{
		if (!isalpha(ciphertext[i]))
		{
			translation += ciphertext[i];
			continue;
		}
		unsigned int index = tolower(ciphertext[i]) - 'a';
		int toIndex = m_currMap->fromPairs[index].otherIndex;
		char toPrint = toIndex >= 0 ? m_currMap->toPairs[toIndex].letter : '?';
		if (islower(ciphertext[i]))
			translation += tolower(toPrint);
		else
			translation += toupper(toPrint);
	}
	return translation;
}

TranslatorImpl::~TranslatorImpl()
{
	vector<MapPair*>::iterator it = m_oldMaps.begin();
	while (it != m_oldMaps.end())
	{
		delete *it;
		it = m_oldMaps.erase(it);
	}
	delete m_currMap;
}
//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
