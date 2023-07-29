#include <gtest/gtest.h>
#include <iostream>

#include "../include/binLinkedList.h"


class BasicStructureInfoTest : public ::testing::Test {
protected:
    int num_atoms;
    double basis_vectors[3][3];
    int atomic_numbers[12];
    double frac_coords[12][3];


    static void SetUpTestSuite() {
        std::cout << "BasicStructureInfo is setting up...\n";
    }


    static void TearDownTestSuite() {
        std::cout << "BasicStructureInfo is tearing down...\n";
    }


    void SetUp() override {
        num_atoms = 12;
        
        basis_vectors[0][0] = 3.1903157348;
        basis_vectors[0][1] = 5.5257885468;
        basis_vectors[0][2] = 0.0000000000;
        basis_vectors[1][0] = -6.3806307800;
        basis_vectors[1][1] = 0.0000000000;
        basis_vectors[1][2] = 0.0000000000;
        basis_vectors[2][0] = 0.0000000000;
        basis_vectors[2][1] = 0.0000000000;
        basis_vectors[2][2] = 23.1297687334;

        atomic_numbers[0] = 42;
        atomic_numbers[1] = 16;
        atomic_numbers[2] = 16;
        atomic_numbers[3] = 42;
        atomic_numbers[4] = 16;
        atomic_numbers[5] = 16;
        atomic_numbers[6] = 42;
        atomic_numbers[7] = 16;
        atomic_numbers[8] = 16;
        atomic_numbers[9] = 42; 
        atomic_numbers[10] = 16;
        atomic_numbers[11] = 16;

        frac_coords[0][0] = 0.333333333333;
        frac_coords[0][1] = 0.166666666667;
        frac_coords[0][2] = 0.500000000000;
        frac_coords[1][0] = 0.166666666667;
        frac_coords[1][1] = 0.333333333333;
        frac_coords[1][2] = 0.432343276548;
        frac_coords[2][0] = 0.166666666667;
        frac_coords[2][1] = 0.333333333333;
        frac_coords[2][2] = 0.567656723452;
        frac_coords[3][0] = 0.333333333333;
        frac_coords[3][1] = 0.666666666667;
        frac_coords[3][2] = 0.500000000000;
        frac_coords[4][0] = 0.166666666667;
        frac_coords[4][1] = 0.833333333333;
        frac_coords[4][2] = 0.432343276548;
        frac_coords[5][0] = 0.166666666667;
        frac_coords[5][1] = 0.833333333333;
        frac_coords[5][2] = 0.567656723452;
        frac_coords[6][0] = 0.833333333333;
        frac_coords[6][1] = 0.166666666667;
        frac_coords[6][2] = 0.500000000000;
        frac_coords[7][0] = 0.666666666667;
        frac_coords[7][1] = 0.333333333333;
        frac_coords[7][2] = 0.432343276548;
        frac_coords[8][0] = 0.666666666667;
        frac_coords[8][1] = 0.333333333333;
        frac_coords[8][2] = 0.567656723452;
        frac_coords[9][0] = 0.833333333333;
        frac_coords[9][1] = 0.666666666667;
        frac_coords[9][2] = 0.500000000000;
        frac_coords[10][0] = 0.666666666667;
        frac_coords[10][1] = 0.833333333333;
        frac_coords[10][2] = 0.432343276548;
        frac_coords[11][0] = 0.666666666667;
        frac_coords[11][1] = 0.833333333333;
        frac_coords[11][2] = 0.567656723452;
    }

    void TearDown() override {

    }
};  // class : BasicStructureInfo 



TEST_F(BasicStructureInfoTest, default_init) {
    matersdk::BasicStructureInfo<double> basic_structure_info;
    //basic_structure_info.show();
}

