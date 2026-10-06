#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <climits>
#include <limits>

using namespace std;
map<char, map<char, int>> network;

void ShowNetwork()
{

    cout << "============================\n";
    cout << "        NETWORK GRAPH       \n";
    cout << "============================\n";

    for (auto outer_pair : network)
    {
        cout << outer_pair.first << ": ";
        for (auto connections : outer_pair.second)
        {
            cout << "   " << connections.first << "--> " << connections.second;
        }
        cout << "\n";
    }
    cout << "\n";
}

void BFS_Algorithm()
{

    char vertex_choice;

    // BFS ALGORITHM
    cout << "======BFS ALGORITHM=====\n";
    // Creating the queue for the vertex waiting to be processed
    queue<char> q;
    // creating a map for discovered vertex
    // Remember: for every key that doesn't exist,C++ creates it with default value false
    // so i dont need to initialize all the vertices to false.
    map<char, bool> bfs_visited;

    cout << "\nFrom which vertex do you want to start searching?";
    cin >> vertex_choice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nPlease enter a valid vertex. ";
        cout << "\nFrom which vertex do you want to start searching?";
        cin >> vertex_choice;
    }

    // while(!network.find(vertex_choice)
    while (network.find(vertex_choice) == network.end())
    {
        cout << "\nThere is no such vertex.Try again.";
        cout << "\nFrom which vertex do you want to start searching? ";
        cin >> vertex_choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nPlease enter a valid vertex. ";
            cout << "\nFrom which vertex do you want to start searching?";
            cin >> vertex_choice;
        }
    }
    // initializing vertex A
    // A has been discovered and is waiting to be processed.
    bfs_visited[vertex_choice] = true;
    q.push(vertex_choice);
    while (!q.empty())
    {
        char bfs_current_vertex = q.front();
        q.pop();
        cout << bfs_current_vertex << " ";
        // examine the neigbors of the poped element
        for (auto connection : network[bfs_current_vertex])
        {
            if (!bfs_visited[connection.first])
            {
                bfs_visited[connection.first] = true;
                q.push(connection.first);
            }
        }
    }
    cout << endl;
    cout << "\n";
}
void DFS_Algorithm()
{

    // creting the stack -->DFS
    stack<char> s;
    map<char, bool> dfs_visited;
    // Maps each vertex to the connected computer it belongs to
    map<char, int> component_id;
    // I know that the DFS will run at least one time
    int num_of_running_dfs = 1;
    char vertex_choice;

    // DFS ALGORITHM
    cout << "======DFS ALGORITHM=====\n";

    cout << "\nFrom which vertex do you want to start searching? ";
    cin >> vertex_choice;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nPlease enter a valid vertex.";
        cout << "\nFrom which vertex do you want to start searching?";
        cin >> vertex_choice;
    }

    // while(!network.find(vertex_choice)
    while (network.find(vertex_choice) == network.end())
    {
        cout << "\nThere is no such vertex.Try again.";
        cout << "\nFrom which vertex do you want to start searching? ";
        cin >> vertex_choice;
    }

    dfs_visited[vertex_choice] = true;
    s.push(vertex_choice);
    while (!s.empty())
    {
        char dfs_current_vertex = s.top();
        cout << dfs_current_vertex << " ";
        s.pop();
        component_id[dfs_current_vertex] = num_of_running_dfs;
        for (auto connection : network[dfs_current_vertex])
        {
            if (!dfs_visited[connection.first])
            {
                dfs_visited[connection.first] = true;
                s.push(connection.first);
            }
        }
    }

    for (auto each : network)
    {
        if (!dfs_visited[each.first])
        {
            dfs_visited[each.first] = true;
            s.push(each.first);

            num_of_running_dfs++;
            // Start DFS
            while (!s.empty())
            {
                char dfs_current_vertex = s.top();
                cout << dfs_current_vertex << " ";
                s.pop();
                component_id[dfs_current_vertex] = num_of_running_dfs;
                for (auto connection : network[dfs_current_vertex])
                {
                    if (!dfs_visited[connection.first])
                    {
                        dfs_visited[connection.first] = true;
                        s.push(connection.first);
                    }
                }
            }
        }
    }
    cout << "\n\n=====NETWORK CONNECTIVITY=====\n";
    if (num_of_running_dfs == 1)
    {
        cout << "Network is connected.\n";
    }
    else
    {
        cout << "Network is disconnected.\n";
    }
    cout << "\n";
    // Printing every component seperately
    for (int n = 1; n <= num_of_running_dfs; n++)
    {
        cout << "Component " << n << ": ";

        for (auto each : component_id)
        {
            if (each.second == n)
            {
                cout << each.first << " ";
            }
        }
        cout << "\n";
    }
}

