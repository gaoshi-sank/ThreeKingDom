#include "UI_Excel.h"

// 构造
UI_Excel::UI_Excel() {
	// 窗口类型 
	window_style = UIStyle_Excel;

	// 基础属性
	object_text = new SText();
	object_background = nullptr;
	maxlength = 1;
	isbuild = true;

}

// 析构
UI_Excel::~UI_Excel() {
	// 文本
	for (auto& text : list_texts) {
		if (text) {
			delete text;
			text = nullptr;
		}
	}
	list_texts.clear();

	if (object_text) {
		delete object_text;
		object_text = nullptr;
	}
}

// 创建
bool UI_Excel::Create() {
	if (window_release) {
		return false;
	}
	return true;
}

// 创建
// 参数：位置和大小
bool UI_Excel::Create(const std::string& filename, int x, int y, int w, int h) {
	if (!Create()) {
		return false;
	}

	if (!filename.empty() && !object_background) {
		object_background = new SImage(filename.c_str());
		if (!object_background) {
			return false;
		}
	}

	SetLocation(x, y);
	SetSize(w, h);
	return true;
}


// 增加字符
void UI_Excel::AddText(std::string _text) {
	ExcelText* onetext = new ExcelText();
	if (list_texts.size() < maxlength && onetext) {
		int index = (int)(list_texts.size());
		onetext->_text = _text;
		onetext->rect_x = window_x;
		onetext->rect_y = window_y;
		onetext->rect_width = window_width;
		onetext->rect_height = window_height;
		list_texts.push_back(onetext);
	}
	
	if (object_text && list_texts.size() >= 1) {
		object_text->ReSetText(list_texts[0]->_text.c_str());
		object_text->ReSetLayout();
	}
}

// 根据位置增加字符
void UI_Excel::AddText(int x, int y, std::string _text) {
	ExcelText* onetext = new ExcelText();
	if (onetext) {
		float width = window_width * 1.0f / maxlength;
		float height = window_height / 10.0f;
		height = (height > 24.0f) ? 24.0f : height;

		onetext->_text = _text;
		onetext->rect_x = (int)(window_x + x * width);
		onetext->rect_y = (int)(window_y + (y - 1) * height);
		onetext->rect_width = (int)width;
		onetext->rect_height = (int)height;
		list_texts.push_back(onetext);
	}

	if (object_text && list_texts.size() >= 1 && isbuild) {
		object_text->ReSetText(list_texts[0]->_text.c_str());
		isbuild = false;
	}
}

// 设置最大长度
void UI_Excel::SetMaxValue(int _maxlength) {
	maxlength = _maxlength;
}

// 设备背景
void UI_Excel::SetBackGround(const char* filename) {
	if (filename) {
		object_background = new SImage(filename);
		if (object_background) {
			object_background->SetLocation(window_x, window_y);
			object_background->SetSize(window_width, window_height);
		}
	}
}

// 绘制文字颜色
void UI_Excel::SetTextColor(int red, int green, int blue) {
	if (object_text) {
		object_text->ReSetColor(red, green, blue);
		object_text->ReSetLayout();
	}
}

// 设置可见性
void UI_Excel::SetVisiable(bool life) {
	// 背景
	if (object_background) {
		object_background->visiable = life;
	}

	// 绘制对象
	if (object_text) {
		object_text->visiable = life;
	}
}

// 更新 
void UI_Excel::Update() {

}

// 绘制 
void UI_Excel::Draw() {
	if (object_text && this->window_visible) {
		for (auto node : list_texts) {
			object_text->Draw(node->_text, node->rect_x, node->rect_y, node->rect_width, node->rect_height);
		}
	}
}

// 设置位置
void UI_Excel::SetLocation(int x, int y) {

}

// 设置大小
void UI_Excel::SetSize(int w, int h) {

}