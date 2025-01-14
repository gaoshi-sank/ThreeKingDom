#include "MemPool.h"

// 构造
BufferNode::BufferNode() {
	_data = nullptr;
	len = 0;
	isUsing = false;
	_next = nullptr;
}


// 构造 - 参数1
BufferNode::BufferNode(int other_len) : BufferNode() {
	if (other_len > 0) {
		this->len = other_len;
		this->_next = nullptr;
		this->_data = new unsigned char[len];
		memset(this->_data, '\0', sizeof(unsigned char) * len);
	}
}

// 析构
BufferNode::~BufferNode() {
	if (_data) {
		delete _data;
		_data = nullptr;
	}

	if (_next) {
		delete _next;
		_next = nullptr;
	}
}

// 释放
// 重新置0
void BufferNode::ReleaseBuffer() {
	if (this->_data) {
		memset(this->_data, '\0', sizeof(unsigned char) * len);
	}
}

// 构造
MemPool::MemPool() {
	_head = nullptr;
}

// 构造 - 参数1
MemPool::MemPool(int count, int bufferLen) : MemPool() {
	count = (count <= 0) ? 10 : count;
	bufferLen = (bufferLen <= 0) ? 128 : count;
	
	_head = new BufferNode(bufferLen);
	if (_head) {
		BufferNode* head = _head;
		for (auto i = 1; i < count;i++) {
			auto newnode = new BufferNode(bufferLen);
			if (newnode) {
				head->_next = newnode;
				head = newnode;
			}
			else {
				// 生成内容失败
			}
		}
	}
}

// 析构
MemPool::~MemPool() {
	if (_head) {
		delete _head;
		_head = nullptr;
	}
}

// 释放
void MemPool::ReleaseBuffer(void* releasenode) {
	if (releasenode) {
		auto head = this->_head;
		while (head) {
			if (releasenode == head) {
				head->isUsing = false;
				head->ReleaseBuffer();
				break;
			}
			head = head->_next;
		}
	}
}