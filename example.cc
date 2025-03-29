#include <print>
#include <string>
#include <vector>

auto main(int const argc, char const* const* const argv) -> int {
	auto const args = std::vector<std::string>{argv+1, argv+argc};

	for (auto const& i : args)
		std::print("{}\n", i);

	std::print("Hello, world!\n");
	return 0;
}
