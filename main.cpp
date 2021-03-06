/**<
	Authors: Allen Higgins C00197373 and Robert Scully C00196960
	Date: 15 December 2017

*/
#include <iostream>
#include "main.h"
#include <vector>
#include <stdio.h>
#include <time.h>
#include "Creacher.h"
#include <chrono>
#include <thread>

static bool freeSpace = false;

/**< return a random number of type int */
int genRandomNum(int range) {
	return (int(rand() % range));
}

/**< set a random number for both row and col - (randomly selecting a posstion in the vector) */
void chooseRowCol(int *row, int *col,int const ROWS, int const COLS) {
	*row = genRandomNum(ROWS - 1);
	*col = genRandomNum(COLS - 1);
}

/**< Shark move replace */
void sharkDoSomeWork(int &count, int pickRow, int pickCol, int newRow, int newCol,
	bool *hasCheckEachSpace, int *randPossibleSpace,
	std::vector < std::vector < Creacher* > > &water)
{
	count++;
	int freeRow = 0, freeCol = 0;


	std::cout << "count = " << count << " -- FREESPACE  = " << freeSpace << std::endl;


	/**<look at each space for fish - if fish is found move to that space and kill the poor fishy*/
	if (water[newRow][newCol] == NULL) {
		freeRow = newRow;
		freeCol = newCol;
		freeSpace = true;
		std::cout << "----------------------------------------------------------------->>> SHARK FOUND FREE SPACE!!!!" << std::endl;
		if (count == 4) {
			if (freeSpace == true) {
				/**<there are no poot fishy's find free space and move to that space*/
				water[freeRow][freeCol] = new Creacher('S', water[pickRow][pickCol]->age);
				std::cout << "----------------------------------------------------------------->>> SHARK HAS MOVED TO A FREE SAPCE!!" << std::endl;
				water[pickRow][pickCol] = NULL;
				*hasCheckEachSpace = true;
				freeSpace = false;
			}
		}
	}else if (water[newRow][newCol]->type == 'F') {
		/**<move to free space*/
		std::cout << "pos = " << pickRow << "," << pickCol << " move to = " << newRow << "," << newCol << std::endl;
		water[newRow][newCol] = new Creacher('F', water[pickRow][pickCol]->age);
		std::cout << "----------------------------------------------------------------->>> SHARK HAS MOVED AND KILLED POOR FISHY!!" << std::endl;
		water[pickRow][pickCol] = NULL;
		*hasCheckEachSpace = true;
		freeSpace = false;
	}else {
		if ( count == 4) {
			if (freeSpace == true) {
				/**<there are no poot fishy's find free space and move to that space*/
				water[freeRow][freeCol] = new Creacher('S', water[pickRow][pickCol]->age);
				std::cout << "----------------------------------------------------------------->>> SHARK HAS MOVED TO A FREE SPACE!!" << std::endl;
				freeSpace = false;
			}
			else {
				/**<re-choose a possible posstion*/
				std::cout << "----------------------------------------------------------------->>> SHARK CANNOT MOVE STAYING PUT!!" << std::endl;
				*randPossibleSpace = genRandomNum(4) + 1;
			}
		}else {
			/**<re-choose a possible posstion */
			std::cout << "----------------------------------------------------------------->>> SHARK CANNOT MOVE!!" << std::endl;
			*randPossibleSpace = genRandomNum(4) + 1;
		}
	}
}



/**<Fish move replace*/
void doSomeWork(int &count, int pickRow, int pickCol, int newRow,int newCol,
	bool *hasCheckEachSpace,int *randPossibleSpace,
	std::vector < std::vector < Creacher* > > &water)
{
	count++;
	if (water[newRow][newCol] == NULL) {
		/**<move to free space*/
		water[newRow][newCol] = new Creacher('F', water[pickRow][pickCol]->age);
		std::cout << "----------------------------------------------------------------->>> FISH HAS MOVED!!" << std::endl;
		water[pickRow][pickCol] = NULL;
		*hasCheckEachSpace = true;
	}else {
		/**<re-choose a possible posstion*/
		std::cout << "----------------------------------------------------------------->>> FISH CANNOT MOVE!!" << std::endl;
		*randPossibleSpace = genRandomNum(4) + 1;
	}
}

/**<nice print for area of each simulation frame*/
void printAreaBondry() {
	std::cout << "___________________________________________________________________________________________________" << std::endl;
}

