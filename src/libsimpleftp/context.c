#include <malloc.h>

#include "context.h"

void simpleftp_context_init(simpleftp_context *context) {
    context = (simpleftp_context *) malloc(sizeof(simpleftp_context));
}

void simpleftp_context_free(simpleftp_context *context) {
    free(context);
}
