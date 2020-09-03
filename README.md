### Introduction
Given proto file demo.proto:
```protobuf
message Bar {
  optional string nickname = 1 [default = "undefined-nickname"];
}

message Foo {
  optional string name = 1 [default="unnamed"];
  required Bar bar = 2;
}

```
This project enables you manipulating naive c++ object by python code
```python
import demo
foo = demo.Foo()
print("---------[ default value ]--------")
print("foo.name():", foo.name())
print("foo.bar().nickname():", foo.bar().nickname())
print("---------[ set value ]--------")
foo.set_name("Jonathan")
foo.mutable_bar().set_nickname("Jonty")
print("foo.name():", foo.name())
print("foo.bar().nickname():", foo.bar().nickname())
```
### Try
```bash
  sh demo.sh
```
