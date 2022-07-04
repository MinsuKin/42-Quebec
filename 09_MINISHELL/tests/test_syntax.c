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

char    *line_odd_quotes;
char	*line_even_quotes;
char	*pipe_no_cmd;
char	*pipe_no_cmd_complex_one;
char	*pipe_no_cmd_complex_two;
char	*pipe_no_cmd_complex_three;
char	*pipe_ok;
char	*pipe_ok_alt;

t_quotestruct	q;

void    test_setup_quotes(void)
{
    line_odd_quotes = ft_strdup("ls | gr\"ep 'fo\"obla' | w'c -l 10 >> outfile");
	line_even_quotes = ft_strdup("ls | grep 'fo\"ob\"la' | wc -l 10 >> outfile");
	q.quote_type = '\0';
	q.within_quotes = 0;
}

void    test_teardown_quotes(void)
{
    free(line_odd_quotes);
	free(line_even_quotes);
}

void    test_setup_pipes(void)
{
    pipe_no_cmd = ft_strdup("ls |     | wc");
	pipe_ok = ft_strdup("ls | grep hello | wc");
	pipe_ok_alt = ft_strdup("cat <infile | foobla -l --arguments | ls >> outfile");
	pipe_no_cmd_complex_one = ft_strdup("  >>  | ls  +|");
	pipe_no_cmd_complex_two = ft_strdup("| +- | stuff");
	pipe_no_cmd_complex_three = ft_strdup(" ls     -n | $VAR foobla || ||");
}

void    test_teardown_pipes(void)
{
    free(pipe_no_cmd);
	free(pipe_ok);
	free(pipe_no_cmd_complex_one);
	free(pipe_no_cmd_complex_two);
	free(pipe_no_cmd_complex_three);
	free(pipe_ok_alt);
}

MU_TEST(test_num_quotes)
{
	//mu_assert(find_num_of_quotes(line_odd_quotes, q) == 5, "should've returned 5.");
    //mu_assert(check_syntax_valid(line_odd_quotes) == 0, "check_syntax() should've returned 0.");
	//mu_assert(find_num_of_quotes(line_even_quotes, q) == 4, "should've returned 4.");
    //mu_assert(check_syntax_valid(line_even_quotes) == 1, "check_syntax() should've returned 1.");
}

MU_TEST(test_pipes)
{
	mu_assert(check_pipe_format_valid(pipe_no_cmd) == 0, "should return 0.");
	mu_assert(check_pipe_format_valid(pipe_ok) == 1, "should return 1.");
	mu_assert(check_pipe_format_valid(pipe_ok_alt) == 1, "should return 1.");
	mu_assert(check_pipe_format_valid(pipe_no_cmd_complex_one) == 0, "should return 0.");
	mu_assert(check_pipe_format_valid(pipe_no_cmd_complex_two) == 0, "should return 0.");
	mu_assert(check_pipe_format_valid(pipe_no_cmd_complex_three) == 0, "should return 0.");
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup_quotes, &test_teardown_quotes);
    MU_RUN_TEST(test_num_quotes);
	MU_SUITE_CONFIGURE(&test_setup_pipes, &test_teardown_pipes);
    MU_RUN_TEST(test_pipes);
}

int main(void)
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return (MU_EXIT_CODE);
}