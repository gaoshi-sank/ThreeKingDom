#include "PlaneFactory.h"
#include "../../FIleControl/FileControl.h"

// 构造
PlaneSetting::PlaneSetting() {
	// 基础属性
	uiId = 0x00;		// UI可辨识ID
	uiType = 0x00;		// UI类型
	x = 0;				// 绘制X点
	y = 0;				// 绘制Y点
	width = 0;			// 绘制宽度
	height = 0;			// 绘制高度
	res = 0;			// 资源标志位
	resPath = "";		// 资源路径
	option = 0;			// 生成Plane还是单独存在

	// 特殊属性
	lable_title = "";

	button_title = "";
	resPath_buttonType = UI_Button::ButtonStyle_Once;		// 按钮资源风格
	resPath_out = "";
	resPath_in = "";
	resPath_down = "";
	resPath_disable = "";

	resPath_checkBoxType = 4;
}

// 析构
PlaneSetting::~PlaneSetting() {

}

// 根据文件生成一个UI_Plane
UI_Plane* PlaneFactory::BuildOnePlane(const char* filename) {
	UI_Plane* _plane = nullptr;
	if (filename) {
		FILE* fp = fopen(filename, "r");
		if (fp) {
			_plane = new UI_Plane();
			if (!_plane) {
				fclose(fp);
				return nullptr;
			}

			while (1) {
				std::vector<StringMap> result;
				auto ret = FileControl::ReadJson(result, fp);
				if (ret == 2) {
					// 一个数据
					std::shared_ptr<PlaneSetting> _data = std::make_shared<PlaneSetting>();
					if (!_data) {
						break;
					}

					// 分歧
					for (auto& key_value : result) {
						if (!key_value.Empty()) {
							auto& key = key_value.key;
							auto& value = key_value.value;

							if (key.compare("uiType") == 0) {
								if (value.compare("Lable") == 0) {
									_data->uiType = UI_Base::UIStyle_Lable;
								}
								else if (value.compare("Button") == 0) {
									_data->uiType = UI_Base::UIStyle_Button;
								}
								else if (value.compare("CheckBox") == 0) {
									_data->uiType = UI_Base::UIStyle_CheckBox;
								}
							}
							else if (key.compare("x") == 0) {
								_data->x = std::atoi(value.c_str());
							}
							else if (key.compare("y") == 0) {
								_data->y = std::atoi(value.c_str());
							}
							else if (key.compare("width") == 0) {
								_data->width = std::atoi(value.c_str());
							}
							else if (key.compare("height") == 0) {
								_data->height = std::atoi(value.c_str());
							}
							else if (key.compare("res") == 0) {
								_data->res = std::atoi(value.c_str());
							}
							else if (key.compare("resPath") == 0) {
								_data->resPath = FileControl::ResPath(value);
							}
							else if (key.compare("option") == 0) {
								_data->option = std::atoi(value.c_str());
							}
							else if (key.compare("lable_title") == 0) {
								_data->lable_title = value;
							}
							else if (key.compare("button_title") == 0) {
								_data->button_title = value;
							}
							else if (key.compare("ButtonType") == 0) {
								_data->resPath_buttonType = std::atoi(value.c_str());
							}
							else if (key.compare("resPath_out") == 0) {
								_data->button_title = FileControl::ResPath(value);
							}
							else if (key.compare("resPath_in") == 0) {
								_data->button_title = FileControl::ResPath(value);
							}
							else if (key.compare("resPath_down") == 0) {
								_data->button_title = FileControl::ResPath(value);
							}
							else if (key.compare("resPath_disable") == 0) {
								_data->button_title = FileControl::ResPath(value);
							}
							else if (key.compare("resPath_checkBoxType") == 0) {
								_data->resPath_checkBoxType = (std::atoi(value.c_str()) == 4) ? 4 : 2;
							}
						}
					}

					// 读取结束
					// 新建UI
					UI_Base* _newui = nullptr;
					switch (_data->uiType) {
					case UI_Base::UIStyle_Lable:
						_newui = new UI_Lable();
						break;
					case UI_Base::UIStyle_Button:
						_newui = new UI_Button();
						break;
					case UI_Base::UIStyle_CheckBox:
						_newui = new UI_CheckBox();
						break;
					}

					// 设置属性
					if (_newui) {
						_newui->SetLocation(_data->x, _data->y);
						_newui->SetSize(_data->width, _data->height);

						// 特别属性
						switch (_data->uiType) {
						case UI_Base::UIStyle_Lable:
						{
							auto alise_lable = (UI_Lable*)(_newui);

							// 图像 和 文本
							alise_lable->Create(_data->resPath, _data->x, _data->y, _data->width, _data->height);
							alise_lable->AddStaticText(_data->lable_title);

							break;
						}
						case UI_Base::UIStyle_Button:
						{
							auto alise_button = (UI_Button*)(_newui);

							// 图像 和 文本
							if (_data->resPath_buttonType == UI_Button::ButtonStyle_Once) {
								alise_button->Create(_data->resPath, _data->x, _data->y, _data->width, _data->height);
							}
							else if (_data->resPath_buttonType == UI_Button::ButtonStyle_Four) {
								alise_button->Create(_data->resPath_out, _data->resPath_in, _data->resPath_down, _data->resPath_disable);
								alise_button->SetLocation(_data->x, _data->y);		// 未指定位置和大小，需要重新设置
								alise_button->SetSize(_data->width, _data->height);
							}
							alise_button->AddStaticText(_data->lable_title);

							// 触发事件
							alise_button->Event_Hover([_plane](int id) {
								_plane->Event_Control(UI_Base::UIStyle_Button, id, UI_Base::UIMsgType_Hover, 1);
							});
							alise_button->Event_Click([_plane](int id) {
								_plane->Event_Control(UI_Base::UIStyle_Button, id, UI_Base::UIMsgType_Click, 1);
							});
							alise_button->Event_Down([_plane](int id) {
								_plane->Event_Control(UI_Base::UIStyle_Button, id, UI_Base::UIMsgType_Down, 1);
							});
							alise_button->Event_Up([_plane](int id) {
								_plane->Event_Control(UI_Base::UIStyle_Button, id, UI_Base::UIMsgType_Up, 1);
							});

							break;
						}
						case UI_Base::UIStyle_CheckBox:
						{
							auto alise_checkbox = (UI_CheckBox*)(_newui);

							// 图像 和 文本
							// 一张图
							if (_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_OneOnce || 
								_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_ChangeOp_Once) {
								alise_checkbox->Create(_data->resPath, _data->x, _data->y, _data->width, _data->height, _data->resPath_checkBoxType);
							}
							// 四张图
							else if (_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_OneFour) {
								alise_checkbox->Create(_data->resPath_out, _data->resPath_in, _data->resPath_down, _data->resPath_disable);
								alise_checkbox->SetLocation(_data->x, _data->y);		// 未指定位置和大小，需要重新设置
								alise_checkbox->SetSize(_data->width, _data->height);
							}
							// 两张图 - 未实装
							else if (_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_ChangeOp_Two) {
								
							}
							alise_checkbox->AddStaticText(_data->lable_title);
							break;
						}
							break;
						}
					}

					// 填装
					if (_newui) {
						_plane->AddAttachedUI(_newui);
					}

					// 清空结构体
					result.clear();
				}
				else {
					break;
				}
			}
			fclose(fp);
		}
	}
	return _plane;
}

