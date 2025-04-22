# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/pseudush/FUNDAMENTAL_ALGHORITMS_4_SEM/Fundamental-Algorithms-4th-Semester/lab1/task2/biuld/_deps/googletest-src"
  "/home/pseudush/FUNDAMENTAL_ALGHORITMS_4_SEM/Fundamental-Algorithms-4th-Semester/lab1/task2/biuld/_deps/googletest-build"
  "/home/pseudush/FUNDAMENTAL_ALGHORITMS_4_SEM/Fundamental-Algorithms-4th-Semester/lab1/task2/biuld/_deps/googletest-subbuild/googletest-populate-prefix"
  "/home/pseudush/FUNDAMENTAL_ALGHORITMS_4_SEM/Fundamental-Algorithms-4th-Semester/lab1/task2/biuld/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/home/pseudush/FUNDAMENTAL_ALGHORITMS_4_SEM/Fundamental-Algorithms-4th-Semester/lab1/task2/biuld/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/home/pseudush/FUNDAMENTAL_ALGHORITMS_4_SEM/Fundamental-Algorithms-4th-Semester/lab1/task2/biuld/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/home/pseudush/FUNDAMENTAL_ALGHORITMS_4_SEM/Fundamental-Algorithms-4th-Semester/lab1/task2/biuld/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/pseudush/FUNDAMENTAL_ALGHORITMS_4_SEM/Fundamental-Algorithms-4th-Semester/lab1/task2/biuld/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/pseudush/FUNDAMENTAL_ALGHORITMS_4_SEM/Fundamental-Algorithms-4th-Semester/lab1/task2/biuld/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
