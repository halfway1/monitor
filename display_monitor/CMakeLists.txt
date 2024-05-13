#
# Dependencies

find_package(Qt5 
  REQUIRED COMPONENTS
  Core
  Widgets
)
# 告诉 CMake 查找 Qt5 库，并要求至少找到 Core 和 Widgets 组件

set(SOURCES
    main.cpp
    monitor_inter.cpp
    cpu_softirq_model.cpp
    cpu_load_model.cpp
    monitor_widget.cpp
    cpu_stat_model.cpp
    mem_model.cpp
    net_model.cpp
)

# source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

#
# Target
#
add_executable(display ${SOURCES})
set_target_properties(display PROPERTIES AUTOMOC TRUE)  
# 用于设置目标属性。在这里，目标是 display，属性是 AUTOMOC。
# AUTOMOC 属性用于指示 CMake 在构建过程中自动生成 Qt 的元对象编译器（MOC）所需的源文件。这对于包含了 Qt 的信号和槽机制以及其他元对象系统特性的类是必需的


target_include_directories(display PUBLIC
  ${PROJECT_SOURCE_DIR}/rpc_manager
)

target_link_libraries(display
    PUBLIC
    client
    monitor_proto
    Qt5::Widgets
    Qt5::Core
    # qwt-qt5
)


# INSTALL(TARGETS client
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
# )