TEST_F(BasicStructureInfoTest, init) {
    matersdk::Structure<double> structure_1(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    matersdk::BasicStructureInfo<double> bst_1(structure_1);
    //bst_1.show();
    
    matersdk::Structure<double> structure_2;
    matersdk::BasicStructureInfo<double> bst_2(structure_2);
    //bst_2.show();
}


TEST_F(BasicStructureInfoTest, copy_constructor) {
    matersdk::Structure<double> structure_1(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    matersdk::Structure<double> structure_2;

    matersdk::BasicStructureInfo<double> bst_1(structure_1);
    matersdk::BasicStructureInfo<double> bst_2(structure_2);
    matersdk::BasicStructureInfo<double> bst_3(bst_1);
    matersdk::BasicStructureInfo<double> bst_4(bst_2);

    //bst_3.show();
    //bst_4.show();
}


TEST_F(BasicStructureInfoTest, assignment_operator) {
    matersdk::Structure<double> structure_1(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    matersdk::Structure<double> structure_2;

    matersdk::BasicStructureInfo<double> bst_1(structure_1);
    matersdk::BasicStructureInfo<double> bst_2(structure_2);
    matersdk::BasicStructureInfo<double> bst_3 = bst_1;
    matersdk::BasicStructureInfo<double> bst_4 = bst_2;
    bst_2 = bst_1; // or `bst_1 = bst_2;`

    //bst_3.show();
    //bst_4.show();
    //bst_1.show();
}








class SupercellTest : public ::testing::Test {
protected:
    int num_atoms;
    double basis_vectors[3][3];
    int atomic_numbers[12];
    double frac_coords[12][3];
    int scaling_matrix[3];

    static void SetUpTestSuite() {
        std::cout << "SupercellTest is setting up...\n";
    }


    static void TearDownTestSuite() {
        std::cout << "SupercellTest is tearing down...\n";
    }


    void SetUp() override {
        num_atoms = 12;
        
        basis_vectors[0][0] = 3.1903157348;
        basis_vectors[0][1] = 5.5257885468;
        basis_vectors[0][2] = 0.0000000000;
        basis_vectors[1][0] = -6.3806307800;
        basis_vectors[1][1] = 0.0000000000;
        basis_vectors[1][2] = 0.0000000000;
        basis_vectors[2][0] = 0.0000000000;
        basis_vectors[2][1] = 0.0000000000;
        basis_vectors[2][2] = 23.1297687334;

        atomic_numbers[0] = 42;
        atomic_numbers[1] = 16;
        atomic_numbers[2] = 16;
        atomic_numbers[3] = 42;
        atomic_numbers[4] = 16;
        atomic_numbers[5] = 16;
        atomic_numbers[6] = 42;
        atomic_numbers[7] = 16;
        atomic_numbers[8] = 16;
        atomic_numbers[9] = 42; 
        atomic_numbers[10] = 16;
        atomic_numbers[11] = 16;

        frac_coords[0][0] = 0.333333333333;
        frac_coords[0][1] = 0.166666666667;
        frac_coords[0][2] = 0.500000000000;
        frac_coords[1][0] = 0.166666666667;
        frac_coords[1][1] = 0.333333333333;
        frac_coords[1][2] = 0.432343276548;
        frac_coords[2][0] = 0.166666666667;
        frac_coords[2][1] = 0.333333333333;
        frac_coords[2][2] = 0.567656723452;
        frac_coords[3][0] = 0.333333333333;
        frac_coords[3][1] = 0.666666666667;
        frac_coords[3][2] = 0.500000000000;
        frac_coords[4][0] = 0.166666666667;
        frac_coords[4][1] = 0.833333333333;
        frac_coords[4][2] = 0.432343276548;
        frac_coords[5][0] = 0.166666666667;
        frac_coords[5][1] = 0.833333333333;
        frac_coords[5][2] = 0.567656723452;
        frac_coords[6][0] = 0.833333333333;
        frac_coords[6][1] = 0.166666666667;
        frac_coords[6][2] = 0.500000000000;
        frac_coords[7][0] = 0.666666666667;
        frac_coords[7][1] = 0.333333333333;
        frac_coords[7][2] = 0.432343276548;
        frac_coords[8][0] = 0.666666666667;
        frac_coords[8][1] = 0.333333333333;
        frac_coords[8][2] = 0.567656723452;
        frac_coords[9][0] = 0.833333333333;
        frac_coords[9][1] = 0.666666666667;
        frac_coords[9][2] = 0.500000000000;
        frac_coords[10][0] = 0.666666666667;
        frac_coords[10][1] = 0.833333333333;
        frac_coords[10][2] = 0.432343276548;
        frac_coords[11][0] = 0.666666666667;
        frac_coords[11][1] = 0.833333333333;
        frac_coords[11][2] = 0.567656723452;

        scaling_matrix[0] = 3;
        scaling_matrix[1] = 3;
        scaling_matrix[2] = 1;
    }


    void TearDown() override {
        
    }
}; // class: Supercell class



TEST_F(SupercellTest, default_constructor) {
    matersdk::Supercell<double> supercell;
    //supercell.show();
}


TEST_F(SupercellTest, constuctor_1) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    matersdk::Supercell<double> supercell(structure, scaling_matrix);
    //supercell.show();
}


TEST_F(SupercellTest, copy_constructor) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    matersdk::Supercell<double> supercell_1(structure, scaling_matrix);
    matersdk::Supercell<double> supercell_2;

    matersdk::Supercell<double> supercell_3(supercell_1);
    matersdk::Supercell<double> supercell_4(supercell_2);

    //supercell_3.show();
    //supercell_4.show();
}


TEST_F(SupercellTest, assignment_operator) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    matersdk::Supercell<double> supercell_1(structure, scaling_matrix);
    matersdk::Supercell<double> supercell_(structure, scaling_matrix);
    matersdk::Supercell<double> supercell_2;
    
    matersdk::Supercell<double> supercell_3;
    matersdk::Supercell<double> supercell_4;

    supercell_3 = supercell_1;
    supercell_4 = supercell_2;
    //supercell_3.show();
    //supercell_4.show();

    //supercell_1 = supercell_2;
    //supercell_1.show();
}


