#include <memory>
#include <vector>

namespace oneflow {
namespace cfg {

{% for enm in util.module_enum_types(module) %}
enum {{ util.enum_name(enm) }} {
{% for value in util.enum_values(enm) %}
  {{ util.enum_value_name(value) }} = {{ util.enum_value_number(value) }},
{% endfor %}
};

{% endfor %}

{% for cls in util.module_message_types(module) %}
class {{ cls.name }} {
{% for field in util.message_type_fields(cls) %}

{% if util.field_has_required_label(field) %}
  // required field {{ util.field_name(field) }}
{% if util.field_is_message_type(field) %}
 public:
  const {{ util.field_message_type_name(field) }}& {{ util.field_name(field) }}() const;
  {{ util.field_message_type_name(field) }}* mutable_{{ util.field_name(field) }}();
  std::shared_ptr<{{ util.field_message_type_name(field) }}> shared_ptr_{{ util.field_name(field) }}();
 private:
  std::shared_ptr<{{ util.field_message_type_name(field) }}> {{ util.field_name(field) }}_;
{% else %}
 public:
  const {{ util.field_scalar_type_name(field) }}& {{ util.field_name(field) }}() const;
  void set_{{ util.field_name(field) }}(const {{ util.field_scalar_type_name(field) }}& value);
 private:
  {{ util.field_scalar_type_name(field) }} {{ util.field_name(field) }}_;
{% endif %}
{% elif util.field_has_optional_label(field) %}
  // optional field {{ util.field_name(field) }}
 public:
  bool has_{{ util.field_name(field) }}() const;
  void clear_{{ util.field_name(field) }}();
{% if util.field_is_message_type(field) %}
  const {{ util.field_message_type_name(field) }}& {{ util.field_name(field) }}() const;
  {{ util.field_message_type_name(field) }}* mutable_{{ util.field_name(field) }}();
  std::shared_ptr<{{ util.field_message_type_name(field) }}> shared_ptr_{{ util.field_name(field) }}();
 private:
  std::shared_ptr<{{ util.field_message_type_name(field) }}> {{ util.field_name(field) }}_;
{% else %}
  const {{ util.field_scalar_type_name(field) }}& {{ util.field_name(field) }}() const;
  void set_{{ util.field_name(field) }}(const {{ util.field_scalar_type_name(field) }}& value);
 private:
  {{ util.field_scalar_type_name(field) }} {{ util.field_name(field) }}_;
{% endif %}
{% elif util.field_is_repeated(field) %}
  // repeated field {{ util.field_name(field) }}
 public:
  std::size_t {{ util.field_name(field) }}_size() const;
  void clear_{{ util.field_name(field) }}();
{% if util.field_is_message_type(field) %}
  const std::vector<std::shared_ptr<{{ util.field_message_type_name(field) }}>>& {{ util.field_name(field) }}() const;
  std::vector<std::shared_ptr<{{ util.field_message_type_name(field) }}>>* mutable_{{ util.field_name(field) }}();
  std::shared_ptr<std::vector<std::shared_ptr<{{ util.field_message_type_name(field) }}>>> shared_ptr_{{ util.field_name(field) }}();
 private:
  std::shared_ptr<std::vector<std::shared_ptr<{{ util.field_message_type_name(field) }}>>> {{ util.field_name(field) }}_;
{% else %}
  const std::vector<{{ util.field_scalar_type_name(field) }}>>& {{ util.field_name(field) }}() const;
  std::vector<{{ util.field_scalar_type_name(field) }}>* mutable_{{ util.field_name(field) }}();
  std::shared_ptr<std::vector<{{ util.field_scalar_type_name(field) }}>> shared_ptr_{{ util.field_name(field) }}();
 private:
  std::shared_ptr<std::vector<{{ util.field_scalar_type_name(field) }}>> {{ util.field_name(field) }}_;
{% endif %}
{% endif %}
{% endfor %}{# field #}
};

{% endfor %}
}
}
