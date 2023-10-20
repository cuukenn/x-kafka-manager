add_library(core "")

target_sources(core
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/context.cpp
    ${CMAKE_CURRENT_LIST_DIR}/kafka_client.cpp
    ${CMAKE_CURRENT_LIST_DIR}/kafka_monitor.cpp
)
target_include_directories(core
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(core
    PUBLIC Qt6::Quick
    PUBLIC RdKafka::rdkafka RdKafka::rdkafka++
)