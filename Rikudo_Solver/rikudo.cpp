#include "pch.h"
#include <iostream>
#include <set>
#include <vector>

#include "rikudo.h"


void rikudo::use_block(int block_idx, bool b_from_end1, int from_value, bool b_down) {

	int value_increment = b_down ? -1 : 1;
	int tile_idx = b_from_end1 ? 0 : fillable_blocks[block_idx].length - 1;
	int tile_idx_increment = b_from_end1 ? 1 : -1;

	for (int i = 0; i < fillable_blocks[block_idx].length; i++) {
		if (filled_values.find(fillable_blocks[block_idx].tiles[tile_idx]) != filled_values.end()) {
			std::cerr << "Elem " << fillable_blocks[block_idx].tiles[tile_idx] << " is already filled!";
		}
		if (filled_values_inv.find(from_value) != filled_values_inv.end()) {
			std::cerr << "Value " << from_value << " is already filled!";
		}
		insert_to_filled(fillable_blocks[block_idx].tiles[tile_idx], from_value);
		tile_idx += tile_idx_increment;
		from_value += value_increment;
	}

	fillable_blocks[block_idx].used = true;
}

void rikudo::unuse_block(int block_idx, bool b_from_end1, int from_value, bool b_down) {

	int value_increment = b_down ? -1 : 1;
	int tile_idx = b_from_end1 ? 0 : fillable_blocks[block_idx].length - 1;
	int tile_idx_increment = b_from_end1 ? 1 : -1;

	for (int i = 0; i < fillable_blocks[block_idx].length; i++) {
		remove_from_filled(fillable_blocks[block_idx].tiles[tile_idx], from_value);
		tile_idx += tile_idx_increment;
		from_value += value_increment;
	}

	fillable_blocks[block_idx].used = false;
}


void rikudo::insert_to_filled(const std::pair<int, int>& elem, int value) {
	filled_values.insert({ elem, value });
	filled_values_inv.insert({ value, elem });
}

void rikudo::remove_from_filled(const std::pair<int, int>& elem, int value) {
	filled_values.erase(elem);
	filled_values_inv.erase(value);
}


bool rikudo::is_already_filled(const std::pair<int, int>& elem) const
{
	return forced_values.find(elem) != forced_values.end() ||
		filled_values.find(elem) != filled_values.end();
}


bool rikudo::is_already_filled(const int val) const
{
	return forced_values_inv.find(val) != forced_values_inv.end() ||
		filled_values_inv.find(val) != filled_values_inv.end();
}

int rikudo::get_fillable_block_index_with_end_containing_elem(const std::pair<int, int>& elem) const
{
	int idx = -1;
	for (int i = 0; i < fillable_blocks.size(); i++) {
		if (fillable_blocks[i].end1 == elem || fillable_blocks[i].end2 == elem) {
			return i;
		}
	}

	return idx;
}

int rikudo::get_unused_fillable_block_index_with_end_containing_elem(const std::pair<int, int>& elem) const
{
	int idx = -1;
	for (int i = 0; i < fillable_blocks.size(); i++) {
		if (!fillable_blocks[i].used) {
			if (fillable_blocks[i].end1 == elem || fillable_blocks[i].end2 == elem) {
				return i;
			}
		}
	}
	return idx;
}

std::vector<int>
rikudo::get_unfilled_neighbour_blocks_idxs(const std::pair<int, int>& elem) const {
	std::vector<int> result;
	// maximal number of neighbours is 6
	result.reserve(6);

	for (int dir = 0; dir < 6; dir++) {

		auto tile = shape.get_tile_in_dir(elem, dir);
		auto non_existing_tile = std::pair<int, int>{ -1,-1 };
		if (tile != non_existing_tile &&
			std::find(non_fillable.begin(), non_fillable.end(), tile) == non_fillable.end() &&
			forced_values.find(tile) == forced_values.end() &&
			filled_values.find(tile) == filled_values.end()
			) {
			int idx = get_unused_fillable_block_index_with_end_containing_elem(tile);
			if (idx != -1) {
				// if not alredy present
				if (std::find(result.begin(), result.end(), idx) == result.end())
					result.push_back(idx);
			}
		}

	}

	return result;
}

bool rikudo::can_fillable_block_fit(int vstart, int block_idx, bool up)
{
	int increment = +1;
	if (!up)
		increment = -1;

	for (int i = 0; i < fillable_blocks[block_idx].length; i++) {
		if (vstart < 1 || vstart > max_elem_value || is_already_filled(vstart))
			return false;
		vstart += increment;
	}
	return true;

}