void Dijkstra_Algorithm()
{

    // DIJkSTRA ALGORITHM
    // Maps for Dijkstra
    stack<char> s;
    map<char, int> distance;
    map<char, bool> dijkstra_visited;
    map<char, char> previous;

    char vertex_choice;

    cout << "\nFrom which vertex do you want to start searching? ";
    cin >> vertex_choice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nPlease enter a valid vertex.";
        cout << "\nFrom which vertex do you want to start searching?";
        cin >> vertex_choice;
    }

    while (network.find(vertex_choice) == network.end())
    {
        cout << "\nThere is no such vertex.Try again.";
        cout << "\nFrom which vertex do you want to start searching? ";
        cin >> vertex_choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nPlease enter a valid vertex.";
            cout << "\nFrom which vertex do you want to start searching?";
            cin >> vertex_choice;
        }
    }

    // Initializing every vertex with infinitive
    for (auto each : network)
    {
        distance[each.first] = INT_MAX;
    }

    distance[vertex_choice] = 0;

    // Initialing every vertex with infinity
    for (int w = 0; w < network.size(); w++)
    {
        int smallest = INT_MAX;

        char dijkstra_current_vertex;

     // Find the smallest unvisited vertex
    for (auto each : network)
        {
            if (!dijkstra_visited[each.first] && distance[each.first] < smallest)
            {
                dijkstra_current_vertex = each.first;
                smallest = distance[each.first];
            }
        }

    if (smallest == INT_MAX)
        {
            break;
        }

        // Look at the current vertex neighbors
    for (auto connection : network[dijkstra_current_vertex])
        {
            int new_distance = distance[dijkstra_current_vertex] + connection.second;

            if (new_distance < distance[connection.first])
            {
                distance[connection.first] = new_distance;
                previous[connection.first] = dijkstra_current_vertex;
            }
        }

        dijkstra_visited[dijkstra_current_vertex] = true;
    }

    cout << "\n=====DIJKSTRA ALGORITHM=====";
    cout << endl;

    for (auto each : distance)
    {
        cout << each.first << ": " << each.second << endl;
    }

    // Printing the selected order of the vertices
    char target;

    cout << "\nEnter destination: ";
    cin >> target;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nPlease enter a valid vertex.";
        cout << "\nEnter destination: ";
        cin >> target;
    }

    while (network.find(target) == network.end())
    {
        cout << "\nThere is no such vertex.Try again.";
        cout << "\nEnter destination: ";

        cin >> target;

        if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nPlease enter a valid vertex.";
        cout << "\nEnter destination: ";
        cin >> target;
    }
}
     
    // Checking whether the two given vertices are the same
    while (vertex_choice == target)
    {
        cout << "\nThe two given vertices are the same.Give something else!";
        cout << "\nEnter destination ";
        cin >> target;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nPlease enter a valid vertex.";
            cout << "\nEnter destination: ";
            cin >> target;
        }

        
        
         while (network.find(target) == network.end())
                {
                    cout << "\nThere is no such vertex.Try again.";
                    cout<<"\nEnter destination: ";
                    cin >> target;

                }
                 
        }

        if (distance[target] == INT_MAX)
        {
            cout << "Destination is unreachable." << endl;
        }
        else
        {
            char current = target;

            while (current != vertex_choice)
            {
                s.push(current);
                current = previous[current];
            }
            s.push(vertex_choice);

            cout << "Shortest path : ";

            while (!s.empty())
            {
                if (s.size() == 1)
                {
                    cout << s.top();
                }
                else
                {
                    cout << s.top() << "--> ";
                }
                s.pop();
            }
        }
        cout << endl;
    }




void SimulateFailure()
{
    char first, second;

    cout << "\n=====SIMULATE LINK FAILURE=====";

    while(true){
        
    cout << "\nEnter first vertex: ";
    cin >> first;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nPlease enter a valid vertex. ";
        continue;
    }


    //Checking whether the first vertex exists
    if(network.find(first)==network.end())
    {
        cout<<"\nVerdex does not exist.Try again. ";
        continue;
    }

    
    cout<<"\nEnter second vertex: ";
    cin>>second;

      if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nPlease enter a valid vertex. ";
        continue;
    }

     //Checking whether the second vertex exists
    if(network.find(second)==network.end())
    {
        cout<<"\nVertex does not exist.Try again. ";
        cout << "\nEnter second vertex: ";
    cin >> second;
    
    while (network.find(second) == network.end())
    {
        cout << "\nVertex does not exist. Try again.";
        cout << "\nEnter second vertex: ";
        cin >> second;
    }
    }

    if(first==second)
    {
        cout<<"\nThe two given vertices are the same.Try something else. ";
        continue;
    }

    //Checking whether the link exists
    if(network[first].find(second)==network[first].end())
    {
        cout<<"\nThis link does not exist.Try something else. ";
        continue;
    }

    //All validation passed
    break;
}
    network[first].erase(second);
    network[second].erase(first);

    cout << "Link " << first << " <----> " << second << " has been removed.\n";
}

