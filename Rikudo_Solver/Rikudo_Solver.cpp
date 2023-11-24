// Rikudo_Solver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include "rikudo_shape.h"
#include "rikudo.h"

// global
int v_min, v_max;

// global for debugging

std::map<std::pair<int, int>, int> small_correctly_filled{
	{{0,0}, 18}, {{0,1}, 17}, {{0,2}, 12}, {{0,3}, 11},
	{{1,0}, 19}, {{1,2}, 13}, {{1,4}, 9},
	{{2,0}, 22}, {{2,1}, 20}, {{2,2}, 15}, {{2,3}, 14},	{{2,4}, 7},	{{2,5}, 8},
	{{3,0}, 23}, {{3,2}, 26}, {{3,4}, 6}, {{3,6}, 36},
	{{4,1}, 25}, {{4,4}, 4}, {{4,5}, 5},
	{{5,0}, 29}, {{5,0}, 28}, {{5,0}, 2}, {{5,0}, 3}, {{5,0}, 34},
	{{6,0}, 30}, {{6,1}, 31}, {{6,2}, 32}
};

/*
47  48  49  54  55
46  45  50  51  53  56
42  43  44  6  52  58  57
41  2  3  5  7  60  59  13
40  39  1  4  X  8  10  12  14
37  38  34  33  32  9  11  15
36  35  28  29  31  18  16
26  27  23  30  19  17
25  24  22  21  20
*/

std::map<std::pair<int, int>, int> medium_correctly_filled{
	{{0,0}, 25}, {{0,1}, 24}, {{0,2}, 22}, {{0,3}, 21}, {{0,4}, 20},
	{{1,0}, 26}, {{1,1}, 27}, {{1,2}, 23}, {{1,3}, 30}, {{1,4}, 19}, {{1,4}, 17},
	{{2,0}, 36}, {{2,1}, 35}, {{2,2}, 28}, {{2,3}, 29},	{{2,4}, 31}, {{2,5}, 18}, {{2,6}, 16},
	{{3,0}, 37}, {{3,1}, 38}, {{3,2}, 34}, {{3,3}, 33}, {{3,4}, 32}, {{3,5}, 9}, {{3,6}, 11}, {{3,7}, 15},
	{{4,0}, 40}, {{4,1}, 39}, {{4,2}, 1}, {{4,3}, 4}, {{4,5}, 8}, {{4,6}, 10}, {{4,7}, 12}, {{4,8}, 14},
	{{5,0}, 41}, {{5,1}, 2}, {{5,2}, 3}, {{5,3}, 5}, {{5,4}, 7}, {{5,5}, 60}, {{5,6}, 59}, {{5,7}, 13},
	{{6,0}, 42}, {{6,1}, 43}, {{6,2}, 44}, {{6,3}, 6}, {{6,4}, 52}, {{6,5}, 58}, {{6,6}, 57},	
	{{7,0}, 46}, {{7,1}, 45}, {{7,2}, 50}, {{7,3}, 51}, {{7,4}, 53}, {{7,5}, 56},
	{{8,0}, 47}, {{8,1}, 48}, {{8,2}, 49}, {{8,3}, 54}, {{8,4}, 55}

};


bool operator==(const std::pair<int, int> &p1, const std::pair<int, int> &p2)
{
	return p1.first == p2.first && p1.second == p2.second;
}

//bool operator==(const std::pair<int, bool>& p1, const std::pair<int, bool>& p2)
//{
//	return p1.first == p2.first && p1.second == p2.second;
//}

std::ostream& operator<<(std::ostream& os, const std::pair<int,int> &el) {
	os << "(" << el.first << "," << el.second << ")";
	return os;
}


bool test_forced_connectivity(rikudo& myrikudo, const std::pair<int, int>& filled_start, const std::pair<int, int>& filled_end, const std::vector<std::pair<int, int>>& path_of_unfilled);


/*
	solve_neigh_elem(elem)
		if (missing_filled(elem - 1) && (elem + 1)
			if (exists(elem - 1 ) && is_not_filled(elem - 1))
				for (each free position around elem)
					try_to_fill(elem - 1) -> tmp_board with filled elem - 1
					if (exists(elem + 1) && is_not_filled(elem + 1))
						for (each free position around elem on tmp_board)
							try_to_fill(elem + 1) -> board with filled elem - 1
		else
		if (missing_filled(elem - 1) && filled (elem + 1)
		else
		if (missing_filled(elem + 1) && filled (elem - 1)


	try_to_fill(elem_id, pos)
		
*/







struct hexagon
{
	int value;
	bool is_filled;

	std::array<int, 6> neighbours; //  UR, R, DR, DL, L, UL
	std::array<bool, 6> forced_order; 
};