std::vector<std::pair<std::pair<int, int>, bool>>
rikudo::get_unfilled_neighbours(const std::pair<int, int>& elem) const
{
	std::vector<std::pair<std::pair<int, int>, bool>> result;
	// maximal number of neighbours is 6
	result.reserve(6);

	// get forced order signature
	int ff = 0;
	auto it = forced_orders.find(elem);
	if (it != forced_orders.end())
		ff = it->second;


	auto tile = shape.get_UR_tile(elem.first, elem.second);
	auto non_existing_tile = std::pair<int, int>{ -1,-1 };
	if (tile != non_existing_tile &&
		std::find(non_fillable.begin(), non_fillable.end(), tile) == non_fillable.end() &&
		forced_values.find(tile) == forced_values.end() &&
		filled_values.find(tile) == filled_values.end()
		) {
		if (count_forced_orders(tile) != 2 || is_forced_from_DL(tile))
			result.push_back({ tile, (ff & UR) != 0 });
	}

	tile = shape.get__R_tile(elem.first, elem.second);
	if (tile != non_existing_tile &&
		std::find(non_fillable.begin(), non_fillable.end(), tile) == non_fillable.end() &&
		forced_values.find(tile) == forced_values.end() &&
		filled_values.find(tile) == filled_values.end()
		) {
		if (count_forced_orders(tile) != 2 || is_forced_from__L(tile))
			result.push_back({ tile, (ff & _R) != 0 });
	}

	tile = shape.get_DR_tile(elem.first, elem.second);
	if (tile != non_existing_tile &&
		std::find(non_fillable.begin(), non_fillable.end(), tile) == non_fillable.end() &&
		forced_values.find(tile) == forced_values.end() &&
		filled_values.find(tile) == filled_values.end()
		) {
		if (count_forced_orders(tile) != 2 || is_forced_from_UL(tile))
			result.push_back({ tile, (ff & DR) != 0 });
	}

	tile = shape.get_DL_tile(elem.first, elem.second);
	if (tile != non_existing_tile &&
		std::find(non_fillable.begin(), non_fillable.end(), tile) == non_fillable.end() &&
		forced_values.find(tile) == forced_values.end() &&
		filled_values.find(tile) == filled_values.end()
		) {
		if (count_forced_orders(tile) != 2 || is_forced_from_UR(tile))
			result.push_back({ tile, (ff & DL) != 0 });
	}

	tile = shape.get__L_tile(elem.first, elem.second);
	if (tile != non_existing_tile &&
		std::find(non_fillable.begin(), non_fillable.end(), tile) == non_fillable.end() &&
		forced_values.find(tile) == forced_values.end() &&
		filled_values.find(tile) == filled_values.end()
		) {
		if (count_forced_orders(tile) != 2 || is_forced_from__R(tile))
			result.push_back({ tile, (ff & _L) != 0 });
	}

	tile = shape.get_UL_tile(elem.first, elem.second);
	if (tile != non_existing_tile &&
		std::find(non_fillable.begin(), non_fillable.end(), tile) == non_fillable.end() &&
		forced_values.find(tile) == forced_values.end() &&
		filled_values.find(tile) == filled_values.end()
		) {
		if (count_forced_orders(tile) != 2 || is_forced_from_DR(tile))
			result.push_back({ tile, (ff & UL) != 0 });
	}

	return result;
}

void rikudo::init_forced_values_inv()
{
	for (const auto& e : forced_values)
		forced_values_inv.insert(std::pair<int, std::pair<int, int>>(e.second, e.first));
}

int rikudo::get_elem(const std::pair<int, int>& addr) const
{
	auto it = forced_values.find(addr);
	if (it != forced_values.end())
		return it->second;
	auto it2 = filled_values.find(addr);
	if (it2 != filled_values.end())
		return it2->second;

	if (std::find(non_fillable.begin(), non_fillable.end(), addr) != non_fillable.end())
		return -1; // empty/unfillable element

	return 0; // yet unfilled element
}

std::pair<int, int> rikudo::get_addr(int value) const
{
	auto it = forced_values_inv.find(value);
	if (it != forced_values_inv.end())
		return it->second;

	auto it2 = filled_values_inv.find(value);

	if (it2 != filled_values_inv.end())
		return it2->second;

	return std::pair<int, int>{-1, -1};
}

bool rikudo::exists_neighbour_from_UR(const std::pair<int, int>& elem) const
{
	auto tile_c = shape.get_UR_tile(elem);
	if (tile_c != std::pair<int, int>(-1, -1) &&
		std::find(non_fillable.begin(), non_fillable.end(), tile_c) == non_fillable.end())
		return true;

	return false;
}

bool rikudo::exists_neighbour_from__R(const std::pair<int, int>& elem) const
{
	auto tile_c = shape.get__R_tile(elem);
	if (tile_c != std::pair<int, int>(-1, -1) &&
		std::find(non_fillable.begin(), non_fillable.end(), tile_c) == non_fillable.end())
		return true;

	return false;
}

bool rikudo::exists_neighbour_from_DR(const std::pair<int, int>& elem) const
{
	auto tile_c = shape.get_DR_tile(elem);
	if (tile_c != std::pair<int, int>(-1, -1) &&
		std::find(non_fillable.begin(), non_fillable.end(), tile_c) == non_fillable.end())
		return true;

	return false;
}

bool rikudo::exists_neighbour_from_DL(const std::pair<int, int>& elem) const
{
	auto tile_c = shape.get_DL_tile(elem);
	if (tile_c != std::pair<int, int>(-1, -1) &&
		std::find(non_fillable.begin(), non_fillable.end(), tile_c) == non_fillable.end())
		return true;

	return false;
}

bool rikudo::exists_neighbour_from__L(const std::pair<int, int>& elem) const
{
	auto tile_c = shape.get__L_tile(elem);
	if (tile_c != std::pair<int, int>(-1, -1) &&
		std::find(non_fillable.begin(), non_fillable.end(), tile_c) == non_fillable.end())
		return true;

	return false;
}

bool rikudo::exists_neighbour_from_UL(const std::pair<int, int>& elem) const
{
	auto tile_c = shape.get_UL_tile(elem);
	if (tile_c != std::pair<int, int>(-1, -1) &&
		std::find(non_fillable.begin(), non_fillable.end(), tile_c) == non_fillable.end())
		return true;

	return false;
}

bool rikudo::is_filled_neighbour_from_UR(const std::pair<int, int>& elem) const
{
	// assumes that UR neigbour exists
	auto tile_c = shape.get_UR_tile(elem);
	return is_already_filled(tile_c);
}

