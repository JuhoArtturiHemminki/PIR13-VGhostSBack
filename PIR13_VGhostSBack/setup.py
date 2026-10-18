from setuptools import setup, Extension
import sys
import os

os.environ["ARCHFLAGS"] = "-arch arm64"
os.environ["MACOSX_DEPLOYMENT_TARGET"] = "11.0"

extra_compile_args = ["-O3", "-flto", "-ffast-math", "-std=c++17", "-faligned-allocation"]

if sys.platform == "darwin":
    extra_compile_args.append("-stdlib=libc++")

module = Extension(
    "pir13_vghost",
    sources=["src/pir13_core.cpp", "src/pir13_python.cpp"],
    include_dirs=["include"],
    extra_compile_args=extra_compile_args,
    extra_link_args=["-flto", "-arch", "arm64"]
)

setup(
    name="pir13_vghost",
    version="1.0",
    ext_modules=[module]
)
