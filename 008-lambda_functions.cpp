#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  vector<string> v{"cat", "dog", "ox", "kitten", "puppy"};

  string suffix{"!"};
  string prefix{"foo."};
  int n = 0;

  // Capture a copy of suffix and a reference of n
  auto suffix_lambda = [suffix, &n](const string &s) {
    ++n;
    return s + suffix;
  };
  // Capture prefix by reference
  auto prefix_lambda = [&prefix](const string &s) { return prefix + s; };
  // Capture everything by reference
  auto lambda = [&](const string &s) { cout << prefix << s << suffix << endl; };
  // Capture everything by value
  auto vlambda = [=](const string &s) {
    cout << prefix << s << suffix << endl;
  };

  /* 
  auto nlambda = [n]() {
    ++n;
    cout << n << endl;
  };

  This is equivalent to:

  struct Lambda {
    Lambda(const int &num) : n(num) {}
    Lambda(const Lambda &) = delete;

    auto operator()() const {
      ++n;
      cout << n << endl;
    }

  private:
    int n;
  };

  n is not modifiable because it uses const function body, 
  but you can override this behaviour using the "mutable" keyword:
  */
  
  auto nlambda = [n]() mutable {
    ++n;
    cout << "nlambda.n = " << n << endl;
  };
  /*
  Note: nlambda is a class and n here is a data member
  */
  for (int i = 0; i < 5; ++i) {
    nlambda();
  }

  lambda("hi");
  vlambda("hi");

  // Change suffix and prefix to see if they change in the lambdas
  suffix = "?";
  prefix = "bar.";

  lambda("bye");
  vlambda("bye");

  cout << "n before = " << n << endl;

  transform(v.begin(), v.end(), v.begin(), suffix_lambda);
  transform(v.begin(), v.end(), v.begin(), prefix_lambda);

  cout << "n after = " << n << endl;

  for (const auto &e : v) {
    cout << e << endl;
  }
}
