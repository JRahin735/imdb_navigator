/*-------------------------------------------

Program 4: IMDB

Course: CS 141, Fall 2022, UIC

IDE/System: CLion on MacOS

Author: Rahin Jain

Starter code provided by: Ellen Kidane Dr. Sara Riazi

Description:
        The program is supported by 3 .tsv files. Each file if stored in a vector with help of structs.
        User has 2 input options, they can either search for a movie name or an actor's name.
        The program would search that name and return all possible results to the user.


------------------------------------------- */
#include <iostream>
#include <cctype>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;


/*********************************************** Struct Declarations ***************************************/

struct TitleRecord{

    string titleId;
    string primaryTitle;
    string startYear;
    string genre;
};

struct NameRecord{

    string nameId;
    string primaryTitle;
    string birthYear;
    string deathYear;
    string primaryProfession;
};

struct PrincipalRecord {

    string titleId;
    string nameId;
    string character;
};


/*********************************************** Function Declarations ***************************************/

// Main running functions
void splitString(string line, char delimiter, vector<string>& items );
int run(string titlesFile, string namesFile, string principalsFile);

// TSV to Vector initialization functions
vector<TitleRecord> initTitleVec (vector <string> items);
vector<NameRecord> initNameVec (vector <string> items);
vector<PrincipalRecord> initPrincipalVec (vector <string> items);

// General Logistic functions
vector <string> SplitInput (string userInput, vector <string> items);
string genreSplit (string genre, vector <string> items);

// If user chooses option 1
void findTitle (vector <TitleRecord>& titleVec, vector <int>& resultLocation, vector <string> userInput);
void displayTitles (vector <TitleRecord>& titleVec, vector <int>& resultLocation);
void displayMovies(int movieSelected, vector <TitleRecord>& titleVec, vector <NameRecord>& nameVec,vector <PrincipalRecord>& principalVec, vector <int>& resultLocation);

// If user chooses option 2
void findName     (vector <NameRecord>& nameVec, vector <int>& resultLocation, vector <string> userInput);
void displayNames (vector <NameRecord>& nameVec, vector <int>& resultLocation, vector <string>& items);
void displayActor (int actorSelected, vector <TitleRecord>& titleVec, vector <NameRecord>& nameVec, vector <PrincipalRecord>& principalVec, vector <int>& resultLocation);
/*********************************************** Function Definitions ***************************************/


/** General Logistics ***************************************************************************************/

// Predefined function.
// Parameters, a string, a character (used as a delimiter) and a vector (pass by ref) to save the results.
void splitString(string line, char delimiter, vector<string>& items ) {
    stringstream s_stream(line);
    while (s_stream.good()) {
        string item;
        getline(s_stream, item, delimiter);
        items.push_back(item);
    }
}


// Convert a string into a vector. Splits different words given as inputs in different index values in a vector.
// Parameters, a string (the actual input given by user), a vector Uto save the split-ed string in).
// Outputs, a vector storing the user input
vector <string> SplitInput (string userInput, vector <string> items) {

    splitString(userInput, '+', items );

    return items;
}

// Removes ',' from the genre and adds space
// Parameters, a string (a bunch of genres saved in one string), a vector to use in the splitString() func.
// Outputs, a string storing the genres
string genreSplit (string genre, vector <string> items) {

    splitString(genre, ',', items);
    genre = "";
    for (int i = 0; i < items.size(); i++){

        genre += items.at(i);
        genre += ' ';
    }

    return genre;
}


/** TSV to vector init funcs. **********************************************************************************/

// All 3 function work on the same principal,
// parameters, a vector storing the items from the tsv file
// Setting the data up properly in struct format
// saving the structs in a vector and returning that vector

// For Movie titles file
vector<TitleRecord> initTitleVec (vector <string> items) {

    // Local variable declaration(s)/ assignment(s)
    vector <TitleRecord> titleVec;

    // Loops across the items vector
    for (int i = 0; i < items.size(); i=i+9){

        // Creating object and initializing values
        TitleRecord TR;

        TR.titleId = items.at(i);
        TR.primaryTitle = items.at(i+2);
        TR.startYear = items.at(i+5);
        TR.genre = items.at(i+8);

        // Adding the object created into the vector
        titleVec.push_back(TR);
    }
    return titleVec;
}


