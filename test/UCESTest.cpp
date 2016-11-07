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
//		cout << uces1.print_list_of_minima () << "\n";
//		cout << uces1.print_search_report () << "\n";
//		cout << uces1.print_list_of_visited_subsets () << "\n";
        uces2.set_parameters (&c2, &set2, false);
		uces2.get_minima_list (3);
//		cout << uces2.print_list_of_minima () << "\n";
//		cout << uces2.print_search_report () << "\n";
//		cout << uces2.print_list_of_visited_subsets () << "\n";
		uces3.set_parameters (&c3, &set3, false);
		uces3.get_minima_list (1);
//		cout << uces3.print_list_of_minima () << "\n";
//		cout << uces3.print_search_report () << "\n";
//		cout << uces3.print_list_of_visited_subsets () << "\n";
        return true;
	}

    bool check_results() {
        ElementSet set1 ("set", "input/UCSTest13ElementsFileA.xml");
        ElementSet set2 ("set", "input/UCSTest13ElementsFileB.xml");
        ElementSet set3 ("set", "input/UCSTest14ElementsFileA.xml");
		UCES uces1;
		UCES uces2;
		UCES uces3;
		MeanAbsSum c1 (&set1);
		MeanAbsSum c2 (&set2);
		MeanAbsSum c3 (&set3);
		uces1.set_parameters (&c1, &set1, false);
        vector <int> positions(3), results;
        positions[0] = 0;
        positions[1] = 2;
        positions[2] = 4;
        uces1.get_steps(results, positions, 1000);

        return true;
    }

} // end of namespace
