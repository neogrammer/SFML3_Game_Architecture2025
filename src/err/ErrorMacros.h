// 1. Include required headers
#include "CidError.h" // must come before macro

extern std::string cidres;

// 2. Define macro (after CidError is declared)
#define chk(cidcall) do { \
    cidres = (cidcall); \
    if (cidres != "OK") \
        throw CidError(__LINE__, __FILE__, cidres); \
} while(0)