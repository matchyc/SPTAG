# This file was automatically generated by SWIG (http://www.swig.org).
# Version 4.0.1
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info < (2, 7, 0):
    raise RuntimeError("Python 2.7 or later required")

# Import the low-level C/C++ module
if __package__ or "." in __name__:
    from . import _SPTAG
else:
    import _SPTAG

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "thisown":
            self.this.own(value)
        elif name == "this":
            set(self, name, value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name), property):
            set(self, name, value)
        else:
            raise AttributeError("You cannot add instance attributes to %s" % self)
    return set_instance_attr


def _swig_setattr_nondynamic_class_variable(set):
    def set_class_attr(cls, name, value):
        if hasattr(cls, name) and not isinstance(getattr(cls, name), property):
            set(cls, name, value)
        else:
            raise AttributeError("You cannot add class attributes to %s" % cls)
    return set_class_attr


def _swig_add_metaclass(metaclass):
    """Class decorator for adding a metaclass to a SWIG wrapped class - a slimmed down version of six.add_metaclass"""
    def wrapper(cls):
        return metaclass(cls.__name__, cls.__bases__, cls.__dict__.copy())
    return wrapper


class _SwigNonDynamicMeta(type):
    """Meta class to enforce nondynamic attributes (no new attributes) for a class"""
    __setattr__ = _swig_setattr_nondynamic_class_variable(type.__setattr__)


SHARED_PTR_DISOWN = _SPTAG.SHARED_PTR_DISOWN
class AnnIndex(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def __init__(self, *args):
        _SPTAG.AnnIndex_swiginit(self, _SPTAG.new_AnnIndex(*args))
    __swig_destroy__ = _SPTAG.delete_AnnIndex

    def SetBuildParam(self, p_name, p_value, p_section):
        return _SPTAG.AnnIndex_SetBuildParam(self, p_name, p_value, p_section)

    def SetSearchParam(self, p_name, p_value, p_section):
        return _SPTAG.AnnIndex_SetSearchParam(self, p_name, p_value, p_section)

    def LoadQuantizer(self, p_quantizerFile):
        return _SPTAG.AnnIndex_LoadQuantizer(self, p_quantizerFile)

    def SetQuantizerADC(self, p_adc):
        return _SPTAG.AnnIndex_SetQuantizerADC(self, p_adc)

    def BuildSPANN(self, p_normalized):
        return _SPTAG.AnnIndex_BuildSPANN(self, p_normalized)

    def BuildSPANNWithMetaData(self, p_meta, p_num, p_withMetaIndex, p_normalized):
        return _SPTAG.AnnIndex_BuildSPANNWithMetaData(self, p_meta, p_num, p_withMetaIndex, p_normalized)

    def Build(self, p_data, p_num, p_normalized):
        return _SPTAG.AnnIndex_Build(self, p_data, p_num, p_normalized)

    def BuildWithMetaData(self, p_data, p_meta, p_num, p_withMetaIndex, p_normalized):
        return _SPTAG.AnnIndex_BuildWithMetaData(self, p_data, p_meta, p_num, p_withMetaIndex, p_normalized)

    def Search(self, p_data, p_resultNum):
        return _SPTAG.AnnIndex_Search(self, p_data, p_resultNum)

    def SearchWithMetaData(self, p_data, p_resultNum):
        return _SPTAG.AnnIndex_SearchWithMetaData(self, p_data, p_resultNum)

    def BatchSearch(self, p_data, p_vectorNum, p_resultNum, p_withMetaData):
        return _SPTAG.AnnIndex_BatchSearch(self, p_data, p_vectorNum, p_resultNum, p_withMetaData)

    def ReadyToServe(self):
        return _SPTAG.AnnIndex_ReadyToServe(self)

    def UpdateIndex(self):
        return _SPTAG.AnnIndex_UpdateIndex(self)

    def Save(self, p_saveFile):
        return _SPTAG.AnnIndex_Save(self, p_saveFile)

    def Add(self, p_data, p_num, p_normalized):
        return _SPTAG.AnnIndex_Add(self, p_data, p_num, p_normalized)

    def AddWithMetaData(self, p_data, p_meta, p_num, p_withMetaIndex, p_normalized):
        return _SPTAG.AnnIndex_AddWithMetaData(self, p_data, p_meta, p_num, p_withMetaIndex, p_normalized)

    def Delete(self, p_data, p_num):
        return _SPTAG.AnnIndex_Delete(self, p_data, p_num)

    def DeleteByMetaData(self, p_meta):
        return _SPTAG.AnnIndex_DeleteByMetaData(self, p_meta)

    @staticmethod
    def Load(p_loaderFile):
        return _SPTAG.AnnIndex_Load(p_loaderFile)

    @staticmethod
    def Merge(p_indexFilePath1, p_indexFilePath2):
        return _SPTAG.AnnIndex_Merge(p_indexFilePath1, p_indexFilePath2)

# Register AnnIndex in _SPTAG:
_SPTAG.AnnIndex_swigregister(AnnIndex)

def AnnIndex_Load(p_loaderFile):
    return _SPTAG.AnnIndex_Load(p_loaderFile)

def AnnIndex_Merge(p_indexFilePath1, p_indexFilePath2):
    return _SPTAG.AnnIndex_Merge(p_indexFilePath1, p_indexFilePath2)



