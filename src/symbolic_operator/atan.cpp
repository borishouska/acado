/*
 *    This file is part of ACADO Toolkit.
 *
 *    ACADO Toolkit -- A Toolkit for Automatic Control and Dynamic Optimization.
 *    Copyright (C) 2008-2014 by Boris Houska, Hans Joachim Ferreau,
 *    Milan Vukov, Rien Quirynen, KU Leuven.
 *    Developed within the Optimization in Engineering Center (OPTEC)
 *    under supervision of Moritz Diehl. All rights reserved.
 *
 *    ACADO Toolkit is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    ACADO Toolkit is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with ACADO Toolkit; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */



/**
*    \file src/symbolic_operator/atan.cpp
*    \author Boris Houska, Hans Joachim Ferreau
*    \date 2008
*/


#include <acado/utils/acado_utils.hpp>
#include <acado/symbolic_operator/symbolic_operator.hpp>


BEGIN_NAMESPACE_ACADO


Atan::Atan():UnaryOperator(){}

Atan::Atan( const SharedOperator &_argument ):UnaryOperator(_argument,"atan"){}

Atan::Atan( const Atan &arg ):UnaryOperator(arg){}

Atan::~Atan(){}

uint Atan::evaluate( EvaluationBase *x, std::vector<uint> &indices, uint base ) {

    x->Atan(indices[base], indices[base+1]);
    return base+2;
}


SharedOperator Atan::substitute( SharedOperatorMap &sub ){

    return SharedOperator( new Atan( argument->substitute(sub) ));
}


returnValue Atan::initDerivative() {

	if( derivative != 0 && derivative2 != 0 ) return SUCCESSFUL_RETURN;

	derivative = convert2TreeProjection(
			SharedOperator( new Quotient(
					SharedOperator( new DoubleConstant( 1.0 , NE_ONE )),
					SharedOperator( new Addition(
							SharedOperator( new DoubleConstant( 1.0 , NE_ONE )),
							SharedOperator( new Power_Int(
									argument,
									2
							))
					))
			)));
	derivative2 = convert2TreeProjection(
			SharedOperator( new Product( SharedOperator( new DoubleConstant( -2.0 , NE_NEITHER_ONE_NOR_ZERO )),
					SharedOperator( new Product(
							SharedOperator( new Power(
									SharedOperator( new Addition(
											SharedOperator( new DoubleConstant(1.0 , NE_ONE)),
											SharedOperator( new Power_Int(
													argument,
													2
											))
									)),
									SharedOperator( new DoubleConstant( -2.0 , NE_NEITHER_ONE_NOR_ZERO ))
							)),
							argument
					))
			)));

	return argument->initDerivative();
}


CLOSE_NAMESPACE_ACADO

// end of file.
