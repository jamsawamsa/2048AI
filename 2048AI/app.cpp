#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

void drawBoard(int score), newTurn(), getNewBoardState(string dir), addTiles(int i1, int j1, int i2, int j2), shiftTile(int i1, int j1, int i2, int j2);

int checkCol(string dir, int i, int j);
int checkRow(string dir, int i, int j);
void shuffleCol(string dir, int j), shuffleRow(string dir, int i);
string commandAdaptr(string choice);
vector<int> getEmptyTiles();
vector<string> getMoves();

string board[4][4] = { "","","","","","","","","","","","","","","","" };
//string board[4][4] = { "","2","4","","","","","","","","","","","","","" };

int score = 0;

int main() { // main loop
	string choice;
	vector<string>availMoves;
	srand((unsigned int)time(NULL)); // activates the random number generator

	do {
		newTurn();
		drawBoard(score);

		availMoves = getMoves(); // get available moves
		if (availMoves.size() == 0) break; // game over

		cout << "Possible moves: "; // print moves
		for (vector<string>::iterator it = availMoves.begin(); it != availMoves.end(); it++) {
			cout << *it << ", ";
		}
		cout << "please select one: ";

		for (;;) { // input validation
			if (cin >> choice) {
				choice = commandAdaptr(choice);
				vector<string>::iterator it;
				it = find(availMoves.begin(), availMoves.end(), choice); // check if input is a valid move given possible moves
				if (it != availMoves.end()) {
					break;
				}
			}
			cout << "Please enter a valid move: "; // input not valid
			cin.clear();
			cin.ignore();
		}
		getNewBoardState(choice); // update board state

	} while (true);
	cout << "\n\n\tGAME OVER\n\n";
	cout << endl;
	cout << "Your final score is: " << score << "!";
	cout << endl;
	system("pause");
	vector<string>().swap(availMoves);
	return 0;
}
/*
Function to initialize a new turn.
Adds a new numbered tile to the board.
*/
void newTurn() {
	vector<int> emptyTiles = getEmptyTiles();
	int numEmptyTiles = emptyTiles.size(); //get empty tiles
	int newTileAddr;
	string newTileVal = "2";

	// Decide if a new '2' or '4' tile is spawned
	double rng = ((double)rand() / (RAND_MAX));
	if (rng > 0.9) {
		newTileVal = "4"; // change the new tile value to 4 with 10% odds
	}

	if (numEmptyTiles > 0) {
		newTileAddr = emptyTiles[rand() % numEmptyTiles];
		board[newTileAddr / 4][newTileAddr % 4] = newTileVal;
		if (newTileVal == "2") { // add value of new tile to the score
			score += 2;
		}
		else {
			score += 4;
		}
	}
	vector<int>().swap(emptyTiles); // free vector memory
}

/*
Function to draw the board onto the console.
params:
int score - current score to draw
*/
void drawBoard(int score)
{
	//system("cls"); // clear previous items on console
	cout << "\n\n\t2048\n\n";
	cout << "Score: " << score << endl;
	cout << endl;

	cout << "     |     |     |     " << endl; // draw the board
	cout << setw(5) << board[0][0] << "|" << setw(5) << board[0][1] << "|" << setw(5) << board[0][2] << "|" << setw(5) << board[0][3] << endl;

	cout << "_____|_____|_____|_____" << endl;
	cout << "     |     |     |     " << endl;

	cout << setw(5) << board[1][0] << "|" << setw(5) << board[1][1] << "|" << setw(5) << board[1][2] << "|" << setw(5) << board[1][3] << endl;

	cout << "_____|_____|_____|_____" << endl;
	cout << "     |     |     |     " << endl;

	cout << setw(5) << board[2][0] << "|" << setw(5) << board[2][1] << "|" << setw(5) << board[2][2] << "|" << setw(5) << board[2][3] << endl;

	cout << "_____|_____|_____|_____" << endl;
	cout << "     |     |     |     " << endl;

	cout << setw(5) << board[3][0] << "|" << setw(5) << board[3][1] << "|" << setw(5) << board[3][2] << "|" << setw(5) << board[3][3] << endl;

	cout << "     |     |     |     " << endl << endl;

}

/*
Function to return the number of empty squares on the board
Return:
vecctor<int> data - the number of empty squares on the board
*/
vector<int> getEmptyTiles() {
	vector<int> data;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == "") { // count empty tiles and push the index to the vector
				data.push_back((i * 4) + j);
			}
		}
	}
	return data;
}

