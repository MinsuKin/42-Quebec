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

// Loops
int		i;

// add_to_array() setup
char	**array_one;
char	*insert_one;
char	*comparison_one;
char	**array_two;
char	*insert_two;
char	*comparison_two;

// tokenize() setup
char	**array_tokenize_one;
char	**array_comparison_one;
char	*line_tokenize_one;
char	**array_tokenize_two;
char	**array_comparison_two;
char	*line_tokenize_two;
char	**array_tokenize_three;
char	**array_comparison_three;
char	*line_tokenize_three;
char	**array_tokenize_four;
char	**array_comparison_four;
char	*line_tokenize_four;
char	**array_tokenize_five;
char	**array_comparison_five;
char	*line_tokenize_five;
char	**array_tokenize_six;
char	**array_comparison_six;
char	*line_tokenize_six;

void    test_setup_add(void)
{
    // DEFINE VARIABLES.
	array_one = ft_calloc(2, sizeof(char *));
	array_one[0] = ft_strdup("echo");
	insert_one = ft_strdup("-n");
	comparison_one = ft_strdup(insert_one);
	
	array_two = NULL;
	insert_two = ft_strdup("echo");
	comparison_two = ft_strdup(insert_two);
}

void    test_teardown_add(void)
{
    // FREE ALLOCATED MEMORY.
	ft_free_carray(array_one);
	free(comparison_one);
	ft_free_carray(array_two);
	free(comparison_two);
}

void    test_setup_tokenize(void)
{
    // DEFINE VARIABLES.
	array_tokenize_one = NULL;
	array_comparison_one = ft_split("echo stuff | grep bla", ' ');
	line_tokenize_one = reformat_string(ft_strdup("echo stuff | grep bla"));
	array_tokenize_two = NULL;
	array_comparison_two = ft_split("echo stuff | grep bla", ' ');
	line_tokenize_two = reformat_string(ft_strdup("echo stuff|grep bla"));
	array_tokenize_three = NULL;
	array_comparison_three = ft_split("echo stuff | grep bla", ' ');
	line_tokenize_three = reformat_string(ft_strdup("echo stuff |grep bla"));
	array_tokenize_four = NULL;
	array_comparison_four = ft_calloc(4, sizeof(char *));
	array_comparison_four[0] = "echo";
	array_comparison_four[1] = "stuff | grep";
	array_comparison_four[2] = "bla";
	line_tokenize_four = reformat_string(ft_strdup("echo 'stuff | grep' bla"));
	array_tokenize_five = NULL;
	array_comparison_five = ft_calloc(4, sizeof(char *));
	array_comparison_five[0] = "echo";
	array_comparison_five[1] = "stuff | grep";
	array_comparison_five[2] = "bla";
	line_tokenize_five = reformat_string(ft_strdup("echo \"stuff | grep\" bla"));
	array_tokenize_six = NULL;
	array_comparison_six = ft_calloc(6, sizeof(char *));
	array_comparison_six[0] = "echo";
	array_comparison_six[1] = "$ARG";
	array_comparison_six[2] = "|";
	array_comparison_six[3] = "echo";
	array_comparison_six[4] = "foobla";
	line_tokenize_six = reformat_string(ft_strdup("echo $ARG | echo foobla"));
}

void    test_teardown_tokenize(void)
{
    // FREE ALLOCATED MEMORY.
	ft_free_carray(array_tokenize_one);
	ft_free_carray(array_comparison_one);
	free(line_tokenize_one);
	ft_free_carray(array_tokenize_two);
	ft_free_carray(array_comparison_two);
	free(line_tokenize_two);
	ft_free_carray(array_tokenize_three);
	ft_free_carray(array_comparison_three);
	free(line_tokenize_three);
	ft_free_carray(array_tokenize_four);
	// ft_free_carray(array_comparison_four);
	free(line_tokenize_four);
	ft_free_carray(array_tokenize_five);
	// ft_free_carray(array_comparison_five);
	free(line_tokenize_five);
	ft_free_carray(array_tokenize_six);
	// ft_free_carray(array_comparison_six);
	free(line_tokenize_six);
}

MU_TEST(test_add_to_array)
{
    // CHANGE PLACEHOLDER NAME
    // ADD ASSERT CALLS.
	array_one = add_to_array(array_one, insert_one);
	mu_assert_string_eq("echo", array_one[0]);
	mu_assert_string_eq(comparison_one, array_one[1]);
	mu_assert_string_eq(NULL, array_one[2]);
	array_two = add_to_array(array_two, insert_two);

}

MU_TEST(test_tokenize)
{
    // CHANGE PLACEHOLDER NAME
    // ADD ASSERT CALLS.
	array_tokenize_one = tokenize(line_tokenize_one);
	i = -1;
	while (array_comparison_one[++i] && array_tokenize_one[i])
		mu_assert_string_eq(array_comparison_one[i], array_tokenize_one[i]);
	array_tokenize_two = tokenize(line_tokenize_two);
	i = -1;
	while (array_comparison_two[++i] && array_tokenize_two[i])
		mu_assert_string_eq(array_comparison_two[i], array_tokenize_two[i]);
	array_tokenize_three = tokenize(line_tokenize_three);
	i = -1;
	while (array_comparison_three[++i] && array_tokenize_three[i])
		mu_assert_string_eq(array_comparison_three[i], array_tokenize_three[i]);
	array_tokenize_four = tokenize(line_tokenize_four);
	i = -1;
	while (array_comparison_four[++i] && array_tokenize_four[i])
		mu_assert_string_eq(array_comparison_four[i], array_tokenize_four[i]);
	array_tokenize_five = tokenize(line_tokenize_five);
	i = -1;
	while (array_comparison_five[++i] && array_tokenize_five[i])
		mu_assert_string_eq(array_comparison_five[i], array_tokenize_five[i]);
	array_tokenize_six = tokenize(line_tokenize_six);
	i = -1;
	while (array_comparison_six[++i] && array_tokenize_six[i])
		mu_assert_string_eq(array_comparison_six[i], array_tokenize_six[i]);
}

MU_TEST_SUITE(test_suite)
{
    MU_SUITE_CONFIGURE(&test_setup_add, &test_teardown_add);
    MU_RUN_TEST(test_add_to_array);
	MU_SUITE_CONFIGURE(&test_setup_tokenize, &test_teardown_tokenize);
	MU_RUN_TEST(test_tokenize);
}

int main(void)
{
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return (MU_EXIT_CODE);
}