#include <iostream>
#include <vector>
#include <stack>

const int WIDTH = 10;  // Width of the grid
const int HEIGHT = 10; // Height of the grid

// Function to set a pixel on the grid
void setPixel(std::vector<std::vector<char>>& grid, int x, int y, char c) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        grid[y][x] = c;
    }
}

// Function to draw the shape
void drawShape(std::vector<std::vector<char>>& grid) {
    std::cout << "Draw your shape on the grid using 'x' (lowercase):\n";
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            std::cin >> grid[y][x];
        }
    }
}

// Function to perform the boundary fill algorithm
void boundaryFill(std::vector<std::vector<char>>& grid, int x, int y, char fillColor, char boundaryColor) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    if (grid[y][x] != boundaryColor && grid[y][x] != fillColor) {
        grid[y][x] = fillColor;
        boundaryFill(grid, x+1, y, fillColor, boundaryColor);
        boundaryFill(grid, x-1, y, fillColor, boundaryColor);
        boundaryFill(grid, x, y+1, fillColor, boundaryColor);
        boundaryFill(grid, x, y-1, fillColor, boundaryColor);
    }
}

int main() {
    std::vector<std::vector<char>> grid(HEIGHT, std::vector<char>(WIDTH, '.'));

    // Step 1: User draws their shape on the grid
    drawShape(grid);

    // Print the grid with the drawn shape
    std::cout << "\nThe shape you drew:\n";
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }

    // Step 2: User inputs the starting coordinates and fill color
    int startX, startY;
    char fillColor;
    std::cout << "\nEnter the starting coordinates (x y) within the shape: ";
    std::cin >> startX >> startY;
    std::cout << "Enter the fill color: ";
    std::cin >> fillColor;

    // Ensure the starting coordinates are within the grid bounds
    if (startX < 0 || startX >= WIDTH || startY < 0 || startY >= HEIGHT) {
        std::cerr << "Error: Starting coordinates are out of bounds." << std::endl;
        return 1;
    }

    // Step 3: Fill the bounded region using the boundary fill algorithm
    boundaryFill(grid, startX, startY, fillColor, 'x');

    // Print the grid with the filled shape
    std::cout << "\nThe shape with filled region:\n";
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
