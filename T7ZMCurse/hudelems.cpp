#include "hudelems.h"

void game_hudelem_s::MoveOverTime(float time, float x, float y) {
	this->elem.fromX = this->elem.x;
	this->elem.fromY = this->elem.y;
	this->elem.moveStartTime = *(uint32_t*)(0x01744A00 + 0x96C);
	this->elem.moveTime = (short)((time * 1000) + 0.5f);
	this->elem.x = x;
	this->elem.y = y;
}

void game_hudelem_s::ScaleFontOverTime(float time, float fontScale) {
	this->elem.fromFontScale = this->elem.fontScale;
	this->elem.fontScaleStartTime = *(uint32_t*)(0x01744A00 + 0x96C);
	this->elem.fontScaleTime = (short)((time * 1000) + 0.5f);
	this->elem.fontScale = fontScale;
}

void game_hudelem_s::ScaleOverTime(float time, short width, short height) {
	this->elem.fromWidth = this->elem.width;
	this->elem.fromHeight = this->elem.height;
	this->elem.scaleStartTime = *(uint32_t*)(0x01744A00 + 0x96C);
	this->elem.scaleTime = (short)((time * 1000) + 0.5f);
	this->elem.width = width;
	this->elem.height = height;
}

void game_hudelem_s::FadeOverTime(float time, color_s color) {
	this->elem.fromColor = this->elem.color;
	this->elem.fadeStartTime = *(uint32_t*)(0x01744A00 + 0x96C);
	this->elem.fadeTime = (short)((time * 1000) + 0.5f);
	this->elem.color = color;
}

void game_hudelem_s::SetShader(const char * shader) {
	this->elem.materialIndex = G_MaterialIndex(shader);
}

void game_hudelem_s::SetText(const char * text) {
	this->elem.text = G_LocalizedStringIndex(text);
}

void game_hudelem_s::SetShaderScale(short width, short height) {
	this->elem.width = width;
	this->elem.height = height;
}

void game_hudelem_s::SetPoint(float x, float y) {
	this->elem.x = x;
	this->elem.y = y;
}

void game_hudelem_s::Free() {
	memset(this, 0x00, sizeof(game_hudelem_s));
}

game_hudelem_s* HudElem_Alloc() {
	for (int i = 20; i < 1024; i++) {
		game_hudelem_s* elem = (game_hudelem_s*)(0x0173B658 + (i * 0x88));
		if (elem->elem.type == 0) {
			return elem;
		}
	}
	return (game_hudelem_s*)0;
}

game_hudelem_s * CreateShader(int clientNum, float x, float y, short width, short height, color_s color, float sort, const char * shader) {
	game_hudelem_s * elem = HudElem_Alloc();
	elem->clientNum = clientNum;
	elem->elem.type = 8;
	elem->SetShader(shader);
	elem->elem.width = width;
	elem->elem.height = height;
	elem->elem.x = x;
	elem->elem.y = y;
	elem->elem.alignOrg = 0x00;
	elem->elem.color = color;
	elem->elem.sort = sort;
	elem->elem.ui3dWindow = 0xFF;
	return elem;
}

game_hudelem_s * CreateFontString(int clientNum, const char * text, float x, float y, float scale, int font, float sort, color_s color) {
	game_hudelem_s * elem = HudElem_Alloc();
	elem->clientNum = clientNum;
	elem->elem.type = 1;
	elem->SetText(text);
	elem->elem.fontScale = scale;
	elem->elem.font = font;
	elem->elem.x = x;
	elem->elem.y = y;
	elem->elem.alignOrg = 0x00;
	elem->elem.color = color;
	elem->elem.sort = sort;
	elem->elem.ui3dWindow = 0xFF;
	return elem;
}
