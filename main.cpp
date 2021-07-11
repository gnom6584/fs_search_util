#include <iostream>

#include <filesystem>
#include <regex>

constexpr const auto RECURSIVE_FLAG = "-r";

constexpr const auto INDEXED_FLAG = "-i";

constexpr const auto HELP_MESSAGE =
	"\nbatya_search [-flags] . [regex] - search in current directory recursively.\n"
	"\nbatya_search [-flags] [directory path] [regex] - search in directory.\n"
	"\nFlags:\n"
	"\n\t-i - search indexed.\n"
	"\n\t-r - search recursively.\n";


using namespace std;

inline void process_directory_entry(const filesystem::directory_entry& dir_entry, const regex& regex, size_t& count, bool indexed) {
	try {
		const auto dir_path = dir_entry.path().native();
		if (regex_match(dir_path, regex)) {
			if (indexed)
				cout << "[" << count << "] ";
			cout << dir_path << endl;
			++count;
		}
	}
	catch (exception& exception) {
		cerr << exception.what() << endl << endl;
	}
}

int main(int argc, char* argv[]) {

	bool indexed = false;
	bool recursive = false;

	if(argc <= 2) {
		cout << HELP_MESSAGE;
		exit(1);
	}

	if(argc > 3)
		for(size_t i = argc - 3; i > 0; --i) {
			if (strcmp(argv[i], INDEXED_FLAG) == 0)
				indexed = true;
			else if (strcmp(argv[i], RECURSIVE_FLAG) == 0)
				recursive = true;
			else {
				cerr << "Invalid flag: " << argv[i] << endl;
				exit(0);
			}
		}

	auto arg_directory = argv[argc - 2];
	auto arg_regex = argv[argc - 1];

	string directory = arg_directory[0] == '.'? filesystem::current_path().string() : arg_directory;

	if(not filesystem::is_directory(directory)) {
		cout << directory << " is not directory!" << endl;
		exit(1);
	}

	cout << endl << "Search in directory = " << directory << ": " << endl << endl;

	regex regex = std::regex(arg_regex);

	size_t count {};

	try {
		if (recursive)
			for (const auto& dir_entry : filesystem::recursive_directory_iterator(directory))
				process_directory_entry(dir_entry, regex, count, indexed);
		else
			for (const auto& dir_entry : filesystem::directory_iterator(directory))
				process_directory_entry(dir_entry, regex, count, indexed);
	}
	catch (exception& exception) {
		cerr << exception.what() << endl << endl;
	}
	if(count == 0)
		cout << "No files found!" << endl;
	else
		cout << endl << count << " files found!" << endl;
	return 0;
}