/*
Function that returns a vector of possible moves for the next turn.
Return;
vector<string> moves - vector of possible moves that can be made in the next turn
*/
vector<string> getMoves() {
	vector<string> moves;
	int u = 0, d = 0, l = 0, r = 0, temp; // directional indicators

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] != "") {
				// check for moves up
				temp = i - 1; // check from the tile above current tile
				while (u == 0 && temp >= 0) { // while there is no up movement previously found
					if (board[temp][j] == "" || board[temp][j] == board[i][j]) {
						u = 1;
						break;
					}
					else if (board[temp][j] != board[i][j]) { // different valued tile
						break;
					}
					temp = temp - 1;
				}

				// check for moves down
				temp = i + 1; // check from the tile below
				while (d == 0 && temp <= 3) {
					if (board[temp][j] == "" || board[temp][j] == board[i][j]) {
						d = 1;
						break;
					}
					else if (board[temp][j] != board[i][j]) { // different valued tile
						break;
					}
					temp = temp + 1;
				}

				// check for moves left
				temp = j - 1;
				while (l == 0 && temp >= 0) { // checks from the tile to the lefft of the current tile
					if (board[i][temp] == "" || board[i][temp] == board[i][j]) {
						l = 1;
						break;
					}
					else if (board[i][temp] != board[i][j]) { // different valued tile
						break;
					}

					temp = temp - 1;
				}

				// check for moves right
				temp = j + 1;
				while (r == 0 && temp <= 3) { // checks to the right of the current tile
					if (board[i][temp] == "" || board[i][temp] == board[i][j]) {
						r = 1;
						break;
					}
					else if (board[i][temp] != board[i][j]) { // different valued tile
						break;
					}
					temp = temp + 1;
				}
			}
		}
	}
	// add possible moves to the vector
	if (u) {
		moves.push_back("up");
	}
	if (d) {
		moves.push_back("down");
	}
	if (l) {
		moves.push_back("left");
	}
	if (r) {
		moves.push_back("right");
	}

	return moves;
}

/*
Function to get a new board state
params:
string dir : indicates the movement applied to the board
*/
void getNewBoardState(string dir) {
	int collision;
	if (dir == "up") { // move up
		for (int j = 0; j <= 3; j++) {
			collision = -1;
			for (int i = 1; i <= 3; i++) {
				if (board[i][j] != "") {
					if (collision == -1) { // if no collisions so far
						collision = checkCol(dir, i, j); //check for a collision
						if (collision != -1) {
							addTiles(collision, j, i, j);
						}
					}
				}
				if (i == 3) {
					shuffleCol(dir, j); // shuffle all tiles upwards 
				}
			}

		}
	}
	else if (dir == "left") { // move left
		for (int i = 0; i <= 3; i++) {
			collision = -1;
			for (int j = 1; j <= 3; j++) {
				if (board[i][j] != "") {
					if (collision == -1) {// if no collisions so far
						collision = checkRow(dir, i, j); //check for a collision
						if (collision != -1) {
							addTiles(i, collision, i, j);
						}
					}
				}
				if (j == 3) {
					shuffleRow(dir, i); // shuffle all tiles leftwards
				}
			}
		}
	}
	else if (dir == "down") { // move down
		for (int j = 0; j <= 3; j++) {
			collision = -1;
			for (int i = 2; i >= 0; i--) {
				if (board[i][j] != "") {
					if (collision == -1) {// if no collisions so far
						collision = checkCol(dir, i, j);
						if (collision != -1) {
							addTiles(collision, j, i, j);
						}
					}
				}
				if (i == 0) {
					shuffleCol(dir, j); // shuffle all tiles downwards 
				}
			}
		}
	}
	else if (dir == "right") { // move right
		for (int i = 0; i <= 3; i++) {
			collision = -1;
			for (int j = 2; j >= 0; j--) {
				if (board[i][j] != "") {
					if (collision == -1) {// if no collisions so far
						collision = checkRow(dir, i, j);
						if (collision != -1) {
							addTiles(i, collision, i, j);
						}
					}
				}
				if (j == 0) {
					shuffleRow(dir, i); // shuffle all tiles to the right 
				}
			}
		}
	}
}

/*
Function to add 2 tiles together
params:
i1 - destination tile row
j1 - destination tile col
i2 - travelling tile row
j2 - travelling tile col
*/
void addTiles(int i1, int j1, int i2, int j2) {
	int newVal = stoi(board[i1][j1]) + stoi(board[i2][j2]);
	board[i1][j1] = to_string(newVal);
	board[i2][j2] = "";
}

