#pragma once

struct InvalidIsoException
{
    char *message;
    InvalidIsoException(char *msg) { message = msg; }
};
