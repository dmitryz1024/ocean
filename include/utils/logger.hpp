#pragma once
#include <fstream>

template<typename T>
class Logger {
public:
    static void log(const std::string& msg) noexcept {
        static std::ofstream ofs("ocean.log", std::ios::app);
        ofs << "[" << T::name() << "] " << msg << "\n";
    }
};