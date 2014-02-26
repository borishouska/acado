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


double dAtan(double x){
  return 1/(1+x*x);
}


double ddAtan(double x){
  double v1 = 1+x*x;
  return -2*x/v1/v1;
}

BEGIN_NAMESPACE_ACADO


Atan::Atan():UnaryOperator(){
  cName = "atan";

  fcn = &atan;
  dfcn = &dAtan;
  ddfcn = &ddAtan;

  operatorName = ON_ATAN;

}

Atan::Atan( Operator *_argument ):UnaryOperator(_argument){
  cName = "atan";

  fcn = &atan;
  dfcn = &dAtan;
  ddfcn = &ddAtan;

  operatorName = ON_ATAN;
}


Atan::Atan( const Atan &arg ):UnaryOperator(arg){
  cName = "atan";

  fcn = &atan;
  dfcn = &dAtan;
  ddfcn = &ddAtan;

  operatorName = ON_ATAN;
}


Atan::~Atan(){

}


Atan& Atan::operator=( const Atan &arg ){

  UnaryOperator::operator=(arg);

  return *this;
}


returnValue Atan::evaluate( EvaluationBase *x ){
 
    x->Atan(*argument);
    return SUCCESSFUL_RETURN;
}


Operator* Atan::substitute( int index, const Operator *sub ){

    return new Atan( argument->substitute( index , sub ) );

}

Operator* Atan::clone() const{

    return new Atan(*this);
}

returnValue Atan::initDerivative() {

	if( derivative != 0 && derivative2 != 0 ) return SUCCESSFUL_RETURN;

	TreeProjection der, der2;
	der = Quotient(
			new DoubleConstant( 1.0 , NE_ONE ),
			new Addition(
					new DoubleConstant( 1.0 , NE_ONE ),
					new Power_Int(
							argument->clone(),
							2
					)
			)
	);
	der2 = Product( new DoubleConstant( -2.0 , NE_NEITHER_ONE_NOR_ZERO ),
			new Product(
					new Power(
							new Addition(
									new DoubleConstant(1.0 , NE_ONE),
									new Power_Int(
											argument->clone(),
											2
									)
							),
							new DoubleConstant( -2.0 , NE_NEITHER_ONE_NOR_ZERO )
					),
					argument->clone()
			)
	);

	derivative = der.clone();
	derivative2 = der2.clone();

	return SUCCESSFUL_RETURN;
}


CLOSE_NAMESPACE_ACADO

// end of file.
