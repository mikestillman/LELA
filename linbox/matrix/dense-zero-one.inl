/* -*- mode: C++; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/* linbox/matrix/dense-zero-one.inl
 * Copyright 2010 Bradford Hovinen <hovinen@gmail.com>
 *
 * Specialisation of DenseMatrixBase for zero-one dense matrices -- support-functions
 *
 * Evolved from dense.h
 */

#ifndef __MATRIX_DENSE_ZERO_ONE_INL
#define __MATRIX_DENSE_ZERO_ONE_INL

#include <iostream>

#include <linbox/matrix/dense-zero-one.h>

namespace LinBox
{

template <class Iterator, class ConstIterator>
class DenseZeroOneMatrix<Iterator, ConstIterator>::ConstRowIterator
{
    public:
	typedef typename ConstRow::const_word_iterator::difference_type difference_type;

	ConstRowIterator (Rep::const_word_iterator p, size_t words, size_t bit_len, size_t d)
		: _row (p, p + words, bit_len), _disp (d) {}
    
	ConstRowIterator () {}
    
	ConstRowIterator (const ConstRowIterator& colp)
		: _row (colp._row), _disp (colp._disp) {}
    
	ConstRowIterator& operator = (const ConstRowIterator& colp)
	{
		_row = colp._row;
		_disp = colp._disp;
		return *this;
	}

	ConstRowIterator& operator --()
	{
		_row = ConstRow (_row.wordBegin () - _disp, _row.wordEnd () - _disp, _row.size ());
		return *this;
	}

	ConstRowIterator  operator-- (int)
        {
                ConstRowIterator tmp (*this);
                --*this;
                return tmp;
	}

	
	ConstRowIterator& operator++ ()
	{
		_row = ConstRow (_row.wordBegin () + _disp, _row.wordEnd () + _disp, _row.size ());
		return *this;
	}

	ConstRowIterator  operator++ (int)
	{
		ConstRowIterator tmp (*this);
		++*this;
		return tmp;
	}

	ConstRowIterator operator+ (int i) const
		{ return ConstRowIterator (_row.wordBegin () + _disp * i, _row.word_size (), _row.size (), _disp); }

	difference_type operator- (const ConstRowIterator &c) const
	{
		return (c._row.wordBegin () - _row.wordBegin ()) / _disp;
	}

	ConstRowIterator& operator += (int i)
	{
		_row = ConstRow (_row.wordBegin () + _disp * i, _row.wordEnd () + _disp * i, _row.size ());
		return *this;
	}

	ConstRow operator[] (int i) const
		{ return ConstRow (_row.wordBegin () + _disp * i, _row.wordEnd () + _disp * i, _row.size ()); }

	const ConstRow* operator-> () const
		{ return &_row; }

	const ConstRow& operator* () const
		{ return _row; }

	bool operator == (const ConstRowIterator& c) const
		{ return (_row.wordBegin () == c._row.wordBegin ()) && (_row.wordEnd () == c._row.wordEnd ()) && (_disp == c._disp); }
    
	bool operator!= (const ConstRowIterator& c) const
		{ return (_row.wordBegin () != c._row.wordBegin ()) || (_row.wordEnd () != c._row.wordEnd ()) || (_disp != c._disp); }

    private:
	friend class DenseZeroOneMatrix::RowIterator;

	ConstRow _row;
	size_t _disp;
};

template <class Iterator, class ConstIterator>
class DenseZeroOneMatrix<Iterator, ConstIterator>::RowIterator
{
    public:
	typedef typename Row::word_iterator::difference_type difference_type;

	RowIterator (Rep::word_iterator p, size_t words, size_t bit_len, size_t d)
		: _row (p, p + words, bit_len), _disp (d) {}

	RowIterator () {}

	RowIterator (const RowIterator& colp)
		: _row (colp._row), _disp (colp._disp) {}
    
	RowIterator& operator = (const RowIterator& colp)
	{
		_row = colp._row;
		_disp = colp._disp;
		return *this;
	}
    
	RowIterator& operator ++ ()
	{
		_row = Row (_row.wordBegin () + _disp, _row.wordEnd () + _disp, _row.size ());
		return *this;
	}
    
	RowIterator  operator ++ (int)
	{
		RowIterator tmp (*this);
		++*this;
		return tmp;
	}
    
        RowIterator& operator -- ()
        {
                _row = Row (_row.wordBegin () - _disp, _row.wordEnd () - _disp, _row.size ());
                return *this;
        }

        RowIterator  operator -- (int)
        {
                RowIterator tmp (*this);
                --*this;
                return tmp;
        }

	RowIterator operator + (int i) const
		{ return RowIterator (const_cast<Row *> (&_row)->wordBegin () + _disp * i, _row.word_size (), _row.size (), _disp); }

	difference_type operator- (const RowIterator &c) const
	{
		return (c._row.wordBegin () - _row.wordBegin ()) / _disp;
	}

	RowIterator& operator += (int i)
	{
		_row = Row (_row.wordBegin () + _disp * i, _row.wordEnd () + _disp * i, _row.size ());
		return *this;
	}

	Row operator[] (int i) const
		{ return Row (const_cast<Row&> (_row).wordBegin () + _disp * i,
			      const_cast<Row&> (_row).wordEnd () + _disp * i, _row.size ()); }

	Row* operator-> ()
		{ return &_row; }

	const Row* operator-> () const
		{ return &_row; }
    
	Row& operator* ()
		{ return _row; }

	const Row& operator* () const
		{ return _row; }
 
	bool operator == (const RowIterator& c) const
		{ return (_row.wordBegin () == c._row.wordBegin ()) && (_row.wordEnd () == c._row.wordEnd ()) && (_disp == c._disp); }

