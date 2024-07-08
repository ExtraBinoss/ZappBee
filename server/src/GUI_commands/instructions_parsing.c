/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** instructions_parsing.c
*/

#include "server.h"
#include "log.h"
#include "general_utils.h"
#include "instructions_parsing_construct.h"
#include "log.h"

/**
 * @file instructions_parsing.c
 * @brief Contains the definition of the instruction_info array.
 *
 * It has 2 parameters:
 * - name: the name of the instruction
 * - arg_count: the number of arguments the instruction takes
 */
static const instruction_info_t instruction_info[] = {
    {"msz", 0},
    {"bct", 2},
    {"mct", 0},
    {"tna", 0},
    {"ppo", 1},
    {"plv", 1},
    {"pin", 1},
    {"sgt", 0},
    {"sst", 1}
};

static void process_valid_instruction(char *token, instruction_stack_t *stack,
    unsigned long i)
{
    char *instruction = malloc_check(strlen(token)
        + instruction_info[i].arg_count * 9 + 1);

    instruction[0] = '\0';
    construct_instruction(instruction,
        token, instruction_info[i].arg_count);
    push_instruction(stack, instruction);
    log_message("log/instructions_parsing.log", GREEN,
        "[INFO] Instruction added to the stack: %s", instruction);
    remove_from_garbage(instruction);
}

void process_token(char *token, instruction_stack_t *stack)
{
    unsigned long end = sizeof(instruction_info) / sizeof(instruction_info[0]);

    for (unsigned long i = 0; i < end; i++) {
        if (strcmp(token, instruction_info[i].name) == 0
            && !skip_instructions(token)) {
                process_valid_instruction(token, stack, i);
                break;
        }
    }
}

/**
 * @brief Checks the validity of an instruction set and
 * adds it to the instruction stack.
 *
 * This function takes an instruction set as input and checks its validity.
 * If the instruction set is valid,
 * it is added to the instruction stack.
 *
 * @param instruction_set The instruction set to be checked.
 * @param stack The instruction stack to
 * which the valid instruction set will be added.
 */
static void instructions_checker(char *instruction_set,
    instruction_stack_t *stack)
{
    char *token = strtok(instruction_set, " ");

    while (token != NULL) {
        process_token(token, stack);
        token = strtok(NULL, " ");
    }
}

/**
 * Parses the given instruction set and performs instructions checking.
 * Prints each instruction message in the stack.
 *
 * before using this function, init instruction in your code.
 * And also use the free_instruction function to free the instruction stack
 * after using instructions_parsing function
 * the char *instruction_set will be free in this function; no need to free it
 *
 * @param instruction_set The instruction set to parse.
 */
void instruction_parsing(instruction_stack_t *stack, char *instruction_set)
{
    instructions_checker(instruction_set, stack);
    for (instruction_t *tmp = stack->top; tmp; tmp = tmp->next) {
        log_message("log/instructions_parsing.log", GREEN,
            "[INFO] Instruction in the stack: %s", tmp->msg);
    }
    remove_from_garbage(instruction_set);
}
