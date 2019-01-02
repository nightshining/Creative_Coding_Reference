///define map

    map<string, int> food;

///approach 1
    food["taco"] = 1;
    food["kimchi"] = 10;
    food["sushi"] = 100;

    cout << food["taco"] << endl; // this prints the corresponding string

    for (auto iter = food.begin(); iter != food.end(); ++iter ) {

        cout << "Food: " << iter->first << " Value: " << iter->second << endl;

        if (iter->first == "taco") {

            cout << "This Works!" << endl;
        }
    }

///approach 2
  map<int, string>::iterator it = food.begin();

    for (it; it != food.end(); ++it)
    {
        string printMap = ofToString(it->first) + " " + it->second;
        cout << printMap << endl;
    }