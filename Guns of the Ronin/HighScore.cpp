
#include "HighScore.h"
#include <fstream>
#include <iostream>
#include <algorithm>


int curHighScore = 0;

//The max amount of time the player needs to finish all 10 waves by
//in order to earn bonus score from time
int maxTimeBonus = 15.0f * 60.0f;

//the bonus score from time, only playthroughs that cleared all waves will recieve it
//it is equal to maxTimeBonus * 10(make number bigger) - (time took to complete all 10 waves) 
int timeBonusScore = 15.0f * 60.0f * 10.0f; 

bool curGameEnded = false;
std::vector<int> highscores;
char const* highScoreFile = "highscore.txt";

void Reset_HighScore() {
	curHighScore = 0;
	curGameEnded = false;
}

void Add_Score(int val) {
	curHighScore += val;
}

//Only to be called when all waves are completed
void Finalize_HighScore() {
	if (curGameTime < maxTimeBonus) {
		curHighScore += timeBonusScore - (static_cast<int>(curGameTime) * 10.0f);
	}	
}




//Load the highscores from the highscore file
void Load_HighScoreFile() {
	std::ifstream file{ highScoreFile };

	if (!file) {
		std::cout << "Error opening highscore.txt " << "__PRETTY_FUNCTION__";
		return;
	}

	highscores.clear();

	int count = 0, curScore = 0;
	char buffer[256];

	//read the first line for number of highscores
	file.getline(buffer, 256);
	sscanf_s(buffer, "%d", &count);

	highscores.reserve(count + 1);

	while (file.getline(buffer, 256)) {
		sscanf_s(buffer, "%d", &curScore);
		highscores.push_back(curScore);
	}

	file.close();
}

//Write the current new highscore into the highscore file
void Update_HighScoreFile() {
	//Add the current highscore into the vecotor
	highscores.push_back(curHighScore);
	//Sort the vector 
	std::sort(highscores.begin(), highscores.end());

	std::ofstream file;
	file.open(highScoreFile, std::ios::trunc);

	if (!file) {
		std::cout<< "Error opening highscore.txt " << "__PRETTY_FUNCTION__";
	}

	//Write number of highscores saved to the first line
	file << highscores.size() << "\n";

	//Write highscore to file 
	for (int const& val : highscores) {
		file << val << "\n";
	}

	file.close();
}