add_subdirectory(libsimpleftp)

set(SIMPLEFTPD_SOURCES
        simpleftpd.c
        ui.c
        config.c
        socket.c
        worker.c
        stack.c)

set(SIMPLEFTPD_HEADERS
        simpleftpd.h
        ui.h
        config.h
        socket.h
        worker.h
        stack.h)

set(SIMPLEFTPD_STANDALONE_HEADERS
        default.h
        version.h)

add_executable(simpleftpd
        ${SIMPLEFTPD_SOURCES}
        ${SIMPLEFTPD_HEADERS}
        ${SIMPLEFTPD_STANDALONE_HEADERS})

target_link_libraries(simpleftpd
        pthread
        simpleftp)
