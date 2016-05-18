cmake_minimum_required(VERSION 3.3)
project(TP3_Fouille)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES
<<<<<<< HEAD
    main.c
    Readme.txt parseur.c parseur.h testSet.h testSet.c trainingSet.c trainingSet.h src/multinomial.c headers/multinomial.h)
=======
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
>>>>>>> 555d5e806120ffb8de64b7f0a46cfa695cb113f7

add_executable(TP3_Fouille ${SOURCE_FILES})