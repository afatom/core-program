
#if !defined(__BIT_SET_H__)
#define __BIT_SET_H__

#include <iostream>
#include <climits> //CHAR_BIT
#include <algorithm>    // std::fill
#include <cstring>

using std::size_t;

template <size_t SIZE, typename Type = unsigned int> //Size is number of bits/servers
class BitSet
{
public:
    class BitRef;
    explicit BitSet(const char* bits = " ");
    //copy Ctor, op=, Dtor provide by g++ 
    

    bool IsAnny();
    bool IsAll();
    bool IsNone();
  	
  	bool    operator==(const BitSet&);
  	//bool    operator!=(const BitSet&); //global
  	
    BitRef& operator[](size_t pos);
 	bool    operator[](size_t pos) const;
	BitSet& operator&= (const BitSet& other);
	BitSet& operator|= (const BitSet& other);
	BitSet& operator^= (const BitSet& other);	

	BitSet& operator<<= (size_t numofshifts);
	BitSet& operator>>= (size_t numofshifts);
	BitSet operator~() const; //unary op
	BitSet& Flip();

	//setters
	void SetBit(size_t bitPos, bool bit);


	//getters
	BitRef GetBit(size_t bitPos) const;
	size_t GetNumOfElements() const;
	size_t GetNumOfBitsPerElement() const;
	const Type* GetBitSet()const;
	const size_t& GetOneElementBitsNum()const;
	bool GetBit(const Type& element, const int& bitOffset);



class BitRef{
public:
    BitRef(BitSet& set, size_t pos)        
    : bitset(set)
    , bitPos(pos){} 

    
    BitRef& operator= (bool bit)
    {
        bitset.SetBit(bitPos, bit);
        return *this;
    }

    //conversion op
    operator bool()
    {
    	return bitset.GetBit(bitPos);
    }

private:
    BitSet& bitset;
    const size_t bitPos;
};



private:

	//static const is letteral not variable. he is born in text in compilation time.
	static const size_t m_numOfElements = ((SIZE/(CHAR_BIT*sizeof(Type))) + (SIZE%(CHAR_BIT*sizeof(Type)) > 0)? 1 : 0);  
    static const size_t m_numOfBitsPerElement = (sizeof(Type) * CHAR_BIT);
    const size_t m_noe =  m_numOfElements;
    const size_t m_nob = m_numOfBitsPerElement;
    Type arr[m_numOfElements];
}; 





/******************************************************************
 * arr[0]                                              arr[N-1]
 *     |------------------------------------------------|
 *     |                                                |
 *     |------------------------------------------------|
 *  MSByte                                           LSByte
*********************************************************************/

template <size_t SIZE, typename Type>
inline BitSet<SIZE, Type>::BitSet(const char* bits) 
{
	if(!bits)
	{
		//throw exception
	}

    size_t bitsLength = strlen(bits);
    int i=0, j=0, k=0;

    std::fill(arr,arr + m_numOfElements, 0);
    
    Type mask = 1; 
    int curpos= (int)bitsLength -1;

    for(i = m_numOfElements - 1; i >= 0; --i) 
    {
        for(j = curpos; j > -1 && k < (int)m_numOfBitsPerElement; --curpos, --j,++k)
        {
            arr[i] |= mask & (bits[j]-'0');
            mask <<= 1;
            mask |= 1;
        }
    }
}






/*******************************************************************/
/*cout*/

template <size_t SIZE, typename Type>
std::ostream& operator<< (std::ostream& os, BitSet<SIZE, Type>& bs)
{
    Type mask = 1;
    
    const Type* const ptr = bs.GetBitSet();
    
    for(int i = (int)bs.GetNumOfElements() - 1; i >= 0; --i)
    {
        for(size_t j=0; j<bs.GetNumOfBitsPerElement(); ++j)
        {
            (mask & ptr[i]) ? (std::cout<<"1 ") : (std::cout<<"0 ");
            mask <<= 1;
            mask |= 1; 
        }
    }

    return os;
}




template <size_t SIZE, typename Type>
inline size_t BitSet<SIZE, Type>::GetNumOfElements() const
{
    return this->m_numOfElements;
}


template <size_t SIZE, typename Type>
inline size_t BitSet<SIZE, Type>::GetNumOfBitsPerElement() const
{
    return this->m_numOfBitsPerElement;
}


template <size_t SIZE, typename Type>
inline const Type* BitSet<SIZE, Type>::GetBitSet()const
{
    return this->arr;
}


/*******************************************************************/


/*










template <size_t SIZE, typename Type>
inline const size_t& BitSet<SIZE, Type>::GetOneElementBitsNum()const
{
    return this->elementBitsNum;
}



size_t GetMyBitSetSize(size_t userbitsnum, size_t elementSize)
{
    size_t j=userbitsnum/(elementSize);
    if(j)
    {
        return j + (size_t)(userbitsnum % (elementSize) > 0);
    }
    return (size_t)(userbitsnum % (elementSize) > 0);
}
*/

#endif // __BIT_SET_H__