	bool operator != (const RowIterator& c) const
		{ return (_row.wordBegin () != c._row.wordBegin ()) || (_row.wordEnd () != c._row.wordEnd ()) || (_disp != c._disp); }

	bool operator != (const ConstRowIterator& c) const
		{ return (_row.wordBegin () != c._row.wordBegin ()) || (_row.wordEnd () != c._row.wordEnd ()) || (_disp != c._disp); }

	operator ConstRowIterator ()
		{ return ConstRowIterator (_row.wordBegin (), _row.word_size (), _row.size (), _disp); }

    private:
	Row _row;
	size_t _disp;
};

template <class Iterator, class ConstIterator>
typename DenseZeroOneMatrix<Iterator, ConstIterator>::RowIterator
DenseZeroOneMatrix<Iterator, ConstIterator>::rowBegin ()
{
	return RowIterator (_begin, (!(_cols & __LINBOX_POS_ALL_ONES)) ? (_cols >> __LINBOX_LOGOF_SIZE) : ((_cols >> __LINBOX_LOGOF_SIZE) + 1), _cols, _disp);
}

template <class Iterator, class ConstIterator>
typename DenseZeroOneMatrix<Iterator, ConstIterator>::RowIterator
DenseZeroOneMatrix<Iterator, ConstIterator>::rowEnd ()
{
	return RowIterator (_begin + _rows * _disp, (!(_cols & __LINBOX_POS_ALL_ONES)) ? (_cols >> __LINBOX_LOGOF_SIZE) : ((_cols >> __LINBOX_LOGOF_SIZE) + 1), _cols, _disp);
}

template <class Iterator, class ConstIterator>
typename DenseZeroOneMatrix<Iterator, ConstIterator>::ConstRowIterator
DenseZeroOneMatrix<Iterator, ConstIterator>::rowBegin () const
{
	return ConstRowIterator (_begin, (!(_cols & __LINBOX_POS_ALL_ONES)) ? (_cols >> __LINBOX_LOGOF_SIZE) : ((_cols >> __LINBOX_LOGOF_SIZE) + 1), _cols, _disp);
}

template <class Iterator, class ConstIterator>
typename DenseZeroOneMatrix<Iterator, ConstIterator>::ConstRowIterator
DenseZeroOneMatrix<Iterator, ConstIterator>::rowEnd () const
{
	return ConstRowIterator (_begin + _rows * _disp, (!(_cols & __LINBOX_POS_ALL_ONES)) ? (_cols >> __LINBOX_LOGOF_SIZE) : ((_cols >> __LINBOX_LOGOF_SIZE) + 1), _cols, _disp);
}

template <class Iterator, class ConstIterator>
template <class Field>
std::istream& DenseZeroOneMatrix<Iterator, ConstIterator>::read (std::istream &file, const Field& field)
{
	size_t i, j;

	for (i = 0; i < rowdim (); ++i) {
		for (j = 0; j < coldim (); ++j) {
			file.ignore (1);
			field.read (file, refEntry (i, j));
		}
	}

	return file;
}

template <class Iterator, class ConstIterator>
template <class Field>
std::ostream& DenseZeroOneMatrix<Iterator, ConstIterator>::write (std::ostream &os, const Field &F) const
{
	ConstRowIterator p;

	for (p = rowBegin (); p != rowEnd (); ++p) {
		typename ConstRow::const_iterator pe;

		os << "  [ ";

		for (pe = p->begin (); pe != p->end (); ++pe) {
			if (F.isZero (*pe))
				os << '.';
			else
				os << '1';
			os << " ";
		}

		os << "]" << std::endl;
	}

	return os;
}

template <class Iterator, class ConstIterator>
class SubvectorFactory<DenseZeroOneMatrix<Iterator, ConstIterator> >
{
    public:
	typedef BitSubvector<BitVector::iterator, BitVector::const_iterator> RowSubvector;
	typedef BitSubvector<BitVector::const_iterator, BitVector::const_iterator> ConstRowSubvector;

	RowSubvector MakeRowSubvector (SubmatrixBase<DenseZeroOneMatrix<Iterator, ConstIterator> > &M, typename DenseZeroOneMatrix<Iterator, ConstIterator>::RowIterator &pos)
		{ return RowSubvector (pos->begin () + M.startCol (), pos->begin () + (M.startCol () + M.coldim ())); }

	ConstRowSubvector MakeConstRowSubvector (const SubmatrixBase<DenseZeroOneMatrix<Iterator, ConstIterator> > &M, typename DenseZeroOneMatrix<Iterator, ConstIterator>::ConstRowIterator &pos)
		{ return ConstRowSubvector (pos->begin () + M.startCol (), pos->begin () + (M.startCol () + M.coldim ())); }
};

template <class Iterator, class ConstIterator>
class SubvectorFactory<const DenseZeroOneMatrix<Iterator, ConstIterator> >
{
    public:
	typedef BitSubvector<BitVector::const_iterator, BitVector::const_iterator> RowSubvector;
	typedef BitSubvector<BitVector::const_iterator, BitVector::const_iterator> ConstRowSubvector;

	ConstRowSubvector MakeConstRowSubvector (const SubmatrixBase<const DenseZeroOneMatrix<Iterator, ConstIterator> > &M, typename DenseZeroOneMatrix<Iterator, ConstIterator>::ConstRowIterator &pos)
		{ return ConstRowSubvector (pos->begin () + M.startCol (), pos->begin () + (M.startCol () + M.coldim ())); }
};

}

#endif // __MATRIX_DENSE_ZERO_ONE_INL