TEST_F(SupercellTest, calc_prim_cell_idx_xyz_even) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    // Test 1: Scaling factor 是奇数
    scaling_matrix[0] = 5;
    scaling_matrix[1] = 7;
    scaling_matrix[2] = 9;
    matersdk::Supercell<double> supercell(structure, scaling_matrix);
    // supercell.calc_prim_cell_idx_xyz();
    // supercell.calc_prim_cell_idx();
    const int* prim_cell_idx_xyz = supercell.get_prim_cell_idx_xyz();

    EXPECT_EQ(prim_cell_idx_xyz[0], 2);
    EXPECT_EQ(prim_cell_idx_xyz[1], 3);
    EXPECT_EQ(prim_cell_idx_xyz[2], 4);
}


TEST_F(SupercellTest, calc_prim_cell_idx_xyz_odd) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    // Test 2: Scaling factor 是偶数
    scaling_matrix[0] = 6;
    scaling_matrix[1] = 8;
    scaling_matrix[2] = 10;
    matersdk::Supercell<double> supercell(structure, scaling_matrix);
    // supercell.calc_prim_cell_idx_xyz();
    // supercell.calc_prim_cell_idx();
    const int* prim_cell_idx_xyz = supercell.get_prim_cell_idx_xyz();
    EXPECT_EQ(prim_cell_idx_xyz[0], 2);
    EXPECT_EQ(prim_cell_idx_xyz[1], 3);
    EXPECT_EQ(prim_cell_idx_xyz[2], 4);
}


