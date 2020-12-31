#include <gnu.hpp>

#include <chrono>
#include <thread>

#include <iomanip>
#include <iostream>

#define loop while (1)

int main(int argc, char *argv[]) {
    gnu::unix_time new_year_time = gnu::time() + gnu::unix_time(3);

    std::cout << std::setfill('0') << "Between now and the happy new year..." << std::endl;
    std::cout.flush();

    loop {
        gnu::unix_time delta_time = new_year_time - gnu::time();

        gnu::tm_t *pretty_time = delta_time.absolute_time();

        std::cout << "\rThere is only " << std::setw(2) << pretty_time->tm_hour << ':' << std::setw(2) << pretty_time->tm_min << ':' << std::setw(2) << pretty_time->tm_sec << " left.";
        std::cout.flush();

        if (delta_time.is_nil())
            break;

        std::this_thread::sleep_for(
            std::chrono::seconds { 1 }
        );
    }

    std::cout << std::endl << "Happy New Year of 2021!" << std::endl;
}

