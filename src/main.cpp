#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>

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

vector<pair<size_t, string>> static calculate_stats(ifstream &input) {
  vector<pair<size_t, string>> result;
  unordered_map<string, size_t> prepared_stats;
  
  string current_word;

  while (!input.eof()) {
    char sym = tolower(input.get());
    if ('a' <= sym && sym <= 'z') {
      current_word.push_back(sym);
    } else {
      if (!current_word.empty()) {
        prepared_stats[current_word]++;
      }
      current_word.clear();
    }
  }

  if (!current_word.empty()) {
    prepared_stats[current_word]++;
  }

  transform(
      prepared_stats.begin(), prepared_stats.end(), back_inserter(result),
      [](const auto &item) { return make_pair(item.second, item.first); });

  sort(result.begin(), result.end(), greater<>());

  return result; // NRVO
}

int main(int argc, char **argv) {
  if (argc != 3) {
    print_wrong_argc_error(cout);
    return 0;
  }

  string input_filename = argv[1], output_filename = argv[2];

  if (!filesystem::exists(input_filename)) {
    print_wrong_input_error(cout);
    return 0;
  }

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

  auto stats = calculate_stats(in);

  for (auto &[count, word] : stats) {
    out << count << " " << word << "\n";
  }

  return 0;
}
