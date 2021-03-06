/*
  @copyright Russell Standish 2019
  @author Russell Standish
  This file is part of Civita.

  Civita is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Civita is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Civita.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CIVITA_HYPERCUBE_H
#define CIVITA_HYPERCUBE_H

#include "xvector.h"

namespace civita
{
  
  struct Hypercube
  {
    Hypercube() {}
    Hypercube(const std::vector<unsigned>& d) {dims(d);}
    Hypercube(const std::vector<XVector>& d): xvectors(d) {}
    Hypercube(std::vector<XVector>&& d): xvectors(std::move(d)) {}
    
    std::vector<XVector> xvectors;
    size_t rank() const {return xvectors.size();}

    bool operator==(const Hypercube& x) const {return xvectors==x.xvectors;}
    bool operator!=(const Hypercube& x) const {return !operator==(x);}
    
    /// dimensions of this variable value. dims.size() is the rank, a
    ///scalar variable has dims[0]=1, etc.
    std::vector<unsigned> dims() const;
    
    /// number of elements in the hypercube, equaly to the product of
    /// dimensions
    size_t numElements() const;
      
    /// set the dimensions. \a d cannot be empty, by may consist of
    ///the single element {1} to refer to a scalar
    const std::vector<unsigned>& dims(const std::vector<unsigned>& d);
    
    /// removes elements of xVector not found in \a a
    void makeConformant(const Hypercube& a);

    /// compute stride and dimension size of dimension \a dim
    /// @throw if dimension \a dim doesn't exist
    /// if \a dim is empty, defaults to first dimension
    void computeStrideAndSize(const std::string& dim, size_t& stride, size_t& size) const;

    /// split lineal index into components along each dimension
    std::vector<size_t> splitIndex(size_t) const;
    /// combine a split index into a lineal hypercube index
    size_t linealIndex(const std::vector<size_t>&) const;
  };
  
}

#endif
