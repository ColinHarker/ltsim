#ifndef UTILS_H
#define UTILS_H

#define APP_VERS 0.1
#define APP_NAME "ltsim"
#define APP_NAME_FULL "Linux Terminal System Information Monitor"

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

std::string exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

#endif