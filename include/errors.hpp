#pragma once

struct errorContext {

};

#define DEBUG
#ifdef DEBUG
#define ON_DEBUG(code) code
#else
#define ON_DEBUG(code)
#endif

const size_t COMMAND_SIZE = 4;

enum toyErrors {
    TOY_SUCCESS,
    TOY_FILE_READ_ERROR,
    TOY_WRONG_FILE_SIZE,

    TOY_FAILED = -1
};

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
