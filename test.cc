#include "test.hh"

auto test_function_run(test::node_t& node) -> void {
	if (node.child.index() == 0)
		for (auto& subnode : std::get<test::branch_t>(node.child))
			test_function_run(subnode);
	else if (node.child.index() == 2) {
		test::report_t report;
		for (auto const& function : std::get<test::list_t>(node.child)) {
			auto const error_opt = function();
			if (error_opt)
				report.push_back(*error_opt);
		}
		node.child = report;
	}
}

auto test_function_run_copy(
	test::node_t const& node
) -> test::node_t {
	auto node_copy = test::node_t {node};
	test_function_run(node_copy);
	return node_copy;
}

#include <print>

auto test_error_print(
	test::error_t const& error,
	bool minimal,
	std::string const& indent_origin,
	std::string const& indent_detail
) -> void {
	std::print(
		"{}{}({}:{})\n",
		indent_origin,
		error.origin.file_name(),
		error.origin.line(),
		error.origin.column()
	);
	if (!minimal)
		for (auto const& more : error.detail)
			std::print("{}{}\n", indent_detail, more);
}

auto test_node_print(
	std::vector<std::string>& indent,
	test::node_t const& node,
	bool minimal,
	std::size_t depth
) -> void {
	while (indent.size() < depth + 3)
		indent.push_back(indent.back() + indent[1]);
	std::print("{}{}\n", indent[depth], node.name);
	if (node.child.index() == 0)
		for (auto const& subnode : std::get<test::branch_t>(node.child))
			test_node_print(indent, subnode, minimal, depth + 1);
	else if (node.child.index() == 1)
		for (auto const& error : std::get<test::report_t>(node.child))
			test_error_print(
				error, minimal, indent[depth + 1], indent[depth + 2]
			);
	else if (node.child.index() == 2)
		if (!minimal)
			for (auto const& _ : std::get<test::list_t>(node.child))
				std::print("{}function\n", indent[depth + 1]);
}

auto test_node_print(
	test::node_t const& node,
	bool minimal,
	std::string const& indent
) -> void {
	auto indent_cache = std::vector<std::string> {"", indent};
	test_node_print(indent_cache, node, minimal, 0);
}
