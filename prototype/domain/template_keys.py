class Key(object):

    def __init__(self, name, default=None):
        self.name = name
        self.default = default


class IntegerKey(Key):

    def __init__(self, name, default=None):
        super(IntegerKey, self).__init__(name, default)
        self.type = int


class StringKey(Key):

    def __init__(self, name, default=None):
        super(StringKey, self).__init__(name, default)
        self.type = str

class TimestampKey(Key):

    def __init__(self, name, default=None):
        super(TimestampKey, self).__init__(name, default)
