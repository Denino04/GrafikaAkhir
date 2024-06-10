#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

// Define the maximum dimensions of the grid
const int WIDTH = 40;  // Width of the grid (20 to the left of 0, 20 to the right of 0)
const int HEIGHT = 40; // Height of the grid (20 above 0, 20 below 0)

// Function to set a pixel on the grid
void setPixel(char grid[][WIDTH], int x, int y, char c) {
    int gridX = x + WIDTH / 2;
    int gridY = HEIGHT / 2 - y - 1;
    if (gridX >= 0 && gridX < WIDTH && gridY >= 0 && gridY < HEIGHT) {
        grid[gridY][gridX] = c;
    }
}

// Function to draw the object on the grid
void drawObject(char grid[][WIDTH], const std::vector<std::pair<int, int>>& objectCoords) {
    for (const auto& coord : objectCoords) {
        setPixel(grid, coord.first, coord.second, '*');
    }
}

// Function to calculate the centroid of the object
std::pair<int, int> calculateCentroid(const std::vector<std::pair<int, int>>& objectCoords) {
    int sumX = 0, sumY = 0;
    for (const auto& coord : objectCoords) {
        sumX += coord.first;
        sumY += coord.second;
    }
    return {sumX / objectCoords.size(), sumY / objectCoords.size()};
}

// Function to perform reflection using matrix transformation
void reflect(std::vector<std::pair<int, int>>& objectCoords, const std::string& axis) {
    auto originalCentroid = calculateCentroid(objectCoords);

    for (auto& coord : objectCoords) {
        if (axis == "x") {
            coord.second = 2 * originalCentroid.second - coord.second;
        } else if (axis == "y") {
            coord.first = 2 * originalCentroid.first - coord.first;
        } else if (axis == "xy") {
            coord.first = 2 * originalCentroid.first - coord.first;
            coord.second = 2 * originalCentroid.second - coord.second;
        }
    }

    auto newCentroid = calculateCentroid(objectCoords);
    int dx = originalCentroid.first - newCentroid.first;
    int dy = originalCentroid.second - newCentroid.second;

    for (auto& coord : objectCoords) {
        coord.first += dx;
        coord.second += dy;
    }
}

// Function to perform shear using matrix transformation on multiple points
void shear(std::vector<std::pair<int, int>>& objectCoords, const std::vector<std::pair<int, int>>& shearPoints, double shearX, double shearY) {
    for (const auto& shearPoint : shearPoints) {
        int x = shearPoint.first;
        int y = shearPoint.second;
        for (auto& coord : objectCoords) {
            coord.first = x + static_cast<int>(shearX * y);
            coord.second = y + static_cast<int>(shearY * x);
        }
    }
}

int main() {
    // Initialize the grid with empty cells
    char grid[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            grid[i][j] = '.';
        }
    }

    // User input for object coordinates
    int numCoords;
    std::cout << "Enter the number of coordinates for the object: ";
    std::cin >> numCoords;

    std::vector<std::pair<int, int>> objectCoords(numCoords);
    std::cout << "Enter the coordinates of the object (x y):\n";
    for (int i = 0; i < numCoords; ++i) {
        std::cin >> objectCoords[i].first >> objectCoords[i].second;
    }

    bool continueTransforming = true;
    while (continueTransforming) {
        // Draw the object on the grid
        drawObject(grid, objectCoords);

        // Print the grid before transformations
        std::cout << "\nObject before transformations:\n";
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                std::cout << grid[i][j] << ' ';
            }
            std::cout << '\n';
        }

        // Transformation options
        const char* options[] = {"Reflection", "Shear"};

        // Prompt the user for transformation choice
        std::cout << "\nChoose the transformation:\n";
        for (int i = 0; i < 2; ++i) {
            std::cout << i + 1 << ". " << options[i] << '\n';
        }
        std::cout << "3. Exit\n";
        int choice;
        std::cin >> choice;

        // Perform the selected transformation
        switch (choice) {
            case 1: {
                // Reflection
                std::string axis;
                std::cout << "Enter the axis of reflection (x, y, or xy): ";
                std::cin >> axis;
                reflect(objectCoords, axis);
                break;
            }
            case 2: {
                // Shear
                double shearX, shearY;
                int numShearPoints;
                std::cout << "Enter the number of shear points: ";
                std::cin >> numShearPoints;
                std::vector<std::pair<int, int>> shearPoints(numShearPoints);
                std::cout << "Enter the shear points (x y):\n";
                for (int i = 0; i < numShearPoints; ++i) {
                    std::cin >> shearPoints[i].first >> shearPoints[i].second;
                }
                std::cout << "Enter the shear factors (shearX shearY): ";
                std::cin >> shearX >> shearY;
                shear(objectCoords, shearPoints, shearX, shearY);
                break;
            }
            case 3: {
                // Exit
                continueTransforming = false;
                break;
            }
            default:
                std::cout << "Invalid choice.\n";
                return 1;
        }

        // Clear the grid for the next iteration
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                grid[i][j] = '.';
            }
        }
    }

    // Draw the final transformed object on the grid
    drawObject(grid, objectCoords);

    // Print the grid after transformations
    std::cout << "\nObject after transformations:\n";
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
