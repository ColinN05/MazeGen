#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <stack>
#include <array>

#define MAZE_SIZE 20

struct Vector
{
    int i, j;
};

Vector operator+(Vector x, Vector y)
{
    return Vector{x.i + y.i, x.j + y.j};
}

int main()
{
    bool maze[2 * MAZE_SIZE + 1][2 * MAZE_SIZE + 1] = { false };

    // entrance and exit of maze
    maze[0][1] = true;
    maze[2 * MAZE_SIZE][2 * MAZE_SIZE - 1] = true;

    std::stack<Vector> path;
    Vector currentPosition, newPosition;
    currentPosition = { 1, 1 };
    maze[1][1] = true;
    path.push(currentPosition);

    std::array<Vector, 4> steps = {Vector{0,2}, Vector{0,-2}, Vector{-2,0}, Vector{2,0}}; // right, left, up, down

    // generate maze
    while (path.size() != 0)
    {
        currentPosition = path.top();
        std::random_shuffle(steps.begin(), steps.end());
        bool moved = false;

        for (Vector step : steps)
        {
            newPosition = currentPosition + step;
            if (newPosition.i > -1 && newPosition.i < 2 * MAZE_SIZE + 1
                && newPosition.j > -1 && newPosition.j < 2 * MAZE_SIZE + 1
                && !maze[newPosition.i][newPosition.j]
            )
            {
                maze[newPosition.i][newPosition.j] = true;
                maze[(int)(currentPosition.i + newPosition.i)/2][(int)(currentPosition.j + newPosition.j)/2] = true;
                currentPosition = newPosition;
                path.push(currentPosition);
                moved = true;
                break;
            }
        }
        if (moved == false)
        {
            path.pop();
        }
    }

    // print maze
    for (int i = 0; i < 2 * MAZE_SIZE + 1; i++)
    {
        for (int j = 0; j < 2 * MAZE_SIZE + 1; j++)
        {
            std::cout << (maze[i][j] ? "  " : "##");
        }
        std::cout << '\n'; 
    }

    return 0;
}