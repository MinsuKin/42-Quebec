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
t_commandtable	*table;
char			**tokens;
char			*string;

void    test_setup(void)
{
    // DEFINE VARIABLES.
	string = ft_strdup("echo stuff | wc -l");
	tokens = tokenize(string);
	table = set_commandtable(tokens);
}

void    test_teardown(void)
{
    // FREE ALLOCATED MEMORY.
	// ft_free_carray(tokens);
	// free_commandtable(table);
}

MU_TEST(test_set_pipes)
{
    // CHANGE PLACEHOLDER NAME
    // ADD ASSERT CALLS.
	mu_assert(STDIN_FILENO == table->commands[0].input, "input should be stdin.");
	mu_assert(table->pipe_fd[WRITE_END] == table->commands[0].output, "output should be pipe[write_end].");
	mu_assert(table->pipe_fd[READ_END] == table->commands[1].input, "input should be pipe[read_end].");
	mu_assert(STDOUT_FILENO == table->commands[1].output, "output should be stdout.");
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_set_pipes);
}

int main(void)
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return (MU_EXIT_CODE);
}