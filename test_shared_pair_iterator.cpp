#include <map>
#include <iostream>
#include "demo.cfg.h"
#include "shared_pair_iterator.h"

struct FooMap {

  using map_type = std::map<int64_t, cfg::Foo>;
  using shared_mut_iterator = ::oneflow::cfg::_SharedMutPairIterator_<map_type, cfg::Foo>;
  using shared_const_iterator = ::oneflow::cfg::_SharedConstPairIterator_<map_type, cfg::ConstFoo>;

  shared_mut_iterator shared_mut_begin() { return foo_map.begin(); }
  shared_mut_iterator shared_mut_end() { return foo_map.end(); }

  shared_const_iterator shared_const_begin() { return foo_map.begin(); }
  shared_const_iterator shared_const_end() { return foo_map.end(); }

 std::map<int64_t, cfg::Foo> foo_map;
};

int main() {
  FooMap map;
  map.foo_map[30].mutable_bar()->set_nickname("good");
  map.foo_map[40].mutable_bar()->set_nickname("nice");
  for (auto iter = map.shared_mut_begin(); iter != map.shared_mut_end(); ++iter) {
    std::cout << iter->first << " " << iter->second->bar().nickname() << std::endl;
  }
  std::cout << "good" << std::endl;
  for (auto iter = map.shared_const_begin(); iter != map.shared_const_end(); ++iter) {
    std::cout << iter->first << " " << iter->second->bar().nickname() << std::endl;
  }
  return 0;
}
