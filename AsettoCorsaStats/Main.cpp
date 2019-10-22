#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

int main(void) 
{
	std::cout << "Hello World!" << std::endl;
	std::ifstream myfile;
	std::string aux;
	std::string auxCar;
	std::string auxTrack;
	std::vector<std::string> tracks;
	std::vector<std::string> cars;
	std::vector<std::string> tokens;
	std::vector<std::pair<std::string, std::string>> Combos;
	std::map<std::pair<std::string, std::string>, int> Laptimes;
	int seperatorLocation = 0;
	int auxLength = 0;
	int ComboCounter = 0;

	myfile.open("personalbest.ini");
	if (!myfile.is_open())
	{
		std::cout << "File not found" << std::endl;
		myfile.close();
		return 0;
	}
	if (myfile.is_open())
	{
		for (std::string each; std::getline(myfile, each, '\n'); tokens.push_back(each));
		for (unsigned int i = 0; i < tokens.size(); i++)
		{
			if (i % 4 == 0) //COMBO-Line
			{
				aux = tokens[i];
				seperatorLocation = aux.find('@');
				auxCar = aux.substr(1, (seperatorLocation - 1));
				auxLength = aux.length() - auxCar.length();
				auxLength-= 3;
				auxTrack = aux.substr((seperatorLocation + 1), auxLength);
				if (std::find(cars.begin(), cars.end(), auxCar) != cars.end()) 
				{
					std::cout << "Car already in!" << std::endl;
				}
				else 
				{
					cars.push_back(auxCar);
					std::cout << "Car added!" << std::endl;
				}
				if (std::find(tracks.begin(), tracks.end(), auxTrack) != tracks.end())
				{
					std::cout << "Track already in!" << std::endl;
				}
				else
				{
					tracks.push_back(auxTrack);
					std::cout << "Track added!" << std::endl;
				}
				Combos.push_back(std::make_pair(auxCar, auxTrack));

			}
			else if (i % 4 == 1) //DATE-Line
			{
			}
			else if (i % 4 == 2) //TIME-Line
			{
				aux = tokens[i];
				Laptimes[Combos[Combos.size()-1]] = stoi(aux.substr(5));

				std::cout << Laptimes[Combos[Combos.size()-1]] << std::endl;
			}
		}
		std::sort(cars.begin(), cars.end());
		std::sort(tracks.begin(), tracks.end());
		std::cout << "Cars: " << cars.size() << std::endl;
		std::cout << "Tracks: " << tracks.size() << std::endl;
		std::sort(Combos.begin(), Combos.end());
		for (unsigned int i = 0; i < Combos.size(); i++)
		{
			std::cout << Combos[i].first << std::endl << Combos[i].second << std::endl;
			std::cout << Laptimes[Combos[i]] << std::endl;
		}
	}
	
	myfile.close();
	return 0;

}