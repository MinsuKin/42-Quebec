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
/*--- whitespace remove ---*/
char    *single_whitespace_end;
char    *single_whitespace_front;
char    *double_whitespace_end;
char    *double_whitespace_middle;
char    *complex_one;
char    *complex_two;
char	*complex_three;

/*--- whitespace add ---*/
char    *redirect;
char    *redirect_alt;
char    *pipes;
char    *complex;

void    test_whitespace_remove_setup(void)
{
    single_whitespace_end = ft_strdup("ls | wc -l ");
    single_whitespace_front = ft_strdup(" ls | wc -l");
    double_whitespace_end = ft_strdup("ls | wc -l  ");
    double_whitespace_middle = ft_strdup("ls |   wc -l");
    double_whitespace_middle = ft_strdup("ls |   wc -l");
    complex_one = ft_strdup(" ls   |   wc -l  ");
    complex_two = ft_strdup(" ls   |   wc -l  >>    outfile");
	complex_three = ft_strdup("echo i==3| set BLARGUMENT | unset an argument>>hello");
}

void    test_whitespace_remove_teardown(void)
{
    free(single_whitespace_end);
    free(single_whitespace_front);
    free(double_whitespace_end);
    free(double_whitespace_middle);
    // free(complex_one);
    // free(complex_two);
}

void    test_whitespace_add_setup(void)
{
    redirect = ft_strdup("ls>>outfile");
    redirect_alt = ft_strdup("cat|grep 'foo'<infile>>outfile");
    pipes = ft_strdup("ls|cat|grep -l");
    complex = ft_strdup("ls|cat>>outfile <infile");
}

void    test_whitespace_add_teardown(void)
{
    free(redirect);
	free(redirect_alt);
    free(pipes);
    free(complex);
}

MU_TEST(test_add_with_redirect)
{
    mu_assert(strcmp(add_whitespace(redirect, find_len_added_whitespace(redirect)), "ls >> outfile") == 0, "strings should be equal");
    mu_assert(strcmp(add_whitespace(redirect_alt, find_len_added_whitespace(redirect_alt)), "cat | grep 'foo' < infile >> outfile") == 0, "strings should be equal");
}

MU_TEST(test_add_with_pipe)
{
    mu_assert(strcmp(add_whitespace(pipes, find_len_added_whitespace(pipes)), "ls | cat | grep -l") == 0, "strings should be equal");
}

MU_TEST(test_add_complex)
{
    mu_assert(strcmp(add_whitespace(complex, find_len_added_whitespace(complex)), "ls | cat >> outfile < infile") == 0, "strings should be equal");
}

MU_TEST(test_len_no_whitespace)
{
    mu_assert(find_len_no_whitespace(single_whitespace_end) == 10, "should've returned 10.");
    mu_assert(find_len_no_whitespace(single_whitespace_front) == 10, "should've returned 10.");
    mu_assert(find_len_no_whitespace(double_whitespace_end) == 10, "should've returned 10.");
    mu_assert(find_len_no_whitespace(double_whitespace_middle) == 10, "should've returned 10.");
    mu_assert(find_len_no_whitespace(complex_one) == 10, "should've returned 10.");
    mu_assert(find_len_no_whitespace(complex_one) == 10, "should've returned 20.");
}

MU_TEST(test_string_no_whitespace)
{
    mu_assert(strcmp(remove_whitespace(single_whitespace_end, find_len_no_whitespace(single_whitespace_end)), "ls | wc -l") == 0, "should've returned 10.");
    mu_assert(strcmp(remove_whitespace(single_whitespace_front, find_len_no_whitespace(single_whitespace_front)), "ls | wc -l") == 0, "should've returned 10.");
    mu_assert(strcmp(remove_whitespace(double_whitespace_end, find_len_no_whitespace(double_whitespace_end)), "ls | wc -l") == 0, "should've returned 10.");
    mu_assert(strcmp(remove_whitespace(double_whitespace_middle, find_len_no_whitespace(double_whitespace_middle)), "ls | wc -l") == 0, "should've returned 10.");
    mu_assert(strcmp(remove_whitespace(complex_one, find_len_no_whitespace(complex_one)), "ls | wc -l") == 0, "should've returned 10.");
    mu_assert(strcmp(remove_whitespace(complex_two, find_len_no_whitespace(complex_two)), "ls | wc -l >> outfile") == 0, "should've returned 20.");
}

MU_TEST(test_reformat_string)
{
    mu_assert_string_eq("ls | wc -l", reformat_string(single_whitespace_end));
    mu_assert_string_eq("ls | wc -l", reformat_string(single_whitespace_front));
    mu_assert_string_eq("ls | wc -l", reformat_string(double_whitespace_end));
    mu_assert_string_eq("ls | wc -l", reformat_string(double_whitespace_middle));
    mu_assert_string_eq("ls | wc -l", reformat_string(complex_one));
    mu_assert_string_eq("ls | wc -l >> outfile", reformat_string(complex_two));
	mu_assert_string_eq("echo i==3 | set BLARGUMENT | unset an argument >> hello", reformat_string(complex_three));
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_whitespace_remove_setup, &test_whitespace_remove_teardown);
    MU_RUN_TEST(test_len_no_whitespace);
    MU_RUN_TEST(test_string_no_whitespace);
    MU_RUN_TEST(test_reformat_string);
    MU_SUITE_CONFIGURE(&test_whitespace_add_setup, &test_whitespace_add_teardown);
    MU_RUN_TEST(test_add_with_redirect);
    MU_RUN_TEST(test_add_with_pipe);
    MU_RUN_TEST(test_add_complex);
}

int main(void)
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return (MU_EXIT_CODE);
}