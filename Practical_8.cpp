#include <iostream>
#include <iomanip> // For formatting output
using namespace std;

#define MAX 20

int n;
float p[MAX], q[MAX], wt[MAX][MAX], c[MAX][MAX];
int r[MAX][MAX];

// Function to construct the Optimal Binary Search Tree
void con_obst() {
    int i, j, k, l, root;
    float minCost, cost;

    // Initialize weight, cost, and root matrices
    for (i = 0; i <= n; i++) {
        wt[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
    }

    // Filling tables for tree sizes 1 to n
    for (l = 1; l <= n; l++) {  // l is the subtree size
        for (i = 0; i <= n - l; i++) {
            j = i + l;
            
            // Compute weight matrix
            wt[i][j] = wt[i][j - 1] + p[j] + q[j];

            minCost = 999;
            root = -1;

            // Find minimum cost root
            for (k = i + 1; k <= j; k++) {
                cost = c[i][k - 1] + c[k][j] + wt[i][j]; // Cost formula
                
                if (cost < minCost) {
                    minCost = cost;
                    root = k;
                }
            }

            // Store the optimal cost and root
            c[i][j] = minCost;
            r[i][j] = root;
        }
    }
}

// Function to print the Optimal Binary Search Tree
void print(int l1, int r1, int parent, bool isLeft) {
    if (l1 >= r1)
        return;

    int root = r[l1][r1];
    if (parent == -1)
        cout << "Root of BST: " << root << "\n";
    else
        cout << (isLeft ? "Left child of " : "Right child of ") << parent << " is " << root << "\n";

    print(l1, root - 1, root, true);  // Print left subtree
    print(root, r1, root, false);     // Print right subtree
}

int main() {
    int i;

    cout << "Enter number of keys: ";
    cin >> n;

    cout << "Enter probabilities for successful searches (p1 to pn): ";
    for (i = 1; i <= n; i++) {
        cin >> p[i];
    }

    cout << "Enter probabilities for unsuccessful searches (q0 to qn): ";
    for (i = 0; i <= n; i++) {
        cin >> q[i];
    }

    con_obst();

    cout << "\nWeight Matrix:\n";
    for (i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << setw(6) << wt[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nCost Matrix:\n";
    for (i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << setw(6) << c[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nRoot Matrix:\n";
    for (i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << setw(6) << r[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nOptimal Binary Search Tree Structure:\n";
    print(0, n, -1, false);

    return 0;
}
