#ifndef UNTITLED_HELPER_H
#define UNTITLED_HELPER_H

#include <iostream>
#include <cstring>
#include "check.h"
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <vector>
#include <algorithm>
#include <random>
#include <unistd.h>

struct game_result
{
    size_t time = 0.0;
    int att_count = 0;
};
game_result object;

void increment_game_count()
{
    object.att_count++;
}

void set_game_time(size_t time)
{
    object.time = time;
}

void str_display(const std::string& data)
{
    std::cout << data << std::endl;
}

void mes_display(const std::string& data, const int value)
{
    std::cout << data << value << std::endl;
}

void stat_display()
{
    std::cout << "Result game time: " << object.time << std::endl;
    std::cout << "Amount of attempts of this game: "  << object.att_count << std::endl;
}

void assumption_display(const int value)
{
    std::cout << "My assumption is: " << value << std::endl;
}

void answer_display(bool flag)
{
    if (flag)
        std::cout << "Your answer is right! Congratulations. Your game just ended. Change places." << std::endl;
    else
        std::cout << "You're not right." << std::endl;
}


#endif //UNTITLED_HELPER_H
