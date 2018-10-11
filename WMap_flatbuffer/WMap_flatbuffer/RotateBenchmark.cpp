#include "StdAfx.h"
#include "RotateBenchmark.h"

#include "windows.h"

#include <vector>
#include <iostream>
#include <numeric>

//parallel
#include <ppl.h>
#include <complex>

CRotateBenchmark::CRotateBenchmark(void)
{
}


CRotateBenchmark::~CRotateBenchmark(void)
{
}


bool is_prime( unsigned int number ) // invariant: n > 2
{
    //const unsigned int sqrt1 = std::sqrt(number) + 1 ;
    //for( unsigned int i = 3 ; i <= sqrt1 ; ++i ) if( number%i == 0 ) return false ;
    return true ;
}


void append_if_prime( unsigned int number )
{
    //if( is_prime(number) )
    //{
    //    const auto i = ++cnt ;
    //    if( i < primes.size() ) primes[i] = number ;
    //}
}

void CRotateBenchmark::Rotate90() 
{
    int nMaxRow = 800;
    int nMaxCol = 800;

    std::cout << "Matrix : Row =" << nMaxRow << " Col = " << nMaxCol << std::endl;

    // Optimize code
    std::unique_ptr<short []> inBuffer;
    inBuffer.reset(new short [nMaxRow * nMaxCol]);

    std::unique_ptr<short []> tmpBuffer;
    tmpBuffer.reset(new short [nMaxRow * nMaxCol]);

    //std::vector<short> inBuffer(nMaxRow * nMaxCol);
    //std::vector<short> tmpBuffer(nMaxRow * nMaxCol);

    DWORD dwStart = GetTickCount();
    memcpy(tmpBuffer.get(), inBuffer.get(), nMaxRow * nMaxCol * sizeof(short));
    //memcpy(&tmpBuffer[0], &inBuffer[0], nMaxRow * nMaxCol * sizeof(short));

    std::cout << "Memcpy : " << GetTickCount() - dwStart << std::endl;
    //
    int nAveLoop = 100;
    std::vector<DWORD> vecTime;
        
    vecTime.reserve(nAveLoop);
    //
    // ~40 - 60ms
    for (int nLoop = 0; nLoop < nAveLoop; nLoop++)
    {
        dwStart = GetTickCount();
        //
        for (int i = 0; i < nMaxRow; i++)
        {
            for (int j = 0; j < nMaxCol; j++)
            {
                inBuffer[j * nMaxRow + (nMaxRow - 1 - i)] = tmpBuffer[i * nMaxCol + j];
                //inBuffer.at(j * nMaxRow + (nMaxRow - 1 - i)) = tmpBuffer.at(i * nMaxCol + j);
            }
        }
        //
        vecTime.push_back(GetTickCount() - dwStart);
    }
    //
    DWORD dwTime = std::accumulate(vecTime.begin(), vecTime.end(), 0);
    std::cout << "Normal Rotate : " << dwTime / nAveLoop << " ms (Averaging Cnt : " << nAveLoop << ")"<< std::endl;

    vecTime.clear();
    // perform outer loop in parallel : one thread for each row ~20 - 50 ms
    for (int nLoop = 0; nLoop < nAveLoop; nLoop++)
    {
        dwStart = GetTickCount();
        //
        Concurrency::parallel_for( size_t(0), size_t(nMaxRow), [&](size_t i)  
        {
            for (int j = 0; j < nMaxCol; j++)
            {
                inBuffer[j * nMaxRow + (nMaxRow - 1 - i)] = tmpBuffer[i * nMaxCol + j];
                //inBuffer.at(j * nMaxRow + (nMaxRow - 1 - i)) = tmpBuffer.at(i * nMaxCol + j);
            }
        });

        //
        vecTime.push_back(GetTickCount() - dwStart);
    }
    //
    dwTime = std::accumulate(vecTime.begin(), vecTime.end(), 0);
    std::cout << "parallel_for Rotate : " << dwTime / nAveLoop << " ms (Averaging Cnt : " << nAveLoop << ")" << std::endl;

//const unsigned int SZ = 1000000 ;
////std::atomic<unsigned int> cnt {0} ; // atomic
//    unsigned int cnt=0;
//    const unsigned int BOUND = SZ * 10 ;
//    Concurrency::parallel_for( 3U, BOUND, 2U, append_if_prime ) ;
//    std::cout << cnt << " prime numbers in all " << " up to " << BOUND << "\n\n" ;


}