// 根据文件生成一系列UI
std::vector<UI_Base*> PlaneFactory::BuildUIByFile(const char* filename, std::function<void(int, int, int, int)> _callback) {
	std::vector<UI_Base*> ListResult;
	if (filename) {
		FILE* fp = fopen(filename, "r");
		if (fp) {
			while (1) {
				std::vector<StringMap> result;
				auto ret = FileControl::ReadJson(result, fp);
				if (ret == 2) {
					// 一个数据
					std::shared_ptr<PlaneSetting> _data = std::make_shared<PlaneSetting>();
					if (!_data) {
						break;
					}

					// 分歧
					for (auto& key_value : result) {
						if (!key_value.Empty()) {
							auto& key = key_value.key;
							auto& value = key_value.value;

							if (key.compare("uiType") == 0) {
								if (value.compare("Lable") == 0) {
									_data->uiType = UI_Base::UIStyle_Lable;
								}
								else if (value.compare("Button") == 0) {
									_data->uiType = UI_Base::UIStyle_Button;
								}
								else if (value.compare("CheckBox") == 0) {
									_data->uiType = UI_Base::UIStyle_CheckBox;
								}
							}
							else if (key.compare("x") == 0) {
								_data->x = std::atoi(value.c_str());
							}
							else if (key.compare("y") == 0) {
								_data->y = std::atoi(value.c_str());
							}
							else if (key.compare("width") == 0) {
								_data->width = std::atoi(value.c_str());
							}
							else if (key.compare("height") == 0) {
								_data->height = std::atoi(value.c_str());
							}
							else if (key.compare("res") == 0) {
								_data->res = std::atoi(value.c_str());
							}
							else if (key.compare("resPath") == 0) {
								_data->resPath = FileControl::ResPath(value);
							}
							else if (key.compare("option") == 0) {
								_data->option = std::atoi(value.c_str());
							}
							else if (key.compare("lable_title") == 0) {
								_data->lable_title = value;
							}
							else if (key.compare("button_title") == 0) {
								_data->button_title = value;
							}
							else if (key.compare("ButtonType") == 0) {
								_data->resPath_buttonType = std::atoi(value.c_str());
							}
							else if (key.compare("resPath_out") == 0) {
								_data->button_title = FileControl::ResPath(value);
							}
							else if (key.compare("resPath_in") == 0) {
								_data->button_title = FileControl::ResPath(value);
							}
							else if (key.compare("resPath_down") == 0) {
								_data->button_title = FileControl::ResPath(value);
							}
							else if (key.compare("resPath_disable") == 0) {
								_data->button_title = FileControl::ResPath(value);
							}
							else if (key.compare("resPath_checkBoxType") == 0) {
								_data->resPath_checkBoxType = (std::atoi(value.c_str()) == 4) ? 4 : 2;
							}
						}
					}

					// 读取结束
					// 新建UI
					UI_Base* _newui = nullptr;
					switch (_data->uiType) {
					case UI_Base::UIStyle_Lable:
						_newui = new UI_Lable();
						break;
					case UI_Base::UIStyle_Button:
						_newui = new UI_Button();
						break;
					case UI_Base::UIStyle_CheckBox:
						_newui = new UI_CheckBox();
						break;
					}

					// 设置属性
					if (_newui) {
						_newui->SetLocation(_data->x, _data->y);
						_newui->SetSize(_data->width, _data->height);

						// 特别属性
						switch (_data->uiType) {
						case UI_Base::UIStyle_Lable:
						{
							auto alise_lable = (UI_Lable*)(_newui);

							// 图像 和 文本
							alise_lable->Create(_data->resPath, _data->x, _data->y, _data->width, _data->height);
							alise_lable->AddStaticText(_data->lable_title);

							break;
						}
						case UI_Base::UIStyle_Button:
						{
							auto alise_button = (UI_Button*)(_newui);

							// 图像 和 文本
							if (_data->resPath_buttonType == UI_Button::ButtonStyle_Once) {
								alise_button->Create(_data->resPath, _data->x, _data->y, _data->width, _data->height);
							}
							else if (_data->resPath_buttonType == UI_Button::ButtonStyle_Four) {
								alise_button->Create(_data->resPath_out, _data->resPath_in, _data->resPath_down, _data->resPath_disable);
								alise_button->SetLocation(_data->x, _data->y);		// 未指定位置和大小，需要重新设置
								alise_button->SetSize(_data->width, _data->height);
							}
							alise_button->AddStaticText(_data->lable_title);

							// 触发事件
							alise_button->Event_Hover([=](int id) {
								if (_callback) {
									_callback(UI_Base::UIStyle_Button, id, UI_Base::UIMsgType_Hover, 1);
								}
							});
							alise_button->Event_Click([=](int id) {
								if (_callback) {
									_callback(UI_Base::UIStyle_Button, id, UI_Base::UIMsgType_Click, 1);
								}
							});
							alise_button->Event_Down([=](int id) {
								if (_callback) {
									_callback(UI_Base::UIStyle_Button, id, UI_Base::UIMsgType_Down, 1);
								}
							});
							alise_button->Event_Up([=](int id) {
								if (_callback) {
									_callback(UI_Base::UIStyle_Button, id, UI_Base::UIMsgType_Up, 1);
								}
							});

							break;
						}
						case UI_Base::UIStyle_CheckBox:
						{
							auto alise_checkbox = (UI_CheckBox*)(_newui);

							// 图像 和 文本
							// 一张图
							if (_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_OneOnce ||
								_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_ChangeOp_Once) {
								alise_checkbox->Create(_data->resPath, _data->x, _data->y, _data->width, _data->height, _data->resPath_checkBoxType);
							}
							// 四张图
							else if (_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_OneFour) {
								alise_checkbox->Create(_data->resPath_out, _data->resPath_in, _data->resPath_down, _data->resPath_disable);
								alise_checkbox->SetLocation(_data->x, _data->y);		// 未指定位置和大小，需要重新设置
								alise_checkbox->SetSize(_data->width, _data->height);
							}
							// 两张图 - 未实装
							else if (_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_ChangeOp_Two) {

							}
							alise_checkbox->AddStaticText(_data->lable_title);
							break;
						}
						break;
						}

						// 加入列表
						ListResult.push_back(_newui);
					}

					// 清空结构体
					result.clear();
				}
				else {
					break;
				}
			}
			fclose(fp);
		}
	}

	return ListResult;
}