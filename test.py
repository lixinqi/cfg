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
foo.mutable_bars().Add().set_nickname("nice nickname")
foo.mutable_bars().Add().set_nickname("good nickname")
print([x.nickname() for x in foo.bars()])
print([x.nickname() for x in foo.Move().bars()])
print([x.nickname() for x in foo.bars()])

m = foo.mutable_map_int_int()

print(foo.map_int_int_size())

m[1]=1
m[2]=5

print(foo.map_int_int_size())
print(dict(m))
