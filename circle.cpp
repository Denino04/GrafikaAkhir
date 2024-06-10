#include <iostream>
#include <vector>

const int WIDTH = 20;  // Width of the grid
const int HEIGHT = 20; // Height of the grid

// Define the setPixel function
void setPixel(std::vector<std::vector<char>>& grid, int x, int y, char c) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        grid[HEIGHT - y - 1][x] = c;
    }
}

// Circle drawing using 8-point symmetry
void drawCircle(int radius, int centerX, int centerY, std::vector<std::vector<char>>& grid) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        // Plot the points using symmetry
        setPixel(grid, centerX + x, centerY + y, '*');
        setPixel(grid, centerX - x, centerY + y, '*');
        setPixel(grid, centerX + x, centerY - y, '*');
        setPixel(grid, centerX - x, centerY - y, '*');
        setPixel(grid, centerX + y, centerY + x, '*');
        setPixel(grid, centerX - y, centerY + x, '*');
        setPixel(grid, centerX + y, centerY - x, '*');
        setPixel(grid, centerX - y, centerY - x, '*');

        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

int main() {
    std::vector<std::vector<char>> grid(HEIGHT, std::vector<char>(WIDTH, ' '));

    // User input for circle coordinates
    int x, y, radius;
    std::cout << "Enter the coordinates of the center of the circle (x y): ";
    std::cin >> x >> y;
    std::cout << "Enter the radius of the circle: ";
    std::cin >> radius;

    // Ensure the coordinates are within the grid bounds
    if (x - radius < 0 || x + radius >= WIDTH || y - radius < 0 || y + radius >= HEIGHT) {
        std::cerr << "Error: Circle is out of bounds." << std::endl;
        return 1;
    }

    // Draw the circle
    drawCircle(radius, x, y, grid);

    // Print the grid
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
    
    system("pause");
    return 0;
}
