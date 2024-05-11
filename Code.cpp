#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
float First_Conductor_Voltage, Second_Conductor_Voltage, Infinitismal_Gap_Voltage;
int No_Symmetry_Lines, n;
void display(vector<vector<float>>& Grid, int it)
{
    //displaying the grid
    cout << setfill(' ');
    cout << "Iteration " << it << '\n';
    cout << ' ';
    for (int i = 1; i <= (No_Symmetry_Lines + 2) * 9-3; i++)
        cout << '_';
    cout << '\n';
    for (int i = 0; i <= No_Symmetry_Lines + 1; i++)
    {
        cout << '|';
        cout << setw(4) << '|';
        for (int j = 1; j <= No_Symmetry_Lines + 1; j++)
        {
            cout << setw(9) << '|';
        }
        cout<< setw(3) << '|' << '\n';

        cout << '|';
        for (int j = 0; j <= No_Symmetry_Lines + 1; j++)
        {
            if (j == 0)
            {
                cout << setfill('_') << setw(6) << Grid[i][j];
            }
            else
                cout << setfill('_') << setw(9) << Grid[i][j];
        }
        cout << '|';
        if(i!=No_Symmetry_Lines + 1)
        {
            cout << setfill(' ');
            cout << '\n' << '|';
            cout << setw(4) << '|';
            for (int j = 1; j <= No_Symmetry_Lines + 1; j++)
            {
                cout << setw(9) << '|';
            }
            cout << setw(3) << '|';
        }
        cout << '\n';
    }
    cout << '|';
    for (int i = 6; i <= (No_Symmetry_Lines + 2) * 9+2; i++)
    {
        if (i % 9 == 0)
            cout << '|';
        else
            cout << '_';
    }
    cout<<'|' << '\n';
}

void setting_Up_Grid(vector<vector<float>>& Grid)
{
    //setting up initial Voltage points of conductors and gaps
    Grid[0][0] = Infinitismal_Gap_Voltage, Grid[0][No_Symmetry_Lines + 1] = Infinitismal_Gap_Voltage;
    for (int i = 1; i <= No_Symmetry_Lines; i++)
    {
        Grid[0][i] = First_Conductor_Voltage;
        Grid[No_Symmetry_Lines + 1][i] = Second_Conductor_Voltage;
    }
    for (int i = 1; i <= No_Symmetry_Lines + 1; i++)
    {
        Grid[i][0] = Second_Conductor_Voltage;
        Grid[i][No_Symmetry_Lines + 1] = Second_Conductor_Voltage;
    }
    //setting up the central point
    n = (No_Symmetry_Lines + 1) / 2;
    Grid[n][n] = (Grid[0][n] + Grid[No_Symmetry_Lines + 1][n] + Grid[n][0] + Grid[n][No_Symmetry_Lines + 1]) / 4.00;
    // setting up other unset points to -1
    for (int i = 1; i < No_Symmetry_Lines + 1; i++)
    {
        for (int j = 1; j < No_Symmetry_Lines + 1; j++)
        {
            if (i == n && j == n)
                continue;
            Grid[i][j] = -1;
        }
    }
}
void prep(vector<vector<float>>& Grid)
{
    //preparing the grid
    if (No_Symmetry_Lines % 2 == 0)
    {
        cout << "The symmetry lines number is preferable to be an Odd number\n";
        cout << "The Corrected symmetry line numbers = " << ++No_Symmetry_Lines << '\n';
    }
    setting_Up_Grid(Grid);
    display(Grid, 0);
}

