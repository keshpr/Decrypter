#include "provided.h"
#include "MyHash.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;

private:
	struct Link
	{
		string word;
		Link* next;
	};
	MyHash<string, string> m_words;
	MyHash<string, vector<string>> m_sequenceTable;

	string produceSequence(const string& s) const;
	void convertToLower(string& s) const;
};

string WordListImpl::produceSequence(const string& s) const
{
	char letters[27];
	for (int i = 0; i < 27; i++)
	{
		letters[i] = '\0';
	}
	string sequence = "";
	char lastChar = 'A';
	char val;
	unsigned int len = s.size();
	for (int i = 0; i < len; i++)
	{
		if (!isalpha(s[i]) && s[i] != '\'')
			return "";
		int index = isalpha(s[i]) ? tolower(s[i]) - 'a' : 26;
		val = letters[index];
		if (val != '\0')
		{
			sequence += val;
		}
		else
		{
			letters[index] = lastChar;
			sequence += lastChar;
			lastChar++;

		}
	}
	return sequence;
}

void WordListImpl::convertToLower(string& s) const
{
	unsigned int len = s.size();
	for (int i = 0; i < len; i++)
	{
		s[i] = tolower(s[i]);
	}
}
bool WordListImpl::loadWordList(string filename)
{
	m_sequenceTable.reset();
	m_words.reset();
	ifstream inputFile(filename);
	if (!inputFile)
	{
		return false;
	}
	string word;
	string seq;
	while (inputFile >> word)
	{
		convertToLower(word);
		seq = produceSequence(word);
		if (seq == "")
			continue;
		m_words.associate(word,word);
		vector<string>* linkPtr = m_sequenceTable.find(seq);
		
		if (linkPtr != nullptr)
		{
			(*linkPtr).push_back(word);
		}
		else
		{
			vector<string> vec;
			vec.push_back(word);
			m_sequenceTable.associate(seq, vec);		
		}				
		
	}
	if (!inputFile.eof())
		return false;
	return true;
}

bool WordListImpl::contains(string word) const
{
	convertToLower(word);
	const string* wordptr  = m_words.find(word);
	if (!wordptr)
		return false;
	return true;
	
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
	vector<string> candidates;
	int transLen = currTranslation.size();
	int cipherLen = cipherWord.size();
	if (transLen != cipherLen)
		return candidates;
	for (int i = 0; i < cipherLen; i++)
	{
		if (!isalpha(currTranslation[i]) && currTranslation[i] != '?' && currTranslation[i] != '\'')
			return candidates;
		if (!isalpha(cipherWord[i]) && cipherWord[i] != '\'')
			return candidates;
		if ((isalpha(currTranslation[i]) || currTranslation[i] == '?') && !isalpha(cipherWord[i]))
			return candidates;
		if (currTranslation[i] == '\'' && cipherWord[i] != '\'')
			return candidates;
	}
	string seq = produceSequence(cipherWord);
	vector<string> const* linkP = m_sequenceTable.find(seq);
	if (!linkP)
		return candidates;

	vector<string>::const_iterator it = (*linkP).begin();
	while (it != (*linkP).end())
	{
		int flag = 0;
		string word = (*it);
		unsigned int len = word.size();
		for (int i = 0; i < len; i++)
		{
			if (currTranslation[i] == '?')
			{
				if (!isalpha(word[i]))
				{
					flag = 1;
					break;
				}
				continue;
			}
			if (tolower(word[i]) != tolower(currTranslation[i]))
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			candidates.push_back(word);
		}
		it++;
	}

    return candidates;
}


//***** hash functions for string, int, and char *****

unsigned int hasher(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hasher(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hasher(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}
