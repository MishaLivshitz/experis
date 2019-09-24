/***
 * 
 * @brief :Bidirectional map implementaition - can get item by key and also by value
 * 
 * Author :Michael Livshitz
 * Date :19.6.19
 */

#include <iostream>
#include <map>

template <typename K, typename V>
class TwoWayMap
{
public:
	//CTOR
	TwoWayMap();
	
	//Operators	
	V operator[] (K const& _key);
	K operator() (V const& _val);
	
	V& getValueByKey(K const& _key);
	K& getKeyByValue(V const& _value);
	
	
	bool insert(K const& _key, V const& _val);
	bool removeByKey(K const& _key);
	bool removeByValue(V const& _val);
	
	size_t size() const;
	void print(std::ostream& _os = std::cout) const;
	
private:
	void printByKey(std::ostream& _os = std::cout) const;
	void printByVal(std::ostream& _os = std::cout) const;

	
private:
	std::map<K, V> m_keyMap;
	std::map<V, K> m_valueMap;
	
};

template <typename K, typename V>
TwoWayMap<K,V>::TwoWayMap()
:m_keyMap()
,m_valueMap()
{	
}

template <typename K, typename V>
V TwoWayMap<K,V>::operator [](K const& _key)
{
	if(m_keyMap.count(_key))
	{
		return m_keyMap[_key];		
	}
	
	return 0;
}

template <typename K, typename V>
K TwoWayMap<K,V>::operator ()(V const& _val)
{
	if(m_valueMap.count(_val))
	{		
		return m_valueMap[_val];
	}
	
	return 0;
}

template <typename K, typename V>
void TwoWayMap<K,V>::print(std::ostream& _os) const
{
	printByKey(_os);
	_os << '\n';
	printByVal(_os);
	
}

template <typename K, typename V>
void TwoWayMap<K,V>::printByKey(std::ostream& _os) const
{
	typename std::map<K, V>::const_iterator bi = m_keyMap.begin();	
	typename std::map<K, V>::const_iterator ei = m_keyMap.end();
	
	_os << "By key:\n";
	
	while(bi!=ei)
	{
		_os << "Key: " << bi->first;
		_os << ", Value: " << bi->second;
		_os << "\n";
		++bi;
	}	
}

template <typename K, typename V>
void TwoWayMap<K,V>::printByVal(std::ostream& _os) const
{
	typename std::map<V, K>::const_iterator bi = m_valueMap.begin();	
	typename std::map<V, K>::const_iterator ei = m_valueMap.end();
	
	_os << "By Value:\n";
	
	while(bi!=ei)
	{
		_os << "Key: " << bi->first;
		_os << ", Value: " << bi->second;
		_os << "\n";
		++bi;
	}
}

template <typename K, typename V>
bool TwoWayMap<K,V>::insert(K const& _key, V const& _val)
{
	bool status = false;
	typename std::map<K,V>:: iterator kItr = m_keyMap.find(_key);
	typename std::map<V,K>:: iterator vItr = m_valueMap.find(_val);
		
	if(kItr == m_keyMap.end() && vItr == m_valueMap.end())
	{	
		m_keyMap[_key] = _val;
		m_valueMap[_val] = _key;
		status = true;
	}
	
	return status;
}

template <typename K, typename V>
bool TwoWayMap<K,V>::removeByKey(K const& _key)
{
	bool status = false;
	typename std::map<K,V>:: iterator kItr = m_keyMap.find(_key);

	if(kItr!= m_keyMap.end())
	{
		m_keyMap.erase(kItr->first);
		m_valueMap.erase(kItr->second);
		status = true;
	}
	
	return status; 
}

template <typename K, typename V>
bool TwoWayMap<K,V>::removeByValue(V const& _val)
{
	bool status = false;
	typename std::map<V,K>:: iterator vItr = m_valueMap.find(_val);

	if(vItr!= m_valueMap.end())
	{
		m_valueMap.erase(vItr->first);
		m_keyMap.erase(vItr->second);
		status = true;
	}
	
	return status; 
}

template <typename K, typename V>
size_t TwoWayMap<K,V>::size() const
{
	return m_keyMap.size();
}

template <typename K, typename V>
V& TwoWayMap<K,V>::getValueByKey(K const& _key)
{
	
	return m_keyMap[_key];
}

template <typename K, typename V>
K& TwoWayMap<K,V>::getKeyByValue(V const& _value)
{
	return m_valueMap[_value];
}

template <typename K, typename V>
std::ostream& operator<< (std::ostream& _os , TwoWayMap<K, V> const& _twMap)
{
	_twMap.print(_os);
	return _os;
}
