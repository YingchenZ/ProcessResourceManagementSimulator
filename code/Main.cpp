#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <queue>
#include "Manager.h"

void shell(Manager* m, std::vector<std::string> command) {
	int commandLength = command.size();
	if (commandLength == 1) {
		if (command[0] == "in") {
			m->init();
		}
			
		else if (command[0] == "to")
			m->timeout();
		else
			std::cout << "Invalid Command." << std::endl;
	}
	else if (commandLength == 2) {
		if (command[0] == "cr") {
			int priority = std::stoi(command[1]);
			m->create(priority);
		}
		else if (command[0] == "de") {
			int index = std::stoi(command[1]);
			m->destroy(index);
		}
		else
			std::cout << "Invalid Command." << std::endl;
	}
	else if (commandLength == 3) {
		if (command[0] == "rq") {
			int r = std::stoi(command[1]);
			int n = std::stoi(command[2]);
			m->request(r, n);
		}
		else if (command[0] == "rl") {
			int r = std::stoi(command[1]);
			int n = std::stoi(command[2]);
			m->release(r, n);
		}
		else
			std::cout << "Invalid Command." << std::endl;
	}
	else
		std::cout << "Invalid Command." << std::endl;
	return;
}

int main() {
	Manager* m = new Manager();
	std::string fileName;
	std::ifstream inputFile;
	std::cout << "Enter the name of your input file: ";
	std::getline(std::cin, fileName);
	inputFile.open(fileName);
	//inputFile.open("sample-input.txt");
	
	if (!inputFile.is_open()) {
		std::cout << fileName << "not found." << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::vector<std::string> commandVector = {};
	std::string command;
	while (!inputFile.eof()) {
		std::getline(inputFile, command);
		std::stringstream ss(command);
		std::string partialCommand;
		while (ss >> partialCommand) {
			commandVector.push_back(partialCommand);
		}
		if (!commandVector.empty()) {
			try {
				shell(m, commandVector);
			}
			catch (Invalid) {
				m->updateOutput("-1\n");
			}
		}
		else {
			if (m->getOutput()[m->getOutput().size() - 1] != '\n')
				m->updateOutput("\n");
		}
		commandVector.clear();
	}
	
	std::fstream outputFile;
	outputFile.open("output.txt", std::ios::out | std::ios::in);
	if (outputFile.is_open()) {
		outputFile.close();
		outputFile.open("output.txt", std::ios::trunc | std::ios::out);
	}
	else {
		outputFile.close();
		outputFile.open("output.txt", std::ios::out);
	}
	outputFile << m->getOutput();
	std::cout << "Done" << std::endl;
	return 0;
}