// For Actor Name file
vector<NameRecord> initNameVec (vector <string> items){

    // Local variable declaration(s)/ assignment(s)
    vector <NameRecord> nameVec;

    // Loops across the items vector
    for (int i = 0; i < items.size(); i=i+6){

        // Creating object and initializing values
        NameRecord TR;

        TR.nameId = items.at(i);
        TR.primaryTitle = items.at(i+1);
        TR.birthYear = items.at(i+2);
        TR.deathYear = items.at(i+3);
        TR.primaryProfession = items.at(i+4);

        // Adding the object created into the vector
        nameVec.push_back(TR);
    }
    return nameVec;
}

// For Principal file
vector<PrincipalRecord> initPrincipalVec (vector <string> items){

    // Local variable declaration(s)/ assignment(s)
    vector <PrincipalRecord> principalVec;

    // Loops across the items vector
    for (int i = 0; i < items.size(); i=i+6){

        // Creating object and initializing values
        PrincipalRecord TR;

        TR.titleId = items.at(i);
        TR.nameId = items.at(i+2);
        TR.character = items.at(i+5);

        // Adding the object created into the vector
        principalVec.push_back(TR);
    }
    return principalVec;
}


/** Option choice 1 ************************************************************************************/

// Searches for the user input in the data (in form of vectors <struct>), for every piece of data that meets the criterion,
// the location is saved in a vector
// Parameter, vector (storing movie title data) (pass by ref), vector (storing the index values that meet the search criterion) (pass by ref),
// vector (storing user input)
void findTitle (vector <TitleRecord>& titleVec, vector <int>& resultLocation, vector <string> userInput){

    // loops across titleVec
    for (int n = 0; n < titleVec.size(); n++){

        // Local variable declaration(s)/ assignment(s)
        int counter = 0;
        string tempString = titleVec.at(n).primaryTitle;
        string movieTitle;

        // loops across tempString, lower cases all characters before comparing
        for (int a = 0; a < tempString.size(); a++){
            movieTitle.push_back(tolower (tempString.at(a)));
        }

        // loops across userInput
        for (int i = 0; i < userInput.size(); i++){

            // searching
            size_t found = movieTitle.find(userInput.at(i));
            if (found != string::npos){

                counter++;
            }
        }

        // stores the location if criterion met
        if (counter == userInput.size()){

            resultLocation.push_back(n);
        }
    }
}

// Displays the results.
// Parameters, vector (storing movie title data) (pass by ref), vector (storing location of results) (pass by ref)
void displayTitles (vector <TitleRecord>& titleVec, vector <int>& resultLocation, vector <string>& items){

    // Local variable declaration(s)/ assignment(s)
    int count = 0;
    int location = -1;

    // If not results from the searching, terminates after displaying error message
    if (resultLocation.size() == 0) {
        cout << "No match found!" << endl;
        return;
    }

    // loops across resultLocation
    for (int i = 0; i < resultLocation.size(); i++) {

        location = resultLocation.at(i);

        // Removing ',' from between the genres
        string genre = titleVec.at(location).genre;
        genre = genreSplit(genre, items);

        // Printing Results
        cout << count << ": " << endl;
        cout << "Title: " << titleVec.at(location).primaryTitle << endl;
        cout << "Year: " << titleVec.at(location).startYear << endl;
        cout << "Genre: " << genre << endl;
        cout << "--------------" << endl;

        count++;
    }
}

// Displays the cast members of the movie selected by the user.
// Parameters, integer (storing user input), vector (storing movie title data) (pass by ref), vector (storing actor name data) (pass by ref),
// vector (storing principal data) (pass by ref), vector (storing location of results) (pass by ref)
void displayMovies(int movieSelected, vector <TitleRecord>& titleVec, vector <NameRecord>& nameVec,vector <PrincipalRecord>& principalVec, vector <int>& resultLocation){

    // Local variable declaration(s)/ assignment(s)
    vector <int> principalLocation;
    vector <string> cast;
    vector <string> rolesPlayed;

    // Fetching the location of the desired struct in the titleVec and then fetching the title ID
    int location = resultLocation.at(movieSelected);
    string tConst = titleVec.at(location).titleId;

    // loops across principalVec
    for (int i = 0; i < principalVec.size(); ++i) {

        // updates principalLocation if criterion is met
        // updates rolesPlayed if criterion is met
        if ( (principalVec.at(i).titleId) == tConst){

            principalLocation.push_back(i);
            rolesPlayed.push_back(principalVec.at(i).character);
        }
    }

    // loops across principalLocation
    for (int a = 0; a < principalLocation.size(); ++a) {

        int locate = principalLocation.at(a);
        string nConst = principalVec.at(locate).nameId;

        // loops across nameVec
        for (int b = 0; b < nameVec.size(); ++b) {

            // updates cast is criterion is met.
            if (nConst == nameVec.at(b).nameId) {
                cast.push_back(nameVec.at(b).primaryTitle);
            }
        }
    }

    // loops across cast
    for (int c = 0; c < cast.size(); ++c) {

        // Prints results
        cout << cast.at(c) << rolesPlayed.at(c) << endl;
    }
}


