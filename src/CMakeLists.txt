set(APP_NAME "kafkaManager")

add_executable(${APP_NAME} main.cpp main.qrc)

add_subdirectory(core)

target_link_libraries(${APP_NAME} 
    PRIVATE core
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
install(TARGETS ${APP_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)