TEST_F(SupercellTest, calc_prim_cell_idx_xyz_even_odd) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    // Test 3: Scaling factor 既有奇数，也有偶数
    scaling_matrix[0] = 5;
    scaling_matrix[1] = 6;
    scaling_matrix[2] = 7;
    matersdk::Supercell<double> supercell(structure, scaling_matrix);
    // supercell.calc_prim_cell_idx_xyz();
    // supercell.calc_prim_cell_idx();
    const int* prim_cell_idx_xyz = supercell.get_prim_cell_idx_xyz();
    EXPECT_EQ(prim_cell_idx_xyz[0], 2);
    EXPECT_EQ(prim_cell_idx_xyz[1], 2);
    EXPECT_EQ(prim_cell_idx_xyz[2], 3);
}


TEST_F(SupercellTest, calc_prim_cell_idx_even) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    // Test 1: Scaling factor 是奇数
    scaling_matrix[0] = 5;
    scaling_matrix[1] = 7;
    scaling_matrix[2] = 9;
    matersdk::Supercell<double> supercell(structure, scaling_matrix);
    // supercell.calc_prim_cell_idx_xyz();
    // supercell.calc_prim_cell_idx();
    const int* prim_cell_idx_xyz = supercell.get_prim_cell_idx_xyz();
    const int prim_cell_idx = supercell.get_prim_cell_idx();

    EXPECT_EQ(
        prim_cell_idx,
        prim_cell_idx_xyz[0] + 
        prim_cell_idx_xyz[1] * scaling_matrix[0] + 
        prim_cell_idx_xyz[2] * scaling_matrix[0] * scaling_matrix[1]
    );
}


TEST_F(SupercellTest, calc_prim_cell_idx_odd) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    // Test 2: Scaling factor 是偶数
    scaling_matrix[0] = 6;
    scaling_matrix[1] = 8;
    scaling_matrix[2] = 10;
    matersdk::Supercell<double> supercell(structure, scaling_matrix);
    // supercell.calc_prim_cell_idx_xyz();
    // supercell.calc_prim_cell_idx();
    const int* prim_cell_idx_xyz = supercell.get_prim_cell_idx_xyz();
    const int prim_cell_idx = supercell.get_prim_cell_idx();
    
    EXPECT_EQ(
        prim_cell_idx, 
        prim_cell_idx_xyz[0] + 
        prim_cell_idx_xyz[1] * scaling_matrix[0] + 
        prim_cell_idx_xyz[2] * scaling_matrix[0] * scaling_matrix[1]
    );
}


TEST_F(SupercellTest, calc_prim_cell_even_odd) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    // Test 3: Scaling factor 既有奇数，也有偶数
    scaling_matrix[0] = 5;
    scaling_matrix[1] = 6;
    scaling_matrix[2] = 7;
    matersdk::Supercell<double> supercell(structure, scaling_matrix);
    // supercell.calc_prim_cell_idx_xyz();
    // supercell.calc_prim_cell_idx();
    const int* prim_cell_idx_xyz = supercell.get_prim_cell_idx_xyz();
    const int prim_cell_idx = supercell.get_prim_cell_idx();

    EXPECT_EQ(
        prim_cell_idx,
        prim_cell_idx_xyz[0] + 
        prim_cell_idx_xyz[1] * scaling_matrix[0] + 
        prim_cell_idx_xyz[2] * scaling_matrix[0] * scaling_matrix[1]
    );
}


TEST_F(SupercellTest, get_structure) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    scaling_matrix[0] = 7;
    scaling_matrix[1] = 8;
    scaling_matrix[2] = 9;
    matersdk::Supercell<double> supercell(structure, scaling_matrix);

    //supercell.get_structure().show();
}


TEST_F(SupercellTest, get_scaling_matrix) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    scaling_matrix[0] = 7;
    scaling_matrix[1] = 8;
    scaling_matrix[2] = 18;
    matersdk::Supercell<double> supercell(structure, scaling_matrix);
    const int* scaling_matrix = supercell.get_scaling_matrix();

    EXPECT_EQ(scaling_matrix[0], 7);
    EXPECT_EQ(scaling_matrix[1], 8);
    EXPECT_EQ(scaling_matrix[2], 18);
}



