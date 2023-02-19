#ifndef HEAP_H
#define HEAP_H

#include<vector>
#include<iostream>
#include<map>

template<typename KEY, typename DATA>
class BinaryHeap{
private:
    int m_size;
    std::vector<KEY> m_key;
    std::vector<DATA> m_data; //pointer to a record
    std::map<DATA, int> m_index_of_data; 

    void up_heap(int index){
        KEY k = m_key[index];
        DATA d = m_data[index];
        while(index>0 and k<m_key[(index-1)/2]){
            m_key[index] = m_key[(index-1)/2];
            m_data[index] = m_key[(index-1)/2];
            m_index_of_data[m_data[index]] = index;
            index = (index-1)/2;
        }
        m_key[index] = k;
        m_data[index] = d;
        m_index_of_data[m_data[index]]=index;
    }

    void down_heap(int index){
        KEY k = m_key[index];
        DATA d = m_data[index];
        int j = 2*index +2;
        while(j<m_size){
            if(m_key[j-1]<m_key[j]) j-=1;
            if(m_key[j]<k){
                m_key[index] = m_key[j];
                m_data[index] = m_data[j];
                m_index_of_data[m_data[index]]=index;
                index = j;
                j = 2*index + 2;
            } else {
                j = m_size + 1;
            }
        }
        --j;
        if(j==m_size-1 and m_key[j]<k){
            m_key[index] = m_key[j];
            m_data[index] = m_data[j];
            m_index_of_data[m_data[index]]=index;
            index=j;
        }
        m_key[index] = k;
        m_data[index] = d;
        m_index_of_data[m_data[index]]=index;
    }

public:
    BinaryHeap()
        : m_size{0}
    {}

    void insert(KEY k, DATA data){
        if(m_key.size()>m_size){
            m_key[m_size] = k;
            m_data[m_size] = data;
        } else {
            m_key.push_back(k);
            m_data.push_back(data);
        }
        ++m_size;
        m_index_of_data[data] = m_size-1;
        up_heap(m_size-1);
    }

    DATA del_min(){
        if(m_size<=0){
            throw "Delete from empty heap!";
        }
        KEY temp_k = m_key[0];
        DATA temp_d = m_data[0];
        m_key[0] = m_key[m_size-1];
        m_data[0] = m_data[m_size-1];
        m_index_of_data[m_data[0]] = 0;
        m_key[m_size-1] = temp_k;
        m_data[m_size-1] = temp_d;
        m_index_of_data[m_data[m_size-1]] = m_size-1;
        --m_size;
        down_heap(0);
        return m_data[m_size];
    }

    void decrease_key(DATA d, KEY diff){
        int index = m_index_of_data.at(d); //throw std::out_of_range if d is invalid
        m_key[index] -=diff;
        up_heap(index);
    }

    int size() const {return m_size;}

    int empty()const {return m_size==0;}

    friend std::ostream& operator<<(std::ostream& out, const BinaryHeap& h){
        out << "Heap(size=" << h.m_size << "): ";
        for(int i=0; i<h.m_size; ++i){
            out << h.m_key[i] << ' ';
        }
        return out;
    }
};

#endif