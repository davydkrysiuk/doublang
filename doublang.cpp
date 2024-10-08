#include <sstream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>

int line_counter = 0;
int line_current = 0;
std::unordered_map<int, std::string> lines;
std::unordered_map<std::string, int> variables;

void interprete_line(std::string line) {
  std::vector<std::string> words;
  std::istringstream iss(line);
  std::string word;
  while (iss >> word) {
	words.push_back(word);
  }

  if (words[0] == "O1") {
	if (words[1][0] == 'V') {
	  std::cout << variables.find(words[1])->second;
	} else if (words[1] != "\\") {
	  std::cout << words[1];
	} else if (words[1] == "\\") {
	  std::cout << "\n";
	}
  } else if (words[0] == "A0") {
	variables[words[1]] = stoi(words[2]);
  }
}

void load_line(std::string line) {
  if (line[0] != 'X') {
	std::cerr << "Line should start with address X*\n";
	exit(1);
  }
  std::string address_w;
  if(line.find(' ') != std::string::npos) address_w = line.substr(0, line.find(' '));
  address_w.erase(0, 1);

  if (line.find(' ') != std::string::npos) {
	line.erase(0, line.find(' ') + 1);
  }
  int address = std::stoi(address_w);

  lines[address] = line;
}

std::string uncomment(std::string line) {
  return (line.find(';') != std::string::npos) ? line.substr(0, line.find(';')) : line;
}

int main() {
  std::string filename = "1.dl";
  std::ifstream file(filename);

  if (!file.is_open()) {
	std::cerr << "Unable to open the file" << std::endl;
	return 1;
  }
  
  std::string line;
  while (std::getline(file, line)) {
	std::string prepared = uncomment(line);
	load_line(prepared);
	line_counter++;
  }

  for (int i = line_current; i < line_counter; ++i) {
	interprete_line(lines.find(i)->second);
  }

}
