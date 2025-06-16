/*
** EPITECH PROJECT, 2025
** redirect_signals.c
** File description:
** ...
*/

#include "../include/my.h"

/**
 * @brief Desactivate some signals in main processus
 * @note Desactivated signals:
 *
 * @note SIGINT
 *
 * @note SIGQUIT
 *
 * @note SIGCONT
 *
 * @note SIGTTIN
 *
 * @note SIGTTOU
 *
 * @note SIGHUP
 */
void ignore_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGCONT, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
}

/**
 * @brief Reactivate some signals in child processus
 * @note Reactivated signals:
 *
 * @note SIGINT
 *
 * @note SIGQUIT
 *
 * @note SIGCONT
 *
 * @note SIGTTIN
 *
 * @note SIGTTOU
 *
 * @note SIGHUP
 */
void reactive_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGCONT, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGHUP, SIG_DFL);
}
