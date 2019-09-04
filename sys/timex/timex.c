#include <stdio.h>
#include <inttypes.h>

#include "timex.h"

timex_t timex_add(const timex_t a, const timex_t b)
{
    timex_t result;
    result.seconds = a.seconds + b.seconds;
    result.microseconds = a.microseconds + b.microseconds;

    if (result.microseconds > US_PER_SEC) {
        result.microseconds -= US_PER_SEC;
        result.seconds++;
    }

    return result;
}

timex_t timex_set(uint32_t seconds, uint32_t microseconds)
{
    timex_t result;
    result.seconds = seconds;
    result.microseconds = microseconds;

    return result;
}

timex_t timex_sub(const timex_t a, const timex_t b)
{
    timex_t result;

    if (a.microseconds >= b.microseconds) {
        result.seconds = a.seconds - b.seconds;
        result.microseconds = a.microseconds - b.microseconds;
    }
    else {
        result.seconds = a.seconds - b.seconds - 1;
        result.microseconds = a.microseconds + US_PER_SEC - b.microseconds;
    }

    return result;
}

int timex_cmp(const timex_t a, const timex_t b)
{
    if (a.seconds < b.seconds) {
        return -1;
    }

    if (a.seconds == b.seconds) {
        if (a.microseconds < b.microseconds) {
            return -1;
        }

        if (a.microseconds == b.microseconds) {
            return 0;
        }
    }

    return 1;
}
