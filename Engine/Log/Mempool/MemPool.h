/*
* 简单内存池实现
*/
#ifndef _MemPool_h_
#define _MemPool_h_

#include <string.h>
#include <mutex>

// 内存节点
class BufferNode {
public:
	unsigned char* _data;			// 数据
	unsigned int len;				// 数据长度
	bool isUsing;					// 状态
	BufferNode* _next;				// 单链表指向

	// 构造
	BufferNode();

	// 构造 - 参数1
	BufferNode(int other_len);

	// 析构
	~BufferNode();

	// 释放
	// 重新置0
	void ReleaseBuffer();

	// 复制构造
	BufferNode(const BufferNode& other) = delete;
	
	// 重载 =运算符
	BufferNode& operator=(const BufferNode& other) = delete;
};



// 分配池
class MemPool {
private:
	BufferNode* _head;
	std::mutex lock;

public:
	// 构造
	MemPool();

	// 构造 - 参数1
	MemPool(int count, int bufferLen);

	// 析构
	~MemPool();

	// 模板类只能在头文件实现
	// 获取
	template<class T>
	T* GetBuffer(unsigned int len) {
		// 无效长度
		if (len <= 0) {
			return nullptr;
		}

		// 遍历查看是否有空闲节点
		bool isfound = false;
		auto found_node = this->_head;
		while (found_node) {
			if (found_node->len >= len && !found_node->isUsing) {
				isfound = true;
				break;
			}
			found_node = found_node->_next;
		}

		// 有
		if (isfound) {
			found_node->isUsing = true;
			return (T*)(found_node->_data);
		}
		// 无 - 重新new一个
		else {
			std::lock_guard<std::mutex> lc(lock);
			auto nexthead = this->_head;
			while (nexthead) {
				if (nexthead->_next) {
					nexthead = nexthead->_next;
				}
				else {
					break;
				}
			}

			if (nexthead) {
				auto newnode = new BufferNode(len);
				if (newnode) {
					newnode->isUsing = true;
					nexthead->_next = newnode;
					return (T*)(newnode->_data);
				}
			}
			
		}
		return nullptr;
	}

	// 释放
	void ReleaseBuffer(void* release_node);

};


#endif // !_MemPool_h_
