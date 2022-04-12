from setuptools import setup, Extension

cpp_base = Extension('tree.cpp._base',
                     sources=["tree/cpp/src/core/core.cpp",
                              "tree/cpp/src/main.cpp"])

c_base = Extension('tree.c._base',
                   sources=["tree/c/src/core/core.c",
                            "tree/c/src/main.c"])

setup(name="tree",
      version="0.1",
      packages=["tree",
                "tree.cpp",
                "tree.c",
                "tree.native",
                "tree.native._core"],
      ext_modules=[cpp_base, c_base])
