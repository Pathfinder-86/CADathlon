#include <glpk.h>
#include <iostream>

int main() {
    // Create a problem object
    glp_prob *ilp;
    ilp = glp_create_prob();
    glp_set_prob_name(ilp, "Maximize_Z");
    glp_set_obj_dir(ilp, GLP_MAX);

    // Define the number of rows (constraints) and columns (variables)
    glp_add_rows(ilp, 2);
    glp_add_cols(ilp, 2);

    // Set the variables
    glp_set_col_name(ilp, 1, "x1");
    glp_set_col_bnds(ilp, 1, GLP_LO, 0.0, 0.0); // x1 >= 0
    glp_set_col_kind(ilp, 1, GLP_IV); // x1 is an integer variable
    glp_set_obj_coef(ilp, 1, 3.0); // Objective coefficient for x1

    glp_set_col_name(ilp, 2, "x2");
    glp_set_col_bnds(ilp, 2, GLP_LO, 0.0, 0.0); // x2 >= 0
    glp_set_col_kind(ilp, 2, GLP_IV); // x2 is an integer variable
    glp_set_obj_coef(ilp, 2, 2.0); // Objective coefficient for x2

    // Set the constraints and define the constraint matrix
    glp_set_row_name(ilp, 1, "c1");
    glp_set_row_bnds(ilp, 1, GLP_UP, 0.0, 4.0); // x1 + x2 <= 4

    glp_set_row_name(ilp, 2, "c2");
    glp_set_row_bnds(ilp, 2, GLP_UP, 0.0, 5.0); // 2x1 + x2 <= 5

    int ia[1+4], ja[1+4];
    double ar[1+4];

    ia[1] = 1, ja[1] = 1, ar[1] = 1.0; // c1: x1
    ia[2] = 1, ja[2] = 2, ar[2] = 1.0; // c1: x2
    ia[3] = 2, ja[3] = 1, ar[3] = 2.0; // c2: 2x1
    ia[4] = 2, ja[4] = 2, ar[4] = 1.0; // c2: x2

    glp_load_matrix(ilp, 4, ia, ja, ar);

    // Print the objective function
    std::cout << "Objective function: Z = ";
    std::cout << glp_get_obj_coef(ilp, 1) << " * x1 + ";
    std::cout << glp_get_obj_coef(ilp, 2) << " * x2" << std::endl;

    // Solve the problem using integer optimization
    glp_iocp parm;
    glp_init_iocp(&parm);
    parm.presolve = GLP_ON;
    glp_intopt(ilp, &parm);

    // Get the results
    double z = glp_mip_obj_val(ilp);
    double x1 = glp_mip_col_val(ilp, 1);
    double x2 = glp_mip_col_val(ilp, 2);

    // Print the results
    std::cout << "Optimal objective value: " << z << std::endl;
    std::cout << "x1 = " << x1 << std::endl;
    std::cout << "x2 = " << x2 << std::endl;

    // Clean up
    glp_delete_prob(ilp);
    glp_free_env();

    return 0;
}