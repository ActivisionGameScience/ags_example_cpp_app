Introduction
============

This repo is part of the tutorial found in
https://github.com/ActivisionGameScience/ags_conda_recipes.git

It contains two C++ executables, ``ags_blosc_compress`` and
``ags_blosc_decompress``, that link against the ``ags_blosc_wrapper`` library
found in the repo https://github.com/ActivisionGameScience/ags_example_cpp_lib.git.

The purpose is to demonstrate:

- How to manage both in-house and third-party dependencies using ``conda``,
  and build using ``cmake``


How to build
============

The ``conda`` build recipe is located in 
https://github.com/ActivisionGameScience/ags_conda_recipes.git.
You can use it to build, publish, and install 
the ``conda`` way.

However, you can also build and install this library by hand.
Assume that ``ags_example_cpp_lib`` is installed in the following location::

    /some/path/include/activision_game_science/*.h
    /some/path/lib/libags_blosc_wrapper.so

Assume that ``boost`` and ``c-blosc`` are similarly installed in ``/some/path``.
Then you can build and install with the following commands::

    git clone https://github.com/ActivisionGameScience/ags_example_cpp_app.git
    cd ags_example_cpp_app
    mkdir build
    cd build
    cmake -G "Unix Makefiles" ../ -DBOOST_ROOT=/some/path -DAGS_EXAMPLE_CPP_LIB_ROOT=/some/path -DCMAKE_INSTALL_PREFIX=/some/path
    make
    make install

You will now have the following files installed::

    /some/path/bin/ags_blosc_compress
    /some/path/bin/ags_blosc_decompress


License
=======

All files are licensed under the BSD 3-Clause License as follows:
 
| Copyright (c) 2015, Activision Publishing, Inc.  
| All rights reserved.
| 
| Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
| 
| 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
|  
| 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
|  
| 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
|  
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

