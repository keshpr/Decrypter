#ifndef MYHASH
#define MYHASH

// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

const int STARTNG_BUCKETS = 100;


template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;


	//to be removed
	//void dump() const;

private:
	struct Pair
	{
		KeyType key;
		ValueType value;
	};
	struct Node
	{
		Pair pair;
		Node* next;
	};
	double m_maxLoadFactor;
	Node** m_array;
	int m_numBuckets;
	int m_numOccupants;

	void deleteTable(Node** ptr, int numBuckets);
	void makeTable(int numBuckets);
	unsigned int getHash(const KeyType& hashMe) const;
};

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
{
	if (maxLoadFactor <= 0.0)
		m_maxLoadFactor = 0.5;
	else if (maxLoadFactor > 2.0)
		m_maxLoadFactor = 2.0;
	else
		m_maxLoadFactor = maxLoadFactor;
	makeTable(STARTNG_BUCKETS);
}

template<typename KeyType, typename ValueType>
unsigned int MyHash<KeyType, ValueType>::getHash(const KeyType& hashMe) const
{
	unsigned int hasher(const KeyType& key);
	return hasher(hashMe) % m_numBuckets;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::makeTable(int numBuckets)
{
	m_array = new Node*[numBuckets];
	m_numBuckets = numBuckets;
	m_numOccupants = 0;
	for (int i = 0; i < m_numBuckets; i++)
	{
		m_array[i] = nullptr;
	}
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::deleteTable(Node** ptr, int numBuckets)
{
	for (int i = 0; i < numBuckets; i++)
	{
		Node* it = ptr[i];
		while (it != nullptr)
		{
			Node* temp = it->next;
			delete it;
			it = temp;
		}
	}
	delete[] ptr;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
	deleteTable(m_array,m_numBuckets);
	makeTable(STARTNG_BUCKETS);
}

template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
	unsigned int bucket = getHash(key);
	Node* it = m_array[bucket];
	while (it != nullptr)
	{
		if (it->pair.key == key)
		{
			return &(it->pair.value);
		}
		it = it->next;
	}
	return nullptr;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
	ValueType* valInMap = find(key);
	if (valInMap != nullptr)
	{
		*valInMap = value;
		return;
	}
	if ((static_cast<double>(m_numOccupants) + 1) / m_numBuckets <= m_maxLoadFactor)
	{
		unsigned int bucket = getHash(key);
		Node* temp = m_array[bucket];

		m_array[bucket] = new Node;
		m_array[bucket]->pair.key = key;
		m_array[bucket]->pair.value = value; 
		m_array[bucket]->next = temp;
		m_numOccupants++;
		return;

	}
	
	Node** tempPtr = m_array;
	int tempNumBuckets = m_numBuckets;
	makeTable(2 * m_numBuckets);
	for (int i = 0; i < tempNumBuckets; i++)
	{
		Node* it = tempPtr[i];
		while (it != nullptr)
		{
			associate(it->pair.key, it->pair.value);
			it = it->next;
		}
	}
	associate(key,value);
	deleteTable(tempPtr,tempNumBuckets);
	
}

template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const
{
	return m_numOccupants;
}
template<typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
	return static_cast<double>(m_numOccupants) / m_numBuckets;
}


template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash()
{
	deleteTable(m_array,m_numBuckets);
}


/*
template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::dump() const
{
	for (int i = 0; i < m_numBuckets; i++)
	{
		Node* it = m_array[i];
		cout << i << "->";
		while (it != nullptr)
		{
			cout << it->pair.value << "->";
			it = it->next;
		}
		cout << endl;
	}
}*/
#endif // !MYHASH

