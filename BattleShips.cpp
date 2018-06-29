#include <iostream>
#include <stdlib.h> // Random
#include <time.h> // Random
#include <string>
#include <unistd.h> // Sleep

const int gridSize = 10;
bool checkHit(int (&grid)[gridSize][gridSize], std::string input);
std::string generateAICoord();
void drawBoard();
void populateGrids();

int gridPlayer[gridSize][gridSize]; // 0 = Empty, 1 = Contains Ship, 2 = Hit, 3 = Miss
int gridAI[gridSize][gridSize];
std::string lastCommand = "Last Command = ";

bool running = true;

int main(){
	system("clear");

	populateGrids();

	std::string input = "";
	while (running == true){ // Game state
		std::cout << lastCommand << std::endl;

		drawBoard();

		// User choose coordinate
		if(input.length() != 2){
			std::cout << "Please enter square to hit in the form <Letter><Number>" << std::endl;
			std::cin >> input;
		} else {
			if(checkHit(gridAI, input)){
				lastCommand = "hit";
			} else {
				lastCommand = "miss";
			}
			input = "";	
		}
		for(int r = 0; r < 1; r++){
			sleep(1);
			if(checkHit(gridPlayer, generateAICoord())){
				lastCommand = "enemy hit";
			}
		}
		system("clear");
		
		// Check for game over
		bool leastOnePlayer = false;
		bool leastOneAI = false;
		for(int j = 0; j < gridSize; j++){
			for(int i = 0; i < gridSize; i++){
				if(gridPlayer[i][j] == 1){
					leastOnePlayer = true;
				}
				if(gridAI[i][j] == 1){
					leastOneAI = true;
				}
			}
		}
		if(leastOnePlayer == false){
			running = false;
			drawBoard();
			std::cout << "You lose!" << std::endl;
		}
		if(leastOneAI == false){
			drawBoard();
			running = false;
			std::cout << "You win!" << std::endl;
		}
	}

}

std::string generateAICoord(){ // Choose random AI coordinate
	std::string coord = "";
	srand (time(NULL));
	int randomLetter = rand() % 10;
	switch(randomLetter){
		case 0: coord.append("A");
		break;
		case 1: coord.append("B");
		break;
		case 2: coord.append("C");
		break;
		case 3: coord.append("D");
		break;
		case 4: coord.append("E");
		break;
		case 5: coord.append("F");
		break;
		case 6: coord.append("G");
		break;
		case 7: coord.append("H");
		break;
		case 8: coord.append("I");
		break;
		case 9: coord.append("J");
		break;
	}
	int randomNumber = rand() % 10;
	coord.append(std::to_string(randomNumber));
	return coord;
}

bool checkHit(int (&grid)[gridSize][gridSize], std::string input){
	char command[2];
	for(int i = 0; i < input.length(); i++){
		command[i] = input.at(i);
	}
	int num = command[1] - '0';
	int letter;
	if(num >= 0 && num < 10 && command[0] <= 'J' && command[0] >= 'A'){
		switch(command[0]){
			case 'A': letter = 0;
			break;
			case 'B': letter = 1;
			break;
			case 'C': letter = 2;
			break;
			case 'D': letter = 3;
			break;
			case 'E': letter = 4;
			break;
			case 'F': letter = 5;
			break;
			case 'G': letter = 6;
			break;
			case 'H': letter = 7;
			break;
			case 'I': letter = 8;
			break;
			case 'J': letter = 9;
			break; 
		}
		if(grid[letter][num] == 1){
			grid[letter][num] = 2;
			return true;
		}	else{
				if(grid[letter][num] != 2)
					grid[letter][num] = 3;
				return false;
		}
	}
	else
			return false;
}

void drawBoard(){
	//enemy display
	std::cout << "ENEMY" << std::endl;
	std::cout << "   A  B  C  D  E  F  G  H  I  J" << std::endl;
	for(int j = 0; j < gridSize; j++){
		std::cout << j << " ";
		for(int i = 0; i < gridSize; i++){
			if(gridAI[i][j] == 2){
				std::cout << "[X]";
			} else if(gridAI[i][j] == 3){
				std::cout << "[.]";
			} else{
				std::cout << "[ ]";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;

	//player display
	std::cout << "PLAYER" << std::endl;
	std::cout << "   A  B  C  D  E  F  G  H  I  J" << std::endl;
	for(int j = 0; j < gridSize; j++){
		std::cout << j << " ";
		for(int i = 0; i < gridSize; i++){
			if(gridPlayer[i][j] == 0){
				std::cout << "[ ]";
			} else if(gridPlayer[i][j] == 1){
				std::cout << "[O]";
			} else if (gridPlayer[i][j] == 2){
				std::cout << "[X]";
			} else if(gridPlayer[i][j] == 3){
				std::cout << "[.]";
			}
		}
		std::cout << std::endl;
	}
}

void populateGrids(){
	// Player
	gridPlayer[3][2] = 1;
	gridPlayer[3][3] = 1;

	gridPlayer[1][4] = 1;
	gridPlayer[1][5] = 1;
	gridPlayer[1][6] = 1;
	gridPlayer[1][7] = 1;

	gridPlayer[5][5] = 1;
	gridPlayer[6][5] = 1;
	
	// AI
	gridAI[1][2] = 1;
	gridAI[1][3] = 1;

	gridAI[4][5] = 1;
	gridAI[5][5] = 1;
	gridAI[6][5] = 1;
	gridAI[7][5] = 1;

	gridAI[7][8] = 1;
	gridAI[7][9] = 1;
}
