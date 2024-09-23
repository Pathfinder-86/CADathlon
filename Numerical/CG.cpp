#include <iostream>
#include <vector>
#include <cmath>

// Function to multiply matrix A with vector x
std::vector<double> matVecMult(const std::vector<std::vector<double>>& A, const std::vector<double>& x) {
    std::vector<double> result(x.size(), 0.0);
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[i].size(); ++j) {
            result[i] += A[i][j] * x[j];
        }
    }
    return result;
}

// Function to compute dot product of two vectors
double dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    double result = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

// Function to add two vectors
std::vector<double> vecAdd(const std::vector<double>& a, const std::vector<double>& b) {
    std::vector<double> result(a.size(), 0.0);
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] + b[i];
    }
    return result;
}

// Function to subtract two vectors
std::vector<double> vecSub(const std::vector<double>& a, const std::vector<double>& b) {
    std::vector<double> result(a.size(), 0.0);
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] - b[i];
    }
    return result;
}

// Function to multiply vector by scalar
std::vector<double> vecScalarMult(const std::vector<double>& a, double scalar) {
    std::vector<double> result(a.size(), 0.0);
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] * scalar;
    }
    return result;
}

// Conjugate Gradient method
std::vector<double> conjugateGradient(const std::vector<std::vector<double>>& A, const std::vector<double>& b, const std::vector<double>& x0, double tol = 1e-6, int maxIter = 1000) {
    std::vector<double> x = x0;
    std::vector<double> r = vecSub(b, matVecMult(A, x));
    std::vector<double> p = r;
    double rsOld = dotProduct(r, r);

    for (int i = 0; i < maxIter; ++i) {
        std::vector<double> Ap = matVecMult(A, p);
        double alpha = rsOld / dotProduct(p, Ap);
        x = vecAdd(x, vecScalarMult(p, alpha));
        r = vecSub(r, vecScalarMult(Ap, alpha));
        double rsNew = dotProduct(r, r);
        if (std::sqrt(rsNew) < tol) {
            break;
        }
        p = vecAdd(r, vecScalarMult(p, rsNew / rsOld));
        rsOld = rsNew;
    }

    return x;
}

int main() {
    // Example usage
    std::vector<std::vector<double>> A = {
        {4, 1},
        {1, 3}
    };
    std::vector<double> b = {1, 2};
    std::vector<double> x0 = {2, 1}; // Initial guess

    std::vector<double> x = conjugateGradient(A, b, x0);

    std::cout << "Solution: ";
    for (double xi : x) {
        std::cout << xi << " ";
    }
    std::cout << std::endl;

    return 0;
}