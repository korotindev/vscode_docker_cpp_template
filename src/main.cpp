#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using namespace std;

void static print_run_help(ostream &out) {
  out << "Please, run me like: \n"
      << "\tfreq in.txt out.txt\n";
}

void static print_wrong_argc_error(ostream &out) {
  out << "Wrong arguments count!\n";
  print_run_help(out);
}

void static print_wrong_input_error(ostream &out) {
  out << "Wrong input file!\n";
  print_run_help(out);
}

void static print_wrong_output_error(ostream &out) {
  out << "Wrong input file!\n";
  print_run_help(out);
}

vector<string> static read_whole_input(ifstream &input) {
  vector<string> result;

  string current_word;

  while (!input.eof()) {
    char sym = static_cast<char>(tolower(input.get()));
    if ('a' <= sym && sym <= 'z') {
      current_word.push_back(sym);
    } else {
      if (!current_word.empty()) {
        result.push_back(move(current_word));
      }
      current_word.clear();
    }
  }

  if (!current_word.empty()) {
    result.push_back(move(current_word));
  }

  return result; // NVRO
}

vector<pair<size_t, string_view>> static calculate_stats(const vector<string> &words) {
  unordered_map<string_view, size_t> prepared_stats;

  for (auto &word : words) {
    prepared_stats[word]++;
  }

  vector<pair<size_t, string_view>> result;

  transform(
      prepared_stats.begin(), prepared_stats.end(), back_inserter(result),
      [](const auto &item) { return make_pair(item.second, item.first); });

  sort(result.begin(), result.end(), [](const auto &lhs, const auto &rhs){
    // sort DESC in first column 
    // sort DESC in second column
    return make_pair(lhs.first, rhs.second) > make_pair(rhs.first, lhs.second);
  });

  return result; // NRVO
}

int main(int argc, char **argv) {
  if (argc != 3) {
    print_wrong_argc_error(cout);
    return 0;
  }

  string input_filename = argv[1], output_filename = argv[2];

  ifstream in(input_filename.c_str());

  if (!in.good()) {
    print_wrong_input_error(cout);
    return 0;
  }

  ofstream out(output_filename.c_str());

  if (!out.good()) {
    print_wrong_output_error(cout);
    return 0;
  }

  auto words = read_whole_input(in);
  auto stats = calculate_stats(words);

  for (auto &[count, word] : stats) {
    out << count << " " << word << "\n";
  }

  return 0;
}
