#ifndef {{ util.module_header_macro_lock(module) }}
#define {{ util.module_header_macro_lock(module) }}

#include <memory>
#include <vector>
{% for dependency in util.module_dependencies(module) %}
#include "{{ util.module_cfg_header_name(dependency) }}"
{% endfor %}

{% for package in util.module_package_list(module) %}
namespace {{ package }} {
{% endfor %}
namespace cfg {

{% for enm in util.module_enum_types(module) %}
enum {{ util.enum_name(enm) }} {
{% for value in util.enum_values(enm) %}
  {{ util.enum_value_name(value) }} = {{ util.enum_value_number(value) }},
{% endfor %}
};

std::string {{ util.enum_name(enm) }}_Name({{ util.enum_name(enm) }} value);

{% endfor %}

{% for cls in util.module_message_types(module) %}
class {{ cls.name }};
class Const{{ cls.name }} {
 public:
  Const{{ cls.name }}() = default;
  ~Const{{ cls.name }}() = default;
{% for field in util.message_type_fields(cls) %}

{% if util.field_has_required_or_optional_label(field) %}
  // optional field {{ util.field_name(field) }}
 public:
  bool has_{{ util.field_name(field) }}() const;
{% if util.field_is_message_type(field) %}
  const {{ util.field_message_type_name(field) }}& {{ util.field_name(field) }}() const;
  // used by pybind11 only
  std::shared_ptr<Const{{ util.field_message_type_name(field) }}> shared_const_{{ util.field_name(field) }}() const;
 protected:
  const std::shared_ptr<{{ util.field_message_type_name(field) }}>& _shared_{{ util.field_name(field) }}() const;
  std::shared_ptr<{{ util.field_message_type_name(field) }}> {{ util.field_name(field) }}_;
{% else %}
  const {{ util.field_scalar_type_name(field) }}& {{ util.field_name(field) }}() const;
 protected:
  {{ util.field_scalar_type_name(field) }} {{ util.field_name(field) }}_;
  bool has_{{ util.field_name(field) }}_;
{% endif %}
{% elif util.field_has_repeated_label(field) %}
  // repeated field {{ util.field_name(field) }}
{% if util.field_is_message_type(field) %}
 public:
  class {{ util.field_repeated_composite_container_name(field) }};
  class Const{{ util.field_repeated_composite_container_name(field) }} : public std::vector<std::shared_ptr<{{ util.field_message_type_name(field) }}>> {
   public:
    Const{{ util.field_repeated_composite_container_name(field) }}() = default;
    ~Const{{ util.field_repeated_composite_container_name(field) }}() = default;
  };
  class {{ util.field_repeated_composite_container_name(field) }} : public Const{{ util.field_repeated_composite_container_name(field) }} {
   public:
    {{ util.field_repeated_composite_container_name(field) }}() = default;
    ~{{ util.field_repeated_composite_container_name(field) }}() = default;
    void Clear();
    void CopyFrom(const Const{{ util.field_repeated_composite_container_name(field) }}& other);
    void CopyFrom(const std::shared_ptr<Const{{ util.field_repeated_composite_container_name(field) }}>& other);
    void CopyFrom(const std::shared_ptr<{{ util.field_repeated_composite_container_name(field) }}>& other);
    {{ util.field_message_type_name(field) }}* Add();
    // used by pybind11 only
    const std::shared_ptr<{{ util.field_message_type_name(field) }}>& SharedAdd();
  };
  std::size_t {{ util.field_name(field) }}_size() const;
  const Const{{ util.field_repeated_composite_container_name(field) }}& {{ util.field_name(field) }}() const;
  const {{ util.field_message_type_name(field) }}& {{ util.field_name(field) }}(int64_t index) const;
  // used by pybind11 only
  std::shared_ptr<Const{{ util.field_repeated_composite_container_name(field) }}> shared_const_{{ util.field_name(field) }}() const;
  std::shared_ptr<Const{{ util.field_message_type_name(field) }}> shared_const_{{ util.field_name(field) }}(int64_t index) const;
 protected:
  std::shared_ptr<{{ util.field_repeated_composite_container_name(field) }}> {{ util.field_name(field) }}_;
{% else %}
 public:
  class {{ util.field_repeated_scalar_container_name(field) }};
  class Const{{ util.field_repeated_scalar_container_name(field) }} : public std::vector<{{ util.field_scalar_type_name(field) }}> {
   public:
    Const{{ util.field_repeated_scalar_container_name(field) }}() = default;
    ~Const{{ util.field_repeated_scalar_container_name(field) }}() = default;
  };
  class {{ util.field_repeated_scalar_container_name(field) }} : public Const{{ util.field_repeated_scalar_container_name(field) }} {
   public:
    {{ util.field_repeated_scalar_container_name(field) }}() = default;
    ~{{ util.field_repeated_scalar_container_name(field) }}() = default;
    void Clear();
    void CopyFrom(const Const{{ util.field_repeated_scalar_container_name(field) }}& other);
    void CopyFrom(const std::shared_ptr<Const{{ util.field_repeated_scalar_container_name(field) }}>& other);
    void CopyFrom(const std::shared_ptr<{{ util.field_repeated_scalar_container_name(field) }}>& other);
  };
  std::size_t {{ util.field_name(field) }}_size() const;
  const Const{{ util.field_repeated_scalar_container_name(field) }}& {{ util.field_name(field) }}() const;
  const {{ util.field_scalar_type_name(field) }}& {{ util.field_name(field) }}(int64_t index) const;
  // used by pybind11 only
  std::shared_ptr<Const{{ util.field_repeated_scalar_container_name(field) }}> shared_const_{{ util.field_name(field) }}() const;
 protected:
  std::shared_ptr<{{ util.field_repeated_scalar_container_name(field) }}> {{ util.field_name(field) }}_;
{% endif %}
{% endif %}
{% endfor %}{# field #}
};
class {{ cls.name }} : public Const{{ cls.name }} {
 public:
  {{ cls.name }}();
  explicit {{ cls.name }}(const Const{{ cls.name }}&); 
  ~{{ cls.name }}() = default;
  void Clear();
  void CopyFrom(const Const{{ cls.name }}& other);
  void CopyFrom(const std::shared_ptr<Const{{ cls.name }}>& other);
  void CopyFrom(const std::shared_ptr<{{ cls.name }}>& other);
{% for field in util.message_type_fields(cls) %}

{% if util.field_has_required_or_optional_label(field) %}
  // optional field {{ util.field_name(field) }}
 public:
  void clear_{{ util.field_name(field) }}();
{% if util.field_is_message_type(field) %}
  {{ util.field_message_type_name(field) }}* mutable_{{ util.field_name(field) }}();
  // used by pybind11 only
  const std::shared_ptr<{{ util.field_message_type_name(field) }}>& shared_mutable_{{ util.field_name(field) }}();
{% else %}
  void set_{{ util.field_name(field) }}(const {{ util.field_scalar_type_name(field) }}& value);
{% endif %}
{% elif util.field_has_repeated_label(field) %}
  // repeated field {{ util.field_name(field) }}
{% if util.field_is_message_type(field) %}
 public:
  void clear_{{ util.field_name(field) }}();
  {{ util.field_repeated_composite_container_name(field) }}* mutable_{{ util.field_name(field) }}();
  {{ util.field_message_type_name(field) }}* mutable_{{ util.field_name(field) }}(int64_t index);
  // used by pybind11 only
  const std::shared_ptr<{{ util.field_repeated_composite_container_name(field) }}>& shared_mutable_{{ util.field_name(field) }}();
  std::shared_ptr<{{ util.field_message_type_name(field) }}> shared_mutable_{{ util.field_name(field) }}(int64_t index);
{% else %}
 public:
  void clear_{{ util.field_name(field) }}();
  {{ util.field_repeated_scalar_container_name(field) }}* mutable_{{ util.field_name(field) }}();
  {{ util.field_scalar_type_name(field) }}* mutable_{{ util.field_name(field) }}(int64_t index);
  void add_{{ util.field_name(field) }}(const {{ util.field_scalar_type_name(field) }}& value);
  // used by pybind11 only
  const std::shared_ptr<{{ util.field_repeated_scalar_container_name(field) }}>& shared_mutable_{{ util.field_name(field) }}();
{% endif %}
{% endif %}
{% endfor %}{# field #}
};

{% endfor %}
}
{% for package in util.module_package_list(module) %}
}
{% endfor %}
#endif  // {{ util.module_header_macro_lock(module) }}