/*
Function to check a column for vertical collisions
params:
string dir : direction to check
int i: i value of current tile
int j: j value of current tile
return:
int -1: if there are no collisions
int n: represents the column value of the tile that the current tile has a collision with
*/
int checkCol(string dir, int i, int j) {
	if (dir == "up") {
		for (int n = i - 1; n >= 0; n--) { // upwards check
			if (board[n][j] == "") { // checked tile is empty
				continue;
			}
			else if (board[n][j] != board[i][j]) { // checked tile has different value
				break;
			}
			else if (board[n][j] == board[i][j]) { // checked tile has same value
				return n;
			}
		}
	}
	else { //downwards check
		for (int n = i + 1; n <= 3; n++) {
			if (board[n][j] == "") { // checked tile is empty
				continue;
			}
			else if (board[n][j] != board[i][j]) { // checked tile has different value
				break;
			}
			else if (board[n][j] == board[i][j]) { // checked tile has same value
				return n;
			}
		}
	}
	return -1;
}

/*
Function to check if there is a collision along a row, in right or left directions.
params:
string dir : direction to check
int i: i value of current tile
int j: j value of current tile
Returns:
int -1: if there are no collisions
int n: represnts the j value (column) of the tile that collides with the current tile
*/
int checkRow(string dir, int i, int j) {
	if (dir == "left") { // leftwards check
		for (int n = j - 1; n >= 0; n--) {
			if (board[i][n] == "") { // checked tile is empty
				continue;
			}
			else if (board[i][n] != board[i][j]) { // checked tile has different value
				break;
			}
			else if (board[i][n] == board[i][j]) { // checked tile has same value
				return n;
			}
		}
	}
	else { //rightwards check
		for (int n = j + 1; n <= 3; n++) {
			if (board[i][n] == "") { // checked tile is empty
				continue;
			}
			else if (board[i][n] != board[i][j]) { // checked tile has different value
				break;
			}
			else if (board[i][n] == board[i][j]) { // checked tile has same value
				return n;
			}
		}
	}
	return -1;
}
/*
Shifts board[i2][j2] to board [i1][j1]
Params:
int i1: destination row value of the tile
int j1: destination column value of the tile
int i2: origin row value of the tile to be moved
int j2: origin column value of the tile to be moved
*/
void shiftTile(int i1, int j1, int i2, int j2) {
	board[i1][j1] = board[i2][j2];
	board[i2][j2] = "";
}

/*
shuffles a column vertically, either upwards or downwards.
Fills up all empty (denoted as "") spaces on the board on the same column
Params:
string dir: direction of the shuffle. Must be either "up" or "down"
int j: the column index that is to be shuffled
*/
void shuffleCol(string dir, int j) {
	if (dir == "up") {
		for (int n = 1; n <= 3; n++) {
			for (int m = n - 1; m >= 0; m--) {
				if (board[m][j] == "") {
					if (board[m - 1][j] == "" && m - 1 >= 0) {
						continue;
					}
					else {
						shiftTile(m, j, n, j);
					}
				}
			}
		}
	}
	else {
		for (int n = 2; n >= 0; n--) {
			for (int m = n + 1; m <= 3; m++) {
				if (board[m][j] == "") {
					if (board[m + 1][j] == "" && m + 1 <= 3) {
						continue;
					}
					else {
						shiftTile(m, j, n, j);
					}
				}
			}
		}
	}
}

/*
shuffles a row horizontally, either to the right or left.
Fills up all empty (denoted as "") spaces on the board on the same row
Params:
string dir: direction of the shuffle. Must be either "right" or "left"
int i: the row index that is to be shuffled
*/
void shuffleRow(string dir, int i) {
	if (dir == "left") { //shuffle to the left
		for (int n = 1; n <= 3; n++) {
			for (int m = n - 1; m >= 0; m--) {
				if (board[i][m] == "") {
					if (board[i][m - 1] == "" && m - 1 >= 0) {
						continue;
					}
					else {
						shiftTile(i, m, i, n);
					}
				}
			}
		}
	}
	else {
		for (int n = 2; n >= 0; n--) {
			for (int m = n + 1; m <= 3; m++) {
				if (board[i][m] == "") {
					if (board[i][m + 1] == "" && m + 1 <= 3) {
						continue;
					}
					else {
						shiftTile(i, m, i, n);
					}
				}
			}
		}
	}
}

string commandAdaptr(string choice) {
	if (choice.length() != 1) {
		return choice;
	}
	if (choice == "r") {
		return "right";
	}
	else if (choice == "left")
	{
		return "left";
	}
	else if (choice == "u") {
		return "up";
	}
	else if (choice == "d") {
		return "down";
	}
}