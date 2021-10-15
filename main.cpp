#include <ios>
#include <iostream>
#include <array>
#include <iomanip>
#include <math.h>
#include <unistd.h>

#define MAX_X_GRID 150 
#define MAX_Y_GRID 40

template<typename T>
void PrintArray(const T& e) {
	if (e == true)
		// \u25AO - square filled
		// \u25CF - sphere filled
		std::cout << "\033[1;32m\u25CF\033[0m";
	
	else
		std::cout << " ";
}

template<typename T, std::size_t N>
void PrintArray(const std::array<T,N>& A) {
	for(const auto& i: A)
		PrintArray(i);
	std::cout << "\n";
}

template<typename T, std::size_t N>
void FillArray(std::array<T,N>& A, bool val) {
	for(auto& i: A)
		i.fill(val);
}

template<typename T, std::size_t N>
void SeedArray(std::array<T,N>& A) {
	int32_t cellstospawn = std::round( (MAX_X_GRID * MAX_Y_GRID) / 2 );
	int32_t random_x = std::rand() % MAX_X_GRID;
	int32_t random_y = std::rand() % MAX_Y_GRID;

	while(cellstospawn > 0) {
		// spawn cell at random location
		(A.at(random_y)).at(random_x) = true;
		random_x = std::rand() % MAX_X_GRID;
	 	random_y = std::rand() % MAX_Y_GRID;
		cellstospawn--;
	}
}

template<typename T, std::size_t N>
bool CheckAlive(std::array<T,N>& A, int32_t x, int32_t y) {
	int32_t yy = (y + MAX_Y_GRID) % MAX_Y_GRID;
	int32_t xx = (x + MAX_X_GRID) % MAX_X_GRID;
	return (A.at(yy)).at(xx);
}

template<typename T, std::size_t N>
int32_t CountNeighbours(std::array<T,N>& A, int32_t x, int32_t y) {
	int32_t neighbours = 0;
	for(int32_t v = -1; v <= 1; v++) {
		for(int32_t h = -1; h <= 1; h++) {
			if( !(v == 0 && h ==0) && CheckAlive(A, x + h, y + v) )
				neighbours++;
		}
	}

	return neighbours;
}

template<typename T, std::size_t N>
bool RulesLife(std::array<T,N>& A, int32_t x, int32_t y) {
	return ( CountNeighbours(A, x, y) == 3 || (CountNeighbours(A, x, y) == 2 && CheckAlive(A, x, y)) );
}

template<typename T, std::size_t N>
void Update(std::array<T, N>& A) {
	std::array<std::array<bool, MAX_X_GRID>, MAX_Y_GRID> copy;
	copy = A;
//	PrintArray(arr_grid);

	for(int32_t y = 0; y < MAX_Y_GRID; y++) {
		for(int32_t x = 0; x < MAX_X_GRID; x++) {
		(copy.at(y)).at(x) = RulesLife(A, x, y);
		}
	}
	A = copy;
}

int main() {
	std::cout << "This is game of life!\n";

	std::array<std::array<bool, MAX_X_GRID>, MAX_Y_GRID> arr_grid;
	FillArray(arr_grid, 0);
	SeedArray(arr_grid);
	while(1) {
		PrintArray(arr_grid);
		Update(arr_grid);
//		usleep(175000);
		usleep(90000);
	}
}
