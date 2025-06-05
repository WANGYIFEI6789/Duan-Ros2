# generated from rosidl_generator_py/resource/_idl.py.em
# with input from status_interfaces:msg/SystemStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SystemStatus(type):
    """Metaclass of message 'SystemStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('status_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'status_interfaces.msg.SystemStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__system_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__system_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__system_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__system_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__system_status

            from builtin_interfaces.msg import Time
            if Time.__class__._TYPE_SUPPORT is None:
                Time.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SystemStatus(metaclass=Metaclass_SystemStatus):
    """Message class 'SystemStatus'."""

    __slots__ = [
        '_stamp',
        '_host_name',
        '_cpu_percent',
        '_memory_percent',
        '_memory_total',
        '_memory_available',
        '_net_sent',
        '_net_recv',
    ]

    _fields_and_field_types = {
        'stamp': 'builtin_interfaces/Time',
        'host_name': 'string',
        'cpu_percent': 'float',
        'memory_percent': 'float',
        'memory_total': 'float',
        'memory_available': 'float',
        'net_sent': 'double',
        'net_recv': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['builtin_interfaces', 'msg'], 'Time'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from builtin_interfaces.msg import Time
        self.stamp = kwargs.get('stamp', Time())
        self.host_name = kwargs.get('host_name', str())
        self.cpu_percent = kwargs.get('cpu_percent', float())
        self.memory_percent = kwargs.get('memory_percent', float())
        self.memory_total = kwargs.get('memory_total', float())
        self.memory_available = kwargs.get('memory_available', float())
        self.net_sent = kwargs.get('net_sent', float())
        self.net_recv = kwargs.get('net_recv', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.stamp != other.stamp:
            return False
        if self.host_name != other.host_name:
            return False
        if self.cpu_percent != other.cpu_percent:
            return False
        if self.memory_percent != other.memory_percent:
            return False
        if self.memory_total != other.memory_total:
            return False
        if self.memory_available != other.memory_available:
            return False
        if self.net_sent != other.net_sent:
            return False
        if self.net_recv != other.net_recv:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def stamp(self):
        """Message field 'stamp'."""
        return self._stamp

    @stamp.setter
    def stamp(self, value):
        if __debug__:
            from builtin_interfaces.msg import Time
            assert \
                isinstance(value, Time), \
                "The 'stamp' field must be a sub message of type 'Time'"
        self._stamp = value

    @builtins.property
    def host_name(self):
        """Message field 'host_name'."""
        return self._host_name

    @host_name.setter
    def host_name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'host_name' field must be of type 'str'"
        self._host_name = value

    @builtins.property
    def cpu_percent(self):
        """Message field 'cpu_percent'."""
        return self._cpu_percent

    @cpu_percent.setter
    def cpu_percent(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'cpu_percent' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'cpu_percent' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._cpu_percent = value

    @builtins.property
    def memory_percent(self):
        """Message field 'memory_percent'."""
        return self._memory_percent

    @memory_percent.setter
    def memory_percent(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'memory_percent' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'memory_percent' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._memory_percent = value

    @builtins.property
    def memory_total(self):
        """Message field 'memory_total'."""
        return self._memory_total

    @memory_total.setter
    def memory_total(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'memory_total' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'memory_total' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._memory_total = value

    @builtins.property
    def memory_available(self):
        """Message field 'memory_available'."""
        return self._memory_available

    @memory_available.setter
    def memory_available(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'memory_available' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'memory_available' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._memory_available = value

    @builtins.property
    def net_sent(self):
        """Message field 'net_sent'."""
        return self._net_sent

    @net_sent.setter
    def net_sent(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'net_sent' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'net_sent' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._net_sent = value

    @builtins.property
    def net_recv(self):
        """Message field 'net_recv'."""
        return self._net_recv

    @net_recv.setter
    def net_recv(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'net_recv' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'net_recv' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._net_recv = value
