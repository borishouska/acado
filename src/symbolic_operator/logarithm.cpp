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
 *    \file src/symbolic_operator/logarithm.cpp
 *    \author Boris Houska, Hans Joachim Ferreau
 *    \date 2008
 */


#include <acado/utils/acado_utils.hpp>
#include <acado/symbolic_operator/symbolic_operator.hpp>


double dLogarithm(double x){
  return 1/x;
}


double ddLogarithm(double x){
  return -1/x/x;
}

BEGIN_NAMESPACE_ACADO


Logarithm::Logarithm():UnaryOperator(){
  cName = "log";

  fcn = &log;
  dfcn = &dLogarithm;
  ddfcn = &ddLogarithm;

  operatorName = ON_LOGARITHM;

}

Logarithm::Logarithm( Operator *_argument ):UnaryOperator(_argument){
  cName = "log";

  fcn = &log;
  dfcn = &dLogarithm;
  ddfcn = &ddLogarithm;

  operatorName = ON_LOGARITHM;
}


Logarithm::Logarithm( const Logarithm &arg ):UnaryOperator(arg){
  cName = "log";

  fcn = &log;
  dfcn = &dLogarithm;
  ddfcn = &ddLogarithm;

  operatorName = ON_LOGARITHM;
}


Logarithm::~Logarithm(){

}


Logarithm& Logarithm::operator=( const Logarithm &arg ){

  UnaryOperator::operator=(arg);

  return *this;
}


returnValue Logarithm::evaluate( EvaluationBase *x ){
 
    x->Log(*argument);
    return SUCCESSFUL_RETURN;
}



Operator* Logarithm::substitute( int index, const Operator *sub ){

    return new Logarithm( argument->substitute( index , sub ) );

}

Operator* Logarithm::clone() const{

    return new Logarithm(*this);
}


CurvatureType Logarithm::getCurvature( ){

    if( curvature != CT_UNKNOWN )  return curvature;

    const CurvatureType cc = argument->getCurvature();

    if( cc == CT_CONSTANT )  return CT_CONSTANT;
    if( cc == CT_AFFINE   )  return CT_CONCAVE ;
    if( cc == CT_CONCAVE  )  return CT_CONCAVE ;

    return CT_NEITHER_CONVEX_NOR_CONCAVE;
}

returnValue Logarithm::initDerivative() {

	if( derivative != 0 && derivative2 != 0 ) return SUCCESSFUL_RETURN;

	derivative = convert2TreeProjection(new Power_Int( argument->clone(), -1 ));
	derivative2 = convert2TreeProjection(new Product( new DoubleConstant( -1.0 , NE_NEITHER_ONE_NOR_ZERO ), new Power_Int( argument->clone(), -2 ) ));

	return argument->initDerivative();
}


CLOSE_NAMESPACE_ACADO

// end of file.
