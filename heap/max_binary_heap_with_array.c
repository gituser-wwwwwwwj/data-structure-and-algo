#include "max_binary_heap_with_array.h"

item* item_new(int val)
{
    item* new_item = (item *)calloc(1,sizeof(item));
    new_item->val = val;
    return new_item;
}

// item* get_item_from_heap(int index)
// {
//     if(index>=0 && index <capacity)
//     {
//         return heap[index];
//     }
//     printf("访问越界!\n");
//     return NULL;
// }

void heap_init(int size)
{
    heap = (item **)calloc(size, sizeof(item *));
    CAPACITY = size;
    heap_size = 0;
}

//返回堆大小
int size()
{
    return heap_size;
}

//返回堆容量
int capacity()
{
    return CAPACITY;
}

//堆是否为空
int isEmpty()
{
    return heap_size == 0;
}

int isFull()
{
    return heap_size == CAPACITY;
}

//返回指定索引的父索引
int get_parent(int index)
{
    return (index-1)/2;
}

//返回指定索引的左子结点索引
int get_leftChild(int index)
{
    return (index+1)*2-1;
}

//返回指定索引的右子节点索引
int get_rightChild(int index)
{
    return (index+1)*2+1;
}

//插入新item
void add(item* new_item)
{
    if(isFull())
    {
        printf("元素已满!\n");
        return;
    }
    heap[heap_size++] = new_item;
    int cur = size()-1;
    sift_up(cur);
}

// 堆化插入后的新堆，新插入目标上浮
// 思路：重复和父结点比较，大于父结点则和父结点交换，小于父结点即已完成
// 因为是最大堆，小的下沉，大的上浮
void sift_up(int index)
{
    int parent = get_parent(index);
    while (index > 0 && heap[index]->val > heap[parent]->val)
    {
        swap(heap[index], heap[parent]);
        index = get_parent(index);
        parent = get_parent(index);
    }
}

// 下沉，每次先取左子结点，因为在数组中左子结点下标小于右子结点
// 先比较左右子结点， 取最大的子结点与当前值比较
// 因为是最大堆，小的下沉，大的上浮
void sift_down(int index)
{
    while(get_leftChild(index)<size())
    {
        int j = get_leftChild(index);
        //确保j是两个子结点中最大的
        if(j+1 < size() && heap[j+1]->val > heap[j]->val)
        {
            printf("j = %d\n",j);
            j++;
        }
        if(heap[j]->val > heap[index]->val)
        {
            printf("index = %d, j = %d\n",index, j);
            swap(heap[j], heap[index]);
            // printf("%d, %d\n", heap[index]->val, heap[j]->val);
            // printAll();
            index = j;
        }else
        {
            break;
        }
        
    }
}

//查看堆中的最大值
item* peekMax()
{
    return heap[0];
}

//弹出堆中的最大值
//调用后需要free!!
item* popMax()
{
    item* ret = heap[0];
    heap[0] = heap[size()-1];
    heap[size()-1] = NULL;
    heap_size--;
    sift_down(0);
    return ret;
}

//取出最大元素并替换成新插入的
//调用后需要free!!
item* replace(item* new_item)
{
    item* ret = heap[0];
    // free(heap[0]);
    heap[0] = new_item;
    sift_down(0);
    return ret;
}

//堆化一个元素数组
void headpiy(item** arr);

void swap(item* a, item* b)
{
    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}

void printAll()
{
    for(int i = 0;i<heap_size;i++)
    {
        printf("%d ", heap[i]->val);
    }
    printf("\n");
}
