/*
** EPITECH PROJECT, 2025
** test_signals.c
** File description:
** ...
*/

#include "../include/my.h"
#include "useful_functions.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>
#include <stdio.h>

Test(get_signals, signal_hangup, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGHUP);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Hangup\n");
}

Test(get_signals, signal_sigint, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGINT);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("\n");
}

Test(get_signals, signal_quit, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGQUIT);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Quit (core dumped)\n");
}

Test(get_signals, signal_sigill, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGILL);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Illegal instruction (core dumped)\n");
}

Test(get_signals, signal_sigtrap, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGTRAP);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Trace/BPT trap (core dumped)\n");
}

Test(get_signals, signal_abort, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGABRT);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Abort (core dumped)\n");
}

Test(get_signals, signal_sigbus, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGBUS);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Bus error (core dumped)\n");
}

Test(get_signals, test_signal_sigfpe, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGFPE);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Floating exception (core dumped)\n");
}

Test(get_signals, test_signal_sigkill, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGKILL);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Killed\n");
}

Test(get_signals, test_signal_siguser1, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGUSR1);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("User signal 1\n");
}

Test(get_signals, signal_segv, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGSEGV);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Segmentation fault (core dumped)\n");
}

Test(get_signals, test_signal_siguser2, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGUSR2);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("User signal 2\n");
}

Test(get_signals, test_signal_sigpipe, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGPIPE);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Broken pipe\n");
}

Test(get_signals, test_signal_sigalrm, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGALRM);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Alarm clock\n");
}

Test(get_signals, test_signal_sigterm, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGTERM);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Terminated\n");
}

Test(get_signals, test_signal_sigstkflt, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGSTKFLT);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Stack limit exceeded\n");
}

Test(get_signals, test_signal_sigstop, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGSTOP);
        exit(1);
    } else {
        waitpid(pid, &status, WUNTRACED);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("\nSuspended (signal)\n");
}

Test(get_signals, test_signal_sigtstp, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGTSTP);
        exit(1);
    } else {
        waitpid(pid, &status, WUNTRACED);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("");
}

Test(get_signals, test_signal_sigttin, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGTTIN);
        exit(1);
    } else {
        waitpid(pid, &status, WUNTRACED);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("");
}

Test(get_signals, test_signal_sigttou, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGTTOU);
        exit(1);
    } else {
        waitpid(pid, &status, WUNTRACED);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("");
}

Test(get_signals, test_signal_sigxcpu, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGXCPU);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Cputime limit exceeded (core dumped)\n");
}

Test(get_signals, test_signal_sigxfsz, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGXFSZ);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Filesize limit exceeded (core dumped)\n");
}

Test(get_signals, test_signal_sigvtalrm, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGVTALRM);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Virtual time alarm\n");
}

Test(get_signals, test_signal_sigprof, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGPROF);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Profiling time alarm\n");
}

Test(get_signals, test_signal_sigio, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGIO);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Pollable event occurred\n");
}

Test(get_signals, test_signal_sigpwr, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGPWR);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Power failure\n");
}

Test(get_signals, test_signal_sigsys, .init = redirect_all_std)
{
    int status = 0;
    pid_t pid = fork();

    if (pid == 0) {
        raise(SIGSYS);
        exit(1);
    } else {
        waitpid(pid, &status, 0);
        get_signals(status);
    }
    cr_assert_stdout_eq_str("Bad system call (core dumped)\n");
}
