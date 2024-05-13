
set(SOURCES
   main.cpp
   monitor/cpu_softirq_monitor.cpp
   monitor/cpu_load_monitor.cpp
   monitor/cpu_stat_monitor.cpp
   monitor/mem_monitor.cpp
   monitor/net_monitor.cpp
   utils/read_file.cpp
)

add_executable(monitor ${SOURCES})

# target_include_directories(monitor PUBLIC
#   ../include/..
# )
# 用于指定特定目标（例如可执行文件、库）的包含目录。这些目录用于告诉编译器在哪里查找头文件
target_include_directories(monitor PUBLIC
  ${PROJECT_SOURCE_DIR}/test_monitor/include
  ${PROJECT_SOURCE_DIR}/rpc_manager
)

# 用于将一个或多个库链接到指定的目标（例如可执行文件、库）。这个函数是 CMake 构建系统中非常重要的一个函数，用于指定目标依赖的外部库
target_link_libraries(monitor
    PUBLIC
    monitor_proto
    client
    boost_system
    boost_chrono
)