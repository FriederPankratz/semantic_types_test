#include "GenericType.h"

generic_type::GenericField::GenericField(int byte_offset, generic_type::DataType type,
                                         generic_type::ScalarType scalar_type) : byte_offset(byte_offset), type(type),
                                                                                 scalar_type(scalar_type) {}