void pre_solve(vector<vector<float>>& Grid)
{
    int nn = n;
    //upper half diagonal points
    while (--n)
    {
        for (int d = 0; n - d >= 0 && n + d <= No_Symmetry_Lines + 1; d++)
        {
            if (Grid[n - d][n - d] != -1 && Grid[n + d][n + d] != -1 && Grid[n - d][n + d] != -1 && Grid[n + d][n - d] != -1)
            {
                Grid[n][n] = (Grid[n - d][n - d] + Grid[n + d][n + d] + Grid[n - d][n + d] + Grid[n + d][n - d]) / 4;
                Grid[n][No_Symmetry_Lines + 1 - n] = Grid[n][n];
                break;
            }
        }
    }
    //lower half diagonal points
    n = nn;
    while (++n && n < No_Symmetry_Lines + 1)
    {
        for (int d = 0; n - d >= 0 && n + d <= No_Symmetry_Lines + 1; d++)
        {
            if (Grid[n - d][n - d] != -1 && Grid[n + d][n + d] != -1 && Grid[n - d][n + d] != -1 && Grid[n + d][n - d] != -1)
            {
                Grid[n][n] = (Grid[n - d][n - d] + Grid[n + d][n + d] + Grid[n - d][n + d] + Grid[n + d][n - d]) / 4;
                Grid[n][No_Symmetry_Lines + 1 - n] = Grid[n][n];
                break;
            }
        }
    }
    //getting rid of -1 values to complete the 0 iteration
    for (int i = 1; i < No_Symmetry_Lines + 1; i++)
    {
        for (int j = 1; j < No_Symmetry_Lines + 1; j++)
        {
            if (Grid[i][j + 1] == -1 || Grid[i][j - 1] == -1 || Grid[i + 1][j] == -1 || Grid[i - 1][j] == -1)
                continue;
            else if (Grid[i][j] == -1)
            {
                Grid[i][j] = (Grid[i][j + 1] + Grid[i][j - 1] + Grid[i + 1][j] + Grid[i - 1][j]) / 4;
            }
        }
    }
    for (int i = 1; i < No_Symmetry_Lines + 1; i++)
    {
        for (int j = 1; j < No_Symmetry_Lines + 1; j++)
        {
            if (Grid[i][j + 1] == -1 || Grid[i][j - 1] == -1 || Grid[i + 1][j] == -1 || Grid[i - 1][j] == -1)
                continue;
            else if (Grid[i][j] == -1)
            {
                Grid[i][j] = (Grid[i][j + 1] + Grid[i][j - 1] + Grid[i + 1][j] + Grid[i - 1][j]) / 4;
            }
        }
    }
}
void solve(vector<vector<float>>& Grid)
{
    int iteratiion_num = 0;
    float p;
    bool r = false;
    n = (No_Symmetry_Lines + 1) / 2;
    while (++iteratiion_num)
    {
        //upper half
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                p = (Grid[i][j + 1] + Grid[i][j - 1] + Grid[i + 1][j] + Grid[i - 1][j]) / 4;
                if (abs(p - Grid[i][j]) <= 0.01)
                    r = true;
                else
                    r = false;
                Grid[i][j] = p;
                Grid[i][No_Symmetry_Lines + 1 - j] = p;

            }
        }

        //lower half
        for (int i = n; i <= No_Symmetry_Lines ; i++)
        {
            for (int j = n; j <= No_Symmetry_Lines; j++)
            {
                p = (Grid[i][j + 1] + Grid[i][j - 1] + Grid[i + 1][j] + Grid[i - 1][j]) / 4;
                if (abs(p - Grid[i][j]) <= 0.01)
                    r = true;
                else
                    r = false;
                Grid[i][j] = p;
                Grid[i][No_Symmetry_Lines + 1 - j] = p;

            }
        }

        display(Grid, iteratiion_num);
        if (r)
            break;
    }
}

int main()
{
    cout << fixed << setprecision(2);
    cout << "Enter the first conductor voltage\n";
    cin >> First_Conductor_Voltage;

    cout << "Enter the second conductor voltage\n";
    cin >> Second_Conductor_Voltage;

    //the gab voltage is equal to the median between the conductors voltage
    Infinitismal_Gap_Voltage = (First_Conductor_Voltage + Second_Conductor_Voltage) / 2;

    cout << "Enter the number of preferred Line of symmetry\n";
    cin >> No_Symmetry_Lines;

    vector<vector<float>>Grid(No_Symmetry_Lines + 2, vector<float>(No_Symmetry_Lines + 2));
    prep(Grid);
    pre_solve(Grid);
    pre_solve(Grid);
    solve(Grid);
}
