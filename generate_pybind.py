import render
import demo_pb2 as demo

print(render.JinjaRender(demo, "template.pybind.cpp", python_module_name='demo'))
