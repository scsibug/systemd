/* SPDX-License-Identifier: LGPL-2.1-or-later */
#pragma once

#include <stdbool.h>

#include "time-util.h"

typedef enum AskPasswordFlags {
        ASK_PASSWORD_ACCEPT_CACHED = 1 << 0,  /* read from kernel keyring */
        ASK_PASSWORD_PUSH_CACHE    = 1 << 1,  /* write to kernel keyring after getting password from elsewhere */
        ASK_PASSWORD_ECHO          = 1 << 2,  /* show the password literally while reading, instead of "*" */
        ASK_PASSWORD_SILENT        = 1 << 3,  /* do no show any password at all while reading */
        ASK_PASSWORD_NO_TTY        = 1 << 4,  /* never ask for password on tty */
        ASK_PASSWORD_NO_AGENT      = 1 << 5,  /* never ask for password via agent */
        ASK_PASSWORD_CONSOLE_COLOR = 1 << 6,  /* Use color if /dev/console points to a console that supports color */
        ASK_PASSWORD_NO_CREDENTIAL = 1 << 7,  /* never use $CREDENTIALS_DIRECTORY data */
        ASK_PASSWORD_HIDE_EMOJI    = 1 << 8,  /* hide the lock and key emoji */
        ASK_PASSWORD_HEADLESS      = 1 << 9,  /* headless mode: never query interactively */
        ASK_PASSWORD_USER          = 1 << 10, /* query only our own agents, not any system password agents */
} AskPasswordFlags;

/* Encapsulates the mostly static fields of a password query */
typedef struct AskPasswordRequest {
        const char *message;         /* The human readable password prompt when asking interactively */
        const char *keyring;         /* kernel keyring key name (key of "user" type) */
        const char *icon;            /* freedesktop icon spec name */
        const char *id;              /* some identifier used for this prompt for the "ask-password" protocol */
        const char *credential;      /* $CREDENTIALS_DIRECTORY credential name */
} AskPasswordRequest;

int ask_password_tty(int tty_fd, const AskPasswordRequest *req, usec_t until, AskPasswordFlags flags, const char *flag_file, char ***ret);
int ask_password_plymouth(const AskPasswordRequest *req, usec_t until, AskPasswordFlags flags, const char *flag_file, char ***ret);
int ask_password_agent(const AskPasswordRequest *req, usec_t until, AskPasswordFlags flag, char ***ret);
int ask_password_auto(const AskPasswordRequest *req, usec_t until, AskPasswordFlags flag, char ***ret);

int acquire_user_ask_password_directory(char **ret);
