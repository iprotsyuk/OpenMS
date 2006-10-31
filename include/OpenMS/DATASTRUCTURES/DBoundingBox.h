// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                   OpenMS Mass Spectrometry Framework 
// --------------------------------------------------------------------------
//  Copyright (C) 2003-2006 -- Oliver Kohlbacher, Knut Reinert
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------
// $Maintainer: Clemens Groepl $
// --------------------------------------------------------------------------

#ifndef OPENMS_DATASTRUCTURES_DBOUNDINGBOX_H
#define OPENMS_DATASTRUCTURES_DBOUNDINGBOX_H

#include <OpenMS/DATASTRUCTURES/DIntervalBase.h>

namespace OpenMS
{
	
	/**
		@brief A D-dimensional bounding box.
		 
		A DBoundingBox denotes a closed interval.  Upper and lower margins are both contained.
		
		@ingroup Datastructures
	*/
	template <Size D, typename Traits = KernelTraits>
	class DBoundingBox
		:	public Internal::DIntervalBase<D, Traits>
	{
		
	 public:

		/**	
			@name Type definitions 
		*/	
		//@{
		/// Dimensions
		enum { DIMENSION = D };
		/// Base class type
		typedef Internal::DIntervalBase<D, Traits> Base; 
		/// Traits types
		typedef typename Base::TraitsType TraitsType;
		/// Position type
		typedef typename Base::PositionType PositionType;
		/// Coordinate type of the positions
		typedef typename Base::CoordinateType CoordinateType;
		//@}

		
		// for convenience
		using Base::min_;
		using Base::max_;

		/**	@name Constructors and Destructor */
		//@{
		///Default constructor. 
		DBoundingBox()
			: Base()
		{
			
		}
		
		/// Copy constructor
		DBoundingBox(const DBoundingBox& rhs)
			: Base(rhs)
		{
			
		}
		
		/// Assignement operator
		DBoundingBox & operator=(const DBoundingBox& rhs)
		{
			Base::operator=(rhs);
			return *this;
		}

		/// Assignement operator for the base class
		DBoundingBox & operator=(const Base& rhs)
		{
			Base::operator=(rhs);
			return *this;
		}
		
		/// Destructor
		~DBoundingBox()
		{
			
		}

		///Constructor from two positions
		DBoundingBox( PositionType const & minimum, PositionType const & maximum )
			: Base ( minimum,  maximum )
		{}

		//@}

		/**	@name Accessors */
		//@{

		/// Enlarges the bounding box such that it contains a position.
		void enlarge(PositionType const & p)
		{
			for ( Size i = 0; i < DIMENSION; ++i )
			{
				if ( p[i] < min_[i] ) min_[i] = p[i];
				if ( p[i] > max_[i] ) max_[i] = p[i];
			}
		}

		///2D-version enlarge(x,y) is for convenience only
		void enlarge(CoordinateType const& x, CoordinateType const& y)
		{
			enlarge( PositionType(x,y) );
		}
		//}@

		/**	@name Predicates */
		//@{
		
		/// Equality operator
		bool operator == (const DBoundingBox& rhs) const throw()
		{
			return Base::operator==(rhs);
		}

		/// Equality operator
		bool operator == (const Base& rhs) const throw()
		{
			return Base::operator==(rhs);
		}

		/**
			@brief Checks whether this range contains a certain point.
			
			@param position The point's position.
			@returns true if point lies inside this area.
		*/
		bool encloses(PositionType const& position) const
		{
			for ( Size i = 0; i < DIMENSION; ++i )
			{
				if ( position[i] < min_[i] || position[i] > max_[i] )
				{
					return false;
				}
			}
			return true;
		}

		///2D-version encloses(x,y) is for convenience only
		bool encloses(CoordinateType const& x, CoordinateType const& y) const
		{
			return encloses( PositionType(x,y) );
		}
		
		/**
			 Checks whether this bounding box intersects with another bounding box
		*/	
		bool intersects(DBoundingBox const & bounding_box) const
		{
			for ( Size i = 0; i < DIMENSION; ++i )
			{
				if ( bounding_box .min_[i] > max_[i] ) return false; 
				if ( bounding_box.max_[i] <  min_[i] ) return false; 
			}
			return true;
	  }         

		/// Test if bounding box is empty
		bool isEmpty() const 
		{ 
			return *this == Base::empty; 
		}
    
		//@}


	};
	
	/**@brief Print the contents to a stream.

	@relatesalso DBoundingBox
	*/
	template <Size D, typename Traits>
	std::ostream& operator << (std::ostream& os, const DBoundingBox<D,Traits>& bounding_box)
	{
		os << "--DBOUNDINGBOX BEGIN--"<<std::endl;
		os << "MIN --> " << bounding_box.min() << std::endl;
		os << "MAX --> " << bounding_box.max() << std::endl;
		os << "--DBOUNDINGBOX END--"<<std::endl;
		return os;
	}

	
} // namespace OpenMS

#endif // OPENMS_KERNEL_DBOUNDINGBOX_H
