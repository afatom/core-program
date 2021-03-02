
template <size_t SIZE, typename Type>
inline void BitSet<SIZE, Type>::SetBit(size_t bitPos, bool bit)
{

}




template <size_t SIZE, typename Type>
inline BitSet<SIZE, Type> operator& (const BitSet<SIZE,Type>& lhs, const BitSet<SIZE,Type>& rhs)
{
    Type mask = 1;
    mask = (signed)mask;
    BitSet<SIZE,Type> temp; 
    size_t i = 0, j =0;
    while(i < SIZE)
    {   
        mask <<= lhs.elementBitsNum-1;
        for(j = 0; j < lhs.elementBitsNum; ++j)
        {
            (temp.arr[i] & mask) = (lhs.arr[i] & mask) & (rhs.arr[i] & mask);
            mask >>= 1;
        }

        ++i;
    }
    return temp;
}



template <size_t SIZE, typename Type>
inline BitSet<SIZE, Type> operator^ (const BitSet<SIZE,Type>& lhs, const BitSet<SIZE,Type>& rhs)
{
    Type mask = 1;
    mask = (signed)mask;
    BitSet<SIZE,Type> temp; 
    size_t i = 0, j =0;
    while(i < SIZE)
    {   
        mask <<= lhs.elementBitsNum-1;
        for(j = 0; j < lhs.elementBitsNum; ++j)
        {
            (temp.arr[i] & mask) = (lhs.arr[i] & mask) & (rhs.arr[i] & mask);
            mask >>= 1;
        }

        ++i;
    }
    return temp;
}





template <size_t SIZE, typename Type>
inline BitSet<SIZE, Type> operator| (const BitSet<SIZE,Type>& lhs, const BitSet<SIZE,Type>& rhs)
{
    Type mask = 1;
    mask = (signed)mask;
    BitSet<SIZE,Type> temp; 
    size_t i = 0, j =0;
    while(i < SIZE)
    {   
        mask <<= lhs.elementBitsNum-1;
        for(j = 0; j < lhs.elementBitsNum; ++j)
        {
            (temp.arr[i] & mask) = (lhs.arr[i] & mask) | (rhs.arr[i] & mask);
            mask >>= 1;
        }

        ++i;
    }
    return temp;
}







template <size_t SIZE, typename Type>
inline BitSet<SIZE, Type>::BitSet() 
: elementBitsNum(sizeof(Type) * CHAR_BIT)
{ std::memset(arr,0,SIZE); }









template <size_t SIZE, typename Type>
inline bool BitSet<SIZE, Type>::IsAnny()
{
    return false;
}

template <size_t SIZE, typename Type>
inline char BitSet<SIZE, Type>::operator[](size_t pos) const
{
    //index in arr
    size_t index= pos / elementBitsNum;
    size_t bitpos = pos % elementBitsNum;
    return ((arr[index] >> (bitpos-1))&1) ? '1' : '0';
}

template <size_t SIZE, typename Type>
inline char BitSet<SIZE, Type>::operator[](size_t pos)
{
    size_t index= pos / elementBitsNum;
    size_t bitpos = pos % elementBitsNum;
    //((arr[index] >> (bitpos-1))&1)
    return '1';
}

template <size_t SIZE, typename Type>
inline bool operator== (const BitSet& lhs, const BitSet& rhs)
{
    return false;
}



bool operator[](size_t pos) const
{
    const Type& elem = arr[index / numofbitsPerElement];
    const int bitOffset = index % numofbitsPerElement;
    return GetBit(elem, bitOffset);
}

