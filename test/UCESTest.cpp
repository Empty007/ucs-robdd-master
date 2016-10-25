//
// UCESTest.cpp -- implementation of the namespace "UCESTest".
//
//    This file is part of the featsel program
//    Copyright (C) 2010  Marcelo S. Reis
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "UCESTest.h"

namespace UCESTest
{

	bool check_number_of_minima() {
		ElementSet set1 ("set", "input/CostFunctionTest3ElementsFile.xml");
		ElementSet set2 ("set", "input/UCSTest9ElementsFileA.xml");
		ElementSet set3 ("set", "input/UCSTest7ElementsFileA.xml");
		UCES uces1;
		UCES uces2;
		UCES uces3;
		MeanAbsSum c1 (&set1);
		MeanAbsSum c2 (&set2);
		HammingDistance c3 (&set3);
		uces1.set_parameters (&c1, &set1, false);
		uces1.get_minima_list (1);
		if (uces1.print_list_of_minima ().find("<010>") == string::npos)
			return false;
		uces2.set_parameters (&c2, &set2, false);
		uces2.get_minima_list (3);
		if ((uces2.print_list_of_minima ().find ("<000010000>") == string::npos) ||
		    (uces2.print_list_of_minima ().find ("<100100000>") == string::npos) ||
			(uces2.print_list_of_minima ().find ("<011000000>") == string::npos) )
			return false;
		uces3.set_parameters (&c3, &set3, false);
		uces3.get_minima_list (1);
		if (uces3.print_list_of_minima ().find ("<0011100>") == string::npos)
			return false;
		return true;

	}

} // end of namespace
