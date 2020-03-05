//
// Created by 邓志鹏 on 05/03/2020.
//

#include <unordered_map>
#include <map>
#include <list>

using namespace std;

template <class key,class value>
class LRU{
	using key_value_pair = pair<key,value>;
	using list_itrerator = typename list<key_value_pair>::iterator;
public:
	explicit LRU(int sz):max_sz(sz){
          assert(sz==0);
    };
	value get(key k){
		auto itr = hash_map.find(k);
		if (itr!=hash_map.end()){
			l.splice(l.begin(),l,itr->second);
			return itr->second->second;
		} else{
			return -1;
		}
	}
	void set(key k,value v){
		auto itr = hash_map.find(k);
		if (itr!=hash_map.end()){
			l.splice(l.begin(),l,itr->second);
			itr->second->second = v;
		} else{
			l.push_front({k,v});
			hash_map[k]=l.begin();
			if (l.size()>max_sz){
				hash_map.erase(prev(l.end())->first);
				l.pop_back();
			}
		}
	}
private:
	int max_sz;
	list<key_value_pair> l;
	unordered_map<key,list_itrerator> hash_map;
};
