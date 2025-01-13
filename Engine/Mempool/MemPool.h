/*
* ���ڴ��ʵ��
*/
#ifndef _MemPool_h_
#define _MemPool_h_

#include "string.h"

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
		auto head = this->_head;
		while (head) {
			if (head->len >= len && !head->isUsing) {
				isfound = true;
				break;
			}
			head = head->_next;
		}

		// ��
		if (isfound) {
			head->isUsing = true;
			return (T*)(head->_data);
		}
		// �� - ����newһ��
		else {
			auto nexthead = this->_head;
			while (nexthead->_next) nexthead = nexthead->_next;
			auto newnode = new BufferNode(len);
			if (newnode) {
				newnode->isUsing = true;
				nexthead->_next = newnode;
				return (T*)(newnode->_data);
			}
		}

		return nullptr;
	}

	// �ͷ�
	void ReleaseBuffer(void* head);

};


#endif // !_MemPool_h_
