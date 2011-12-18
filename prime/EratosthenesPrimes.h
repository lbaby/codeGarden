/**
* @file    EratosthenesPrimes.h
* @brief   Eratosthenesɸ����������
* @author  Tu Yongce <yongce (at) 126 (dot) com>
* @date    2009-4-21
* @version 0.2
*/

#ifndef ERATOSTHENES_PRIMES_H_INCLUDED
#define ERATOSTHENES_PRIMES_H_INCLUDED

#include <cmath>
#include <cstring>
#include <stdexcept>
#include <cassert>

/**
* @brief ʹ��Eratosthenesɸ������[1, M]��Χ�ڵ���������
* @tparam IntType ģ���� EratosthenesPrimes ��ģ������������int��unsigned int���Ի����õ�����Ч�ʣ�
*/

template <typename IntType>
class EratosthenesPrimes
{
public:
    /// ������IsPrime��Ա����ʱ�������׳����쳣��
    class Unready: public std::runtime_error
    {
    public:
        /// ���캯��
        Unready(const char *errMsg): std::runtime_error(errMsg) { }
    };
    
public:
    /// ���캯��
    EratosthenesPrimes()
    {
        m_tags = 0;
        m_maxNum = 0;
        m_primesCount = 0;
        m_done = false;
    }

    /// ��������
    ~EratosthenesPrimes() 
    {
        delete m_tags;
    }

    /**
    * @brief ����[1, <em>maxNum</em>]��Χ�ڵ���������
    * @param maxNum ���ҷ�Χ������ֵ�����벻С��1
    * @return ���maxNumС��1����ô���Ҳ���ʧ�ܣ�����false��������������ɹ�������true
    */
    bool FindPrimes(IntType maxNum); 

    /**
    * @brief ����FindPrimes�Ĳ��ҽ�����ж�[1, <em>maxNum</em>]��Χ�ڵ�����<em>num</em>�Ƿ�Ϊ����
    * @param num ��Ҫ�ж����Ե���
    * @return ���<em>num</em>Ϊ�������򷵻�true�����򷵻�false
    * @throw Unready �������IsPrime֮ǰû�е���FindPrimes����<em>num</em>����[1, <em>maxNum</em>]��Χ�ڣ�
    *                ���׳������쳣��
    */
    bool IsPrime(IntType num) const
    {
        if (!m_done || num < 1 || num > m_maxNum)
            throw Unready("failed");
        if (num == 2)
            return true;
        if (num % 2 == 0)
            return false;
        return GetTag(num);
    }

    /// ����[1, <em>maxNum</em>]��Χ�ڵ���������
    IntType GetPrimesCount() const
    {
        return m_primesCount;
    }

    /**
    * @brief �����������
    * @tparam OutIterator �������������
    * @param outIt ���������
    * @return ����������е����һ��Ԫ�ص���һ��λ��
    */
    template <typename OutIterator>
    OutIterator OutputPrimes(OutIterator outIt) const;

private:
    bool GetTag(IntType num) const
    {
        assert(num % 2 == 1);
        return (m_tags[num / BM_CYCLE] & (BitMap(1) << (num % BM_CYCLE / 2))) != 0;
    }

    void ClearTag(IntType num)
    {
        assert(num % 2 == 1);
        m_tags[num / BM_CYCLE] &= ~(BitMap(1) << (num % BM_CYCLE / 2));
    }
    
private:
    // ��ֹ����
    EratosthenesPrimes(const EratosthenesPrimes &);
    EratosthenesPrimes& operator = (const EratosthenesPrimes &);

private:
    typedef unsigned int BitMap;
    static const int BM_CYCLE = sizeof(BitMap) * 16;
    
    BitMap *m_tags;
    IntType m_maxNum;
    IntType m_primesCount;
    bool m_done;
};

template <typename IntType>
bool EratosthenesPrimes<IntType>::FindPrimes(IntType maxNum)
{
    if (maxNum < 1)
        return false;

    IntType newNum = maxNum / BM_CYCLE + 1;
    if (!m_tags || (m_maxNum / BM_CYCLE + 1) < newNum) {
        delete m_tags;
        m_tags = new BitMap[static_cast<size_t>(newNum)];
    }
    m_maxNum = maxNum;
    std::memset(m_tags, 0xFF, static_cast<size_t>(newNum) * sizeof(BitMap));
    m_primesCount = (m_maxNum - 1) / 2 + 1;  // С�����

    ClearTag(1);
    //--m_primesCount;      // 1
    //++m_primesCount;      // 2

    IntType root = IntType(std::sqrt(double(m_maxNum)));
    for (IntType i = 3; i <= root; i += 2) {
        if (!GetTag(i)) {
            continue;
        }

        IntType i2 = 2 * i;
        IntType limit = m_maxNum - i2;  // ��ֹ�޷������͵����
        IntType k;
        for (k = i * 3; k <= limit; k += i2) {
            if (GetTag(k)) {
                ClearTag(k);
                --m_primesCount;
            }
        }
        if (k <= m_maxNum && GetTag(k)) {
            ClearTag(k);
            --m_primesCount;
        }
    }

    m_done = true;
    return true;
}

template <typename IntType>
template <typename OutIterator>
OutIterator EratosthenesPrimes<IntType>::OutputPrimes(OutIterator outIt) const
{
    if (!m_done)
        return outIt;

    if (m_maxNum >= 2)
        *outIt++ = 2;

    for (IntType i = 3; i <= m_maxNum; i += 2) {
        if (GetTag(i)) {
            *outIt++ = i;
        }
    }
    return outIt;
}

#endif //ERATOSTHENES_PRIMES_H_INCLUDED
