from distutils.core import setup, Extension

# Description de l'extension et du code a compiler.
# Notez bien le nom de l'extension `_tuto` prefixe par le caractere `_`

tuto_module = Extension(
    "_tuto",
    sources=["tank_obj.cpp", "binder_wrap.cxx"],
)


setup(
    name="tuto",
    version="0.1",
    author="Laurette Alexandre",
    ext_modules=[tuto_module],
    py_modules=["tuto"],
)