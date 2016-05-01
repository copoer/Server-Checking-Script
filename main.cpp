/*
 * System Status Report
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <unistd.h>  

using namespace std;

//Talk Away
int espeak(string mess) {
	string command ("espeak '");
	string speak = mess;
	string end ("'");
	string all;
	all = command + speak + end;
	system((all).c_str());
	return 0;
}

int display(string mess) {
	string command ("figlet '");
	string speak = mess;
	string end ("'");
	string all;
	all = command + speak + end;
	system((all).c_str());
	return 0;
}

char test(string location) {
	string command ("curl -s ");
	string end (" >/dev/null && echo 1 || echo 0");
	string all;
	all = command + location + end;

	FILE *output = popen((all).c_str(), "r");
	char buffer[1024];
	char *out = fgets(buffer, sizeof(buffer),output);
	pclose(output);
	return *out;
}

int list(string ip, string domain) {
	string all;
	string speaks;
	string speak = " is Down!";
	speaks = domain + speak;

	char a = test(ip);
	if(a == '1') {
		all = domain + " : UP";
		display((all).c_str());
	} else {
		all = domain + " : DOWN";
		display((all).c_str());
		int n = 1;
		while (n>0) {
			espeak(speaks);
			sleep(5);
		}
	}
}

int main() {
	int n = 1;
	while (n>0) {	
		system("clear");
		list("IPADDRESS:PORT", "NAME OF SERVER");
		sleep(60);
	}
	return 0;
}

