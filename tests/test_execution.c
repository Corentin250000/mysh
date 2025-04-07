/*
** EPITECH PROJECT, 2025
** test_command.c
** File description:
** ...
*/

#include "../include/minishell2.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

char **create_env(void)
{
    char *not_separated_env = my_strdup("SHELL=/bin/bash\n"
        "SESSION_MANAGER=local/corentinpasquier:@/tmp/.ICE-unix/3858,unix/corentinpasquier:/tmp/.ICE-unix/3858\n"
        "QT_ACCESSIBILITY=1\n"
        "COLORTERM=truecolor\n"
        "XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu-wayland:/etc/xdg\n"
        "XDG_MENU_PREFIX=gnome-\n"
        "GNOME_DESKTOP_SESSION_ID=this-is-deprecated\n"
        "GNOME_SHELL_SESSION_MODE=ubuntu\n"
        "SSH_AUTH_SOCK=/run/user/1000/keyring/ssh\n"
        "MEMORY_PRESSURE_WRITE=c29tZSAyMDAwMDAgMjAwMDAwMAA=\n"
        "XMODIFIERS=@im=ibus\n"
        "DESKTOP_SESSION=ubuntu-wayland\n"
        "GPG_TTY=/dev/pts/3\n"
        "GTK_MODULES=gail:atk-bridge\n"
        "PWD=/home/corentin/Epitech_projects/2024-2025_tek1/Semester2/PSU/minishell2/B-PSU-200-MLH-2-1-minishell2-corentin.pasquier\n"
        "LOGNAME=corentin\n"
        "XDG_SESSION_DESKTOP=ubuntu-wayland\n"
        "XDG_SESSION_TYPE=wayland\n"
        "SYSTEMD_EXEC_PID=3902\n"
        "XAUTHORITY=/run/user/1000/.mutter-Xwaylandauth.FH0B22\n"
        "HOME=/home/corentin\n"
        "USERNAME=corentin\n"
        "IM_CONFIG_PHASE=1\n"
        "LANG=en_US.UTF-8\n"
        "LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=00:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.avif=01;35:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:*~=00;90:*#=00;90:*.bak=00;90:*.crdownload=00;90:*.dpkg-dist=00;90:*.dpkg-new=00;90:*.dpkg-old=00;90:*.dpkg-tmp=00;90:*.old=00;90:*.orig=00;90:*.part=00;90:*.rej=00;90:*.rpmnew=00;90:*.rpmorig=00;90:*.rpmsave=00;90:*.swp=00;90:*.tmp=00;90:*.ucf-dist=00;90:*.ucf-new=00;90:*.ucf-old=00;90:\n"
        "XDG_CURRENT_DESKTOP=ubuntu:GNOME\n"
        "MEMORY_PRESSURE_WATCH=/sys/fs/cgroup/user.slice/user-1000.slice/user@1000.service/session.slice/org.gnome.Shell@wayland.service/memory.pressure\n"
        "VTE_VERSION=7600\n"
        "WAYLAND_DISPLAY=wayland-0\n"
        "GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/a5034443_c776_4e71_a1ea_f7eb6e33f829\n"
        "GNOME_SETUP_DISPLAY=:2\n"
        "LESSCLOSE=/usr/bin/lesspipe %s %s\n"
        "XDG_SESSION_CLASS=user\n"
        "TERM=xterm-256color\n"
        "LESSOPEN=| /usr/bin/lesspipe %s\n"
        "LIBVIRT_DEFAULT_URI=qemu:///system\n"
        "USER=corentin\n"
        "GNOME_TERMINAL_SERVICE=:1.137\n"
        "DISPLAY=:1\n"
        "SHLVL=2\n"
        "GSM_SKIP_SSH_AGENT_WORKAROUND=true\n"
        "QT_IM_MODULE=ibus\n"
        "XDG_RUNTIME_DIR=/run/user/1000\n"
        "DEBUGINFOD_URLS=https://debuginfod.ubuntu.com \n"
        "XDG_DATA_DIRS=/usr/share/ubuntu-wayland:/usr/share/gnome:/usr/local/share/:/usr/share/:/var/lib/snapd/desktop\n"
        "PATH=/home/corentin/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin:/home/corentinpasquier/.local/bin:/home/corentin/Epitech_projects/2024-2025_tek1/Create-base-Makefile:/home/corentin/Epitech_projects/2024-2025_tek1/put_header_c_file:/home/corentin/.local/bin\n"
        "GDMSESSION=ubuntu-wayland\n"
        "DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus\n"
        "_=/usr/bin/tcsh\n"
        "NLSPATH=/usr/share/locale/%L/LC_MESSAGES/%N.cat:/usr/share/locale/%l/LC_MESSAGES/%N.cat\n"
        "HOSTTYPE=x86_64-linux\n"
        "VENDOR=unknown\n"
        "OSTYPE=linux\n"
        "MACHTYPE=x86_64\n"
        "GROUP=corentin\n"
        "HOST=corentinpasquier");
    char **env;

    if (!not_separated_env)
        return NULL;
    env = my_str_to_word_array(not_separated_env, "\n");
    free(not_separated_env);
    return env;
}

