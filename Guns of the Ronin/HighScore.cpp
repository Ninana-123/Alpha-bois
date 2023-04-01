
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
	//std::ifstream file{ "../Assets/highscore.txt" };
	std::fstream file;
	file.open("Assets/highscore.txt", std::ios_base::in);// , std::ifstream::in);
	
	if (!file) {
		std::cout << "Error opening highscore.txt";
		return;
	}

	highscores.clear();
	int curScore = 0;
	char buffer[256];

	//read the first line for number of highscores
	file.getline(buffer, 256);
	std::cout << buffer << "\n";

	highscores.reserve(NUM_OF_HIGH_SCORES);
	int count = 0;
	while (file.getline(buffer, 256) && count++ < NUM_OF_HIGH_SCORES) {
		sscanf_s(buffer, "%d", &curScore);
		highscores.push_back(curScore);
	}
	//sort the high scores
	Sort_HighScores();
	highscores.erase(std::unique(highscores.begin(), highscores.end()), highscores.end());

	file.close();
}
void Sort_HighScores() {
	std::sort(highscores.begin(), highscores.end(), std::greater<>());
}

//Write the current new highscore into the highscore file
void Update_HighScoreFile() {
	//Add the current highscore into the vecotor
	highscores.push_back(curHighScore);
	//Sort the high scores
	Sort_HighScores();
	highscores.erase(std::unique(highscores.begin(), highscores.end()), highscores.end());

	std::ofstream file;
	file.open("Assets/highscore.txt", std::ios::trunc);

	if (!file) {
		std::cout << "Error opening highscore.txt";
	}

	//Write highscore to file 
	int numOfHighScores = highscores.size() < NUM_OF_HIGH_SCORES ? highscores.size() : NUM_OF_HIGH_SCORES;
	for (int i = 0; i < numOfHighScores; ++i) {
		file << highscores[i] << "\n";
	}

	file.close();
}