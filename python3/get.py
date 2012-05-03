class Descriptor(object):
    def __get__(self, obj, type=None):
        return 'get', self, obj, type
    def __set__(self, obj, val):
         print('set', self, obj, val )
    def __delete__(self, obj):
          print('delete', self, obj)

