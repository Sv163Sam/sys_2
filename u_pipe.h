#ifndef UNTITLED_U_PIPE_H
#define UNTITLED_U_PIPE_H

#include "helper.h"

void guess_player(const int pipe_fd[], const int pipe_fd_s[])//zagadivaet
{
    int end_range = 1 + (int) random() % 20;
    int value = 1 + (int) random() % end_range;
    bool flag = false;

    str_display("A number is guessed");
    mes_display("Our range is: ", end_range);
    mes_display("Value is: ", value);
    check(write(pipe_fd[1], &end_range, sizeof(end_range)));

    do
    {
        int assumption;
        if (check(read(pipe_fd_s[0], &assumption, sizeof(int))))
        {
            if(assumption == value)
                flag = true;
            check(write(pipe_fd[1], &flag, sizeof(flag)));
            answer_display(flag);
        }
        else
            _exit(EXIT_FAILURE);
    }while(!flag);
    return;
}

void assump_player(const int pipe_fd[], const int pipe_fd_s[])//otgadivaet
{
    int range;
    int value = 0;
    bool flag = false;
    std::vector<int> attempt = {};

    if (check(read(pipe_fd[0], &range, sizeof(int))))
    {
        for(size_t i = 1; i < range; i++)
        {
            attempt.push_back(i);
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(attempt.begin(), attempt.end(), g);

        do
        {
            value = attempt[0];
            assumption_display(value);
            check(write(pipe_fd_s[1], &value, sizeof(value)));
            if (check(read(pipe_fd[0], &flag, sizeof(bool))))
            {
                if (!flag)
                {
                    attempt.erase(attempt.begin());
                    increment_game_count();
                }
                else
                    return;
            }
            else {
                _exit(EXIT_FAILURE);
            }
        }while (!flag);
        return;
    }
    _exit(EXIT_FAILURE);
}
/*
void player_1(const int pipe_fd[], const int pipe_fd_s[], bool flag)
{
    if(flag)
    {
        str_display("First player - guesser");
        guess_player(pipe_fd, pipe_fd_s);
        return;
    }
    str_display("First player - assumper");
    assump_player(pipe_fd, pipe_fd_s);
    return;
}

void player_2(const int pipe_fd[], const int pipe_fd_s[], bool flag)
{
    if (flag) {
        str_display("Second player - assumper");
        assump_player(pipe_fd, pipe_fd_s);
        return;
    }
    str_display("Second player - guesser");
    guess_player(pipe_fd, pipe_fd_s);
    return;
}

namespace UP
{
    void riddler(const int pipe_fd[])
    {


        int value = 1 + (int) random() % n;
        std::cout << "Guessed value: " << value << '\n';
        check(write(pipe_fd[1], &n, sizeof(n)));

        bool flag = false;
        while (!flag)
        {
            int buffer;
            if (check(read(pipe_fd[0], &buffer, sizeof(int))))
            {
                if(buffer == value)
                    flag = true;
                check(write(pipe_fd[1], &flag, sizeof(flag)));

            }
            else
                _exit(EXIT_FAILURE);
        }
    }

    std::pair<bool, int> guesser(const int pipe_fd[])
    {
        struct timespec ts{};
        clock_gettime(CLOCK_MONOTONIC, &ts);
        srandom((time_t)ts.tv_nsec);

        int n;
        if (check(read(pipe_fd[0], &n, sizeof(int))))
        {
            bool flag = false;
            int i = 0;
            std::vector<bool> was_guessed(n, false);
            while (i < INT_MAX && !flag)
            {
                int value;
                do
                {
                    value = 1 + (int)random() % n;
                }
                while(was_guessed[value - 1]);
                was_guessed[value - 1] = true;

                check(write(pipe_fd[1], &value, sizeof(value)));
                usleep(DELAY);

                if (check(read(pipe_fd[0], &flag, sizeof(bool))))
                    std::cout << '[' << i++ + 1 << "]\t" << value << "\t" << (flag ? "true\n" : "false\n");
                else
                    _exit(EXIT_FAILURE);
            }
            std::cout << '\n';
            return std::make_pair(flag, i);
        }
        _exit(EXIT_FAILURE);
    }

    void player(const int i, const int fd[], const int n,
                std::pair<std::pair<int, int>, double>& stats, bool (*cmp)(const int))
    {
        if (cmp(i))
        {
            sleep(DELAY);
            riddler(fd, n);
        }
        else
        {
            auto start_time = std::chrono::high_resolution_clock::now();
            const std::pair<bool, int> result = guesser(fd);

            auto end_time = std::chrono::high_resolution_clock::now();
            print_result(result, std::chrono::duration<double, std::micro>(end_time - start_time).count());

            if(result.first)
                stats.first.first++;
            stats.first.second += result.second;
            stats.second += std::chrono::duration<double, std::micro>(end_time - start_time).count();

            sleep(1);
        }
    }

    void start(const int n, const int count)
    {
        std::pair<std::pair<int, int>, double> stats {{0, 0}, 0.0};

        int fd[2];
        check(pipe(fd));
        pid_t p_id = check(fork());

        bool (*cmp)(const int);
        if (p_id)
            cmp = comp_1;
        else
            cmp = comp_2;

        for(int i = 0; i < count; i++)
            player(i, fd, n, stats, cmp);


        if(p_id)
        {
            std::pair<std::pair<int, int>, double> buffer;
            if(check(read(fd[0], &buffer, sizeof(std::pair<std::pair<int, int>, double>))))
            {
                stats.first.first += buffer.first.first;
                stats.first.second += buffer.first.second;
                stats.second += buffer.second;
            }
            close(fd[0]);
            close(fd[1]);

            print_stat(stats, count);

            waitpid(p_id, nullptr, 0);
            exit(EXIT_SUCCESS);
        }
        else
        {
            sleep(DELAY);

            check(write(fd[1], &stats, sizeof(std::pair<std::pair<int, int>, double>)));
            usleep(DELAY);

            exit(EXIT_SUCCESS);
        }
    }
}
*/






#endif //UNTITLED_U_PIPE_H
