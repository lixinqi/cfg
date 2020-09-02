def module_enum_types(module):
    return module.DESCRIPTOR.enum_types_by_name.values()

def module_message_types(module):
    return module.DESCRIPTOR.message_types_by_name.values()

def enum_name(enum):
    return enum.name

def enum_values(enum):
    return enum.values

def enum_value_name(enum_value):
    return enum_value.name

def enum_value_number(enum_value):
    return enum_value.number

def message_type_fields(cls):
    return cls.fields

def field_has_required_label(field):
    return field.label == field.LABEL_REQUIRED

def field_has_optional_label(field):
    return field.label == field.LABEL_OPTIONAL and not field_in_oneof(field)

def field_is_repeated(field):
    return field.label == field.LABEL_REPEATED and not _field_is_map_entry(field)

def field_is_map(field):
    return field.label == field.LABEL_REPEATED and _field_is_map_entry(field)

def field_in_oneof(field):
    return field.containing_oneof is not None

def field_name(field):
    return field.name

def field_is_message_type(field):
    return field.message_type is not None

def field_message_type_name(field):
    return field.message_type.name

def field_is_enum_type(field):
    return field.enum_type is not None

def field_scalar_type_name(field):
    if field.cpp_type == field.CPPTYPE_BOOL:
        return "bool"
    if field.cpp_type == field.CPPTYPE_ENUM:
        return field.enum_type.name
    if field.cpp_type == field.CPPTYPE_DOUBLE:
        return "double"
    if field.cpp_type == field.CPPTYPE_FLOAT:
        return "float"
    if field.cpp_type == field.CPPTYPE_INT32:
        return "int32_t"
    if field.cpp_type == field.CPPTYPE_INT64:
        return "int64_t"
    if field.cpp_type == field.CPPTYPE_INT64:
        return "int64_t"
    if field.cpp_type == field.CPPTYPE_STRING:
        return "std::string"
    if field.cpp_type == field.CPPTYPE_UINT32:
        return "uint32_t"
    if field.cpp_type == field.CPPTYPE_UINT64:
        return "uint64_t"
    raise NotImplementedError("field.cpp_type is %s"%field.cpp_type)

def _field_is_map_entry(field):
    if field.message_type is None:
        return False
    capitalized_name = field.camelcase_name[0].capitalize() + field.camelcase_name[1:]
    entry_type_name = capitalized_name + "Entry"
    if field.message_type.name != entry_type_name:
        return False
    entry_fields = field.message_type.fields
    if len(entry_fields) != 2:
        return False
    if entry_fields[0].name != 'key':
        return False
    if entry_fields[1].name != 'value':
        return False
    return True