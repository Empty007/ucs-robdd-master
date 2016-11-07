//
// ExhaustiveSearch.cpp -- implementation of the class "ExhaustiveSearch".
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

#include "UCES.h"


UCES::UCES ()
{
	cost_function = NULL;
}


UCES::~UCES ()
{

}

// get_minima_list return the local minima, and we run this algorithm n times
//
void UCES::dfs (ElementSubset * X) {
//    cout << "start dfs" << endl;
    X->cost = cost_function->cost (X);  
//    cout << "X cost = " << X->cost << endl;
    
	int n = set->get_set_cardinality ();

	ElementSubset * Y; 
    Y = new ElementSubset("", set);

    bool Neighbors[n];
    int cntneighbors = 0;
    for (int j = 0; j < n; j++) {
        Neighbors[j] = false;
        Y = new ElementSubset ("", set);
        Y->copy(X);
        if (X->has_element(j)) 
            Y->remove_element(j);
        else 
            Y->add_element(j);


        Y->cost = cost_function->cost (Y);
//        cout << Y->cost << " " << X->cost << endl;
//        cout << "Y cost = " << Y->cost << endl;
        if (Y->cost < X->cost) {
            cntneighbors++;
            Neighbors[j] = true;
        }
        delete Y;
    }

//    cout << cntneighbors << endl;
    if (cntneighbors == 0) return ;

    int aleatory_choose = rand()%cntneighbors;
    int vis = 0;
//    cout << "watching neighbors" << endl;
    for (int j = 0; j < n; j++) if (Neighbors[j]) {
//        cout << j << endl;
        if (aleatory_choose == vis) {
//            cout << j << " " << aleatory_choose << " " << vis << endl;
            if (X->has_element(j)) 
                X->remove_element(j);
            else 
                X->add_element(j);
            break;
            //X = Y
        }
        vis++;
    }
////    cout << "end dfs" << endl;
    dfs(X);
}

void UCES::get_minima_list (unsigned int max_size_of_minima_list)
{
	timeval begin_program, end_program;
	gettimeofday (& begin_program, NULL);

	ElementSubset * X;
	int n = set->get_set_cardinality ();

    int cnt_size_of_minima_list = 0;

    do {

        X = new ElementSubset("X", set);
        X->set_empty_subset (); // X starts with empty set

        int aleatory_subset = rand()%(1<<n);
        for (int i = 0; i < n; i++) {
            if (aleatory_subset & (1<<i))
                X->add_element(i);
        }

        dfs(X);

        list_of_minima.push_back (X);

        cnt_size_of_minima_list++;
    } while (cnt_size_of_minima_list < max_size_of_minima_list);

	clean_list_of_minima (max_size_of_minima_list);

	// Exhaustive search, if implemented keeping just an element of minimum cost,
	// needs to compute the cost function 2^|S| times.
	//
	number_of_visited_subsets =  cost_function->get_number_of_calls_of_cost_function ();


	gettimeofday (& end_program, NULL);
	elapsed_time_of_the_algorithm = diff_us (end_program, begin_program);

}

void UCES::get_steps (vector <int> &results, vector <int> &positions, unsigned int max_size_of_minima_list) {

	timeval begin_program, end_program;
	gettimeofday (& begin_program, NULL);


    // find all the costs and then sort them
	ElementSubset XX ("XX", set);
	int i;
	int n = (int) set->get_set_cardinality ();

    vector <int> Costs;

	XX.set_empty_subset (); // X starts with empty set

    int cnt = 0;
	do  // Amortized time per iteration is O(1) + O(f(n))
	{
        cnt++;
		i = 0;
		while ((i < n) && (XX.has_element (i)))
		{
			XX.remove_element (i);
			i++;
		}
		if (i < n)
			XX.add_element (i);

		if (store_visited_subsets)
			list_of_visited_subsets->add_subset (&XX);

        Costs.push_back(cost_function->cost (&XX));
//        cout << X.print_subset () <<  "cost: " << X.cost << endl;
        //add cost

	}
	while ( (i < n) );
//    cout << cnt << endl;
//

    sort(Costs.begin(), Costs.end());
    
    sort(positions.begin(), positions.end());

    for (i = 0; i < positions.size(); i++) {
        cout << positions[i] << " " << Costs[i] << "\n";
    }

    //initiate results
    int max_value = (1<<30); //2^30
    results = vector <int> (positions.size(), (max_value)); //high value

	ElementSubset * X;

    int cnt_size_of_minima_list = 0;

//    for (int k = 0; k < 100; k++) {
//        cout << rand()%10000 << endl;
//    }

    int aleatory_subset;

    for (cnt_size_of_minima_list = 0; i < max_size_of_minima_list; i++) {

        X = new ElementSubset("X", set);
        X->set_empty_subset (); // X starts with empty set


//        for (int k = 0; k < 100; k++) {
//            cout << rand()%10000 << endl;
//        }
        aleatory_subset = rand()%(1<<n);
        cout << cnt_size_of_minima_list << " " << aleatory_subset << endl;

//        cout << "aleatory " << rand()%1024 << " " << (1<<n) << " " << aleatory_subset << "\n";
        for (int i = 0; i < n; i++) {
            if (aleatory_subset & (1<<i))
                X->add_element(i);
        }

        dfs(X);

        list_of_minima.push_back (X);
        
        for (i = 0; i < positions.size(); i++) {
//            cout << i << " " << X->cost << " " << Costs.size() << endl;
            if (X->cost <= Costs[positions[i]]) {
                results[i] = min(cnt_size_of_minima_list, results[i]);
            }
        }

        cnt_size_of_minima_list++;

        if (results[0] != max_value) break;

    } 

    for (i = 0; i < results.size(); i++) {
        cout << "position i = " << i << " result = " << results[i] << " cost = " << Costs[i] << endl;
    }

	clean_list_of_minima (max_size_of_minima_list);

	// Exhaustive search, if implemented keeping just an element of minimum cost,
	// needs to compute the cost function 2^|S| times.
	//
	number_of_visited_subsets =  cost_function->get_number_of_calls_of_cost_function ();

	gettimeofday (& end_program, NULL);
	elapsed_time_of_the_algorithm = diff_us (end_program, begin_program);

}
