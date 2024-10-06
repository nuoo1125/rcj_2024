add_library(mcp3208 mcp3208.c)

target_link_libraries(mcp3208 pico_stdlib hardware_spi)