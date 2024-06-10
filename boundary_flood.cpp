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

// Function to perform the flood fill algorithm
void floodFill(std::vector<std::vector<char>>& grid, int x, int y, char fillColor, char targetColor) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    if (grid[y][x] != targetColor) return;

    std::stack<std::pair<int, int>> stack;
    stack.push({x, y});

    while (!stack.empty()) {
        std::pair<int, int> current = stack.top();
        stack.pop();

        int cx = current.first;
        int cy = current.second;

        if (cx < 0 || cx >= WIDTH || cy < 0 || cy >= HEIGHT) continue;
        if (grid[cy][cx] != targetColor) continue;

        grid[cy][cx] = fillColor;

        stack.push({cx + 1, cy});
        stack.push({cx - 1, cy});
        stack.push({cx, cy + 1});
        stack.push({cx, cy - 1});
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

    // Get the target color to be replaced
    char targetColor = grid[startY][startX];

    // Step 3: Fill the bounded region using the flood fill algorithm
    if (targetColor != fillColor) {
        floodFill(grid, startX, startY, fillColor, targetColor);
    }

    // Print the grid with the filled shape
    std::cout << "\nThe shape with filled region:\n";
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
    system("pause");
    return 0;
}
