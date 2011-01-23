
#include <xmmintrin.h>
#include <vector>
#include <iostream>

#include "math3d/core/core.h"

// create pages of 16kB
#define PAGE_SIZE 16 * 1024

namespace {
    struct MemoryPage {

        MemoryPage(size_t _alignment, size_t page_pool_size) {
            ref_count = 0;    
            alignment = _alignment;
            pool_size = page_pool_size;
            page_pool = (char*)_mm_malloc(pool_size, alignment);
            next_ptr = page_pool;
        }

        ~MemoryPage() {
            _mm_free(page_pool);
        }

        void * alloc(size_t size) {
            this->ref_count++;
            void * to_return = next_ptr;
            next_ptr += size_offset(size);
            return to_return;
        }

        void release(void * p) {
            --ref_count;
            if(ref_count == 0) {
                next_ptr = page_pool;
            }
        }

        bool can_alloc(size_t size) {
            return (next_ptr + size) <= (page_pool + pool_size);
        }

        bool contains(void * ptr) {
            char * _ptr = static_cast<char*>(ptr);
            return (_ptr >= page_pool && _ptr <= page_pool + pool_size);
        }

        void print_page_info() {
            std::cout << "page pool address: " << (void*)page_pool << std::endl;
            std::cout << "next ptr address: " << (void*)next_ptr << std::endl;
            std::cout << "reference count: " << ref_count << std::endl;
            std::cout << "page alignment: " << alignment << std::endl;
            std::cout << "page size: " << pool_size << std::endl;
            std::cout << std::endl;
        }

        char * page_pool;

        char * next_ptr;
        
        size_t ref_count;
        
        size_t alignment;

        size_t pool_size;

    private:
        inline size_t size_offset(size_t size) {
            if(size % alignment == 0) return size;
            size_t offset = 0;
            while(offset < size) offset += alignment;
            return offset;
        }
    };
    
    typedef std::vector<MemoryPage*> page_list;

    page_list pages;

    MemoryPage * searchPageThatCanAlloc(size_t size, size_t align) {
        page_list::iterator it;
        MemoryPage * page = NULL;
        for(it = pages.begin(); it != pages.end(); it++) {
            if((*it)->alignment == align && (*it)->can_alloc(size)) {
                page = *it;
                break;
            }
        }
        if(page == NULL) {
            page = new MemoryPage(align, size > PAGE_SIZE ? size : PAGE_SIZE);
            pages.push_back(page);
        }
        return page;
    }

    MemoryPage * searchPageThatContains(void * ptr) {
        page_list::iterator it;
        MemoryPage * page = NULL;
        for(it = pages.begin(); it != pages.end(); it++) {
            if((*it)->contains(ptr)) {
                page = *it;
                break;
            }
        }
        return page;
    }
}

namespace math3d {
    void print_internal_memory_page_info() {
        page_list::iterator it;
        for(it = pages.begin(); it != pages.end(); it++) 
            (*it)->print_page_info();
        std::cout << "number of pages: " << pages.size() << std::endl;
    }

    void * internal_malloc(size_t size, size_t align) {
        MemoryPage * page = searchPageThatCanAlloc(size, align);
        void * ptr = page->alloc(size);
        return ptr;
    }

    void internal_free(void * p) {
        MemoryPage * page = searchPageThatContains(p);
        if(page != NULL)
            page->release(p);
    }

}