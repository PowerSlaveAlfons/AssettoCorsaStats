#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <algorithm>

int main(void) 
{
	std::cout << "Hello World!" << std::endl;
	std::ifstream myfile;
	std::ofstream output("output.csv");
	std::string aux;
	std::string auxCar;
	std::string auxTrack;
	std::vector<std::string> Tracks;
	std::vector<std::string> Cars;
	std::vector<std::string> tokens;
	std::vector<std::pair<std::string, std::string>> Combos;
	std::vector<std::pair<std::string, std::string>> EmptyCombos;
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
				seperatorLocation = (int)aux.find('@');
				auxCar = aux.substr(1, (seperatorLocation - (size_t)1)); //nice "warning", VS
				auxLength = (int)aux.length() - (int)auxCar.length();
				auxLength-= 3;
				auxTrack = aux.substr((seperatorLocation + (size_t)1), auxLength);
				if (!(std::find(Cars.begin(), Cars.end(), auxCar) != Cars.end())) 
				{
					Cars.push_back(auxCar);
				}
				if (!(std::find(Tracks.begin(), Tracks.end(), auxTrack) != Tracks.end()))
				{
					Tracks.push_back(auxTrack);
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
			}
		}

		std::sort(Cars.begin(), Cars.end());
		std::sort(Tracks.begin(), Tracks.end());
		for (auto car : Cars)
		{
			for (auto track : Tracks)
			{
				if (!(std::find(Combos.begin(), Combos.end(), std::make_pair(car, track)) != Combos.end()))
				{
					EmptyCombos.push_back(std::make_pair(car, track));
				}
			}
			std::cout << car << std::endl;
		}
		int Comby = (int)Combos.size();
		for (auto combo : EmptyCombos)
		{
			Combos.push_back(combo);
			Laptimes[Combos[Combos.size() - 1]] = -1;
		}

		std::cout << "Cars: " << Cars.size() << std::endl;
		std::cout << "Tracks: " << Tracks.size() << std::endl;
		std::sort(Combos.begin(), Combos.end());
		output << "x,";
		for (auto track : Tracks)
		{
			output << track << ',';
		}
		output << std::endl;
		for (int i = 0; i < Cars.size(); i++)
		{
			output << Cars[i] << ',';
			for (int j = 0; j < Tracks.size(); j++)
			{
				output << Laptimes[Combos[i * Tracks.size()+j]] << ',';
			}
			output << std::endl;
		}

		std::vector<std::pair<std::string, std::string>> out;
		std::sample(EmptyCombos.begin(), EmptyCombos.end(), std::back_inserter(out), 1, std::mt19937{ std::random_device{}() });
		std::cout << "Here's a combo you haven't driven: " << out[0].first << " at " << out[0].second << std::endl;
		std::cout << "You have yet to drive " << EmptyCombos.size() << " combinations." << std::endl;
		std::cout << "You have already driven " << Comby << " combinations." << std::endl;


	}
	
	myfile.close();
	return 0;

}