int main()
{
	/**<for generation new random numbers*/
	srand((unsigned int)time(NULL));
	/**<constant values for vectore rows and cols*/
	int const ROWS = 12, COLS = 32;
	/**<delare vector of Class Creaher*/
	std::vector < std::vector < Creacher* > > water(ROWS, std::vector< Creacher* >(COLS));
	/**<	count is for total nuber of Creachers
		posRow and posCol for random position to place Creaher in the vector
		whichOne is for determining at random which type a Creacher will be - fish or shark
		age is for generating a random age of the Creather between 0-4
		SCount (Shark) and FCount (Fish) to keep track of total Creachers in the world
	*/
	int countCreacher = 200;
	int count = countCreacher, posRow = 0, posCol = 0, whichOne = 0,SCount = 0,FCount = 0, spawnRow = 0, spawnCol = 0;
	int age = genRandomNum(4) + 1;
	/**<
		while count > 0 assings Creachers
		get random number for row and col with age of Creacher.
		if whichOne = 1 a Creacher is a Shark otherwise it is a Fish and count total of each type
	*/
	while (count > 0) {
		chooseRowCol(&posRow, &posCol, ROWS, COLS);
		whichOne = genRandomNum(2);
		if (whichOne == 1) {
			water[posRow][posCol] = new Creacher('S', age);
			SCount++;
		}
		else {
			water[posRow][posCol] = new Creacher('F', age);
			FCount++;
		}
		count--;
	}
	/**<
		Start Simulation
		set up vars for randomly picking rows and cols
	*/
	int pickRow = 0;
	int pickCol = 0;
	while (countCreacher > 0) {
		/**<nice print for start of area*/
		printAreaBondry();
		if (water.empty()) {
			break;
		}

		/**< Draw Vector*/
		for (int i = 0; i < ROWS; ++i)
		{
			for (int j = 0; j < COLS; ++j) {
				water[i][j] == NULL ? std::cout << " " : std::cout << water[i][j]->type;
			}
			std::cout << std::endl;
		}

		/**<pick at random a location in the vector until a location is found that has a Creacher*/
		chooseRowCol(&pickRow, &pickCol, ROWS, COLS);
		while (water[pickRow][pickCol] == NULL) {
			chooseRowCol(&pickRow, &pickCol, ROWS, COLS);
		}

			/**<logic*/
			const int checkAge = 3;
			int randPossibleSpace;
			int newRow = 0;
			int newCol = 0;
			int count = 0;

			bool hasCheckEachSpace = false;
			bool one = false;
			bool two = false;
			bool three = false;
			bool four = false;

			/**<If Fish*/
			if (water[pickRow][pickCol]->type == 'F') {

				/**<increse age by 1*/
				water[pickRow][pickCol]->age++;
				std::cout << "----------------------------------------------------------------->>> FISH AGE: " << water[pickRow][pickCol]->age << std::endl;

				/**<if age equals 4 - die*/
				if (water[pickRow][pickCol]->age > checkAge) {
					water[pickRow][pickCol] = NULL;
					FCount--;
					countCreacher--;
					std::cout << "----------------------------------------------------------------->>> FISH STARVING!!" << std::endl;
					continue;
				}else if (water[pickRow][pickCol]->age == checkAge) {
					/**<else if age equals = 3 create new fish in random free space*/
					chooseRowCol(&spawnRow, &spawnCol, ROWS, COLS);
					while (water[spawnRow][spawnCol] != NULL) {
						chooseRowCol(&spawnRow, &spawnCol, ROWS, COLS);
					}
					water[spawnRow][spawnCol] = new Creacher('F', age = int(genRandomNum(4)));
					/**<increse the fish population and overall population*/
					FCount++;
					countCreacher++;
					std::cout << "----------------------------------------------------------------->>> CREATE FISH!!" << std::endl;
				}
				/**<randomly pick an ajcent space*/
				while (hasCheckEachSpace == false) {
					randPossibleSpace = genRandomNum(4) + 1;
					newRow = 0;
					newCol = 0;
					/**<if case 1-4 has come out fish is surrounded - hasCheckEachSpace = true to end loop*/
					if (count == 4) {
						hasCheckEachSpace = true;
						std::cout << "----------------------------------------------------------------->>> STAYING PUT!" << std::endl;
						continue;
					}
					one = false;
					two = false;
					three = false;
					four = false;

					if (pickRow == 0 && pickCol == 0) {
						/**<leth corner
						randomly pick a possible space to move to*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow + 11;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol + 31;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol + 1;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow + 1;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickRow == 0 && pickCol == 31) {
						/**<right corner
						randomly pick a possible space to move to*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow + 11;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol - 1;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol - 31;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow + 1;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickRow == 11 && pickCol == 31) {
						/**<bottom rigth corner
						randomly pick a possible space to move to*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow - 1;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol - 1;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol - 31;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow - 11;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickRow == 11 && pickCol == 0) {
						/**<Bottom Left
						randomly pick a possible space to move to*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow - 1;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol + 31;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol + 1;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow - 11;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickRow == 0 && (pickCol > 0 && pickCol < 31)) {
						/**<randomly pick a possible space to move to
						Top row*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow + 11;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol - 1;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol + 1;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow + 1;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickRow == 11 && (pickCol > 0 && pickCol < 31)) {
						/**<randomly pick a possible space to move to
						Bottom Row*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow - 1;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol - 1;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol + 1;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow - 11;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickCol == 0 && (pickRow > 0 && pickRow < 11)) {
						/**<randomly pick a possible space to move to
						Down Left side*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow - 1;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol + 31;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol + 1;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow + 1;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickCol == 31 && (pickRow > 0 && pickRow < 11)) {
						/**<randomly pick a possible space to move to
						Down Right side*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow - 1;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol - 31;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol - 1;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow; +1;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else {
						/**<randomly pick a possible space to move to*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow - 1;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow + 1;
								newCol = pickCol;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol - 1;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow;
								newCol = pickCol + 1;
								doSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
				}/**<end fish while  - If Shark*/
			}
			else if (water[pickRow][pickCol]->type == 'S') {

				/**<increse age by 1*/
				water[pickRow][pickCol]->age++;
				std::cout << "----------------------------------------------------------------->>> SHARK AGE: " << water[pickRow][pickCol]->age << std::endl;

				/**<if age equals 4 - die*/
				if (water[pickRow][pickCol]->age > checkAge) {
					water[pickRow][pickCol] = NULL;
					SCount--;
					countCreacher--;
					std::cout << "----------------------------------------------------------------->>> SHARK STARVING!!" << std::endl;
					continue;
				}
				else if (water[pickRow][pickCol]->age == checkAge) {
					/**<else if age equals = 3 create new Shark in random free space*/
					chooseRowCol(&spawnRow, &spawnCol, ROWS, COLS);
					while (water[spawnRow][spawnCol] != NULL) {
						chooseRowCol(&spawnRow, &spawnCol, ROWS, COLS);
					}
					water[spawnRow][spawnCol] = new Creacher('S', age = int(genRandomNum(4)));
					/**<increse the shark population and overall population*/
					SCount++;
					countCreacher++;
					std::cout << "----------------------------------------------------------------->>> CREATE SHARK!!" << std::endl;
				}

				/**<randomly pick an ajcent space*/
				while (hasCheckEachSpace == false) {
					randPossibleSpace = genRandomNum(4) + 1;
					newRow = 0;
					newCol = 0;
					/**<if case 1-4 has come out shark is surrounded - hasCheckEachSpace = true to end loop*/
					if (count == 4) {
						hasCheckEachSpace = true;
						continue;
					}
					one = false;
					two = false;
					three = false;
					four = false;


					if (pickRow == 0 && pickCol == 0) {
						/**<leth corner
						randomly pick a possible space to move to*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow + 11;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol + 31;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol + 1;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow + 1;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickRow == 0 && pickCol == 31) {
						/**<right corner
						randomly pick a possible space to move to*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow + 11;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol - 1;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol - 31;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow + 1;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickRow == 11 && pickCol == 31) {
						/**<bottom rigth corner
						randomly pick a possible space to move to*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow - 1;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol - 1;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol - 31;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow - 11;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickRow == 11 && pickCol == 0) {
						/**<Bottom Left
						randomly pick a possible space to move to*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow - 1;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol + 31;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol + 1;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow - 11;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickRow == 0 && (pickCol > 0 && pickCol < 31)) {
						/**<randomly pick a possible space to move to
						Top row*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow + 11;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol - 1;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol + 1;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow + 1;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickRow == 11 && (pickCol > 0 && pickCol < 31)) {
						/**<randomly pick a possible space to move to
						Bottom Row*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow - 1;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol - 1;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol + 1;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow - 11;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickCol == 0 && (pickRow > 0 && pickRow < 11)) {
						/**<randomly pick a possible space to move to
						Down Left side*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow - 1;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol + 31;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol + 1;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow + 1;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else if (pickCol == 31 && (pickRow > 0 && pickRow < 11)) {
						/**<randomly pick a possible space to move to
						Down Right side*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow - 1;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow;
								newCol = pickCol - 31;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol - 1;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow; +1;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
					else {
						/**<randomly pick a possible space to move to*/
						switch (randPossibleSpace) {
						case 1:
							if (one == false) {
								one = true;
								newRow = pickRow - 1;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 2:
							if (two == false) {
								two = true;
								newRow = pickRow + 1;
								newCol = pickCol;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 3:
							if (three == false) {
								three = true;
								newRow = pickRow;
								newCol = pickCol - 1;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						case 4:
							if (four == false) {
								four = true;
								newRow = pickRow;
								newCol = pickCol + 1;
								sharkDoSomeWork(count, pickRow, pickCol, newRow, newCol, &hasCheckEachSpace, &randPossibleSpace, water);
							}
							break;
						}
					}
				}/**<end shark while */
		}/**<end of while */
		printAreaBondry();
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		//system("PAUSE");
	}/**<end of while */
	std::cout << "//////////////////////////////////////////////////////////\n\n\n" << std::endl;
	std::cout << "////   It's the End of the world as we know it! - REM   ////" << std::endl;
	std::cout << "\n\n\n/////////////////////////////////////////////////////////" << std::endl;
	system("PAUSE");
    return 0;
}
