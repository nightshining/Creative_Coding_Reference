 auto someStuff = "someString";
    auto someMoreStuff = 50.001f;
    auto someOtherStuff = 200;

    cout << someStuff << ' ' << someMoreStuff << ' ' << someOtherStuff << ' ' << endl;

    vector<float> someNumbers;

    someNumbers.resize(5);

    for ( auto & someNumbers : someNumbers ) {

        someNumbers = ofRandom(5);
        cout << someNumbers << endl;
    }

    map<string, int> someNames;

    someNames["one"] = 1;
    someNames["two"] = 2;
    someNames["three"] = 3;
    someNames["four"] = 4;
    someNames["five"] = 5;

    for (auto i : someNames ) {
        cout << i.first << ' ' << i.second << endl;
    }