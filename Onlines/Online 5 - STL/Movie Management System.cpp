#include <bits/stdc++.h>
using namespace std;

#define paragraph cout << endl

int sl = 0;

struct movie
{
    string title;
    string id;
    int available;
    int rented = 0;
    vector<pair<int, int>> dates;
};

vector<movie> MovieSystem;

void addMovie()
{
    paragraph;
    string title;
    int avail;
    cout << "Enter title and available copies: ";
    cin >> title >> avail;
    MovieSystem.resize(sl + 1);
    MovieSystem[sl].title = title;
    MovieSystem[sl].available = avail;
    MovieSystem[sl].id = "MOV" + to_string((sl + 100));
    sl++;
    paragraph;
}

void removeMovie()
{
    paragraph;
    cout << "Enter Movie ID to remove: ";
    string search;
    cin >> search;
    int i = 0;
    for (auto m : MovieSystem)
    {
        i++;
        if (m.id == search)
        {
            MovieSystem.erase(MovieSystem.begin() + i);
            return;
        }
    }
    paragraph;
}

void displayMovies()
{
    paragraph;
    cout << "Available Movies:" << endl;
    paragraph;
    for (auto m : MovieSystem)
    {
        cout << "Title: " << m.title << endl
             << "Id: " << m.id << endl
             << "Available copies: " << m.available << endl;

        if (m.rented)
        {
            cout << "Rented Copies: " << m.rented << endl;
        }

        paragraph;
    }
    paragraph;
}

void rentMovie()
{
    paragraph;
    cout << "Enter Movie ID to rent: ";
    string renting;
    cin >> renting;
    for (int i = 0; i < MovieSystem.size(); i++)
    {
        if (MovieSystem[i].id == renting)
        {
            if (MovieSystem[i].available)
            {
                MovieSystem[i].available--;
                MovieSystem[i].rented++;
                cout << "Renting Movie: " << MovieSystem[i].title << endl;

                MovieSystem[i].dates.resize(MovieSystem[i].rented);
                cout << "Enter Date (dd mm): ";
                cin >> MovieSystem[i].dates[MovieSystem[i].rented - 1].first >> MovieSystem[i].dates[MovieSystem[i].rented - 1].second;
                return;
            }
            else
            {
                cout << "All of the movie is rented" << endl;
                return;
            }
        }
    }
    cout << "Movie is not available!" << endl;
    paragraph;
}

void returnMovie()
{
    cout << "Enter Movie ID to return: ";
    string returning;
    cin >> returning;
    int i = 0;
    for (auto m : MovieSystem)
    {
        i++;
        if (m.id == returning)
        {
            if (m.rented)
            {
                MovieSystem[i].rented--;
                MovieSystem[i].available++;

                int dd, mm;
                cout << "Enter returning date (dd mm): ";
                cin >> dd >> mm;

                dd += (mm * 30);

                cout << "Returned Succesfully!" << endl;

                int rentDate = (MovieSystem[i].dates.back().second) * 30 + MovieSystem[i].dates.back().first;

                if ((rentDate - dd) > 30)
                {
                    cout << "Due Cost: " << 2 * (rentDate - dd) << endl;
                }
                cout << "Returned Succesfully!" << endl;
                return;
            }
        }
    }
    cout << "Movie Not Rented!" << endl;
    return;
    paragraph;
}

void displayRented()
{
    paragraph;
    cout << "Rented Movies: " << endl;
    paragraph;
    for (auto m : MovieSystem)
    {
        if (m.rented)
        {
            cout << "Title: " << m.title << endl
                 << "Id: " << m.id << endl
                 << "Rented Copies: " << m.rented << endl
                 << "On (dd mm):" << endl;
            for (auto ddmm : m.dates)
            {
                cout << ddmm.first << " " << ddmm.second;
            }

            paragraph;
        }
    }
    paragraph;
}

int main()
{
    int choice;
    cout << "1. Add Movie" << endl
         << "2. Remove Movie" << endl
         << "3. Display All Movies" << endl
         << "4. Rent Movie" << endl
         << "5. Return Movie" << endl
         << "6. Display All Rented Movies" << endl
         << "7. Exit System" << endl;
    paragraph;
    while (true)
    {
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1)
        {
            addMovie();
        }
        else if (choice == 3)
        {
            displayMovies();
        }
        else if (choice == 2)
        {
            removeMovie();
        }
        else if (choice == 4)
        {
            rentMovie();
        }
        else if (choice == 5)
        {
            returnMovie();
        }
        else if (choice == 6)
        {
            displayRented();
        }
        // 5 Movie return + Cost check: If return date is more than 30 days, cost = 2*(30-days)
        // 6 Checks which movies are rented and are due
        else if (choice == 7)
        {
            cout << "Exiting System";
            break;
        }
        // cout << "loop";
    }
}
