#include <iostream>
#include "demo.cfg.h"

int main() {
  {
    cfg::Foo foo;
    std::cout << foo.name() << std::endl;
    std::cout << foo.bar().nickname() << std::endl;
    foo.mutable_bar()->set_nickname("Jacky");
    std::cout << foo.bar().nickname() << std::endl;
    std::cout << foo.optional_bar().nickname() << std::endl;
    foo.mutable_optional_bar()->set_nickname("Jacky");
    std::cout << foo.optional_bar().nickname() << std::endl;

    std::cout << foo.map_int_int().size() << std::endl;
    auto* m = foo.mutable_map_int_int();
    (*m)[0] = 1;
    (*m)[2] = 3;

    for (const auto& pair: foo.map_int_int())
    {
      std::cout << pair.first << " " << pair.second << std::endl;
    }
    
    std::cout << foo.map_int_int().size() << std::endl;
  }
  return 0;
}
