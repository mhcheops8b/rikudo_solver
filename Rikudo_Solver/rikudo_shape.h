#pragma once

struct rikudo_shape
{
	// possibly enum
	static const int ANY_type = 0;
	static const int UL_type = 1;
	static const int UR_type = 2;
	static const int DL_type = 3;
	static const int DR_type = 4;
	int rows;
	// numbers of tiles in each row
	std::vector<int> row_sizes;
	// tiles of (row + 1) start are connected
	// at UL or UR part of row
	std::vector<int> row_connection_up_types;
	// tiles of (row - 1) start are connected
	// at DL or DR part of row
	std::vector<int> row_connection_down_types;

	// 
	bool check_coords(int row, int col) const;
	std::pair<int, int> get_UR_tile(int row, int col) const;
	std::pair<int, int> get__R_tile(int row, int col) const;
	std::pair<int, int> get_DR_tile(int row, int col) const;
	std::pair<int, int> get_DL_tile(int row, int col) const;
	std::pair<int, int> get__L_tile(int row, int col) const;
	std::pair<int, int> get_UL_tile(int row, int col) const;

	std::pair<int, int> get_UR_tile(const std::pair<int, int>& elem) const;
	std::pair<int, int> get__R_tile(const std::pair<int, int>& elem) const;
	std::pair<int, int> get_DR_tile(const std::pair<int, int>& elem) const;
	std::pair<int, int> get_DL_tile(const std::pair<int, int>& elem) const;
	std::pair<int, int> get__L_tile(const std::pair<int, int>& elem) const;
	std::pair<int, int> get_UL_tile(const std::pair<int, int>& elem) const;

	// 0 = UR, 1 = _R, 2 = DR, 3 = DL, 4 = _L, 5 = UL
	// opposite direction: 5 - dir
	std::pair<int, int> get_tile_in_dir(int row, int col, int direction) const;
	std::pair<int, int> get_tile_in_dir(const std::pair<int, int>& elem, int direction) const;

};
