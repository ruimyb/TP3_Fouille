cmake_minimum_required(VERSION 3.3)
project(TP3_Fouille)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES
    headers/Bernouilli.h
    headers/multinomial.h
    headers/parseur.h
    headers/testSet.h
    headers/trainingSet.h
    src/Bernouilli.c
    src/main.c
    src/multinomial.c
    src/parseur.c
    src/testSet.c
    src/trainingSet.c)

add_executable(TP3_Fouille ${SOURCE_FILES})