#pragma once

#include "CommonFunction.h"

//Lớp chuyên xử lí hình ảnh
class BaseObject
{
public:
	//Constructor
	BaseObject();

	//Destructor
	~BaseObject();

	//Khởi tạo thông số cho rect
	void SetRect(const int& x, const int& y) {
		rect_.x = x;
		rect_.y = y;
	}

	//Xuất ra rect
	SDL_Rect GetRect() const { return rect_;}

	//Xuất p_object_
	SDL_Texture* GetObject() const { return p_object_; }

	//Load ảnh bitmap lên p_object_
	bool LoadImage(std::string path, SDL_Renderer* screen);

	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

protected:
	//Lưu trữ hình ảnh
	SDL_Texture* p_object_;

	//Lưu trữ kích thước
	SDL_Rect rect_;
};
