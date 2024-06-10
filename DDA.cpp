#include <iostream>
#include <cmath>
#include <vector>

const int WIDTH = 20;  // Width of the grid
const int HEIGHT = 20; // Height of the grid

// Define the setPixel function
void setPixel(std::vector<std::vector<char>>& grid, int x, int y, char c) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        grid[HEIGHT - y - 1][x] = c;
    }
}

void drawLineDDA(int x1, int y1, int x2, int y2) {
    // Calculate dx and dy
    int dx = x2 - x1;
    int dy = y2 - y1;

    // Determine the number of steps
    int steps = std::max(std::abs(dx), std::abs(dy));

    // Calculate increments
    float x_increment = static_cast<float>(dx) / steps;
    float y_increment = static_cast<float>(dy) / steps;

    // Initialize current coordinates
    float x = static_cast<float>(x1);
    float y = static_cast<float>(y1);

    // Create a grid for visualization
    std::vector<std::vector<char>> grid(HEIGHT, std::vector<char>(WIDTH, ' '));

    // Plot the initial point using setPixel function
    setPixel(grid, static_cast<int>(round(x)), static_cast<int>(round(y)), '*');

    // Perform the line drawing
    for (int i = 0; i < steps; ++i) {
        x += x_increment;
        y += y_increment;
        setPixel(grid, static_cast<int>(round(x)), static_cast<int>(round(y)), '*');
    }

    // Print the grid
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    int x1, y1, x2, y2;

    // User input for coordinates
    std::cout << "Enter the coordinates of the first point (x1 y1): ";
    std::cin >> x1 >> y1;
    std::cout << "Enter the coordinates of the second point (x2 y2): ";
    std::cin >> x2 >> y2;

    // Ensure the coordinates are within the grid bounds
    if (x1 < 0 || x1 >= WIDTH || y1 < 0 || y1 >= HEIGHT || x2 < 0 || x2 >= WIDTH || y2 < 0 || y2 >= HEIGHT) {
        std::cerr << "Error: Coordinates must be within the grid bounds (0 to " << WIDTH-1 << " for x and 0 to " << HEIGHT-1 << " for y)." << std::endl;
        return 1;
    }

    std::cout << "Drawing a line from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << "):" << std::endl;
    drawLineDDA(x1, y1, x2, y2);
    system("pause");

    return 0;
}
