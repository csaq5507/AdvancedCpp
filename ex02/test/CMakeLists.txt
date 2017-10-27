file(GLOB_RECURSE ALL_TEST_CPP *.cpp)

foreach(ONE_TEST_CPP ${ALL_TEST_CPP})

    get_filename_component(ONE_TEST_EXEC ${ONE_TEST_CPP} NAME_WE)

    set(TARGET_NAME Test_${ONE_TEST_EXEC})

    add_executable(${TARGET_NAME} ${ONE_TEST_CPP})
    set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${ONE_TEST_EXEC})

    add_test(NAME ${TARGET_NAME} COMMAND ${ONE_TEST_EXEC})

endforeach()