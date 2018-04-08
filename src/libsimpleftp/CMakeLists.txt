set(LIBSIMPLEFTP_SOURCES
        context.c
        command.c)

set(LIBSIMPLEFTP_HEADERS
        context.h
        command.h)

add_library(simpleftp
        STATIC
        ${LIBSIMPLEFTP_SOURCES}
        ${LIBSIMPLEFTP_HEADERS})