bool rikudo::is_filled_neighbour_from__R(const std::pair<int, int>& elem) const
{
	// assumes that R neigbour exists
	auto tile_c = shape.get__R_tile(elem);
	return is_already_filled(tile_c);
}

bool rikudo::is_filled_neighbour_from_DR(const std::pair<int, int>& elem) const
{
	// assumes that DR neigbour exists
	auto tile_c = shape.get_DR_tile(elem);
	return is_already_filled(tile_c);
}

bool rikudo::is_filled_neighbour_from_DL(const std::pair<int, int>& elem) const
{
	// assumes that DL neigbour exists
	auto tile_c = shape.get_DL_tile(elem);
	return is_already_filled(tile_c);
}

bool rikudo::is_filled_neighbour_from__L(const std::pair<int, int>& elem) const
{
	// assumes that L neigbour exists
	auto tile_c = shape.get__L_tile(elem);
	return is_already_filled(tile_c);
}

bool rikudo::is_filled_neighbour_from_UL(const std::pair<int, int>& elem) const
{
	// assumes that UL neigbour exists
	auto tile_c = shape.get_UL_tile(elem);
	return is_already_filled(tile_c);
}



bool rikudo::are_neighbours_from_UR(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const
{
	std::pair<int, int> tile;
	tile = shape.get_UR_tile(addr1);
	if (tile == addr2)
		return true;

	return false;
}

bool rikudo::are_neighbours_from__R(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const
{
	std::pair<int, int> tile;
	tile = shape.get__R_tile(addr1);
	if (tile == addr2)
		return true;

	return false;
}

bool rikudo::are_neighbours_from_DR(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const
{
	std::pair<int, int> tile;
	tile = shape.get_DR_tile(addr1);
	if (tile == addr2)
		return true;

	return false;
}

bool rikudo::are_neighbours_from_DL(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const
{
	std::pair<int, int> tile;

	tile = shape.get_DL_tile(addr1);
	if (tile == addr2)
		return true;

	return false;
}

bool rikudo::are_neighbours_from__L(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const
{
	std::pair<int, int> tile;

	tile = shape.get__L_tile(addr1);
	if (tile == addr2)
		return true;

	return false;
}

bool rikudo::are_neighbours_from_UL(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const
{
	std::pair<int, int> tile;

	tile = shape.get_UL_tile(addr1);
	if (tile == addr2)
		return true;

	return false;
}

bool rikudo::are_neighbours(const std::pair<int, int>& addr1, const std::pair<int, int>& addr2) const
{
	return are_neighbours_from_UR(addr1, addr2) ||
		are_neighbours_from__R(addr1, addr2) ||
		are_neighbours_from_DR(addr1, addr2) ||
		are_neighbours_from_DL(addr1, addr2) ||
		are_neighbours_from__L(addr1, addr2) ||
		are_neighbours_from_UL(addr1, addr2);
}

bool rikudo::has_enough_space_elem(int filled_value) const
{
	int necc_count = 0;
	auto elem = get_addr(filled_value);
	if (filled_value - 1 >= 1 && !is_already_filled(filled_value))
		necc_count++;
	if (filled_value + 1 <= max_elem_value && !is_already_filled(filled_value + 1))
		necc_count++;
	int has_count = (int)get_unfilled_neighbours(elem).size();
	if (has_count < necc_count) {
		//std::cerr << "(" << elem.first << "," << elem.second << ")[" << filled_value << "] needs " << necc_count << ", but it has only " << has_count << " neighbours.\n";
		//disp_crude();
		return false;
	}

	return true;
}

bool rikudo::has_enough_space_elems() const
{
	for (auto& v : forced_values)
		if (!has_enough_space_elem(v.second)) {
			return false;
		}

	for (auto& v : filled_values)
		if (!has_enough_space_elem(v.second))
			return false;

	return true;
}


// assumes that all fillable blocks
// contain just internal elements 1 < ee < max_elem
bool rikudo::is_attached(int block_idx) const
{
	if (!fillable_blocks[block_idx].used)
		return false;

	// is used
	int val1 = get_elem(fillable_blocks[block_idx].end1);
	int val2 = get_elem(fillable_blocks[block_idx].end2);

	if (val1 <= val2) {
		if (!is_already_filled(val1 - 1) || !is_already_filled(val2 + 1))
			return false;
	}
	else {
		if (!is_already_filled(val1 + 1) || !is_already_filled(val2 - 1))
			return false;
	}
	return true;
}

bool rikudo::can_be_attached(int block_idx) const
{
	//return true;
	bool b_end1 = false;
	if (!is_attached(block_idx)) {
		// get attach candidates
		std::set<std::pair<int, int>> candidates_end1, candidates_end2;
		std::set<std::pair<int, int>> union_of_canditates;

		for (int dir = 0; dir < 6; dir++) {
			auto tile = shape.get_tile_in_dir(fillable_blocks[block_idx].end1, dir);
			if (tile != std::pair<int, int>(-1, -1) &&
				std::find(non_fillable.begin(), non_fillable.end(), tile) == non_fillable.end()
				) {
				if (is_forced_element(tile) && !is_attached_forced_value(get_elem(tile)))
					candidates_end1.insert(tile);
				else {
					int bidx = get_fillable_block_index_with_end_containing_elem(tile);
					if (bidx != -1 && !is_attached(bidx)) {
						if (fillable_blocks[bidx].used) {
							if (fillable_blocks[bidx].length > 1) {
								if (tile == fillable_blocks[bidx].end1) {
									if (get_elem(fillable_blocks[bidx].end1) < get_elem(fillable_blocks[bidx].end2)) {
										if (!is_already_filled(get_elem(fillable_blocks[bidx].end1) - 1))
											candidates_end1.insert(tile);
									}
									else {
										if (!is_already_filled(get_elem(fillable_blocks[bidx].end1) + 1))
											candidates_end1.insert(tile);
									}
								}
								else {
									if (get_elem(fillable_blocks[bidx].end1) < get_elem(fillable_blocks[bidx].end2)) {
										if (!is_already_filled(get_elem(fillable_blocks[bidx].end2) + 1))
											candidates_end1.insert(tile);
									}
									else {
										if (!is_already_filled(get_elem(fillable_blocks[bidx].end2) - 1))
											candidates_end1.insert(tile);
									}
								}
							}
							else {
								candidates_end1.insert(tile);
							}
						}
						else {
							candidates_end1.insert(tile);
						}
					}
				}
			}
		}
		b_end1 = candidates_end1.empty();

		if (!fillable_blocks[block_idx].used || fillable_blocks[block_idx].length == 1)
			if (b_end1) {
				return false;
			}

		union_of_canditates = candidates_end1;

		if (fillable_blocks[block_idx].length > 1) {
			for (int dir = 0; dir < 6; dir++) {
				auto tile = shape.get_tile_in_dir(fillable_blocks[block_idx].end2, dir);
				if (tile != std::pair<int, int>(-1, -1) &&
					std::find(non_fillable.begin(), non_fillable.end(), tile) == non_fillable.end()
					) {
					if (is_forced_element(tile) && !is_attached_forced_value(get_elem(tile)))
						candidates_end2.insert(tile);
					else {
						int bidx = get_fillable_block_index_with_end_containing_elem(tile);
						if (bidx != -1 && !is_attached(bidx)) {
							if (fillable_blocks[bidx].used) {
								if (fillable_blocks[bidx].length > 1) {
									if (tile == fillable_blocks[bidx].end1) {
										if (get_elem(fillable_blocks[bidx].end1) < get_elem(fillable_blocks[bidx].end2)) {
											if (!is_already_filled(get_elem(fillable_blocks[bidx].end1) - 1))
												candidates_end2.insert(tile);
										}
										else {
											if (!is_already_filled(get_elem(fillable_blocks[bidx].end1) + 1))
												candidates_end2.insert(tile);
										}
									}
									else {
										if (get_elem(fillable_blocks[bidx].end1) < get_elem(fillable_blocks[bidx].end2)) {
											if (!is_already_filled(get_elem(fillable_blocks[bidx].end2) + 1))
												candidates_end2.insert(tile);
										}
										else {
											if (!is_already_filled(get_elem(fillable_blocks[bidx].end2) - 1))
												candidates_end2.insert(tile);
										}
									}
								}
								else {
									candidates_end2.insert(tile);
								}
							}
							else {
								candidates_end2.insert(tile);
							}
						}
					}
				}
			}

			if (!fillable_blocks[block_idx].used || b_end1)
				if (candidates_end2.empty()) {
					return false;
				}


			/*for (auto& e : candidates_end1)
				union_of_canditates.insert(e);*/
			for (auto& e : candidates_end2)
				union_of_canditates.insert(e);
		}

		if (!fillable_blocks[block_idx].used) {
			if (union_of_canditates.size() < 2) {
				/*std::cerr << "Block " << block_idx << ":";
				for (auto& e : fillable_blocks[block_idx].tiles)
					std::cerr << " " << e;
				std::cerr << " cannot be attached.\nFound just these candidates to attach:";
				for (auto& e : union_of_canditates)
					std::cerr << " " << e;
				std::cerr << '\n';
				disp_crude();*/
				return false;
			}
		}
	}
	return true;
}

bool rikudo::can_be_attached_all() const
{
	//return true;
	/* Original function */
	for (int i = 0; i < fillable_blocks.size(); i++) {
		//bool b1 = is_attached(i);
		//bool b2 = can_be_attached(i);
		if (!is_attached(i) && !can_be_attached(i)) {
			// find error


			/*std::cout << "Block " << i << ": ";
			for (auto& e : fillable_blocks[i].tiles)
				std::cout << " " << e;
			std::cout << " cannot be attached.\n";
			disp_crude();
			bool b1 = is_attached(i);
			bool b2 = can_be_attached(i);*/
			return false;
		}

	}
	return true;

#if 0
	/* Function to find error */
	for (int i = 0; i < fillable_blocks.size(); i++) {
		if (!is_attached(i) && !can_be_attached(i)) {
			// find error:
			// if is partially correct and ends here
			// error


			bool b_partially_correct = true;
			for (auto& e : filled_values) {
				int correct_value = medium_correctly_filled[e.first];//medium_correctly_filled.find(e.first)->second;
				int filled_value = e.second;
				if (filled_value != correct_value) {
					b_partially_correct = false;
					break;
				}

			}
			if (b_partially_correct) {
				std::cerr << "Problem with `can_be_attached` for block: " << i << '\n';
				disp_crude();

				return true;
			}



			/*std::cout << "Block " << i << ": ";
			for (auto& e : fillable_blocks[i].tiles)
				std::cout << " " << e;
			std::cout << " cannot be attached.\n";
			disp_crude();*/
			//return false;
		}

	}
	return true;
#endif
}

bool rikudo::is_attached_forced_value(int fv) const
{
	if (fv > 1 && fv < max_elem_value) {
		if (is_already_filled(fv - 1) && is_already_filled(fv + 1))
			return true;
	}
	else {
		if (fv == 1) {
			if (is_already_filled(fv + 1))
				return true;
		}
		if (fv == max_elem_value)
			if (is_already_filled(fv - 1))
				return true;
	}
	return false;
}

void rikudo::get_unfilled_intervals(std::vector<std::pair<int, int>>& intervals) const
{
	int sidx = first_forced_value;
	do {
		int first_unfilled_value = -1;
		for (int i = sidx; i <= last_forced_value; i++)
			if (!is_already_filled(i)) {
				first_unfilled_value = i;
				break;
			}

		if (first_unfilled_value != -1) {
			int interval_start;
			if (first_unfilled_value < first_forced_value)
				interval_start = first_forced_value;
			else
				interval_start = first_unfilled_value - 1;

			if (!is_already_filled(interval_start + 1)) {
				int idx = interval_start + 1;
				while (idx <= last_forced_value && !is_already_filled(idx)) {
					idx++;
				}
				int interval_end;
				if (idx <= last_forced_value)
					interval_end = idx;
				else
					interval_end = -1;

				if (interval_end != -1) {

					intervals.push_back({ interval_start, interval_end });
					sidx = interval_end;
				}
				else
					sidx = last_forced_value;
			}
		}
		else
			break;

	} while (sidx <= last_forced_value);
}

bool rikudo::test_block_components() const
{
	// get unprocessed unfilled blocks
	std::set<int> unfilled_blocks_unprocessed;
	int bidx = 0;
	for (auto& b : fillable_blocks) {
		if (!b.used)
			unfilled_blocks_unprocessed.insert(bidx);
		bidx++;
	}

	// find components of connectivity
	std::vector<std::set<int>> block_components;
	while (!unfilled_blocks_unprocessed.empty()) {
		std::set<int> b_component;
		std::set<int> to_expand;
		std::set<int> processed;
		//std::map<int, int> b_processed;
		// select first unprocessed
		b_component.insert(*unfilled_blocks_unprocessed.begin());
		to_expand.insert(*unfilled_blocks_unprocessed.begin());

		while (!to_expand.empty()) {

			std::set<int> new_to_expand;

			for (int exp_idx : to_expand) {
				for (auto& nei_idx : get_unfilled_neighbour_blocks_idxs(fillable_blocks[exp_idx].end1))
					if (processed.find(nei_idx) == processed.end()) {
						// if not already processed
						new_to_expand.insert(nei_idx);
						b_component.insert(nei_idx);
					}
				if (fillable_blocks[exp_idx].length > 1) {
					// expand also end2
					for (auto& nei_idx : get_unfilled_neighbour_blocks_idxs(fillable_blocks[exp_idx].end2))
						if (processed.find(nei_idx) == processed.end()) {
							// if not already processed
							new_to_expand.insert(nei_idx);
							b_component.insert(nei_idx);
						}
				}
				processed.insert(exp_idx);
			}
			to_expand.clear();
			for (int nexp_idx : new_to_expand)
				to_expand.insert(nexp_idx);
		}

		// print component
		/*std::cout << "Component: ";
		for (int c_idx : b_component) {
			std::cout << " " << c_idx;
		}
		std::cout << '\n';*/

		// process_component
		//int cnt_connections = 0;
		//std::vector<std::pair<int, int>> possible_connections_to_filled;
		std::set<std::pair<int, int>> possible_connections_to_filled;
		for (int c_idx : b_component) {
			// count possible connections to already filled end1
			for (int dir = 0; dir < 6; dir++) {
				auto tile = shape.get_tile_in_dir(fillable_blocks[c_idx].end1, dir);
				if (tile != std::pair<int, int>({ -1, -1 }) && std::find(non_fillable.begin(), non_fillable.end(), tile) == non_fillable.end()) {
					if (is_forced_element(tile)) {
						if (!is_attached_forced_value(get_elem(tile)))
							//possible_connections_to_filled.push_back(tile);
							possible_connections_to_filled.insert(tile);
					}
					else {
						int b_idx = get_fillable_block_index_with_end_containing_elem(tile);
						if (b_idx != -1 && fillable_blocks[b_idx].used && !is_attached(b_idx)) {
							int val1 = get_elem(fillable_blocks[b_idx].end1);
							int val2 = get_elem(fillable_blocks[b_idx].end2);

							if (val1 != val2) {
								// which end is unsaturated
								if (val1 < val2) {
									if (is_already_filled(val1 - 1)) {
										if (is_already_filled(val2 + 1)) {
											std::cerr << "Error: no unsaturaded\n";
										}
										else {
											//possible_connections_to_filled.push_back(fillable_blocks[b_idx].end2);
											possible_connections_to_filled.insert(fillable_blocks[b_idx].end2);
										}
									}
									else {
										//possible_connections_to_filled.push_back(fillable_blocks[b_idx].end1);
										possible_connections_to_filled.insert(fillable_blocks[b_idx].end1);
									}
								}
								else {
									// val2 < val1
									if (is_already_filled(val2 - 1)) {
										if (is_already_filled(val1 + 1)) {
											std::cerr << "Error: no unsaturaded\n";
										}
										else {
											possible_connections_to_filled.insert(fillable_blocks[b_idx].end1);
										}
									}
									else {
										possible_connections_to_filled.insert(fillable_blocks[b_idx].end2);
									}
								}
							}
							else {
								possible_connections_to_filled.insert(tile);
							}
						}
					}
				}
			}

			if (fillable_blocks[c_idx].length > 1) {
				// count possible connections to already filled end2
				for (int dir = 0; dir < 6; dir++) {
					auto tile = shape.get_tile_in_dir(fillable_blocks[c_idx].end2, dir);
					if (tile != std::pair<int, int>({ -1, -1 }) && std::find(non_fillable.begin(), non_fillable.end(), tile) == non_fillable.end()) {
						if (is_forced_element(tile)) {
							if (!is_attached_forced_value(get_elem(tile)))
								possible_connections_to_filled.insert(tile);
						}
						else {
							int b_idx = get_fillable_block_index_with_end_containing_elem(tile);
							if (b_idx != -1 && fillable_blocks[b_idx].used && !is_attached(b_idx)) {
								int val1 = get_elem(fillable_blocks[b_idx].end1);
								int val2 = get_elem(fillable_blocks[b_idx].end2);

								if (val1 != val2) {
									// which end is unsaturated
									if (val1 < val2) {
										if (is_already_filled(val1 - 1)) {
											if (is_already_filled(val2 + 1)) {
												std::cerr << "Error: no unsaturaded\n";
											}
											else {
												possible_connections_to_filled.insert(fillable_blocks[b_idx].end2);
											}
										}
										else {
											possible_connections_to_filled.insert(fillable_blocks[b_idx].end1);
										}
									}
									else {
										// val2 < val1
										if (is_already_filled(val2 - 1)) {
											if (is_already_filled(val1 + 1)) {
												std::cerr << "Error: no unsaturaded\n";
											}
											else {
												possible_connections_to_filled.insert(fillable_blocks[b_idx].end1);
											}
										}
										else {
											possible_connections_to_filled.insert(fillable_blocks[b_idx].end2);
										}
									}
								}
								else {
									possible_connections_to_filled.insert(tile);
								}
							}
						}
					}
				}
			}
		}

		if (possible_connections_to_filled.size() < 2)
			return false;
		else {
			if ((possible_connections_to_filled.size() == 2)) {
				// compute size of component
				int size = 0;
				for (int c_idx : b_component) {
					size += fillable_blocks[c_idx].length;
				}
				auto it = possible_connections_to_filled.begin();
				int val1 = get_elem(*it);
				++it;
				int val2 = get_elem(*it);

				if (size != abs(val1 - val2) - 1)
					return false;
			}


			//	// find if size is one of possible diffs
			//	bool b_found = false;
			//	for (auto& e1 : possible_connections_to_filled) {
			//		if (!b_found)
			//			for (auto& e2 : possible_connections_to_filled)
			//				if (!b_found)
			//					if (e1 != e2) {
			//						int val1 = get_elem(e1);
			//						int val2 = get_elem(e2);
			//						if (size == abs(val1 - val2) - 1)
			//							b_found = true;
			//					}
			//	}
			//	if (!b_found)
			//		return false;
		}


		// remove component from unfilled_blocks_unprocessed
		for (int c_idx : b_component)
			unfilled_blocks_unprocessed.erase(c_idx);
	}

	return true;
}

bool rikudo::exist_paths_via_unfilled()
{
	//find_first_unfilled
	int sidx = first_forced_value;
	do {
		int first_unfilled_value = -1;
		for (int i = sidx; i <= last_forced_value; i++)
			if (!is_already_filled(i)) {
				first_unfilled_value = i;
				break;
			}

		if (first_unfilled_value != -1) {
			int interval_start;
			if (first_unfilled_value < first_forced_value)
				interval_start = first_forced_value;
			else
				interval_start = first_unfilled_value - 1;

			if (!is_already_filled(interval_start + 1)) {
				int idx = interval_start + 1;
				while (idx <= last_forced_value && !is_already_filled(idx)) {
					idx++;
				}
				int interval_end;
				if (idx <= last_forced_value)
					interval_end = idx;
				else
					interval_end = -1;

				if (interval_end != -1) {

					bool b_path_found = false;
					//std::vector<std::pair<int,int>> v_bs;
					std::vector<int> v_bs;
					std::vector<int> v_bc;
					std::vector<std::pair<int, int>> v_es;

					auto el_from = get_addr(interval_start),
						el_to = get_addr(interval_end);
					int plen = interval_end - interval_start - 1;


					/*exists_path_via_unused_blocks_of_length_recOLD(plen, v_bs, v_bc, v_es, *this,
						el_from, el_to, b_path_found, false);*/
					exists_path_via_unused_blocks_of_length_rec(plen, v_bs, v_bc, interval_start, interval_end, *this,
						el_from, el_to, b_path_found);
					//exists_path_of_length(interval_end - interval_start, vv, myrikudo, myrikudo.get_addr(interval_start), myrikudo.get_addr(interval_end));
					/*if (changed || (v_min == v.start && v_max == v.end)) {
						std::cerr << "Checking the interval [" << interval_start << "," << interval_end << "]: " << b_path_found << "\n";
					}*/

					if (!b_path_found) {
						//std::cerr << "There is no path via unfilled block from " << interval_start << " to " << interval_end << '\n';
						//myrikudo.disp_crude();
						return false;
					}

					sidx = interval_end;
				}
				else
					sidx = last_forced_value;
			}

		}
		else
			break;

	} while (sidx <= last_forced_value);

	return true;
}

bool rikudo::init()
{
	init_forced_values_inv();
	int min_value = max_elem_value;
	int max_value = 1;
	for (auto& e : forced_values_inv) {
		if (min_value > e.first)
			min_value = e.first;
		if (max_value < e.first)
			max_value = e.first;
	}
	first_forced_value = min_value;
	last_forced_value = max_value;

	return initialize_fillable_blocks();
}

bool rikudo::initialize_fillable_blocks()
{
	// initialize blocks (TODO as function of rikudo struct)
	std::set<std::pair<int, int>> unmatched_forced;
	//std::vector<fillable_block> fillable_blocks;
	{
		for (int i = 0; i < shape.rows; i++)
			for (int j = 0; j < shape.row_sizes[i]; j++) {
				if (is_fillable_element({ i,j })) {
					if (!count_forced_orders({ i,j })) {
						// tiles without forced orders
						// form a block of size 1
						fillable_blocks.push_back({ 1, {{i,j}}, {i,j}, {i,j} });
					}
					else {
						unmatched_forced.insert({ i,j });
					}
				}
			}

		// try to join forced tiles into blocks
		while (!unmatched_forced.empty()) {
			std::vector<std::pair<int, int>> block;
			// find unmatched with a single forced order

			std::pair<int, int> block_start = { -1,-1 };
			for (auto& e : unmatched_forced) {
				if (count_forced_orders(e) == 1) {
					block_start = e;
					break;
				}
			}

			// assert 
			if (block_start == std::pair<int, int>({ -1, -1 }))
			{
				std::cerr << "Error: There is no beginning of matched order!\n";
				return false;
			}

			// follow the path via forced directions
			block.push_back(block_start);
			auto fo = get_forced_orders(block_start);
			int forced_direction = rikudo::get_numeric_direction(fo);

			std::pair<int, int> curr_tile = block_start;
			std::pair<int, int> block_end = { -1, -1 };
			bool finished_block = false;
			do {
				auto next_tile = shape.get_tile_in_dir(curr_tile, forced_direction);
				if (count_forced_orders(next_tile) == 1) {
					// next tile is the ending path
					block_end = next_tile;
					block.push_back(next_tile);
					finished_block = true;
				}
				else {
					// two forced directions
					// continue
					int fos = get_forced_orders(next_tile);
					// remove opposite direction
					fos &= ~(1 << ((forced_direction + 3) % 6));
					forced_direction = rikudo::get_numeric_direction(fos);
					block.push_back(next_tile);
					curr_tile = next_tile;
				}
			} while (!finished_block);

			fillable_blocks.push_back({ (int)block.size(), block, block_start, block_end });

			// remove from unmatched
			for (auto& ti : block) {
				if (unmatched_forced.find(ti) != unmatched_forced.end())
					unmatched_forced.erase(ti);
			}
		}
	}
	return true;
}

int rikudo::get_numeric_direction(int hex_dir)
{
	if (hex_dir == UR)
		return 0;

	if (hex_dir == _R)
		return 1;

	if (hex_dir == DR)
		return 2;

	if (hex_dir == DL)
		return 3;

	if (hex_dir == _L)
		return 4;

	if (hex_dir == UL)
		return 5;

	return -1;
}

void rikudo::disp_crude() const
{
	for (int i = (int)shape.row_sizes.size() - 1; i >= 0; i--) {
		for (int j = 0; j < shape.row_sizes[i]; j++) {
			int val = get_elem({ i,j });
			if (val == -1) {
				std::cout << " X ";
			}
			else if (val == 0) {
				std::cout << " . ";
			}
			else
				std::cout << " " << val << " ";

		}
		std::cout << '\n';
	}
}

bool rikudo::check_forced_orders() const
{
	for (const auto& p : forced_orders)
	{
		if (p.second & UR)
		{
			auto neigh = shape.get_UR_tile(p.first.first, p.first.second);

			if (neigh.first == -1 && neigh.second == -1)
			{
				std::cout << "Tile (" << p.first.first << "," << p.first.second << ") has no neighbour in UR direction" << '\n';
				return false;
			}
			if (forced_orders.find({ neigh.first, neigh.second }) != forced_orders.end())
			{
				if (!(forced_orders.at({ neigh.first, neigh.second }) & DL))
				{
					std::cout << "Tile (" << p.first.first << "," << p.first.second << ") is missing DL forced order specializer" << '\n';
				}
			}
			else
			{
				std::cout << "Tile (" << neigh.first << "," << neigh.second << ") has no forced order specializer" << '\n';
				return false;
			}
		}

		if (p.second & _R)
		{
			auto neigh = shape.get__R_tile(p.first.first, p.first.second);

			if (neigh.first == -1 && neigh.second == -1)
			{
				std::cout << "Tile (" << p.first.first << "," << p.first.second << ") has no neighbour in R direction" << '\n';
				return false;
			}
			if (forced_orders.find({ neigh.first, neigh.second }) != forced_orders.end())
			{
				if (!(forced_orders.at({ neigh.first, neigh.second }) & _L))
				{
					std::cout << "Tile (" << p.first.first << "," << p.first.second << ") is missing L forced order specializer" << '\n';
				}
			}
			else
			{
				std::cout << "Tile (" << neigh.first << "," << neigh.second << ") has no forced order specializer" << '\n';
				return false;
			}
		}

		if (p.second & DR)
		{
			auto neigh = shape.get_DR_tile(p.first.first, p.first.second);

			if (neigh.first == -1 && neigh.second == -1)
			{
				std::cout << "Tile (" << p.first.first << "," << p.first.second << ") has no neighbour in DR direction" << '\n';
				return false;
			}
			if (forced_orders.find({ neigh.first, neigh.second }) != forced_orders.end())
			{
				if (!(forced_orders.at({ neigh.first, neigh.second }) & UL))
				{
					std::cout << "Tile (" << p.first.first << "," << p.first.second << ") is missing UL forced order specializer" << '\n';
				}
			}
			else
			{
				std::cout << "Tile (" << neigh.first << "," << neigh.second << ") has no forced order specializer" << '\n';
				return false;
			}
		}

		if (p.second & DL)
		{
			auto neigh = shape.get_DL_tile(p.first.first, p.first.second);

			if (neigh.first == -1 && neigh.second == -1)
			{
				std::cout << "Tile (" << p.first.first << "," << p.first.second << ") has no neighbour in DL direction" << '\n';
				return false;
			}
			if (forced_orders.find({ neigh.first, neigh.second }) != forced_orders.end())
			{
				if (!(forced_orders.at({ neigh.first, neigh.second }) & UR))
				{
					std::cout << "Tile (" << p.first.first << "," << p.first.second << ") is missing UR forced order specializer" << '\n';
				}
			}
			else
			{
				std::cout << "Tile (" << neigh.first << "," << neigh.second << ") has no forced order specializer" << '\n';
				return false;
			}
		}

		if (p.second & _L)
		{
			auto neigh = shape.get__L_tile(p.first.first, p.first.second);

			if (neigh.first == -1 && neigh.second == -1)
			{
				std::cout << "Tile (" << p.first.first << "," << p.first.second << ") has no neighbour in L direction" << '\n';
				return false;
			}
			if (forced_orders.find({ neigh.first, neigh.second }) != forced_orders.end())
			{
				if (!(forced_orders.at({ neigh.first, neigh.second }) & _R))
				{
					std::cout << "Tile (" << p.first.first << "," << p.first.second << ") is missing R forced order specializer" << '\n';
				}
			}
			else
			{
				std::cout << "Tile (" << neigh.first << "," << neigh.second << ") has no forced order specializer" << '\n';
				return false;
			}
		}

		if (p.second & UL)
		{
			auto neigh = shape.get_UL_tile(p.first.first, p.first.second);

			if (neigh.first == -1 && neigh.second == -1)
			{
				std::cout << "Tile (" << p.first.first << "," << p.first.second << ") has no neighbour in UL direction" << '\n';
				return false;
			}
			if (forced_orders.find({ neigh.first, neigh.second }) != forced_orders.end())
			{
				if (!(forced_orders.at({ neigh.first, neigh.second }) & DR))
				{
					std::cout << "Tile (" << p.first.first << "," << p.first.second << ") is missing DR forced order specializer" << '\n';
				}
			}
			else
			{
				std::cout << "Tile (" << neigh.first << "," << neigh.second << ") has no forced order specializer" << '\n';
				return false;
			}
		}
	}
	return true;
}

int rikudo::get_forced_orders(const std::pair<int, int>& elem) const
{
	auto it = forced_orders.find(elem);
	int ff = 0;
	if (it != forced_orders.end())
		ff = it->second;
	return ff;
}

int rikudo::count_forced_orders(const std::pair<int, int>& elem) const
{
	auto it = forced_orders.find(elem);
	int ff = 0;
	if (it != forced_orders.end())
		ff = it->second;
	int cnt = 0;
	if (ff) {
		if (ff & UR)
			cnt++;
		if (ff & _R)
			cnt++;
		if (ff & DR)
			cnt++;
		if (ff & DL)
			cnt++;
		if (ff & _L)
			cnt++;
		if (ff & UL)
			cnt++;
	}

	return cnt;
}

bool rikudo::is_forced_from_UR(const std::pair<int, int>& elem) const
{
	auto it = forced_orders.find(elem);
	if (it != forced_orders.end())
		return (it->second & UR) != 0;
	else
		return false;
}

bool rikudo::is_forced_from__R(const std::pair<int, int>& elem) const
{
	auto it = forced_orders.find(elem);
	if (it != forced_orders.end())
		return (it->second & _R) != 0;
	else
		return false;
}

bool rikudo::is_forced_from_DR(const std::pair<int, int>& elem) const
{
	auto it = forced_orders.find(elem);
	if (it != forced_orders.end())
		return (it->second & DR) != 0;
	else
		return false;
}

bool rikudo::is_forced_from_DL(const std::pair<int, int>& elem) const
{
	auto it = forced_orders.find(elem);
	if (it != forced_orders.end())
		return (it->second & DL) != 0;
	else
		return false;
}

bool rikudo::is_forced_from__L(const std::pair<int, int>& elem) const
{
	auto it = forced_orders.find(elem);
	if (it != forced_orders.end())
		return (it->second & _L) != 0;
	else
		return false;
}

bool rikudo::is_forced_from_UL(const std::pair<int, int>& elem) const
{
	auto it = forced_orders.find(elem);
	if (it != forced_orders.end())
		return (it->second & UL) != 0;
	else
		return false;
}

bool rikudo::is_forced_element(int value) const
{
	return forced_values_inv.find(value) != forced_values_inv.end();
}


bool rikudo::is_forced_element(const std::pair<int, int>& elem) const
{
	return forced_values.find(elem) != forced_values.end();
}


bool rikudo::is_fillable_element(const std::pair<int, int>& elem) const
{
	return shape.check_coords(elem.first, elem.second) // is valid address
		&& std::find(non_fillable.begin(), non_fillable.end(), elem)
		== non_fillable.end() // is not unfillable
		&& forced_values.find(elem) == forced_values.end(); // is not forced value
}

