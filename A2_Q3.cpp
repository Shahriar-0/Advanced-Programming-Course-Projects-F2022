#include <iostream>
#include <vector>

using namespace std;

#define ROCK '#'
#define BAMBOO '*'
#define EMPTY '.'
#define NO_PATH -1

enum Direction {RIGHT, LEFT, UP, DOWN};
enum Coordinate_status {NOT_SEEN, SEEN};

struct Coordinate {
    char data;
    Coordinate_status right;
    Coordinate_status left;
    Coordinate_status up;
    Coordinate_status down;
};

struct Point {
    int x;
    int y;
};

int length_of_shortest_path(vector<vector<Coordinate>>&);
int find_shortest_path(vector<vector<Coordinate>>, Direction, Point , int = 0);
int changing_direction(vector<vector<Coordinate>>, Direction, Point , int);
void mark_position(vector<vector<Coordinate>>&, const Point, Direction);
int check_result(int, int);
bool in_loop(const vector<vector<Coordinate>>&, Direction, Point);
bool hit_edge(Point, int, int);
Point generate_previous_coordinate(Point, Direction);
Point generate_new_coordinate(Point, Direction);
vector<vector<Coordinate>> get_input(void);

int main(void) {
    vector<vector<Coordinate>> map = get_input();
    int minLength = length_of_shortest_path(map);
    (minLength == NO_PATH)? cout << "No path found" << endl : cout << minLength << endl;
}

vector<vector<Coordinate>> get_input() {
    vector<vector<Coordinate>> map;
    int index = 0;
    string line;
    while (cin >> line) {
        map.resize(index + 1);
        map[index].resize(line.length());
        for (int i = 0; i < line.length(); i++) {
            map[index][i].data = line[i];
            //at first we haven't seen any of them
            map[index][i].down = map[index][i].up = map[index][i].right = map[index][i].left = NOT_SEEN;
        }
        index++;
    }
    return map;
}

Point generate_new_coordinate(Point position, Direction direction) {
    position.y += (direction == RIGHT) - (direction == LEFT);
    position.x += (direction == DOWN) - (direction == UP);
    return position;
}

Point generate_previous_coordinate(Point position, Direction direction) {
    position.y -= (direction == RIGHT) - (direction == LEFT);
    position.x -= (direction == DOWN) - (direction == UP);
    return position;
}

bool hit_edge(Point position, int numOfRows, int numOFColumns) {
    return (position.x == numOfRows) || (position.x == -1) ||
           (position.y == numOFColumns) || (position.y == -1);
}

bool in_loop(const vector<vector<Coordinate>>& map, Direction direction, Point position) {
    switch (direction) {
            case RIGHT: return map[position.x][position.y].right;
            case LEFT: return map[position.x][position.y].left;
            case UP: return map[position.x][position.y].up;
            case DOWN: return map[position.x][position.y].down;
    }
}

void mark_position(vector<vector<Coordinate>>& map, const Point position, Direction direction) {
    switch (direction) {
            case RIGHT: map[position.x][position.y].right = SEEN; break;
            case LEFT: map[position.x][position.y].left = SEEN; break;
            case UP: map[position.x][position.y].up = SEEN; break;
            case DOWN: map[position.x][position.y].down = SEEN; break;
    }
}

int changing_direction(vector<vector<Coordinate>> map, Direction direction, Point position, int length) {
    //return value is the minimum length of the other two possible choices
    position = generate_previous_coordinate(position, direction);
    int minLengthFirst, minLengthSecond;
    if (direction == RIGHT || direction == LEFT) {
        minLengthFirst = find_shortest_path(map, UP, position,length - 1);
        minLengthSecond = find_shortest_path(map, DOWN, position, length - 1);
    }
    else {
        minLengthFirst = find_shortest_path(map, LEFT, position,length - 1);
        minLengthSecond = find_shortest_path(map, RIGHT, position, length - 1);
    }

    return check_result(minLengthFirst, minLengthSecond);
}

int find_shortest_path(vector<vector<Coordinate>> map, Direction direction, Point position, int length) {
    bool hittedEdge = false, inLoop = false;

    do {
        //we go ahead till we hit rock or edge or we stuck in a loop
        //and we mark places that we see
        inLoop = in_loop(map, direction, position);
        mark_position(map, position, direction);
        position = generate_new_coordinate(position, direction);
        hittedEdge = hit_edge(position, map.size(), map[0].size());
        length++;
    } while (!hittedEdge && !inLoop && map[position.x][position.y].data == EMPTY);

    if (inLoop) 
        return NO_PATH;

    if (hittedEdge || map[position.x][position.y].data == ROCK) 
        return changing_direction(map, direction, position, length);
    
    if (map[position.x][position.y].data == BAMBOO)
        return length;
}

int length_of_shortest_path(vector<vector<Coordinate>>& map) {
    constexpr Point PANDA_POSITION = {0, 0};
    Direction FIRST_INITIAL_DIRECTION = RIGHT, SECOND_INITIAL_DIRECTION = DOWN;
    int minLengthFirst = find_shortest_path(map, FIRST_INITIAL_DIRECTION, PANDA_POSITION);
    int minLengthSecond = find_shortest_path(map, SECOND_INITIAL_DIRECTION, PANDA_POSITION);
    return check_result(minLengthFirst, minLengthSecond);
}

int check_result(int first, int second) {
    if (first == NO_PATH && second == NO_PATH)
        return NO_PATH;
    if (first == NO_PATH)
        return second;
    if (second == NO_PATH)
        return first;
    return min(first, second);
}