#include <iostream>
#include <cmath>

// Define the maximum dimensions of the grid
const int WIDTH = 20;  // Width of the grid
const int HEIGHT = 20; // Height of the grid

// Function to set a pixel on the grid
void setPixel(char grid[][WIDTH], int x, int y, char c) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        grid[y][x] = c;
    }
}

// Function to draw the object on the grid
void drawObject(char grid[][WIDTH], const std::pair<int, int>* objectCoords, int numCoords) {
    for (int i = 0; i < numCoords; ++i) {
        int x = objectCoords[i].first;
        int y = objectCoords[i].second;
        setPixel(grid, x, y, '*');
    }
}

// Function to perform translation
void translate(std::pair<int, int>* objectCoords, int numCoords, int tx, int ty) {
    for (int i = 0; i < numCoords; ++i) {
        objectCoords[i].first += tx;
        objectCoords[i].second += ty;
    }
}

// Function to perform rotation
void rotate(std::pair<int, int>* objectCoords, int numCoords, double angle) {
    double theta = angle * M_PI / 180.0;
    int cx = 0, cy = 0;
    for (int i = 0; i < numCoords; ++i) {
        cx += objectCoords[i].first;
        cy += objectCoords[i].second;
    }
    cx /= numCoords;
    cy /= numCoords;
    for (int i = 0; i < numCoords; ++i) {
        int x = objectCoords[i].first;
        int y = objectCoords[i].second;
        int newX = round((x - cx) * cos(theta) - (y - cy) * sin(theta)) + cx;
        int newY = round((x - cx) * sin(theta) + (y - cy) * cos(theta)) + cy;
        objectCoords[i].first = newX;
        objectCoords[i].second = newY;
    }
}

// Function to perform scaling
void scale(std::pair<int, int>* objectCoords, int numCoords, double scaleX, double scaleY) {
    int cx = 0, cy = 0;
    for (int i = 0; i < numCoords; ++i) {
        cx += objectCoords[i].first;
        cy += objectCoords[i].second;
    }
    cx /= numCoords;
    cy /= numCoords;
    for (int i = 0; i < numCoords; ++i) {
        int x = objectCoords[i].first;
        int y = objectCoords[i].second;
        int newX = round((x - cx) * scaleX) + cx;
        int newY = round((y - cy) * scaleY) + cy;
        objectCoords[i].first = newX;
        objectCoords[i].second = newY;
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

    std::pair<int, int> objectCoords[numCoords];
    std::cout << "Enter the coordinates of the object:\n";
    for (int i = 0; i < numCoords; ++i) {
        std::cin >> objectCoords[i].first >> objectCoords[i].second;
    }

    bool continueTransforming = true;
    while (continueTransforming) {
        // Draw the object on the grid
        drawObject(grid, objectCoords, numCoords);

        // Print the grid before transformations
        std::cout << "\nObject before transformations:\n";
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                std::cout << grid[i][j] << ' ';
            }
            std::cout << '\n';
        }

        // Transformation options
        std::string options[] = {"Translation", "Rotation", "Scaling"};

        // Prompt the user for transformation choice
        std::cout << "\nChoose the transformation:\n";
        for (int i = 0; i < 3; ++i) {
            std::cout << i + 1 << ". " << options[i] << '\n';
        }
        std::cout << "4. Exit\n";
        int choice;
        std::cin >> choice;

        // Perform the selected transformation
        switch (choice) {
            case 1: {
                // Translation
                int tx, ty;
                std::cout << "Enter the translation vector (tx ty): ";
                std::cin >> tx >> ty;
                translate(objectCoords, numCoords, tx, ty);
                break;
            }
            case 2: {
                // Rotation
                double angle;
                std::cout << "Enter the rotation angle (degrees): ";
                std::cin >> angle;
                rotate(objectCoords, numCoords, angle);
                break;
            }
            case 3: {
                // Scaling
                double scaleX, scaleY;
                std::cout << "Enter the scaling factors (scaleX scaleY): ";
                std::cin >> scaleX >> scaleY;
                scale(objectCoords, numCoords, scaleX, scaleY);
                break;
            }
            case 4: {
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

    return 0;
}
