set(SIMPLEFTPD_SOURCES
        simpleftpd.c
        ui.c
        config.c
        socket.c
        worker.c
        stack.c)

set(SIMPLEFTPD_HEADERS
        default.h
        version.h
        simpleftpd.h
        ui.h
        config.h
        socket.h
        worker.h
        stack.h)

add_executable(simpleftpd
        ${SIMPLEFTPD_SOURCES}
        ${SIMPLEFTPD_HEADERS})

target_link_libraries(simpleftpd
        pthread)
