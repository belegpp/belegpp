#include "belegpp.h"
#include "belegpp_sf.h"
#include <iostream>
#include <cassert>
#include <time.h>
#include <map>

using namespace beleg::lambdas;
using namespace beleg::helpers::print;
using namespace beleg::extensions::strings;
using namespace beleg::extensions::containers;

int main()
{
	{
		std::string test("TEST");
		assert((test | toLower()) == "test");
		assert(("TEST" | toLower()) == "test");
	}
	{
		std::string test("test");
		assert((test | toUpper()) == "TEST");
		assert(("test" | toUpper()) == "TEST");
	}
	{
		std::string test("n");
		assert((test * 3) == "nnn");
		assert(("n" | mul(3)) == "nnn");
	}
	{
		std::string test("");
		assert(!test == true);
		assert(!!test == false);
	}
	{
		std::string test("test");
		assert((test | replace("t", "s")) == "sess");
		assert(("test" | replace("t", "s")) == "sess");
	}
	{
		std::string test("test,test");
		assert((test | split(",")).size() == 2);
		assert(("test,test" | split(",")).size() == 2);
	}
	{
		std::string test("sometest");
		assert((test | startsWith("some")) == true);
		assert(("sometest" | startsWith("some")) == true);
	}
	{
		std::string test("sometest");
		assert((test | endsWith("test")) == true);
		assert(("sometest" | endsWith("test")) == true);
	}
	{
		std::string test("TEST");
		assert((test | equalsIgnoreCase("tEst")) == true);
		assert(("TEST" | equalsIgnoreCase("tEst")) == true);
	}
	{
		std::string test("    test  ");
		assert((test | trim()) == "test");
		assert(("    test  " | trim()) == "test");
	}
	{
		std::string test("test");
		assert((test | contains("es")) == true);
		assert(("test" | contains("es")) == true);
	}
	{
		std::vector<int> test = { 1, 2, 3 };
		assert((test | contains(2)) == true);
	}
	{
		std::map<int, int> test = { {1,2} };
		assert((test | containsKey(1)) == true);
		assert((test | containsItem(2)) == true);
	}
	{
		std::vector<std::string> test = { "One", "Two" };
		auto mapped = test | map([](auto& item) { return "Number " + item; });
		assert(mapped.at(0) == "Number One");

		auto x = QuickPlaceholder<0>{};
		auto mapped2 = test | map("Number " + x);
		assert(mapped2.at(0) == "Number One");
	}
	{
		std::vector<int> test = { 1, 2, 3, 4, 5, 6 };
		auto filtered = test | filter([](auto& item) { return item % 2 == 0; });
		assert((filtered.at(1) == 4));

		auto x = QuickPlaceholder<0>{};
		auto filtered2 = test | filter((x % 2) == 0);
		assert((filtered2.at(1) == 4));
	}
	{
		std::vector<int> test = { 1 };
		test | forEach([](auto& item) { assert(item == 1); });
		
		auto x = QuickPlaceholder<0>{};
		test | forEach(x = 5);

		assert(test.at(0) == 5);
	}
	{
		std::vector<int> test = { 1,2,3 };
		auto it = test | find(2);
		assert(it);
		assert(**it == 2);
	}
	{
		std::vector<int> test = { 1,2,3 };
		auto it = test | findIf([](auto& item) { return item % 2 == 0; });
		assert(it);
		assert(**it == 2);
		
		auto x = QuickPlaceholder<0>{};
		auto it2 = test | findIf((x % 2) == 0);
		assert(it2);
		assert(**it2 == 2);
	}
	{
		std::vector<int> test = { 1,2,3 };
		auto reversed = test | reverse();
		assert(reversed.at(0) == 3);
	}
	{
		std::vector<int> test = { 1, 2, 3 };
		test | beleg::extensions::containers::remove(2);
		assert(test.at(1) == 3);
	}
	{
		std::vector<int> test = { 1,2,3,4 };
		test | removeIf([](auto& item) { return item % 2 == 0; });
		assert(test.at(1) == 3);
		
		std::vector<int> test2 = { 1,2,3,4 };
		auto x = QuickPlaceholder<0>{};
		test2 | removeIf((x % 2) == 0);
		assert(test2.at(1) == 3);
	}
	{
		std::vector<int> test = { 1, 2, 3 };
		test | removeAt(1);
		assert(test.at(1) == 3);
	}
	{
		std::vector<int> test = { 1, 2, 3 };
		auto sorted = test | sort([](auto& first, auto& second) { return first > second; });
		assert(sorted.at(0) == 3);

		auto x = QuickPlaceholder<0>{};
		auto x2 = QuickPlaceholder<1>{};
		auto sorted2 = test | sort(x > x2);
		assert(sorted2.at(0) == 3);
	}
	{
		std::vector<int> test = { 1, 2, 3, 4, 5 };
		assert((test | some([](auto item) {return item % 2 == 0; })) == true);
		
		auto x = QuickPlaceholder<0>{};
		assert((test | some((x % 2) == 0)) == true);
	}
	{
		std::vector<int> test = { 1, 2, 3, 4, 5 };
		assert((test | every([](auto item) {return item % 2 == 0; })) == false);
	
		auto x = QuickPlaceholder<0>{};
		assert((test | every((x % 2) == 0)) == false);
	}
	{
		std::vector<int> test = { 1, 2, 3, 4, 5, 6 };
		auto sliced = test | slice(1, -1);
		assert(sliced.at(0) == 2);
		assert(sliced.at(3) == 5);
	}
	{
		//Well, this may fail sometimes but hey
		std::vector<int> test = { 1, 2, 3 };
		auto shuffled = test | shuffle();
		bool success = false;
		for (int i = 0; 100 > i; i++)
		{
			if (shuffled != test)
				success = true;
		}
		assert(success == true);
	}
	{
		std::vector<int> test = { 1, 2, 3, 4, 5, 6 };
		std::stringstream sstr;
		sstr << test;
		assert(sstr.str().size() > 0);
	}
	{
		std::vector<int> test = { 1,2,3 };
		auto res = test | mapTo<std::vector<std::string>>([](auto& item) { return std::to_string(item); });
		assert(res.at(0) == "1");
	}
	{
		println("belegpp - current time: ", time(0));
	}
	{
		printfln("[1] Test: %i", 10);
	}
	{
		std::stringstream sstream;
		printfln(sstream, "[2] Test: %i", 20);
		assert(sstream.str() == "[2] Test: 20\n");
	}
	{
		auto result = printfs("[4] Test: %i", 40);
		assert(result == "[4] Test: 40");
	}
	{
		auto result = printfsln("[5] Test: %i", 50);
		assert(result == "[5] Test: 50\n");
	}
	{
		std::vector<int> test = { 1,2,3 };
		auto result = test | join();
		assert(result == "123");
	}
	{
		std::map<std::string, int> test = { {"one", 1},{"two", 2},{"three", 3} };
		auto result = test | join("...");
		assert(result == "[one,1]...[three,3]...[two,2]");
	}

	std::cout << "Tests finished!" << std::endl;
	return 0;
}