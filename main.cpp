#include <iostream>
#include "demo.cfg.h"
#include "demo.pb.h"

int main() {
  {
    cfg::Foo foo;
    std::cout << foo.name() << std::endl;
    std::cout << foo.optional_int32() << std::endl;
    std::cout << foo.bar().nickname() << std::endl;
    foo.mutable_bar()->set_nickname("Jacky");
    std::cout << foo.bar().nickname() << std::endl;
    std::cout << foo.optional_bar().nickname() << std::endl;
    foo.mutable_optional_bar()->set_nickname("Jacky");
    std::cout << foo.optional_bar().nickname() << std::endl;
    foo.add_card_strings("good");
    std::cout << foo.card_strings_size() << std::endl;
    std::cout << foo.card_strings(0) << std::endl;
    foo.add_card_strings("nice");
    std::cout << foo.card_strings_size() << std::endl;
    std::cout << foo.card_strings(1) << std::endl;
  }
  return 0;
}
