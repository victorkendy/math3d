#include <iostream>
#include <cstdio>
#include <xmmintrin.h>

#define _EXPORT

#include "math3d/core/core.h"
#include "math3d/core/math3d_plugin.h"
#include "math3d/core/math3d_plugin_sse.h"
#include "math3d/core/math3d_plugin_sse3.h"


#ifdef __GNUG__
  #include <cpuid.h>
  inline void _cpuid(int op, unsigned & a, unsigned & b, unsigned & c, unsigned & d){
      __get_cpuid(op, &a, &b, &c, &d);
  }
#else
  #ifdef _MSC_VER
    //#include <intrin.h>
    inline void _cpuid(unsigned op, unsigned & a, unsigned & b, unsigned & c, unsigned & d) {
        unsigned _a, _b, _c, _d;
        _asm {
            MOV eax, 1
            CPUID
            MOV _a, eax
            MOV _b, ebx
            MOV _c, ecx
            MOV _d, edx
        }
        a = _a; b = _b; c = _c; d = _d;
    }
  #endif
#endif


namespace math3d {

    class CPUInfo {
    public:
        bool hasSSE() {
            return ((edx & (1 << 25)) > 0);
        }
        bool hasSSE2() {
            return ((edx & (1 << 26)) > 0);
        }
        bool hasSSE3() {
            return ((ecx & 1) > 0);
        }
        bool hasSSSE3() {
            return ((ecx & (1 << 9)) > 0);
        }
        bool hasSSE4_1() {
            return ((ecx & (1 << 19)) > 0);
        }

        void printInformation() {
            if(hasSSE())
                std::cout << "tem SSE" << std::endl;
            if(hasSSE2())
                std::cout << "tem SSE 2" << std::endl;
            if(hasSSE3())
                std::cout << "tem SSE 3" << std::endl;
            if(hasSSSE3())
                std::cout << "tem SSSE 3" << std::endl;
            if(hasSSE4_1())
                std::cout << "tem SSE 4.1" << std::endl;
        }

        static CPUInfo * getInstance() {
            if(instance == NULL)
                createCPUInfo();
            return instance;
        }
    private:
        static void createCPUInfo() {
            unsigned int a, b, c, d;
            _cpuid(1, a, b, c, d);
            instance = new CPUInfo(a,b,c,d);
        }

        CPUInfo(unsigned _eax, unsigned _ebx, unsigned _ecx, unsigned _edx) {
            eax = _eax; ebx = _ebx; ecx = _ecx; edx=_edx;
        }

        unsigned eax, ebx, ecx, edx;
        static CPUInfo * instance;
    };

    CPUInfo * CPUInfo::instance = NULL;
    
    // Sets a initial implementation in case the user forgets
    static math3dImplementation * currentImplementation = new math3dImplementation();

    math3dImplementation * getImplementation(int which) {
        CPUInfo * info = CPUInfo::getInstance();
        math3dImplementation * implementation;
        if(which == SSE_IMPLEMENTATION && info->hasSSE())
            implementation = new sseImplementation();
        else if(which == SSE3_IMPLEMENTATION && (info->hasSSE3() || info->hasSSSE3()))
            implementation = new sse3Implementation();
        else
            implementation = new math3dImplementation();
        if(currentImplementation)
            delete currentImplementation;
        currentImplementation = implementation;
        return implementation;
    }

    math3dImplementation * getBestImplementation() {
        CPUInfo * info = CPUInfo::getInstance();
        math3dImplementation * implementation;
        if (info->hasSSE3())
            implementation = new sse3Implementation();
        else if(info->hasSSE())
            implementation = new sseImplementation();
        else
            implementation = new math3dImplementation();
        if(currentImplementation)
            delete currentImplementation;
        currentImplementation = implementation;
        return implementation;
    }

    void * aligned_malloc(size_t size, size_t align) {
        return _mm_malloc(size, align);
    }

    void aligned_free(void * ptr) {
        _mm_free(ptr);
    }

    math3dImplementation * getCurrent() {
        return currentImplementation;
    }

    void printCPUInfo() {
        CPUInfo * info = CPUInfo::getInstance();
        info->printInformation();
    }
}
