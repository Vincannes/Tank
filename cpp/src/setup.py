from distutils.core import setup, Extension

# Description de l'extension et du code a compiler.
# Notez bien le nom de l'extension `_tuto` prefixe par le caractere `_`

tuto_module = Extension(
    "_tank",
    sources=["tank.cpp", "tank_wrap.cxx"],
)


setup(
    name="tank",
    version="0.1",
    author="trolardv",
    ext_modules=[tuto_module],
    py_modules=["tank"],
)