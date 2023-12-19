#include <iostream>
#include <string>

int main(int argc, char **argv){
	if(argc == 1){
		std::cerr << "Error: Arguments needed" << std::endl;
		return 0;
	}

	std::string day_num = argv[1];
	std::string geturl = "https://adventofcode.com/2023/day/" + day_num + "/input";
	std::string cookies = "session=53616c7465645f5ff784101bd41356d91d49ec9622b01e9b562a7614dcd35d3e8d211536f5bd7e693af62f414e591a98a65f75c597e4e1e78b2e96d728242e2a;";
	std::string curl_command = "curl " + geturl + " --cookie \"" + cookies + "\"" + " -o data.in";

	int result = system(curl_command.c_str());

	return 0;
}