std::array<hexagon, 93> field;
#if 0
{ {
	{ 1, true, {10, 2, -1, -1, -1, 8}, {false, false, false, false, false, false}},
	{-1, true, {11, 3, -1, -1, 1, 10}, {false, false, false, false, false, false}},
	{-1, true, {}
} };
#endif

/* 
 ...
row+1
 row
row+1
 row


 [row, col] -> neighbours 
 UR -> row % 2 == 1 [row + 1, col + 1], 
    -> row % 2 == 0 [row + 1, col]
 R  -> [row, col + 1]
 DR -> row % 2 == 1 [row - 1, col + 1]

*/
void init_field(int row, int columns)
{

}

void disp_pair(const std::pair<int, int>& p) {
	std::cout << "(" << p.first << "," << p.second << ")";
}

bool test_solution(const rikudo& myrikudo) {

	std::pair<int, int> addr1 = myrikudo.get_addr(1);
	for (int i = 2; i <= myrikudo.max_elem_value; i++) {
		std::pair<int, int> addr2 = myrikudo.get_addr(i);
		//std::cout << "Comparing pairs ";
		//disp_pair(addr1); std::cout << ", ";
		//disp_pair(addr2); std::cout << ": ";
		bool v = myrikudo.are_neighbours(addr1, addr2);
		//std::cout << v << '\n';
		if (!v)
			return false;
		addr1 = addr2;
	}

	return true;
}

bool exists_neighbour(rikudo& myrikudo, std::set<std::pair<int,int>> &verts, std::pair<int, int> &elem) {
	for (auto& v : verts) {
		if (myrikudo.are_neighbours(v, elem))
			return true;
	}
	return false;
}


// global
bool b_path_found = false;
int number_of_solutions = 0;
// the number of unfilled elements between 
void exists_path_of_length(int length, std::vector<std::pair<int,int>> & used_elements, rikudo& myrikudo, const std::pair<int, int>& el_from, const std::pair<int, int>& el_to, bool b_all=false) {
	if (!b_all)
		if (b_path_found)
			return;

	if (length == 0) {
		if (myrikudo.are_neighbours(used_elements.back(), el_to) 
			 //&& test_forced_connectivity(myrikudo, el_from, el_to, used_elements)
			) {
			b_path_found = true;
			// for DEBUG

			/*std::cerr << el_from;
			for (auto& e : used_elements)
				std::cerr << " -> " << e;
			std::cerr << " -> " << el_to << '\n';
			number_of_solutions++;*/
		}
	}
	else {
		std::pair<int, int> el_start;
		
		if (used_elements.empty())
			el_start = el_from;
		else
			el_start = used_elements.back();

		for (auto& e : myrikudo.get_unfilled_neighbours(el_start)) {
			if (b_all || !b_path_found ) {
				if (e.first != el_from && std::find(used_elements.begin(), used_elements.end(), e.first) == used_elements.end()) {
					// try to prolong path
					used_elements.push_back(e.first);
					exists_path_of_length(length - 1, used_elements, myrikudo, el_from, el_to, b_all);
					used_elements.pop_back();

				}
			}
		}
	}
}



// used elements - all elements of path
void exists_path_via_unused_blocks_of_length_recOLD(int length, std::vector<int>& used_blocks, std::vector<int>& used_connections, std::vector<std::pair<int,int>>& used_elements, rikudo &myrikudo, const std::pair<int, int>& el_from, const std::pair<int, int>& el_to, bool &b_found, bool b_all) {
	if (!b_all)
		if (b_found)
			return;

	if (length == 0) {
		if (myrikudo.are_neighbours(used_elements.back(), el_to)
			//&& test_forced_connectivity(myrikudo, el_from, el_to, used_elements)
			) {
			// try to use found path
			int val1 = myrikudo.get_elem(el_from);
			int val2 = myrikudo.get_elem(el_to);
			int incr = val1 <= val2 ? 1 : -1;
			int curr_value = val1<=val2? val1+1: val2-1;
			bool bdown = val2 < val1 ? true : false;

			int idx = 0;
			for (int bb : used_blocks) {
				myrikudo.use_block(bb, used_connections[idx], curr_value, bdown);
				if (bdown)
					curr_value -= myrikudo.fillable_blocks[bb].length;
				else
					curr_value += myrikudo.fillable_blocks[bb].length;
				idx++;
			}

			//myrikudo.disp_crude();
			if (myrikudo.can_be_attached_all() && myrikudo.test_block_components()) {
				b_found = true;
			}

			idx = 0;
			curr_value = val1 <= val2 ? val1 + 1 : val2 - 1;
			for (auto& bb : used_blocks) {
				myrikudo.unuse_block(bb, used_connections[idx], curr_value, bdown);
				if (bdown)
					curr_value -= myrikudo.fillable_blocks[bb].length;
				else
					curr_value += myrikudo.fillable_blocks[bb].length;
				idx++;
			}

			//myrikudo.disp_crude();

			// if still attached
			// b_found = true


			//b_found = true;
			// for DEBUG

			/*std::cerr << el_from;
			for (auto& e : used_elements)
				std::cerr << " -> " << e;
			std::cerr << " -> " << el_to << '\n';
			number_of_solutions++;*/
		}
	}
	else {
		std::pair<int, int> el_start;

		if (used_elements.empty())
			el_start = el_from;
		else
			el_start = used_elements.back();

		for (int b_idx : myrikudo.get_unfilled_neighbour_blocks_idxs(el_start)) {
			if (b_all || !b_found) {
				int blen = myrikudo.fillable_blocks[b_idx].length;

				if (length >= blen && std::find(used_blocks.begin(), used_blocks.end(), b_idx) == used_blocks.end()) {

					// use block

					if (myrikudo.are_neighbours(el_start, myrikudo.fillable_blocks[b_idx].end1)) {
						// connect it via end1
						used_blocks.push_back(b_idx/*{ b_idx, 1 }*/);
						used_connections.push_back(1);
						for (int i = 0; i < myrikudo.fillable_blocks[b_idx].length; i++)
							used_elements.push_back(myrikudo.fillable_blocks[b_idx].tiles[i]);

						exists_path_via_unused_blocks_of_length_recOLD(length - blen, used_blocks, used_connections, 
							used_elements, myrikudo, el_from, el_to, b_found, b_all);

						// clear connection
						for (int i = 0; i < myrikudo.fillable_blocks[b_idx].length; i++)
							used_elements.pop_back();
						used_connections.pop_back();
						used_blocks.pop_back();


					}

					if (blen > 1 && myrikudo.are_neighbours(el_start, myrikudo.fillable_blocks[b_idx].end2)) {
						// connect it via end2

						used_blocks.push_back(b_idx/*{ b_idx, 0 }*/);
						used_connections.push_back(0);
						for (int i = myrikudo.fillable_blocks[b_idx].length - 1; i >= 0; i--)
							used_elements.push_back(myrikudo.fillable_blocks[b_idx].tiles[i]);

						exists_path_via_unused_blocks_of_length_recOLD(length - blen, used_blocks, used_connections, 
							used_elements, myrikudo, el_from, el_to, b_found, b_all);

						// clear connection
						for (int i = 0; i < myrikudo.fillable_blocks[b_idx].length; i++)
							used_elements.pop_back();
						used_connections.pop_back();
						used_blocks.pop_back();
					}
				}
			}
		}
	}
}

bool exists_path_via_unused_blocks_of_lengthOLD(rikudo& myrikudo, const std::pair<int, int>& el_from, const std::pair<int, int>& el_to, int length) {
	bool b_path_found = false;
	//std::vector<std::pair<int, int>> v_bs;
	std::vector<int> v_bs;
	std::vector<int> v_bc;
	std::vector<std::pair<int, int>> v_es;

	exists_path_via_unused_blocks_of_length_recOLD(length, v_bs, v_bc, v_es, myrikudo, el_from, el_to, b_path_found, false);

	return b_path_found;
}

// used elements - all elements of path
void exists_path_via_unused_blocks_of_length_rec(int length, std::vector<int>& used_blocks, std::vector<int>& used_connections, int start_value, int end_value, rikudo& myrikudo, const std::pair<int, int>& el_from, const std::pair<int, int>& el_to, bool& b_found) {
	if (b_found)
		return;

	if (length == 0) {
		std::pair<int, int> last_elem = (used_connections.back() == 1) ? myrikudo.fillable_blocks[used_blocks.back()].end2 : myrikudo.fillable_blocks[used_blocks.back()].end1;
		//myrikudo.disp_crude();
		if (myrikudo.are_neighbours(last_elem, el_to)
			//&& test_forced_connectivity(myrikudo, el_from, el_to, used_elements)
			) {
#if 0
			// try to use found path
			int val1 = start_value;
			int val2 = end_value;
			int incr = val1 <= val2 ? 1 : -1;
			int curr_value = val1 <= val2 ? val1 + 1 : val2 - 1;
			bool bdown = val2 < val1 ? true : false;

			int idx = 0;
			for (int bb : used_blocks) {
				myrikudo.use_block(bb, used_connections[idx], curr_value, bdown);
				if (bdown)
					curr_value -= myrikudo.fillable_blocks[bb].length;
				else
					curr_value += myrikudo.fillable_blocks[bb].length;
				idx++;
			}
#endif

			//myrikudo.disp_crude();
			if (myrikudo.can_be_attached_all() && myrikudo.test_block_components()) {
				b_found = true;
			}
#if 0
			idx = 0;
			curr_value = val1 <= val2 ? val1 + 1 : val2 - 1;
			for (auto& bb : used_blocks) {
				myrikudo.unuse_block(bb, used_connections[idx], curr_value, bdown);
				if (bdown)
					curr_value -= myrikudo.fillable_blocks[bb].length;
				else
					curr_value += myrikudo.fillable_blocks[bb].length;
				idx++;
			}
#endif
			//myrikudo.disp_crude();

			// if still attached
			// b_found = true


			//b_found = true;
			// for DEBUG

			/*std::cerr << el_from;
			for (auto& e : used_elements)
				std::cerr << " -> " << e;
			std::cerr << " -> " << el_to << '\n';
			number_of_solutions++;*/
		}
	}
	else {
		std::pair<int, int> el_start;

		if (used_blocks.empty())
			el_start = el_from;
		else
			el_start = (used_connections.back() == 1) ? myrikudo.fillable_blocks[used_blocks.back()].end2 : myrikudo.fillable_blocks[used_blocks.back()].end1;
		
		int val1 = myrikudo.get_elem(el_from);
		int val2 = myrikudo.get_elem(el_to);
		int new_val = (val1 <= val2) ? val1 + 1 : val1 - 1;

		for (int b_idx : myrikudo.get_unfilled_neighbour_blocks_idxs(el_start)) {
			if (!b_found) {
				int blen = myrikudo.fillable_blocks[b_idx].length;

				if (length >= blen && std::find(used_blocks.begin(), used_blocks.end(), b_idx) == used_blocks.end()) {

					// use block

					if (myrikudo.are_neighbours(el_start, myrikudo.fillable_blocks[b_idx].end1)) {
						// connect it via end1
						used_blocks.push_back(b_idx/*{ b_idx, 1 }*/);
						used_connections.push_back(1);
						
						

						myrikudo.use_block(b_idx, true, new_val, val1 > val2);

						/*for (int i = 0; i < myrikudo.fillable_blocks[b_idx].length; i++)
							used_elements.push_back(myrikudo.fillable_blocks[b_idx].tiles[i]);*/

						exists_path_via_unused_blocks_of_length_rec(length - blen, used_blocks, used_connections/*,
							used_elements*/,start_value, end_value, myrikudo, myrikudo.fillable_blocks[b_idx].end2, el_to, b_found);

						// clear connection
						/*for (int i = 0; i < myrikudo.fillable_blocks[b_idx].length; i++)
							used_elements.pop_back();*/
						myrikudo.unuse_block(b_idx, true, new_val, val1 > val2);
						used_connections.pop_back();
						used_blocks.pop_back();


					}

					if (blen > 1 && myrikudo.are_neighbours(el_start, myrikudo.fillable_blocks[b_idx].end2)) {
						// connect it via end2

						used_blocks.push_back(b_idx/*{ b_idx, 0 }*/);
						used_connections.push_back(0);
						/*for (int i = myrikudo.fillable_blocks[b_idx].length - 1; i >= 0; i--)
							used_elements.push_back(myrikudo.fillable_blocks[b_idx].tiles[i]);*/

						myrikudo.use_block(b_idx, false, new_val, val1 > val2);

						exists_path_via_unused_blocks_of_length_rec(length - blen, used_blocks, used_connections/*,
							used_elements*/, start_value, end_value, myrikudo, myrikudo.fillable_blocks[b_idx].end1, el_to, b_found);

						// clear connection
						myrikudo.unuse_block(b_idx, false, new_val, val1 > val2);
						/*for (int i = 0; i < myrikudo.fillable_blocks[b_idx].length; i++)
							used_elements.pop_back();*/
						used_connections.pop_back();
						used_blocks.pop_back();
					}
				}
			}
		}
	}
}

bool exists_path_via_unused_blocks_of_length(rikudo& myrikudo, const std::pair<int, int>& el_from, const std::pair<int, int>& el_to, int length) {
	bool b_path_found = false;
	std::vector<int> v_bs;
	std::vector<int> v_bc;

	exists_path_via_unused_blocks_of_length_rec(length, v_bs, v_bc, myrikudo.get_elem(el_from), myrikudo.get_elem(el_to), myrikudo, el_from, el_to, b_path_found);

	return b_path_found;
}


void count_paths_via_unused_blocks_of_length_rec(int length, std::vector<int>& used_blocks, std::vector<int>& used_connections, std::vector<std::pair<int, int>>& used_elements, rikudo& myrikudo, const std::pair<int, int>& el_from, const std::pair<int, int>& el_to,int& path_count) {

	if (length == 0) {
		if (myrikudo.are_neighbours(used_elements.back(), el_to)
			//&& test_forced_connectivity(myrikudo, el_from, el_to, used_elements)
			) {
			// try to use found path
			int val1 = myrikudo.get_elem(el_from);
			int val2 = myrikudo.get_elem(el_to);
			int incr = val1 <= val2 ? 1 : -1;
			int curr_value = val1 <= val2 ? val1 + 1 : val2 - 1;
			bool bdown = val2 < val1 ? true : false;

			int idx = 0;
			for (int bb : used_blocks) {
				myrikudo.use_block(bb, used_connections[idx], curr_value, bdown);
				if (bdown)
					curr_value -= myrikudo.fillable_blocks[bb].length;
				else
					curr_value += myrikudo.fillable_blocks[bb].length;
				idx++;
			}

			//myrikudo.disp_crude();
			if (myrikudo.can_be_attached_all() && myrikudo.test_block_components()) {
				path_count++;
			}

			idx = 0;
			curr_value = val1 <= val2 ? val1 + 1 : val2 - 1;
			for (auto& bb : used_blocks) {
				myrikudo.unuse_block(bb, used_connections[idx], curr_value, bdown);
				if (bdown)
					curr_value -= myrikudo.fillable_blocks[bb].length;
				else
					curr_value += myrikudo.fillable_blocks[bb].length;
				idx++;
			}

			//myrikudo.disp_crude();

			// if still attached
			// b_found = true


			//b_found = true;
			// for DEBUG

			/*std::cerr << el_from;
			for (auto& e : used_elements)
				std::cerr << " -> " << e;
			std::cerr << " -> " << el_to << '\n';
			number_of_solutions++;*/
		}
	}
	else {
		std::pair<int, int> el_start;

		if (used_elements.empty())
			el_start = el_from;
		else
			el_start = used_elements.back();

		for (int b_idx : myrikudo.get_unfilled_neighbour_blocks_idxs(el_start)) {
			int blen = myrikudo.fillable_blocks[b_idx].length;

			if (length >= blen && std::find(used_blocks.begin(), used_blocks.end(), b_idx) == used_blocks.end()) {

				// use block

				if (myrikudo.are_neighbours(el_start, myrikudo.fillable_blocks[b_idx].end1)) {
					// connect it via end1
					used_blocks.push_back(b_idx/*{ b_idx, 1 }*/);
					used_connections.push_back(1);
					for (int i = 0; i < myrikudo.fillable_blocks[b_idx].length; i++)
						used_elements.push_back(myrikudo.fillable_blocks[b_idx].tiles[i]);

					count_paths_via_unused_blocks_of_length_rec(length - blen, used_blocks, used_connections,
						used_elements, myrikudo, el_from, el_to, path_count);

					// clear connection
					for (int i = 0; i < myrikudo.fillable_blocks[b_idx].length; i++)
						used_elements.pop_back();
					used_connections.pop_back();
					used_blocks.pop_back();


				}

				if (blen > 1 && myrikudo.are_neighbours(el_start, myrikudo.fillable_blocks[b_idx].end2)) {
					// connect it via end2

					used_blocks.push_back(b_idx/*{ b_idx, 0 }*/);
					used_connections.push_back(0);
					for (int i = myrikudo.fillable_blocks[b_idx].length - 1; i >= 0; i--)
						used_elements.push_back(myrikudo.fillable_blocks[b_idx].tiles[i]);

					count_paths_via_unused_blocks_of_length_rec(length - blen, used_blocks, used_connections,
						used_elements, myrikudo, el_from, el_to, path_count);

					// clear connection
					for (int i = 0; i < myrikudo.fillable_blocks[b_idx].length; i++)
						used_elements.pop_back();
					used_connections.pop_back();
					used_blocks.pop_back();
				}
			}			
		}
	}
}



int count_paths_via_unused_blocks_of_length(rikudo& myrikudo, const std::pair<int, int>& el_from, const std::pair<int, int>& el_to, int length) {
	std::vector<int> v_bs;
	std::vector<int> v_bc;
	std::vector<std::pair<int, int>> v_es;

	int path_cnt = 0;

	count_paths_via_unused_blocks_of_length_rec(length, v_bs, v_bc, v_es, myrikudo, el_from, el_to, path_cnt);

	return path_cnt;
}

void compute_paths_via_unused_blocks_of_length_rec(int length, std::vector<int>& used_blocks, std::vector<int>& used_connections, int orig_from, int orig_to, /*, std::vector<std::pair<int, int>>& used_elements*/ rikudo& myrikudo, const std::pair<int, int>& el_from, const std::pair<int, int>& el_to, std::vector<std::vector<std::pair<int, int>>> &paths) {

	if (length == 0) {
		std::pair<int, int> last_elem = (used_connections.back() == 1) ? myrikudo.fillable_blocks[used_blocks.back()].end2 : myrikudo.fillable_blocks[used_blocks.back()].end1;
		
		//// DEBUG
		//// print found path 
		//auto it_b = used_blocks.begin();
		//auto it_c = used_connections.begin();
		//std::cerr << "Found path:";
		//while (it_b != used_blocks.end()) {
		//	std::cerr << " " << std::pair<int, int>(*it_b, *it_c);
		//	++it_b;
		//	++it_c;
		//}
		//std::cerr << '\n';


		if (myrikudo.are_neighbours(last_elem, el_to)
			//&& test_forced_connectivity(myrikudo, el_from, el_to, used_elements)
			) {
			// try to use found path
			int val1 = orig_from;/*myrikudo.get_elem(el_from);*/
			int val2 = orig_to;/* myrikudo.get_elem(el_to);*/
			int incr = val1 <= val2 ? 1 : -1;
			int curr_value = val1 <= val2 ? val1 + 1 : val2 - 1;
			bool bdown = val2 < val1 ? true : false;

			int idx = 0;
			for (int bb : used_blocks) {
				myrikudo.use_block(bb, used_connections[idx], curr_value, bdown);
				if (bdown)
					curr_value -= myrikudo.fillable_blocks[bb].length;
				else
					curr_value += myrikudo.fillable_blocks[bb].length;
				idx++;
			}

			//myrikudo.disp_crude();
			bool b_at = myrikudo.can_be_attached_all();
			bool b_comp = myrikudo.test_block_components();
			if (myrikudo.can_be_attached_all() && myrikudo.test_block_components()) {
				std::vector<std::pair<int, int>> found_path;
				auto it_b = used_blocks.begin();
				auto it_c = used_connections.begin();
				while (it_b != used_blocks.end())
				{
					found_path.push_back({ *it_b, *it_c });
					++it_b;
					++it_c;
				}
				paths.push_back(found_path);
			}

			idx = 0;
			curr_value = val1 <= val2 ? val1 + 1 : val2 - 1;
			for (auto& bb : used_blocks) {
				myrikudo.unuse_block(bb, used_connections[idx], curr_value, bdown);
				if (bdown)
					curr_value -= myrikudo.fillable_blocks[bb].length;
				else
					curr_value += myrikudo.fillable_blocks[bb].length;
				idx++;
			}

			//myrikudo.disp_crude();

			// if still attached
			// b_found = true


			//b_found = true;
			// for DEBUG

			/*std::cerr << el_from;
			for (auto& e : used_elements)
				std::cerr << " -> " << e;
			std::cerr << " -> " << el_to << '\n';
			number_of_solutions++;*/
		}
	}
	else {
		std::pair<int, int> el_start;

		if (used_blocks.empty())
			el_start = el_from;
		else 
			el_start = (used_connections.back() == 1) ? myrikudo.fillable_blocks[used_blocks.back()].end2 : myrikudo.fillable_blocks[used_blocks.back()].end1;
		
		auto tmp = myrikudo.get_unfilled_neighbour_blocks_idxs(el_start);
		for (int b_idx : myrikudo.get_unfilled_neighbour_blocks_idxs(el_start)) {
			int blen = myrikudo.fillable_blocks[b_idx].length;

			if (length >= blen && std::find(used_blocks.begin(), used_blocks.end(), b_idx) == used_blocks.end()) {

				// use block

				if (myrikudo.are_neighbours(el_start, myrikudo.fillable_blocks[b_idx].end1)) {
					// connect it via end1
					used_blocks.push_back(b_idx/*{ b_idx, 1 }*/);
					used_connections.push_back(1);
					/*for (int i = 0; i < myrikudo.fillable_blocks[b_idx].length; i++)
						used_elements.push_back(myrikudo.fillable_blocks[b_idx].tiles[i]);*/
					//std::pair<int, int> new_el_from = myrikudo.fillable_blocks[b_idx].end2;
					compute_paths_via_unused_blocks_of_length_rec(length - blen, used_blocks, used_connections, orig_from, orig_to, myrikudo, el_start, el_to, paths);

					// clear connection
					/*for (int i = 0; i < myrikudo.fillable_blocks[b_idx].length; i++)
						used_elements.pop_back();*/
					used_connections.pop_back();
					used_blocks.pop_back();


				}

				if (blen > 1 && myrikudo.are_neighbours(el_start, myrikudo.fillable_blocks[b_idx].end2)) {
					// connect it via end2

					used_blocks.push_back(b_idx/*{ b_idx, 0 }*/);
					used_connections.push_back(0);
					/*for (int i = myrikudo.fillable_blocks[b_idx].length - 1; i >= 0; i--)
						used_elements.push_back(myrikudo.fillable_blocks[b_idx].tiles[i]);*/

					//std::pair<int, int> new_el_from = myrikudo.fillable_blocks[b_idx].end1;
					compute_paths_via_unused_blocks_of_length_rec(length - blen, used_blocks, used_connections, orig_from, orig_to, myrikudo, el_start, el_to, paths);

					// clear connection
					/*for (int i = 0; i < myrikudo.fillable_blocks[b_idx].length; i++)
						used_elements.pop_back();*/
					used_connections.pop_back();
					used_blocks.pop_back();
				}
			}
		}
	}
}



std::vector<std::vector<std::pair<int, int>>> compute_paths_via_unused_blocks_of_length(rikudo& myrikudo, const std::pair<int, int>& el_from, const std::pair<int, int>& el_to, int length) {
	std::vector<int> v_bs;
	std::vector<int> v_bc;
	std::vector<std::vector<std::pair<int, int>>> paths;

	int path_cnt = 0;
	int orig_from = myrikudo.get_elem(el_from);
	int orig_to = myrikudo.get_elem(el_to);

	compute_paths_via_unused_blocks_of_length_rec(length, v_bs, v_bc, orig_from, orig_to, myrikudo, el_from, el_to, paths);

	return paths;
}


bool exists_path(rikudo& myrikudo, interval v) {
	// assumes that v.start and v.end are filled
	// tries to find a path via unfilled elements
	// from v.start to v.end
	// TODO
	if (v.start == v.end)
		return true;

	auto el_s = myrikudo.get_addr(v.start);
	auto el_e = myrikudo.get_addr(v.end);

//	if (myrikudo.are_neighbours(el_s, el_e))
//		return true;

	std::set<std::pair<int, int>> neighbours;
	neighbours.insert(el_s);


	//auto neigb = myrikudo.get_unfilled_neighbours(el_s);

	//std::set<std::pair<int, int>> neighbours;

	//for (auto& e : neigb)
	//	neighbours.insert(e.first);


	bool b_new = true; // (neighbours.size() > 0);
	
	std::set<std::pair<int, int>> expanded;

	while (b_new && !exists_neighbour(myrikudo, neighbours, el_e)) {
		b_new = false;
		
		for (auto& e : neighbours) {
			if (expanded.find(e) == expanded.end()) {
				for (auto& eb : myrikudo.get_unfilled_neighbours(e))
				{
					if (neighbours.find(eb.first) == neighbours.end()) {
						neighbours.insert(eb.first);
						b_new = true;

					}
				}
				expanded.insert(e);
			}
		}
	}

	return exists_neighbour(myrikudo, neighbours, el_e);
}

bool test_forced_connectivity(rikudo &myrikudo, const std::pair<int, int> &filled_start, const std::pair<int, int>& filled_end, const std::vector<std::pair<int,int>> &path_of_unfilled) {
	{
		int path_unfilled_size = (int)path_of_unfilled.size();

		if (path_unfilled_size > 0) {

			std::pair<int, int> e_b{ -1,-1 }, e_m{ -1,-1 }, e_e{ -1,-1 };
			e_b = filled_start;
			int path_unfilled_idx = 0;
			
			e_m = path_of_unfilled[path_unfilled_idx];
			path_unfilled_idx++;
			while (path_unfilled_idx <= path_unfilled_size) {
				if (path_unfilled_idx < path_unfilled_size)
					e_e = path_of_unfilled[path_unfilled_idx];
				else
					e_e = filled_end;

				int foc = myrikudo.count_forced_orders(e_m);

				if (foc == 1) {
					int fo_m = myrikudo.get_forced_orders(e_m);

					if (fo_m & myrikudo.UR) {
						if (!myrikudo.are_neighbours_from_UR(e_m, e_b) && !myrikudo.are_neighbours_from_UR(e_m, e_e)) {
							return false;
						}
					}

					if (fo_m & myrikudo._R) {
						if (!myrikudo.are_neighbours_from__R(e_m, e_b) && !myrikudo.are_neighbours_from__R(e_m, e_e))
							return false;
					}

					if (fo_m & myrikudo.DR) {
						if (!myrikudo.are_neighbours_from_DR(e_m, e_b) && !myrikudo.are_neighbours_from_DR(e_m, e_e))
							return false;
					}

					if (fo_m & myrikudo.DL) {
						if (!myrikudo.are_neighbours_from_DL(e_m, e_b) && !myrikudo.are_neighbours_from_DL(e_m, e_e))
							return false;
					}

					if (fo_m & myrikudo._L) {
						if (!myrikudo.are_neighbours_from__L(e_m, e_b) && !myrikudo.are_neighbours_from__L(e_m, e_e))
							return false;
					}

					if (fo_m & myrikudo.UL) {
						if (!myrikudo.are_neighbours_from_UL(e_m, e_b) && !myrikudo.are_neighbours_from_UL(e_m, e_e))
							return false;
					}
				}
				else if (foc == 2) {
					if (myrikudo.count_forced_orders(e_b) == 0 || myrikudo.count_forced_orders(e_e) == 0)
						return false;

					int fo_b = myrikudo.get_forced_orders(e_b);
					int fo_m = myrikudo.get_forced_orders(e_m);
					int fo_e = myrikudo.get_forced_orders(e_e);

					if (myrikudo.are_neighbours_from_UR(e_b, e_m) && !myrikudo.is_forced_from_DL(e_m))
						return false;
					if (myrikudo.are_neighbours_from__R(e_b, e_m) && !myrikudo.is_forced_from__L(e_m))
						return false;
					if (myrikudo.are_neighbours_from_DR(e_b, e_m) && !myrikudo.is_forced_from_UL(e_m))
						return false;
					if (myrikudo.are_neighbours_from_DL(e_b, e_m) && !myrikudo.is_forced_from_UR(e_m))
						return false;
					if (myrikudo.are_neighbours_from__L(e_b, e_m) && !myrikudo.is_forced_from__R(e_m))
						return false;
					if (myrikudo.are_neighbours_from_UL(e_b, e_m) && !myrikudo.is_forced_from_DR(e_m))
						return false;

					if (myrikudo.are_neighbours_from_UR(e_e, e_m) && !myrikudo.is_forced_from_DL(e_m))
						return false;
					if (myrikudo.are_neighbours_from__R(e_e, e_m) && !myrikudo.is_forced_from__L(e_m))
						return false;
					if (myrikudo.are_neighbours_from_DR(e_e, e_m) && !myrikudo.is_forced_from_UL(e_m))
						return false;
					if (myrikudo.are_neighbours_from_DL(e_e, e_m) && !myrikudo.is_forced_from_UR(e_m))
						return false;
					if (myrikudo.are_neighbours_from__L(e_e, e_m) && !myrikudo.is_forced_from__R(e_m))
						return false;
					if (myrikudo.are_neighbours_from_UL(e_e, e_m) && !myrikudo.is_forced_from_DR(e_m))
						return false;
				}

				path_unfilled_idx++;
				e_b = e_m;
				e_m = e_e;
			}

		}
	}

	return true;
}







// all elements between start and end in v must be a filled value
bool prolong_path(rikudo& myrikudo, interval v) {
	bool changed = false;
	if (v_min > v.start) {
		v_min = v.start;
		changed = true;
	}
	if (v_max < v.end) {
		v_max = v.end;
		changed = true;
	}
	if (changed || (v_min == v.start && v_max == v.end)) {
		std::cerr << v.start << ", " << v.end << '\n';
		myrikudo.disp_crude();
	}



	/*if (v.start <=15 && v.end >=75)*/
		//std::cerr << v.start << ", " << v.end << '\n';
	/*if (v.end >= 75)
		std::cout << v.start << ", " << v.end << '\n';*/
		/*for (int i = (int)myrikudo.shape.row_sizes.size() - 1; i >= 0; i--) {
			for (int j = 0; j < myrikudo.shape.row_sizes[i]; j++) {
				int val = myrikudo.get_elem({ i,j });
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
		}*/

	for (int i = v.start; i <= v.end; i++) {
		if (!myrikudo.is_already_filled(i)) {
			std::cerr << "Error: Element " << i << " is unfilled.\n";
			return false;
		}
	}

	// check correctness of partial solution
	// v_i v_{i+1} are connected
	// if v_i is forced 
	// forced_cnt==1: v_{i-1} ... v_i or v_i ... v_{i+1} is connected via forced direction
	// forced_cnt==2: v_{i-1} ... v_i and v_i ... v_{i+1} are connected via forced directions
	
	
    // tests connectivity	
	if (v.end - v.start > 0) {
		
		std::pair<int, int> e_1{ -1,-1 }, e_2{ -1,-1 };
		e_1 = myrikudo.get_addr(v.start);
		int idx = v.start + 1;

		while (idx <= v.end) {
			e_2 = myrikudo.get_addr(idx);

			if (!myrikudo.are_neighbours(e_1, e_2)) {
				std::cerr << "(" << e_1.first << ", " << e_1.second << ")[" << myrikudo.get_elem(e_1) << "] and (" << e_2.first << ", " << e_2.second << ")[" << myrikudo.get_elem(e_2) << "] are not connected.";
				return false;
			}

			idx++;
			e_1 = e_2;
		}
	}
	


	// test forced connectivity
	if (v.end - v.start > 1) {
		std::pair<int, int> e_b{ -1,-1 }, e_m{ -1,-1 }, e_e{ -1,-1 };
		e_b = myrikudo.get_addr(v.start);
		e_m = myrikudo.get_addr(v.start+1);
		int idx = v.start + 2;

		while (idx <= v.end) {
			e_e = myrikudo.get_addr(idx);

			int foc = myrikudo.count_forced_orders(e_m);

			if (foc == 1) {
				int fo_m = myrikudo.get_forced_orders(e_m);
				
				if (fo_m & myrikudo.UR) {
					if (!myrikudo.are_neighbours_from_UR(e_m, e_b) && !myrikudo.are_neighbours_from_UR(e_m, e_e)) {
						return false;
					}
				}

				if (fo_m & myrikudo._R) {
					if (!myrikudo.are_neighbours_from__R(e_m, e_b) && !myrikudo.are_neighbours_from__R(e_m, e_e))
						return false;
				}

				if (fo_m & myrikudo.DR) {
					if (!myrikudo.are_neighbours_from_DR(e_m, e_b) && !myrikudo.are_neighbours_from_DR(e_m, e_e))
						return false;
				}

				if (fo_m & myrikudo.DL) {
					if (!myrikudo.are_neighbours_from_DL(e_m, e_b) && !myrikudo.are_neighbours_from_DL(e_m, e_e))
						return false;
				}
				
				if (fo_m & myrikudo._L) {
					if (!myrikudo.are_neighbours_from__L(e_m, e_b) && !myrikudo.are_neighbours_from__L(e_m, e_e))
						return false;
				}

				if (fo_m & myrikudo.UL) {
					if (!myrikudo.are_neighbours_from_UL(e_m, e_b) && !myrikudo.are_neighbours_from_UL(e_m, e_e))
						return false;
				}
			}
			else if (foc == 2) {
				if (myrikudo.count_forced_orders(e_b) == 0 || myrikudo.count_forced_orders(e_e) == 0)
					return false;

				int fo_b  = myrikudo.get_forced_orders(e_b);
				int fo_m = myrikudo.get_forced_orders(e_m);
				int fo_e = myrikudo.get_forced_orders(e_e);

				if (myrikudo.are_neighbours_from_UR(e_b, e_m) && !myrikudo.is_forced_from_DL(e_m))
					return false;
				if (myrikudo.are_neighbours_from__R(e_b, e_m) && !myrikudo.is_forced_from__L(e_m))
					return false;
				if (myrikudo.are_neighbours_from_DR(e_b, e_m) && !myrikudo.is_forced_from_UL(e_m))
					return false;
				if (myrikudo.are_neighbours_from_DL(e_b, e_m) && !myrikudo.is_forced_from_UR(e_m))
					return false;
				if (myrikudo.are_neighbours_from__L(e_b, e_m) && !myrikudo.is_forced_from__R(e_m))
					return false;
				if (myrikudo.are_neighbours_from_UL(e_b, e_m) && !myrikudo.is_forced_from_DR(e_m))
					return false;

				if (myrikudo.are_neighbours_from_UR(e_e, e_m) && !myrikudo.is_forced_from_DL(e_m))
					return false;
				if (myrikudo.are_neighbours_from__R(e_e, e_m) && !myrikudo.is_forced_from__L(e_m))
					return false;
				if (myrikudo.are_neighbours_from_DR(e_e, e_m) && !myrikudo.is_forced_from_UL(e_m))
					return false;
				if (myrikudo.are_neighbours_from_DL(e_e, e_m) && !myrikudo.is_forced_from_UR(e_m))
					return false;
				if (myrikudo.are_neighbours_from__L(e_e, e_m) && !myrikudo.is_forced_from__R(e_m))
					return false;
				if (myrikudo.are_neighbours_from_UL(e_e, e_m) && !myrikudo.is_forced_from_DR(e_m))
					return false;
			}


			idx++;
			e_b = e_m;
			e_m = e_e;
		}

	}


	
	if (v.start == 1 && v.end == myrikudo.max_elem_value) {
		if (true || test_solution(myrikudo)) {
			// we have solution 
			// print TODO 
			std::cout << "Solution.\n";

			for (auto& e : myrikudo.filled_values_inv) {
				std::cout << "(" << e.second.first << "," << e.second.second << ") -> " << e.first << ", ";
			}
			std::cout << "\n";

			for (int i = (int)myrikudo.shape.row_sizes.size() - 1; i >= 0; i--) {
				for (int j = 0; j < myrikudo.shape.row_sizes[i]; j++) {
					int val = myrikudo.get_elem({ i,j });
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

		return true;
	}


#if 0
	{
		/*const*/
		//int first_forced_value;
		//int last_forced_value;

		//find_first_unfilled
		int sidx = myrikudo.first_forced_value;
		do {
			int first_unfilled_value = -1;
			for (int i = sidx; i <= myrikudo.last_forced_value;i++)
				if (!myrikudo.is_already_filled(i)) {
					first_unfilled_value = i;
					break;
				}

			if (first_unfilled_value != -1) {
				int interval_start;
				if (first_unfilled_value < myrikudo.first_forced_value)
					interval_start = myrikudo.first_forced_value;
				else
					interval_start = first_unfilled_value - 1;

				if (!myrikudo.is_already_filled(interval_start + 1)) {
					int idx = interval_start + 1;
					while (idx <= myrikudo.last_forced_value && !myrikudo.is_already_filled(idx)) {
						idx++;
					}
					int interval_end;
					if (idx <= myrikudo.last_forced_value)
						interval_end = idx;
					else
						interval_end = -1;

					if (interval_end != -1) {
						//std::cerr << "Checking the interval [" << interval_start << "," << interval_end << "]:\n";
						b_path_found = false;
						std::vector<std::pair<int, int>> vv;
						exists_path_of_length(interval_end - interval_start, vv, myrikudo, myrikudo.get_addr(interval_start), myrikudo.get_addr(interval_end));
						if (false && !b_path_found)
							return false;

						sidx = interval_end;
					}
					else
						sidx = myrikudo.last_forced_value;
				}

			}
			else
				sidx++;
			
		} while (sidx <= myrikudo.last_forced_value);
	}

#endif

	if (v.start - 1 >= 1 && !myrikudo.is_already_filled(v.start - 1)) {

		if (v.end + 1 <= myrikudo.max_elem_value && !myrikudo.is_already_filled(v.end + 1)) {

			auto res_neigh_start = myrikudo.get_unfilled_neighbours(myrikudo.get_addr(v.start));
			// unfilled value, but no unfilled tile
			if (res_neigh_start.size() == 0)
				return false;
			auto res_neigh_end = myrikudo.get_unfilled_neighbours(myrikudo.get_addr(v.end));			
			// unfilled value, but no unfilled tile
			if (res_neigh_end.size() == 0)
				return false;

			// can be prolonged down?

			std::pair<int, int> el_vs = myrikudo.get_addr(v.start);
			int fo_vs = myrikudo.get_forced_orders(el_vs);

			if (false && fo_vs) {
				// has some forced orders
				
				// if the forced order is in the direction of already filled element, 
				// this element needs to be equal to v.start+1

				if ((fo_vs & rikudo::hex_dirs::UR) &&
					myrikudo.exists_neighbour_from_UR(el_vs) &&
					myrikudo.is_filled_neighbour_from_UR(el_vs)) {
					auto UR_neigh = myrikudo.shape.get_UR_tile(el_vs);
					if (myrikudo.get_elem(UR_neigh) != v.start + 1)
						return false;
				}

				if ((fo_vs & rikudo::hex_dirs::_R) &&
					myrikudo.exists_neighbour_from__R(el_vs) &&
					myrikudo.is_filled_neighbour_from__R(el_vs)) {
					auto _R_neigh = myrikudo.shape.get__R_tile(el_vs);
					if (myrikudo.get_elem(_R_neigh) != v.start + 1)
						return false;
				}

				if ((fo_vs & rikudo::hex_dirs::DR) &&
					myrikudo.exists_neighbour_from_DR(el_vs) &&
					myrikudo.is_filled_neighbour_from_DR(el_vs)) {
					auto DR_neigh = myrikudo.shape.get_DR_tile(el_vs);
					if (myrikudo.get_elem(DR_neigh) != v.start + 1)
						return false;
				}

				if ((fo_vs & rikudo::hex_dirs::DL) &&
					myrikudo.exists_neighbour_from_DL(el_vs) &&
					myrikudo.is_filled_neighbour_from_DL(el_vs)) {
					auto DL_neigh = myrikudo.shape.get_DL_tile(el_vs);
					if (myrikudo.get_elem(DL_neigh) != v.start + 1)
						return false;
				}

				if ((fo_vs & rikudo::hex_dirs::_L) &&
					myrikudo.exists_neighbour_from__L(el_vs) &&
					myrikudo.is_filled_neighbour_from__L(el_vs)) {
					auto _L_neigh = myrikudo.shape.get__L_tile(el_vs);
					if (myrikudo.get_elem(_L_neigh) != v.start + 1)
						return false;
				}

				if ((fo_vs & rikudo::hex_dirs::UL) &&
					myrikudo.exists_neighbour_from_UL(el_vs) &&
					myrikudo.is_filled_neighbour_from_UL(el_vs)) {
					auto UL_neigh = myrikudo.shape.get_UL_tile(el_vs);
					if (myrikudo.get_elem(UL_neigh) != v.start + 1)
						return false;
				}

				/*if ((fo_vs & rikudo::hex_dirs::UR) &&
					myrikudo.exists_neighbour_from_UR(el_vs) &&
					!myrikudo.is_filled_neighbour_from_UR(el_vs)
					)*/

				// forced order is in the direction of unfilled element
				//    a) v.start+1 is already filled / does not exists
				//       => if there are more than 1 forced directions in unfilled error
				//          else fill v.start-1 to this particular unfilled element
				//    b) v.start+1 is unfilled (and it exists)
				//       => v.start - 1 can be filled to both unfilled elements in forced directions
				
				bool has_forced_start = false;
				for (auto& e_st : res_neigh_start) {
					if (e_st.second)
						has_forced_start = true;
				}

				if (has_forced_start) {
					if (v.start + 1 > myrikudo.max_elem_value || myrikudo.is_already_filled(v.start + 1)) {
						int foc = myrikudo.count_forced_orders(el_vs);
						if (foc > 1)
							return false;
						else {
							// select single element from res_neigh_start
							for (auto it = res_neigh_start.begin(); it != res_neigh_start.end();)
							{
								if (!it->second)
									it = res_neigh_start.erase(it);
								else
									++it;
							}
						}
					}
					else {
						// from res_neigh_start selects elements with forced directions 
						for (auto it = res_neigh_start.begin(); it != res_neigh_start.end();)
						{
							if (!it->second)
								it = res_neigh_start.erase(it);
							else
								++it;
						}
					}
		
				}

			}

			// can be prolonged up?

			std::pair<int, int> el_ve = myrikudo.get_addr(v.end);
			int fo_ve = myrikudo.get_forced_orders(el_ve);

			if (false && fo_ve) {
				// has some forced orders

				// if the forced order is in the direction of already filled element, 
				// this element needs to be equal to v.end - 1

				if ((fo_ve & rikudo::hex_dirs::UR) &&
					myrikudo.exists_neighbour_from_UR(el_ve) &&
					myrikudo.is_filled_neighbour_from_UR(el_ve)) {
					auto UR_neigh = myrikudo.shape.get_UR_tile(el_ve);
					if (myrikudo.get_elem(UR_neigh) != v.end - 1)
						return false;
				}

				if ((fo_ve & rikudo::hex_dirs::_R) &&
					myrikudo.exists_neighbour_from__R(el_ve) &&
					myrikudo.is_filled_neighbour_from__R(el_ve)) {
					auto _R_neigh = myrikudo.shape.get__R_tile(el_ve);
					if (myrikudo.get_elem(_R_neigh) != v.end - 1)
						return false;
				}

				if ((fo_ve & rikudo::hex_dirs::DR) &&
					myrikudo.exists_neighbour_from_DR(el_ve) &&
					myrikudo.is_filled_neighbour_from_DR(el_ve)) {
					auto DR_neigh = myrikudo.shape.get_DR_tile(el_ve);
					if (myrikudo.get_elem(DR_neigh) != v.end - 1)
						return false;
				}

				if ((fo_ve & rikudo::hex_dirs::DL) &&
					myrikudo.exists_neighbour_from_DL(el_ve) &&
					myrikudo.is_filled_neighbour_from_DL(el_ve)) {
					auto DL_neigh = myrikudo.shape.get_DL_tile(el_ve);
					if (myrikudo.get_elem(DL_neigh) != v.end - 1)
						return false;
				}

				if ((fo_ve & rikudo::hex_dirs::_L) &&
					myrikudo.exists_neighbour_from__L(el_ve) &&
					myrikudo.is_filled_neighbour_from__L(el_ve)) {
					auto _L_neigh = myrikudo.shape.get__L_tile(el_ve);
					if (myrikudo.get_elem(_L_neigh) != v.end - 1)
						return false;
				}

				if ((fo_ve & rikudo::hex_dirs::UL) &&
					myrikudo.exists_neighbour_from_UL(el_ve) &&
					myrikudo.is_filled_neighbour_from_UL(el_ve)) {
					auto UL_neigh = myrikudo.shape.get_UL_tile(el_ve);
					if (myrikudo.get_elem(UL_neigh) != v.end - 1)
						return false;
				}

				// forced order is in the direction of unfilled element
				//    a) v.end - 1 is already filled / ??does not exists
				//       => if there are more than 1 forced directions in unfilled error
				//          else fill v.end-1 to this particular unfilled element
				//    b) v.end - 1 is unfilled (and it exists)
				//       => v.end + 1 can be filled to unfilled elements in forced directions
				
				bool  has_forced_end = false;
				for (auto& e_en : res_neigh_end) {
					if (e_en.second)
						has_forced_end = true;
				}

				if (has_forced_end) {
					if (v.end - 1 < 1 || myrikudo.is_already_filled(v.end - 1)) {
						int foe = myrikudo.count_forced_orders(el_ve);
						if (foe > 1)
							return false;
						else {
							// select single element from res_neigh_start
							for (auto it = res_neigh_end.begin(); it != res_neigh_end.end();)
							{
								if (!it->second)
									it = res_neigh_end.erase(it);
								else
									++it;
							}
						}
					}
					else {
						// from res_neigh_start selects elements with forced directions 
						for (auto it = res_neigh_end.begin(); it != res_neigh_end.end();)
						{
							if (!it->second)
								it = res_neigh_end.erase(it);
							else
								++it;
						}
					}

				}

			}
			
			for (auto& e_st : res_neigh_start) {
				for (auto& e_en : res_neigh_end) {
					if (e_st.first != e_en.first) {
						myrikudo.filled_values.insert({ e_st.first, v.start - 1 });
						myrikudo.filled_values_inv.insert({ v.start - 1, e_st.first });
						myrikudo.filled_values.insert({ e_en.first, v.end + 1 });
						myrikudo.filled_values_inv.insert({ v.end + 1, e_en.first });

						if (myrikudo.has_enough_space_elems())
							prolong_path(myrikudo, { v.start - 1, v.end + 1 });

						myrikudo.filled_values.erase(e_st.first);
						myrikudo.filled_values.erase(e_en.first);
						myrikudo.filled_values_inv.erase(v.start - 1);
						myrikudo.filled_values_inv.erase(v.end + 1);
					}
				}
			}						
		}
		else {	
			// v.end + 1 does not exists or is already filled

			
			if (v.end + 1 <= myrikudo.max_elem_value) {
				// v.end+1 is already filled
				auto addr_ve = myrikudo.get_addr(v.end);
				auto addr_vep1 = myrikudo.get_addr(v.end + 1);
				if (!myrikudo.are_neighbours(addr_ve, addr_vep1))
					return false;
			}
			
			// new v_end
			int vend = (v.end + 1 <= myrikudo.max_elem_value) ? v.end + 1 : myrikudo.max_elem_value;

			// can be prolonged down?

			auto res_neigh_start = myrikudo.get_unfilled_neighbours(myrikudo.get_addr(v.start));
			// unfilled but no candidates
			if (res_neigh_start.size() == 0)
				return false;

			std::pair<int, int> el_vs = myrikudo.get_addr(v.start);
			int fo_vs = myrikudo.get_forced_orders(el_vs);

			if (false && fo_vs) {
				// has some forced orders

				// if the forced order is in the direction of already filled element, 
				// this element needs to be equal to v.start+1

				if ((fo_vs & rikudo::hex_dirs::UR) &&
					myrikudo.exists_neighbour_from_UR(el_vs) &&
					myrikudo.is_filled_neighbour_from_UR(el_vs)) {
					auto UR_neigh = myrikudo.shape.get_UR_tile(el_vs);
					if (myrikudo.get_elem(UR_neigh) != v.start + 1)
						return false;
				}

				if ((fo_vs & rikudo::hex_dirs::_R) &&
					myrikudo.exists_neighbour_from__R(el_vs) &&
					myrikudo.is_filled_neighbour_from__R(el_vs)) {
					auto _R_neigh = myrikudo.shape.get__R_tile(el_vs);
					if (myrikudo.get_elem(_R_neigh) != v.start + 1)
						return false;
				}

				if ((fo_vs & rikudo::hex_dirs::DR) &&
					myrikudo.exists_neighbour_from_DR(el_vs) &&
					myrikudo.is_filled_neighbour_from_DR(el_vs)) {
					auto DR_neigh = myrikudo.shape.get_DR_tile(el_vs);
					if (myrikudo.get_elem(DR_neigh) != v.start + 1)
						return false;
				}

				if ((fo_vs & rikudo::hex_dirs::DL) &&
					myrikudo.exists_neighbour_from_DL(el_vs) &&
					myrikudo.is_filled_neighbour_from_DL(el_vs)) {
					auto DL_neigh = myrikudo.shape.get_DL_tile(el_vs);
					if (myrikudo.get_elem(DL_neigh) != v.start + 1)
						return false;
				}

				if ((fo_vs & rikudo::hex_dirs::_L) &&
					myrikudo.exists_neighbour_from__L(el_vs) &&
					myrikudo.is_filled_neighbour_from__L(el_vs)) {
					auto _L_neigh = myrikudo.shape.get__L_tile(el_vs);
					if (myrikudo.get_elem(_L_neigh) != v.start + 1)
						return false;
				}

				if ((fo_vs & rikudo::hex_dirs::UL) &&
					myrikudo.exists_neighbour_from_UL(el_vs) &&
					myrikudo.is_filled_neighbour_from_UL(el_vs)) {
					auto UL_neigh = myrikudo.shape.get_UL_tile(el_vs);
					if (myrikudo.get_elem(UL_neigh) != v.start + 1)
						return false;
				}

				/*if ((fo_vs & rikudo::hex_dirs::UR) &&
					myrikudo.exists_neighbour_from_UR(el_vs) &&
					!myrikudo.is_filled_neighbour_from_UR(el_vs)
					)*/

					// forced order is in the direction of unfilled element
					//    a) v.start+1 is already filled / does not exists
					//       => if there are more than 1 forced directions in unfilled error
					//          else fill v.start-1 to this particular unfilled element
					//    b) v.start+1 is unfilled (and it exists)
					//       => v.start - 1 can be filled to both unfilled elements in forced directions

				bool has_forced_start = false;
				for (auto& e_st : res_neigh_start) {
					if (e_st.second)
						has_forced_start = true;
				}

				if (has_forced_start) {
					if (v.start + 1 > myrikudo.max_elem_value || myrikudo.is_already_filled(v.start + 1)) {
						int foc = myrikudo.count_forced_orders(el_vs);
						if (foc > 1)
							return false;
						else {
							// select single element from res_neigh_start
							for (auto it = res_neigh_start.begin(); it != res_neigh_start.end();)
							{
								if (!it->second)
									it = res_neigh_start.erase(it);
								else
									++it;
							}
						}
					}
					else {
						// from res_neigh_start selects elements with forced directions 
						for (auto it = res_neigh_start.begin(); it != res_neigh_start.end();)
						{
							if (!it->second)
								it = res_neigh_start.erase(it);
							else
								++it;
						}
					}

				}

			}
			for (auto& e_st : res_neigh_start) {
				myrikudo.filled_values.insert({ e_st.first, v.start - 1 });
				myrikudo.filled_values_inv.insert({ v.start - 1, e_st.first });

				if (myrikudo.has_enough_space_elems())
					prolong_path(myrikudo, { v.start - 1, vend });

				myrikudo.filled_values.erase(e_st.first);
				myrikudo.filled_values_inv.erase(v.start - 1);
			}
		}
	}
	else {
		// v.start - 1 does not exist or is already filled 
		
		if (v.start - 1 >= 1) {
			auto addr_vs = myrikudo.get_addr(v.start);
			auto addr_vsm1 = myrikudo.get_addr(v.start - 1);
			if (!myrikudo.are_neighbours(addr_vs, addr_vsm1))
				return false;

		}

		// new vstart
		int vstart = (v.start - 1 >= 1) ? v.start - 1 : 1;



		if (v.end + 1 <= myrikudo.max_elem_value && !myrikudo.is_already_filled(v.end + 1)) {
			auto res_neigh_end = myrikudo.get_unfilled_neighbours(myrikudo.get_addr(v.end));
			if (res_neigh_end.size() == 0)
				return false;

			std::pair<int, int> el_ve = myrikudo.get_addr(v.end);
			int fo_ve = myrikudo.get_forced_orders(el_ve);

			if (false && fo_ve) {
				// has some forced orders

				// if the forced order is in the direction of already filled element, 
				// this element needs to be equal to v.end - 1

				if ((fo_ve & rikudo::hex_dirs::UR) &&
					myrikudo.exists_neighbour_from_UR(el_ve) &&
					myrikudo.is_filled_neighbour_from_UR(el_ve)) {
					auto UR_neigh = myrikudo.shape.get_UR_tile(el_ve);
					if (myrikudo.get_elem(UR_neigh) != v.end - 1)
						return false;
				}

				if ((fo_ve & rikudo::hex_dirs::_R) &&
					myrikudo.exists_neighbour_from__R(el_ve) &&
					myrikudo.is_filled_neighbour_from__R(el_ve)) {
					auto _R_neigh = myrikudo.shape.get__R_tile(el_ve);
					if (myrikudo.get_elem(_R_neigh) != v.end - 1)
						return false;
				}

				if ((fo_ve & rikudo::hex_dirs::DR) &&
					myrikudo.exists_neighbour_from_DR(el_ve) &&
					myrikudo.is_filled_neighbour_from_DR(el_ve)) {
					auto DR_neigh = myrikudo.shape.get_DR_tile(el_ve);
					if (myrikudo.get_elem(DR_neigh) != v.end - 1)
						return false;
				}

				if ((fo_ve & rikudo::hex_dirs::DL) &&
					myrikudo.exists_neighbour_from_DL(el_ve) &&
					myrikudo.is_filled_neighbour_from_DL(el_ve)) {
					auto DL_neigh = myrikudo.shape.get_DL_tile(el_ve);
					if (myrikudo.get_elem(DL_neigh) != v.end - 1)
						return false;
				}

				if ((fo_ve & rikudo::hex_dirs::_L) &&
					myrikudo.exists_neighbour_from__L(el_ve) &&
					myrikudo.is_filled_neighbour_from__L(el_ve)) {
					auto _L_neigh = myrikudo.shape.get__L_tile(el_ve);
					if (myrikudo.get_elem(_L_neigh) != v.end - 1)
						return false;
				}

				if ((fo_ve & rikudo::hex_dirs::UL) &&
					myrikudo.exists_neighbour_from_UL(el_ve) &&
					myrikudo.is_filled_neighbour_from_UL(el_ve)) {
					auto UL_neigh = myrikudo.shape.get_UL_tile(el_ve);
					if (myrikudo.get_elem(UL_neigh) != v.end - 1)
						return false;
				}

				// forced order is in the direction of unfilled element
				//    a) v.end - 1 is already filled / ??does not exists
				//       => if there are more than 1 forced directions in unfilled error
				//          else fill v.end-1 to this particular unfilled element
				//    b) v.end - 1 is unfilled (and it exists)
				//       => v.end + 1 can be filled to unfilled elements in forced directions

				bool  has_forced_end = false;
				for (auto& e_en : res_neigh_end) {
					if (e_en.second)
						has_forced_end = true;
				}

				if (has_forced_end) {
					if (v.end - 1 < 1 || myrikudo.is_already_filled(v.end - 1)) {
						int foe = myrikudo.count_forced_orders(el_ve);
						if (foe > 1)
							return false;
						else {
							// select single element from res_neigh_end
							for (auto it = res_neigh_end.begin(); it != res_neigh_end.end();)
							{
								if (!it->second)
									it = res_neigh_end.erase(it);
								else
									++it;
							}
						}
					}
					else {
						// from res_neigh_start select elements with forced directions 
						for (auto it = res_neigh_end.begin(); it != res_neigh_end.end();)
						{
							if (!it->second)
								it = res_neigh_end.erase(it);
							else
								++it;
						}
					}

				}

			}



			//bool has_forced_end = false;
			//for (auto& e_en : res_neigh_end) {
			//	if (e_en.second)
			//		has_forced_end = true;
			//}

			for (auto& e_en : res_neigh_end) {
				myrikudo.filled_values.insert({ e_en.first, v.end + 1 });
				myrikudo.filled_values_inv.insert({ v.end + 1, e_en.first });

				if (myrikudo.has_enough_space_elems())
					prolong_path(myrikudo, { vstart, v.end + 1 });

				myrikudo.filled_values.erase(e_en.first);
				myrikudo.filled_values_inv.erase(v.end + 1);
			}
		}
		else {
			if (v.end + 1 <= myrikudo.max_elem_value) {
				// v.end+1 is already filled
				auto addr_ve = myrikudo.get_addr(v.end);
				auto addr_vep1 = myrikudo.get_addr(v.end + 1);
				if (!myrikudo.are_neighbours(addr_ve, addr_vep1))
					return false;
			}

			int vend = (v.end + 1 <= myrikudo.max_elem_value) ? v.end + 1 : myrikudo.max_elem_value;

			// probably not necessary
			if (myrikudo.has_enough_space_elems())
				prolong_path(myrikudo, { vstart, vend });
		}
	}


	return false;
}

bool prolong_path_with_blocks(rikudo& myrikudo, interval v) {

	//bool changed = false;
	//if (v_min > v.start) {
	//	v_min = v.start;
	//	changed = true;
	//}
	//if (v_max < v.end) {
	//	v_max = v.end;
	//	changed = true;
	//}
	//if (changed || (v_min == v.start && v_max == v.end)) {
	//	std::cerr << v.start << ", " << v.end << '\n';
	//	myrikudo.disp_crude();
	//}

	for (int i = v.start; i <= v.end; i++) {
		if (!myrikudo.is_already_filled(i)) {
			std::cerr << "Error: Element " << i << " is unfilled.\n";
			return false;
		}
	}


	/*if (v.start <=15 && v.end >=75)*/
		//std::cerr << v.start << ", " << v.end << '\n';
	/*if (v.end >= 75)
		std::cout << v.start << ", " << v.end << '\n';*/
		/*for (int i = (int)myrikudo.shape.row_sizes.size() - 1; i >= 0; i--) {
			for (int j = 0; j < myrikudo.shape.row_sizes[i]; j++) {
				int val = myrikudo.get_elem({ i,j });
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
		}*/



	// check correctness of partial solution
	// v_i v_{i+1} are connected
	// if v_i is forced 
	// forced_cnt==1: v_{i-1} ... v_i or v_i ... v_{i+1} is connected via forced direction
	// forced_cnt==2: v_{i-1} ... v_i and v_i ... v_{i+1} are connected via forced directions


#if 0
	// tests connectivity	
	if (v.end - v.start > 0) {

		std::pair<int, int> e_1{ -1,-1 }, e_2{ -1,-1 };
		e_1 = myrikudo.get_addr(v.start);
		int idx = v.start + 1;

		while (idx <= v.end) {
			e_2 = myrikudo.get_addr(idx);

			if (!myrikudo.are_neighbours(e_1, e_2)) {
				//std::cerr << "(" << e_1.first << ", " << e_1.second << ")[" << myrikudo.get_elem(e_1) << "] and (" << e_2.first << ", " << e_2.second << ")[" << myrikudo.get_elem(e_2) << "] are not connected.";
				return false;
			}

			idx++;
			e_1 = e_2;
		}
	}
#endif



	// test forced connectivity
	/*if (v.end - v.start > 1) {
		std::pair<int, int> e_b{ -1,-1 }, e_m{ -1,-1 }, e_e{ -1,-1 };
		e_b = myrikudo.get_addr(v.start);
		e_m = myrikudo.get_addr(v.start + 1);
		int idx = v.start + 2;

		while (idx <= v.end) {
			e_e = myrikudo.get_addr(idx);

			int foc = myrikudo.count_forced_orders(e_m);

			if (foc == 1) {
				int fo_m = myrikudo.get_forced_orders(e_m);

				if (fo_m & myrikudo.UR) {
					if (!myrikudo.are_neighbours_from_UR(e_m, e_b) && !myrikudo.are_neighbours_from_UR(e_m, e_e)) {
						return false;
					}
				}

				if (fo_m & myrikudo._R) {
					if (!myrikudo.are_neighbours_from__R(e_m, e_b) && !myrikudo.are_neighbours_from__R(e_m, e_e))
						return false;
				}

				if (fo_m & myrikudo.DR) {
					if (!myrikudo.are_neighbours_from_DR(e_m, e_b) && !myrikudo.are_neighbours_from_DR(e_m, e_e))
						return false;
				}

				if (fo_m & myrikudo.DL) {
					if (!myrikudo.are_neighbours_from_DL(e_m, e_b) && !myrikudo.are_neighbours_from_DL(e_m, e_e))
						return false;
				}

				if (fo_m & myrikudo._L) {
					if (!myrikudo.are_neighbours_from__L(e_m, e_b) && !myrikudo.are_neighbours_from__L(e_m, e_e))
						return false;
				}

				if (fo_m & myrikudo.UL) {
					if (!myrikudo.are_neighbours_from_UL(e_m, e_b) && !myrikudo.are_neighbours_from_UL(e_m, e_e))
						return false;
				}
			}
			else if (foc == 2) {
				if (myrikudo.count_forced_orders(e_b) == 0 || myrikudo.count_forced_orders(e_e) == 0)
					return false;

				int fo_b = myrikudo.get_forced_orders(e_b);
				int fo_m = myrikudo.get_forced_orders(e_m);
				int fo_e = myrikudo.get_forced_orders(e_e);

				if (myrikudo.are_neighbours_from_UR(e_b, e_m) && !myrikudo.is_forced_from_DL(e_m))
					return false;
				if (myrikudo.are_neighbours_from__R(e_b, e_m) && !myrikudo.is_forced_from__L(e_m))
					return false;
				if (myrikudo.are_neighbours_from_DR(e_b, e_m) && !myrikudo.is_forced_from_UL(e_m))
					return false;
				if (myrikudo.are_neighbours_from_DL(e_b, e_m) && !myrikudo.is_forced_from_UR(e_m))
					return false;
				if (myrikudo.are_neighbours_from__L(e_b, e_m) && !myrikudo.is_forced_from__R(e_m))
					return false;
				if (myrikudo.are_neighbours_from_UL(e_b, e_m) && !myrikudo.is_forced_from_DR(e_m))
					return false;

				if (myrikudo.are_neighbours_from_UR(e_e, e_m) && !myrikudo.is_forced_from_DL(e_m))
					return false;
				if (myrikudo.are_neighbours_from__R(e_e, e_m) && !myrikudo.is_forced_from__L(e_m))
					return false;
				if (myrikudo.are_neighbours_from_DR(e_e, e_m) && !myrikudo.is_forced_from_UL(e_m))
					return false;
				if (myrikudo.are_neighbours_from_DL(e_e, e_m) && !myrikudo.is_forced_from_UR(e_m))
					return false;
				if (myrikudo.are_neighbours_from__L(e_e, e_m) && !myrikudo.is_forced_from__R(e_m))
					return false;
				if (myrikudo.are_neighbours_from_UL(e_e, e_m) && !myrikudo.is_forced_from_DR(e_m))
					return false;
			}


			idx++;
			e_b = e_m;
			e_m = e_e;
		}

	}*/

	// if exists unused block
	bool b_unused_block = false;
	for (auto& b : myrikudo.fillable_blocks)
		if (!b.used) {
			b_unused_block = true;
			break;
		}


	//if (v.start == 1 && v.end == myrikudo.max_elem_value) {
	if (!b_unused_block) {
		if (true || test_solution(myrikudo)) {
			// we have solution 
			// print TODO
			std::cout << "Solution.\n";

			for (auto& e : myrikudo.filled_values_inv) {
				std::cout << "(" << e.second.first << "," << e.second.second << ") -> " << e.first << ", ";
			}
			std::cout << "\n";

			for (int i = (int)myrikudo.shape.row_sizes.size() - 1; i >= 0; i--) {
				for (int j = 0; j < myrikudo.shape.row_sizes[i]; j++) {
					int val = myrikudo.get_elem({ i,j });
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

		return true;
	}


	if (true)
	{
		/*const*/
		//int first_forced_value;
		//int last_forced_value;

		//find_first_unfilled
		int sidx = myrikudo.first_forced_value;
		do {
			int first_unfilled_value = -1;
			for (int i = sidx; i <= myrikudo.last_forced_value; i++)
				if (!myrikudo.is_already_filled(i)) {
					first_unfilled_value = i;
					break;
				}

			if (first_unfilled_value != -1) {
				int interval_start;
				if (first_unfilled_value < myrikudo.first_forced_value)
					interval_start = myrikudo.first_forced_value;
				else
					interval_start = first_unfilled_value - 1;

				if (!myrikudo.is_already_filled(interval_start + 1)) {
					int idx = interval_start + 1;
					while (idx <= myrikudo.last_forced_value && !myrikudo.is_already_filled(idx)) {
						idx++;
					}
					int interval_end;
					if (idx <= myrikudo.last_forced_value)
						interval_end = idx;
					else
						interval_end = -1;

					if (interval_end != -1) {
						
						b_path_found = false;
						//std::vector<std::pair<int,int>> v_bs;
						std::vector<int> v_bs;
						std::vector<int> v_bc;
						std::vector<std::pair<int, int>> v_es;

						auto el_from = myrikudo.get_addr(interval_start),
							 el_to = myrikudo.get_addr(interval_end);
						int plen = interval_end - interval_start-1;


						/*exists_path_via_unused_blocks_of_length_recOLD(plen, v_bs, v_bc, v_es, myrikudo,
							el_from, el_to, b_path_found, false);*/
						exists_path_via_unused_blocks_of_length_rec(plen, v_bs, v_bc, interval_start, interval_end, myrikudo,
							el_from, el_to, b_path_found);
						//exists_path_of_length(interval_end - interval_start, vv, myrikudo, myrikudo.get_addr(interval_start), myrikudo.get_addr(interval_end));
						/*if (changed || (v_min == v.start && v_max == v.end)) {
							std::cerr << "Checking the interval [" << interval_start << "," << interval_end << "]: " << b_path_found << "\n";
						}*/

#if 0
						// for debugging
						if (!b_path_found) {
							// compare if correct
							bool b_is_partially_correct = true;
							for (auto& fe : myrikudo.filled_values) {
								int v1 = fe.second;
								auto it = small_correctly_filled.find(fe.first);
								if (it == small_correctly_filled.end()) {
									std::cerr << "Problem: stange value filled " << fe.first << "!\n";
									b_is_partially_correct = false;
								}
								else {
									int v2 = it->second;
									if (v1 != v2) {
										b_is_partially_correct = false;
										break;
									}
								}
							}

							if (b_is_partially_correct) {
								std::cerr << "Problem: partially correct possibility is excluded!\n";
								std::cerr << "From: " << el_from << " to: " << el_to <<
									exists_path_via_unused_blocks_of_length(myrikudo, el_from, el_to, plen)
								<< ".\n";

								std::cerr << "HERE\n";

							}
						}
#endif
						if (!b_path_found) {
							//std::cerr << "There is no path via unfilled block from " << interval_start << " to " << interval_end << '\n';
							//myrikudo.disp_crude();
							return false;
						}

						sidx = interval_end;
					}
					else
						sidx = myrikudo.last_forced_value;
				}

			}
			else
				break;

		} while (sidx <= myrikudo.last_forced_value);
	}

	if (!myrikudo.test_block_components())
		return false;

	if (v.start - 1 >= 1 && !myrikudo.is_already_filled(v.start - 1)) {

		if (v.end + 1 <= myrikudo.max_elem_value && !myrikudo.is_already_filled(v.end + 1)) {

			auto elem_vs = myrikudo.get_addr(v.start);
			auto res_neigh_blocks_start = myrikudo.get_unfilled_neighbour_blocks_idxs(elem_vs);
			// unfilled value, but no unfilled tile
			if (res_neigh_blocks_start.size() == 0)
				return false;
			
			auto elem_ve = myrikudo.get_addr(v.end);
			auto res_neigh_blocks_end = myrikudo.get_unfilled_neighbour_blocks_idxs(elem_ve);
			// unfilled value, but no unfilled tile
			if (res_neigh_blocks_end.size() == 0)
				return false;


			for (int e_st_idx : res_neigh_blocks_start) {
				if (myrikudo.can_fillable_block_fit(v.start - 1, e_st_idx, false /*down*/)) {
					for (int e_en_idx : res_neigh_blocks_end) {
						if (e_st_idx != e_en_idx) {
							if (myrikudo.can_fillable_block_fit(v.end + 1, e_en_idx, true /*up*/)) {
							
								if (myrikudo.are_neighbours(elem_vs, myrikudo.fillable_blocks[e_st_idx].end1)) {
									if (myrikudo.are_neighbours(elem_ve, myrikudo.fillable_blocks[e_en_idx].end1)) {
										// fill block down from end1
										myrikudo.use_block(e_st_idx, true, v.start - 1, true);
										// fill block up from end1
										myrikudo.use_block(e_en_idx, true, v.end + 1, false);									

										if (myrikudo.has_enough_space_elems()
											&& myrikudo.can_be_attached_all()
											&& myrikudo.exist_paths_via_unfilled()
											&& (v.start - myrikudo.fillable_blocks[e_st_idx].length - 1 < 1
												|| !myrikudo.is_already_filled(v.start - myrikudo.fillable_blocks[e_st_idx].length - 1)
												|| myrikudo.are_neighbours(myrikudo.get_addr(v.start - myrikudo.fillable_blocks[e_st_idx].length - 1), myrikudo.fillable_blocks[e_st_idx].end2)
												)
											&& (v.end + myrikudo.fillable_blocks[e_en_idx].length + 1 > myrikudo.max_elem_value
												|| !myrikudo.is_already_filled(v.end + myrikudo.fillable_blocks[e_en_idx].length + 1)
												|| myrikudo.are_neighbours(myrikudo.get_addr(v.end + myrikudo.fillable_blocks[e_en_idx].length + 1), myrikudo.fillable_blocks[e_en_idx].end2)
												)
											)
											prolong_path_with_blocks(myrikudo, { v.start - myrikudo.fillable_blocks[e_st_idx].length,
												v.end + myrikudo.fillable_blocks[e_en_idx].length });

										// unfill block down from end1
										myrikudo.unuse_block(e_st_idx, true, v.start - 1, true);										
										// unfill block up from end1
										myrikudo.unuse_block(e_en_idx, true, v.end + 1, false);
									}
									if (myrikudo.fillable_blocks[e_en_idx].end1 != myrikudo.fillable_blocks[e_en_idx].end2
										&& myrikudo.are_neighbours(elem_ve, myrikudo.fillable_blocks[e_en_idx].end2)) {
										// fill block down from end1
										myrikudo.use_block(e_st_idx, true, v.start - 1, true);								
										// fill block up from end2
										myrikudo.use_block(e_en_idx, false, v.end + 1, false);

										if (myrikudo.has_enough_space_elems()
											&& myrikudo.can_be_attached_all()
											&& myrikudo.exist_paths_via_unfilled()
											&& (v.start - myrikudo.fillable_blocks[e_st_idx].length - 1 < 1
												|| !myrikudo.is_already_filled(v.start - myrikudo.fillable_blocks[e_st_idx].length - 1)
												|| myrikudo.are_neighbours(myrikudo.get_addr(v.start - myrikudo.fillable_blocks[e_st_idx].length - 1), myrikudo.fillable_blocks[e_st_idx].end2)
												)
											&& (v.end + myrikudo.fillable_blocks[e_en_idx].length + 1 > myrikudo.max_elem_value
												|| !myrikudo.is_already_filled(v.end + myrikudo.fillable_blocks[e_en_idx].length + 1)
												|| myrikudo.are_neighbours(myrikudo.get_addr(v.end + myrikudo.fillable_blocks[e_en_idx].length + 1), myrikudo.fillable_blocks[e_en_idx].end1)
												)
										)
											prolong_path_with_blocks(myrikudo, { v.start - myrikudo.fillable_blocks[e_st_idx].length,
												v.end + myrikudo.fillable_blocks[e_en_idx].length });

										// unfill block down end1
										myrikudo.unuse_block(e_st_idx, true, v.start - 1, true);
										// unfill block up end2
										myrikudo.unuse_block(e_en_idx, false, v.end + 1, false);
									}
								}

								if (myrikudo.fillable_blocks[e_st_idx].end1 != myrikudo.fillable_blocks[e_st_idx].end2
									&& myrikudo.are_neighbours(elem_vs, myrikudo.fillable_blocks[e_st_idx].end2)) {
									
									if (myrikudo.are_neighbours(elem_ve, myrikudo.fillable_blocks[e_en_idx].end1)) {
										// fill block down from end2
										myrikudo.use_block(e_st_idx, false, v.start - 1, true);
										// fill block up from end1
										myrikudo.use_block(e_en_idx, true, v.end + 1, false);
										
										if (myrikudo.has_enough_space_elems()
											&& myrikudo.can_be_attached_all()
											&& myrikudo.exist_paths_via_unfilled()
											&& (v.start - myrikudo.fillable_blocks[e_st_idx].length - 1 < 1
												|| !myrikudo.is_already_filled(v.start - myrikudo.fillable_blocks[e_st_idx].length - 1)
												|| myrikudo.are_neighbours(myrikudo.get_addr(v.start - myrikudo.fillable_blocks[e_st_idx].length - 1), myrikudo.fillable_blocks[e_st_idx].end1)
												)
											&& (v.end + myrikudo.fillable_blocks[e_en_idx].length + 1 > myrikudo.max_elem_value
												|| !myrikudo.is_already_filled(v.end + myrikudo.fillable_blocks[e_en_idx].length + 1)
												|| myrikudo.are_neighbours(myrikudo.get_addr(v.end + myrikudo.fillable_blocks[e_en_idx].length + 1), myrikudo.fillable_blocks[e_en_idx].end2)
												)
										)
											prolong_path_with_blocks(myrikudo, { v.start - myrikudo.fillable_blocks[e_st_idx].length,
												v.end + myrikudo.fillable_blocks[e_en_idx].length });

										// unfill block down end2
										myrikudo.unuse_block(e_st_idx, false, v.start - 1, true);
										// unfill block up end1
										myrikudo.unuse_block(e_en_idx, true, v.end + 1, false);
									}
									if (myrikudo.fillable_blocks[e_en_idx].end1 != myrikudo.fillable_blocks[e_en_idx].end2
										&& myrikudo.are_neighbours(elem_ve, myrikudo.fillable_blocks[e_en_idx].end2)) {
										// fill block down end2
										myrikudo.use_block(e_st_idx, false, v.start - 1, true);
										// fill block up end2
										myrikudo.use_block(e_en_idx, false, v.end + 1, false);
										
										if (myrikudo.has_enough_space_elems()
											&& myrikudo.can_be_attached_all()
											&& myrikudo.exist_paths_via_unfilled()
											&& (v.start - myrikudo.fillable_blocks[e_st_idx].length - 1 < 1
												|| !myrikudo.is_already_filled(v.start - myrikudo.fillable_blocks[e_st_idx].length - 1)
												|| myrikudo.are_neighbours(myrikudo.get_addr(v.start - myrikudo.fillable_blocks[e_st_idx].length - 1), myrikudo.fillable_blocks[e_st_idx].end1)
												)
											&& (v.end + myrikudo.fillable_blocks[e_en_idx].length + 1 > myrikudo.max_elem_value
												|| !myrikudo.is_already_filled(v.end + myrikudo.fillable_blocks[e_en_idx].length + 1)
												|| myrikudo.are_neighbours(myrikudo.get_addr(v.end + myrikudo.fillable_blocks[e_en_idx].length + 1), myrikudo.fillable_blocks[e_en_idx].end1)
												)
										)
											prolong_path_with_blocks(myrikudo, { v.start - myrikudo.fillable_blocks[e_st_idx].length,
												v.end + myrikudo.fillable_blocks[e_en_idx].length });

										// unfill block down end2
										myrikudo.unuse_block(e_st_idx, false, v.start - 1, true);
										// unfill block up end2
										myrikudo.unuse_block(e_en_idx, false, v.end + 1, false);
									}
								}
							}
						}
					}
				}
			}
		}
		else {
			// v.end + 1 does not exists or is already filled


			if (v.end + 1 <= myrikudo.max_elem_value) {
				// v.end+1 is already filled
				auto addr_ve = myrikudo.get_addr(v.end);
				auto addr_vep1 = myrikudo.get_addr(v.end + 1);
				if (!myrikudo.are_neighbours(addr_ve, addr_vep1))
					return false;
			}

			// new v_end
			int vend = (v.end + 1 <= myrikudo.max_elem_value) ? v.end + 1 : myrikudo.max_elem_value;

			auto elem_vs = myrikudo.get_addr(v.start);
			auto res_neigh_blocks_start = myrikudo.get_unfilled_neighbour_blocks_idxs(elem_vs);
			// unfilled value, but no unfilled tile
			if (res_neigh_blocks_start.size() == 0)
				return false;


			for (int e_st_idx : res_neigh_blocks_start) {
				if (myrikudo.can_fillable_block_fit(v.start - 1, e_st_idx, false /*down*/)) {

					if (myrikudo.are_neighbours(elem_vs, myrikudo.fillable_blocks[e_st_idx].end1)) {						
						// fill block down from end1
						myrikudo.use_block(e_st_idx, true, v.start - 1, true);

						if (myrikudo.has_enough_space_elems()
							&& myrikudo.can_be_attached_all()
							&& myrikudo.exist_paths_via_unfilled()
							&& (v.start - myrikudo.fillable_blocks[e_st_idx].length - 1 < 1
								|| !myrikudo.is_already_filled(v.start - myrikudo.fillable_blocks[e_st_idx].length - 1)
								|| myrikudo.are_neighbours(myrikudo.get_addr(v.start - myrikudo.fillable_blocks[e_st_idx].length - 1), myrikudo.fillable_blocks[e_st_idx].end2)
								)
						)
							prolong_path_with_blocks(myrikudo, { v.start - myrikudo.fillable_blocks[e_st_idx].length, vend });

						// unfill block down from end1							
						myrikudo.unuse_block(e_st_idx, true, v.start - 1, true);
					}

					if (myrikudo.fillable_blocks[e_st_idx].end1 != myrikudo.fillable_blocks[e_st_idx].end2
						&& myrikudo.are_neighbours(elem_vs, myrikudo.fillable_blocks[e_st_idx].end2)) {

						// fill block down from end2
						myrikudo.use_block(e_st_idx, false, v.start - 1, true);

						if (myrikudo.has_enough_space_elems()
							&& myrikudo.can_be_attached_all()
							&& myrikudo.exist_paths_via_unfilled()
							&& (v.start - myrikudo.fillable_blocks[e_st_idx].length - 1 < 1
								|| !myrikudo.is_already_filled(v.start - myrikudo.fillable_blocks[e_st_idx].length - 1)
								|| myrikudo.are_neighbours(myrikudo.get_addr(v.start - myrikudo.fillable_blocks[e_st_idx].length - 1), myrikudo.fillable_blocks[e_st_idx].end1)
								)
						)
							prolong_path_with_blocks(myrikudo, { v.start - myrikudo.fillable_blocks[e_st_idx].length, vend });

						// unfill block down end2
						myrikudo.unuse_block(e_st_idx, false, v.start - 1, true);
					}
				}
			}
		}
	}
	else {
		// v.start - 1 does not exist or is already filled 

		if (v.start - 1 >= 1) {
			auto addr_vs = myrikudo.get_addr(v.start);
			auto addr_vsm1 = myrikudo.get_addr(v.start - 1);
			if (!myrikudo.are_neighbours(addr_vs, addr_vsm1))
				return false;

		}

		// new vstart
		int vstart = (v.start - 1 >= 1) ? v.start - 1 : 1;



		if (v.end + 1 <= myrikudo.max_elem_value && !myrikudo.is_already_filled(v.end + 1)) {

			auto elem_ve = myrikudo.get_addr(v.end);
			auto res_neigh_blocks_end = myrikudo.get_unfilled_neighbour_blocks_idxs(elem_ve);
			// unfilled value, but no unfilled tile
			if (res_neigh_blocks_end.size() == 0)
				return false;


			for (int e_en_idx : res_neigh_blocks_end) {
				if (myrikudo.can_fillable_block_fit(v.end + 1, e_en_idx, true /*up*/)) {
					if (myrikudo.are_neighbours(elem_ve, myrikudo.fillable_blocks[e_en_idx].end1)) {
						// fill block up from end1
						myrikudo.use_block(e_en_idx, true, v.end + 1, false);

						if (myrikudo.has_enough_space_elems()
							&& myrikudo.can_be_attached_all()
							&& myrikudo.exist_paths_via_unfilled()
							&& (v.end + myrikudo.fillable_blocks[e_en_idx].length + 1 > myrikudo.max_elem_value
								|| !myrikudo.is_already_filled(v.end + myrikudo.fillable_blocks[e_en_idx].length + 1)
								|| myrikudo.are_neighbours(myrikudo.get_addr(v.end + myrikudo.fillable_blocks[e_en_idx].length + 1), myrikudo.fillable_blocks[e_en_idx].end2)
								)
						)
							prolong_path_with_blocks(myrikudo, { vstart,v.end + myrikudo.fillable_blocks[e_en_idx].length });

						// unfill block up from end1
						myrikudo.unuse_block(e_en_idx, true, v.end + 1, false);
					}

					if (myrikudo.fillable_blocks[e_en_idx].end1 != myrikudo.fillable_blocks[e_en_idx].end2
						&& myrikudo.are_neighbours(elem_ve, myrikudo.fillable_blocks[e_en_idx].end2)) {
						// fill block up from end2
						myrikudo.use_block(e_en_idx, false, v.end + 1, false);

						if (myrikudo.has_enough_space_elems()
							&& myrikudo.can_be_attached_all()
							&& myrikudo.exist_paths_via_unfilled()
							&& (v.end + myrikudo.fillable_blocks[e_en_idx].length + 1 > myrikudo.max_elem_value
								|| !myrikudo.is_already_filled(v.end + myrikudo.fillable_blocks[e_en_idx].length + 1)
								|| myrikudo.are_neighbours(myrikudo.get_addr(v.end + myrikudo.fillable_blocks[e_en_idx].length + 1), myrikudo.fillable_blocks[e_en_idx].end1)
								)
						)
							prolong_path_with_blocks(myrikudo, { vstart, v.end + myrikudo.fillable_blocks[e_en_idx].length });

						// unfill block up end2
						myrikudo.unuse_block(e_en_idx, false, v.end + 1, false);
					}
				}
			}
		}	
		else {
			if (v.end + 1 <= myrikudo.max_elem_value) {
				// v.end+1 is already filled
				auto addr_ve = myrikudo.get_addr(v.end);
				auto addr_vep1 = myrikudo.get_addr(v.end + 1);
				if (!myrikudo.are_neighbours(addr_ve, addr_vep1))
					return false;
			}

			int vend = (v.end + 1 <= myrikudo.max_elem_value) ? v.end + 1 : myrikudo.max_elem_value;

			// probably not necessary
			if (myrikudo.has_enough_space_elems())
				prolong_path_with_blocks(myrikudo, { vstart, vend });
		}
	}

	return false;
}

bool can_coeexist(std::set<int>& used_blocks, std::vector<std::pair<int, int>>& path) {
	if (!used_blocks.empty()) {
		for (auto& pe : path) {
			if (used_blocks.find(pe.first) != used_blocks.end())
				return false;
		}
	}
	return true;
}

void search_coexistent_paths(int depth, const std::vector<std::pair<int,int>>::iterator &it, 
	const std::map<std::pair<int,int>, std::vector<std::vector<std::pair<int,int>>>> &available_paths, 
	std::set<int> &used_blocks, std::vector<int> &paths_idxs, rikudo &myrikudo, std::vector<std::pair<int,int>> &intes) {
	if (depth == 0) {
		// Solution
		std::cout << "Solution:";
		for (auto e : paths_idxs) {
			std::cout << " " << e;
		}
		std::cout << '\n';

		std::cout << '\n';
		auto it = intes.begin();
		for (auto e : paths_idxs) {
			//std::cout << " " << e;
			int fill_value = it->first + 1;
			for (auto& pth : available_paths.at(*it)[e]) {
				//std::cout << "Filling " << pth << " by value " << fill_value << '\n';
				myrikudo.use_block(pth.first, pth.second, fill_value, false);
				fill_value += myrikudo.fillable_blocks[pth.first].length;
			}

			++it;
		}
		myrikudo.disp_crude();



	}
	else {
		int cur_path_idx = 0;
		auto path_candidates = available_paths.at(*it);
		for (auto& pth : path_candidates) {
			if (can_coeexist(used_blocks, pth)) {
				// add elements of pth to used_blocks (just block_ids)
				for (auto& e : pth)
					used_blocks.insert(e.first);
				paths_idxs.push_back(cur_path_idx);
				
				auto next_it = it + 1;

				search_coexistent_paths(depth - 1, next_it, available_paths, used_blocks, paths_idxs, myrikudo, intes);

				// remove elements of pth from used_blocks
				for (auto& e : pth)
					used_blocks.erase(e.first);
				paths_idxs.pop_back();
			}
			cur_path_idx++;
		}
	}

}

void search_coexistent_paths_1(int depth, const std::vector<std::pair<int, int>>::iterator& it,
	const std::map<std::pair<int, int>, std::vector<std::vector<std::pair<int, int>>>>& available_paths,
	std::set<int>& used_blocks, std::vector<int>& paths_idxs, rikudo& myrikudo, std::vector<std::pair<int, int>>& intes) {
	if (depth == 0) {
		// Solution
		std::cout << "Solution:";
		for (auto e : paths_idxs) {
			std::cout << " " << e;
		}
		std::cout << '\n';

		std::cout << '\n';
		auto it = intes.begin();
		for (auto e : paths_idxs) {
			//std::cout << " " << e;
			int fill_value = it->first + 1;
			for (auto& pth : available_paths.at(*it)[e]) {
				//std::cout << "Filling " << pth << " by value " << fill_value << '\n';
				myrikudo.use_block(pth.first, pth.second, fill_value, false);
				fill_value += myrikudo.fillable_blocks[pth.first].length;
			}

			++it;
		}
		myrikudo.disp_crude();



	}
	else {
		int cur_path_idx = 0;
		auto path_candidates = available_paths.at(*it);
		for (auto& pth : path_candidates) {
			if (can_coeexist(used_blocks, pth)) {
				// add elements of pth to used_blocks (just block_ids)
				for (auto& e : pth)
					used_blocks.insert(e.first);
				paths_idxs.push_back(cur_path_idx);

				auto next_it = it + 1;

				search_coexistent_paths_1(depth - 1, next_it, available_paths, used_blocks, paths_idxs, myrikudo, intes);

				// remove elements of pth from used_blocks
				for (auto& e : pth)
					used_blocks.erase(e.first);
				paths_idxs.pop_back();
			}
			cur_path_idx++;
		}
	}

}



void search_coexistent_paths2(unsigned long long int &itcount, int depth, const std::vector<std::pair<int, int>>::iterator& it,
	const std::map<std::pair<int, int>, std::vector<std::vector<std::pair<int, int>>>>& available_paths,
	std::set<int>& used_blocks, std::vector<int>& paths_idxs, rikudo& myrikudo, std::vector<std::pair<int, int>>& intes) {
	itcount++;
	if ((itcount % 100000) == 0) {
		for (auto& pthi : paths_idxs)
			std::cerr << " " << pthi;
		std::cerr << '\n';
	}

	if (depth == 0) {
		// Solution
		std::cout << "Solution:";
		for (auto e : paths_idxs) {
			std::cout << " " << e;
		}
		std::cout << '\n';

		std::cout << '\n';
		
		//myrikudo.disp_crude();
		auto it = intes.begin();
		for (auto e : paths_idxs) {
			//std::cout << " " << e;
			int fill_value = it->first + 1;
			for (auto& pth : available_paths.at(*it)[e]) {
				//std::cout << "Filling " << pth << " by value " << fill_value << '\n';
				myrikudo.use_block(pth.first, pth.second, fill_value, false);
				fill_value += myrikudo.fillable_blocks[pth.first].length;
			}

			++it;
		}
		myrikudo.disp_crude();
		// clear solution
		//it = intes.begin();
		//for (auto e : paths_idxs) {
		//	//std::cout << " " << e;
		//	int fill_value = it->first + 1;
		//	for (auto& pth : available_paths.at(*it)[e]) {
		//		//std::cout << "Filling " << pth << " by value " << fill_value << '\n';
		//		myrikudo.unuse_block(pth.first, pth.second, fill_value, false);
		//		fill_value += myrikudo.fillable_blocks[pth.first].length;
		//	}

		//	++it;
		//}
		//myrikudo.disp_crude();


	}
	else {
		int cur_path_idx = 0;
		auto path_candidates = available_paths.at(*it);
		for (auto& pth : path_candidates) {
			if (can_coeexist(used_blocks, pth)) {
				// add elements of pth to used_blocks (just block_ids)
				for (auto& e : pth)
					used_blocks.insert(e.first);
				paths_idxs.push_back(cur_path_idx);

				auto next_it = it + 1;

				search_coexistent_paths2(itcount, depth - 1, next_it, available_paths, used_blocks, paths_idxs, myrikudo, intes);

				// remove elements of pth from used_blocks
				for (auto& e : pth)
					used_blocks.erase(e.first);
				paths_idxs.pop_back();
			}
			cur_path_idx++;
		}
	}

}



void solve_rikudo(rikudo& myrikudo) {
	//myrikudo.init();
	
	myrikudo.disp_crude();
	std::vector<std::pair<int, int>> intes;
	myrikudo.get_unfilled_intervals(intes);
	std::map<std::pair<int, int>, std::vector<std::vector<std::pair<int, int>>>> paths_map;
	for (auto& inte : intes) {
		std::cout << inte << ": ";
		std::vector<std::vector<std::pair<int, int>>> paths;
		paths = compute_paths_via_unused_blocks_of_length(myrikudo, myrikudo.get_addr(inte.first),
			myrikudo.get_addr(inte.second), inte.second - inte.first - 1);
		paths_map.insert({ inte, paths });
		std::cout << paths.size();
		std::cout << '\n';
		/*for (auto& pth : paths) {
			std::cout << "Path: ";
			for (auto& e : pth) {
				std::cout << " - " << e;
			}
			std::cout << '\n';
		}*/

	}
	std::set<int> used_blocks;
	std::vector<int> paths_idxs;
	search_coexistent_paths((int)intes.size(), intes.begin(), paths_map, used_blocks, paths_idxs, myrikudo, intes);
}

void solve_rikudo_1(rikudo& myrikudo) {
	//myrikudo.init();

	myrikudo.disp_crude();
	std::vector<std::pair<int, int>> intes;
	myrikudo.get_unfilled_intervals(intes);
	std::map<std::pair<int, int>, std::vector<std::vector<std::pair<int, int>>>> paths_map;
	for (auto& inte : intes) {
		std::cout << inte << ": ";
		std::vector<std::vector<std::pair<int, int>>> paths;
		paths = compute_paths_via_unused_blocks_of_length(myrikudo, myrikudo.get_addr(inte.first),
			myrikudo.get_addr(inte.second), inte.second - inte.first - 1);
		paths_map.insert({ inte, paths });
		std::cout << paths.size();
		std::cout << '\n';
		/*for (auto& pth : paths) {
			std::cout << "Path: ";
			for (auto& e : pth) {
				std::cout << " - " << e;
			}
			std::cout << '\n';
		}*/

	}

	// sorted intes
	std::sort(intes.begin(), intes.end(), [&](const std::pair<int, int> &a, const std::pair<int, int> &b) {return paths_map.at(a).size() < paths_map.at(b).size(); });

	std::cout << "Sorted intes:\n";
	for (auto& inte : intes) {
		std::cout << inte << ": " << paths_map.at(inte).size() << '\n';
	}


	std::set<int> used_blocks;
	std::vector<int> paths_idxs;
	search_coexistent_paths((int)intes.size(), intes.begin(), paths_map, used_blocks, paths_idxs, myrikudo, intes);
}



void use_path(rikudo& myrikudo, std::vector<std::pair<int, int>>& pth, std::pair<int,int> &inte) {
	
	int fill_val = inte.first + 1;
	for (auto& pe : pth) {
		
		myrikudo.use_block(pe.first, pe.second, fill_val, false);
		fill_val += myrikudo.fillable_blocks[pe.first].length;
	}
}

void unuse_path(rikudo& myrikudo, std::vector<std::pair<int, int>>& pth, std::pair<int, int>& inte) {

	int fill_val = inte.first + 1;
	for (auto& pe : pth) {

		myrikudo.unuse_block(pe.first, pe.second, fill_val, false);
		fill_val += myrikudo.fillable_blocks[pe.first].length;
	}
}

void solve_rikudo2(rikudo& myrikudo) {
	//myrikudo.init();

	myrikudo.disp_crude();
	std::vector<std::pair<int, int>> intes;
	myrikudo.get_unfilled_intervals(intes);

	std::map<std::pair<int, int>, std::vector<std::vector<std::pair<int, int>>>> paths_map;
	bool new_filled;
	std::set<int> used_blocks;
	do {
		new_filled = false;
		intes.clear();
		myrikudo.get_unfilled_intervals(intes);
		for (auto& inte : intes) {
			std::cout << inte << ": ";
			std::vector<std::vector<std::pair<int, int>>> paths;
			paths = compute_paths_via_unused_blocks_of_length(myrikudo, myrikudo.get_addr(inte.first),
				myrikudo.get_addr(inte.second), inte.second - inte.first - 1);
			if (paths.size() == 1) {
				// use the single path
				use_path(myrikudo, paths[0], inte);
				for (auto& pe : paths[0])
					used_blocks.insert(pe.first);
				new_filled = true;
			}
			paths_map.insert({ inte, paths });
			std::cout << paths.size();
			std::cout << '\n';
			/*for (auto& pth : paths) {
				std::cout << "Path: ";
				for (auto& e : pth) {
					std::cout << " - " << e;
				}
				std::cout << '\n';
			}*/

		}
	} while (new_filled);
	
	myrikudo.disp_crude();
	
	std::vector<int> paths_idxs;
	unsigned long long int itcount = 0;
	search_coexistent_paths2(itcount, (int)intes.size(), intes.begin(), paths_map, used_blocks, paths_idxs, myrikudo, intes);
}

void solve_rikudo3(rikudo& myrikudo) {
	//myrikudo.init();

	myrikudo.disp_crude();
	std::vector<std::pair<int, int>> intes;
	myrikudo.get_unfilled_intervals(intes);

	std::map<std::pair<int, int>, std::vector<std::vector<std::pair<int, int>>>> paths_map;
	bool new_filled;
	std::set<int> oo_used_blocks;
	do {
		new_filled = false;
		intes.clear();
		myrikudo.get_unfilled_intervals(intes);

		for (auto& inte : intes) {
			if (paths_map.find(inte) != paths_map.end()) {
				auto pths = paths_map.at(inte);
				pths.erase(
					std::remove_if(pths.begin(), pths.end(), [&](std::vector<std::pair<int, int>>& pth) {return !can_coeexist(oo_used_blocks, pth); }),
					pths.end()
				);
				std::cout << inte << ": ";
				std::cout << pths.size();
				std::cout << '\n';
				if (pths.size() == 1) {
					// use the single path
					use_path(myrikudo, pths[0], inte);
					for (auto& e : pths[0])
						oo_used_blocks.insert(e.first);
					new_filled = true;
				}
				//auto it = paths_map.at(inte).begin();
				//
				//for (auto& pth : paths_map.at(inte)) {
				//	if (!can_coeexist(oo_used_blocks, pth))

				//}
			}
			else {
				std::cout << inte << ": ";
				std::vector<std::vector<std::pair<int, int>>> paths;
				paths = compute_paths_via_unused_blocks_of_length(myrikudo, myrikudo.get_addr(inte.first),
					myrikudo.get_addr(inte.second), inte.second - inte.first - 1);
				if (paths.size() == 1) {
					// use the single path
					use_path(myrikudo, paths[0], inte);
					for (auto& e : paths[0])
						oo_used_blocks.insert(e.first);
					new_filled = true;
				}
				paths_map.insert({ inte, paths });
				std::cout << paths.size();
				std::cout << '\n';
			
				/*for (auto& pth : paths) {
					std::cout << "Path: ";
					for (auto& e : pth) {
						std::cout << " - " << e;
					}
					std::cout << '\n';
				}*/			
			}

		}
	} while (new_filled);

	myrikudo.disp_crude();
	std::set<int> used_blocks;
	std::vector<int> paths_idxs;
	//unsigned long long int itcount = 0;
	//search_coexistent_paths2(itcount, intes.size(), intes.begin(), paths_map, used_blocks, paths_idxs, myrikudo, intes);
	int max_possib_cnt = 0;
	std::pair<int, int> max_possib_inte;
	for (auto& inte : intes) {
		int tmp_siz = (int)paths_map.at(inte).size();
		if (tmp_siz > max_possib_cnt) {
			max_possib_cnt = tmp_siz;
			max_possib_inte = inte;
		}
	}


	//std::pair<int, int> p{ 46,59 };
	if (max_possib_cnt) {
		int cnt = 0;
		for (auto& pth : paths_map.at(max_possib_inte)) {
			cnt++;
			
			// cnt == 184 solution for my_rikudo
			// if (cnt >= 180 && cnt <= 190) {
			
			std::cout << cnt << "/" << max_possib_cnt << '\n';
			if (can_coeexist(oo_used_blocks, pth)) {
				use_path(myrikudo, pth, max_possib_inte);
				//myrikudo.disp_crude();
				prolong_path_with_blocks(myrikudo, { max_possib_inte.first, max_possib_inte.second });
				unuse_path(myrikudo, pth, max_possib_inte);
				//myrikudo.disp_crude();
			}
			//}
		}
	}
	else
		prolong_path_with_blocks(myrikudo, { 1, 1 });
}



int main()
{
	

    //std::cout << "Hello World!\n"; 
	//std::cout << field[0].value << " " << field[0].is_filled << " " << field[0].neighbours[0] << '\n';

	rikudo_shape small_field_shape{
		7,
		{4, 5, 6, 7, 6, 5, 4},
		{rikudo_shape::UL_type, rikudo_shape::UL_type,
		 rikudo_shape::UL_type, rikudo_shape::UR_type,
		 rikudo_shape::UR_type, rikudo_shape::UR_type,
		 rikudo_shape::ANY_type
		},
		{rikudo_shape::ANY_type,
		 rikudo_shape::DR_type, rikudo_shape::DR_type,
		 rikudo_shape::DR_type, rikudo_shape::DL_type,
		 rikudo_shape::DL_type, rikudo_shape::DL_type
		}
	};

	rikudo my_small_rikudo{
		small_field_shape,
		// forced_orders
		{
			{{0,2}, rikudo::UL}, {{1,2}, rikudo::DR }, // 1. unfilled block
			{{1,4}, rikudo::UR}, {{2,5}, rikudo::DL}, // 2. unfilled block
			{{2,4}, rikudo::UL}, {{3,4}, rikudo::DR}, // 3. unfilled block
			{{5,0}, rikudo::_R}, {{5,1}, rikudo::_L}, // 4. unfilled block
			{{6,0}, rikudo::_R}, {{6,1}, rikudo::_L | rikudo::_R}, {{6,2}, rikudo::_L} // 5. unfilled block
		},
		// non fillable
		{{3,3}},
		// forced values
		{
			{{1, 1}, 16}, {{1,3}, 10}, {{2,3}, 14}, {{3,1}, 21}, {{3,5}, 5},
			{{3,6}, 36}, {{4,0}, 24}, {{4,2}, 27}, {{4,3}, 1}, {{6,3}, 33}
		},
		36
	};

	/*
		30  31  32  33
		29  28  2  3  34
		24  25  27  1  4  35
		23  21  26  X  6  5  36
		22  20  15  14  7  8
		19  16  13  10  9
		18  17  12  11
	*/


	rikudo_shape field_shape{
		11,
		{8, 9, 8, 9, 8, 9, 8, 9, 8, 9, 8},
		{rikudo_shape::UL_type, rikudo_shape::UR_type,
		 rikudo_shape::UL_type, rikudo_shape::UR_type,
		 rikudo_shape::UL_type, rikudo_shape::UR_type,
		 rikudo_shape::UL_type, rikudo_shape::UR_type,
		 rikudo_shape::UL_type, rikudo_shape::UR_type,
		 rikudo_shape::ANY_type
		},
		{rikudo_shape::ANY_type,
		 rikudo_shape::DR_type, rikudo_shape::DL_type,
		 rikudo_shape::DR_type, rikudo_shape::DL_type,
		 rikudo_shape::DR_type, rikudo_shape::DL_type,
		 rikudo_shape::DR_type, rikudo_shape::DL_type,
		 rikudo_shape::DR_type, rikudo_shape::DL_type
		}
	};

	int row = 8, col = 7;

	auto ur_tile = field_shape.get_UR_tile(row, col);
	auto  r_tile = field_shape.get__R_tile (row, col);
	auto dr_tile = field_shape.get_DR_tile(row, col);
	auto dl_tile = field_shape.get_DL_tile(row, col);
	auto  l_tile = field_shape.get__L_tile (row, col);
	auto ul_tile = field_shape.get_UL_tile(row, col);

	std::cout << "UR(" << row << "," << col << ") = (" << ur_tile.first << "," << ur_tile.second << ")" << '\n';
	std::cout << " R(" << row << "," << col << ") = (" <<  r_tile.first << "," <<  r_tile.second << ")" << '\n';
	std::cout << "DR(" << row << "," << col << ") = (" << dr_tile.first << "," << dr_tile.second << ")" << '\n';
	std::cout << "DL(" << row << "," << col << ") = (" << dl_tile.first << "," << dl_tile.second << ")" << '\n';
	std::cout << " L(" << row << "," << col << ") = (" <<  l_tile.first << "," <<  l_tile.second << ")" << '\n';
	std::cout << "UL(" << row << "," << col << ") = (" << ul_tile.first << "," << ul_tile.second << ")" << '\n';

	rikudo my_rikudo{ field_shape,
			// forced_orders
			{ 
				{{0,2}, rikudo::_R}, {{0,3}, rikudo::_L }, 
				{{2,6}, rikudo::UR}, {{3,7}, rikudo::DL},
				{{4,5}, rikudo::_R}, {{4,6}, rikudo::_L}, 
				{{4,7}, rikudo::UR}, {{5,8}, rikudo::DL}, 
				{{5,2}, rikudo::_R}, {{5,3}, rikudo::_L},
				{{6,5}, rikudo::_R}, {{6,6}, rikudo::_L},
				{{7,8}, rikudo::UL}, {{8,7}, rikudo::UR | rikudo::DR },
				{{8,4}, rikudo::_R}, {{8,5}, rikudo::_L},
				{{9,6}, rikudo::UR}, {{9,8}, rikudo::DL}, {{10,6}, rikudo::DL}

			},
			// non fillable
			{{5,4}},
			// forced values
			{
				{{0, 0}, 1}, {{0,5}, 14}, {{1,0}, 3}, {{1,4}, 11}, {{1,7}, 17},
				{{3,5}, 26}, {{4,0}, 92}, {{4,3}, 33}, {{5,0}, 85}, {{6,4}, 59},
				{{7,7}, 42}, {{8,1}, 66}, {{9,0}, 78}, {{9,7}, 46}, {{10,2}, 75}, 
				{{10,3}, 72}
	
			},
			92
	};

	// medium www.rikudo-puzzle.com
	rikudo_shape medium_shape{
		9,
		{5, 6, 7, 8, 9, 8, 7, 6, 5},
		{rikudo_shape::UL_type, rikudo_shape::UL_type,
		 rikudo_shape::UL_type, rikudo_shape::UL_type,
		 rikudo_shape::UR_type, rikudo_shape::UR_type,
		 rikudo_shape::UR_type, rikudo_shape::UR_type,
		 rikudo_shape::ANY_type
		},
		{rikudo_shape::ANY_type,
		 rikudo_shape::DR_type, rikudo_shape::DR_type,
		 rikudo_shape::DR_type, rikudo_shape::DR_type,
		 rikudo_shape::DL_type, rikudo_shape::DL_type,
		 rikudo_shape::DL_type, rikudo_shape::DL_type
		}
	};
	
	rikudo my_medium_rikudo{
		medium_shape,
		// forced_orders
		{
			{{1,3}, rikudo::UR}, {{2,4}, rikudo::DL }, // 1. u_b
			{{3,1}, rikudo::UL}, {{4,1}, rikudo::DR }, // 2. u_b
			{{5,2}, rikudo::DR}, {{4,3}, rikudo::UL | rikudo::UR}, // 3. u_b 
			{{5,3}, rikudo::DL | rikudo::UR}, {{6,3}, rikudo::DL}, // ...
			{{4,7}, rikudo::UR}, {{5,7}, rikudo::DL}, // 4. u_b
			{{6,4}, rikudo::UL}, {{7,3}, rikudo::DR}, // 5. u_b
			{{7,0}, rikudo::UR}, {{8,0}, rikudo::DL}
		},
		// non fillable
		{ {4,4} },
		// forced values
			{
				{{1, 1}, 27}, {{1,5}, 17}, {{3,0}, 37}, {{3,3}, 33}, {{3,6}, 11},
				{{4,2}, 1}, {{4,6}, 10}, {{5,5}, 60}, {{6,5}, 58}, {{7,2}, 50},
				{{8,3}, 54}

			},
			60
	};

	// rikudo game - android
	/* Solution
	 9  8  33  34  35
	 10  7  6  32  31  36
	 11  2  1  5  30  27  37
	 60  12  3  4  29  28  26  38
	 59  13  15  17  X  21  22  25  39
	 58  14  16  18  20  23  24  40
	 57  55  54  19  46  45  41
	 56  52  53  47  44  42
	 51  50  49  48  43	
	*/
	rikudo my_medium_rikudo2{
		medium_shape,
		// forced_orders
		{
			{{0,1}, rikudo::_R}, {{0,2}, rikudo::_L }, // 1. u_b
			{{0,4}, rikudo::UR}, {{1,5}, rikudo::DL }, // 2. u_b
			{{2,0}, rikudo::DR}, {{1,0}, rikudo::UL | rikudo::UR}, {{2,1}, rikudo::DL}, // 3. u_b
			{{1,3}, rikudo::UR}, {{2,4}, rikudo::DL }, // 4. u_b
			{{3,3}, rikudo::UL}, {{4,3}, rikudo::DR} // 5. u_b
		},
		// non fillable
		{ {4,4} },
		// forced values
			{
				{{2, 5}, 45}, {{3,5}, 23}, {{4,2}, 15}, {{5,0}, 60}, {{5,4}, 29},
				{{6,2}, 1}, {{6,3}, 5}, {{6,6}, 37}, {{7,1}, 7}, {{7,4}, 31}

			},
			60
	};

#if 0
	{
		//test path
		// (3,5) -> (4,4) -> (3,4) -> (3,3) -> (4,2) -> (5,2) -> (6,2) -> (5,3) -> (4,3)
		my_rikudo.init_forced_values_inv();
		std::vector<std::pair<int, int>> myused_elements{ {4,4}, {3,4}, {3,3}, {4,2}, {5,2}, {6,2}, {5,3} };
		if (test_forced_connectivity(my_rikudo, { 3,5 }, { 4,3 }, myused_elements))
			std::cout << "OK";
		return 0;
	}
#endif

	
#if 0
	my_rikudo.init_forced_values_inv();
	std::vector<std::pair<int, int>> myused_elements;
	b_path_found = false;
	number_of_solutions = 0;
	int vmin = 26, vmax = 33;
	exists_path_of_length(vmax-vmin, myused_elements, my_rikudo, my_rikudo.get_addr(vmin), my_rikudo.get_addr(vmax), true);
	if (b_path_found)
		std::cout << "OK\n";
	std::cout << "Number of solutions: " << number_of_solutions << '\n';
	//std::cout << exists_path(my_rikudo, { 1, 3 }) << '\n';
	return 0;
#endif

#if 0
	// test directions
	{
		std::pair<int, int> elem{ 4,5 }, tile;
		tile = my_rikudo.shape.get_UR_tile(elem);
		std::cout << "UR: ";
		disp_pair(tile);
		std::cout << '\n';
		tile = my_rikudo.shape.get__R_tile(elem);
		std::cout << " R: ";
		disp_pair(tile);
		std::cout << '\n';
		tile = my_rikudo.shape.get_DR_tile(elem);
		std::cout << "DR: ";
		disp_pair(tile);
		std::cout << '\n';
		tile = my_rikudo.shape.get_DL_tile(elem);
		std::cout << "DL: ";
		disp_pair(tile);
		std::cout << '\n';
		tile = my_rikudo.shape.get__L_tile(elem);
		std::cout << " L: ";
		disp_pair(tile);
		std::cout << '\n';
		tile = my_rikudo.shape.get_UL_tile(elem);
		std::cout << "UL: ";
		disp_pair(tile);
		std::cout << '\n';

		return 0;
	}
#endif



	my_rikudo.check_forced_orders();

	//auto res_neigh = my_rikudo.get_unfilled_neighbours({ 1, 1 });
	auto res_neigh = my_rikudo.get_unfilled_neighbours({ 0, 0 });

	for (auto &e : res_neigh)
		std::cout << "(" << e.first.first << ", " << e.first.second << ") -> " << e.second << '\n';



	//std::cout << my_rikudo.are_neighbours({ 0,0 }, {2,0}) << '\n';
	
	//my_rikudo.init_forced_values_inv();


#if 0
	my_rikudo.init();
	v_min = v_max = 42;
	prolong_path_with_blocks(my_rikudo, { v_min,v_max });

/* Rikudo solution 

 77  76  75  72  71  50  48  47
 78  79  74  73  70  51  49  46  45
 80  66  67  69  52  53  54  44
 81  82  65  68  60  58  55  42  43
 84  83  64  61  59  57  56  41
 85  86  63  62  X  36  37  38  40
 92  87  88  33  35  25  24  39
 91  90  89  32  34  26  23  21  20
 4  5  31  29  28  27  22  19
 3  2  6  30  11  12  13  17  18
 1  7  8  9  10  14  15  16



*/
	
#endif

#if 0
	my_rikudo.init();
	// fill with unique path
	my_rikudo.filled_values.insert({ { 0,1 }, 2 });
	my_rikudo.filled_values_inv.insert({ 2, { 0,1 } });
	my_rikudo.fillable_blocks[0].used = true;

	//std::vector<std::pair<int, int>> intes;
	//my_rikudo.get_unfilled_intervals(intes);
	//for (auto& inte : intes) {
	//	std::cout << inte << ": ";
	//	int path_cnt = 0;
	//	std::cout << count_paths_via_unused_blocks_of_length(my_rikudo, my_rikudo.get_addr(inte.first),
	//		my_rikudo.get_addr(inte.second), inte.second - inte.first - 1);
	//	std::cout << '\n';
	//}
	
	v_min = v_max = 59;
	prolong_path_with_blocks(my_rikudo, { v_min,v_max });
#endif

#if 0
my_rikudo.init();
std::vector<std::pair<int, int>> intes;
my_rikudo.get_unfilled_intervals(intes);
std::map<std::pair<int, int>, std::vector<std::vector<std::pair<int, int>>>> paths_map;
for (auto& inte : intes) {	
	std::cout << inte << ": ";
	std::vector<std::vector<std::pair<int, int>>> paths;
	paths = compute_paths_via_unused_blocks_of_length(my_rikudo, my_rikudo.get_addr(inte.first),
		my_rikudo.get_addr(inte.second), inte.second - inte.first - 1);
	paths_map.insert({ inte, paths });
	std::cout << paths.size();
	std::cout << '\n';
	//for (auto& pth : paths) {
	//		std::cout << "Path: ";
	//		for (auto& e : pth) {
	//			std::cout << " - " << e;
	//		}
	//		std::cout << '\n';
	//}
	
}
std::set<int> used_blocks;
std::vector<int> paths_idxs;
search_coexistent_paths(intes.size(), intes.begin(), paths_map, used_blocks, paths_idxs);	
#endif

#if 0
my_small_rikudo.init();
//compute_paths_via_unused_blocks_of_length(my_small_rikudo, my_small_rikudo.get_addr(5), my_small_rikudo.get_addr(10), 4);
//return 0;
my_small_rikudo.disp_crude();
std::vector<std::pair<int, int>> intes;
my_small_rikudo.get_unfilled_intervals(intes);
std::map<std::pair<int, int>, std::vector<std::vector<std::pair<int, int>>>> paths_map;
for (auto& inte : intes) {
	std::cout << inte << ": ";
	std::vector<std::vector<std::pair<int, int>>> paths;
	paths = compute_paths_via_unused_blocks_of_length(my_small_rikudo, my_small_rikudo.get_addr(inte.first),
		my_small_rikudo.get_addr(inte.second), inte.second - inte.first - 1);
	paths_map.insert({ inte, paths });
	std::cout << paths.size();
	std::cout << '\n';
	for (auto& pth : paths) {
			std::cout << "Path: ";
			for (auto& e : pth) {
				std::cout << " - " << e;
			}
			std::cout << '\n';
	}

}
std::set<int> used_blocks;
std::vector<int> paths_idxs;
search_coexistent_paths(intes.size(), intes.begin(), paths_map, used_blocks, paths_idxs, my_small_rikudo, intes);
#endif



#if 0
	my_medium_rikudo.init();
	v_min = v_max = 37;

	

	prolong_path_with_blocks(my_medium_rikudo, { v_min,v_max });
#endif


#if 0
	// for debugging can_be_attached

	my_medium_rikudo.init();
	v_min = v_max = 37;

	/*
 47  48  49  54  55
 46  45  50  51  53  56
 42  43  44  6  52  58  57
 41  .  3  5  7  60  59  13
 40  39  1  4  X  8  10  12  14
 37  38  34  33  32  9  11  15
 36  35  28  29  31  18  16
 26  27  23  30  19  17
 25  24  22  21  20

Block 38=(5,1) cannot be attached, but it can be.
*/
	/*
	{{1, 1}, 27}, {{1,5}, 17}, {{3,0}, 37}, {{3,3}, 33}, {{3,6}, 11},
				{{4,2}, 1}, {{4,6}, 10}, {{5,5}, 60}, {{6,5}, 58}, {{7,2}, 50},
				{{8,3}, 54}
	*/

	for (auto& e : medium_correctly_filled) {
		if (!my_medium_rikudo.is_forced_element(e.first))
		{
			my_medium_rikudo.filled_values.insert(e);
			my_medium_rikudo.filled_values_inv.insert({ e.second, e.first });
		}
	}
	for (auto& b : my_medium_rikudo.fillable_blocks)
		b.used = true;

	/*my_medium_rikudo.filled_values.erase({ 5,1 });
	my_medium_rikudo.filled_values_inv.erase(2);
	my_medium_rikudo.fillable_blocks[22].used = false;*/
	my_medium_rikudo.unuse_block(22, true, 2, false);

	my_medium_rikudo.unuse_block(38, true, 3, false);
	//my_medium_rikudo.use_block(22, true, 2, false);


	my_medium_rikudo.disp_crude();

	//my_medium_rikudo.can_be_attached_all();
	//my_medium_rikudo.can_be_attached(38);

	//v_min = v_max = 3;
	//prolong_path_with_blocks(my_medium_rikudo, { v_min,v_max });
	// must be already initialized();
	solve_rikudo(my_medium_rikudo);
#endif
	


#if 0
	my_small_rikudo.init();
	v_min = v_max = 16;
	
	/*
	 .  .  .  33
 .  .  .  .  .
 24  .  27  1  .  .
 .  21  .  X  .  5  36
 .  .  15  14  .  .
 19  16  13  10  .
 18  17  12  .

 {{1, 1}, 16}, {{1,3}, 10}, {{2,3}, 14}, {{3,1}, 21}, {{3,5}, 5},
			{{3,6}, 36}, {{4,0}, 24}, {{4,2}, 27}, {{4,3}, 1}, {{6,3}, 33}

	*/

	my_small_rikudo.filled_values.insert({ {0,0}, 18 });
	my_small_rikudo.filled_values_inv.insert({ 18, {0,0} });
	my_small_rikudo.filled_values.insert({ {0,1}, 17 });
	my_small_rikudo.filled_values_inv.insert({ 17, {0,1} });
	my_small_rikudo.filled_values.insert({ {0,2}, 12 });
	my_small_rikudo.filled_values_inv.insert({ 12, {0,2} });
	my_small_rikudo.filled_values.insert({ {1,0}, 19 });
	my_small_rikudo.filled_values_inv.insert({ 19, {1,0} });
	my_small_rikudo.filled_values.insert({ {1,2}, 13 });
	my_small_rikudo.filled_values_inv.insert({ 13, {1,2} });
	my_small_rikudo.filled_values.insert({ {2,2}, 15 });
	my_small_rikudo.filled_values_inv.insert({ 15, {2,2} });
	// these are in the blocks
	//  (0,0) - 0, (0,1) - 1, (0,2)-(1,2) - 15, 
	//  (1,0) - 3, (2,2) - 6
	my_small_rikudo.fillable_blocks[0].used = true;
	my_small_rikudo.fillable_blocks[1].used = true;
	my_small_rikudo.fillable_blocks[15].used = true;
	my_small_rikudo.fillable_blocks[3].used = true;
	my_small_rikudo.fillable_blocks[6].used = true;

	bool b_f = false;
	std::vector<int> b_bs;
	std::vector<std::pair<int, int>> b_be;
	exists_path_via_unused_blocks_of_length_rec(1, b_bs, b_be, my_small_rikudo, { 0,2 }, { 1,3 },  b_f, false);
	std::cout << "b_f: " << b_f << '\n';
	for (int b : b_bs)
		std::cout << " " << b;
	std::cout << '\n';
	for (auto &e : b_be)
		std::cout << " " << e;
	std::cout << '\n';

	//return 0;


	prolong_path_with_blocks(my_small_rikudo, { v_min,v_max });
	//prolong_path(my_small_rikudo, { v_min,v_max });
#endif

#if 0
	my_small_rikudo.init();
	v_min = v_max = 16;
	prolong_path_with_blocks(my_small_rikudo, { v_min,v_max });
#endif

#if 0
	my_small_rikudo.init();
	solve_rikudo3(my_small_rikudo);
#endif

#if 0
// cnt == 177 solution
	my_medium_rikudo.init();
	solve_rikudo3(my_medium_rikudo);
#endif

#if 0
	my_medium_rikudo2.init();
	solve_rikudo3(my_medium_rikudo2);
#endif

#if 0
	my_rikudo.init();
	solve_rikudo3(my_rikudo);
#endif

#if 0
	my_small_rikudo.init();
	solve_rikudo_1(my_small_rikudo);
#endif

#if 0
	my_medium_rikudo.init();
	solve_rikudo_1(my_medium_rikudo);
#endif

#if 0
	my_medium_rikudo2.init();
	solve_rikudo_1(my_medium_rikudo2);
#endif

//#if 0
	my_rikudo.init();
	solve_rikudo_1(my_rikudo);
//#endif


#if 0
	// test compute paths between filled
	// problem with some blocks of length 2
	rikudo test_small_rikudo{
		{
			2,
			{2, 2},
			{rikudo_shape::UL_type,
			 rikudo_shape::ANY_type
			},
			{rikudo_shape::ANY_type,
			 rikudo_shape::DR_type
			}		
		},
		// forced_orders
		{
			{{0,0}, rikudo::hex_dirs::UR}, {{1,1}, rikudo::hex_dirs::DL}
		},
		// non fillable
		{},
		// forced values
		{
			{{1, 0}, 1}, {{0,1}, 4}
		},
		4
	};

	test_small_rikudo.init();
	compute_paths_via_unused_blocks_of_length(test_small_rikudo, test_small_rikudo.get_addr(1), test_small_rikudo.get_addr(4), 2);
#endif
	
	//my_small_rikudo.init();
	//solve_rikudo(my_small_rikudo);
	
	/*my_medium_rikudo.init();
	solve_rikudo(my_medium_rikudo);*/
	
	//my_rikudo.init();
	//my_rikudo.use_block(0, true, 2, false);
	//solve_rikudo(my_rikudo);


#if 0
	my_medium_rikudo.init();
	v_min = v_max = 37;



	prolong_path_with_blocks(my_medium_rikudo, { v_min,v_max });
#endif
}





//bool prolong_path_up()
//bool prolong_path_down()



/*
 
 Prolong path:
	filled element of value v:
	a) unfilled v-1 and v+1
		no forced directions:
			try to fill v-1, v+1 to pairs of o_i, o_j
		1 forced direction:
			d1 - o1, o2, ..., ok
			try to fill v-1 to d1, v+1 to o1, ..., ok
			try to fill v+1 to d1, v-1 to o1, ..., ok
		2 forced directions:
			d1 d2, try to fill: 
			           v-1 in d1 and v+1 in d2 or
					   v-1 in d2 and v+1 in d1 

	b) unfilled v-1 but filled v+1
		no forced directions:
			try to fill v-1 to o1, ..., ok
		1 forced directon (to unfilled)
		    fill v-1 to it
	c) filled v-1 but unfilled v+1
		no forced directions:
			try to fill v+1 to o1, ..., ok
		1 forced directon (to unfilled)
			fill v+1 to it

	d) both v-1 and v+1 filled


 */

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

