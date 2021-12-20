#ifndef _NETWORK_PROGRAMMING_SHARED_TCP_STRUCTS

#define _NETWORK_PROGRAMMING_SHARED_TCP_STRUCTS

struct SquareRootRequest {
    double a;
    double b;
    double c;
};

enum RootStatus {
    NO_ROOTS = 0, ONE_ROOTS = 1, TWO_ROOTS = 2
};
struct SquareRootResponse {
    double x1;
    double x2;
    enum RootStatus status;
};


struct CesarRequest {
    int shiftKey;

    char textToEncode[256];
};

struct CesarResponse {
    int shiftKey;
    char encodedText[256];
};
#endif // !_NETWORK_PROGRAMMING_SHARED_TCP_STRUCTS
