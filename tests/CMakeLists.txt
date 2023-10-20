# unit test
function(x_add_executable_and_link name source_name)
    add_executable(${name} ${source_name} ${SOURCE})
    target_link_libraries(${name}
        PRIVATE core
        PRIVATE Qt6::Quick
        PRIVATE RdKafka::rdkafka RdKafka::rdkafka++
    )
endfunction(x_add_executable_and_link)
x_add_executable_and_link(${APP_NAME}_test_1 test_case_1.cpp)
x_add_executable_and_link(${APP_NAME}_test_2 test_case_2.cpp)