TEST_F(SupercellTest, get_num_atoms) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    scaling_matrix[0] = 6;
    scaling_matrix[1] = 8;
    scaling_matrix[2] = 10;
    matersdk::Supercell<double> supercell(structure, scaling_matrix);
    
    EXPECT_EQ(supercell.get_prim_num_atoms(), 12);
    EXPECT_EQ(supercell.get_num_atoms(), 12 * scaling_matrix[0] * scaling_matrix[1] * scaling_matrix[2]);
}


TEST_F(SupercellTest, get_owned_atom_idxs) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    scaling_matrix[0] = 3;
    scaling_matrix[1] = 3;
    scaling_matrix[2] = 1;
    matersdk::Supercell<double> supercell(structure, scaling_matrix);
    /*
        72~83   84~95   96~107
        36~47   48~59   60~71
         0~11   12~23   24~35
    */
    const int* owned_atom_idxs = supercell.get_owned_atom_idxs();
    EXPECT_EQ(owned_atom_idxs[0], 48);
    EXPECT_EQ(owned_atom_idxs[1], 49);
    EXPECT_EQ(owned_atom_idxs[2], 50);
    EXPECT_EQ(owned_atom_idxs[3], 51);
    EXPECT_EQ(owned_atom_idxs[4], 52);
    EXPECT_EQ(owned_atom_idxs[5], 53);
    EXPECT_EQ(owned_atom_idxs[6], 54);
    EXPECT_EQ(owned_atom_idxs[7], 55);
    EXPECT_EQ(owned_atom_idxs[8], 56);
    EXPECT_EQ(owned_atom_idxs[9], 57);
    EXPECT_EQ(owned_atom_idxs[10], 58);
    EXPECT_EQ(owned_atom_idxs[11], 59);
}






class BinLinkedListTest : public ::testing::Test {
protected:
    int num_atoms;
    double basis_vectors[3][3];
    int atomic_numbers[12];
    double frac_coords[12][3];
    double rcut;
    double bin_size_xyz[3];
    bool pbc_xyz[3];



    static void SetUpTestSuite() {
        std::cout << "BinLinkedListTest is setting up...\n";
    }


    static void TearDownTestSuite() {
        std::cout << "BinLinkedListTest is tearing down...\n";
    }


    void SetUp() override {
        num_atoms = 12;
        
        basis_vectors[0][0] = 3.1903157348;
        basis_vectors[0][1] = 5.5257885468;
        basis_vectors[0][2] = 0.0000000000;
        basis_vectors[1][0] = -6.3806307800;
        basis_vectors[1][1] = 0.0000000000;
        basis_vectors[1][2] = 0.0000000000;
        basis_vectors[2][0] = 0.0000000000;
        basis_vectors[2][1] = 0.0000000000;
        basis_vectors[2][2] = 23.1297687334;

        atomic_numbers[0] = 42;
        atomic_numbers[1] = 16;
        atomic_numbers[2] = 16;
        atomic_numbers[3] = 42;
        atomic_numbers[4] = 16;
        atomic_numbers[5] = 16;
        atomic_numbers[6] = 42;
        atomic_numbers[7] = 16;
        atomic_numbers[8] = 16;
        atomic_numbers[9] = 42; 
        atomic_numbers[10] = 16;
        atomic_numbers[11] = 16;

        frac_coords[0][0] = 0.333333333333;
        frac_coords[0][1] = 0.166666666667;
        frac_coords[0][2] = 0.500000000000;
        frac_coords[1][0] = 0.166666666667;
        frac_coords[1][1] = 0.333333333333;
        frac_coords[1][2] = 0.432343276548;
        frac_coords[2][0] = 0.166666666667;
        frac_coords[2][1] = 0.333333333333;
        frac_coords[2][2] = 0.567656723452;
        frac_coords[3][0] = 0.333333333333;
        frac_coords[3][1] = 0.666666666667;
        frac_coords[3][2] = 0.500000000000;
        frac_coords[4][0] = 0.166666666667;
        frac_coords[4][1] = 0.833333333333;
        frac_coords[4][2] = 0.432343276548;
        frac_coords[5][0] = 0.166666666667;
        frac_coords[5][1] = 0.833333333333;
        frac_coords[5][2] = 0.567656723452;
        frac_coords[6][0] = 0.833333333333;
        frac_coords[6][1] = 0.166666666667;
        frac_coords[6][2] = 0.500000000000;
        frac_coords[7][0] = 0.666666666667;
        frac_coords[7][1] = 0.333333333333;
        frac_coords[7][2] = 0.432343276548;
        frac_coords[8][0] = 0.666666666667;
        frac_coords[8][1] = 0.333333333333;
        frac_coords[8][2] = 0.567656723452;
        frac_coords[9][0] = 0.833333333333;
        frac_coords[9][1] = 0.666666666667;
        frac_coords[9][2] = 0.500000000000;
        frac_coords[10][0] = 0.666666666667;
        frac_coords[10][1] = 0.833333333333;
        frac_coords[10][2] = 0.432343276548;
        frac_coords[11][0] = 0.666666666667;
        frac_coords[11][1] = 0.833333333333;
        frac_coords[11][2] = 0.567656723452;

        rcut = 3.0;
        bin_size_xyz[0] = 3.0;
        bin_size_xyz[1] = 3.0;
        bin_size_xyz[2] = 3.0;
        pbc_xyz[0] = true;
        pbc_xyz[1] = true;
        pbc_xyz[2] = false;
    }


