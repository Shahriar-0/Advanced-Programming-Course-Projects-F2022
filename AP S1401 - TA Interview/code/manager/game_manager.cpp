#include "game_manager.hpp"
#include "../cli/cli.hpp"

typedef void (GameManager::*game_manager_method)(std::vector<std::string>);
typedef std::map<std::string, game_manager_method> game_manager_func_map_type;

using namespace std;

GameManager::GameManager(game_manager_func_map_type& func_map) : is_working(true) {
    load_nodes();
    map_functions(func_map);
}

enum LoadStation {
    ID_INDEX, 
    LEFT_INDEX,
    RIGHT_INDEX,
    TYPE_INDEX
};

void GameManager::load_nodes() {
    // Load all nodes from input file
    int num_nodes;
    cin >> num_nodes;
    vector<Node*> nodes;
    string line;
    while (num_nodes--) {
        getline(cin, line);
        add_node(line, nodes, num_nodes);
    }
    root_node = *find_if(nodes.begin(), nodes.end(), [](Node* node) { return node->is_root(); });
}

void GameManager::split_line(int& node_id, int& right_node_id, int& left_node_id, string& type, string& line) {
    // Split the line into the node id, right node id, left node id and type
    node_id = stoi(line.substr(0, line.find(' ')));
    line = line.substr(line.find(' ') + 1);
    right_node_id = stoi(line.substr(0, line.find(' ')));
    line = line.substr(line.find(' ') + 1);
    left_node_id = stoi(line.substr(0, line.find(' ')));
    line = line.substr(line.find(' ') + 1);
    type = line.substr(0, line.find(' '));
}

void GameManager::find_left_and_right(Node*& left_node, Node*& right_node, vector<Node*>& nodes,
                 int left_node_id, int right_node_id) {
    // Find the left and right nodes in the nodes vector, if they exist, otherwise create queue nodes
    auto right_node_it = find(nodes.begin(), nodes.end(), right_node_id);
    auto left_node_it = find(nodes.begin(), nodes.end(), left_node_id);

    if (right_node_it != nodes.end()) 
        right_node = *right_node_it;
    else {
        right_node = createInstance<QueueNode>(right_node_id, nullptr, nullptr);
        nodes.push_back(right_node);
    }

    if (left_node_it != nodes.end()) 
        left_node = *left_node_it;
    else {
        left_node = createInstance<QueueNode>(left_node_id, nullptr, nullptr);
        nodes.push_back(left_node);
    }
}

void GameManager::add_node(string line, vector<Node*>& nodes, int num_nodes) {
    // Add a node to the nodes vector and to the tree
    int node_id, right_node_id, left_node_id;
    string type;
    split_line(node_id, right_node_id, left_node_id, type, line);


    Node* left_node = nullptr;
    Node* right_node = nullptr;
    find_left_and_right(left_node, right_node, nodes, left_node_id, right_node_id);
    
    Node* node;
    // nullptrs are used to indicate that the node does not yet have a parent
    if (node_id > num_nodes) 
        node = createInstance<QueueNode>(node_id, right_node, left_node);

    else {
        if (type == CHESS_KEYWORD) 
            node = createInstance<Chess>(node_id, right_node, left_node);
        else if (type == WRESTLE_KEYWORD) 
            node = createInstance<Wrestle>(node_id, right_node, left_node);
        else if (type == ARMWRESTLE_KEYWORD) 
            node = createInstance<ArmWrestle>(node_id, right_node, left_node);
        else if (type == KABAB_KEYWORD)
            node = createInstance<Kabab>(node_id, right_node, left_node);
        else 
            throw logic_error("Invalid node type");
        
    }
    nodes.push_back(node);
}

void GameManager::map_functions(game_manager_func_map_type& game_manager_function_map) {
    // Map all strings to the function map

    game_manager_function_map[ARRIVAL_KEYWORD] = &GameManager::add_player;
    game_manager_function_map[RUN_KEYWORD] = &GameManager::run;
    game_manager_function_map[END_GAME_KEYWORD] = &GameManager::shutdown;
    game_manager_function_map[CLOSE_KEYWORD] = &GameManager::close_station;

}

void GameManager::run(std::vector<std::string> args){
    
}

enum Close { // indexes of the arguments in the close station command
    CLOSE_KEYWORD_INDEX,
    QUEUE_INDEX,
};

void GameManager::close_station(std::vector<std::string> args){
    root_node = root_node->close_station(stoi(args[QUEUE_INDEX]));
}

enum Arrival {  // indexes of the arguments in the arrival command
    ARRIVAL_KEYWORD_INDEX,
    QUEUE_INDEX,
    PLAYER_INDEX,
    STRENGTH_INDEX,
    AGILITY_INDEX,
    INTELLIGENCE_INDEX,
    MAIN_ABILITY_INDEX 
};


void GameManager::add_player(std::vector<std::string> args){
    Player* player = new Player(stoi(args[PLAYER_INDEX]), stoi(args[STRENGTH_INDEX]),
                     stoi(args[AGILITY_INDEX]), stoi(args[INTELLIGENCE_INDEX]), args[MAIN_ABILITY_INDEX]);
    root_node->add_player(player, stoi(args[QUEUE_INDEX]));
}

void GameManager::shutdown(std::vector<std::string> args){
    // root_node->shutdown(); // TODO: implement shutdown
    is_working = false;
}

template <typename T>
T* createInstance(int _id, T* right, T* left) { 
    // Create a new instance of a specific type of node with the given parameters
    return new T(_id, right, left); 
}