#include <glpk.h>
#include <iostream>

int main() {
    // Create a problem object
    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "Maximize_Z");
    glp_set_obj_dir(lp, GLP_MAX);

    // Define the number of rows (constraints) and columns (variables)
    glp_add_rows(lp, 2);
    glp_add_cols(lp, 2);

    // Set the variables
    glp_set_col_name(lp, 1, "x1");
    glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0); // x1 >= 0
    glp_set_obj_coef(lp, 1, 3.0); // Objective coefficient for x1

    glp_set_col_name(lp, 2, "x2");
    glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0); // x2 >= 0
    glp_set_obj_coef(lp, 2, 2.0); // Objective coefficient for x2

    // Set the constraints and define the constraint matrix
    glp_set_row_name(lp, 1, "c1");
    glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 4.0); // x1 + x2 <= 4

    glp_set_row_name(lp, 2, "c2");
    glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 5.0); // 2x1 + x2 <= 5

    int ia[1+4], ja[1+4];
    double ar[1+4];

    ia[1] = 1, ja[1] = 1, ar[1] = 1.0; // c1: x1
    ia[2] = 1, ja[2] = 2, ar[2] = 1.0; // c1: x2
    ia[3] = 2, ja[3] = 1, ar[3] = 2.0; // c2: 2x1
    ia[4] = 2, ja[4] = 2, ar[4] = 1.0; // c2: x2

    glp_load_matrix(lp, 4, ia, ja, ar);

    // Print the objective function
    std::cout << "Objective function: Z = ";
    std::cout << glp_get_obj_coef(lp, 1) << " * x1 + ";
    std::cout << glp_get_obj_coef(lp, 2) << " * x2" << std::endl;

    // Solve the problem
    int status = glp_simplex(lp, NULL);

    // Check if the solution is feasible
    if (status == 0) {
        int sol_status = glp_get_status(lp);
        if (sol_status == GLP_OPT) {
            std::cout << "Solution is optimal." << std::endl;
        } else if (sol_status == GLP_FEAS) {
            std::cout << "Solution is feasible." << std::endl;
        } else {
            std::cout << "Solution is infeasible or undefined." << std::endl;
        }
    } else {
        std::cout << "Solver failed to find a solution." << std::endl;
    }

    // Get the results if feasible
    if (status == 0 && (glp_get_status(lp) == GLP_OPT || glp_get_status(lp) == GLP_FEAS)) {
        double z = glp_get_obj_val(lp);
        double x1 = glp_get_col_prim(lp, 1);
        double x2 = glp_get_col_prim(lp, 2);

        // Print the results
        std::cout << "Optimal objective value: " << z << std::endl;
        std::cout << "x1 = " << x1 << std::endl;
        std::cout << "x2 = " << x2 << std::endl;
    }

    // Clean up
    glp_delete_prob(lp);
    glp_free_env();

    return 0;
}