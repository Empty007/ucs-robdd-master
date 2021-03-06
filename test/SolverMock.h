//
// SolverMock.h -- definition of the mock class "SolverMock".
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

// A class to create mock objects, in order to test the abstract class "Solver"

#ifndef SOLVER_MOCK_H_
#define SOLVER_MOCK_H_

#include "../src/global.h"
#include "../src/Solver.h"

class SolverMock : public Solver
{

public:

	void get_minima_list (unsigned int);

};

#endif /* SOLVER_MOCK_H_ */
