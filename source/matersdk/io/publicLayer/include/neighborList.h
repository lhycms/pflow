#ifndef MATERSDK_NEIGHBOR_LIST_H
#define MATERSDK_NEIGHBOR_LIST_H

#include <cassert>
#include <cmath>
#include <algorithm>
#include "./binLinkedList.h"




namespace matersdk {


/**
 * @brief A `neighbor list` class
 * 
 * @tparam CoordType 
 */
template <typename CoordType>
class NeighborList {
public:
    friend class BinLinkedList<CoordType>;
    
    NeighborList(Structure<CoordType> structure, CoordType rcut, CoordType* bin_size_xyz, bool* pbc_xyz);

    ~NeighborList();

    void _build(bool sort=false);       // Populate `this->neighbor_list` (`std::vector<int>* this->neighbor_list = new std::vector<int>[this->num_atoms];`)

    void show_in_index() const;         // 展示 supercell 中的 atom_index

    void show_in_prim_index() const;    // 展示 primitive cell 中的 atom_index

    void show_in_an() const;            // 展示 atomic_number

    void show_in_distances() const;     // 展示 距中心原子的距离

    const BinLinkedList<CoordType>& get_binLinkedList() const;

    const int get_max_num_neigh_atoms() const;

    const int get_max_num_neigh_atoms_ss(int neigh_atomic_number) const; // `ss`: specified specie

private:
    BinLinkedList<CoordType> bin_linked_list;
    int num_atoms;                              // The number of atoms in primitive cell.
    std::vector<int>* neighbor_lists;           // `num_atoms` 个 `neighbor_lists` 构成完整的 `neighbor_list`
};  // class: NeighborList



/**
 * @brief Construct a new Neighbor List< Coord Type>:: Neighbor List object
 * 
 * @tparam CoordType 
 * @param structure 
 * @param rcut 
 * @param bin_size_xyz 
 * @param pbc_xyz 
 */
template <typename CoordType>
NeighborList<CoordType>::NeighborList(Structure<CoordType> structure, CoordType rcut, CoordType* bin_size_xyz, bool* pbc_xyz) {
    assert(structure.get_num_atoms() > 0);

    this->bin_linked_list = BinLinkedList<CoordType>(structure, rcut, bin_size_xyz, pbc_xyz);
    this->num_atoms = this->bin_linked_list.get_supercell().get_prim_num_atoms();
    this->neighbor_lists = new std::vector<int>[this->num_atoms];
    this->_build();     // Populate `this->neighbor_lists`
}


/**
 * @brief Destroy the Neighbor List< Coord Type>:: Neighbor List object
 * 
 * @tparam CoordType 
 */
template <typename CoordType>
NeighborList<CoordType>::~NeighborList() {
    if (this->num_atoms != 0) {
        delete [] this->neighbor_lists;
        this->num_atoms = 0;
    }
}


/**
 * @brief Populate `this->neighbor_lists`
 * 
 * @tparam CoordType 
 * @param sort 是否按照距中心原子的距离排序
 */
template <typename CoordType>
void NeighborList<CoordType>::_build(bool sort) {
    // Step 1. 得到 primitive cell 的相关信息
    // Step 1.1. primitive cell 中的原子个数、primitive cell 的 `prim_cell_idx`
    int prim_cell_idx = this->bin_linked_list.get_supercell().get_prim_cell_idx();
    int prim_num_atoms = this->bin_linked_list.get_supercell().get_prim_num_atoms();
    assert(prim_num_atoms == this->num_atoms);

    // Step 2. Populate `this->neighbor_lists`
    int center_atom_idx;    // `center_atom_index`: atom 在 supercell 中对应的 index
    int center_atomic_number;
    for (int ii=0; ii<this->num_atoms; ii++) {  // `ii`: atom 在 primitive cell 中的 index
        this->neighbor_lists[ii] = this->bin_linked_list.get_neigh_atoms(ii);
    }
}


template <typename CoordType>
void NeighborList<CoordType>::show_in_index() const {
    for (int ii=0; ii<this->num_atoms; ii++) {
        printf("%4d:\t", ii);
        for (int jj: this->neighbor_lists[ii]) {
            printf("%4d, ", jj);
        }
        printf("\n");
    }
}


template <typename CoordType>
void NeighborList<CoordType>::show_in_prim_index() const {
    for (int ii=0; ii<this->num_atoms; ii++) {
        printf("%4d:\t", ii);
        for (int jj: this->neighbor_lists[ii]) {
            printf("%4d, ", jj % this->num_atoms);
        }
        printf("\n");
    }
}


template <typename CoordType>
void NeighborList<CoordType>::show_in_an() const {
    const int* supercell_atomic_numbers = this->bin_linked_list.get_supercell().get_structure().get_atomic_numbers();

    for (int ii=0; ii<this->num_atoms; ii++) {
        printf("%4d:\t", supercell_atomic_numbers[ii]);
        for (int jj: this->neighbor_lists[ii]) {
            printf("%4d, ", supercell_atomic_numbers[jj]);
        }
        printf("\n");
    }
}


template <typename CoordType>
void NeighborList<CoordType>::show_in_distances() const {
    const CoordType** supercell_cart_coords = this->bin_linked_list.get_supercell().get_structure().get_cart_coords();
    const int* supercell_atomic_numbers = this->bin_linked_list.get_supercell().get_structure().get_atomic_numbers();
    CoordType* center_cart_coord = (CoordType*)malloc(sizeof(CoordType) * 3);   // 中心原子的坐标
    CoordType* neigh_cart_coord = (CoordType*)malloc(sizeof(CoordType) * 3);    // 近邻原子的坐标
    const int prim_cell_idx = this->bin_linked_list.get_supercell().get_prim_cell_idx();
    CoordType tmp_distance;

    for (int ii=0; ii<this->num_atoms; ii++) {
        printf("%d:\t", supercell_atomic_numbers[ii]);
        center_cart_coord[0] = supercell_cart_coords[ii + this->num_atoms * prim_cell_idx][0];
        center_cart_coord[1] = supercell_cart_coords[ii + this->num_atoms * prim_cell_idx][1];
        center_cart_coord[2] = supercell_cart_coords[ii + this->num_atoms * prim_cell_idx][2];

        for (int jj: this->neighbor_lists[ii]) {
            neigh_cart_coord[0] = supercell_cart_coords[jj][0];
            neigh_cart_coord[1] = supercell_cart_coords[jj][1];
            neigh_cart_coord[2] = supercell_cart_coords[jj][2];
            
            tmp_distance = std::sqrt(
                std::pow(neigh_cart_coord[0] - center_cart_coord[0], 2) + 
                std::pow(neigh_cart_coord[1] - center_cart_coord[1], 2) + 
                std::pow(neigh_cart_coord[2] - center_cart_coord[2], 2)
            );
            printf("%6.6f, ", tmp_distance);
        }
        printf("\n");
    }

    free(center_cart_coord);
    free(neigh_cart_coord);
}


template <typename CoordType>
const BinLinkedList<CoordType>& NeighborList<CoordType>::get_binLinkedList() const {
    return this->bin_linked_list;
}


/**
 * @brief 计算最大近邻原子数 （包含所有元素种类）
 * 
 * @tparam CoordType 
 * @return const int 
 */
template <typename CoordType>
const int NeighborList<CoordType>::get_max_num_neigh_atoms() const {
    int max_num_neigh_atoms = 0;
    for (int ii=0; ii<this->num_atoms; ii++) {
        if ( this->neighbor_lists[ii].size() > max_num_neigh_atoms ) {
            max_num_neigh_atoms = this->neighbor_lists[ii].size();
        }
    }
    return max_num_neigh_atoms;
}


/**
 * @brief 计算 元素为`neigh_atomic_number` 的最大近邻原子数 （包含某种元素 -- `neigh_atomioc_number`）
 * 
 * @tparam CoordType 
 * @param neigh_atomic_number 
 * @return const int 
 */
template <typename CoordType>
const int NeighborList<CoordType>::get_max_num_neigh_atoms_ss(int neigh_atomic_number) const {
    // Step 1. Initialize the value 
    // Step 1.1. 
    int max_num_neigh_atoms_ss = 0;             // return value
    int tmp_max_num_neigh_atoms_ss = 0;         // 在循环中，暂时存储某个中心原子的 `tmp_max_num_neigh_atoms_ss`
    std::vector<int> tmp_neigh_atomic_numbers;  // 将 `this->neighbor_lists[ii]` 的index换成 `atomic_number` 存储在 `std::vector<int>` 中
    // Step 1.2. 
    const int* supercell_atomic_numbers = this->bin_linked_list.get_supercell().get_structure().get_atomic_numbers();

    // Step 2. Update the `max_num_neigh_atoms_ss`
    for (int ii=0; ii<this->num_atoms; ii++) {
        tmp_neigh_atomic_numbers.clear();   // Clears all elements from the vector, making it empty
        // Step 2.1. Populate `tmp_neigh_atomic_numbers`.
        for (int supercell_atom_index: this->neighbor_lists[ii]) {
            tmp_neigh_atomic_numbers.push_back(supercell_atomic_numbers[supercell_atom_index]);
        }

        // Step 2.2. 
        tmp_max_num_neigh_atoms_ss = std::count(
                    tmp_neigh_atomic_numbers.begin(), 
                    tmp_neigh_atomic_numbers.end(), 
                    neigh_atomic_number
        );

        // Step 2.3. 
        if (tmp_max_num_neigh_atoms_ss > max_num_neigh_atoms_ss) 
            max_num_neigh_atoms_ss = tmp_max_num_neigh_atoms_ss;
    }

    return max_num_neigh_atoms_ss;
}

}; // namespace: matersdk


#endif