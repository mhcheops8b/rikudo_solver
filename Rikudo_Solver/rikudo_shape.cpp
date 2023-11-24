//#include "pch.h"
#include <vector>
#include <iostream>
#include "rikudo_shape.h"

rikudo_shape::rikudo_shape()
{
	rows = 0;
	row_sizes.clear();
	row_connection_up_types.clear();
	row_connection_down_types.clear();
}

// tests whether (row, col) is in board
bool rikudo_shape::check_coords(int row, int col) const
{
	if (row < 0 || row >= rows || col < 0 || col >= row_sizes[row])
		return false;

	return true;
}

std::pair<int, int> rikudo_shape::get_UR_tile(int row, int col) const
{
	if (row < rows - 1)
	{

		int row_res = row + 1,
			col_res = col;

		if (row_connection_up_types[row] == rikudo_shape::UL_type)
			++col_res;


		//return { row_res, col_res };
		// check ? here or when used TODO
		if (check_coords(row_res, col_res))
			return { row_res, col_res };
	}

	return { -1, -1 };
}

std::pair<int, int> rikudo_shape::get__R_tile(int row, int col) const
{
	int row_res = row,
		col_res = col + 1;

	//return { row_res, col_res };
	// check ? here or when used TODO
	if (check_coords(row_res, col_res))
		return { row_res, col_res };
	else
		return { -1, -1 };
}

std::pair<int, int> rikudo_shape::get_DR_tile(int row, int col) const
{
	if (row > 0)
	{
		int row_res = row - 1,
			col_res = col;

		if (row_connection_down_types[row] == rikudo_shape::DL_type)
			col_res++;

		//return { row_res, col_res };
		// check ? here or when used TODO
		if (check_coords(row_res, col_res))
			return { row_res, col_res };
	}

	return { -1, -1 };
}

std::pair<int, int> rikudo_shape::get_DL_tile(int row, int col) const
{
	if (row > 0)
	{
		int row_res = row - 1,
			col_res = col;

		if (row_connection_down_types[row] == rikudo_shape::DR_type)
			col_res--;

		//return { row_res, col_res };
		// check ? here or when used TODO
		if (check_coords(row_res, col_res))
			return { row_res, col_res };
	}

	return { -1, -1 };
}


std::pair<int, int> rikudo_shape::get__L_tile(int row, int col) const
{
	int row_res = row,
		col_res = col - 1;

	//return { row_res, col_res };
	// check ? here or when used TODO
	if (check_coords(row_res, col_res))
		return { row_res, col_res };
	else
		return { -1, -1 };
}

std::pair<int, int> rikudo_shape::get_UL_tile(int row, int col) const
{
	if (row < rows - 1)
	{
		int row_res = row + 1,
			col_res = col;

		if (row_connection_up_types[row] == rikudo_shape::UR_type)
			col_res--;

		//return { row_res, col_res };
		// check ? here or when used TODO
		if (check_coords(row_res, col_res))
			return { row_res, col_res };
	}

	return { -1, -1 };
}

std::pair<int, int> rikudo_shape::get_UR_tile(const std::pair<int, int>& elem) const
{
	return get_UR_tile(elem.first, elem.second);
}

std::pair<int, int> rikudo_shape::get__R_tile(const std::pair<int, int>& elem) const
{
	return get__R_tile(elem.first, elem.second);
}

std::pair<int, int> rikudo_shape::get_DR_tile(const std::pair<int, int>& elem) const
{
	return get_DR_tile(elem.first, elem.second);
}

std::pair<int, int> rikudo_shape::get_DL_tile(const std::pair<int, int>& elem) const
{
	return get_DL_tile(elem.first, elem.second);
}

std::pair<int, int> rikudo_shape::get__L_tile(const std::pair<int, int>& elem) const
{
	return get__L_tile(elem.first, elem.second);
}

std::pair<int, int> rikudo_shape::get_UL_tile(const std::pair<int, int>& elem) const
{
	return get_UL_tile(elem.first, elem.second);
}

std::pair<int, int> rikudo_shape::get_tile_in_dir(int row, int col, int direction) const
{
	switch (direction) {
	case 0:
		// UR
		return get_UR_tile(row, col);
	case 1:
		// _R
		return get__R_tile(row, col);
	case 2:
		// DR
		return get_DR_tile(row, col);
	case 3:
		// DL
		return get_DL_tile(row, col);
	case 4:
		// _L
		return get__L_tile(row, col);
	case 5:
		// UL
		return get_UL_tile(row, col);
	default:
		std::cerr << "Error: Incorrect direction.\n";
		return { -1, -1 };
	}
}

std::pair<int, int> rikudo_shape::get_tile_in_dir(const std::pair<int, int>& elem, int direction) const
{
	switch (direction) {
	case 0:
		// UR
		return get_UR_tile(elem);
	case 1:
		// _R
		return get__R_tile(elem);
	case 2:
		// DR
		return get_DR_tile(elem);
	case 3:
		// DL
		return get_DL_tile(elem);
	case 4:
		// _L
		return get__L_tile(elem);
	case 5:
		// UL
		return get_UL_tile(elem);
	default:
		std::cerr << "Error: Incorrect direction.\n";
		return { -1, -1 };
	}
}

void rikudo_shape::add_row(int no_elems, int up_conn_type, int down_conn_type)
{
	rows++;
	row_sizes.push_back(no_elems);
	row_connection_up_types.push_back(up_conn_type);
	row_connection_down_types.push_back(down_conn_type);
}
