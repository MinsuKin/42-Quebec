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
    --> mu_assert_string_eq(str1, str2): compares two strings. 

    *!* A _fail TEST EXISTS FOR MOST TESTS. EX: mu_assert_int_eq_fail(expected, result);
*/

// USE GLOBAL VARIABLES FOR TESTING.
// EACH test_UNIT.c FILE SHOULD TEST ONE THING.
char	*line_ok;
// char	*line_pipe_fault;
// char	*line_redirection_fault_one;
// char	*line_redirection_fault_two;

void    test_setup(void)
{
    // DEFINE VARIABLES.
	remove("infile");
	remove("outfile");
	line_ok = ft_strdup("ls | cat < infile | grep 'line' >> outfile");
	// line_pipe_fault = ft_strdup("ls | cat < infile |");
	// line_redirection_fault_one = ft_strdup("ls | cat < infile | >>");
	// line_redirection_fault_two = ft_strdup("<  | cmd -n l | >> infile ");
}

void    test_teardown(void)
{
    // FREE ALLOCATED MEMORY.
	// free(line_ok);
	// free(line_pipe_fault);
	// free(line_redirection_fault_one);
	// free(line_redirection_fault_two);
}

MU_TEST(test_parse)
{
	mu_assert(parse(line_ok) != NULL, "shouldn't return a NULL pointer.");
	// mu_assert(parse(line_pipe_fault) == NULL, "should return a NULL pointer.");
	// mu_assert(parse(line_redirection_fault_one) == NULL, "should return a NULL pointer.");
	// mu_assert(parse(line_redirection_fault_two) == NULL, "should return a NULL pointer.");
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_parse);
}

int main(void)
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return (MU_EXIT_CODE);
}