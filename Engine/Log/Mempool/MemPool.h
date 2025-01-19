/*
* ���ڴ��ʵ��
*/
#ifndef _MemPool_h_
#define _MemPool_h_

#include <string.h>
#include <mutex>

// �ڴ�ڵ�
class BufferNode {
public:
	unsigned char* _data;			// ����
	unsigned int len;				// ���ݳ���
	bool isUsing;					// ״̬
	BufferNode* _next;				// ������ָ��

	// ����
	BufferNode();

	// ���� - ����1
	BufferNode(int other_len);

	// ����
	~BufferNode();

	// �ͷ�
	// ������0
	void ReleaseBuffer();

	// ���ƹ���
	BufferNode(const BufferNode& other) = delete;
	
	// ���� =�����
	BufferNode& operator=(const BufferNode& other) = delete;
};



// �����
class MemPool {
private:
	BufferNode* _head;
	std::mutex lock;

public:
	// ����
	MemPool();

	// ���� - ����1
	MemPool(int count, int bufferLen);

	// ����
	~MemPool();

	// ģ����ֻ����ͷ�ļ�ʵ��
	// ��ȡ
	template<class T>
	T* GetBuffer(unsigned int len) {
		// ��Ч����
		if (len <= 0) {
			return nullptr;
		}

		// �����鿴�Ƿ��п��нڵ�
		bool isfound = false;
		auto found_node = this->_head;
		while (found_node) {
			if (found_node->len >= len && !found_node->isUsing) {
				isfound = true;
				break;
			}
			found_node = found_node->_next;
		}

		// ��
		if (isfound) {
			found_node->isUsing = true;
			return (T*)(found_node->_data);
		}
		// �� - ����newһ��
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

	// �ͷ�
	void ReleaseBuffer(void* release_node);

};


#endif // !_MemPool_h_
