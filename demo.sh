#!/bin/bash
protoc demo.proto --python_out=./
python3 generate_hpp.py > demo.cfg.h
python3 generate_cpp.py > demo.cfg.cpp
python3 generate_pybind.py > demo.pybind.cpp
g++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` demo.cfg.cpp demo.pybind.cpp -o demo`python3-config --extension-suffix`
python3 test.py
