//
// Created by 邓志鹏 on 05/03/2020.
//

#include <unordered_map>
#include <map>
#include <list>
using namespace std;

template <class key_t,class value_t>
class LFU{
	using  key_value_pair = pair<key_t,value_t>;
	using map_iterator = typename multimap<int,key_value_pair>::iterator;
public:
	explicit LFU(size_t sz):max_sz(sz){
        assert(sz==0);
    };
	
	value_t get(key_t key){
		auto itr = hash_map.find(key);
		if(itr!=hash_map.end()){
			auto newItr = freq_map.insert({itr->second->first+1,itr->second->second});
			freq_map.erase(itr->second);
			hash_map[key] = newItr;
			return itr->second->second.second;
		} else{
			return -1;
		}
	}
	void set(key_t key,value_t value){
		auto itr = hash_map.find(key);
		if(itr!=hash_map.end()){
			auto newItr = freq_map.insert({itr->second->first+1,itr->second->second});
			newItr->second.second = value;
			freq_map.erase(itr->second);
			hash_map[key] = newItr;
		} else{

			if (freq_map.size()==max_sz){
				hash_map.erase(freq_map.begin()->second.first);
				freq_map.erase(freq_map.begin());
			}
			//freq_map.begin() is a hint position, which can make the complexity to constant
		        auto newItr = freq_map.insert(freq_map.begin(),{1,{key,value}});
		        hash_map[key]=newItr;
		}
	}

private:
	size_t max_sz;
	multimap<int,key_value_pair> freq_map;
	unordered_map<key_t,map_iterator> hash_map;
};
