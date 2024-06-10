#include <iostream>
#include <vector>

const int WIDTH = 40;  // Width of the grid (increased for better representation of ellipses)
const int HEIGHT = 20; // Height of the grid

// Define the setPixel function
void setPixel(std::vector<std::vector<char>>& grid, int x, int y, char c) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        grid[y][x] = c;
    }
}

// Ellipse drawing using 4-point symmetry
void drawEllipse(int a, int b, int centerX, int centerY, std::vector<std::vector<char>>& grid) {
    int x = 0;
    int y = b;
    int d1 = b * b + a * a * (-b + 0.25);
    int dx = 2 * b * b * x;
    int dy = 2 * a * a * y;

    // Region 1
    while (dx < dy) {
        setPixel(grid, centerX + x, centerY + y, '*');
        setPixel(grid, centerX - x, centerY + y, '*');
        setPixel(grid, centerX + x, centerY - y, '*');
        setPixel(grid, centerX - x, centerY - y, '*');

        if (d1 < 0) {
            x++;
            dx = dx + (2 * b * b);
            d1 = d1 + dx + (b * b);
        } else {
            x++;
            y--;
            dx = dx + (2 * b * b);
            dy = dy - (2 * a * a);
            d1 = d1 + dx - dy + (b * b);
        }
    }

    // Region 2
    int d2 = (b * b) * (x + 0.5) * (x + 0.5) + (a * a) * (y - 1) * (y - 1) - (a * a * b * b);
    while (y >= 0) {
        setPixel(grid, centerX + x, centerY + y, '*');
        setPixel(grid, centerX - x, centerY + y, '*');
        setPixel(grid, centerX + x, centerY - y, '*');
        setPixel(grid, centerX - x, centerY - y, '*');

        if (d2 > 0) {
            y--;
            dy = dy - (2 * a * a);
            d2 = d2 + (a * a) - dy;
        } else {
            y--;
            x++;
            dx = dx + (2 * b * b);
            dy = dy - (2 * a * a);
            d2 = d2 + dx - dy + (a * a);
        }
    }
}

int main() {
    std::vector<std::vector<char>> grid(HEIGHT, std::vector<char>(WIDTH, ' '));

    // User input for ellipse parameters
    int centerX, centerY, a, b;
    std::cout << "Enter the coordinates of the center of the ellipse (x y): ";
    std::cin >> centerX >> centerY;
    std::cout << "Enter the semi-major axis (a): ";
    std::cin >> a;
    std::cout << "Enter the semi-minor axis (b): ";
    std::cin >> b;

    // Ensure the coordinates are within the grid bounds
    if (centerX - a < 0 || centerX + a >= WIDTH || centerY - b < 0 || centerY + b >= HEIGHT) {
        std::cerr << "Error: Ellipse is out of bounds." << std::endl;
        return 1;
    }

    // Draw the ellipse
    drawEllipse(a, b, centerX, centerY, grid);

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