    void TearDown() override {

    }
};  // class BinLinkedListTest



TEST_F(BinLinkedListTest, constructor_1_case_1) {
    rcut = 3.0;
    bin_size_xyz[0] = 3.0;
    bin_size_xyz[1] = 3.0;
    bin_size_xyz[2] = 3.0;
    pbc_xyz[0] = true;
    pbc_xyz[1] = true;
    pbc_xyz[2] = false;

    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    matersdk::BinLinkedList<double> bin_linked_list(structure, rcut, bin_size_xyz, pbc_xyz);

    // Step 1. 验证 `extending_matrix`, `scaling_matrix`
    const int* scaling_matrix = bin_linked_list.get_supercell().get_scaling_matrix();
    double* prim_interplanar_distances = (double *)structure.get_interplanar_distances();
    int* standard_scaling_matrix = (int*)malloc(sizeof(int) * 3);
    for (int ii=0; ii<3; ii++) {
        standard_scaling_matrix[ii] = std::ceil(rcut / prim_interplanar_distances[ii]);
        standard_scaling_matrix[ii] = standard_scaling_matrix[ii] * 2 + 1;

        if (pbc_xyz[ii] != true) 
            standard_scaling_matrix[ii] = 1;
    }

    EXPECT_EQ(scaling_matrix[0], standard_scaling_matrix[0]);
    EXPECT_EQ(scaling_matrix[1], standard_scaling_matrix[1]);
    EXPECT_EQ(scaling_matrix[2], standard_scaling_matrix[2]);

    // Step 2. 验证 `num_bin_xyz`
    const int* num_bin_xyz = bin_linked_list.get_num_bin_xyz();
    double* projected_lengths = (double*)bin_linked_list.get_supercell().get_structure().get_projected_lengths();
    printf("***[%f, %f, %f]\n", structure.get_projected_lengths()[0], structure.get_projected_lengths()[1], structure.get_projected_lengths()[2]);
    printf("***[%f, %f, %f]\n", projected_lengths[0], projected_lengths[1], projected_lengths[2]);
    int* standard_num_bin_xyz = (int*)malloc(sizeof(int) * 3);
    for (int ii=0; ii<3; ii++) {
        standard_num_bin_xyz[ii] = std::ceil( projected_lengths[ii] / bin_size_xyz[ii] );
    }
    EXPECT_EQ(num_bin_xyz[0], standard_num_bin_xyz[0]);
    EXPECT_EQ(num_bin_xyz[1], standard_num_bin_xyz[1]);
    EXPECT_EQ(num_bin_xyz[2], standard_num_bin_xyz[2]);

    // Step 3. 验证 `min_limit_xyz`
    int* extending_matrix = (int*)malloc(sizeof(int) * 3);
    double* standard_min_limit_xyz = (double*)malloc(sizeof(double) * 3);
    double* prim_projected_lengths = (double*)structure.get_projected_lengths();
    for (int ii=0; ii<3; ii++) {
        extending_matrix[ii] = std::ceil( rcut / prim_interplanar_distances[ii] );
        if (pbc_xyz[ii] != true) {
            extending_matrix[ii] = 0;
        }
        standard_min_limit_xyz[ii] = -extending_matrix[ii] * prim_projected_lengths[ii];
    }
    const double* min_limit_xyz = bin_linked_list.get_min_limit_xyz();
    EXPECT_EQ(min_limit_xyz[0], standard_min_limit_xyz[0]);
    EXPECT_EQ(min_limit_xyz[1], standard_min_limit_xyz[1]);
    EXPECT_EQ(min_limit_xyz[2], standard_min_limit_xyz[2]);


    // Step . Free memory
    free(prim_interplanar_distances);
    free(standard_scaling_matrix);
    free(projected_lengths);
    free(standard_num_bin_xyz);
    free(extending_matrix);
    free(prim_projected_lengths);
}


