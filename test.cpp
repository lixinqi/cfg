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
    std::cout << "Just init ..." << std::endl;
    std::cout << foo.oneof_type_case() << std::endl;
    std::cout << foo.of_int_value() << std::endl;
    std::cout << foo.has_of_int_value() << std::endl;
    std::cout << "After set int value(20)  ..." << std::endl;
    foo.set_of_int_value(20);
    std::cout << foo.oneof_type_case() << std::endl;
    std::cout << foo.of_int_value() << std::endl;
    std::cout << foo.has_of_int_value() << std::endl;
    std::cout << "After set enum value(Enum::kEnum0)  ..." << std::endl;
    foo.set_of_enum_value(cfg::Enum::kEnum0);
    std::cout << foo.oneof_type_case() << std::endl;
    std::cout << foo.of_enum_value() << std::endl;
    std::cout << foo.has_of_enum_value() << std::endl;
    std::cout << "After set string value(binbin)  ..." << std::endl;
    foo.set_of_string_value(std::string("binbin"));
    std::cout << foo.oneof_type_case() << std::endl;
    std::cout << foo.of_string_value() << std::endl;
    std::cout << foo.has_of_string_value() << std::endl;
    std::cout << "After set bytes value(xinqi)  ..." << std::endl;
    foo.set_of_bytes_value(std::string("xinqi"));
    std::cout << foo.oneof_type_case() << std::endl;
    std::cout << foo.of_bytes_value() << std::endl;
    std::cout << foo.has_of_bytes_value() << std::endl;
    std::cout << "After mutable_of_bar()..." << std::endl;
    foo.mutable_of_bar()->set_nickname("hongyu");
    std::cout << foo.oneof_type_case() << std::endl;
    std::cout << foo.of_bar().nickname() << std::endl;
    std::cout << foo.has_of_bar() << std::endl;
    std::cout << "After clear_of_bar()..." << std::endl;
    foo.clear_of_bar();
    std::cout << foo.oneof_type_case() << std::endl;

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