void RestoreLink()
{
    char first, second;
    int weight;

    cout << "\n=====RESTORE LINK=====";

   

     while(true){
        
    cout << "\nEnter first vertex: ";
    cin >> first;

    if (network.find(first)!=network.end())
    {break;}

    cout<<"\nThere is no such vertex.Try again.";
     }


     while(true){
        
    cout << "\nEnter second vertex: ";
    cin >> second;

    if (network.find(second)!=network.end())
    {break;}

    cout<<"\nThere is no such vertex.Try again.";
     }



    //Checking whether the two vertices are the same
    while(first==second)
    {
        cout<<"\nThe two given vertices are the same.Give something else.";

        while(true)
        {

             
    cout<<"\nEnter second vertex: ";
    cin>>second;

    if(network.find(second)!=network.end())
        { break; }
        cout<<"\nThere is no such vertex.Try again.";
    }}



    //Checking whether the link already exists
    while(network[first].find(second)!=network[first].end()){
        cout<<"\nThis link already exists.Try something else.";

        while(true){
            cout<<"\nEnter first vertex: ";
            cin>>first;

            if (network.find(first)!=network.end()){
                break;
            }
            
            cout<<"\nThere is no such vertex.Try again.";
        
        
        }

          while(true){
            cout<<"\nEnter second vertex: ";
            cin>>second;

            if (network.find(second)!=network.end()){
                break;
            }
            
            cout<<"\nThere is no such vertex.Try again.";
        
        
        }
    

    while(first==second){
        cout<<"\nThe two given vertices are the same.Give something else.";

        while(true)
        {
            cout<<"\nEnter second vertex: ";
            cin>>second;

            if (network.find(second)!=network.end()){
                break;
            }
            
            cout<<"\nThere is no such vertex.Try again.";
        
        }}
    }

cout << "\nEnter link weight: ";
cin >> weight;

while (cin.fail() || weight < 0)
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nPlease enter a number.";
    }
    else
    {
        cout << "\nThe weight cannot be negative. Try again.";
    }

    cout << "\nEnter link weight: ";
    cin >> weight;
}

network[first][second] = weight;
network[second][first] = weight;

cout << "\nLink " << first << " <----> " << second
     << " has been restored with weight " << weight << endl;
}
int main()
{

    // Adding connections for vertex A
    network['A']['B'] = 5;
    network['A']['C'] = 6;
    network['A']['D'] = 2;

    // Adding connections for vertex B
    network['B']['A'] = 5;
    network['B']['C'] = 1;

    // Adding connections for vertex C
    network['C']['A'] = 6;
    network['C']['B'] = 1;
    network['C']['D'] = 3;

    // Adding connections for vertex D
    network['D']['A'] = 2;
    network['D']['C'] = 3;
    network['D']['X'] = 2;

    // Adding connections for vertex X
    network['X']['D'] = 2;
    network['X']['Y'] = 7;

    // Adding connections for vertex Y
    network['Y']['X'] = 7;


    int choice = 0;
    
    while (choice != 7)
    {
        cout << "\n=====NETWORK ROUTING & RESILIENCE ENGINE=====\n";
        cout << "1.Show network\n";
        cout << "2.Run BFS\n";
        cout << "3.Run DFS\n";
        cout << "4.Find shortest path (Run Dijkstra)\n";
        cout << "5.Simulate link failure\n";
        cout << "6.Restore link\n";
        cout << "7.Exit\n";
        cout << endl;

        cout << "Choose an option: ";
        cin >> choice;


        // Validation chack whether the user put any other type of variable instead of the expected
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nPlease enter a valid number from 1-7.";
            cout << "\nChoose an option: ";
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nPlease enter a number.";
                cout << "Choose an option: ";
                cin >> choice;
            }
        }

        if (choice == 1)
        {
            ShowNetwork();
        }
        else if (choice == 2)
        {

            BFS_Algorithm();
        }

        else if (choice == 3)
        {
            DFS_Algorithm();
        }
        else if (choice == 4)
        {
            Dijkstra_Algorithm();
        }
        else if (choice == 5)
        {
            SimulateFailure();
        }
        else if (choice == 6)
        {
            RestoreLink();
        }
        else if (choice == 7)
        {  cout<<"\nExiting Network Routing Simulator....";
            break;
        }

        else
        {
            cout << "\nInvalid option.Please choose 1-7.";
            cout<<endl;
        }
    }
    return 0;
}
