from jinja2 import Environment, FileSystemLoader
import proto_reflect_util
import os
THIS_DIR = os.path.dirname(os.path.abspath(__file__))

def JinjaRender(module, filename, **kwargs): 
    j2_env = Environment(loader=FileSystemLoader(THIS_DIR), trim_blocks=True)
    return j2_env.get_template(filename).render(
            module=module.DESCRIPTOR,
            util=proto_reflect_util,
            **kwargs)
