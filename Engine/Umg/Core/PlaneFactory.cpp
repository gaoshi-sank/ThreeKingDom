#include "PlaneFactory.h"
#include "../../FIleControl/FileControl.h"

// ����
PlaneSetting::PlaneSetting() {
	// ��������
	uiId = 0x00;		// UI�ɱ�ʶID
	uiType = 0x00;		// UI����
	x = 0;				// ����X��
	y = 0;				// ����Y��
	width = 0;			// ���ƿ��
	height = 0;			// ���Ƹ߶�
	res = 0;			// ��Դ��־λ
	resPath = "";		// ��Դ·��
	option = 0;			// ����Plane���ǵ�������

	// ��������
	lable_title = "";

	button_title = "";
	resPath_buttonType = UI_Button::ButtonStyle_Once;		// ��ť��Դ���
	resPath_out = "";
	resPath_in = "";
	resPath_down = "";
	resPath_disable = "";

	resPath_checkBoxType = 4;
}

// ����
PlaneSetting::~PlaneSetting() {

}

// �����ļ�����һ��UI_Plane
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
					// һ������
					std::shared_ptr<PlaneSetting> _data = std::make_shared<PlaneSetting>();
					if (!_data) {
						break;
					}

					// ����
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

					// ��ȡ����
					// �½�UI
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

					// ��������
					if (_newui) {
						_newui->SetLocation(_data->x, _data->y);
						_newui->SetSize(_data->width, _data->height);

						// �ر�����
						switch (_data->uiType) {
						case UI_Base::UIStyle_Lable:
						{
							auto alise_lable = (UI_Lable*)(_newui);

							// ͼ�� �� �ı�
							alise_lable->Create(_data->resPath, _data->x, _data->y, _data->width, _data->height);
							alise_lable->AddStaticText(_data->lable_title);

							break;
						}
						case UI_Base::UIStyle_Button:
						{
							auto alise_button = (UI_Button*)(_newui);

							// ͼ�� �� �ı�
							if (_data->resPath_buttonType == UI_Button::ButtonStyle_Once) {
								alise_button->Create(_data->resPath, _data->x, _data->y, _data->width, _data->height);
							}
							else if (_data->resPath_buttonType == UI_Button::ButtonStyle_Four) {
								alise_button->Create(_data->resPath_out, _data->resPath_in, _data->resPath_down, _data->resPath_disable);
								alise_button->SetLocation(_data->x, _data->y);		// δָ��λ�úʹ�С����Ҫ��������
								alise_button->SetSize(_data->width, _data->height);
							}
							alise_button->AddStaticText(_data->lable_title);

							// �����¼�
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

							// ͼ�� �� �ı�
							// һ��ͼ
							if (_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_OneOnce || 
								_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_ChangeOp_Once) {
								alise_checkbox->Create(_data->resPath, _data->x, _data->y, _data->width, _data->height, _data->resPath_checkBoxType);
							}
							// ����ͼ
							else if (_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_OneFour) {
								alise_checkbox->Create(_data->resPath_out, _data->resPath_in, _data->resPath_down, _data->resPath_disable);
								alise_checkbox->SetLocation(_data->x, _data->y);		// δָ��λ�úʹ�С����Ҫ��������
								alise_checkbox->SetSize(_data->width, _data->height);
							}
							// ����ͼ - δʵװ
							else if (_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_ChangeOp_Two) {
								
							}
							alise_checkbox->AddStaticText(_data->lable_title);
							break;
						}
							break;
						}
					}

					// ��װ
					if (_newui) {
						_plane->AddAttachedUI(_newui);
					}

					// ��սṹ��
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

// �����ļ�����һϵ��UI
std::vector<UI_Base*> PlaneFactory::BuildUIByFile(const char* filename, std::function<void(int, int, int, int)> _callback) {
	std::vector<UI_Base*> ListResult;
	if (filename) {
		FILE* fp = fopen(filename, "r");
		if (fp) {
			while (1) {
				std::vector<StringMap> result;
				auto ret = FileControl::ReadJson(result, fp);
				if (ret == 2) {
					// һ������
					std::shared_ptr<PlaneSetting> _data = std::make_shared<PlaneSetting>();
					if (!_data) {
						break;
					}

					// ����
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

					// ��ȡ����
					// �½�UI
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

					// ��������
					if (_newui) {
						_newui->SetLocation(_data->x, _data->y);
						_newui->SetSize(_data->width, _data->height);

						// �ر�����
						switch (_data->uiType) {
						case UI_Base::UIStyle_Lable:
						{
							auto alise_lable = (UI_Lable*)(_newui);

							// ͼ�� �� �ı�
							alise_lable->Create(_data->resPath, _data->x, _data->y, _data->width, _data->height);
							alise_lable->AddStaticText(_data->lable_title);

							break;
						}
						case UI_Base::UIStyle_Button:
						{
							auto alise_button = (UI_Button*)(_newui);

							// ͼ�� �� �ı�
							if (_data->resPath_buttonType == UI_Button::ButtonStyle_Once) {
								alise_button->Create(_data->resPath, _data->x, _data->y, _data->width, _data->height);
							}
							else if (_data->resPath_buttonType == UI_Button::ButtonStyle_Four) {
								alise_button->Create(_data->resPath_out, _data->resPath_in, _data->resPath_down, _data->resPath_disable);
								alise_button->SetLocation(_data->x, _data->y);		// δָ��λ�úʹ�С����Ҫ��������
								alise_button->SetSize(_data->width, _data->height);
							}
							alise_button->AddStaticText(_data->lable_title);

							// �����¼�
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

							// ͼ�� �� �ı�
							// һ��ͼ
							if (_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_OneOnce ||
								_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_ChangeOp_Once) {
								alise_checkbox->Create(_data->resPath, _data->x, _data->y, _data->width, _data->height, _data->resPath_checkBoxType);
							}
							// ����ͼ
							else if (_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_OneFour) {
								alise_checkbox->Create(_data->resPath_out, _data->resPath_in, _data->resPath_down, _data->resPath_disable);
								alise_checkbox->SetLocation(_data->x, _data->y);		// δָ��λ�úʹ�С����Ҫ��������
								alise_checkbox->SetSize(_data->width, _data->height);
							}
							// ����ͼ - δʵװ
							else if (_data->resPath_buttonType == UI_CheckBox::CheckBoxStyle_ChangeOp_Two) {

							}
							alise_checkbox->AddStaticText(_data->lable_title);
							break;
						}
						break;
						}

						// �����б�
						ListResult.push_back(_newui);
					}

					// ��սṹ��
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