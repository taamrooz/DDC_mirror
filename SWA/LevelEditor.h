#pragma once
#include "BaseScene.h"
#include "Texture.h"
#include "Animation.h"
#include "TileComponent.h"
#include "EditorObject.h"

enum state
{
	filepicker,
	tile_editor,
	object_editor,
	save
};
class LevelEditor :
	public BaseScene
{
private:
	state state = filepicker;
	int selected_tile_type_ = 0;
	std::vector<TileComponent> tiles_on_grid_;
	std::vector<TileComponent> tiles_in_toolbox_;
	std::vector<EditorObject> objects_on_grid_;
	std::vector<EditorObject> objects_in_toolbox_;
	std::string text_;
	std::string save_file_name_;
	std::vector<Texture*> file_names_;
	Texture* text_texture_ = nullptr;
	Texture* save_text_texture_ = nullptr;
	constexpr static int k_level_width_ = 1280;
	constexpr static int k_total_tiles_ = 300;
	constexpr static int k_tile_height_ = 64;
	constexpr static int k_tile_width_ = 64;
	constexpr static int k_total_sprites_ = 36;
	constexpr static int k_lmb_ = 1;
	constexpr static int k_rmb_ = 3;
	const std::string k_path_ = "Tileset.png";
	int selected_object_;
	void RenderTileGrid();
public:
	LevelEditor(SceneManager* manager);
	void render();
	void RenderTileEditor();
	void RenderFilePicker();
	void RenderObjectEditor();
	void RenderSave();
	void input();
	void InputSave(SDL_Keycode keycode, std::string text);
	void InputFilePicker(SDL_Keycode keycode, std::string text);
	void InputTileEditor(SDL_Keycode keycode);
	void SelectObject(int first, int second);
	void PlaceObject(int first, int second);
	void InputObjectEditor(SDL_Keycode keycode);
	void SelectTile(int x, int y);
	void PlaceTile(int x, int y);
	void GetFiles();
	bool SaveFile();
	void cleanup();
	bool OpenFile(std::string path);
	void CreateEmptyLevel();
	bool init();
	void InitObjects();
};


