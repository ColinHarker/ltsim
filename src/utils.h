#ifndef UTILS_H
#define UTILS_H

#define APP_VERS 0.1
#define APP_NAME "ltssd"
#define APP_NAME_FULL "Linux Terminal System Statistics Display"

#ifdef _WIN32
std::cerr << "Program not built for windows os" << '\n';
exit(1);
#endif

#ifdef __APPLE__
std::cerr << "Program not built for apple os" << '\n';
exit(1);
#endif

enum color
{
    null,
    green,
    yellow,
    red
};

#endif