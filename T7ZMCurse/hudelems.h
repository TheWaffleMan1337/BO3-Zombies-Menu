#pragma once
#include "TheCurse.h"


union color_s {
	struct {
		char color[4];
	};

	color_s()
	{
		this->color[0] = this->color[1] = this->color[2] = this->color[3] = 0;
	}

	color_s(int r, int g, int b, int a) {
		this->color[0] = r; this->color[1] = g; this->color[2] = b; this->color[3] = a;
	}
};

struct hudelem_s {
	float x;//0x00
	float y;//0x04
	float z;//0x08;
	float fontScale;//0xC
	float fromFontScale;//0x10
	int fontScaleStartTime;//0x14
	color_s color;//0x18
	color_s fromColor;//0x1C
	int fadeStartTime;//0x20
	int scaleStartTime;//0x24
	float fromX;//0x28
	float fromY;//0x2C
	int moveStartTime;//0x30
	int time;//0x34
	int duration;//0x38
	float value;//0x3C
	float sort;//0x40
	color_s glowColor;//0x44
	int fxBirthTime;//0x48
	int flags;//0x4C
	short targetEntNum;//0x50
	short fontScaleTime;//0x52
	short fadeTime;//0x54
	short label;//0x56
	short width;//0x58
	short height; //0x5A
	short fromWidth;//0x5C
	short fromHeight;//0x5E
	short scaleTime;//0x60
	short moveTime;//0x62
	short text;//0x64
	short fxLetterTime;//0x66
	short fxDecayStartTime;//0x68
	short fxDecayDuration;//0x6A
	short fxRedactDecayStartTime;//0x6C
	short fxRedactDecayDuration;//0x6E
	unsigned char type;//0x70
	unsigned char font;//0x71
	unsigned char alignOrg;//0x72
	unsigned char alignScreen;//0x73
	short materialIndex;//0x74
	short offscreenMaterialIndex;//0x76
	unsigned char fromAlignOrg;//0x78
	unsigned char fromAlignScreen;//0x79
	unsigned char soundID;//0x7A
	unsigned char ui3dWindow;
};

struct game_hudelem_s {
	hudelem_s elem;//0x00 - 0x7B
	int clientNum;//0x7C
	int team;//0x80
	int abilityFlag;//0x84

	void MoveOverTime(float time, float x, float y);
	void ScaleFontOverTime(float time, float fontScale);
	void ScaleOverTime(float time, short width, short height);
	void FadeOverTime(float time, color_s color);
	void SetShader(const char * shader);
	void SetText(const char * text);
	void SetShaderScale(short width, short height);
	void SetPoint(float x, float y);
	void Free();
};

game_hudelem_s* HudElem_Alloc();

game_hudelem_s * CreateShader(int clientNum, float x, float y, short width, short height, color_s color, float sort, const char * shader);
game_hudelem_s * CreateFontString(int clientNum, const char * text, float x, float y, float scale, int font, float sort, color_s color);

