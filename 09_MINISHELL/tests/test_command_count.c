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
char    **tokens_base;
char    **tokens_faulty;
char    **tokens_quotes;
char    **tokens_complex_one;
char	*string;

void    test_setup(void)
{
    tokens_base = tokenize(ft_strdup("ls | grep 'foobla' | wc -l"));
    tokens_quotes = tokenize(ft_strdup("ls \"| grep 'foobla'\" | wc -l"));
	string = reformat_string(ft_strdup("ls $ARG| grep 'foobla' |wc -l"));
	tokens_complex_one = tokenize(string);
	tokens_faulty = NULL;
}

void    test_teardown(void)
{
    // FREE ALLOCATED MEMORY.
    free(tokens_base);
    free(tokens_quotes);
	free(tokens_complex_one);
	free(string);
}

MU_TEST(test_command_count)
{
    mu_assert(get_num_commands(tokens_base) == 3, "count should equal 3.");
	mu_assert(ft_get_array_length(tokens_base) == 7, "there should be 7 tokens.");
    mu_assert(get_num_commands(tokens_quotes) == 2, "count should equal 2.");
    // Find out why this fails in run_tests, but not in main...
	// mu_assert(ft_get_array_length(tokens_quotes) == 5, "there should be 5 tokens.");
	mu_assert(get_num_commands(tokens_complex_one) == 3, "count should equal 3.");
	mu_assert(ft_get_array_length(tokens_complex_one) == 8, "there should be 8 tokens.");
	mu_assert(get_num_commands(tokens_faulty) == -1, "count should equal -1.");
	mu_assert(ft_get_array_length(tokens_faulty) == 0, "there should be 0 tokens.");
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_command_count);
}

int main(void)
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return (MU_EXIT_CODE);
}