#include "provided.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

const string SEPARATORS = "0123456789 ,;:.!()[]{}-\"#$%^&";

class DecrypterImpl
{
public:
	DecrypterImpl();
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
	WordList m_wordList;
	Translator m_translator;
	Tokenizer m_tokenizer;
	vector<string> m_possibleAnswers;
	set<int> chosenWords;

	int numUnknowns(const string& word) const;
	void reset();
	void sortThis(vector<string>& words);
	
};

DecrypterImpl::DecrypterImpl() : m_tokenizer(SEPARATORS)
{}

void DecrypterImpl::reset()
{
	vector<string>::iterator it = m_possibleAnswers.begin();
	while (it != m_possibleAnswers.end())
	{
		it = m_possibleAnswers.erase(it);
	}
	
}

bool DecrypterImpl::load(string filename)
{
	return m_wordList.loadWordList(filename);
}

int DecrypterImpl::numUnknowns(const string& word) const
{
	int num = 0;
	int len = word.size();
	for (int i = 0; i < len; i++)
	{
		if (word[i] == '?')
			num++;
	}
	return num;
}

void DecrypterImpl::sortThis(vector<string>& words)
{
	if (words.empty())
		return;
	set<string> temp;
	vector<string>::iterator vecIt = words.end();
	vecIt--;
	while (vecIt != words.end())
	{
		temp.insert(*vecIt);
		vecIt = words.erase(vecIt);
		if (!words.empty())
			vecIt--;
	}
	set<string>::iterator it = temp.begin();
	int i = 0;
	while (it != temp.end())
	{
		words.push_back(*it);
		it++;
		i++;
	}
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
	if (chosenWords.empty())
		reset();
	vector<string> cipherWords = m_tokenizer.tokenize(ciphertext);	
	int chosenOne = 0;
	int maxUnknowns = 0;
	int len = cipherWords.size();
	for (int i = 0; i < len; i++)
	{
		string translation = m_translator.getTranslation(cipherWords[i]);
		int unknowns = numUnknowns(translation);
		if ( unknowns > maxUnknowns &&
			chosenWords.find(i) == chosenWords.end())
		{
			maxUnknowns = unknowns;
			chosenOne = i;
		}
	}
	chosenWords.insert(chosenOne);
	string translation = m_translator.getTranslation(cipherWords[chosenOne]);
	vector<string> possibleWords = m_wordList.findCandidates(cipherWords[chosenOne], translation);
	sortThis(possibleWords);
	if (possibleWords.empty())
	{
		m_translator.popMapping();
		chosenWords.erase(chosenOne);
		return possibleWords;
	}
	for (int i = 0; i < possibleWords.size(); i++)
	{
		if (!m_translator.pushMapping(cipherWords[chosenOne], possibleWords[i]))
		{
			continue;
		}
		string possiblePlainText = m_translator.getTranslation(ciphertext);
		bool notFoundInWordList = false;
		bool notCompletelyDone = false;
		vector<string> translatedWords = m_tokenizer.tokenize(possiblePlainText);
		//vector<string> fromNextCrack;
		for (int j = 0; j < translatedWords.size(); j++)
		{
			if (numUnknowns(translatedWords[j]) == 0)
			{
				if (!m_wordList.contains(translatedWords[j]))
				{
					notFoundInWordList = true;
					break;
				}
			}
			else
				notCompletelyDone = true;
		}
		if (notFoundInWordList)
		{
			m_translator.popMapping();
			continue;
		}
		if (notCompletelyDone)
		{
			crack(ciphertext);
			//m_translator.popMapping();
			continue;
		}
		//cout << possiblePlainText << endl;
		m_possibleAnswers.push_back(possiblePlainText);		
		m_translator.popMapping();
	}
	m_translator.popMapping();
	chosenWords.erase(chosenOne);	
	return m_possibleAnswers;


}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
