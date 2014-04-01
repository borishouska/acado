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
*    \file include/acado/symbolic_operator/powerint.hpp
*    \author Boris Houska, Hans Joachim Ferreau
*    \date 2008
*/


#ifndef ACADO_TOOLKIT_POWERINT_HPP
#define ACADO_TOOLKIT_POWERINT_HPP


#include <acado/symbolic_operator/symbolic_operator_fwd.hpp>


BEGIN_NAMESPACE_ACADO


/**
 *	\brief Implements the scalar power operator with integer exponent within the symbolic operators family.
 *
 *	\ingroup BasicDataStructures
 *
 *	The class Power_Int implements the scalar power operator with integer exponent 
 *	within the symbolic operators family.
 *
 *	\author Boris Houska, Hans Joachim Ferreau
 */

class Power_Int : public UnaryOperator{

public:

    /** Default constructor. */
    Power_Int();

    /** Default constructor. */
    Power_Int( const SharedOperator &_argument, const int &_exponent );

    /** Copy constructor. */
    Power_Int( const Power_Int &arg );

    /** Default destructor. */
    ~Power_Int();

    /** Evaluates the expression (templated version) */
    virtual uint evaluate( EvaluationBase *x, std::vector<uint> &indices, uint base );

    /** Substitutes key with the expression sub. \n
     *  \return The substituted expression.      \n
     *
     */
    virtual SharedOperator substitute( SharedOperatorMap &sub /**< the substitution */ );

    /** Initializes the derivative operators */
    virtual returnValue initDerivative();
 
    
    virtual std::ostream& print(std::ostream& stream, StringMap &name ) const;
    
protected:
  
    int exponent;
};


CLOSE_NAMESPACE_ACADO



#endif
