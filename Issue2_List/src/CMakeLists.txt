# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.19.4)
# プロジェクト名と使用する言語を設定
project(main_cmake)
# main.exeという実行ファイルをmain.cppとhello.cppから作成
#add_executable(main.exe main.cpp)
# サブディレクトリを登録

#
#target_link_libraries()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../build/src/lib)