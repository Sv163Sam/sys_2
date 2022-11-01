//#include "u_pipe.h"
#include "signals.h"


int main() {

    str_display("GAME STARTING");

    pid_t p_id = check(fork());

    if (p_id) {
        guess_player(p_id);
    } else {
        assump_player(p_id);
    }
    exit(EXIT_SUCCESS);
}


/*
int main()
{
    int count = 0;
    bool game_flag = true;
    str_display("GAME STARTING");

        int fd[2];
        int fd_s[2];
        check(pipe(fd));
        check(pipe(fd_s));
        pid_t p_id = check(fork());

        do {
            if(count % 2 != 0) game_flag = false;
            if (p_id) {
                if(game_flag) guess_player(fd, fd_s);
                else
                {
                    sleep(1);
                    assump_player(fd, fd_s);
                }
            }
            else
            {
                if(game_flag) assump_player(fd, fd_s);
                else
                {
                    sleep(1);
                    guess_player(fd, fd_s);
                }
            }
            count++;
            if (!game_flag) game_flag = true;
        }while(count < 11);
        exit(EXIT_SUCCESS);
}
// time, attempts
*/
