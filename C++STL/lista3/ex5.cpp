#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using Matrix = std::vector<std::vector<double>>;


Matrix random_matrix(int size, double min = 0.5, double max = 2.0)
{
    Matrix M(size, std::vector<double>(size));

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min, max);

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            M[i][j] = dist(gen);

    return M;
}

Matrix square(const Matrix& A)
{
    int n = A.size();
    Matrix C(n, std::vector<double>(n, 0.0));

    for(int i = 0; i < n; i++)
        for(int k = 0; k < n; k++)
            for(int j = 0; j < n; j++)
                C[i][j] += A[i][k] * A[k][j];

    return C;
}

double measure(int n, int repeats)
{
    Matrix A = random_matrix(n);

    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < repeats; i++)
        square(A);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;

    return diff.count() / repeats;
}

int main()
{
    std::vector<std::pair<int,int>> cases = {
        {50,  50},
        {100, 20},
        {200, 5}
    };

    for(auto [n, reps] : cases)
    {
        double seconds = measure(n, reps);

        int ms = static_cast<int>(seconds * 1000.0);
        double min = seconds / 60.0;
        
        std::cout << "Macierz " << n << "x" << n << "\n";
        std::cout << "czas: " << ms << " ms\n";
        std::cout << "czas: " << std::fixed << std::setprecision(3)
                  << min << " min\n\n";
    }

    return 0;
}
