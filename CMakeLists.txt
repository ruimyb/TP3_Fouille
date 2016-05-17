cmake_minimum_required(VERSION 3.3)
project(TP3_Fouille)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c
    Readme.txt parseur.c parseur.h testSet.h testSet.c trainingSet.c trainingSet.h multinomial.c multinomial.h)

add_executable(TP3_Fouille ${SOURCE_FILES})