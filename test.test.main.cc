#include "test.test.hh"
#include <print>

auto main() -> int {
	test_node_print(test_test);
	std::print("\n");
	test_node_print(test_function_run_copy(test_test));
	return 0;
}
