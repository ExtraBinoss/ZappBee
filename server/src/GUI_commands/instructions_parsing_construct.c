/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** instructions_parsing_utils.c
*/

#include "instructions_parsing_construct.h"
#include "instructions.h"
#include "general_utils.h"
#include "log.h"

void construct_instruction(char *instruction, char *token, int arg_count)
{
    strcat(instruction, token);
    for (int j = 0; j < arg_count; j++) {
        token = strtok(NULL, "\n");
        if (token == NULL) {
            log_message("log/instructions_parsing.log", RED,
                "[ERROR] Invalid instruction parameters.");
            return;
        }
        strcat(instruction, " ");
        strcat(instruction, token);
    }
}

bool skip_instructions(char *token)
{
    char *skip_list[] = {"sbp", "suc"};
    int skip_count = sizeof(skip_list) / sizeof(skip_list[0]);

    for (int i = 0; i < skip_count; i++) {
        if (strcmp(token, skip_list[i]) == 0) {
            return true;
        }
    }
    return false;
}
