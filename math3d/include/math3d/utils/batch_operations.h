

#ifndef math3d_batch_
#define math3d_batch_ 1
#include <iostream>
#include "math3d/core/core.h"

namespace math3d {
    template <class Transformator, class Data>
    class _BatchUpdater : public basicMath3dObject{
    public:
        _BatchUpdater(const Transformator & _transformator, int nData) {
            transformator = _transformator;
            std::cout << "allocating data: " << sizeof(Data) * nData << std::endl;
            data = static_cast<Data *>(aligned_malloc(sizeof(Data) * nData, 16));
            next = data;
            sizeData = nData;
        }

        ~_BatchUpdater() {
            std::cout << "being called" << std::endl;
            aligned_free(data);
        }

        Data * nextPointer() {
            return next++;
        }

        void resetPointer() {
            next = data;
        }
    protected:
        Transformator transformator;
        Data * data;
        Data * next;
        int sizeData;
    };
    
    template <class Transformer, class Data>
    class BatchUpdater : public _BatchUpdater<Transformer, Data> {
    public:
        BatchUpdater(const Transformer & base, int nSize) : _BatchUpdater<Transformer, nData>(base, nSize){}
    };

    template <> 
    class BatchUpdater<matrix44, matrix44> : public _BatchUpdater<matrix44, matrix44>{
    public:
        BatchUpdater(const matrix44 & base, int nData) :_BatchUpdater<matrix44,matrix44>(base,nData) {}
        ~BatchUpdater(){}

        void performMult() {
            std::cout << "inside: "  << getCurrent()->getName() << std::endl;
            getCurrent()->batchm44mul((float4*)data, transformator, sizeData);
        }
    };

}


#endif