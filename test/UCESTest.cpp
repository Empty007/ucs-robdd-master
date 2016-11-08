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

    //always run nroLocalMinima before get_steps
    //always run nroLocalMinima before get_steps
    //always run nroLocalMinima before get_steps
    //always run nroLocalMinima before get_steps

	bool check_number_of_minima() { //past tests, doesnt work now
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

        int n = 25;

        string arr[] = {
        "input/UCS2bTest5ElementsFileA.xml", 
        "input/UCS2bTest5ElementsFileB.xml",
        "input/UCS2bTest6ElementsFileA.xml",
        "input/UCS2bTest6ElementsFileB.xml",
        "input/UCS2bTest9ElementsFileA.xml",
        "input/UCSTest4ElementsFileA.xml",
        "input/UCSTest4ElementsFileB.xml", 
        "input/UCSTest5ElementsFileA.xml",
        "input/UCSTest6ElementsFileA.xml",
        "input/UCSTest6ElementsFileB.xml",
        "input/UCSTest7ElementsFileA.xml",
        "input/UCSTest7ElementsFileB.xml",
        "input/UCSTest7ElementsFileC.xml",
        "input/UCSTest7ElementsFileD.xml",
        "input/UCSTest9ElementsFileA.xml",
        "input/UCSTest9ElementsFileB.xml",
        "input/UCSTest10ElementsFileA.xml",
        "input/UCSTest11ElementsFileA.xml",
        "input/UCSTest13ElementsFileA.xml",
        "input/UCSTest13ElementsFileB.xml",
        "input/UCSTest14ElementsFileA.xml",
        "input/UCSTest15ElementsFileA.xml",
        "input/UCSTest17ElementsFileA.xml",
        "input/UCSTest19ElementsFileA.xml",
        "input/UCSTest21ElementsFileA.xml"
        };
        vector <string> S(arr, arr+25);

        vector <int> positions(5), results;
        positions[0] = 0;
        positions[1] = 1;
        positions[2] = 2;
        positions[3] = 4;
        positions[4] = 9;


        UCES uces;
        for (int i = 0; i < n; i++) {
            cout << S[i] << endl;
            ElementSet pset("set", S[i]);
            MeanAbsSum pc (&pset);
            uces.set_parameters (&pc, &pset, false);
            int nset = pset.get_set_cardinality ();
            cout << "size of the set = " << nset << endl;
            vector <int> Costs;
            int nMinima = uces.nLocalMinima(Costs);
            cout << "number of Local Minima = " << nMinima << endl;
            double media = 0;
            int iterations = 20, nresults = positions.size();
            vector <double> mediaResults(nresults, 0.0);
            for (int j = 0; j < iterations; j++) {
                media += uces.get_steps(Costs, results, positions, 1000);
                for (int k = 0; k < nresults; k++) {
                    mediaResults[k] += results[k];
                }
            }

            for (int k = 0; k < nresults; k++) {
                mediaResults[k] /= iterations;
//                cout << "Media of results position = " << positions[k]+1 << " result = " << mediaResults[k] << endl;
            }


            double mediaSearchingMinima = media*1.0/iterations;
            cout << "media of searching minima " << mediaSearchingMinima << endl;
            for (int j = 0; j < nresults; j++) {
                double muT = nMinima*1.0/(1<<nset);
                double epsilon = (positions[j]+1)*1.0/(1<<nset);
                double log1d = log(1.0/0.001); //delta 0.1%, 1-delta = 99.9%
                double lowerbound = muT/epsilon*log1d;
                double upperbound = 1.0/epsilon*log1d;
                cout << "Expected values for position=" << positions[j]+1 << 
                    ", lower bound= " << lowerbound << 
                    ", upper bound= " << upperbound << 
                    ", media real value = " << mediaResults[j] << 
                    ", media of nodes visited = " << mediaResults[j]*mediaSearchingMinima << endl;
            }
        }
        
//        ElementSet set1 ("set", "input/UCSTest13ElementsFileA.xml");
//        ElementSet set2 ("set", "input/UCSTest13ElementsFileB.xml");
//        ElementSet set3 ("set", "input/UCSTest14ElementsFileA.xml");
//		UCES uces1;
//		UCES uces2;
//		UCES uces3;
//		MeanAbsSum c1 (&set1);
//		MeanAbsSum c2 (&set2);
//		MeanAbsSum c3 (&set3);
//		uces1.set_parameters (&c1, &set1, false);
//        uces1.get_steps(results, positions, 1000);
//        uces1.set_parameters(&c2, &set2, false);
//        uces1.get_steps(results, positions, 1000);

        return true;
    }

} // end of namespace
