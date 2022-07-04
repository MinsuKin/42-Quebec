#include "minunit.h"
#include "../minishell.h"

// THIS CODE WAS PULLED FROM: https://github.com/siu/minunit

/*
    --> mu_check(condition): will pass if the condition is evaluated to true,
            otherwise it will show the condition as the error message
            mu_check(i == 3);
    --> mu_fail(message): will fail and show the message
            mu_fail("this fails");
    --> mu_assert(condition, message): will pass if the condition is true,
            otherwise it will show the failed condition and the message
            mu_assert(i == 3, "i should be equal to three");
    --> mu_assert_int_eq(expected, result): it will pass if the two numbers are
            equal or show their values as the error message

    --> mu_assert_double_eq(expected, result): it will pass if the two values are
            almost equal or show their values as the error message. The value of MINUNIT_EPSILON
            sets the threshold to determine if the values are close enough.
    --> mu_assert_string_eq(expected_str, comparison_str): compares two strings. 

    *!* A _fail TEST EXISTS FOR MOST TESTS. EX: mu_assert_int_eq_fail(expected, result);
*/

// USE GLOBAL VARIABLES FOR TESTING.
// EACH test_UNIT.c FILE SHOULD TEST ONE THING.
t_commandtable	*table_one;
t_commandtable	*table_two;
t_commandtable	*table_three;
char			*line_one;
char			*line_two;
char			*line_three;


void    test_setup(void)
{
    // DEFINE VARIABLES.
	remove("outfile");
	setenv("ARG", "an argument", 1);
	line_one = ft_strdup("echo $ARG | ls >> outfile");
	table_one = parse(line_one);
	remove("outfile");
	remove("infile");
	line_two = ft_strdup("echo < infile |stuff arguments >outfile | foobla");
	table_two = parse(line_two);
	line_three = ft_strdup("");
	table_three = parse(line_three);
}

void    test_teardown(void)
{
    // FREE ALLOCATED MEMORY.
	free_commandtable(table_one);
	free_commandtable(table_two);
	free_commandtable(table_three);
}

MU_TEST(test_set_command_table)
{
	/*--- table_one ---*/
	mu_assert(table_one != NULL, "table was malloc'd improperly.");
	mu_assert(table_one->num_commands == 2, "wrong number of commands");
	mu_assert(table_one->commands != NULL, "commands were malloc'd improperly.");
	mu_assert(table_one->commands[0].input == 0, "input should be stdin.");
	mu_assert(table_one->commands[0].output == table_one->pipe_fd[WRITE_END], "output should be pipe.");
	mu_assert(table_one->commands[1].input == table_one->pipe_fd[READ_END], "input should be pipe.");
	mu_assert(table_one->commands[1].output != 1, "output should not be stdout.");
	mu_assert_string_eq(table_one->commands[0].command, "echo");
	mu_assert_string_eq(table_one->commands[1].command, "ls");
	/*--- table_two ---*/
	mu_assert(table_two != NULL, "table was malloc'd improperly.");
	mu_assert(table_two->num_commands == 3, "wrong number of commands");
	mu_assert(table_two->commands != NULL, "commands were malloc'd improperly.");
	mu_assert(table_two->commands[0].input != 0, "input should not be stdin.");
	mu_assert(table_two->commands[0].output == table_two->pipe_fd[WRITE_END], "output should be pipe.");
	mu_assert(table_two->commands[1].input == table_two->pipe_fd[READ_END], "input should be pipe.");
	mu_assert(table_two->commands[1].output != table_two->pipe_fd[WRITE_END], "output should not be pipe.");
	mu_assert(table_two->commands[1].output != 1, "output should not be stdout.");
	mu_assert(table_two->commands[2].input == table_two->pipe_fd[READ_END], "input should be pipe.");
	mu_assert(table_two->commands[2].output == 1, "output should be stdin.");
	mu_assert_string_eq(table_two->commands[0].command, "echo");
	mu_assert_string_eq(table_two->commands[1].command, "stuff");
	mu_assert_string_eq(table_two->commands[2].command, "foobla");

}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_set_command_table);
}

int main(void)
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return (MU_EXIT_CODE);
}