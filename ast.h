#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

struct AST 
    {
    static constexpr size_t NULL_IDX = static_cast<size_t>(-1);

    std::vector<size_t> parent_idx;
    std::vector<size_t> first_child_idx;
    std::vector<size_t> last_child_idx;
    std::vector<size_t> next_sibling_idx;
    std::vector<size_t> metadatas_idx;
    std::vector<size_t> empty_slots;

    size_t create_node(const size_t metadatas) 
    {
        size_t idx;
        if (this->empty_slots.empty()) 
        {
            idx = (size_t)this->parent_idx.size();
            this->metadatas_idx.push_back(metadatas);
            this->parent_idx.push_back(NULL_IDX);
            this->first_child_idx.push_back(NULL_IDX);
            this->last_child_idx.push_back(NULL_IDX);
            this->next_sibling_idx.push_back(NULL_IDX);
        }
        else 
        {
            idx = this->empty_slots.back();
            this->empty_slots.pop_back();
            this->metadatas_idx[idx] = metadatas;
            this->parent_idx[idx] = NULL_IDX;
            this->first_child_idx[idx] = NULL_IDX;
            this->last_child_idx[idx] = NULL_IDX;
            this->next_sibling_idx[idx] = NULL_IDX;
        }
        return idx;
    }
    void add_child(const size_t parent, const size_t child) 
    {
        if (this->parent_idx[child] != NULL_IDX) 
        {
            this->remove_child(this->parent_idx[child], child);
        }

        this->parent_idx[child] = parent;

        if (this->first_child_idx[parent] == NULL_IDX) 
        {
            this->first_child_idx[parent] = child;
            this->last_child_idx[parent] = child;
        }
        else 
        {
            size_t previous_last = this->last_child_idx[parent];
            this->next_sibling_idx[previous_last] = child;
            this->last_child_idx[parent] = child;
        }
        this->next_sibling_idx[child] = NULL_IDX;
    }
    void remove_child(const size_t parent, const size_t child) 
    {
        if (this->first_child_idx[parent] == child) 
        {
            this->first_child_idx[parent] = this->next_sibling_idx[child];
            if (this->first_child_idx[parent] == NULL_IDX) 
            {
                this->last_child_idx[parent] = NULL_IDX;
            }
        }
        else 
        {
            size_t current = this->first_child_idx[parent];
            while (current != NULL_IDX && this->next_sibling_idx[current] != child) 
            {
                current = this->next_sibling_idx[current];
            }

            if (current != NULL_IDX) 
            {
                this->next_sibling_idx[current] = this->next_sibling_idx[child];
                if (this->last_child_idx[parent] == child) 
                {
                    this->last_child_idx[parent] = current;
                }
            }
        }
        this->parent_idx[child] = NULL_IDX;
        this->next_sibling_idx[child] = NULL_IDX;
    }
    void delete_node(const size_t node_idx) 
    {
        size_t current_child = this->first_child_idx[node_idx];
        while (current_child != NULL_IDX) 
        {
            size_t next_v = this->next_sibling_idx[current_child];
            this->delete_node(current_child);
            current_child = next_v;
        }
        size_t p = this->parent_idx[node_idx];
        if (p != NULL_IDX) 
        {
            this->remove_child(p, node_idx);
        }
        this->empty_slots.push_back(node_idx);
    }
    void print_tree(const size_t depth = 0, const size_t index = 0) const 
    {
        if (index == NULL_IDX) return;

        for (size_t i = 0; i < depth; i++) std::cout << "  ";
        std::cout << "-> " << this->metadatas_idx[index] << " (id:" << index << ")\n";

        size_t child = this->first_child_idx[index];
        while (child != NULL_IDX) 
        {
            this->print_tree(depth + 1, child);
            child = this->next_sibling_idx[child];
        }
    }
    void print_all_tree()
    {
        for (size_t idx = 0; idx < this->parent_idx.size(); idx++)
        {
            if (parent_idx[idx] != NULL_IDX)
            {
                print_tree(idx);
                std::cout << "\n";
            }
        }
    }

};

