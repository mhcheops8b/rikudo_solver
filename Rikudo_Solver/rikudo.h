#pragma once

//#include "pch.h"
#include "rikudo_shape.h"
#include <vector>
#include <map>

struct interval
{
	int start;
	int end;
};

// probably not necessary as structure
struct fillable_block {
	int length;
	std::vector<std::pair<int, int>> tiles;
	std::pair<int, int> end1;
	std::pair<int, int> end2;
	bool used = false;
	// length == tiles.size()
	// tiles.front(), tiles.back()
};


struct rikudo
{
	enum hex_dirs { ANY = 0, UR = 1, _R = 2, DR = 4, DL = 8, _L = 16, UL = 32 };

	/*const*/ rikudo_shape shape;

	// row, rol -> xx 0, UR 1, R 2, DR 4, DL 8, L 16, UL 32
	/*const*/ std::map<std::pair<int, int>, int> forced_orders;
	// no fill elements non-fillable
	/*const*/ std::vector< std::pair<int, int>> non_fillable;
	/*const*/ std::map<std::pair<int, int>, int> forced_values;
	/*const*/ int max_elem_value;

	rikudo() : max_elem_value(0) {};
	rikudo(const rikudo_shape _shape, const std::map<std::pair<int, int>, int> _forced_orders, const std::vector< std::pair<int, int>> _non_fillable,
		std::map<std::pair<int, int>, int> _forced_values, int _max_elem_value) : 
		shape(_shape),
		forced_orders(_forced_orders), non_fillable(_non_fillable), 
		forced_values(_forced_values), max_elem_value(_max_elem_value) {
		check_forced_orders();
		init();
	};

	bool init();
	bool initialize_fillable_blocks();
	//

	static int get_numeric_direction(int hex_dir);

	void disp_crude() const;
	bool check_forced_orders() const;
	int get_forced_orders(const std::pair<int, int>& elem) const;
	int count_forced_orders(const std::pair<int, int>& elem) const;
	bool is_forced_from_UR(const std::pair<int, int>& elem) const;
	bool is_forced_from__R(const std::pair<int, int>& elem) const;
	bool is_forced_from_DR(const std::pair<int, int>& elem) const;
	bool is_forced_from_DL(const std::pair<int, int>& elem) const;
	bool is_forced_from__L(const std::pair<int, int>& elem) const;
	bool is_forced_from_UL(const std::pair<int, int>& elem) const;

	bool is_forced_element(int value) const;
	bool is_forced_element(const std::pair<int, int>& elem) const;

	bool is_fillable_element(const std::pair<int, int>& elem) const;

	bool is_already_filled(const std::pair<int, int>& elem) const;
	bool is_already_filled(const int val) const;

	int get_fillable_block_index_with_end_containing_elem(const std::pair<int, int>& elem) const;
	int get_unused_fillable_block_index_with_end_containing_elem(const std::pair<int, int>& elem) const;
	std::vector<int> get_unfilled_neighbour_blocks_idxs(const std::pair<int, int>& elem) const;

	bool can_fillable_block_fit(int vstart, int block_idx, bool up = true);

	std::vector<std::pair<std::pair<int, int>, bool>>
		get_unfilled_neighbours(const std::pair<int, int>& elem) const;
	void init_forced_values_inv();
	int get_elem(const std::pair<int, int>& addr) const;
	std::pair<int, int> get_addr(int value) const;

	bool exists_neighbour_from_UR(const std::pair<int, int>& elem) const;
	bool exists_neighbour_from__R(const std::pair<int, int>& elem) const;
	bool exists_neighbour_from_DR(const std::pair<int, int>& elem) const;
	bool exists_neighbour_from_DL(const std::pair<int, int>& elem) const;
	bool exists_neighbour_from__L(const std::pair<int, int>& elem) const;
	bool exists_neighbour_from_UL(const std::pair<int, int>& elem) const;

	bool is_filled_neighbour_from_UR(const std::pair<int, int>& elem) const;
	bool is_filled_neighbour_from__R(const std::pair<int, int>& elem) const;
	bool is_filled_neighbour_from_DR(const std::pair<int, int>& elem) const;
	bool is_filled_neighbour_from_DL(const std::pair<int, int>& elem) const;
	bool is_filled_neighbour_from__L(const std::pair<int, int>& elem) const;
	bool is_filled_neighbour_from_UL(const std::pair<int, int>& elem) const;

	bool are_neighbours_from_UR(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const;
	bool are_neighbours_from__R(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const;
	bool are_neighbours_from_DR(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const;
	bool are_neighbours_from_DL(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const;
	bool are_neighbours_from__L(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const;
	bool are_neighbours_from_UL(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const;

	bool are_neighbours(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const;
	//bool is_forced_neighbour()
	bool has_enough_space_elem(int filled_value) const;
	bool has_enough_space_elems() const;

	void insert_to_filled(const std::pair<int, int>& elem, int value);
	void remove_from_filled(const std::pair<int, int>& elem, int value);

	//// end part of the block is neighbour of already filled element
	//bool test_use_block(int block_idx, bool b_from_end1, int from_value, bool b_down) {
	//}

	void use_block(int block_idx, bool b_from_end1, int from_value, bool b_down);
	void unuse_block(int block_idx, bool b_from_end1, int from_value, bool b_down);

	bool is_attached(int block_idx) const;
	bool can_be_attached(int block_idx) const;
	bool can_be_attached_all() const;
	bool is_attached_forced_value(int fv) const;

	void get_unfilled_intervals(std::vector<std::pair<int, int>>& intervals) const;

	// tests whether components
	// of connectivity made out of
	// blocks can be expanded
	// <=> there are at least 2
	// unsaturated surrounding blocks
	bool test_block_components() const;

	bool exist_paths_via_unfilled();


	// computed values
	std::map<int, std::pair<int, int>> forced_values_inv;
	std::map<std::pair<int, int>, int> filled_values;
	std::map<int, std::pair<int, int>> filled_values_inv;
	int first_forced_value;
	int last_forced_value;
	std::vector<fillable_block> fillable_blocks;
};

void exists_path_via_unused_blocks_of_length_recOLD(int length, std::vector<int>& used_blocks, std::vector<int>& used_connections, std::vector<std::pair<int, int>>& used_elements, rikudo& myrikudo, const std::pair<int, int>& el_from, const std::pair<int, int>& el_to, bool& b_found, bool b_all = false);
void exists_path_via_unused_blocks_of_length_rec(int length, std::vector<int>& used_blocks, std::vector<int>& used_connections, int start_value, int end_value, rikudo& myrikudo, const std::pair<int, int>& el_from, const std::pair<int, int>& el_to, bool& b_found);

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& el);
