#include "test.test.hh"

auto const test_test = test::node_t {"main", test::branch_t {
	{"report error", test::report_t {
		test::fail({"construct with vector"}),
		test::fail(),
		test::fail("construct with template")
	}},
	{"list function success", test::list_t {
		[] static { return test::success; },
	}},
	{"list function fail", test::list_t {
		[] static { return test::fail({"construct with vector"}); },
		[] static { return test::fail(); },
		[] static { return test::fail("construct with template"); }
	}},
	{"branch empty", test::branch_t {}},
	{"report empty", test::report_t {}},
	{"list empty", test::list_t {}},
	{"report error current()", test::report_t {
		test::fail(
			{"construct with vector"},
			test::origin_t::current()
		),
		test::fail(test::origin_t::current()),
		// test::fail(
		// 	"construct with template",
		// 	test::origin_t::current()
		// )
	}},
	{"list function fail current()", test::list_t {
		[] static {
			return test::fail(
				{"construct with vector"},
				test::origin_t::current()
			);
		},
		[] static {
			return test::fail(test::origin_t::current());
		},
		// [] static {
		// 	return test::fail(
		// 		"construct with template",
		// 		test::origin_t::current()
		// 	);
		// }
	}}
}};
