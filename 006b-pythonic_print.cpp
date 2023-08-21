#include <iostream>
#include <string>
#include <tuple>
#include <type_traits> // for std::false_type and std::true_type
using namespace std;

// A struct that holds the sep and end parameters
struct PrintOptions {
	string sep;
	string end;
};

// A custom type trait that checks if a type is a PrintOptions struct or not
template <typename T> struct is_print_options : false_type {};
template <> struct is_print_options<PrintOptions> : true_type {};

// A helper function that prints a single argument with a separator
// This version is enabled only when the argument is not a PrintOptions struct
template <typename T> void print_arg(T arg, const string &sep) {
	if constexpr (!is_print_options<T>::value) {
		cout << arg << sep;
	}
}

// A variadic template function that can print any number of arguments
// This version uses fold expressions to iterate over the arguments
template <typename... Args> void print(Args... args) {
	string sep = " ";
	string end = "\n";
	
	// Check if there are any arguments
	if constexpr (sizeof...(args) > 0) {
		// Get the last argument
		auto last = get<sizeof...(args) - 1>(forward_as_tuple(args...));
		
        // Check if the last argument is a PrintOptions struct
		if constexpr (is_print_options<decltype(last)>::value) {
			// If so, use its sep and end values
			sep = last.sep;
			end = last.end;
		}
			
		// Use a fold expression to print all the arguments
		(print_arg(args, sep), ...);
		
		// Print the end
		cout << end;
	}
}

// A test program
int main() {
	// Examples of using the print function
	print("Hello, world!");
	print(42);
	print(3.14, "is", "pi");
	print("This", "is", "a", "sentence", ".", PrintOptions{"-", "!\n\n"});

	return 0;
}
