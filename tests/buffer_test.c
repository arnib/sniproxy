#include <assert.h>
#include "buffer.h"

static void test1() {
    struct Buffer *buffer;
    char input[] = "This is a test.";
    char output[sizeof(input)];
    int len, i;

    buffer = new_buffer(200);
    assert(buffer != NULL);

    len = buffer_push(buffer, input, sizeof(input));
    assert(len == sizeof(input));


    len = buffer_peek(buffer, output, sizeof(output));
    assert(len == sizeof(input));

    for (i = 0; i < len; i++)
        assert(input[i] == output[i]);

    len = buffer_peek(buffer, output, sizeof(output));
    assert(len == sizeof(input));

    for (i = 0; i < len; i++)
        assert(input[i] == output[i]);

    len = buffer_pop(buffer, output, sizeof(output));
    assert(len == sizeof(input));

    for (i = 0; i < len; i++)
        assert(input[i] == output[i]);

    len = buffer_pop(buffer, output, sizeof(output));
    assert(len == 0);

    free_buffer(buffer);
}

static void test2() {
    struct Buffer *buffer;
    char input[] = "Testing wrap around behaviour.";
    char output[sizeof(input)];
    int len, i = 0;

    buffer = new_buffer(200);
    assert(buffer != NULL);

    while (i < 180) {
        len = buffer_push(buffer, input, sizeof(input));
        assert(len  == sizeof(input));

        i += len;
    }

    while (len) {
        len = buffer_pop(buffer, output, sizeof(output));
    }

    len = buffer_push(buffer, input, sizeof(input));
    assert(len == sizeof(input));


    len = buffer_peek(buffer, output, sizeof(output));
    assert(len == sizeof(input));

    for (i = 0; i < len; i++)
        assert(input[i] == output[i]);

    len = buffer_pop(buffer, output, sizeof(output));
    assert(len == sizeof(input));

    for (i = 0; i < len; i++)
        assert(input[i] == output[i]);

    len = buffer_push(buffer, input, sizeof(input));
    assert(len == sizeof(input));


    len = buffer_peek(buffer, output, sizeof(output));
    assert(len == sizeof(input));

    for (i = 0; i < len; i++)
        assert(input[i] == output[i]);

    free_buffer(buffer);
}

int main() {
    test1();

    test2();
}