/** Option choice 2 ************************************************************************************/

// Searches for the user input in the data (in form of vectors <struct>), for every piece of data that meets the criterion,
// the location is saved in a vector
// Parameter, vector (storing actor name data) (pass by ref), vector (storing the index values that meet the search criterion) (pass by ref),
// vector (storing user input)
void findName (vector <NameRecord>& nameVec,vector <int>& resultLocation,vector <string> userInput){

    // loops across nameVec
    for (int i = 0; i < nameVec.size(); ++i) {

        int counter = 0;
        string tempString = nameVec.at(i).primaryTitle;
        string nameTitle;

        // loops across tempString, lower cases all characters before comparing
        for (int j = 0; j < tempString.size(); ++j) {
            nameTitle.push_back(tolower(tempString.at(j)));
        }

        // loops across userInput
        for (int a = 0; a < userInput.size(); ++a) {
            // Searching
            size_t found = nameTitle.find(userInput.at(a));
            if (found != string::npos) {
                counter++;
            }
        }

        // Stores location if criterion is met
        if (counter == userInput.size()) {
             resultLocation.push_back(i);
        }
    }
}


// Displays the results.
// Parameters, vector (storing actor name data) (pass by ref), vector (storing location of results) (pass by ref)
void displayNames (vector <NameRecord>& nameVec, vector <int>& resultLocation, vector <string>& items){

    // Local variable declaration(s)/ assignment(s)
    int count = 0;
    int location = -1;

    // If not results from the searching, terminates after displaying error message
    if (resultLocation.size() == 0) {
        cout << "No match found!" << endl;
        return;
    }

    // loops across resultLocation
    for (int i = 0; i < resultLocation.size(); i++) {

        location = resultLocation.at(i);

        // Printing Results
        cout << count << ": " << endl;
        cout << nameVec.at(location).primaryTitle << endl;
        cout << nameVec.at(location).primaryProfession << endl;
        cout << "(" << nameVec.at(location).birthYear << "-"
             << nameVec.at(location).deathYear << ")" << endl;
        cout << "--------------" << endl;

        count++;
    }
}

void displayActor (int actorSelected, vector <TitleRecord>& titleVec, vector <NameRecord>& nameVec, vector <PrincipalRecord>& principalVec, vector <int>& resultLocation){

    // Local variable declaration(s)/ assignment(s)
    vector <int> principalLocation;
    vector <string> movies;
    vector <string> startYear;
    vector <string> characters;

    int location = resultLocation.at(actorSelected);
    string nConst = nameVec.at(location).nameId;

    // looping across principalVec
    for (int i = 0; i < principalVec.size(); ++i) {

        // updates principalLocation if criterion is met
        // updates characters if criterion is met
        size_t foundName = principalVec.at(i).nameId.find(nConst);
        if (foundName != string::npos){

            principalLocation.push_back(i);
            characters.push_back(principalVec.at(i).character);
        }
    }

    for (int a = 0; a < principalLocation.size(); ++a) {

        int locate = principalLocation.at(a);
        string tConst = principalVec.at(locate).titleId;

        // loops across titleVec
        for (int b = 0; b < titleVec.size(); ++b) {

            // updates movies is criterion is met.
            size_t foundTitle = titleVec.at(b).titleId.find(tConst);
            if (foundTitle != string::npos && titleVec.at(b).titleId.size() == tConst.size()) {

                movies.push_back(titleVec.at(b).primaryTitle);
                startYear.push_back((titleVec.at(b).startYear));
            }
        }
    }

    // loops across movies
    for (int c = 0; c < movies.size(); ++c) {

        // Prints results
        cout << movies.at(c) << " " << startYear.at(c) << " " << characters.at(c) << endl;
    }
}