void redirect(void)
{
    cr_redirect_stderr();
    cr_redirect_stdout();
}

Test(copy_env, error_handling_nb_arguments, .init = redirect)
{
    int ac = 2;
    char **env = create_env();
    command_t *infos;

    cr_assert_not_null(env);
    infos = copy_env(env, ac);
    cr_assert_null(infos);
}

Test(copy_env, normal_execution, .init = redirect)
{
    int ac = 1;
    char **env = create_env();
    command_t *infos;

    cr_assert_not_null(env);
    infos = copy_env(env, ac);
    cr_assert_not_null(infos);
}

Test(execution, error_handling_builtin, .init = redirect)
{
    int ac = 1;
    char **env = create_env();
    command_t *infos;
    char *good_path = my_strdup("/bin/pwd");

    cr_assert_not_null(env);
    infos = copy_env(env, ac);
    cr_assert_not_null(infos);
    infos->builtin = 1;
    infos->command = my_strdup("/bin/pwd");
    cr_assert_not_null(infos->command);
    cr_assert_not_null(good_path);
    execution(infos, good_path);
    cr_assert_stdout_neq_str("/home/corentin/Epitech_projects/2024-2025_tek1/Semester2/PSU/minishell2/B-PSU-200-MLH-2-1-minishell2-corentin.pasquier");
}

Test(execution, error_handling_options, .init = redirect)
{
    int ac = 1;
    char **env = create_env();
    command_t *infos;
    char *good_path = my_strdup("/bin/pwd");

    cr_assert_not_null(env);
    infos = copy_env(env, ac);
    cr_assert_not_null(infos);
    infos->builtin = 0;
    infos->options = NULL;
    infos->command = my_strdup("/bin/pwd");
    cr_assert_not_null(infos->command);
    cr_assert_not_null(good_path);
    execution(infos, good_path);
    cr_assert_stdout_neq_str("/home/corentin/Epitech_projects/2024-2025_tek1/Semester2/PSU/minishell2/B-PSU-200-MLH-2-1-minishell2-corentin.pasquier");
}

Test(execution, error_handling_env, .init = redirect)
{
    int ac = 1;
    char **env = create_env();
    command_t *infos;
    char *good_path = my_strdup("/bin/pwd");

    cr_assert_not_null(env);
    infos = copy_env(env, ac);
    cr_assert_not_null(infos);
    infos->builtin = 0;
    infos->command = my_strdup("/bin/pwd");
    cr_assert_not_null(infos->command);
    cr_assert_not_null(good_path);
    for (int i = 0; infos->cpy_env[i] != NULL; ++i)
        free(infos->cpy_env[i]);
    free(infos->cpy_env);
    infos->cpy_env = NULL;
    execution(infos, good_path);
    cr_assert_stdout_neq_str("/home/corentin/Epitech_projects/2024-2025_tek1/Semester2/PSU/minishell2/B-PSU-200-MLH-2-1-minishell2-corentin.pasquier");
    error_free_structure(infos, 0);
}

Test(execution, null_absolute_path, .init = redirect)
{
    int ac = 1;
    char **env = create_env();
    command_t *infos;
    char *good_path = NULL;

    cr_assert_not_null(env);
    infos = copy_env(env, ac);
    cr_assert_not_null(infos);
    infos->builtin = 0;
    infos->command = my_strdup("/bin/pwd");
    infos->options = malloc(sizeof(char *) * 3);
    cr_assert_not_null(infos->options);
    infos->options[0] = my_strdup("OK\n");
    cr_assert_not_null(infos->options[0]);
    cr_assert_not_null(infos->command);
    cr_assert_null(good_path);
    execution(infos, good_path);
    cr_assert_stdout_eq_str("/home/corentin/Epitech_projects/2024-2025_tek1/Semester2/PSU/minishell2/B-PSU-200-MLH-2-1-minishell2-corentin.pasquier");
    error_free_structure(infos, 0);
}

Test(execution, need_absolute_path, .init = redirect)
{
    int ac = 1;
    char **env = create_env();
    command_t *infos;
    char *good_path = my_strdup("/bin/pwd");

    cr_assert_not_null(env);
    infos = copy_env(env, ac);
    cr_assert_not_null(infos);
    infos->builtin = 0;
    infos->command = my_strdup("pwd");
    infos->options = malloc(sizeof(char *) * 3);
    cr_assert_not_null(infos->options);
    infos->options[0] = my_strdup("OK\n");
    cr_assert_not_null(infos->options[0]);
    cr_assert_not_null(infos->command);
    cr_assert_not_null(good_path);
    execution(infos, good_path);
    cr_assert_stdout_eq_str("/home/corentin/Epitech_projects/2024-2025_tek1/Semester2/PSU/minishell2/B-PSU-200-MLH-2-1-minishell2-corentin.pasquier");
    error_free_structure(infos, 0);
}
