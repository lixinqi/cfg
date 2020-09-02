#include <pybind11/pybind11.h>
#include "{{ util.module_cfg_header_name(module) }}"

PYBIND11_MODULE({{ python_module_name }}, m) {
{% if util.module_has_package(module) %}
  using namespace {{ "::".join(util.module_package_list(module)) }};
{% endif %}
{% for cls in util.module_message_types(module) %}
  {
    pybind11::class_<cfg::Const{{ cls.name }}, std::shared_ptr<cfg::Const{{ cls.name }}>> registry(m, "Const{{ cls.name }}");
{% for field in util.message_type_fields(cls) %}

{% if util.field_has_required_or_optional_label(field) %}
    registry.def("has_{{ util.field_name(field) }}", &cfg::Const{{ cls.name }}::has_{{ util.field_name(field) }});
{% if util.field_is_message_type(field) %}
    registry.def("{{ util.field_name(field) }}", &cfg::Const{{ cls.name }}::shared_const_{{ util.field_name(field) }});
{% else %}
    registry.def("{{ util.field_name(field) }}", &cfg::Const{{ cls.name }}::{{ util.field_name(field) }});
{% endif %}
{% elif util.field_has_repeated_label(field) %}
    registry.def("{{ util.field_name(field) }}_size", &cfg::Const{{ cls.name }}::{{ util.field_name(field) }}_size);
{% if util.field_is_message_type(field) %}
    registry.def("{{ util.field_name(field) }}", (std::shared_ptr<cfg::Const{{ cls.name }}::Const{{ util.field_repeated_composite_container_name(field) }}> (cfg::Const{{ cls.name }}::*)() const)&cfg::Const{{ cls.name }}::shared_const_{{ util.field_name(field) }});
{% else %}
    registry.def("{{ util.field_name(field) }}", (std::shared_ptr<cfg::Const{{ cls.name }}::Const{{ util.field_repeated_scalar_container_name(field) }}> (cfg::Const{{ cls.name }}::*)() const)&cfg::Const{{ cls.name }}::shared_const_{{ util.field_name(field) }});
{% endif %}
{% endif %}
{% endfor %}{# field #}
  }
  {
    pybind11::class_<cfg::{{ cls.name }}, std::shared_ptr<cfg::{{ cls.name }}>> registry(m, "{{ cls.name }}");
    registry.def(pybind11::init<>());
    registry.def("Clear", &cfg::{{ cls.name }}::Clear);
{% for field in util.message_type_fields(cls) %}

{% if util.field_has_required_or_optional_label(field) %}
    registry.def("has_{{ util.field_name(field) }}", &cfg::{{ cls.name }}::has_{{ util.field_name(field) }});
    registry.def("clear_{{ util.field_name(field) }}", &cfg::{{ cls.name }}::clear_{{ util.field_name(field) }});
{% if util.field_is_message_type(field) %}
    registry.def("{{ util.field_name(field) }}", &cfg::{{ cls.name }}::shared_const_{{ util.field_name(field) }});
    registry.def("mutable_{{ util.field_name(field) }}", &cfg::{{ cls.name }}::shared_mutable_{{ util.field_name(field) }});
{% else %}
    registry.def("{{ util.field_name(field) }}", &cfg::{{ cls.name }}::{{ util.field_name(field) }});
    registry.def("set_{{ util.field_name(field) }}", &cfg::{{ cls.name }}::set_{{ util.field_name(field) }});
{% endif %}
{% elif util.field_has_repeated_label(field) %}
    registry.def("{{ util.field_name(field) }}_size", &cfg::{{ cls.name }}::{{ util.field_name(field) }}_size);
    registry.def("clear_{{ util.field_name(field) }}", &cfg::{{ cls.name }}::clear_{{ util.field_name(field) }});
{% if util.field_is_message_type(field) %}
    registry.def("{{ util.field_name(field) }}", (std::shared_ptr<cfg::{{ cls.name }}::Const{{ util.field_repeated_composite_container_name(field) }}> (cfg::{{ cls.name }}::*)() const)&cfg::{{ cls.name }}::shared_const_{{ util.field_name(field) }});
    registry.def("mutable_{{ util.field_name(field) }}", (const std::shared_ptr<cfg::{{ cls.name }}::{{ util.field_repeated_composite_container_name(field) }}>& (cfg::{{ cls.name }}::*)())&cfg::{{ cls.name }}::shared_mutable_{{ util.field_name(field) }});
{% else %}
    registry.def("{{ util.field_name(field) }}", (std::shared_ptr<cfg::{{ cls.name }}::Const{{ util.field_repeated_scalar_container_name(field) }}> (cfg::{{ cls.name }}::*)() const)&cfg::{{ cls.name }}::shared_const_{{ util.field_name(field) }});
    registry.def("mutable_{{ util.field_name(field) }}", (const std::shared_ptr<cfg::{{ cls.name }}::{{ util.field_repeated_scalar_container_name(field) }}>& (cfg::{{ cls.name }}::*)())&cfg::{{ cls.name }}::shared_mutable_{{ util.field_name(field) }});
    registry.def("add_{{ util.field_name(field) }}", &cfg::{{ cls.name }}::add_{{ util.field_name(field) }});
{% endif %}
{% endif %}
{% endfor %}{# field #}
  }
{% endfor %}{# cls #}
}
