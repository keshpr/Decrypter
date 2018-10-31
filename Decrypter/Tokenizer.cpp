#include "provided.h"
#include "MyHash.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
	~TokenizerImpl();
    vector<string> tokenize(const std::string& s) const;
private:
	char* m_separators;
	int m_numSeparators;
	bool isInSeparators(char c) const;
};

TokenizerImpl::TokenizerImpl(string separators)
{
	m_numSeparators = separators.size();
	m_separators = new char[m_numSeparators];
	for (int i = 0; i < m_numSeparators; i++)
	{
		m_separators[i] = separators[i];
	}
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
	vector<string> words;
	string word;
	int len = s.size();
	for (int i = 0; i < len; i++)
	{
		if (isInSeparators(s[i]))
		{
			if (word != "")
			{
				words.push_back(word);
				word = "";
			}
		}
		else
		{
			word += s[i];
		}
	}
	if (word != "")
		words.push_back(word);
    return words;
}

bool TokenizerImpl::isInSeparators(char c) const
{
	for (int i = 0; i < m_numSeparators; i++)
	{
		if (c == m_separators[i])
			return true;
	}
	return false;
}

TokenizerImpl::~TokenizerImpl()
{
	delete[] m_separators;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