/**********************************************************************************************************/

// The actual main function
int run(string titlesFile, string namesFile, string principalsFile) {

    // Local variable declaration(s)/ assignment(s)
    vector <string> items;
    vector <string> searchPhrase;
    vector <int> resultLocation;

    string placeholderA;
    string placeholderB;
    string placeholderC;

    int optionChoice;
    string userInput;

    //Asking for user input
    cout << "Select a menu option: " << endl;
    cout << '\t' << "1. Search for movies" << endl
         << '\t' <<"2. Search for actors/actresses" << endl
         << '\t' <<"3. Exit" << endl;
    cout << "Your choice --> ";
    cin >> optionChoice;
    cout << endl <<"Enter search phrase: ";
    cin >> userInput;

    // saving tsv files into vectors
    // File 1
    ifstream movieTitles;
    movieTitles.open("movie.titles.tsv");
    while (getline(movieTitles, placeholderA)){
        splitString(placeholderA, '\t', items );
    }

    vector<TitleRecord> titleVec = initTitleVec (items);
    movieTitles.close();
    items.clear();

    // File 2
    ifstream movieNames;
    movieNames.open("movie.names.tsv");
    while (getline(movieNames, placeholderB)){
        splitString(placeholderB, '\t', items);
    }

    vector<NameRecord> nameVec = initNameVec(items);
    movieNames.close();
    items.clear();

    // File 3
    ifstream moviePrincipals;
    moviePrincipals.open("movie.principals.tsv");
    while (getline(moviePrincipals, placeholderC)){
        splitString(placeholderC, '\t', items);
    }

    vector<PrincipalRecord> principalVec = initPrincipalVec(items);
    moviePrincipals.close();
    items.clear();

    // Saving input as a vector
    searchPhrase = SplitInput(userInput, items);
    string userInputAllLowered;
    vector <string> searchPhraseLowered;
    items.clear();

    // Lower casing searchPhrase
    for (int a = 0; a < searchPhrase.size(); a++) {

        string temp = searchPhrase.at(a);
        for (int b = 0; b < temp.size(); b++){
            userInputAllLowered.push_back(tolower(temp.at(b)));
        }

        searchPhraseLowered.push_back(userInputAllLowered);
        userInputAllLowered = "";
    }

    // Searching for userInput
    // For option 1
    if (optionChoice == 1){

        // Searching and displaying the movie titles
        findTitle(titleVec, resultLocation, searchPhraseLowered);
        displayTitles(titleVec, resultLocation, items);

        // asking for user input
        int movieSelected;
        cout << "Select a movie to see its actors/actresses (-1 to go back to the main menu): " << endl;
        cin >> movieSelected;

        if (movieSelected == -1){

            // Taking user back to the beginning
            run(titlesFile, namesFile, principalsFile);
        } else {

            // searching and displaying the cast members of chosen movie
            displayMovies(movieSelected, titleVec, nameVec, principalVec, resultLocation);
        }

        // logistics
        resultLocation.clear();
        items.clear();
    }
    // For option 2
    else if (optionChoice == 2){

        // searching and displaying the actor details
        findName (nameVec, resultLocation, searchPhraseLowered);
        displayNames(nameVec, resultLocation, items);

        // asking for user input
        int actorSelected;
        cout << "Select and actor/actress to see movies (-1 to go back to the previous menu): " << endl;
        cin >> actorSelected;

        if (actorSelected == -1){

            // Taking user back to the beginning
            run(titlesFile, namesFile, principalsFile);
        } else{

            //searching and displaying movies of selected actor
            displayActor (actorSelected, titleVec, nameVec, principalVec, resultLocation);
        }

        // logistics
        resultLocation.clear();
        items.clear();
    }
    return 0;
}


// Dummy main function
int main() {
    //Change these addresses according to your local machine
    string titlesFile =	"movie.titles.tsv";
    string namesFile = "movie.names.tsv";
    string principalsFile = "movie.principals.tsv";

    //DO NOT change the main function. The main function will be removed by the autograder
    run(titlesFile, namesFile, principalsFile);
    return 0;
}
