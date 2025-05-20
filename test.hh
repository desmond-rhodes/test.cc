#ifndef TEST_HH
#define TEST_HH

#include <functional>
#include <optional>
#include <source_location>
#include <string>
#include <variant>
#include <vector>

namespace test {
	struct node_t;
	struct error_t;
	using result_t = std::optional<error_t>;
	using function_t = std::function<result_t()>;

	using branch_t = std::vector<node_t>;
	using report_t = std::vector<error_t>;
	using list_t = std::vector<function_t>;

	using origin_t = std::source_location;
	using detail_t = std::vector<std::string>;

	inline auto constexpr success = std::nullopt;
	template<typename ...T> struct fail;

	struct node_t {
		std::string name;
		std::variant<branch_t, report_t, list_t> child;
	};

	struct error_t {
		origin_t origin;
		detail_t detail;
	};

	template<typename ...T>
	struct fail {
		error_t const error;

		operator error_t() const;

		fail(
			detail_t const& detail,
			origin_t const& origin = origin_t::current()
		);

		fail(
			T const&... detail,
			origin_t const& origin = origin_t::current()
		);
	};

	template<typename ...T> fail(T...) -> fail<T...>;
	template<typename ...T> fail(origin_t) -> fail<>;
}

auto test_function_run(test::node_t& node) -> void;

auto test_function_run_copy(
	test::node_t const& node
) -> test::node_t;

auto test_error_print(
	test::error_t const& error,
	bool minimal = false,
	std::string const& indent_origin = "",
	std::string const& indent_detail = "  "
) -> void;

auto test_node_print(
	test::node_t const& node,
	bool minimal = false,
	std::string const& indent = "  "
) -> void;

#include "test.tt"

#endif
