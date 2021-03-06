
#include <xmmintrin.h>
#include <vector>
#include <iostream>
#include <algorithm>

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

        inline size_t memory_used() {
            return (size_t)(next_ptr - page_pool);
        }

        inline size_t memory_free() {
            return pool_size - memory_used();
        }

        void print_page_info() {
            std::cout << "page pool address: " << (void*)page_pool << std::endl;
            std::cout << "next ptr address: " << (void*)next_ptr << std::endl;
            std::cout << "reference count: " << ref_count << std::endl;
            std::cout << "page alignment: " << alignment << std::endl;
            std::cout << "page size: " << pool_size << std::endl;
            std::cout << "memory used: " << memory_used() << std::endl;
            std::cout << "memory free: " << pool_size - memory_used() << std::endl;
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

    void releasePage(MemoryPage * page) {
        page_list::iterator location = std::find(pages.begin(), pages.end(), page);
        pages.erase(location);
    }
}

namespace math3d {
    void print_internal_memory_page_info() {
        page_list::iterator it;
        
        size_t total_memory = 0;
        size_t free_memory = 0;
        size_t total_used = 0;
        
        std::cout << "======= starting memory report =======" << std::endl;
        for(it = pages.begin(); it != pages.end(); it++) {
            (*it)->print_page_info();
            total_memory += (*it)->pool_size;
            free_memory += (*it)->memory_free();
            total_used += (*it)->memory_used();
        }
        std::cout << "number of pages: " << pages.size() << std::endl;
        std::cout << "total memory allocated: " << total_memory << std::endl;
        std::cout << "total free memory: " << free_memory << std::endl;
        std::cout << "total used: " << total_used << std::endl;

        std::cout << "======== end of memory report ========" << std::endl << std::endl;
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
        if(page->ref_count == 0) 
            releasePage(page);
    }

}