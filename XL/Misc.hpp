#ifndef XL_MISC_HPP
#define XL_MISC_HPP

#include <map>

namespace XL
{
	//checks if an element exists for a given key
	template<class K, class V>
	bool exists(K key, std::map<K, V> map)
	{
		std::map<K, V>::const_iterator it = map.find(key);
		return it != map.End();
	}
};

#endif