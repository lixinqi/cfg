import render
import demo_pb2 as demo

print(render.JinjaRender(demo, "template.hpp"))