/*
TEST_F(BinLinkedListTest, get_bin_idx_from_prim_atom_idx) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    matersdk::BinLinkedList<double> bin_linked_list(structure, rcut, bin_size_xyz, pbc_xyz);
    int prim_atom_idx = 0;
    int bin_idx = bin_linked_list.get_bin_idx(prim_atom_idx);

    // Step 1.
    int bin_idx_xyz[3];
    int standard_bin_idx_xyz[3];
    
    // Step 1.1. 
    bin_idx_xyz[0] = bin_idx % bin_linked_list.get_num_bin_xyz()[0];
    bin_idx_xyz[1] = bin_idx / bin_linked_list.get_num_bin_xyz()[0];
    bin_idx_xyz[2] = bin_idx / (bin_linked_list.get_num_bin_xyz()[0] * bin_linked_list.get_num_bin_xyz()[1]);
    printf("bin_idx = %d\n", bin_idx);
    printf("num_bin_xyz = [%d, %d, %d]\n", bin_linked_list.get_num_bin_xyz()[0], bin_linked_list.get_num_bin_xyz()[1], bin_linked_list.get_num_bin_xyz()[2]);
    printf("bin_idx_xyz = [%d, %d, %d]\n", bin_idx_xyz[0], bin_idx_xyz[1], bin_idx_xyz[2]);
    
    // Step 1.2. 得到 `prim_atom_idx` 在 supercell 中对应的 `atom_idx`
    int atom_idx = prim_atom_idx + bin_linked_list.get_supercell().get_prim_cell_idx();
    const double* atom_coord = bin_linked_list.get_supercell().get_structure().get_cart_coords()[atom_idx];
    for (int ii=0; ii<3; ii++) {
        standard_bin_idx_xyz[ii] = std::floor( (atom_coord[ii] - bin_linked_list.get_min_limit_xyz()[ii]) / bin_linked_list.get_bin_size_xyz()[ii] );
    }

    EXPECT_EQ(bin_idx_xyz[0], standard_bin_idx_xyz[0]);
    EXPECT_EQ(bin_idx_xyz[1], standard_bin_idx_xyz[1]);
    EXPECT_EQ(bin_idx_xyz[2], standard_bin_idx_xyz[2]);
}
*/

TEST_F(BinLinkedListTest, get_supercell) {
    matersdk::Structure<double> structure(num_atoms, basis_vectors, atomic_numbers, frac_coords, false);
    matersdk::BinLinkedList<double> bin_linked_list(structure, rcut, bin_size_xyz, pbc_xyz);

}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}