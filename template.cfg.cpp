#include "{{ util.module_cfg_header_name(module) }}"

{% for package in util.module_package_list(module) %}
namespace {{ package }} {
{% endfor %}
namespace cfg {

{% for enm in util.module_enum_types(module) %}
std::string {{ util.enum_name(enm) }}_Name({{ util.enum_name(enm) }} value) {
  switch (value) {
{% for value in util.enum_values(enm) %}
  case {{ util.enum_value_name(value) }}: { return "{{ util.enum_value_name(value) }}"; }
{% endfor %}
  default:
    return "";
  }
}
{% endfor %}

{% for cls in util.module_message_types(module) %}
{{ cls.name }}::{{ cls.name }}() { Clear(); }

{{ cls.name }}::{{ cls.name }}(const Const{{ cls.name }}& other) { CopyFrom(other); }

void {{ cls.name }}::Clear() {
{% for field in util.message_type_fields(cls) %}
{% if util.field_has_required_or_optional_label(field) %}
  clear_{{ util.field_name(field) }}();
{% elif util.field_has_repeated_label(field) %}
  clear_{{ util.field_name(field) }}();
{% endif %}
{% endfor %}
}

void {{ cls.name }}::CopyFrom(const Const{{ cls.name }}& other) {
{% for field in util.message_type_fields(cls) %}
{% if util.field_in_oneof(field) %}
{% elif util.field_has_repeated_label(field) %}
  mutable_{{ util.field_name(field) }}()->CopyFrom(other.{{ util.field_name(field) }}());
{% elif util.field_has_required_or_optional_label(field) %}
  if (other.has_{{ util.field_name(field) }}()) {
{% if util.field_is_message_type(field) %}
    mutable_{{ util.field_name(field) }}()->CopyFrom(other.{{ util.field_name(field) }}());
{% else %}
    set_{{ util.field_name(field) }}(other.{{ util.field_name(field) }}());
{% endif %}
  } else {
    clear_{{ util.field_name(field) }}();
  }
{% endif %}
{% endfor %}
}

void {{ cls.name }}::CopyFrom(const std::shared_ptr<Const{{ cls.name }}>& other) { CopyFrom(*other); }

void {{ cls.name }}::CopyFrom(const std::shared_ptr<{{ cls.name }}>& other) { CopyFrom(*other); }

{% for field in util.message_type_fields(cls) %}
{% if util.field_has_required_or_optional_label(field) %}
{% if util.field_is_message_type(field) %}
void {{ cls.name }}::clear_{{ util.field_name(field) }}() {
  {{ util.field_name(field) }}_.reset();
}

bool Const{{ cls.name }}::has_{{ util.field_name(field) }}() const {
  return static_cast<bool>({{ util.field_name(field) }}_);
}

const {{ util.field_message_type_name(field) }}& Const{{ cls.name }}::{{ util.field_name(field) }}() const {
  return *_shared_{{ util.field_name(field) }}();
}
{{ util.field_message_type_name(field) }}* {{ cls.name }}::mutable_{{ util.field_name(field) }}() {
  return shared_mutable_{{ util.field_name(field) }}().get();
}

std::shared_ptr<Const{{ util.field_message_type_name(field) }}> Const{{ cls.name }}::shared_const_{{ util.field_name(field) }}() const {
  return std::dynamic_pointer_cast<Const{{ util.field_message_type_name(field) }}>(_shared_{{ util.field_name(field) }}());
}

const std::shared_ptr<{{ util.field_message_type_name(field) }}>& Const{{ cls.name }}::_shared_{{ util.field_name(field) }}() const {
  if ({{ util.field_name(field) }}_) { return {{ util.field_name(field) }}_; }
  static const std::shared_ptr<{{ util.field_message_type_name(field) }}> __default_ptr__(new {{ util.field_message_type_name(field) }}());
  return __default_ptr__;
}

const std::shared_ptr<{{ util.field_message_type_name(field) }}>& {{ cls.name }}::shared_mutable_{{ util.field_name(field) }}() {
  if (!{{ util.field_name(field) }}_) {
    {{ util.field_name(field) }}_.reset(new {{ util.field_message_type_name(field) }}());
  }
  return {{ util.field_name(field) }}_;
}
{% else %}
void {{ cls.name }}::clear_{{ util.field_name(field) }}() {
  has_{{ util.field_name(field) }}_ = false;
}

bool Const{{ cls.name }}::has_{{ util.field_name(field) }}() const {
  return has_{{ util.field_name(field) }}_;
}

const {{ util.field_scalar_type_name(field) }}& Const{{ cls.name }}::{{ util.field_name(field) }}() const {
  if (has_{{ util.field_name(field) }}_) { return {{ util.field_name(field) }}_; }
{% if util.field_has_default_value(field) %}
  static const {{ util.field_scalar_type_name(field) }} default_static_value =
    {{ util.field_default_value_literal(field) }};
{% else %}
  static const {{ util.field_scalar_type_name(field) }} default_static_value = {{ util.field_scalar_type_name(field) }}();
{% endif %}
  return default_static_value;
}

void {{ cls.name }}::set_{{ util.field_name(field) }}(const {{ util.field_scalar_type_name(field) }}& value) {
  {{ util.field_name(field) }}_ = value;
  has_{{ util.field_name(field) }}_ = true;
}
{% endif %}

{% elif util.field_has_repeated_label(field) %}
std::size_t Const{{ cls.name }}::{{ util.field_name(field) }}_size() const {
  return {{ util.field_name(field) }}_->size();
}
void {{ cls.name }}::clear_{{ util.field_name(field) }}() {
  mutable_{{ util.field_name(field) }}()->Clear();
}
{% if util.field_is_message_type(field) %}
void Const{{ cls.name }}::{{ util.field_repeated_composite_container_name(field) }}::Clear() {
  clear();
}
void Const{{ cls.name }}::{{ util.field_repeated_composite_container_name(field) }}::CopyFrom(const Const{{ cls.name }}::Const{{ util.field_repeated_composite_container_name(field) }}& other) {
  clear();
  for (std::size_t i = 0; i < other.size(); ++i) {
    push_back(std::make_shared<{{ util.field_message_type_name(field) }}>(*other.at(i)));
  }
}
void Const{{ cls.name }}::{{ util.field_repeated_composite_container_name(field) }}::CopyFrom(const std::shared_ptr<Const{{ cls.name }}::Const{{ util.field_repeated_composite_container_name(field) }}>& other) {
  CopyFrom(*other);
}
void Const{{ cls.name }}::{{ util.field_repeated_composite_container_name(field) }}::CopyFrom(const std::shared_ptr<Const{{ cls.name }}::{{ util.field_repeated_composite_container_name(field) }}>& other) {
  CopyFrom(*other);
}
{{ util.field_message_type_name(field) }}* Const{{ cls.name }}::{{ util.field_repeated_composite_container_name(field) }}::Add() {
  push_back(std::make_shared<{{ util.field_message_type_name(field) }}>());
  return back().get();
}
const Const{{ cls.name }}::Const{{ util.field_repeated_composite_container_name(field) }}& Const{{ cls.name }}::{{ util.field_name(field) }}() const {
  return *{{ util.field_name(field) }}_;
}
const {{ util.field_message_type_name(field) }}& Const{{ cls.name }}::{{ util.field_name(field) }}(int64_t index) const {
  return *{{ util.field_name(field) }}_->at(index);
}
Const{{ cls.name }}::{{ util.field_repeated_composite_container_name(field) }}* {{ cls.name }}::mutable_{{ util.field_name(field) }}() {
  return shared_mutable_{{ util.field_name(field) }}().get();
}
{{ util.field_message_type_name(field) }}* {{ cls.name }}::mutable_{{ util.field_name(field) }}(int64_t index) {
  return shared_mutable_{{ util.field_name(field) }}(index).get();
}
std::shared_ptr<Const{{ cls.name }}::Const{{ util.field_repeated_composite_container_name(field) }}> Const{{ cls.name }}::shared_const_{{ util.field_name(field) }}() const {
  return std::dynamic_pointer_cast<Const{{ util.field_repeated_composite_container_name(field) }}>({{ util.field_name(field) }}_);
}
std::shared_ptr<Const{{ util.field_message_type_name(field) }}> Const{{ cls.name }}::shared_const_{{ util.field_name(field) }}(int64_t index) const {
  return std::dynamic_pointer_cast<Const{{ util.field_message_type_name(field) }}>({{ util.field_name(field) }}_->at(index));
}
const std::shared_ptr<Const{{ cls.name }}::{{ util.field_repeated_composite_container_name(field) }}>& {{ cls.name }}::shared_mutable_{{ util.field_name(field) }}() {
  if (!{{ util.field_name(field) }}_) {
    {{ util.field_name(field) }}_.reset(new {{ util.field_repeated_composite_container_name(field) }}());
  }
  return {{ util.field_name(field) }}_;
}
std::shared_ptr<{{ util.field_message_type_name(field) }}> {{ cls.name }}::shared_mutable_{{ util.field_name(field) }}(int64_t index) {
  return shared_mutable_{{ util.field_name(field) }}()->at(index);
}
{% else %}
void Const{{ cls.name }}::{{ util.field_repeated_scalar_container_name(field) }}::Clear() {
  clear();
}
void Const{{ cls.name }}::{{ util.field_repeated_scalar_container_name(field) }}::CopyFrom(const Const{{ cls.name }}::Const{{ util.field_repeated_scalar_container_name(field) }}& other) {
  this->assign(other.begin(), other.end());
}
void Const{{ cls.name }}::{{ util.field_repeated_scalar_container_name(field) }}::CopyFrom(const std::shared_ptr<Const{{ cls.name }}::Const{{ util.field_repeated_scalar_container_name(field) }}>& other) {
  CopyFrom(*other);
}
void Const{{ cls.name }}::{{ util.field_repeated_scalar_container_name(field) }}::CopyFrom(const std::shared_ptr<Const{{ cls.name }}::{{ util.field_repeated_scalar_container_name(field) }}>& other) {
  CopyFrom(*other);
}
const Const{{ cls.name }}::Const{{ util.field_repeated_scalar_container_name(field) }}& Const{{ cls.name }}::{{ util.field_name(field) }}() const {
  return *{{ util.field_name(field) }}_;
}
const {{ util.field_scalar_type_name(field) }}& Const{{ cls.name }}::{{ util.field_name(field) }}(int64_t index) const {
  return {{ util.field_name(field) }}_->at(index);
}
Const{{ cls.name }}::{{ util.field_repeated_scalar_container_name(field) }}* {{ cls.name }}::mutable_{{ util.field_name(field) }}() {
  return shared_mutable_{{ util.field_name(field) }}().get();
}
{{ util.field_scalar_type_name(field) }}* {{ cls.name }}::mutable_{{ util.field_name(field) }}(int64_t index) {
  return &shared_mutable_{{ util.field_name(field) }}()->at(index);
}
void {{ cls.name }}::add_{{ util.field_name(field) }}(const {{ util.field_scalar_type_name(field) }}& value) {
  return mutable_{{ util.field_name(field) }}()->push_back(value);
}
std::shared_ptr<Const{{ cls.name }}::Const{{ util.field_repeated_scalar_container_name(field) }}> Const{{ cls.name }}::shared_const_{{ util.field_name(field) }}() const {
  return std::dynamic_pointer_cast<Const{{ util.field_repeated_scalar_container_name(field) }}>({{ util.field_name(field) }}_);
}
const std::shared_ptr<Const{{ cls.name }}::{{ util.field_repeated_scalar_container_name(field) }}>& {{ cls.name }}::shared_mutable_{{ util.field_name(field) }}() {
  if (!{{ util.field_name(field) }}_) {
    {{ util.field_name(field) }}_.reset(new {{ util.field_repeated_scalar_container_name(field) }}());
  }
  return {{ util.field_name(field) }}_;
}
{% endif %}
{% endif %} {# label #}
{% endfor %}{# fields #}

{% endfor %}{# cls #}
}
{% for package in util.module_package_list(module) %}
}
{% endfor %}
