/*
** EPITECH PROJECT, 2025
** get_prompt.c
** File description:
** get a shell prompt
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../include/my.h"
#include <signal.h>

/**
* @brief Get the id of a signal in case of the child was
* terminated/stopped by signal.
* @param pid the pid of the child
* @return id of a signal or 84 if there is no signal.
*/
static int get_signal(__pid_t pid)
{
    if (WIFSIGNALED(pid))
        return WTERMSIG(pid);
    if (WIFSTOPPED(pid))
        return WSTOPSIG(pid);
    return 84;
}

static void print_signal_msg_core_dump(__pid_t pid, char const *msg)
{
    if (WCOREDUMP(pid)) {
        if (my_strlen(msg) > 0)
            write(1, msg, my_strlen(msg));
        write(1, " (core dumped)\n", 15);
    } else {
        if (my_strlen(msg) > 0)
            write(1, msg, my_strlen(msg));
        write(1, "\n", 1);
    }
}

static void print_signal_msg_part6(int signal_code, __pid_t pid)
{
    switch (signal_code) {
        case 29:
            print_signal_msg_core_dump(pid, "Pollable event occurred");
            break;
        case 30:
            print_signal_msg_core_dump(pid, "Power failure");
            break;
        case 31:
            print_signal_msg_core_dump(pid, "Bad system call");
            break;
        default:
            break;
    }
}

static void print_signal_msg_part5(int signal_code, __pid_t pid)
{
    switch (signal_code) {
        case 22:
            print_signal_msg_core_dump(pid, "\nSuspended (tty output)");
            break;
        case 24:
            print_signal_msg_core_dump(pid, "Cputime limit exceeded");
            break;
        case 25:
            print_signal_msg_core_dump(pid, "Filesize limit exceeded");
            break;
        case 26:
            print_signal_msg_core_dump(pid, "Virtual time alarm");
            break;
        case 27:
            print_signal_msg_core_dump(pid, "Profiling time alarm");
            break;
        default:
            print_signal_msg_part6(signal_code, pid);
    }
}

static void print_signal_msg_part4(int signal_code, __pid_t pid)
{
    switch (signal_code) {
        case 15:
            print_signal_msg_core_dump(pid, "Terminated");
            break;
        case 16:
            print_signal_msg_core_dump(pid, "Stack limit exceeded");
            break;
        case 19:
            print_signal_msg_core_dump(pid, "\nSuspended (signal)");
            break;
        case 20:
            print_signal_msg_core_dump(pid, "\nSuspended");
            break;
        case 21:
            print_signal_msg_core_dump(pid, "\nSuspended (tty input)");
            break;
        default:
            print_signal_msg_part5(signal_code, pid);
    }
}

static void print_signal_msg_part3(int signal_code, __pid_t pid)
{
    switch (signal_code) {
        case 10:
            print_signal_msg_core_dump(pid, "User signal 1");
            break;
        case 11:
            print_signal_msg_core_dump(pid, "Segmentation fault");
            break;
        case 12:
            print_signal_msg_core_dump(pid, "User signal 2");
            break;
        case 13:
            print_signal_msg_core_dump(pid, "Broken pipe");
            break;
        case 14:
            print_signal_msg_core_dump(pid, "Alarm clock");
            break;
        default:
            print_signal_msg_part4(signal_code, pid);
    }
}

static void print_signal_msg_part2(int signal_code, __pid_t pid)
{
    switch (signal_code) {
        case 5:
            print_signal_msg_core_dump(pid, "Trace/BPT trap");
            break;
        case 6:
            print_signal_msg_core_dump(pid, "Abort");
            break;
        case 7:
            print_signal_msg_core_dump(pid, "Bus error");
            break;
        case 8:
            print_signal_msg_core_dump(pid, "Floating exception");
            break;
        case 9:
            print_signal_msg_core_dump(pid, "Killed");
            break;
        default:
            print_signal_msg_part3(signal_code, pid);
    }
}

/**
* @brief Print the corresponding message according to received signal
* @param pid Pid of the child process
* @param good_path A string to free
*/
static void print_signal_msg_final(__pid_t pid)
{
    int signal_code = get_signal(pid);

    switch (signal_code) {
        case 1:
            print_signal_msg_core_dump(pid, "Hangup");
            break;
        case 2:
            mini_printf("\n");
            break;
        case 3:
            print_signal_msg_core_dump(pid, "Quit");
            break;
        case 4:
            print_signal_msg_core_dump(pid, "Illegal instruction");
            break;
        default:
            print_signal_msg_part2(signal_code, pid);
    }
}

int get_signals(__pid_t pid)
{
    print_signal_msg_final(pid);
    return 0;
}
